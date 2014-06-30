#include "Base.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "LoadResourceLayer.h"
#include "MenuSettings.h"
#include "PlayerBar.h"
#include "StageSelect.h"
#include "Medal.h"
#include "PlayerMenuItem.h"
#include "UpgradeUILayer.h"
#include "NotificationLayer.h"
#include "NoGemLayer.h"
#include "MedalChecker.h"
#include "ConfigManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool Base::init()
{
    if (Scene::init())
    {
        auto loadLayer = LoadResourceLayer::create(CC_CALLBACK_1(Base::createBase, this));
        loadLayer->addPlist("playerBag.plist","playerBag.png");
        loadLayer->addPlist("upgrade.plist","upgrade.png");
        loadLayer->addPlist("home.plist","home.png");
        loadLayer->addPlist("medal_icons.plist","medal_icons.png");
        loadLayer->addPlist("medal_icons_0.plist","medal_icons_0.png");
        loadLayer->addPlist("bombs.plist", "bombs.png");
        loadLayer->addImage("door_l.png");
        loadLayer->addImage("door_r.png");
        this->addChild(loadLayer);
        loadLayer->startLoad();
        
        s_gameConfig.isInBattle = false;
        _isInFilghtUpgradeUI = true;

        return true;
    }

    return false;
}

void Base::createBase(Ref *sender)
{
    PLAY_BASE_MUSIC;
    auto bg = Sprite::create("mainBackground.png");
    bg->setPosition(s_visibleRect.center);
    addChild(bg);
    
    //************ adds emission flare ****************
    auto flare = ParticleSystemQuad::create("homeFire.plist");
    flare->setPosition(s_visibleRect.center + Point(0,355));
    flare->setScaleX(2.0f);
    this->addChild(flare,1);
    
    //************ adds vanishing ****************
    auto vanishing = ParticleSystemQuad::create("vanishingPoint.plist");
    vanishing->setPosition(s_visibleRect.center);
    this->addChild(vanishing);
    
    this->removeChild((LoadResourceLayer*)sender,true);

    GSBaseInit((GameLanguage)s_playerConfig.language);

    createUpgrade(true, 0);

    createBottomPanel();
    
    createTopPanel();

    
    //enter,default 1st flight
    {
        PLAY_TOUCH_ITEM_EFFECT;
        auto player = (PlayerMenuItem*)_playerBag->_playerMenu->getChildByTag(1000);
        player->selected();
        
        char name[30];
        sprintf(name,"plain_%d_lv_%d.png",1,s_playerConfig.fighterslevel[0]+1);
        
        auto flightNode = Node::create();
        _bottomPanel->addChild(flightNode);
        flightNode->setPosition(player->getPosition()+Point(0,50));
        
        auto flight = Sprite::createWithSpriteFrameName(name);
        flightNode->addChild(flight,1,1);
        auto flightpar = ParticleSystemQuad::create("plain_effect_1.plist");
        flightpar->setStartColor(getPlainParticleEffectColor(0));
        flightpar->setAnchorPoint(Point::ANCHOR_MIDDLE);
        flightpar->setScale(0.5f);
        flightpar->setPosition(Point::ZERO - Point(0,20));
        flightNode->addChild(flightpar);
        
        _curSelectedFlight = flightNode;
        _curSeletedIndex = 0;
        
        auto move = MoveTo::create(0.5f, Point(128,360));
        flightNode->runAction(move);
    }

}

