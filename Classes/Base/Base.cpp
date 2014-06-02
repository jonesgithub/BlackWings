#include "Base.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "LoadResourceLayer.h"
#include "MenuSettings.h"
#include "PlayerBar.h"
#include "StageSelect.h"
#include "Medal.h"
#include "BuyGemLayer.h"

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
        loadLayer->addImage("door_l.png");
        loadLayer->addImage("door_r.png");
        this->addChild(loadLayer);
        loadLayer->startLoad();

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

    _playerBag = PlayerBar::create();
    this->addChild(_playerBag);

    createTopPanel();

    auto listenerStageSelect = EventListenerCustom::create(StageSelect::eventBack, [=](EventCustom* event){
        _topPanel->runAction(MoveBy::create(0.2f,Point(0,-200)));
        _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,s_visibleRect.visibleHeight)));
        _playerBag->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,136)),nullptr ));
    });
    
    auto listenerMedal = EventListenerCustom::create(Medal::eventBack, [=](EventCustom* event){
        _topPanel->runAction(MoveBy::create(0.2f,Point(0,-200)));
        _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,s_visibleRect.visibleHeight)));
        _playerBag->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,136)),nullptr ));
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStageSelect, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMedal, this);
}

void Base::createUpgrade()
{
    _upgradePanel = Node::create();
    this->addChild(_upgradePanel);

    int baseHeight = 50;
    int padding = 30;

    auto boxPos = Point(s_visibleRect.center.x,s_visibleRect.center.y - baseHeight * 5);

    auto upgradeFighter = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
    upgradeFighter->setContentSize(Size(s_visibleRect.visibleWidth - 50,baseHeight * 4.5));
    upgradeFighter->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    upgradeFighter->setPosition(boxPos);
    _upgradePanel->addChild(upgradeFighter);
    createFighterBottomInfo(upgradeFighter);

    boxPos.y += baseHeight * 4.5 + padding;
    auto sparCapacitySize = Size(s_visibleRect.visibleWidth - 60,baseHeight * 3);
    auto upgradeSparCapacity = Scale9Sprite::createWithSpriteFrameName("upgrade_box.png");
    upgradeSparCapacity->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    upgradeSparCapacity->setContentSize(sparCapacitySize);
    upgradeSparCapacity->setPosition(boxPos);
    _upgradePanel->addChild(upgradeSparCapacity);
    auto bg1 = Scale9Sprite::createWithSpriteFrameName("upgrade_box_bg.png");
    bg1->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bg1->setContentSize(Size(sparCapacitySize.width * 5 /7,baseHeight));
    bg1->setPosition(Point(sparCapacitySize.width /2,sparCapacitySize.height - 2));
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
    bg2->setContentSize(Size(sparRecoverySize.width * 5 /7,baseHeight));
    bg2->setPosition(Point(sparRecoverySize.width /2,sparRecoverySize.height - 2));
    upgradeSparRecovery->addChild(bg2);
    createFighterTopInfo(upgradeSparRecovery);
}

