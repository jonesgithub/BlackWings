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
    auto bg = Sprite::create("mainBackground.png");
    bg->setPosition(s_visibleRect.center);
    addChild(bg);
    
    this->removeChild((LoadResourceLayer*)sender,true);

    GSBaseInit((GameLanguage)s_playerConfig.language);

    createUpgrade();

    createBottomPanel();
    
    createTopPanel();

    auto listenerStageSelect = EventListenerCustom::create(StageSelect::eventBack, [=](EventCustom* event){
        _topPanel->runAction(MoveBy::create(0.2f,Point(0,-200)));
        _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,s_visibleRect.visibleHeight)));
        _bottomPanel->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,136)),nullptr ));
        _curSelectedFlight->setVisible(true);
    });
    
    auto listenerMedal = EventListenerCustom::create(Medal::eventBack, [=](EventCustom* event){
        _topPanel->runAction(MoveBy::create(0.2f,Point(0,-200)));
        _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,s_visibleRect.visibleHeight)));
        _bottomPanel->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,136)),nullptr ));
        _curSelectedFlight->setVisible(true);
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStageSelect, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMedal, this);
    
    //enter,default 1st flight
    {
        auto player = (PlayerMenuItem*)_playerBag->_playerMenu->getChildByTag(1000);
        player->selected();
        
        char name[30];
        sprintf(name,"plain_%d_lv_%d.png",1,s_playerConfig.fighterslevel[0]+1);
        
        auto flight = Sprite::createWithSpriteFrameName(name);
        flight->setPosition(player->getPosition()+Point(0,50));
        _bottomPanel->addChild(flight);
        
        _curSelectedFlight = flight;
        _curSeletedIndex = 0;
        
        auto move = MoveTo::create(1.0, Point(123,370));
        flight->runAction(move);
    }
    
    auto listener = EventListenerCustom::create(PlayerBar::eventPlayerSelect, [=](EventCustom* event)
                                                         {
                                                             int index = (uintptr_t)event->getUserData();
                                                             for (int i = 0; i<FIGHTER_MAX; i++)
                                                             {
                                                                 if(index == i && _curSeletedIndex!=i)
                                                                 {
                                                                     _curSelectedFlight->runAction(Sequence::create(FadeOut::create(0.5f),
                                                                                                                    RemoveSelf::create(),
                                                                                                                    nullptr));
                                                                     char name[30];
                                                                     sprintf(name,"plain_%d_lv_%d.png",index+1,s_playerConfig.fighterslevel[index]+1);
                                                                     
                                                                     auto flight = Sprite::createWithSpriteFrameName(name);
                                                                     flight->setPosition(_playerBag->_playerMenu->getChildByTag(1000+i)->getPosition()+Point(0,50));
                                                                     _bottomPanel->addChild(flight);
                                                                     
                                                                     _curSelectedFlight = flight;
                                                                     _curSeletedIndex = i;
                                                                     
                                                                     auto move = MoveTo::create(1.0f, Point(123,370));
                                                                     flight->runAction(move);
                                                                 }
                                                                 
                                                             }
                                                             for (int i=FIGHTER_MAX; i<FIGHTER_MAX + WEAPON_MAX; ++i) {
                                                                 if(index == i && _curSeletedIndex!=i)
                                                                 {
                                                                     _curSelectedFlight->runAction(Sequence::create(FadeOut::create(0.5f),
                                                                                                                    RemoveSelf::create(),
                                                                                                                    nullptr));
                                                                     char name[30];
                                                                     sprintf(name,"bomb_%d_%d.png",index-FIGHTER_MAX+1,s_playerConfig.weaponslevel[index-FIGHTER_MAX]+1);
                                                                     
                                                                     auto flight = Sprite::createWithSpriteFrameName(name);
                                                                     flight->setPosition(_playerBag->_playerMenu->getChildByTag(1000+i)->getPosition()-Point(s_visibleRect.visibleWidth, 0)+Point(0,50));
                                                                     _bottomPanel->addChild(flight);
                                                                     
                                                                     _curSelectedFlight = flight;
                                                                     _curSeletedIndex = i;
                                                                     
                                                                     auto move = MoveTo::create(1.0f, Point(123,370));
                                                                     flight->runAction(move);
                                                                 }
                                                                 
                                                             }
                                                             
                                                             if (index<6) {
                                                                 if(_isInFilghtUpgradeUI)
                                                                 {
                                                                 _flight_level_label ->setString(Value(s_playerConfig.fighterslevel[index]+1).asString());
                                                                 _flight_attack_label ->setString(Value(s_plainConfigs[index][s_playerConfig.fighterslevel[index]].attack).asString());
                                                                 _flight_defend_label ->setString(Value(s_plainConfigs[index][s_playerConfig.fighterslevel[index]].defense).asString());
                                                                 _flight_life_label ->setString(Value(s_plainConfigs[index][s_playerConfig.fighterslevel[index]].life).asString());
                                                                 _flight_speed_label ->setString(Value(s_plainConfigs[index][s_playerConfig.fighterslevel[index]].speed).asString());
                                                                 _flight_range_label ->setString(Value(s_plainConfigs[index][s_playerConfig.fighterslevel[index]].range).asString());
                                                                 _flight_upgradeforgem_label->setString(Value(s_plainConfigs[index][s_playerConfig.fighterslevel[index]].gemForUpgrade).asString());
                                                                 }
                                                                 else
                                                                 {
                                                                     upgradeFighter->removeAllChildren();
                                                                     int baseHeight = 50;
                                                                     auto boxPos = Point(s_visibleRect.center.x,s_visibleRect.center.y - baseHeight * 5);
                                                                     
                                                                     upgradeFighter = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
                                                                     upgradeFighter->setContentSize(Size(s_visibleRect.visibleWidth - 50,baseHeight * 4.5));
                                                                     upgradeFighter->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
                                                                     upgradeFighter->setPosition(boxPos);
                                                                     _upgradePanel->addChild(upgradeFighter);
                                                                     createFighterBottomInfo(upgradeFighter, index);
                                                                 }
                                                             }
                                                             else
                                                             {
                                                                 if(_isInFilghtUpgradeUI)
                                                                 {
                                                                     upgradeFighter->removeAllChildren();
                                                                     int baseHeight = 50;
                                                                     auto boxPos = Point(s_visibleRect.center.x,s_visibleRect.center.y - baseHeight * 5);
                                                                     
                                                                     upgradeFighter = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
                                                                     upgradeFighter->setContentSize(Size(s_visibleRect.visibleWidth - 50,baseHeight * 4.5));
                                                                     upgradeFighter->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
                                                                     upgradeFighter->setPosition(boxPos);
                                                                     _upgradePanel->addChild(upgradeFighter);
                                                                     createWeaponBottomInfo(upgradeFighter, index - FIGHTER_MAX);
                                                                 }
                                                                 else
                                                                 {
                                                                     _weapon_level_label ->setString(Value(s_playerConfig.weaponslevel[index - FIGHTER_MAX]+1).asString());
                                                                     _weapon_attack_label ->setString(Value(s_weaponConfigs[index - FIGHTER_MAX][s_playerConfig.weaponslevel[index - FIGHTER_MAX]+1].attack).asString());
                                                                     _weapon_duration_label ->setString(Value(s_weaponConfigs[index - FIGHTER_MAX][s_playerConfig.weaponslevel[index - FIGHTER_MAX]+1].duration).asString());
                                                                     _weapon_upgradeforgem_label ->setString(Value(s_weaponConfigs[index - FIGHTER_MAX][s_playerConfig.weaponslevel[index - FIGHTER_MAX]+1].gemForUpgrade).asString());                                                                 }
                                                             }
                                                             
                                                         });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    

}