void Base::onEnter()
{
    Scene::onEnter();
    
    auto listenerStageSelect = EventListenerCustom::create(StageSelect::eventBack, [=](EventCustom* event){
        _topPanel->runAction(MoveBy::create(0.2f,Point(0,-200)));
        _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,s_visibleRect.visibleHeight)));
        _bottomPanel->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,136)),nullptr ));
        _curSelectedFlight->setVisible(true);
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStageSelect, this);
    
    auto listenerMedal = EventListenerCustom::create(Medal::eventBack, [=](EventCustom* event){
        _topPanel->runAction(MoveBy::create(0.2f,Point(0,-200)));
        _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,s_visibleRect.visibleHeight)));
        _bottomPanel->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,136)),nullptr ));
        _curSelectedFlight->setVisible(true);
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMedal, this);

    auto listener = EventListenerCustom::create(PlayerBar::eventPlayerSelect, [=](EventCustom* event)
                                                {
                                                    int index = (uintptr_t)event->getUserData();
                                                    for (int i = 0; i<FIGHTER_MAX; i++)
                                                    {
                                                        if(index == i && _curSeletedIndex!=i)
                                                        {
                                                            PLAY_TOUCH_ITEM_EFFECT;
                                                            _curSelectedFlight->runAction(Sequence::create(FadeOut::create(0.3f),
                                                                                                           RemoveSelf::create(),
                                                                                                           nullptr));
                                                            char name[30];
                                                            sprintf(name,"plain_%d_lv_%d.png",index+1,s_playerConfig.fighterslevel[index]+1);
                                                            
                                                            auto flightNode = Node::create();
                                                            _bottomPanel->addChild(flightNode);
                                                            flightNode->setPosition(_playerBag->_playerMenu->getChildByTag(1000+i)->getPosition()+Point(0,50));
                                                            
                                                            auto flight = Sprite::createWithSpriteFrameName(name);
                                                            flightNode->addChild(flight,1,1);
                                                            auto flightpar = ParticleSystemQuad::create("plain_effect_1.plist");
                                                            flightpar->setAnchorPoint(Point::ANCHOR_MIDDLE);
                                                            flightpar->setScale(0.5f);
                                                            flightpar->setPosition(Point::ZERO - Point(0,20));
                                                            flightpar->setStartColor(getPlainParticleEffectColor(i));
                                                            flightNode->addChild(flightpar);
                                                            
                                                            _curSelectedFlight = flightNode;
                                                            _curSeletedIndex = i;
                                                            
                                                            auto move = MoveTo::create(0.5f, Point(128,370));
                                                            flightNode->runAction(move);
                                                        }
                                                        
                                                    }
                                                    for (int i=FIGHTER_MAX; i<FIGHTER_MAX + WEAPON_MAX; ++i) {
                                                        if(index == i && _curSeletedIndex!=i)
                                                        {
                                                            PLAY_TOUCH_ITEM_EFFECT;
                                                            _curSelectedFlight->runAction(Sequence::create(FadeOut::create(0.3f),
                                                                                                           RemoveSelf::create(),
                                                                                                           nullptr));
                                                            char name[30];
                                                            sprintf(name,"bomb_%d_%d.png",index-FIGHTER_MAX+1,s_playerConfig.weaponslevel[index-FIGHTER_MAX]+1);
                                                            
                                                            auto flightNode = Node::create();
                                                            _bottomPanel->addChild(flightNode);
                                                            flightNode->setPosition(_playerBag->_playerMenu->getChildByTag(1000+i)->getPosition()-Point(s_visibleRect.visibleWidth, 0)+Point(0,50));
                                                            
                                                            auto flight = Sprite::createWithSpriteFrameName(name);
                                                            flightNode->addChild(flight,1,1);
                                                            
                                                            _curSelectedFlight = flightNode;
                                                            _curSeletedIndex = i;
                                                            
                                                            auto move = MoveTo::create(0.5f, Point(128,370));
                                                            flightNode->runAction(move);
                                                        }
                                                        
                                                    }
                                                    
                                                    if (index<6) {
                                                            upgradeFighter->removeAllChildren();
                                                            int baseHeight = 50;
                                                            auto boxPos = Point(s_visibleRect.center.x,s_visibleRect.center.y - baseHeight * 5.5-10);
                                                            
                                                            upgradeFighter = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
                                                            upgradeFighter->setContentSize(Size(s_visibleRect.visibleWidth - 60,baseHeight * 5.4));
                                                            upgradeFighter->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
                                                            upgradeFighter->setPosition(boxPos);
                                                            _upgradePanel->addChild(upgradeFighter,10);
                                                            createFighterBottomInfo(upgradeFighter, index);
//                                                        }
                                                    }
                                                    else
                                                    {

                                                            upgradeFighter->removeAllChildren();
                                                            int baseHeight = 50;
                                                            auto boxPos = Point(s_visibleRect.center.x,s_visibleRect.center.y - baseHeight * 5.5-10);
                                                            
                                                            upgradeFighter = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
                                                            upgradeFighter->setContentSize(Size(s_visibleRect.visibleWidth - 60,baseHeight * 5.4));
                                                            upgradeFighter->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
                                                            upgradeFighter->setPosition(boxPos);
                                                            _upgradePanel->addChild(upgradeFighter,10);
                                                            createWeaponBottomInfo(upgradeFighter, index - FIGHTER_MAX);
                                                    }
                                                    
                                                });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto listenerUpdateBaseData = EventListenerCustom::create(GameConfig::eventUpdateBaseData, [=](EventCustom* event){

        if (_isInFilghtUpgradeUI) {
            _upgradePanel->removeAllChildren();
            createUpgrade(true,_curSeletedIndex);
            
            char iconFileName[25];
            sprintf(iconFileName,"plain_%d_lv_%d.png",_curSeletedIndex + 1,s_playerConfig.fighterslevel[_curSeletedIndex] + 1);
            ((Sprite*)(_curSelectedFlight->getChildByTag(1)))->setSpriteFrame(iconFileName);
        }
        else
        {
            _upgradePanel->removeAllChildren();
            createUpgrade(false,_curSeletedIndex - FIGHTER_MAX);
            
            char iconFileName[25];
            sprintf(iconFileName,"bomb_%d_%d.png",_curSeletedIndex - FIGHTER_MAX + 1,s_playerConfig.weaponslevel[_curSeletedIndex - FIGHTER_MAX] + 1);
            ((Sprite*)(_curSelectedFlight->getChildByTag(1)))->setSpriteFrame(iconFileName);
        }
        
        if(_playerBag)
        {
            _playerBag->setGem(s_playerConfig.gem);
            _playerBag->setStone(s_stoneCapacity[s_playerConfig.stonecapacitylevel].initstone);
            _playerBag->setStoneMax(s_stoneCapacity[s_playerConfig.stonecapacitylevel].maxstone);
        }
        
        int cost = (uintptr_t)event->getUserData();
        showGemTip(cost,true);
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerUpdateBaseData, this);
    
    auto listenerShowHideMedalLogo = EventListenerCustom::create(GameConfig::eventShowHideMedalLogo, CC_CALLBACK_1(Base::showOrHideMedalLogo,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerShowHideMedalLogo, this);
    
    auto languagelistener = EventListenerCustom::create(GameConfig::eventLanguageChange, [=](EventCustom* event)
                                                {
                                                    if(_isInFilghtUpgradeUI)
                                                    {
                                                        fighter_levelText->setText(s_gameStrings.base->upgradeLevel);
                                                        fighter_attText->setText(s_gameStrings.base->upgradeAtt);
                                                        fighter_defText->setText(s_gameStrings.base->upgradeDef);
                                                        fighter_lifeText->setText(s_gameStrings.base->upgradeLife);
                                                        fighter_spdText->setText(s_gameStrings.base->upgradeSpd);
                                                        fighter_rangeText->setText(s_gameStrings.base->upgradeRange);
                                                        if (!fighter_maxlevel)
                                                        {
                                                            fighter_leveUpText->setText(s_gameStrings.base->upgrade);
                                                        }
                                                        else
                                                        {
                                                            fighter_maxlevel_text->setText(s_gameStrings.base->maxlevel);
                                                        }
                                                    }
                                                    else
                                                    {
                                                        weapon_levelText->setText(s_gameStrings.base->upgradeLevel);
                                                        weapon_attText->setText(s_gameStrings.base->upgradeAtt);
                                                        weapon_durationText->setText(s_gameStrings.base->upgradeDuration);
                                                        if (!weapon_maxlevel)
                                                        {
                                                            weapon_leveUpText->setText(s_gameStrings.base->upgrade);
                                                        }
                                                        else
                                                        {
                                                            weapon_maxlevel_text->setText(s_gameStrings.base->maxlevel);
                                                        }
                                                        weapon_buy_text->setText(s_gameStrings.base->upgradeBuy);
                                                    }
                                                });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(languagelistener, this);
}
void Base::onExit()
{
    _eventDispatcher->removeCustomEventListeners(PlayerBar::eventPlayerSelect);
    _eventDispatcher->removeCustomEventListeners(StageSelect::eventBack);
    _eventDispatcher->removeCustomEventListeners(Medal::eventBack);
    _eventDispatcher->removeCustomEventListeners(GameConfig::eventUpdateBaseData);
    _eventDispatcher->removeCustomEventListeners(GameConfig::eventShowHideMedalLogo);

    Scene::onExit();
}
void Base::createBottomPanel()
{
    _bottomPanel =  Node::create();
    this->addChild(_bottomPanel,2);
    _playerBag = PlayerBar::create();
    _bottomPanel->addChild(_playerBag,3);
}

void Base::createUpgrade(bool isFightUI, int t_index)
{
    _upgradePanel = Node::create();
    this->addChild(_upgradePanel,1);

    int baseHeight = 50;
    int padding = 15;

    auto boxPos = Point(s_visibleRect.center.x,s_visibleRect.center.y - baseHeight * 5.5-10);

    if (isFightUI) {
        
        upgradeFighter = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
        upgradeFighter->setContentSize(Size(s_visibleRect.visibleWidth - 60,baseHeight * 5.4));
        upgradeFighter->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        upgradeFighter->setPosition(boxPos);
        _upgradePanel->addChild(upgradeFighter);
        createFighterBottomInfo(upgradeFighter, t_index);
    }
    else
    {
        upgradeFighter = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
        upgradeFighter->setContentSize(Size(s_visibleRect.visibleWidth - 60,baseHeight * 5.4));
        upgradeFighter->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        upgradeFighter->setPosition(boxPos);
        _upgradePanel->addChild(upgradeFighter);
        createWeaponBottomInfo(upgradeFighter, t_index);
    }

    boxPos.y += baseHeight * 4.5 + padding + 24;
    auto sparCapacitySize = Size(s_visibleRect.visibleWidth - 80,baseHeight * 3.7);
    upgradeSparCapacity = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
    upgradeSparCapacity->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    upgradeSparCapacity->setContentSize(sparCapacitySize);
    upgradeSparCapacity->setPosition(boxPos);
    _upgradePanel->addChild(upgradeSparCapacity);
    auto bg1 = Scale9Sprite::createWithSpriteFrameName("upgrade_box_bg.png");
    bg1->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bg1->setContentSize(Size(sparCapacitySize.width * 5 /7,baseHeight-15));
    bg1->setPosition(Point(sparCapacitySize.width /2,sparCapacitySize.height - 10));
    upgradeSparCapacity->addChild(bg1);
    createFighterMiddleInfo(upgradeSparCapacity);
    
    boxPos.y += baseHeight * 3 + padding +13;
    auto sparRecoverySize = Size(s_visibleRect.visibleWidth - 100,baseHeight * 3.7);
    upgradeSparRecovery = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
    upgradeSparRecovery->setContentSize(sparRecoverySize);
    upgradeSparRecovery->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    upgradeSparRecovery->setPosition(boxPos);
    _upgradePanel->addChild(upgradeSparRecovery);
    auto bg2 = Scale9Sprite::createWithSpriteFrameName("upgrade_box_bg.png");
    bg2->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bg2->setContentSize(Size(sparRecoverySize.width * 5 /7,baseHeight-15));
    bg2->setPosition(Point(sparRecoverySize.width /2,sparRecoverySize.height - 10));
    upgradeSparRecovery->addChild(bg2);
    createFighterTopInfo(upgradeSparRecovery);
}

void Base::createFighterBottomInfo(Node* panel,int t_index)
{
    _isInFilghtUpgradeUI = true;
    auto panelSize = panel->getContentSize();
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
    int fontSize_m = 23;
    int fontSize_l = 25;
    auto infoColor = DIY_COLOR_BLUE3;
    
    auto fighterBox = Sprite::createWithSpriteFrameName("upgrade_box_mini.png");
    //fighterBox->setContentSize(Size(panelSize.width / 6,panelSize.height * 0.5f));
    //fighterBox->setScale(0.7f);
    fighterBox->setPosition(Point(panelSize.width / 6,panelSize.height * 0.625f));
    panel->addChild(fighterBox);
    fighterBox->setTag(0);
    

    auto menuitem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",CC_CALLBACK_1(Base::upgradeFlight,this));
    menuitem->setScale(1.2f,0.7f);
    menuitem->setPosition(Point(panelSize.width / 2,panelSize.height * 0.20f));
    auto menu = Menu::create(menuitem,nullptr);
    menu->setPosition(Point::ZERO);
    panel->addChild(menu);
    
    Sprite* spar;
    
    auto pos = Point(200,panelSize.height * 0.85f);

    {
        fighter_levelText = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize_m);
        fighter_levelText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        fighter_levelText->setPosition(pos);
        panel->addChild(fighter_levelText);

        pos.y = panelSize.height * 0.67f;
        fighter_attText = TextSprite::create(s_gameStrings.base->upgradeAtt,GameConfig::defaultFontName,fontSize_m);
        fighter_attText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        fighter_attText->setPosition(pos);
        panel->addChild(fighter_attText);
        fighter_attText->setTag(3);

        pos.y = panelSize.height * 0.5f;
        fighter_defText = TextSprite::create(s_gameStrings.base->upgradeDef,GameConfig::defaultFontName,fontSize_m);
        fighter_defText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        fighter_defText->setPosition(pos);
        panel->addChild(fighter_defText);
        fighter_defText->setTag(4);

        pos.x = 380;
        pos.y = panelSize.height * 0.85f;
        fighter_lifeText = TextSprite::create(s_gameStrings.base->upgradeLife,GameConfig::defaultFontName,fontSize_m);
        fighter_lifeText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        fighter_lifeText->setPosition(pos);
        panel->addChild(fighter_lifeText);
        fighter_lifeText->setTag(5);

        pos.y = panelSize.height * 0.67f;
        fighter_spdText = TextSprite::create(s_gameStrings.base->upgradeSpd,GameConfig::defaultFontName,fontSize_m);
        fighter_spdText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        fighter_spdText->setPosition(pos);
        panel->addChild(fighter_spdText);
        fighter_spdText->setTag(6);

        pos.y = panelSize.height * 0.5f;
        fighter_rangeText = TextSprite::create(s_gameStrings.base->upgradeRange,GameConfig::defaultFontName,fontSize_m);
        fighter_rangeText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        fighter_rangeText->setPosition(pos);
        panel->addChild(fighter_rangeText);
        fighter_rangeText->setTag(7);
        
        fighter_maxlevel = false;
        if (s_playerConfig.fighterslevel[t_index] < FIGHTER_LEVEL_MAX-1)
        {
            spar = Sprite::createWithSpriteFrameName("icon_gem.png");
            spar->setPosition(Point(180,panelSize.height * 0.20f));
            panel->addChild(spar);
            spar->setTag(2);
            
            pos.y = panelSize.height * 0.20f;
            fighter_leveUpText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize_l);
            fighter_leveUpText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            fighter_leveUpText->setPosition(pos-Point(65,0));
            panel->addChild(fighter_leveUpText);
            fighter_leveUpText->setTag(8);
        }
        else
        {
            pos.x = panelSize.width/2;
            pos.y = panelSize.height * 0.20f;
            fighter_maxlevel_text = TextSprite::create(s_gameStrings.base->maxlevel,GameConfig::defaultFontName,fontSize_l);
            fighter_maxlevel_text->setColor(Color3B::YELLOW);
            fighter_maxlevel_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
            fighter_maxlevel_text->setPosition(pos);
            panel->addChild(fighter_maxlevel_text);
            menu->setEnabled(false);
            fighter_maxlevel= true;
        }
    }

    {
        pos.x = 290;
        pos.y = panelSize.height * 0.85f;
        _flight_level_label = Label::createWithTTF(Value(s_playerConfig.fighterslevel[t_index]+1).asString(),fontFile,fontSize_m);
        _flight_level_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_level_label->setPosition(pos);
        _flight_level_label->setTextColor(infoColor);
        panel->addChild(_flight_level_label);
        _flight_level_label->setTag(9);
        
        pos.y = panelSize.height * 0.67f;
        _flight_attack_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].attack).asString(),fontFile,fontSize_m);
        _flight_attack_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_attack_label->setPosition(pos);
        _flight_attack_label->setTextColor(infoColor);
        panel->addChild(_flight_attack_label);
        _flight_attack_label->setTag(10);
        
        pos.y = panelSize.height * 0.5f;
        _flight_defend_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].defense).asString(),fontFile,fontSize_m);
        _flight_defend_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_defend_label->setPosition(pos);
        _flight_defend_label->setTextColor(infoColor);
        panel->addChild(_flight_defend_label);
        _flight_defend_label->setTag(11);
        
        if (s_playerConfig.fighterslevel[t_index] < FIGHTER_LEVEL_MAX-1)
        {
            pos.y = panelSize.height * 0.25f;
            _flight_upgradeforgem_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].gemForUpgrade).asString(),fontFile,fontSize_l);
            _flight_upgradeforgem_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            _flight_upgradeforgem_label->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
            _flight_upgradeforgem_label->setTextColor(Color4B(255,255,0,255));
            panel->addChild(_flight_upgradeforgem_label);
            _flight_upgradeforgem_label->setTag(12);
        }
        pos.x = 470;
        pos.y = panelSize.height * 0.85f;
        _flight_life_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].life).asString(),fontFile,fontSize_m);
        _flight_life_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_life_label->setPosition(pos);
        _flight_life_label->setTextColor(infoColor);
        panel->addChild(_flight_life_label);
        _flight_life_label->setTag(13);
        
        pos.y = panelSize.height * 0.67f;
        _flight_speed_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].speed).asString(),fontFile,fontSize_m);
        _flight_speed_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_speed_label->setPosition(pos);
        _flight_speed_label->setTextColor(infoColor);
        panel->addChild(_flight_speed_label);
        _flight_speed_label->setTag(14);
        
        pos.y = panelSize.height * 0.5f;
        _flight_range_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].range).asString(),fontFile,fontSize_m);
        _flight_range_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_range_label->setPosition(pos);
        _flight_range_label->setTextColor(infoColor);
        panel->addChild(_flight_range_label);
        _flight_range_label->setTag(15);
    }
}

