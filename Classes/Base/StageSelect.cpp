#include "StageSelect.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "Battleground.h"

USING_NS_CC_EXT;

const std::string StageSelect::eventBack = "eventStageSelsctBack";

bool StageSelect::init()
{
    if (Layer::init())
    {
        selected_cell = nullptr;
        
        s_playerConfig.overstage =46;
        
        _selectItem = s_playerConfig.overstage+1;
        _noTouch = true ;
        isCloseClick = true;
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        auto panelSize = Size(520,s_visibleRect.visibleHeight * 0.88f);//s_visibleRect.visibleWidth - 97

        _cellSize.width = panelSize.width;
        _cellSize.height = 100;

        _panel = Scale9Sprite::create("mission.png");
        _panel->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        _panel->setPosition(Point(s_visibleRect.center.x,s_visibleRect.top.y + panelSize.height));
        _panel->setContentSize(panelSize);
        this->addChild(_panel);
        
        auto stageselect_text = TextSprite::create(s_gameStrings.mainMenu->stageselect.c_str());
        stageselect_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        stageselect_text->setPosition(Point(panelSize.width/2, panelSize.height-170));
        _panel->addChild(stageselect_text);
        
        //door effect.
        left_door = Sprite::create("door_l.png");
        right_door = Sprite::create("door_r.png");
        left_door->setScale(1.0f, 0.9f);
        right_door->setScale(1.0f, 0.9f);
        left_door->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        right_door->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        left_door->setPosition(Point(panelSize.width/2+25,panelSize.height/2-39));
        right_door->setPosition(Point(panelSize.width/2-25,panelSize.height/2-39));
        _panel->addChild(left_door,2);
        _panel->addChild(right_door,2);

        
        auto actionmovedone = CallFunc::create(
                                        [=](){
                                            PLAY_OPENDOOR_EFFECT;
                                            auto size = left_door->getContentSize();
                                            auto move = MoveBy::create(0.5, Point(-(size.width), 0));
                                            left_door->runAction(move);
                                            left_door->runAction(ScaleTo::create(0.5, 0, 0.9f));
                                            auto move1 = move->reverse();
                                            right_door->runAction(move1);
                                            right_door->runAction(Sequence::create(ScaleTo::create(0.5, 0, 0.9f),
                                                                                   CallFunc::create([=]()
                                                                                                    {
                                                                                                        PLAY_STAGELIST_EFFECT;
                                                                                                        isCloseClick = false;
                                                                                                        if(s_playerConfig.overstage>0 && s_playerConfig.overstage<47)
                                                                                                        tableView->setContentOffsetInDuration(tableView->getContentOffset() + Point(0,_cellSize.height*(s_playerConfig.overstage-1)),s_playerConfig.overstage*0.02f);
                                                                                                    }),
                                                                                   nullptr));
                                        });
        _panel->runAction(Sequence::create(MoveTo::create(0.15f,s_visibleRect.top),
                                           DelayTime::create(0.3f),
                                           actionmovedone,nullptr));

        tableView = TableView::create(this, Size(panelSize.width, panelSize.height - 345));
        tableView->setDirection(ScrollView::Direction::VERTICAL);
        tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
        tableView->setPosition(Point(0,135));
        tableView->setDelegate(this);
        tableView->reloadData();
        _panel->addChild(tableView,0);
        tableView->setTouchEnabled(false);
        runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){tableView->setTouchEnabled(true);}), nullptr));
        
        auto itemClosed = MenuItemImageLabel::createWithFrameName("back_0.png","back_1.png",
            CC_CALLBACK_1(StageSelect::menuCallbackClosed,this));
        itemClosed->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
        itemClosed->setPosition((s_visibleRect.visibleWidth + panelSize.width)/2,panelSize.height);

        auto itemFight = MenuItemImageLabel::createWithFrameName("btA_0.png","btA_1.png",
            CC_CALLBACK_1(StageSelect::menuCallbackFight,this), s_gameStrings.mainMenu->stage_fight.c_str());
        itemFight->setPosition(Point(panelSize.width / 2,77));
        itemFight->setTextColor(Color3B(255, 255, 0));
        
        auto menu = Menu::create( itemClosed, itemFight, nullptr);
        menu->setPosition(Point::ZERO);
        _panel->addChild(menu);
        
        addBall();

        return true;
    }

    return false;
}

