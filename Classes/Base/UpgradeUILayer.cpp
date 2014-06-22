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
#include "NotificationLayer.h"
#include "NoGemLayer.h"
#include "MedalChecker.h"
#include "ConfigManager.h"

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
    
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
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
    
    switch (_basePanel) {
        case BasePanel::Toppanel:
            _needgem = s_stoneSpeed[s_playerConfig.stonespeedlevel].gemForUpgrade;
            break;
        case BasePanel::MiddlePanel:
            _needgem = s_stoneCapacity[s_playerConfig.stonecapacitylevel].gemForUpgrade;
            break;
        case BasePanel::FlightPanel:
            _needgem = s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].gemForUpgrade;
            break;
        case BasePanel::WeaponPanel:
            _needgem = s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]].gemForUpgrade;
            break;
        default:
            break;
    }
    
    auto gemforUpgradeText = TextSprite::create(Value(_needgem).asString(),GameConfig::defaultFontName,fontSize);
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
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
    int fontSize = 25;
    
    auto bk = Scale9Sprite::create("helpCellBG.png");
    auto bkSize = panelSize - Size(30,150);
    bk->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bk->setPosition(Point(panelSize.width/2,panelSize.height-70));
    bk->setContentSize(bkSize);
    _panel->addChild(bk);
    
    Point pos1(60,bkSize.height/2+40);
    Point pos2(260,bkSize.height/2+40);
    Point pos3(340,bkSize.height/2+40);
    Point pos4(400,bkSize.height/2+40);
    Point offset(0,-70);
    
    auto level_text = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize);
    level_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_text->setPosition(pos1);
    bk->addChild(level_text);
    
    auto level_before = TextSprite::create(Value(s_playerConfig.stonespeedlevel+1).asString(),GameConfig::defaultFontName,fontSize);
    level_before->setColor(Color3B::BLUE);
    level_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_before->setPosition(pos2);
    bk->addChild(level_before);
    
    auto level_after = TextSprite::create(Value(s_playerConfig.stonespeedlevel+2).asString(),GameConfig::defaultFontName,fontSize);
    level_after->setColor(Color3B::BLUE);
    level_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_after->setPosition(pos4);
    bk->addChild(level_after);
    
    auto speed_text = TextSprite::create(s_gameStrings.base->stonespeed,GameConfig::defaultFontName,fontSize);
    speed_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    speed_text->setPosition(pos1+offset);
    bk->addChild(speed_text);
    
    auto speed_before = TextSprite::create(Value(s_stoneSpeed[s_playerConfig.stonespeedlevel].speed).asString(),GameConfig::defaultFontName,fontSize);
    speed_before->setColor(Color3B::BLUE);
    speed_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    speed_before->setPosition(pos2+offset);
    bk->addChild(speed_before);
    
    auto speed_after = TextSprite::create(Value(s_stoneSpeed[s_playerConfig.stonespeedlevel+1].speed).asString(),GameConfig::defaultFontName,fontSize);
    speed_after->setColor(Color3B::BLUE);
    speed_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    speed_after->setPosition(pos4+offset);
    bk->addChild(speed_after);
}

void UpgradeUILayer::createStoneMaxUI()
{
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
    int fontSize = 25;
    
    auto bk = Scale9Sprite::create("helpCellBG.png");
    auto bkSize = panelSize - Size(30,150);
    bk->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bk->setPosition(Point(panelSize.width/2,panelSize.height-70));
    bk->setContentSize(bkSize);
    _panel->addChild(bk);
    
    Point pos1(60,bkSize.height/2+80);
    Point pos2(260,bkSize.height/2+80);
    Point pos3(360,bkSize.height/2+80);
    Point pos4(400,bkSize.height/2+80);
    Point offset(0,-70);
    
    auto level_text = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize);
    level_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_text->setPosition(pos1);
    bk->addChild(level_text);
    
    auto level_before = TextSprite::create(Value(s_playerConfig.stonecapacitylevel+1).asString(),GameConfig::defaultFontName,fontSize);
    level_before->setColor(Color3B::BLUE);
    level_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_before->setPosition(pos2);
    bk->addChild(level_before);
    
    auto level_after = TextSprite::create(Value(s_playerConfig.stonecapacitylevel+2).asString(),GameConfig::defaultFontName,fontSize);
    level_after->setColor(Color3B::BLUE);
    level_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_after->setPosition(pos4);
    bk->addChild(level_after);
    
    auto init_text = TextSprite::create(s_gameStrings.base->stoneinit,GameConfig::defaultFontName,fontSize);
    init_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    init_text->setPosition(pos1+offset);
    bk->addChild(init_text);
    
    auto init_before = TextSprite::create(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel].initstone).asString(),GameConfig::defaultFontName,fontSize);
    init_before->setColor(Color3B::BLUE);
    init_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    init_before->setPosition(pos2+offset);
    bk->addChild(init_before);
    
    auto init_after = TextSprite::create(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel+1].initstone).asString(),GameConfig::defaultFontName,fontSize);
    init_after->setColor(Color3B::BLUE);
    init_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    init_after->setPosition(pos4+offset);
    bk->addChild(init_after);
    
    auto max_text = TextSprite::create(s_gameStrings.base->stonemax,GameConfig::defaultFontName,fontSize);
    max_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    max_text->setPosition(pos1+offset*2);
    bk->addChild(max_text);
    
    auto max_before = TextSprite::create(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel].maxstone).asString(),GameConfig::defaultFontName,fontSize);
    max_before->setColor(Color3B::BLUE);
    max_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    max_before->setPosition(pos2+offset*2);
    bk->addChild(max_before);
    
    auto max_after = TextSprite::create(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel+1].maxstone).asString(),GameConfig::defaultFontName,fontSize);
    max_after->setColor(Color3B::BLUE);
    max_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    max_after->setPosition(pos4+offset*2);
    bk->addChild(max_after);

}

