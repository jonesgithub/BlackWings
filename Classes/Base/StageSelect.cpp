#include "StageSelect.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "Battleground.h"
#include "RotateBall.h"


USING_NS_CC_EXT;
using namespace cocos2d::ui;

const std::string StageSelect::eventBack = "eventStageSelsctBack";

bool StageSelect::init()
{
    if (Layer::init())
    {
        
        s_playerConfig.overstage =10;
        
        _selectItem = s_playerConfig.overstage+1;
        isCloseClick = true;
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        auto panelSize = Size(520,s_visibleRect.visibleHeight * 0.88f);//s_visibleRect.visibleWidth - 97
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
//                                                                                                        if(s_playerConfig.overstage>0 && s_playerConfig.overstage<47)
//                                                                                                        tableView->setContentOffsetInDuration(tableView->getContentOffset() + Point(0,_cellSize.height*(s_playerConfig.overstage-1)),s_playerConfig.overstage*0.02f);
                                                                                                    }),
                                                                                   nullptr));
                                        });
        _panel->runAction(Sequence::create(MoveTo::create(0.15f,s_visibleRect.top),
                                           DelayTime::create(0.3f),
                                           actionmovedone,nullptr));
        
        //listview
        listView = ListView::create();
        listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
        listView->setTouchEnabled(true);
        listView->setBounceEnabled(true);
        listView->setSize(Size(panelSize.width, panelSize.height - 335));
        listView->setPosition(Point(0,132));
        listView->addEventListenerListView(this, listvieweventselector(StageSelect::selectedItemEvent));
        _panel->addChild(listView);
        
        //init listview
        initListviewItem();
        
        // set all items layout gravity
        listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
        
        // set items margin
        listView->setItemsMargin(2.0f);

        
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

void StageSelect::initListviewItem()
{
    for (int i = 0; i < STAGE_COUNT; ++i)
    {
        Layout *custom_item = Layout::create();
        custom_item->setSize(_cellSize);
        
        Button* item_bk = nullptr;
        if(i<=s_playerConfig.overstage+1)
            item_bk = Button::create("bt_mission_00.png","bt_mission_00.png");
        else
            item_bk = Button::create("bt_mission_01.png","bt_mission_01.png");
        item_bk->setPosition(Point(_cellSize.width/2,_cellSize.height/2));
        custom_item->addChild(item_bk,0,20);
        
        auto item_hl = Sprite::createWithSpriteFrameName("bt_mission_3.png");
        item_hl->setAnchorPoint(Point::ANCHOR_MIDDLE);
        item_hl->setPosition(Point(_cellSize.width/2,_cellSize.height/2));
        item_hl->setVisible(false);
        custom_item->addChild(item_hl,0,30);
        
        if (_selectItem == i)
            item_hl->setVisible(true);
        else
            item_hl->setVisible(false);
        
        
        std::string stage_text_str = s_gameStrings.mainMenu->stagetext + " - " + Value(i+1).asString();
        auto stage_text = TextSprite::create(stage_text_str,GameConfig::defaultFontName,GameConfig::defaultFontSize);
        if(i<=s_playerConfig.overstage+1)
            stage_text->setColor(Color3B(230,230,230));
        else
            stage_text->setColor(Color3B(80,80,80));
        stage_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        stage_text->setPosition(Point(_cellSize.width/2,_cellSize.height/2));
        stage_text->setTag(40);
        custom_item->addChild(stage_text,0,40);
        
        if (_selectItem == i) {
            auto sp_new = Sprite::createWithSpriteFrameName("icon_new.png");
            sp_new->setAnchorPoint(Point::ANCHOR_MIDDLE);
            sp_new->setPosition(Point(_cellSize.width/2+150,_cellSize.height/2));
            sp_new->setTag(50);
            custom_item->addChild(sp_new,0,50);
        }
        
        if (_selectItem == i) {
        auto ball = RotateBall::createWithIdx(13);
        ball->setAnchorPoint(Point::ANCHOR_MIDDLE);
        ball->setPosition(Point(100,_cellSize.height/2));
        custom_item->addChild(ball,0,60);
        }
        listView->pushBackCustomItem(custom_item);
    }
}

void StageSelect::selectedItemEvent(Ref *pSender, ui::ListViewEventType type)
{
    switch (type)
    {
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
        {
            
        }
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
        {
            
        }
        default:
            break;
    }
    int touchindex = listView->getCurSelectedIndex();
    if (touchindex <= s_playerConfig.overstage+1 && touchindex != _selectItem) {
        listView->getItem(_selectItem)->getChildByTag(30)->setVisible(false);
        listView->getItem(touchindex)->getChildByTag(30)->setVisible(true);
        _selectItem = touchindex;
    }
}

void StageSelect::menuCallbackFight(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    auto battle = Battleground::create(_selectItem);
    Director::getInstance()->replaceScene(battle);
}

void StageSelect::menuCallbackClosed(Ref *sender)
{
    if(!isCloseClick)
    {
        PLAY_BUTTON_EFFECT;
        isCloseClick = true;
        //listView->setTouchEnabled(false);
        
        this->runAction(FadeTo::create(0.15f,0));
        
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

void StageSelect::update(float dt)
{
    
}