cocos2d::extension::TableViewCell* StageSelect::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    auto cell = table->dequeueCell();
    
    if (!cell)
    {
        cell = TableViewCell::create();

        /*auto icon = Sprite::createWithSpriteFrameName(iconFileName);
        icon->setPosition(Point(50,_cellSize.height /2));
        cell->addChild(icon,0,10);*/

        auto cell_node = getItemNode(idx);
        cell->addChild(cell_node,0,10);
        if(_noTouch && idx==_selectItem)
        {selected_cell = cell;}
        
        log("!cell.....%d",idx);
    }
    else
    {
        log("cell.....%d",idx);
        auto item_bk = (Sprite*)cell->getChildByTag(10)->getChildByTag(20);
        if(idx <= s_playerConfig.overstage+1)
            item_bk->setSpriteFrame("bt_mission_0.png");
        else
            item_bk->setSpriteFrame("bt_mission_1.png");
        
//        auto item_hl = (Sprite*)cell->getChildByTag(10)->getChildByTag(30);
//        item_hl->setSpriteFrame("bt_mission_3.png");
//        item_hl->setVisible(false);
        
        std::string stage_text_str = s_gameStrings.mainMenu->stagetext + " - " + Value((int)idx+1).asString();
        auto stage_text = (TextSprite*)cell->getChildByTag(10)->getChildByTag(40);
        stage_text->setText(stage_text_str);
        if(idx<=s_playerConfig.overstage+1)
            stage_text->setColor(Color3B(230,230,230));
        else
            stage_text->setColor(Color3B(80,80,80));
        
        if(_selectItem == idx)
            cell->getChildByTag(10)->getChildByTag(30)->setVisible(true);
        else
            cell->getChildByTag(10)->getChildByTag(30)->setVisible(false);
        
        if(_noTouch && idx==_selectItem)
        {
            selected_cell = cell;
            cell->getChildByTag(10)->getChildByTag(30)->setVisible(true);
        }
        
        if (s_playerConfig.overstage +1 == idx) {
            cell->getChildByTag(10)->getChildByTag(50)->setVisible(true);
        }
        else{
            cell->getChildByTag(10)->getChildByTag(50)->setVisible(false);
        }
        
        ((RotateBall*)cell->getChildByTag(10)->getChildByTag(60))->resetIdx(idx);
        
        if(idx<=s_playerConfig.overstage+1)
            cell->getChildByTag(10)->getChildByTag(70)->setVisible(false);
        else
            cell->getChildByTag(10)->getChildByTag(70)->setVisible(true);
    }

    return cell;
}

void StageSelect::tableCellTouched(extension::TableView* table, extension::TableViewCell* cell)
{
    _noTouch = false;
    if(cell->getIdx()<=s_playerConfig.overstage+1)
    {
        if(selected_cell)
        {
            selected_cell->getChildByTag(10)->getChildByTag(30)->setVisible(false);
        }
        _selectItem = cell->getIdx();
        cell->getChildByTag(10)->getChildByTag(30)->setVisible(true);
        selected_cell = cell;
        log("====>%d",_selectItem);
        rotateBall->resetIdx(_selectItem);
        int posy = (STAGE_COUNT - _selectItem)*100-50;
        rotateBall->setPositionY(posy);
    }
}

void StageSelect::menuCallbackFight(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    auto battle = Battleground::create(_selectItem);
    Director::getInstance()->replaceScene(battle);
}

cocos2d::Size StageSelect::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return _cellSize;
}

ssize_t StageSelect::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return 50;
}

