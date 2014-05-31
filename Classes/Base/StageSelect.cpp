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
        s_playerConfig.overstage = 20;
        _selectItem = s_playerConfig.overstage;
        _noTouch = true ;
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        auto panelSize = Size(568,s_visibleRect.visibleHeight * 0.88f);//s_visibleRect.visibleWidth - 97
        auto panelCenterX = panelSize.width / 2.0f;

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
        auto left_door = Sprite::create("door_l.png");
        auto right_door = Sprite::create("door_r.png");
        left_door->setScale(0.95f, 0.78f);
        right_door->setScale(0.95f, 0.78f);
        left_door->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        right_door->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        left_door->setPosition(Point(panelSize.width/2+20,panelSize.height/2-35));
        right_door->setPosition(Point(panelSize.width/2-20,panelSize.height/2-35));
        _panel->addChild(left_door,2);
        _panel->addChild(right_door,2);

        
        auto actionmovedone = CallFunc::create(
                                        [=](){
                                            left_door->runAction(ScaleTo::create(0.5f, 0, 1.0f));
                                            right_door->runAction(ScaleTo::create(0.5f, 0, 1.0f));
                                        });
        _panel->runAction(Sequence::create(MoveTo::create(0.15f,s_visibleRect.top),
                                           actionmovedone,nullptr));

        auto tableView = TableView::create(this, Size(panelSize.width, panelSize.height - 335));
        tableView->setDirection(ScrollView::Direction::VERTICAL);
        tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
        tableView->setPosition(Point(0,132));
        tableView->setDelegate(this);
        tableView->reloadData();
        _panel->addChild(tableView);
        
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
        log("aaaaaaaaaaaa");
        if(_noTouch && idx==_selectItem)
        {selected_cell = cell;}
    }
    else
    {
        auto item_bk = (Sprite*)cell->getChildByTag(10)->getChildByTag(20);
        if(idx <= s_playerConfig.overstage)
            item_bk->setSpriteFrame("bt_mission_0.png");
        else
            item_bk->setSpriteFrame("bt_mission_1.png");
        
//        auto item_hl = (Sprite*)cell->getChildByTag(10)->getChildByTag(30);
//        item_hl->setSpriteFrame("bt_mission_3.png");
//        item_hl->setVisible(false);
        
        std::string stage_text_str = s_gameStrings.mainMenu->stagetext + " - " + Value((int)idx+1).asString();
        auto stage_text = (TextSprite*)cell->getChildByTag(10)->getChildByTag(40);
        stage_text->setText(stage_text_str);
        if(idx<=s_playerConfig.overstage)
            stage_text->setColor(Color3B(230,230,230));
        else
            stage_text->setColor(Color3B(80,80,80));
        
        if(_selectItem == idx)
            cell->getChildByTag(10)->getChildByTag(30)->setVisible(true);
        else
            cell->getChildByTag(10)->getChildByTag(30)->setVisible(false);
        
        if(_noTouch && idx==_selectItem)
        {selected_cell = cell;
            cell->getChildByTag(10)->getChildByTag(30)->setVisible(true);}
        log("bbbbbbbbbbbbb");
        
    }

    return cell;
}

void StageSelect::tableCellTouched(extension::TableView* table, extension::TableViewCell* cell)
{
    _noTouch = false;
    if(cell->getIdx()<=s_playerConfig.overstage)
    {
        if(selected_cell)
        {
            selected_cell->getChildByTag(10)->getChildByTag(30)->setVisible(false);
//            auto stage_text = (TextSprite*)cell->getChildByTag(10)->getChildByTag(40);
//            stage_text->setColor(Color3B(230,230,230));
        }
        _selectItem = cell->getIdx();
        cell->getChildByTag(10)->getChildByTag(30)->setVisible(true);
//        auto stage_text = (TextSprite*)cell->getChildByTag(10)->getChildByTag(40);
//        stage_text->setColor(Color3B(0,0,255));
        selected_cell = cell;
        log("====>%d",_selectItem);
    }
}


//void StageSelect::tableCellHighlight(extension::TableView* table, extension::TableViewCell* cell)
//{
//    if (cell->getIdx()<=s_gameConfig.treasure.overStage) {
//        cell->getChildByTag(10)->getChildByTag(30)->setVisible(true);
//        auto stage_text = (TextSprite*)cell->getChildByTag(10)->getChildByTag(40);
//        stage_text->setColor(Color3B(0,0,255));
//    }
//}

//void StageSelect::tableCellUnhighlight(extension::TableView* table, extension::TableViewCell* cell)
//{
//    if (cell->getIdx()<=s_gameConfig.treasure.overStage) {
//    cell->getChildByTag(10)->getChildByTag(30)->setVisible(false);
//    auto stage_text = (TextSprite*)cell->getChildByTag(10)->getChildByTag(40);
//    stage_text->setColor(Color3B(230,230,230));
//    }
//}

void StageSelect::menuCallbackFight(Ref *sender)
{
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
    this->runAction(FadeTo::create(0.15f,0));
    auto action = Sequence::create(
        MoveBy::create(0.15f, Point(0,s_visibleRect.visibleHeight * 0.8f)),
        CallFunc::create(
        [&](){
            _eventDispatcher->dispatchCustomEvent(StageSelect::eventBack);

            this->removeFromParentAndCleanup(true);
    }  ),nullptr);
    _panel->runAction(action);
}

Node* StageSelect::getItemNode(int i)
{
    auto item = Node::create();
    Sprite* item_bk = nullptr;
    if(i<=s_playerConfig.overstage)
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
    if(i<=s_playerConfig.overstage)
        stage_text->setColor(Color3B(230,230,230));
    else
        stage_text->setColor(Color3B(80,80,80));
    stage_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
    stage_text->setPosition(Point(_cellSize.width/2,_cellSize.height/2));
    stage_text->setTag(40);
    item->addChild(stage_text);

    return item;
}
