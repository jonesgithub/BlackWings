//
//  Medal.cpp
//  BlackWings
//
//  Created by Jacky on 14-5-27.
//
//

#include "Medal.h"
#include "VisibleRect.h"
#include "TextSprite.h"
#include "MenuItemImageLabel.h"
#include "GameStrings.h"
#include "Configuration.h"
#include "MedalRewardsLayer.h"
#include "PlayerBar.h"
#include "ConfigManager.h"


USING_NS_CC;
using namespace cocos2d::ui;

const std::string Medal::eventBack = "eventMedalBack";

bool Medal::init()
{
    if (!Layer::init()) {
        return false;
    }
            
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //panel
    auto panelSize = Size(s_visibleRect.visibleWidth,s_visibleRect.visibleHeight-60);
    
    _cellSize.width = 546;
    _cellSize.height = 140;
    
    //add to sprite frame
    auto sp = Sprite::create("medal_minibox_1.png");
    SpriteFrameCache::getInstance()->addSpriteFrame(SpriteFrame::createWithTexture(sp->getTexture(), sp->getTextureRect()), "medal_minibox_1.png");
    
    _panel = Scale9Sprite::create("windowBox.png");
    _panel->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _panel->setPosition(Point(s_visibleRect.center.x,s_visibleRect.top.y + panelSize.height));
    _panel->setContentSize(panelSize);
    this->addChild(_panel);
    _panel->runAction(MoveTo::create(0.4f,s_visibleRect.top));
    
    //medal_top_panel
    auto medal_data_bk = Sprite::createWithSpriteFrameName("bt_mission_3.png");
    medal_data_bk->setAnchorPoint(Point::ANCHOR_MIDDLE);
    medal_data_bk->setPosition(panelSize.width/2,panelSize.height-70);
    _panel->addChild(medal_data_bk);
    
    auto medal_logo = Sprite::createWithSpriteFrameName("icon_medal.png");
    medal_logo->setAnchorPoint(Point::ANCHOR_MIDDLE);
    medal_logo->setPosition(Point(50,50));
    medal_data_bk->addChild(medal_logo);
    
    auto label_1 = TextSprite::create(s_gameStrings.medalInfo->medaloverstage, s_gameConfig.defaultFontName, 20);
    auto label_2 = TextSprite::create(s_gameStrings.medalInfo->medalusedspcweapon, s_gameConfig.defaultFontName, 20);
    auto label_3 = TextSprite::create(s_gameStrings.medalInfo->medalkillenemy, s_gameConfig.defaultFontName, 20);
    auto label_4 = TextSprite::create(s_gameStrings.medalInfo->medalkillbigenemy, s_gameConfig.defaultFontName, 20);
    label_1->setColor(DIY_COLOR_GRAY2);
    label_2->setColor(DIY_COLOR_GRAY2);
    label_3->setColor(DIY_COLOR_GRAY2);
    label_4->setColor(DIY_COLOR_GRAY2);
    label_1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label_2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label_3->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label_4->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label_1->setPosition(Point(120,70));
    label_2->setPosition(Point(290,70));
    label_3->setPosition(Point(120,30));
    label_4->setPosition(Point(290,30));
    medal_data_bk->addChild(label_1);
    medal_data_bk->addChild(label_2);
    medal_data_bk->addChild(label_3);
    medal_data_bk->addChild(label_4);

    auto label_num1 = TextSprite::create(Value(s_playerConfig.overstage).asString().c_str(), s_gameConfig.defaultFontName, 20);
    auto label_num2 = TextSprite::create(Value(s_playerConfig.usedweapon).asString().c_str(), s_gameConfig.defaultFontName, 20);
    auto label_num3 = TextSprite::create(Value(s_playerConfig.killenemy).asString().c_str(), s_gameConfig.defaultFontName, 20);
    auto label_num4 = TextSprite::create(Value(s_playerConfig.killbigenemy).asString().c_str(), s_gameConfig.defaultFontName, 20);
    label_num1->setColor(DIY_COLOR_BLUE2);
    label_num2->setColor(DIY_COLOR_BLUE2);
    label_num3->setColor(DIY_COLOR_BLUE2);
    label_num4->setColor(DIY_COLOR_BLUE2);
    label_num1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label_num2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label_num3->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label_num4->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    label_num1->setPosition(Point(230,70));
    label_num2->setPosition(Point(440,70));
    label_num3->setPosition(Point(230,30));
    label_num4->setPosition(Point(440,30));
    medal_data_bk->addChild(label_num1);
    medal_data_bk->addChild(label_num2);
    medal_data_bk->addChild(label_num3);
    medal_data_bk->addChild(label_num4);
    

    
    //listview
    listView = ListView::create();
    // set list view ex direction
    listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
    listView->setTouchEnabled(true);
    listView->setBounceEnabled(true);
    listView->setSize(Size(panelSize.width, panelSize.height - 150));
    listView->setPosition(Point(0,20));
    listView->addEventListenerListView(this, listvieweventselector(Medal::selectedItemEvent));
    _panel->addChild(listView);
    
    //init listview
    initListviewItem();
    
    // set all items layout gravity
    listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
    
    // set items margin
    listView->setItemsMargin(2.0f);
    
    listView->_allContentSize = Size(listView->getContentSize().width, MEDAL_MAX*_cellSize.height);
    
    //scorll
    auto call1 = CallFunc::create([=](){
                listView->scrollToBottom(0.1f, false);
                              });
    
    auto call2 = CallFunc::create([=](){
        listView->scrollToTop(0.4f, true);
    });
    runAction(Sequence::create(call1, call2, NULL));
    
    
    //closebtn
    auto itemClosed = MenuItemImageLabel::createWithFrameName("back_0.png","back_1.png",
                                                              CC_CALLBACK_1(Medal::menuCallbackClosed,this));
    itemClosed->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    itemClosed->setPosition((s_visibleRect.visibleWidth + panelSize.width)/2,panelSize.height);
    
    auto menu = Menu::create( itemClosed, nullptr);
    menu->setPosition(Point::ZERO);
    _panel->addChild(menu,3);
    
    return true;
}