void StageSelect::menuCallbackClosed(Ref *sender)
{
    if(!isCloseClick)
    {
        PLAY_BUTTON_EFFECT;
        isCloseClick = true;
        
        this->runAction(FadeTo::create(0.15f,0));
        tableView->setTouchEnabled(false);
        
        auto actionmovedone = CallFunc::create(
                                               [=](){
                                                   PLAY_OPENDOOR_EFFECT;
                                                   auto size = left_door->getContentSize();
                                                   auto move = MoveBy::create(0.5, Point((size.width+20), 0));
                                                   left_door->runAction(move);
                                                   left_door->runAction(ScaleTo::create(0.5, 1.08, 0.9f));
                                                   auto move1 = move->reverse();
                                                   right_door->runAction(move1);
                                                   right_door->runAction(ScaleTo::create(0.5, 1.08, 0.9f));
                                               });
        auto action = Sequence::create(
                                       actionmovedone,
                                       DelayTime::create(0.6f),
                                       MoveBy::create(0.15f, Point(0,s_visibleRect.visibleHeight * 0.8f)),
                                       CallFunc::create(
                                                        [&](){
                                                            _eventDispatcher->dispatchCustomEvent(StageSelect::eventBack);
                                                            
                                                            this->removeFromParentAndCleanup(true);
                                                        }  ),nullptr);
        _panel->runAction(action);
    }
}

Node* StageSelect::getItemNode(int i)
{
    auto item = Node::create();
    Sprite* item_bk = nullptr;
    if(i<=s_playerConfig.overstage+1)
        item_bk = Sprite::createWithSpriteFrameName("bt_mission_0.png");
    else
        item_bk = Sprite::createWithSpriteFrameName("bt_mission_1.png");
    item->setAnchorPoint(Point::ANCHOR_MIDDLE);
    item_bk->setPosition(Point(_cellSize.width/2,_cellSize.height/2));
    item_bk->setTag(20);
    item->addChild(item_bk);
    
    auto item_hl = Sprite::createWithSpriteFrameName("bt_mission_3.png");
    item_hl->setAnchorPoint(Point::ANCHOR_MIDDLE);
    item_hl->setPosition(Point(_cellSize.width/2,_cellSize.height/2));
    item_hl->setTag(30);
    item_hl->setVisible(false);
    item->addChild(item_hl);
    
    if(i == _selectItem)
        item_hl->setVisible(true);
    else
        item_hl->setVisible(false);
    
    if(_noTouch && i==_selectItem)
        item_hl->setVisible(true);
    
    std::string stage_text_str = s_gameStrings.mainMenu->stagetext + " - " + Value(i+1).asString();
    auto stage_text = TextSprite::create(stage_text_str,GameConfig::defaultFontName,GameConfig::defaultFontSize);
    if(i<=s_playerConfig.overstage+1)
        stage_text->setColor(Color3B(230,230,230));
    else
        stage_text->setColor(Color3B(80,80,80));
    stage_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
    stage_text->setPosition(Point(_cellSize.width/2,_cellSize.height/2));
    stage_text->setTag(40);
    item->addChild(stage_text);
    
    auto sp_new = Sprite::createWithSpriteFrameName("icon_new.png");
    sp_new->setAnchorPoint(Point::ANCHOR_MIDDLE);
    sp_new->setPosition(Point(_cellSize.width/2+150,_cellSize.height/2));
    sp_new->setTag(50);
    sp_new->setVisible(false);
    item->addChild(sp_new);
    
    if (s_playerConfig.overstage +1 == i) {
        sp_new->setVisible(true);
    }
    

    auto ball = RotateBall::createWithIdx(i);
    ball->setAnchorPoint(Point::ANCHOR_MIDDLE);
    ball->setPosition(100, 50);
    ball->setTag(60);
    item->addChild(ball);
    ball->setRotate(true);
    
    auto ball_mask = Sprite::createWithSpriteFrameName("icon_planet_mask.png");
    ball_mask->setOpacity(120);
    ball_mask->setScale(0.8f);
    ball_mask->setAnchorPoint(Point::ANCHOR_MIDDLE);
    ball_mask->setPosition(100, 50);
    ball_mask->setTag(70);
    item->addChild(ball_mask);
    if(i<=s_playerConfig.overstage+1)
        ball_mask->setVisible(false);
    else
        ball_mask->setVisible(true);
    
    
    return item;
}

void StageSelect::addBall()
{
    rotateBall = RotateBall::createWithIdx(_selectItem);
    rotateBall->setAnchorPoint(Point::ANCHOR_MIDDLE);
    int posy = (STAGE_COUNT - _selectItem)*100-50;
    rotateBall->setPosition(Point(102,posy));
    tableView->addChild(rotateBall,6);
    rotateBall->setRotate(true);
}