void Base::createBottomPanel()
{
    _bottomPanel =  Node::create();
    this->addChild(_bottomPanel);
    _playerBag = PlayerBar::create();
    _bottomPanel->addChild(_playerBag,1);
}

void Base::createUpgrade()
{
    _upgradePanel = Node::create();
    this->addChild(_upgradePanel);

    int baseHeight = 50;
    int padding = 30;

    auto boxPos = Point(s_visibleRect.center.x,s_visibleRect.center.y - baseHeight * 5);

    upgradeFighter = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
    upgradeFighter->setContentSize(Size(s_visibleRect.visibleWidth - 50,baseHeight * 4.5));
    upgradeFighter->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    upgradeFighter->setPosition(boxPos);
    _upgradePanel->addChild(upgradeFighter);
    createFighterBottomInfo(upgradeFighter, 0);

    boxPos.y += baseHeight * 4.5 + padding;
    auto sparCapacitySize = Size(s_visibleRect.visibleWidth - 60,baseHeight * 3);
    auto upgradeSparCapacity = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
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
    
    boxPos.y += baseHeight * 3 + padding;
    auto sparRecoverySize = Size(s_visibleRect.visibleWidth - 70,baseHeight * 3);
    auto upgradeSparRecovery = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
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
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    auto infoColor = Color4B(153,217,234,255);
    
    auto fighterBox = Sprite::createWithSpriteFrameName("upgrade_box_mini.png");
    //fighterBox->setContentSize(Size(panelSize.width / 6,panelSize.height * 0.5f));
    fighterBox->setScale(0.7f);
    fighterBox->setPosition(Point(panelSize.width / 6,panelSize.height * 0.625f));
    panel->addChild(fighterBox);
    fighterBox->setTag(0);
    
//    auto bottombluBar = Scale9Sprite::createWithSpriteFrameName("bt_main_1.png");
//    bottombluBar->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
//    bottombluBar->setScaleX(1.2f);
//    bottombluBar->setScaleY(0.5f);
//    panel->addChild(bottombluBar);
//    bottombluBar->setTag(1);

    auto menuitem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",CC_CALLBACK_1(Base::upgradeFlight,this));
    menuitem->setScale(1.2f,0.5f);
    menuitem->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
    auto menu = Menu::create(menuitem,nullptr);
    menu->setPosition(Point::ZERO);
    panel->addChild(menu);
    
    auto spar = Sprite::createWithSpriteFrameName("icon_gem.png");
    spar->setPosition(Point(200,panelSize.height * 0.25f));
    panel->addChild(spar);
    spar->setTag(2);
    
    auto pos = Point(200,panelSize.height * 0.85f);

    {
        auto levelText = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize);
        levelText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        levelText->setPosition(pos);
        panel->addChild(levelText);

        pos.y = panelSize.height * 0.67f;
        auto attText = TextSprite::create(s_gameStrings.base->upgradeAtt,GameConfig::defaultFontName,fontSize);
        attText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        attText->setPosition(pos);
        panel->addChild(attText);
        attText->setTag(3);

        pos.y = panelSize.height * 0.5f;
        auto defText = TextSprite::create(s_gameStrings.base->upgradeDef,GameConfig::defaultFontName,fontSize);
        defText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        defText->setPosition(pos);
        panel->addChild(defText);
        defText->setTag(4);

        pos.x = 400;
        pos.y = panelSize.height * 0.85f;
        auto lifeText = TextSprite::create(s_gameStrings.base->upgradeLife,GameConfig::defaultFontName,fontSize);
        lifeText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        lifeText->setPosition(pos);
        panel->addChild(lifeText);
        lifeText->setTag(5);

        pos.y = panelSize.height * 0.67f;
        auto spdText = TextSprite::create(s_gameStrings.base->upgradeSpd,GameConfig::defaultFontName,fontSize);
        spdText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        spdText->setPosition(pos);
        panel->addChild(spdText);
        spdText->setTag(6);

        pos.y = panelSize.height * 0.5f;
        auto rangeText = TextSprite::create(s_gameStrings.base->upgradeRange,GameConfig::defaultFontName,fontSize);
        rangeText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        rangeText->setPosition(pos);
        panel->addChild(rangeText);
        rangeText->setTag(7);
        
        pos.y = panelSize.height * 0.25f;
        auto leveUpText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize);
        leveUpText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpText->setPosition(pos-Point(40,0));
        panel->addChild(leveUpText);
        leveUpText->setTag(8);
    }

    {
        pos.x = 290;
        pos.y = panelSize.height * 0.85f;
        _flight_level_label = Label::createWithTTF(Value(s_playerConfig.fighterslevel[t_index]+1).asString(),fontFile,fontSize);
        _flight_level_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_level_label->setPosition(pos);
        _flight_level_label->setTextColor(infoColor);
        panel->addChild(_flight_level_label);
        _flight_level_label->setTag(9);
        
        pos.y = panelSize.height * 0.67f;
        _flight_attack_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].attack).asString(),fontFile,fontSize);
        _flight_attack_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_attack_label->setPosition(pos);
        _flight_attack_label->setTextColor(infoColor);
        panel->addChild(_flight_attack_label);
        _flight_attack_label->setTag(10);
        
        pos.y = panelSize.height * 0.5f;
        _flight_defend_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].defense).asString(),fontFile,fontSize);
        _flight_defend_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_defend_label->setPosition(pos);
        _flight_defend_label->setTextColor(infoColor);
        panel->addChild(_flight_defend_label);
        _flight_defend_label->setTag(11);
        
        pos.y = panelSize.height * 0.25f;
        _flight_upgradeforgem_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].gemForUpgrade).asString(),fontFile,fontSize);
        _flight_upgradeforgem_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _flight_upgradeforgem_label->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
        _flight_upgradeforgem_label->setTextColor(Color4B(255,255,0,255));
        panel->addChild(_flight_upgradeforgem_label);
        _flight_upgradeforgem_label->setTag(12);
        
        pos.x = 490;
        pos.y = panelSize.height * 0.85f;
        _flight_life_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].life).asString(),fontFile,fontSize);
        _flight_life_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_life_label->setPosition(pos);
        _flight_life_label->setTextColor(infoColor);
        panel->addChild(_flight_life_label);
        _flight_life_label->setTag(13);
        
        pos.y = panelSize.height * 0.67f;
        _flight_speed_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].speed).asString(),fontFile,fontSize);
        _flight_speed_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _flight_speed_label->setPosition(pos);
        _flight_speed_label->setTextColor(infoColor);
        panel->addChild(_flight_speed_label);
        _flight_speed_label->setTag(14);
        
        pos.y = panelSize.height * 0.5f;
        _flight_range_label = Label::createWithTTF(Value(s_plainConfigs[t_index][s_playerConfig.fighterslevel[t_index]].range).asString(),fontFile,fontSize);
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
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    auto infoColor = Color4B(153,217,234,255);
    
    auto fighterBox = Sprite::createWithSpriteFrameName("upgrade_box_mini.png");
    //fighterBox->setContentSize(Size(panelSize.width / 6,panelSize.height * 0.5f));
    fighterBox->setScale(0.7f);
    fighterBox->setPosition(Point(panelSize.width / 6,panelSize.height * 0.625f));
    panel->addChild(fighterBox);
    
