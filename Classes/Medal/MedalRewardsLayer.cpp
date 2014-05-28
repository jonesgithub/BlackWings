//
//  MedalRewardsLayer.cpp
//  BlackWings
//
//  Created by Jacky on 14-5-28.
//
//

#include "MedalRewardsLayer.h"
#include "VisibleRect.h"
#include "extensions/cocos-ext.h"
#include "MenuItemImageLabel.h"
#include "TextSprite.h"
#include "GameStrings.h"
#include "Configuration.h"

USING_NS_CC;
USING_NS_CC_EXT;

MedalRewardsLayer* MedalRewardsLayer::create(int money, int starboom, int laser, int blackhole)
{
    auto pRet = new MedalRewardsLayer();
    if (pRet && pRet->init(money, starboom, laser, blackhole))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool MedalRewardsLayer::init(int money, int starboom, int laser, int blackhole)
{
    if(!Layer::init())
        return false;
    
    //todo:语言
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto panelSize = Size(s_visibleRect.visibleWidth-100,s_visibleRect.visibleHeight-500);
    
    auto _panel = Scale9Sprite::create("windowBox.png");
    _panel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    _panel->setPosition(Point(s_visibleRect.center.x,s_visibleRect.center.y + 100));
    _panel->setContentSize(panelSize);
    this->addChild(_panel);
    _panel->setScale(0.1f);
    _panel->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f),
                                       ScaleTo::create(0.1f, 0.9f),
                                       ScaleTo::create(0.1f, 1.0f),
                                       nullptr));
    
    auto itemClosed = MenuItemImageLabel::createWithFrameName("close_0.png","close_1.png",
                                                              CC_CALLBACK_1(MedalRewardsLayer::menuCallbackClosed,this));
    itemClosed->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    itemClosed->setPosition((s_visibleRect.visibleWidth + panelSize.width)/2-5,panelSize.height+35);
    
    auto menu = Menu::create( itemClosed, nullptr);
    menu->setPosition(Point::ZERO);
    _panel->addChild(menu,3);
    
    _money = money;
    _starboom = starboom;
    _laser = laser;
    _blackhole = blackhole;
    
    auto tips = TextSprite::create(s_gameStrings.medalInfo->medalrewardstip,GameConfig::defaultFontName,30,
                                           Size(500,30),TextHAlignment::CENTER,TextVAlignment::CENTER);
    tips->setColor(Color3B(255, 255, 0));
    tips->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tips->setPosition(Point(panelSize.width/2,panelSize.height/2+120));
    _panel->addChild(tips,3);
    
    if(_starboom == 0 && _laser == 0 && _blackhole == 0)
    {
        auto icon = Sprite::createWithSpriteFrameName("icon_gem.png");
        icon->setPosition(panelSize.width/2-50, panelSize.height/2);
        _panel->addChild(icon);
        
        auto label = Label::createWithSystemFont(Value(_money).asString().c_str(), s_gameConfig.defaultFontName, s_gameConfig.defaultFontSize);
        label->setPosition(panelSize.width/2+50,panelSize.height/2);
        label->setColor(Color3B(255, 255, 0));
        _panel->addChild(label);
    }
    else
    {
        auto icon1 = Sprite::createWithSpriteFrameName("icon_gem.png");
        icon1->setPosition(panelSize.width/2-50, panelSize.height/2+20);
        _panel->addChild(icon1);
        
        auto label1 = Label::createWithSystemFont(Value(_money).asString().c_str(), s_gameConfig.defaultFontName, s_gameConfig.defaultFontSize);
        label1->setPosition(panelSize.width/2+50,panelSize.height/2+20);
        label1->setColor(Color3B(255, 255, 0));
        _panel->addChild(label1);
        if (_starboom > 0) {
            auto icon2 = Sprite::createWithSpriteFrameName("bomb_1_1.png");
            icon2->setScale(0.5f);icon2->setRotation(90);
            icon2->setPosition(panelSize.width/2-50, panelSize.height/2-40);
            _panel->addChild(icon2);
            
            auto label2 = Label::createWithSystemFont(Value(_starboom).asString().c_str(), s_gameConfig.defaultFontName, s_gameConfig.defaultFontSize);
            label2->setPosition(panelSize.width/2+50,panelSize.height/2-40);
            label2->setColor(Color3B(255, 255, 0));
            _panel->addChild(label2);
        }
        else if (_laser > 0) {
            
            auto icon2 = Sprite::createWithSpriteFrameName("bomb_2_1.png");
            icon2->setScale(0.8f);icon2->setRotation(90);
            icon2->setPosition(panelSize.width/2-50, panelSize.height/2-40);
            _panel->addChild(icon2);
            
            auto label2 = Label::createWithSystemFont(Value(_laser).asString().c_str(), s_gameConfig.defaultFontName, s_gameConfig.defaultFontSize);
            label2->setPosition(panelSize.width/2+50,panelSize.height/2-40);
            label2->setColor(Color3B(255, 255, 0));
            _panel->addChild(label2);
        }
        else if (_blackhole > 0) {
            
            auto icon2 = Sprite::createWithSpriteFrameName("bomb_3_1.png");
            icon2->setScale(0.6f);
            icon2->setPosition(panelSize.width/2-50, panelSize.height/2-40);
            _panel->addChild(icon2);
            
            auto label2 = Label::createWithSystemFont(Value(_blackhole).asString().c_str(), s_gameConfig.defaultFontName, s_gameConfig.defaultFontSize);
            label2->setPosition(panelSize.width/2+50,panelSize.height/2-40);
            label2->setColor(Color3B(255, 255, 0));
            _panel->addChild(label2);
        }
    }
    
    auto btnok = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                                                         CC_CALLBACK_1(MedalRewardsLayer::menuCallbackClosed,this),
                                                         s_gameStrings.medalInfo->medalrewardok);
    btnok->setAnchorPoint(Point::ANCHOR_MIDDLE);
    btnok->setPosition(Point(panelSize.width/2,panelSize.height/2-150));
    auto menuok = Menu::create( btnok, nullptr);
    menuok->setPosition(Point::ZERO);
    _panel->addChild(menuok,3);
    return true;
}

void MedalRewardsLayer::menuCallbackClosed(Ref *sender)
{
    this->removeFromParent();
}

void MedalRewardsLayer::initRewards()
{
    
}