void UpgradeUILayer::createFlightUI()
{
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
    int fontSize = 25;
    
    auto bk = Scale9Sprite::create("helpCellBG.png");
    auto bkSize = panelSize - Size(30,150);
    bk->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bk->setPosition(Point(panelSize.width/2,panelSize.height-70));
    bk->setContentSize(bkSize);
    _panel->addChild(bk);
    
    Point pos1(80,bkSize.height/2+120);
    Point pos2(260,bkSize.height/2+120);
    Point pos3(360,bkSize.height/2+120);
    Point pos4(400,bkSize.height/2+120);
    Point offset(0,-40);
    
    auto level_text = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize);
    level_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_text->setPosition(pos1);
    bk->addChild(level_text);
    
    auto level_before = TextSprite::create(Value(s_playerConfig.fighterslevel[_index]+1).asString(),GameConfig::defaultFontName,fontSize);
    level_before->setColor(Color3B::BLUE);
    level_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_before->setPosition(pos2);
    bk->addChild(level_before);
    
    auto level_after = TextSprite::create(Value(s_playerConfig.fighterslevel[_index]+2).asString(),GameConfig::defaultFontName,fontSize);
    level_after->setColor(Color3B::BLUE);
    level_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_after->setPosition(pos4);
    bk->addChild(level_after);
    
    auto life_text = TextSprite::create(s_gameStrings.base->upgradeLife,GameConfig::defaultFontName,fontSize);
    life_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    life_text->setPosition(pos1+offset);
    bk->addChild(life_text);
    
    auto life_before = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].life).asString(),GameConfig::defaultFontName,fontSize);
    life_before->setColor(Color3B::BLUE);
    life_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    life_before->setPosition(pos2+offset);
    bk->addChild(life_before);
    
    auto life_after = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]+1].life).asString(),GameConfig::defaultFontName,fontSize);
    life_after->setColor(Color3B::BLUE);
    life_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    life_after->setPosition(pos4+offset);
    bk->addChild(life_after);
    
    auto attack_text = TextSprite::create(s_gameStrings.base->upgradeAtt,GameConfig::defaultFontName,fontSize);
    attack_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    attack_text->setPosition(pos1+offset*2);
    bk->addChild(attack_text);
    
    auto attack_before = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].attack).asString(),GameConfig::defaultFontName,fontSize);
    attack_before->setColor(Color3B::BLUE);
    attack_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    attack_before->setPosition(pos2+offset*2);
    bk->addChild(attack_before);
    
    auto attack_after = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]+1].attack).asString(),GameConfig::defaultFontName,fontSize);
    attack_after->setColor(Color3B::BLUE);
    attack_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    attack_after->setPosition(pos4+offset*2);
    bk->addChild(attack_after);
    
    auto defense_text = TextSprite::create(s_gameStrings.base->upgradeDef,GameConfig::defaultFontName,fontSize);
    defense_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    defense_text->setPosition(pos1+offset*3);
    bk->addChild(defense_text);
    
    auto defense_before = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].defense).asString(),GameConfig::defaultFontName,fontSize);
    defense_before->setColor(Color3B::BLUE);
    defense_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    defense_before->setPosition(pos2+offset*3);
    bk->addChild(defense_before);
    
    auto defense_after = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]+1].defense).asString(),GameConfig::defaultFontName,fontSize);
    defense_after->setColor(Color3B::BLUE);
    defense_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    defense_after->setPosition(pos4+offset*3);
    bk->addChild(defense_after);
    
    auto speed_text = TextSprite::create(s_gameStrings.base->upgradeSpd,GameConfig::defaultFontName,fontSize);
    speed_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    speed_text->setPosition(pos1+offset*4);
    bk->addChild(speed_text);
    
    auto speed_before = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].speed).asString(),GameConfig::defaultFontName,fontSize);
    speed_before->setColor(Color3B::BLUE);
    speed_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    speed_before->setPosition(pos2+offset*4);
    bk->addChild(speed_before);
    
    auto speed_after = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]+1].speed).asString(),GameConfig::defaultFontName,fontSize);
    speed_after->setColor(Color3B::BLUE);
    speed_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    speed_after->setPosition(pos4+offset*4);
    bk->addChild(speed_after);

    auto range_text = TextSprite::create(s_gameStrings.base->upgradeRange,GameConfig::defaultFontName,fontSize);
    range_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    range_text->setPosition(pos1+offset*5);
    bk->addChild(range_text);
    
    auto range_before = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].range).asString(),GameConfig::defaultFontName,fontSize);
    range_before->setColor(Color3B::BLUE);
    range_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    range_before->setPosition(pos2+offset*5);
    bk->addChild(range_before);
    
    auto range_after = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]+1].range).asString(),GameConfig::defaultFontName,fontSize);
    range_after->setColor(Color3B::BLUE);
    range_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    range_after->setPosition(pos4+offset*5);
    bk->addChild(range_after);
    
    auto usestone_text = TextSprite::create(s_gameStrings.base->useStone,GameConfig::defaultFontName,fontSize);
    usestone_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    usestone_text->setPosition(pos1+offset*6);
    bk->addChild(usestone_text);
    
    auto usestone_before = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].sparForMake).asString(),GameConfig::defaultFontName,fontSize);
    usestone_before->setColor(Color3B::BLUE);
    usestone_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    usestone_before->setPosition(pos2+offset*6);
    bk->addChild(usestone_before);
    
    auto usestone_after = TextSprite::create(Value(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]+1].sparForMake).asString(),GameConfig::defaultFontName,fontSize);
    usestone_after->setColor(Color3B::BLUE);
    usestone_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    usestone_after->setPosition(pos4+offset*6);
    bk->addChild(usestone_after);
}