void Base::createFighterBottomInfo(Node* panel)
{
    auto panelSize = panel->getContentSize();
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    auto infoColor = Color4B(153,217,234,255);
    
    auto fighterBox = Sprite::createWithSpriteFrameName("upgrade_box_mini.png");
    //fighterBox->setContentSize(Size(panelSize.width / 6,panelSize.height * 0.5f));
    fighterBox->setScale(0.7f);
    fighterBox->setPosition(Point(panelSize.width / 6,panelSize.height * 0.625f));
    panel->addChild(fighterBox);
    
    auto bottombluBar = Scale9Sprite::createWithSpriteFrameName("bt_main_1.png");
    bottombluBar->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
    bottombluBar->setScaleX(1.2f);
    bottombluBar->setScaleY(0.5f);
    panel->addChild(bottombluBar);
    
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
        auto defText = TextSprite::create(s_gameStrings.base->upgradeDef,GameConfig::defaultFontName,fontSize);
        defText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        defText->setPosition(pos);
        panel->addChild(defText);

        pos.x = 400;
        pos.y = panelSize.height * 0.85f;
        auto lifeText = TextSprite::create(s_gameStrings.base->upgradeLife,GameConfig::defaultFontName,fontSize);
        lifeText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        lifeText->setPosition(pos);
        panel->addChild(lifeText);

        pos.y = panelSize.height * 0.67f;
        auto spdText = TextSprite::create(s_gameStrings.base->upgradeSpd,GameConfig::defaultFontName,fontSize);
        spdText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        spdText->setPosition(pos);
        panel->addChild(spdText);

        pos.y = panelSize.height * 0.5f;
        auto rangeText = TextSprite::create(s_gameStrings.base->upgradeRange,GameConfig::defaultFontName,fontSize);
        rangeText->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        rangeText->setPosition(pos);
        panel->addChild(rangeText);
        
        pos.y = panelSize.height * 0.25f;
        auto leveUpText = TextSprite::create(s_gameStrings.base->upgrade,GameConfig::defaultFontName,fontSize);
        leveUpText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpText->setPosition(pos-Point(40,0));
        panel->addChild(leveUpText);
    }

    {
        pos.x = 290;
        pos.y = panelSize.height * 0.85f;
        auto level = Label::createWithTTF("0",fontFile,fontSize);
        level->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        level->setPosition(pos);
        level->setTextColor(infoColor);
        panel->addChild(level);
        
        pos.y = panelSize.height * 0.67f;
        auto att = Label::createWithTTF("0",fontFile,fontSize);
        att->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        att->setPosition(pos);
        att->setTextColor(infoColor);
        panel->addChild(att);
        
        pos.y = panelSize.height * 0.5f;
        auto def = Label::createWithTTF("0",fontFile,fontSize);
        def->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        def->setPosition(pos);
        def->setTextColor(infoColor);
        panel->addChild(def);
        
        pos.y = panelSize.height * 0.25f;
        auto leveUpCost = Label::createWithTTF("13000",fontFile,fontSize);
        leveUpCost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpCost->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
        leveUpCost->setTextColor(Color4B(255,255,0,255));
        panel->addChild(leveUpCost);
        
        pos.x = 490;
        pos.y = panelSize.height * 0.85f;
        auto life = Label::createWithTTF("0",fontFile,fontSize);
        life->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        life->setPosition(pos);
        life->setTextColor(infoColor);
        panel->addChild(life);
        
        pos.y = panelSize.height * 0.67f;
        auto spd = Label::createWithTTF("0",fontFile,fontSize);
        spd->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        spd->setPosition(pos);
        spd->setTextColor(infoColor);
        panel->addChild(spd);
        
        pos.y = panelSize.height * 0.5f;
        auto range = Label::createWithTTF("0",fontFile,fontSize);
        range->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        range->setPosition(pos);
        range->setTextColor(infoColor);
        panel->addChild(range);
   
   
        auto listener = EventListenerCustom::create(PlayerBar::eventPlayerSelect, [=](EventCustom* event)
       {
            level ->setString("10");
            att ->setString("10");
            def ->setString("10");
            life ->setString("10");
            spd ->setString("10");
            range ->setString("10");
            leveUpCost->setString("3100");
       });
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
}
void Base::createFighterMiddleInfo(Node* panel)
{
    auto panelSize = panel->getContentSize();
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    auto infoColor = Color4B(153,217,234,255);
    
    
    auto bottombluBar = Scale9Sprite::createWithSpriteFrameName("bt_main_1.png");
    bottombluBar->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
    bottombluBar->setScaleX(1.2f);
    bottombluBar->setScaleY(0.5f);
    panel->addChild(bottombluBar);
    
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
        auto level = Label::createWithTTF("0",fontFile,fontSize);
        level->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        level->setPosition(pos);
        panel->addChild(level);
        
        pos.x = 350;
        pos.y = panelSize.height * 0.85f;
        auto cost = Label::createWithTTF("0",fontFile,fontSize);
        cost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        cost->setPosition(pos);
        cost->setTextColor(infoColor);
        panel->addChild(cost);
        
        auto slash = Label::createWithTTF("/",fontFile,fontSize);
        slash->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        slash->setPosition(cost->getPosition()+Point(cost->getContentSize().width,0));
        panel->addChild(slash);
        
        auto total = Label::createWithTTF("0",fontFile,fontSize);
        total->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        total->setPosition(slash->getPosition()+Point(slash->getContentSize().width,0));
        panel->addChild(total);
        
        
        pos.y = panelSize.height * 0.25f;
        auto leveUpCost = Label::createWithTTF("13000",fontFile,fontSize);
        leveUpCost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpCost->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
        leveUpCost->setTextColor(Color4B(255,255,0,255));
        panel->addChild(leveUpCost);
        
        auto listener = EventListenerCustom::create(PlayerBar::eventPlayerSelect, [=](EventCustom* event)
                                                    {
                                                        level ->setString("10");
                                            
                                                        cost ->setString("1200");
                                                        
                                                        slash->setPosition(cost->getPosition()+Point(cost->getContentSize().width,0));
                                                        
                                                        total ->setString("1500");
                                                        total->setPosition(slash->getPosition()+Point(slash->getContentSize().width,0));
                                                        
                                                        leveUpCost->setString("1500");
                                                    });
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
}
void Base::createFighterTopInfo(Node* panel)
{
    auto panelSize = panel->getContentSize();
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    auto infoColor = Color4B(153,217,234,255);
    
    
    auto bottombluBar = Scale9Sprite::createWithSpriteFrameName("bt_main_1.png");
    bottombluBar->setPosition(Point(panelSize.width / 2,panelSize.height * 0.25f));
    bottombluBar->setScaleX(1.2f);
    bottombluBar->setScaleY(0.5f);
    panel->addChild(bottombluBar);
    
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
        auto level = Label::createWithTTF("0",fontFile,fontSize);
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
        
        auto cost = Label::createWithTTF("0",fontFile,fontSize);
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
        auto leveUpCost = Label::createWithTTF("13000",fontFile,fontSize);
        leveUpCost->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        leveUpCost->setPosition(spar->getPosition()+Point(spar->getContentSize().width/2,0));
        leveUpCost->setTextColor(Color4B(255,255,0,255));
        panel->addChild(leveUpCost);
        
        auto listener = EventListenerCustom::create(PlayerBar::eventPlayerSelect, [=](EventCustom* event)
//        {
//            _flight_level_label ->setString(<#const std::string &text#>);
//            _flight_life_label ->setString(<#const std::string &text#>);
//            _flight_attack_label ->setString(<#const std::string &text#>);
//            _flight_speed_label ->setString(<#const std::string &text#>);
//            _flight_defend_label ->setString(<#const std::string &text#>);
//            _flight_range_label ->setString(<#const std::string &text#>);
//            _flight_upgrade_need_money_label ->setString(<#const std::string &text#>);
//        });
                                                    {
                                                        level ->setString("10");
                                                        
                                                        cost ->setString("1200");
                                                        cost->setPosition(plus->getPosition()+Point(plus->getContentSize().width,0));
                                                        
                                                        slash->setPosition(cost->getPosition()+Point(cost->getContentSize().width,0));
                                                    
                                                        total->setPosition(slash->getPosition()+Point(slash->getContentSize().width,0));
                                                        
                                                        leveUpCost->setString("1500");
                                                    });
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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
    
    //add get more gem
    auto itemBuyGem = MenuItemImageLabel::createWithFrameName("bt_buy_gem_0.png","bt_buy_gem_1.png",
                                                              CC_CALLBACK_1(Base::menuCallbackBuyGem,this), "获取更多");
    itemBuyGem->setPosition(300, 800);

    auto menu = Menu::create( medalItem, settingItem, battleItem, itemBuyGem,nullptr);
    menu->setPosition(Point::ZERO);
    _topPanel->addChild(menu);
}