//    auto bottombluBar = Scale9Sprite::createWithSpriteFrameName("bt_main_1.png");
//    bottombluBar->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
//    bottombluBar->setScaleX(1.2f);
//    bottombluBar->setScaleY(0.5f);
//    panel->addChild(bottombluBar);

    auto menuitem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",CC_CALLBACK_1(Base::upgradeWeapon,this));
    menuitem->setScale(1.2f,0.5f);
    menuitem->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
    auto menu = Menu::create(menuitem,nullptr);
    menu->setPosition(Point::ZERO);
    panel->addChild(menu);
    
    auto menuitembuy = MenuItemImageLabel::createWithFrameName("btB_0.png","btB_1.png",CC_CALLBACK_1(Base::buyWeapon,this));
    menuitembuy->setScale(0.8f);
    menuitembuy->setPosition(Point(panelSize.width / 2+200,panelSize.height/2+50));
    auto menubuy = Menu::create(menuitembuy,nullptr);
    menubuy->setPosition(Point::ZERO);
    panel->addChild(menubuy);
    
    auto spar = Sprite::createWithSpriteFrameName("icon_gem.png");
    spar->setPosition(Point(200,panelSize.height * 0.25f));
    panel->addChild(spar);
    
    auto pos = Point(200,panelSize.height * 0.85f);
    
    {
        auto levelText = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize);
        levelText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        levelText->setPosition(pos);
        panel->addChild(levelText);
        
        pos.y = panelSize.height * 0.67f;
        auto attText = TextSprite::create(s_gameStrings.base->upgradeAtt,GameConfig::defaultFontName,fontSize);
        attText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        attText->setPosition(pos);
        panel->addChild(attText);
        
        pos.y = panelSize.height * 0.5f;
        auto duartionText = TextSprite::create(s_gameStrings.base->upgradeDuration,GameConfig::defaultFontName,fontSize);
        duartionText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        duartionText->setPosition(pos);
        panel->addChild(duartionText);
        
        pos.x = 400;
        pos.y = panelSize.height * 0.25f;
        auto leveUpText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize);
        leveUpText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpText->setPosition(pos-Point(40,0));
        panel->addChild(leveUpText);
        
        auto stone_icon = Sprite::createWithSpriteFrameName("icon_gem.png");
        stone_icon->setPosition(Point(menuitembuy->getContentSize().width/2-35,menuitembuy->getContentSize().height/2+20));
        menuitembuy->addChild(stone_icon);
        
        auto buy_text = TextSprite::create(s_gameStrings.base->upgradeBuy,GameConfig::defaultFontName,GameConfig::defaultFontSize);
        buy_text->setColor(Color3B::BLUE);
        buy_text->setPosition(Point(menuitembuy->getContentSize().width/2,menuitembuy->getContentSize().height/2-20));
        menuitembuy->addChild(buy_text);
    }
    
    {
        pos.x = 290;
        pos.y = panelSize.height * 0.85f;
        _weapon_level_label = Label::createWithTTF(Value(s_playerConfig.weaponslevel[t_index]+1).asString(),fontFile,fontSize);
        _weapon_level_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _weapon_level_label->setPosition(pos);
        _weapon_level_label->setTextColor(infoColor);
        panel->addChild(_weapon_level_label);
        
        pos.y = panelSize.height * 0.67f;
        _weapon_attack_label = Label::createWithTTF(Value(s_weaponConfigs[t_index][s_playerConfig.weaponslevel[t_index]].attack).asString(),fontFile,fontSize);
        _weapon_attack_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _weapon_attack_label->setPosition(pos);
        _weapon_attack_label->setTextColor(infoColor);
        panel->addChild(_weapon_attack_label);
        
        pos.y = panelSize.height * 0.5f;
        _weapon_duration_label = Label::createWithTTF(Value(s_weaponConfigs[t_index][s_playerConfig.weaponslevel[t_index]].duration).asString(),fontFile,fontSize);
        _weapon_duration_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        _weapon_duration_label->setPosition(pos);
        _weapon_duration_label->setTextColor(infoColor);
        panel->addChild(_weapon_duration_label);
        
        pos.y = panelSize.height * 0.25f;
        _weapon_upgradeforgem_label = Label::createWithTTF(Value(s_weaponConfigs[t_index][s_playerConfig.weaponslevel[t_index]].gemForUpgrade).asString(),fontFile,fontSize);
        _weapon_upgradeforgem_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _weapon_upgradeforgem_label->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
        _weapon_upgradeforgem_label->setTextColor(Color4B(255,255,0,255));
        panel->addChild(_weapon_upgradeforgem_label);
        
        auto buy_gem = TextSprite::create(Value(s_weaponConfigs[t_index][s_playerConfig.weaponslevel[t_index]].gemForUpgrade).asString().c_str(),fontFile,25);
        buy_gem->setColor(Color3B::YELLOW);
        buy_gem->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        buy_gem->setPosition(Point(menuitembuy->getContentSize().width/2-20,menuitembuy->getContentSize().height/2+20));
        menuitembuy->addChild(buy_gem);
    }
}