void Medal::initListviewItem()
{
    for (int i = 0; i < MEDAL_MAX; ++i)
    {
        Layout *custom_item = Layout::create();
        custom_item->setSize(_cellSize);

        Sprite* item_bk =nullptr;
        if(s_playerConfig.medallocked[i])
            item_bk = Sprite::create("medal_minibox_1.png");
        else
            item_bk = Sprite::createWithSpriteFrameName("medal_minibox_0.png");
        item_bk->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        custom_item->addChild(item_bk, 0, 20);
        
        Sprite* item_image_bk = nullptr;
        if (s_playerConfig.medallocked[i]) {
            item_image_bk = Sprite::createWithSpriteFrameName("icon_medal_box_1.png");
        }
        else{
            item_image_bk = Sprite::createWithSpriteFrameName("icon_medal_box_0.png");
        }
        item_image_bk->setAnchorPoint(Point::ANCHOR_MIDDLE);
        item_image_bk->setPosition(Point(70,_cellSize.height/2-10));
        custom_item->addChild(item_image_bk, 0, 30);
        
        Sprite* item_got_icon = Sprite::createWithSpriteFrameName("icon_get.png");
        item_got_icon->setPosition(476, 35);
        custom_item->addChild(item_got_icon, 0, 120);
        
        auto callback = [=](Ref* ref){
            log("callback is %d", i);
            if (s_playerConfig.medalget[i]) {
                PLAY_GETGEM_EFFECT;
                //s_gameConfig.medal_reward_callbacks[cell->getIdx()]();
                s_playerConfig.gem+=s_medalRewards[i][0];
                s_playerConfig.weaponCount[0]+=s_medalRewards[i][1];
                
                s_playerConfig.weaponCount[0] = s_playerConfig.weaponCount[0] < s_weaponConfigs[0][s_playerConfig.weaponslevel[0]].capacity ?
                s_playerConfig.weaponCount[0] : s_weaponConfigs[0][s_playerConfig.weaponslevel[0]].capacity;
                
                s_playerConfig.weaponCount[1]+=s_medalRewards[i][2];
                
                s_playerConfig.weaponCount[1] = s_playerConfig.weaponCount[1] < s_weaponConfigs[1][s_playerConfig.weaponslevel[1]].capacity ?
                s_playerConfig.weaponCount[1] : s_weaponConfigs[1][s_playerConfig.weaponslevel[1]].capacity;
                
                s_playerConfig.weaponCount[2]+=s_medalRewards[i][3];
                
                s_playerConfig.weaponCount[2] = s_playerConfig.weaponCount[2] < s_weaponConfigs[2][s_playerConfig.weaponslevel[2]].capacity ?
                s_playerConfig.weaponCount[2] : s_weaponConfigs[2][s_playerConfig.weaponslevel[2]].capacity;
                
                s_playerConfig.medalget[i] = false;
                auto layer = MedalRewardsLayer::create(s_medalRewards[i][0],
                                                       s_medalRewards[i][1],
                                                       s_medalRewards[i][2],
                                                       s_medalRewards[i][3]);
                this->addChild(layer,4);
                
                //save
                ConfigManager::getInstance()->saveConfig();
                
                //update weaponcount
                _eventDispatcher->dispatchCustomEvent(GameConfig::eventUpdateMenuItemWeaponData,(void*)0);
                _eventDispatcher->dispatchCustomEvent(GameConfig::eventUpdateMenuItemWeaponData,(void*)1);
                _eventDispatcher->dispatchCustomEvent(GameConfig::eventUpdateMenuItemWeaponData,(void*)2);
                
                //update gem
                _eventDispatcher->dispatchCustomEvent(GameConfig::eventUpdateGem);
                
                //ui
                refreshAllItems();
            }
            
        };
        MenuItemImageLabel* btnGetBonus = MenuItemImageLabel::createWithFrameName("bt_buy_gem_0.png", "bt_buy_gem_4.png", callback, s_gameStrings.medalInfo->getbonus, GameConfig::defaultFontName, 25);
        btnGetBonus->setPosition(453, 45);
        btnGetBonus->setTag(110);
        btnGetBonus->setTextColor(DIY_COLOR_YELLOW3,Color3B::BLACK);
        auto menuGetBonus = Menu::create(btnGetBonus, nullptr);
        menuGetBonus->setPosition(Point::ZERO);
        custom_item->addChild(menuGetBonus, 0, 111);
        
        item_got_icon->setVisible(false);
        btnGetBonus->setVisible(false);
        
        if(s_playerConfig.medallocked[i])
        {
            btnGetBonus->setVisible(true);
            btnGetBonus->setEnabled(false);
            btnGetBonus->selected();
            item_got_icon->setVisible(false);
        }
        else
        {
            if (s_playerConfig.medalget[i]) {
                btnGetBonus->setVisible(true);
                btnGetBonus->setEnabled(true);
                btnGetBonus->unselected();
                item_got_icon->setVisible(false);
            }
            else
            {
                btnGetBonus->setVisible(false);
                item_got_icon->setVisible(true);
            }
        }
        
        char iconFileName[30];
        if(s_playerConfig.medallocked[i])
            sprintf(iconFileName,"icon_medal_%d_0.png",i+1);
        else
            sprintf(iconFileName,"icon_medal_%d.png",i+1);
        
        auto item_image=Sprite::createWithSpriteFrameName(iconFileName);
        item_image->setAnchorPoint(Point::ANCHOR_MIDDLE);
        item_image->setPosition(Point(70,_cellSize.height/2-5));
        custom_item->addChild(item_image,0,40);
        
        auto infoSprite_1 = TextSprite::create(s_gameStrings.medalInfo->medalname[i],GameConfig::defaultFontName,27,
                                               Size(_cellSize.width - 200,_cellSize.height - 30),TextHAlignment::LEFT,TextVAlignment::CENTER);
        infoSprite_1->setPosition(Point(_cellSize.width /2+50,_cellSize.height /2+30));
        if(s_playerConfig.medallocked[i])
            infoSprite_1->setColor(DIY_COLOR_GRAY3);
        else
            infoSprite_1->setColor(DIY_COLOR_YELLOW2);
        custom_item->addChild(infoSprite_1,0,50);
        
        auto infoSprite_2 = TextSprite::create(s_gameStrings.medalInfo->medaldscr[i],GameConfig::defaultFontName,22,
                                               Size(_cellSize.width - 200,_cellSize.height - 30),TextHAlignment::LEFT,TextVAlignment::CENTER);
        infoSprite_2->setPosition(Point(_cellSize.width /2+50,_cellSize.height /2-10));
        infoSprite_2->setColor(DIY_COLOR_GRAY3);
        custom_item->addChild(infoSprite_2,0,60);

        
        listView->pushBackCustomItem(custom_item);
    }
}

