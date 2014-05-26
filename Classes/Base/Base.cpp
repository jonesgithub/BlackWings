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

    GSBaseInit((GameLanguage)s_gameConfig.language);

    createUpgrade();

    _playerBag = PlayerBar::create();
    this->addChild(_playerBag);

    createTopPanel();

    auto listener = EventListenerCustom::create(StageSelect::eventBack, [=](EventCustom* event){
        _topPanel->runAction(MoveBy::create(0.2f,Point(0,-200)));
        _upgradePanel->runAction(MoveBy::create(0.2f,Point(0,s_visibleRect.visibleHeight)));
        _playerBag->runAction(Sequence::create( MoveBy::create(0.15f,Point(0,136)),nullptr ));
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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
    createFighterInfo(upgradeFighter);

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
}

void Base::createFighterInfo(Node* panel)
{
    auto panelSize = panel->getContentSize();
    std::string fontFile = "fonts/arial.ttf";
    int fontSize = 20;
    auto infoColor = Color4B(153,217,234,255);
    
    auto fighterBox = Sprite::createWithSpriteFrameName("upgrade_box_mini.png");
    //fighterBox->setContentSize(Size(panelSize.width / 6,panelSize.height * 0.5f));
    fighterBox->setScale(0.7f);
    fighterBox->setPosition(Point(panelSize.width / 6,panelSize.height * 0.625f));
    panel->addChild(fighterBox);

    auto pos = Point(200,panelSize.height * 0.85f);

    {
        auto levelText = TextSprite::create(s_gameStrings.base->upgradeLevel,GameConfig::defaultFontName,fontSize);
        levelText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        levelText->setPosition(pos);
        panel->addChild(levelText);

        pos.y = panelSize.height * 0.6f;
        auto attText = TextSprite::create(s_gameStrings.base->upgradeAtt,GameConfig::defaultFontName,fontSize);
        attText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        attText->setPosition(pos);
        panel->addChild(attText);

        pos.y = panelSize.height * 0.35f;
        auto defText = TextSprite::create(s_gameStrings.base->upgradeDef,GameConfig::defaultFontName,fontSize);
        defText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        defText->setPosition(pos);
        panel->addChild(defText);

        pos.x = 400;
        pos.y = panelSize.height * 0.85f;
        auto lifeText = TextSprite::create(s_gameStrings.base->upgradeLife,GameConfig::defaultFontName,fontSize);
        lifeText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        lifeText->setPosition(pos);
        panel->addChild(lifeText);

        pos.y = panelSize.height * 0.6f;
        auto spdText = TextSprite::create(s_gameStrings.base->upgradeSpd,GameConfig::defaultFontName,fontSize);
        spdText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        spdText->setPosition(pos);
        panel->addChild(spdText);

        pos.y = panelSize.height * 0.35f;
        auto rangeText = TextSprite::create(s_gameStrings.base->upgradeRange,GameConfig::defaultFontName,fontSize);
        rangeText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        rangeText->setPosition(pos);
        panel->addChild(rangeText);
    }
    
    
    
    {
        pos.x = 290;
        pos.y = panelSize.height * 0.85f;
        _flight_level_label = Label::createWithTTF("0",fontFile,fontSize);
        _flight_level_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _flight_level_label->setPosition(pos);
        _flight_level_label->setTextColor(infoColor);
        panel->addChild(_flight_level_label);

        pos.y = panelSize.height * 0.6f;
        _flight_attack_label = Label::createWithTTF("0",fontFile,fontSize);
        _flight_attack_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _flight_attack_label->setPosition(pos);
        _flight_attack_label->setTextColor(infoColor);
        panel->addChild(_flight_attack_label);

        pos.y = panelSize.height * 0.35f;
        _flight_defend_label = Label::createWithTTF("0",fontFile,fontSize);
        _flight_defend_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _flight_defend_label->setPosition(pos);
        _flight_defend_label->setTextColor(infoColor);
        panel->addChild(_flight_defend_label);
    
        pos.x = 490;
        pos.y = panelSize.height * 0.85f;
        _flight_life_label = Label::createWithTTF("0",fontFile,fontSize);
        _flight_life_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _flight_life_label->setPosition(pos);
        _flight_life_label->setTextColor(infoColor);
        panel->addChild(_flight_life_label);

        pos.y = panelSize.height * 0.6f;
        _flight_speed_label = Label::createWithTTF("0",fontFile,fontSize);
        _flight_speed_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _flight_speed_label->setPosition(pos);
        _flight_speed_label->setTextColor(infoColor);
        panel->addChild(_flight_speed_label);

        pos.y = panelSize.height * 0.35f;
        _flight_range_label = Label::createWithTTF("0",fontFile,fontSize);
        _flight_range_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _flight_range_label->setPosition(pos);
        _flight_range_label->setTextColor(infoColor);
        panel->addChild(_flight_range_label);
        
        
        auto listener = EventListenerCustom::create(PlayerBar::eventPlayerSelect, [=](EventCustom* event)
        {
            /*
            _flight_level_label ->setString(<#const std::string &text#>);
            _flight_life_label ->setString(<#const std::string &text#>);
            _flight_attack_label ->setString(<#const std::string &text#>);
            _flight_speed_label ->setString(<#const std::string &text#>);
            _flight_defend_label ->setString(<#const std::string &text#>);
            _flight_range_label ->setString(<#const std::string &text#>);
            _flight_upgrade_need_money_label ->setString(<#const std::string &text#>);
             */
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
        CC_CALLBACK_1(Base::menuCallbackMeadl,this),s_gameStrings.base->topBarMedal);
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

void Base::menuCallbackMeadl(Ref *sender)
{
    log("menuCallbackMeadl");
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