void Base::createFighterMiddleInfo(Node* panel)
{
    auto panelSize = panel->getContentSize();
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    auto infoColor = Color4B(153,217,234,255);
    
    
//    auto bottombluBar = Scale9Sprite::createWithSpriteFrameName("bt_main_1.png");
//    bottombluBar->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
//    bottombluBar->setScaleX(1.2f);
//    bottombluBar->setScaleY(0.5f);
//    panel->addChild(bottombluBar);
    
    auto menuitem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",CC_CALLBACK_1(Base::upgradeStoneMax,this));
    menuitem->setScale(1.2f,0.5f);
    menuitem->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
    auto menu = Menu::create(menuitem,nullptr);
    menu->setPosition(Point::ZERO);
    panel->addChild(menu);
    
    auto spar = Sprite::createWithSpriteFrameName("icon_gem.png");
    spar->setPosition(Point(200,panelSize.height * 0.25f));
    panel->addChild(spar);
    
    auto pos = Point(200,panelSize.height * 0.85f);
    
    {
        auto levelText = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize);
        levelText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        levelText->setPosition(pos);
        panel->addChild(levelText);
        
        pos.x = panelSize.width/2;
        pos.y = panelSize.height * 0.53f;
        auto sparCapacityText = TextSprite::create(s_gameStrings.base->sparCapacity,GameConfig::defaultFontName,fontSize);
        sparCapacityText->setPosition(pos);
        sparCapacityText->setColor(Color3B(169,169,169));
        panel->addChild(sparCapacityText);
        
        pos.x = 400;
        pos.y = panelSize.height * 0.25f;
        auto leveUpText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize);
        leveUpText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpText->setPosition(pos-Point(40,0));
        panel->addChild(leveUpText);
    }
    {
        pos.x = 290;
        pos.y = panelSize.height * 0.85f;
        auto level = Label::createWithTTF(Value(s_playerConfig.stonecapacitylevel+1).asString(),fontFile,fontSize);
        level->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        level->setPosition(pos);
        panel->addChild(level);
        
        pos.x = 350;
        pos.y = panelSize.height * 0.85f;
        auto cost = Label::createWithTTF(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel].initstone).asString(),fontFile,fontSize);
        cost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        cost->setPosition(pos);
        cost->setTextColor(infoColor);
        panel->addChild(cost);
        
        auto slash = Label::createWithTTF("/",fontFile,fontSize);
        slash->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        slash->setPosition(cost->getPosition()+Point(cost->getContentSize().width,0));
        panel->addChild(slash);
        
        auto total = Label::createWithTTF(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel].maxstone).asString(),fontFile,fontSize);
        total->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        total->setPosition(slash->getPosition()+Point(slash->getContentSize().width,0));
        panel->addChild(total);
        
        
        pos.y = panelSize.height * 0.25f;
        auto leveUpCost = Label::createWithTTF(Value(s_stoneCapacity[s_playerConfig.stonecapacitylevel].gemForUpgrade).asString(),fontFile,fontSize);
        leveUpCost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpCost->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
        leveUpCost->setTextColor(Color4B(255,255,0,255));
        panel->addChild(leveUpCost);
        