void Base::createWeaponBottomInfo(Node* panel, int t_index)
{
    _isInFilghtUpgradeUI = false;
    auto panelSize = panel->getContentSize();
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
    int fontSize_m = 23;
    int fontSize_l = 25;
    auto infoColor = DIY_COLOR_BLUE3;
    
    auto fighterBox = Sprite::createWithSpriteFrameName("upgrade_box_mini.png");
    //fighterBox->setContentSize(Size(panelSize.width / 6,panelSize.height * 0.5f));
    //fighterBox->setScale(0.7f);
    fighterBox->setPosition(Point(panelSize.width / 6,panelSize.height * 0.625f));
    panel->addChild(fighterBox);

    auto menuitem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",CC_CALLBACK_1(Base::upgradeWeapon,this));
    menuitem->setScale(1.2f,0.7f);
    menuitem->setPosition(Point(panelSize.width / 2,panelSize.height * 0.20f));
    auto menu = Menu::create(menuitem,nullptr);
    menu->setPosition(Point::ZERO);
    panel->addChild(menu);
    
    auto menuitembuy = MenuItemImageLabel::createWithFrameName("btB_0.png","btB_1.png",CC_CALLBACK_1(Base::buyWeapon,this));
    //menuitembuy->setScale(0.8f);
    menuitembuy->setPosition(Point(panelSize.width / 2+180,panelSize.height/2+30));
    auto menubuy = Menu::create(menuitembuy,nullptr);
    menubuy->setPosition(Point::ZERO);
    panel->addChild(menubuy);
    
    Sprite* spar;
    
    auto pos = Point(200,panelSize.height * 0.85f);
    
    {
        weapon_levelText = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize_m);
        weapon_levelText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        weapon_levelText->setPosition(pos);
        panel->addChild(weapon_levelText);
        
        pos.y = panelSize.height * 0.67f;
        weapon_attText = TextSprite::create(s_gameStrings.base->upgradeAtt,GameConfig::defaultFontName,fontSize_m);
        weapon_attText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        weapon_attText->setPosition(pos);
        panel->addChild(weapon_attText);
        
        pos.y = panelSize.height * 0.5f;
        weapon_durationText = TextSprite::create(s_gameStrings.base->upgradeDuration,GameConfig::defaultFontName,fontSize_m);
        weapon_durationText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        weapon_durationText->setPosition(pos);
        panel->addChild(weapon_durationText);
        
        weapon_maxlevel = false;
        if(s_playerConfig.weaponslevel[t_index] < WEAPON_LEVEL_MAX-1)
        {
            spar = Sprite::createWithSpriteFrameName("icon_gem.png");
            spar->setPosition(Point(180,panelSize.height * 0.20f));
            panel->addChild(spar);
            
            pos.x = 400;
            pos.y = panelSize.height * 0.20f;
            weapon_leveUpText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize_l);
            weapon_leveUpText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            weapon_leveUpText->setPosition(pos-Point(85,0));
            panel->addChild(weapon_leveUpText);
        }
        else
        {
            pos.x = panelSize.width/2;
            pos.y = panelSize.height * 0.20f;
            weapon_maxlevel_text = TextSprite::create(s_gameStrings.base->maxlevel,GameConfig::defaultFontName,fontSize_l);
            weapon_maxlevel_text->setColor(Color3B::YELLOW);
            weapon_maxlevel_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
            weapon_maxlevel_text->setPosition(pos);
            panel->addChild(weapon_maxlevel_text);
            menu->setEnabled(false);
            weapon_maxlevel = true;
        }
        
        auto stone_icon = Sprite::createWithSpriteFrameName("icon_gem.png");
        stone_icon->setPosition(Point(menuitembuy->getContentSize().width/2-35,menuitembuy->getContentSize().height/2+20));
        menuitembuy->addChild(stone_icon);
        
        weapon_buy_text = TextSprite::create(s_gameStrings.base->upgradeBuy,GameConfig::defaultFontName,fontSize_l);
        weapon_buy_text->setColor(DIY_COLOR_BLUE5);
        weapon_buy_text->setPosition(Point(menuitembuy->getContentSize().width/2,menuitembuy->getContentSize().height/2-20));
        menuitembuy->addChild(weapon_buy_text);
    }
    
    {
        pos.x = 310;
        pos.y = panelSize.height * 0.85f;
        _weapon_level_label = Label::createWithTTF(Value(s_playerConfig.weaponslevel[t_index]+1).asString(),fontFile,fontSize_m);
        _weapon_level_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _weapon_level_label->setPosition(pos);
        _weapon_level_label->setTextColor(infoColor);
        panel->addChild(_weapon_level_label);
        
        pos.y = panelSize.height * 0.67f;
        _weapon_attack_label = Label::createWithTTF(Value(s_weaponConfigs[t_index][s_playerConfig.weaponslevel[t_index]].attack).asString(),fontFile,fontSize_m);
        _weapon_attack_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _weapon_attack_label->setPosition(pos);
        _weapon_attack_label->setTextColor(infoColor);
        panel->addChild(_weapon_attack_label);
        
        pos.y = panelSize.height * 0.5f;
        char p[30];
        sprintf(p, "%.2f",s_weaponConfigs[t_index][s_playerConfig.weaponslevel[t_index]].duration);
        _weapon_duration_label = Label::createWithTTF(p,fontFile,fontSize_m);
        _weapon_duration_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _weapon_duration_label->setPosition(pos);
        _weapon_duration_label->setTextColor(infoColor);
        panel->addChild(_weapon_duration_label);
        
        if(s_playerConfig.weaponslevel[t_index] < WEAPON_LEVEL_MAX-1)
        {
            pos.y = panelSize.height * 0.25f;
            _weapon_upgradeforgem_label = Label::createWithTTF(Value(s_weaponConfigs[t_index][s_playerConfig.weaponslevel[t_index]].gemForUpgrade).asString(),fontFile,fontSize_l);
            _weapon_upgradeforgem_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            _weapon_upgradeforgem_label->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
            _weapon_upgradeforgem_label->setTextColor(Color4B(255,255,0,255));
            panel->addChild(_weapon_upgradeforgem_label);
        }
        _buy_gem = Label::createWithTTF(Value(s_weaponConfigs[t_index][s_playerConfig.weaponslevel[t_index]].gemForUpgrade).asString(),fontFile,fontSize_m);
        _buy_gem->setColor(Color3B::YELLOW);
        _buy_gem->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _buy_gem->setPosition(Point(menuitembuy->getContentSize().width/2-15,menuitembuy->getContentSize().height/2+18));
        menuitembuy->addChild(_buy_gem);
    }
}


