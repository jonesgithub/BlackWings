//
//  PromtWindow.cpp
//  BlackWings
//
//  Created by Jacky on 14-6-21.
//
//

#include "PromtWindow.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "NotificationLayer.h"
#include "ConfigManager.h"
#include "Battleground.h"
#include "Base.h"
#include "MainMenu.h"

extern Battleground* s_battleground;

USING_NS_CC_EXT;

PromtWindow* PromtWindow::create(ForWhat forwhat)
{
    auto ret = new PromtWindow;
    if (ret && ret->init(forwhat))
    {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}

bool PromtWindow::init(ForWhat forwhat)
{
    if (LayerColor::initWithColor(Color4B(0,0,0,0)))
    {
        
        _forWhat = forwhat;
        
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
        panel->setPosition(s_visibleRect.center.x,s_visibleRect.center.y - 220);
        panel->setContentSize(panelSize);
        this->addChild(panel);
        
        auto itemClosed = MenuItemImageLabel::createWithFrameName("close_0.png","close_1.png",
                                                                  CC_CALLBACK_1(PromtWindow::menuCallbackClosed,this));
        itemClosed->setPosition(panelSize.width,panelSize.height);
        
        auto itemConfirm = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                                                                   CC_CALLBACK_1(PromtWindow::menuCallbackConfirm,this),s_gameStrings.mainMenu->settingResetConfirm);
        itemConfirm->setPosition(panelSize.width / 2, 180);
        
        auto itemCancel = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                                                                  CC_CALLBACK_1(PromtWindow::menuCallbackClosed,this),s_gameStrings.mainMenu->settingResetCancel);
        itemCancel->setPosition(panelSize.width / 2, 80);
        
        auto menu = Menu::create( itemClosed, itemConfirm, itemCancel, nullptr);
        menu->setPosition(Point::ZERO);
        panel->addChild(menu);
        
        if(forwhat == ForWhat::Restart)
        {
            auto tipTitle = TextSprite::create(s_gameStrings.battleInfo->tips);
            tipTitle->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            tipTitle->setPosition(panelSize.width * 0.1f,panelSize.height * 0.80f);
            tipTitle->setColor(Color3B::YELLOW);
            panel->addChild(tipTitle);
        }
        
        std::string contentText;
        switch (forwhat) {
            case ForWhat::Restart:
                contentText = s_gameStrings.battleInfo->comfirmrestartgame;
                break;
            case ForWhat::BackToBase:
                contentText = s_gameStrings.battleInfo->comfirmreturntobase;
                break;
            case ForWhat::BACKToMainMenu:
                contentText = s_gameStrings.battleInfo->comfirmreturntomainmenu;
                break;
            default:
                break;
        }
        auto tipContent = TextSprite::create(contentText,GameConfig::defaultFontName,GameConfig::defaultFontSize,
                                             Size(panelSize.width * 0.8f,panelSize.height * 0.25f));
        tipContent->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        tipContent->setPosition(panelSize.width * 0.1f,panelSize.height * 0.80f);
        if(forwhat == ForWhat::Restart)
            tipContent->setColor(Color3B::YELLOW);
        panel->addChild(tipContent);
        
        Director::getInstance()->resume();
        panel->setScale(0.1f);
        panel->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                          ScaleTo::create(0.05f, 0.9f),
                                          ScaleTo::create(0.05f, 1.0f),
                                          CallFunc::create([](){Director::getInstance()->pause();}),
                                          nullptr));
        
        return true;
    }
    
    return false;
}

void PromtWindow::menuCallbackClosed(Ref *sender)
{
    this->removeFromParentAndCleanup(true);
}

void PromtWindow::menuCallbackConfirm(Ref *sender)
{
    this->getParent()->removeFromParentAndCleanup(true);
    
    switch (_forWhat) {
        case ForWhat::Restart:
        {
            if (Director::getInstance()->isPaused()) {
                Director::getInstance()->resume();
            }
            ConfigManager::getInstance()->saveConfig();
            auto bettle = Battleground::create(s_battleground->_battledata.stage);
            Director::getInstance()->replaceScene(bettle);
        }
            break;
        case ForWhat::BackToBase:
        {
            if (Director::getInstance()->isPaused()) {
                Director::getInstance()->resume();
            }
            ConfigManager::getInstance()->saveConfig();
            auto base = Base::create();
            Director::getInstance()->replaceScene(base);
        }
            break;
        case ForWhat::BACKToMainMenu:
        {
            if (Director::getInstance()->isPaused()) {
                Director::getInstance()->resume();
            }
            ConfigManager::getInstance()->saveConfig();
            auto mainMenu = MainMenu::create();
            Director::getInstance()->replaceScene(mainMenu);
        }
            break;
        default:
            break;
    }
}