void UpgradeUILayer::createWeaponUI()
{
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
    int fontSize = 25;
    
    auto bk = Scale9Sprite::create("helpCellBG.png");
    auto bkSize = panelSize - Size(30,150);
    bk->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bk->setPosition(Point(panelSize.width/2,panelSize.height-70));
    bk->setContentSize(bkSize);
    _panel->addChild(bk);
    
    Point pos1(60,bkSize.height/2+95);
    Point pos2(220,bkSize.height/2+95);
    Point pos3(360,bkSize.height/2+95);
    Point pos4(400,bkSize.height/2+95);
    Point offset(0,-50);
    
    auto level_text = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize);
    level_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_text->setPosition(pos1);
    bk->addChild(level_text);
    
    auto level_before = TextSprite::create(Value(s_playerConfig.weaponslevel[_index-FIGHTER_MAX]+1).asString(),GameConfig::defaultFontName,fontSize);
    level_before->setColor(Color3B::BLUE);
    level_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_before->setPosition(pos2);
    bk->addChild(level_before);
    
    auto level_after = TextSprite::create(Value(s_playerConfig.weaponslevel[_index-FIGHTER_MAX]+2).asString(),GameConfig::defaultFontName,fontSize);
    level_after->setColor(Color3B::BLUE);
    level_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    level_after->setPosition(pos4);
    bk->addChild(level_after);
    
    auto attack_text = TextSprite::create(s_gameStrings.base->upgradeAtt,GameConfig::defaultFontName,fontSize);
    attack_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    attack_text->setPosition(pos1+offset);
    bk->addChild(attack_text);
    
    auto attack_before = TextSprite::create(Value(s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]].attack).asString(),GameConfig::defaultFontName,fontSize);
    attack_before->setColor(Color3B::BLUE);
    attack_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    attack_before->setPosition(pos2+offset);
    bk->addChild(attack_before);
    
    auto attack_after = TextSprite::create(Value(s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]+1].attack).asString(),GameConfig::defaultFontName,fontSize);
    attack_after->setColor(Color3B::BLUE);
    attack_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    attack_after->setPosition(pos4+offset);
    bk->addChild(attack_after);
    
    auto duration_text = TextSprite::create(s_gameStrings.base->upgradeDuration,GameConfig::defaultFontName,fontSize);
    duration_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    duration_text->setPosition(pos1+offset*2);
    bk->addChild(duration_text);
    
    char p[30];
    float duration_before_data = s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]].duration;
    sprintf(p, "%.2f",duration_before_data);
    auto duration_before = TextSprite::create(p,GameConfig::defaultFontName,fontSize);
    duration_before->setColor(Color3B::BLUE);
    duration_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    duration_before->setPosition(pos2+offset*2);
    bk->addChild(duration_before);
    
    float duration_after_data = s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]+1].duration;
    sprintf(p, "%.2f",duration_after_data);
    auto duration_after = TextSprite::create(p,GameConfig::defaultFontName,fontSize);
    duration_after->setColor(Color3B::BLUE);
    duration_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    duration_after->setPosition(pos4+offset*2);
    bk->addChild(duration_after);
    
    auto buyusegem_text = TextSprite::create(s_gameStrings.base->buyusegem,GameConfig::defaultFontName,fontSize);
    buyusegem_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    buyusegem_text->setPosition(pos1+offset*3);
    bk->addChild(buyusegem_text);
    
    auto buyusegem_before = TextSprite::create(Value(s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]].costGem).asString(),GameConfig::defaultFontName,fontSize);
    buyusegem_before->setColor(Color3B::BLUE);
    buyusegem_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    buyusegem_before->setPosition(pos2+offset*3);
    bk->addChild(buyusegem_before);
    
    auto buyusegem_after = TextSprite::create(Value(s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]+1].costGem).asString(),GameConfig::defaultFontName,fontSize);
    buyusegem_after->setColor(Color3B::BLUE);
    buyusegem_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    buyusegem_after->setPosition(pos4+offset*3);
    bk->addChild(buyusegem_after);
    
    auto buymax_text = TextSprite::create(s_gameStrings.base->buymax,GameConfig::defaultFontName,fontSize);
    buymax_text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    buymax_text->setPosition(pos1+offset*4);
    bk->addChild(buymax_text);
    
    auto buymax_before = TextSprite::create(Value(s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]].capacity).asString(),GameConfig::defaultFontName,fontSize);
    buymax_before->setColor(Color3B::BLUE);
    buymax_before->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    buymax_before->setPosition(pos2+offset*4);
    bk->addChild(buymax_before);
    
    auto buymax_after = TextSprite::create(Value(s_weaponConfigs[_index-FIGHTER_MAX][s_playerConfig.weaponslevel[_index-FIGHTER_MAX]+1].capacity).asString(),GameConfig::defaultFontName,fontSize);
    buymax_after->setColor(Color3B::BLUE);
    buymax_after->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    buymax_after->setPosition(pos4+offset*4);
    bk->addChild(buymax_after);

}