void Base::createFighterMiddleInfo(Node* panel)
{
    auto panelSize = panel->getContentSize();
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
    int fontSize_m = 23;
    int fontSize_l = 25;
    auto infoColor = DIY_COLOR_BLUE3;
    
    auto menuitem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",CC_CALLBACK_1(Base::upgradeStoneMax,this));
    menuitem->setScale(1.2f,0.7f);
    menuitem->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
    auto menu = Menu::create(menuitem,nullptr);
    menu->setPosition(Point::ZERO);
    panel->addChild(menu);
    
    Sprite* spar;
    
    auto pos = Point(180,panelSize.height * 0.85f);
    TextSprite* levelText;
    {
        auto stoneicon = Sprite::createWithSpriteFrameName("icon_stone.png");
        stoneicon->setScale(0.8f);
        stoneicon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        stoneicon->setPosition(pos-Point(50,0));
        panel->addChild(stoneicon);
        
        levelText = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize_m);
        levelText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        levelText->setPosition(stoneicon->getPositionX()+stoneicon->getContentSize().width,stoneicon->getPositionY());
        panel->addChild(levelText);
        
        pos.x = panelSize.width/2;
        pos.y = panelSize.height * 0.57f;
        auto sparCapacityText = TextSprite::create(s_gameStrings.base->sparCapacity,GameConfig::defaultFontName,fontSize_m);
        sparCapacityText->setColor(DIY_COLOR_YELLOW4);
        sparCapacityText->setPosition(pos);
        panel->addChild(sparCapacityText);
        
        
        TextSprite * leveUpText;
        TextSprite * maxlevel_text;
        bool tempBool = true;
        if(s_playerConfig.stonecapacitylevel < STONE_CAPACITY_LEVEL_MAX-1)
        {
            spar = Sprite::createWithSpriteFrameName("icon_gem.png");
            spar->setPosition(Point(170,panelSize.height * 0.25f));
            panel->addChild(spar);
            
            pos.x = 345;
            pos.y = panelSize.height * 0.25f;
            leveUpText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize_l);
            leveUpText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            leveUpText->setPosition(pos-Point(40,0));
            panel->addChild(leveUpText);
        }
        else
        {
            pos.x = panelSize.width/2;
            pos.y = panelSize.height * 0.25f;
            maxlevel_text = TextSprite::create(s_gameStrings.base->maxlevel,GameConfig::defaultFontName,fontSize_l);
            maxlevel_text->setColor(Color3B::YELLOW);
            maxlevel_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
            maxlevel_text->setPosition(pos);
            panel->addChild(maxlevel_text);
            menu->setEnabled(false);
            tempBool = false;
        }
        auto listener = EventListenerCustom::create(GameConfig::eventLanguageChange, [=](EventCustom* event)
                                                    {
                                                        levelText->setText(s_gameStrings.base->upgradeLevel);
                                                        sparCapacityText->setText(s_gameStrings.base->sparCapacity);
                                                        if (tempBool)
                                                        {
                                                            leveUpText->setText(s_gameStrings.base->upgrade);
                                                            middle_level->setPosition(Point(levelText->getPositionX()+levelText->getContentSize().width,levelText->getPositionY()));
                                                        }
                                                        else
                                                        {
                                                            maxlevel_text->setText(s_gameStrings.base->maxlevel);
                                                        }
                                                    });
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    {
        pos.x = 235;
        pos.y = panelSize.height * 0.85f;
        middle_level = Label::createWithSystemFont(Value(s_playerConfig.stonecapacitylevel+1).asString(),"Arial",fontSize_m);
        middle_level->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        middle_level->setPosition(Point(levelText->getPositionX()+levelText->getContentSize().width,levelText->getPositionY()));
        panel->addChild(middle_level);
        
        pos.x = 330;
        pos.y = panelSize.height * 0.85f;
        middle_init = Label::createWithTTF(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel].initstone).asString(),fontFile,fontSize_m);
        middle_init->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        middle_init->setPosition(pos);
        middle_init->setTextColor(infoColor);
        panel->addChild(middle_init);
        
        middle_slash = Label::createWithTTF("/",fontFile,fontSize_m);
        middle_slash->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        middle_slash->setPosition(middle_init->getPosition()+Point(middle_init->getContentSize().width,0));
        panel->addChild(middle_slash);
        
        middle_total = Label::createWithTTF(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel].maxstone).asString(),fontFile,fontSize_m);
        middle_total->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        middle_total->setPosition(middle_slash->getPosition()+Point(middle_slash->getContentSize().width,0));
        panel->addChild(middle_total);
        
        if(s_playerConfig.stonecapacitylevel < STONE_CAPACITY_LEVEL_MAX-1)
        {
            pos.y = panelSize.height * 0.25f;
            middle_leveUpCost = Label::createWithTTF(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel].gemForUpgrade).asString(),fontFile,fontSize_l);
            middle_leveUpCost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            middle_leveUpCost->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
            middle_leveUpCost->setTextColor(Color4B(255,255,0,255));
            panel->addChild(middle_leveUpCost);
        }
    }
}
void Base::createFighterTopInfo(Node* panel)
{
    auto panelSize = panel->getContentSize();
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
    int fontSize_m = 23;
    int fontSize_l = 25;
    auto infoColor = DIY_COLOR_BLUE3;
    
    auto menuitem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",CC_CALLBACK_1(Base::upgradeStoneSpeed,this));
    menuitem->setScale(1.2f,0.7f);
    menuitem->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
    auto menu = Menu::create(menuitem,nullptr);
    menu->setPosition(Point::ZERO);
    panel->addChild(menu);
    
    Sprite* spar;
    
    auto pos = Point(180,panelSize.height * 0.85f);
    TextSprite* levelText = nullptr;
    {
        auto stoneicon = Sprite::createWithSpriteFrameName("icon_stone.png");
        stoneicon->setScale(0.8f);
        stoneicon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        stoneicon->setPosition(pos-Point(60,0));
        panel->addChild(stoneicon);
        
        levelText = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize_m);
        levelText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        levelText->setPosition(Point(stoneicon->getPositionX()+stoneicon->getContentSize().width,stoneicon->getPositionY()));
        panel->addChild(levelText);
        
        pos.x = panelSize.width/2;
        pos.y = panelSize.height * 0.57f;
        auto sparRecoverRateText = TextSprite::create(s_gameStrings.base->sparRecoverRate,GameConfig::defaultFontName,fontSize_m);
        sparRecoverRateText->setColor(DIY_COLOR_YELLOW4);
        sparRecoverRateText->setPosition(pos);
        panel->addChild(sparRecoverRateText);
        
        TextSprite * leveUpText;
        TextSprite * maxlevel_text;
        bool tempBool = true;
        //不能超过最大级别
        if(s_playerConfig.stonespeedlevel < STONE_SPEED_LEVEL_MAX-1)
        {
            spar = Sprite::createWithSpriteFrameName("icon_gem.png");
            spar->setPosition(Point(165,panelSize.height * 0.25f));
            panel->addChild(spar);
            
            pos.x = 340;
            pos.y = panelSize.height * 0.25f;
            leveUpText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize_l);
            leveUpText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            leveUpText->setPosition(pos-Point(40,0));
            panel->addChild(leveUpText);
        }
        else
        {
            pos.x = panelSize.width/2;
            pos.y = panelSize.height * 0.25f;
            maxlevel_text = TextSprite::create(s_gameStrings.base->maxlevel,GameConfig::defaultFontName,fontSize_l);
            maxlevel_text->setColor(Color3B::YELLOW);
            maxlevel_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
            maxlevel_text->setPosition(pos);
            panel->addChild(maxlevel_text);
            menu->setEnabled(false);
            tempBool = false;
        }
        auto listener = EventListenerCustom::create(GameConfig::eventLanguageChange, [=](EventCustom* event)
                                                    {
                                                        levelText->setText(s_gameStrings.base->upgradeLevel);
                                                        sparRecoverRateText->setText(s_gameStrings.base->sparRecoverRate);
                                                        top_second->setText(s_gameStrings.base->second);
                                                        if (tempBool)
                                                        {
                                                            leveUpText->setText(s_gameStrings.base->upgrade);
                                                            top_level->setPosition(Point(levelText->getPositionX()+levelText->getContentSize().width,levelText->getPositionY()));
                                                        }
                                                        else
                                                        {
                                                            maxlevel_text->setText(s_gameStrings.base->maxlevel);
                                                        }
                                                    });
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    {
        pos.x = 235;
        pos.y = panelSize.height * 0.85f;
        top_level = Label::createWithSystemFont(Value(s_playerConfig.stonespeedlevel+1).asString(),"Arial",fontSize_m);
        top_level->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        top_level->setPosition(Point(levelText->getPositionX()+levelText->getContentSize().width,levelText->getPositionY()));
        panel->addChild(top_level);
        
        pos.x = 320;
        pos.y = panelSize.height * 0.85f;
        top_plus = Label::createWithTTF("+",fontFile,fontSize_m);
        top_plus->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        top_plus->setPosition(pos);
        top_plus->setTextColor(infoColor);
        panel->addChild(top_plus);
        
        top_speed = Label::createWithTTF(Value(s_stoneSpeed[s_playerConfig.stonespeedlevel].speed).asString(),fontFile,fontSize_m);
        top_speed->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        top_speed->setPosition(top_plus->getPosition()+Point(top_plus->getContentSize().width,0));
        top_speed->setTextColor(infoColor);
        panel->addChild(top_speed);
        
        top_slash = Label::createWithTTF("/",fontFile,fontSize_m);
        top_slash->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        top_slash->setPosition(top_speed->getPosition()+Point(top_speed->getContentSize().width,0)+Point(5,0));
        panel->addChild(top_slash);
        
        
        top_second = TextSprite::create(s_gameStrings.base->second,GameConfig::defaultFontName,fontSize_m);
        top_second->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        top_second->setPosition(top_slash->getPosition()+Point(top_slash->getContentSize().width,0));
        panel->addChild(top_second);
        
        if(s_playerConfig.stonespeedlevel < STONE_SPEED_LEVEL_MAX-1)
        {
            pos.y = panelSize.height * 0.25f;
            top_leveUpCost = Label::createWithTTF(Value(s_stoneSpeed[s_playerConfig.stonespeedlevel].gemForUpgrade).asString(),fontFile,fontSize_l);
            top_leveUpCost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            top_leveUpCost->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
            top_leveUpCost->setTextColor(Color4B(255,255,0,255));
            panel->addChild(top_leveUpCost);
        }
    }
}
void Base::createTopPanel()
{
    _topPanel = Node::create();
    this->addChild(_topPanel);

    auto leftRail = Sprite::createWithSpriteFrameName("dingjia.png");
    leftRail->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    leftRail->setPosition(s_visibleRect.top);
    _topPanel->addChild(leftRail);

    auto rightRail = Sprite::createWithSpriteFrameName("dingjia.png");
    rightRail->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    rightRail->setFlippedX(true);
    rightRail->setPosition(s_visibleRect.top);
    _topPanel->addChild(rightRail);

    medalItem = MenuItemImageLabel::createWithFrameName("btA_0.png","btA_1.png",
        CC_CALLBACK_1(Base::menuCallbackMedal,this),s_gameStrings.base->topBarMedal);
    medalItem->setPosition(Point(120,890));

    auto settingItem = MenuItemImageLabel::createWithFrameName("option_0.png","option_1.png",
        CC_CALLBACK_1(Base::menuCallbackSetting,this));
    settingItem->setPosition(Point(s_visibleRect.center.x,890));

    auto battleItem = MenuItemImageLabel::createWithFrameName("btA_0.png","btA_1.png",
        CC_CALLBACK_1(Base::menuCallbackBattle,this),s_gameStrings.base->topBarBattle);
    battleItem->setPosition(Point(520,890));

    auto menu = Menu::create( medalItem, settingItem, battleItem,nullptr);
    menu->setPosition(Point::ZERO);
    _topPanel->addChild(menu);
    
    showOrHideMedalLogo(nullptr);
    
    auto listener = EventListenerCustom::create(GameConfig::eventLanguageChange, [=](EventCustom* event)
                                                {
                                                    medalItem->setText(s_gameStrings.base->topBarMedal);
                                                    battleItem->setText(s_gameStrings.base->topBarBattle);
                                                    ConfigManager::getInstance()->saveConfig();
                                                   
                                                });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Base::menuCallbackMedal(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    _topPanel->runAction(MoveBy::create(0.2f,Point(0,200)));
    _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,-s_visibleRect.visibleHeight)));
    _bottomPanel->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,-150)),
                                           MoveBy::create(0.05f,Point(0,14)),nullptr ));
    _curSelectedFlight->setVisible(false);
    auto medalLayer = Medal::create();
    addChild(medalLayer,4);
}

