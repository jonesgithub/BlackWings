//
//  NoGemLayer.cpp
//  BlackWings
//
//  Created by Jacky on 14-6-8.
//
//

#include "NoGemLayer.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "NotificationLayer.h"

USING_NS_CC_EXT;

bool NoGemLayer::init()
{
    if (LayerColor::initWithColor(Color4B(0,0,0,0)))
    {
        this->runAction(FadeTo::create(0.5f,100));
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        auto panelSize = Size(s_visibleRect.visibleWidth - 97,500);
        
        auto panel = Scale9Sprite::create("windowBox.png");
        panel->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        panel->setPosition(s_visibleRect.center.x,s_visibleRect.center.y - 100);
        panel->setContentSize(panelSize);
        this->addChild(panel);
        
        auto itemClosed = MenuItemImageLabel::createWithFrameName("close_0.png","close_1.png",
                                                                  CC_CALLBACK_1(NoGemLayer::menuCallbackClosed,this));
        itemClosed->setPosition(panelSize.width,panelSize.height);
        
        auto itemConfirm = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                                                                   CC_CALLBACK_1(NoGemLayer::menuCallbackConfirm,this),s_gameStrings.mainMenu->settingResetConfirm);
        itemConfirm->setPosition(panelSize.width / 2, 180);
        
        auto itemCancel = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                                                                  CC_CALLBACK_1(NoGemLayer::menuCallbackClosed,this),s_gameStrings.mainMenu->settingResetCancel);
        itemCancel->setPosition(panelSize.width / 2, 80);
        
        auto menu = Menu::create( itemClosed, itemConfirm, itemCancel, nullptr);
        menu->setPosition(Point::ZERO);
        panel->addChild(menu);
        
        auto tipContent = TextSprite::create(s_gameStrings.base->nogemcanbuy,GameConfig::defaultFontName,GameConfig::defaultFontSize,
                                             Size(panelSize.width * 0.8f,panelSize.height * 0.3f));
        tipContent->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        tipContent->setPosition(panelSize.width * 0.1f,panelSize.height * 0.85f);
        tipContent->setColor(Color3B::YELLOW);
        panel->addChild(tipContent);
        
        return true;
    }
    
    return false;
}

void NoGemLayer::menuCallbackClosed(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    this->removeFromParentAndCleanup(true);
}

void NoGemLayer::menuCallbackConfirm(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    this->getParent()->removeFromParentAndCleanup(true);
    
    //enter buy gem ui.
}