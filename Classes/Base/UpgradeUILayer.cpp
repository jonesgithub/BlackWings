//
//  UpgradeUILayer.cpp
//  BlackWings
//
//  Created by Jacky on 14-6-7.
//
//

#include "UpgradeUILayer.h"
#include "VisibleRect.h"
#include "extensions/cocos-ext.h"
#include "MenuItemImageLabel.h"
#include "TextSprite.h"
#include "GameStrings.h"
#include "Configuration.h"

USING_NS_CC;
USING_NS_CC_EXT;

UpgradeUILayer* UpgradeUILayer::create(BasePanel basePanel, int index)
{
    auto pRet = new UpgradeUILayer();
    if (pRet && pRet->init(basePanel, index))
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

bool UpgradeUILayer::init(BasePanel basePanel, int index)
{
    if(!Layer::init())
        return false;
    
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    panelSize = Size(s_visibleRect.visibleWidth-100,s_visibleRect.visibleHeight-500);
    
    _panel = Scale9Sprite::create("windowBox.png");
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
                                                              CC_CALLBACK_1(UpgradeUILayer::menuCallbackClosed,this));
    itemClosed->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    itemClosed->setPosition((s_visibleRect.visibleWidth + panelSize.width)/2-5,panelSize.height+35);
    
    auto menu = Menu::create( itemClosed, nullptr);
    menu->setPosition(Point::ZERO);
    _panel->addChild(menu,3);
    
    _basePanel = basePanel;
    _index = index;
    
    //title
    std::string title_text;
    switch (_basePanel) {
        case BasePanel::Toppanel:
            title_text = s_gameStrings.base->sparRecoverRate;
            break;
        case BasePanel::MiddlePanel:
            title_text = s_gameStrings.base->sparCapacity;
            break;
        case BasePanel::FlightPanel:
            title_text = s_gameStrings.base->flightname[_index];
            break;
        case BasePanel::WeaponPanel:
            title_text = s_gameStrings.base->weaponname[_index-FIGHTER_MAX];
            break;
        default:
            break;
    }
    
    auto tittle = TextSprite::create(title_text,GameConfig::defaultFontName,30,
                                   Size(500,30),TextHAlignment::CENTER,TextVAlignment::CENTER);
    tittle->setColor(Color3B(255, 255, 0));
    tittle->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tittle->setPosition(Point(panelSize.width/2,panelSize.height-40));
    _panel->addChild(tittle);

    //upgrade button
    auto menuitem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",CC_CALLBACK_1(UpgradeUILayer::menuCallbackUpgrade,this));
    menuitem->setScale(1.2f,0.5f);
    menuitem->setPosition(Point(panelSize.width / 2,40));
    auto menuupgrade = Menu::create(menuitem,nullptr);
    menuupgrade->setPosition(Point::ZERO);
    _panel->addChild(menuupgrade);

    auto spar = Sprite::createWithSpriteFrameName("icon_gem.png");
    spar->setPosition(Point(panelSize.width/2-80,40));
    _panel->addChild(spar);

    auto upgradeText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize);
    upgradeText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    upgradeText->setPosition(panelSize.width/2+60,40);
    _panel->addChild(upgradeText);
    
    std::string gemforupgrade_text;
    switch (_basePanel) {
        case BasePanel::Toppanel:
            gemforupgrade_text = Value(s_stoneSpeed[s_playerConfig.stonespeedlevel].gemForUpgrade).asString();
            break;
        case BasePanel::MiddlePanel:
            gemforupgrade_text = Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel].gemForUpgrade).asString();
            break;
        case BasePanel::FlightPanel:
            gemforupgrade_text = Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].gemForUpgrade).asString();
            break;
        case BasePanel::WeaponPanel:
            gemforupgrade_text = Value(s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]].gemForUpgrade).asString();
            break;
        default:
            break;
    }
    
    auto gemforUpgradeText = TextSprite::create(gemforupgrade_text,GameConfig::defaultFontName,fontSize);
    gemforUpgradeText->setColor(Color3B::YELLOW);
    gemforUpgradeText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    gemforUpgradeText->setPosition(panelSize.width/2-60,40);
    _panel->addChild(gemforUpgradeText);
    
    //content
    
    switch (basePanel) {
        case BasePanel::Toppanel:
            createStoneSpeedUI();
            break;
        case BasePanel::MiddlePanel:
            createStoneMaxUI();
            break;
        case BasePanel::FlightPanel:
            createFlightUI();
            break;
        case BasePanel::WeaponPanel:
            createWeaponUI();
            break;
        default:
            break;
    }
    
    return true;
}

void UpgradeUILayer::createStoneSpeedUI()
{
    auto bk = Scale9Sprite::create("helpCellBG.png");
    bk->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bk->setPosition(Point(panelSize.width/2,panelSize.height-70));
    bk->setContentSize(panelSize - Size(30,150));
    _panel->addChild(bk);
    
    
}

void UpgradeUILayer::createStoneMaxUI()
{
    
}

void UpgradeUILayer::createFlightUI()
{
    
}

void UpgradeUILayer::createWeaponUI()
{
    
}

void UpgradeUILayer::menuCallbackUpgrade(Ref *sender)
{
    //判断并发送通知
    this->removeFromParent();
}

void UpgradeUILayer::menuCallbackClosed(cocos2d::Ref *sender)
{
    this->removeFromParent();
}