void Base::menuCallbackSetting(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    auto settingLayer = MenuSettings::create(GameInterface::Base);
    addChild(settingLayer,4);
}

void Base::menuCallbackBattle(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    _topPanel->runAction(MoveBy::create(0.2f,Point(0,200)));
    _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,-s_visibleRect.visibleHeight)));
    _bottomPanel->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,-150)),
        MoveBy::create(0.05f,Point(0,14)),nullptr ));
    _curSelectedFlight->setVisible(false);
    
    auto stageSelect = StageSelect::create();
    this->addChild(stageSelect,4);
}

void Base::upgradeStoneSpeed(Ref* sender)
{
    showUpgradeUI(BasePanel::Toppanel);
}

void Base::upgradeStoneMax(Ref* sender)
{
    showUpgradeUI(BasePanel::MiddlePanel);
}

void Base::upgradeFlight(Ref* sender)
{
    showUpgradeUI(BasePanel::FlightPanel);
}

void Base::upgradeWeapon(Ref* sender)
{
    showUpgradeUI(BasePanel::WeaponPanel);

}

void Base::buyWeapon(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    MedalChecker::getInstance()->showTip();
    int cost = s_weaponConfigs[_curSeletedIndex-FIGHTER_MAX][s_playerConfig.weaponslevel[_curSeletedIndex-FIGHTER_MAX]].costGem;
    if (cost <= s_playerConfig.gem) {
        if(s_playerConfig.weaponCount[_curSeletedIndex-FIGHTER_MAX] < s_weaponConfigs[_curSeletedIndex-FIGHTER_MAX][s_playerConfig.weaponslevel[_curSeletedIndex-FIGHTER_MAX]].capacity)
        {
            s_playerConfig.gem = s_playerConfig.gem - cost;
            s_playerConfig.weaponCount[_curSeletedIndex-FIGHTER_MAX]++;
            showGemTip(cost, true);
            
            if(_playerBag)
            {
                _playerBag->setGem(s_playerConfig.gem);
            }
            
            _eventDispatcher->dispatchCustomEvent(GameConfig::eventUpdateMenuItemWeaponData,(void*)(_curSeletedIndex-FIGHTER_MAX));
            _eventDispatcher->dispatchCustomEvent(GameConfig::eventShowWeaponMenu);//菜单动画
            
            ConfigManager::getInstance()->saveConfig();
        }
        else
        {
            //提示超出携带
        }
    }
    else
    {
        if(s_playerConfig.overstage < STAGEOFCANBUYGEM)
        {
            addChild(NotificationLayer::create(s_gameStrings.base->nogemcannotbuy),100);
        }
        else
        {
            addChild(NoGemLayer::create(),100);
        }
    }
}