//        auto listener = EventListenerCustom::create(PlayerBar::eventPlayerSelect, [=](EventCustom* event)
//                                                    {
//                                                        level ->setString("10");
//                                            
//                                                        cost ->setString("1200");
//                                                        
//                                                        slash->setPosition(cost->getPosition()+Point(cost->getContentSize().width,0));
//                                                        
//                                                        total ->setString("1500");
//                                                        total->setPosition(slash->getPosition()+Point(slash->getContentSize().width,0));
//                                                        
//                                                        leveUpCost->setString("1500");
//                                                    });
//        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
}
void Base::createFighterTopInfo(Node* panel)
{
    auto panelSize = panel->getContentSize();
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    auto infoColor = Color4B(153,217,234,255);
    
    
    //
//    auto bottombluBar = Scale9Sprite::createWithSpriteFrameName("bt_main_1.png");
//    bottombluBar->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
//    bottombluBar->setScaleX(1.2f);
//    bottombluBar->setScaleY(0.5f);
//    panel->addChild(bottombluBar);
    
    auto menuitem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",CC_CALLBACK_1(Base::upgradeStoneSpeed,this));
    menuitem->setScale(1.2f,0.5f);
    menuitem->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
    auto menu = Menu::create(menuitem,nullptr);
    menu->setPosition(Point::ZERO);
    panel->addChild(menu);
    
    
    auto spar = Sprite::createWithSpriteFrameName("icon_gem.png");
    spar->setPosition(Point(200,panelSize.height * 0.25f));
    panel->addChild(spar);
    
    auto pos = Point(200,panelSize.height * 0.85f);
    
    {
        auto levelText = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize);
        levelText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        levelText->setPosition(pos);
        panel->addChild(levelText);
        
        pos.x = panelSize.width/2;
        pos.y = panelSize.height * 0.53f;
        auto sparRecoverRateText = TextSprite::create(s_gameStrings.base->sparRecoverRate,GameConfig::defaultFontName,fontSize);
        sparRecoverRateText->setPosition(pos);
        sparRecoverRateText->setColor(Color3B(169,169,169));
        panel->addChild(sparRecoverRateText);
        
        pos.x = 400;
        pos.y = panelSize.height * 0.25f;
        auto leveUpText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize);
        leveUpText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpText->setPosition(pos-Point(40,0));
        panel->addChild(leveUpText);
    }
    {
        pos.x = 290;
        pos.y = panelSize.height * 0.85f;
        auto level = Label::createWithTTF(Value(s_playerConfig.stonespeedlevel+1).asString(),fontFile,fontSize);
        level->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        level->setPosition(pos);
        panel->addChild(level);
        
        pos.x = 350;
        pos.y = panelSize.height * 0.85f;
        auto plus = Label::createWithTTF("+",fontFile,fontSize);
        plus->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        plus->setPosition(pos);
        plus->setTextColor(infoColor);
        panel->addChild(plus);
        
        auto cost = Label::createWithTTF(Value(s_stoneSpeed[s_playerConfig.stonespeedlevel].speed).asString(),fontFile,fontSize);
        cost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        cost->setPosition(plus->getPosition()+Point(plus->getContentSize().width,0));
        cost->setTextColor(infoColor);
        panel->addChild(cost);
        
        auto slash = Label::createWithTTF("/",fontFile,fontSize);
        slash->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        slash->setPosition(cost->getPosition()+Point(cost->getContentSize().width,0));
        panel->addChild(slash);
        
        
        auto total = Label::createWithTTF(s_gameStrings.base->second,fontFile,fontSize);
        total->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        total->setPosition(slash->getPosition()+Point(slash->getContentSize().width,0));
        panel->addChild(total);
        
        
        pos.y = panelSize.height * 0.25f;
        auto leveUpCost = Label::createWithTTF(Value(s_stoneSpeed[s_playerConfig.stonespeedlevel].gemForUpgrade).asString(),fontFile,fontSize);
        leveUpCost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpCost->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
        leveUpCost->setTextColor(Color4B(255,255,0,255));
        panel->addChild(leveUpCost);
        
//        auto listener = EventListenerCustom::create(PlayerBar::eventPlayerSelect, [=](EventCustom* event)
////        {
////            _flight_level_label ->setString(const std::string &text);
////            _flight_life_label ->setString(<#const std::string &text#>);
////            _flight_attack_label ->setString(<#const std::string &text#>);
////            _flight_speed_label ->setString(<#const std::string &text#>);
////            _flight_defend_label ->setString(<#const std::string &text#>);
////            _flight_range_label ->setString(<#const std::string &text#>);
////            _flight_upgrade_need_money_label ->setString(<#const std::string &text#>);
////        });
//                                                    {
//                                                        level ->setString("10");
//                                                        
//                                                        cost ->setString("1200");
//                                                        cost->setPosition(plus->getPosition()+Point(plus->getContentSize().width,0));
//                                                        
//                                                        slash->setPosition(cost->getPosition()+Point(cost->getContentSize().width,0));
//                                                    
//                                                        total->setPosition(slash->getPosition()+Point(slash->getContentSize().width,0));
//                                                        
//                                                        leveUpCost->setString("1500");
//                                                    });
//        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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

    auto medalItem = MenuItemImageLabel::createWithFrameName("btA_0.png","btA_1.png",
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
}

void Base::menuCallbackMedal(Ref *sender)
{
    log("menuCallbackMeadl");
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
    auto settingLayer = MenuSettings::create(GameInterface::Base);
    addChild(settingLayer,4);
}

void Base::menuCallbackBattle(Ref *sender)
{
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

}

void Base::showUpgradeUI(BasePanel basePanel)
{
    auto layer = UpgradeUILayer::create(basePanel, _curSeletedIndex);
    this->addChild(layer);
}

void Base::updatePanelStatus()
{
    
}