void Base::menuCallbackMedal(Ref *sender)
{
    log("menuCallbackMeadl");
    _topPanel->runAction(MoveBy::create(0.2f,Point(0,200)));
    _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,-s_visibleRect.visibleHeight)));
    _playerBag->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,-150)),
                                           MoveBy::create(0.05f,Point(0,14)),nullptr ));
    auto medalLayer = Medal::create();
    addChild(medalLayer);
}

void Base::menuCallbackSetting(Ref *sender)
{
    auto settingLayer = MenuSettings::create(GameInterface::Base);
    addChild(settingLayer);
}

void Base::menuCallbackBattle(Ref *sender)
{
    _topPanel->runAction(MoveBy::create(0.2f,Point(0,200)));
    _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,-s_visibleRect.visibleHeight)));
    _playerBag->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,-150)),
        MoveBy::create(0.05f,Point(0,14)),nullptr ));
    
    auto stageSelect = StageSelect::create();
    this->addChild(stageSelect);
}

void Base::menuCallbackUpgrade(Ref *sender)
{
    
}

void Base::menuCallbackBuyGem(Ref *sender)
{
    CCLOG("will shop gem");
    auto gemLy = BuyGemLayer::create();
    addChild(gemLy);
    gemLy->setPosition(s_visibleRect.center.x, s_visibleRect.center.y);
}