void Base::showUpgradeUI(BasePanel basePanel)
{
    PLAY_BUTTON_EFFECT;
    auto layer = UpgradeUILayer::create(basePanel, _curSeletedIndex);
    this->addChild(layer,4);
}

void Base::showGemTip(int num, bool isCost)
{
    const Point GemPos = Point(300,180);

    if (isCost) {
        if(num)
        {
            if (num) {
                auto gem_text_bk = Sprite::createWithSpriteFrameName("gemTip_box.png");
                gem_text_bk->setAnchorPoint(Point::ANCHOR_MIDDLE);
                gem_text_bk->setPosition(GemPos+Point(0,30));
                this->addChild(gem_text_bk);
                
                std::string strGemtext = "- " + Value(num).asString();
                auto gem_text = TextSprite::create(strGemtext);
                gem_text->setColor(Color3B::RED);
                gem_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
                gem_text->setPosition(Point(gem_text_bk->getContentSize().width/2,gem_text_bk->getContentSize().height/2));
                gem_text_bk->addChild(gem_text);
                
                gem_text_bk->setOpacity(0);
                gem_text_bk->runAction(Sequence::create(FadeIn::create(0.1f), DelayTime::create(0.3f), FadeOut::create(0.1f), RemoveSelf::create(), nullptr));
            }
        }
    }
    else
    {
        if (num) {
            auto gem_text_bk = Sprite::createWithSpriteFrameName("gemTip_box.png");
            gem_text_bk->setAnchorPoint(Point::ANCHOR_MIDDLE);
            gem_text_bk->setPosition(GemPos+Point(0,30));
            this->addChild(gem_text_bk);
            
            std::string strGemtext = "+ " + Value(num).asString();
            auto gem_text = TextSprite::create(strGemtext);
            gem_text->setColor(DIY_COLOR_BLUE5);
            gem_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
            gem_text->setPosition(Point(gem_text_bk->getContentSize().width/2,gem_text_bk->getContentSize().height/2));
            gem_text_bk->addChild(gem_text);
            
            gem_text_bk->setOpacity(0);
            gem_text_bk->runAction(Sequence::create(FadeIn::create(0.1f), DelayTime::create(0.3f), FadeOut::create(0.1f), RemoveSelf::create(), nullptr));
        }
    }
}