void UpgradeUILayer::menuCallbackUpgrade(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    //判断并发送通知
    if (_needgem<=s_playerConfig.gem) {
        s_playerConfig.gem = s_playerConfig.gem - _needgem;
        
        switch (_basePanel) {
            case BasePanel::Toppanel :
                s_playerConfig.stonespeedlevel++;
                break;
            case BasePanel::MiddlePanel :
                s_playerConfig.stonecapacitylevel++;
                break;
            case BasePanel::FlightPanel :
                s_playerConfig.fighterslevel[_index]++;
                _eventDispatcher->dispatchCustomEvent(GameConfig::eventUpdateMenuItemFlightData,(void*)_index);
                break;
            case BasePanel::WeaponPanel :
                s_playerConfig.weaponslevel[_index-FIGHTER_MAX]++;
                _eventDispatcher->dispatchCustomEvent(GameConfig::eventUpdateMenuItemWeaponData,(void*)(_index-FIGHTER_MAX));
                break;
            default:
                break;
        }
        
        MedalChecker::getInstance()->check();
        ConfigManager::getInstance()->saveConfig();
        _eventDispatcher->dispatchCustomEvent(GameConfig::eventUpdateBaseData,(void*)_needgem);
        _eventDispatcher->dispatchCustomEvent(GameConfig::eventShowHideMedalLogo);
        this->removeFromParent();
    }
    else
    {
        if(s_playerConfig.overstage < STAGEOFCANBUYGEM)
        {
            getParent()->addChild(NotificationLayer::create(s_gameStrings.base->nogemcannotbuy),100);
            this->removeFromParent();
        }
        else
        {
            getParent()->addChild(NoGemLayer::create(),100);
            this->removeFromParent();
        }
    }
}

void UpgradeUILayer::menuCallbackClosed(cocos2d::Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    this->removeFromParent();
}