void Medal::refreshAllItems()
{
    for (int i = 0; i < MEDAL_MAX; ++i)
    {
        auto custom_item = listView->getItem(i);
        
        Sprite* item_bk =static_cast<Sprite*>(custom_item->getChildByTag(20));
        if(s_playerConfig.medallocked[i])
            item_bk->setTexture("medal_minibox_1.png");
        else
            item_bk->setSpriteFrame("medal_minibox_0.png");
        
        Sprite* item_image_bk = static_cast<Sprite*>(custom_item->getChildByTag(30));
        if (s_playerConfig.medallocked[i]) {
            item_image_bk->setSpriteFrame("icon_medal_box_1.png");
        }
        else{
            item_image_bk->setSpriteFrame("icon_medal_box_0.png");
        }
        
        Sprite* item_got_icon = static_cast<Sprite*>(custom_item->getChildByTag(120));
        
        MenuItemImageLabel* btnGetBonus = static_cast<MenuItemImageLabel*>(custom_item->getChildByTag(111)->getChildByTag(110));;
        
        item_got_icon->setVisible(false);
        btnGetBonus->setVisible(false);
        
        if(s_playerConfig.medallocked[i])
        {
            btnGetBonus->setVisible(true);
            btnGetBonus->setEnabled(false);
            btnGetBonus->selected();
            item_got_icon->setVisible(false);
        }
        else
        {
            if (s_playerConfig.medalget[i]) {
                btnGetBonus->setVisible(true);
                btnGetBonus->setEnabled(true);
                btnGetBonus->unselected();
                item_got_icon->setVisible(false);
            }
            else
            {
                btnGetBonus->setVisible(false);
                item_got_icon->setVisible(true);
            }
        }
        
        char iconFileName[30];
        if(s_playerConfig.medallocked[i])
            sprintf(iconFileName,"icon_medal_%d_0.png",i+1);
        else
            sprintf(iconFileName,"icon_medal_%d.png",i+1);
        
        auto item_image=static_cast<Sprite*>(custom_item->getChildByTag(40));
        item_image->setSpriteFrame(iconFileName);
        
        auto infoSprite_1 = static_cast<TextSprite*>(custom_item->getChildByTag(50));
        if(s_playerConfig.medallocked[i])
            infoSprite_1->setColor(DIY_COLOR_GRAY3);
        else
            infoSprite_1->setColor(DIY_COLOR_YELLOW2);
        
        auto infoSprite_2 = static_cast<TextSprite*>(custom_item->getChildByTag(60));
        CC_UNUSED_PARAM(infoSprite_2);
    }
}

void Medal::selectedItemEvent(Ref *pSender, ui::ListViewEventType type)
{
    
}

void Medal::menuCallbackClosed(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    _eventDispatcher->dispatchCustomEvent(GameConfig::eventShowHideMedalLogo);
    //listView->scrollToBottom(0.5f, false);
    //this->runAction(FadeTo::create(0.15f,0));
    listView->scrollToBottom(1.0f, false);
    auto action = Sequence::create(
                                   MoveBy::create(0.15f, Point(0,s_visibleRect.visibleHeight * 0.8f)),
                                   CallFunc::create(
                                                    [&](){
                                                        _eventDispatcher->dispatchCustomEvent(Medal::eventBack);
                                                        
                                                        this->removeFromParentAndCleanup(true);
                                                    }  ),nullptr);
    _panel->runAction(action);
}