void Base::showOrHideMedalLogo(EventCustom* event)
{
    bool isNewButNoGet = false;
    for (int i=0; i<25; ++i) {
        if (!s_playerConfig.medallocked[i] && s_playerConfig.medalget[i]) {
            isNewButNoGet = true;
        }
    }
    
    if (isNewButNoGet) {
        if (!medalLogo) {
            medalLogo = Sprite::createWithSpriteFrameName("icon_new.png");
            medalLogo->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
            medalLogo->setPosition(medalItem->getContentSize().width,medalItem->getContentSize().height);
            medalItem->addChild(medalLogo);
        }
    }
    else{
        if (medalLogo) {
            medalLogo->removeFromParent();
            medalLogo = nullptr;
        }
    }
}

//飞机尾部粒子效果颜色设置
Color4F Base::getPlainParticleEffectColor(int i)
{
    Color4F parEffColor;
    switch (i) {
        case 0:
            parEffColor = Color4F(0.0f, 0.0f, 1.0f, 0.5f);//r,g,b,a
            break;
        case 1:
            parEffColor = Color4F(0.0f, 1.0f, 0.0f, 0.5f);
            break;
        case 2:
            parEffColor = Color4F(1.0f, 0.0f, 0.0f, 0.5f);
            break;
        case 3:
            parEffColor = Color4F(0.0f, 1.0f, 1.0f, 0.5f);
            break;
        case 4:
            parEffColor = Color4F(1.0f, 0.0f, 1.0f, 0.5f);
            break;
        case 5:
        default:
            parEffColor = Color4F(1.0f, 1.0f, 0.0f, 0.5f);
            break;
    }
    return parEffColor;
}
