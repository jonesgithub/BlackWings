#include "PlayerMenuItem.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "TextSprite.h"
#include "PlayerBar.h"
#include "Configuration.h"

USING_NS_CC;
USING_NS_CC_EXT;

PlayerMenuItem* PlayerMenuItem::create(Type type,int index)
{
    auto ret = new PlayerMenuItem();

    if (ret && ret->init(type,index))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

PlayerMenuItem::PlayerMenuItem()
: _label(nullptr),
flight_avaliable(nullptr),
weapon_avaliable(nullptr),
_isInProgress(false),
_isLocked(true)
{
    
}

bool PlayerMenuItem::init(Type playerType,int index)
{
    bool ret = false;


    _type = playerType;
    _index = index;
    
    Node *normalSprite = nullptr;
    Node *selectedSprite = nullptr;
    Node *disabledSprite = nullptr;

    if (playerType == Type::Fighter)
    {
        typeIndex = index;
        normalSprite = Sprite::createWithSpriteFrameName("item_0.png");
        selectedSprite = Sprite::createWithSpriteFrameName("item_1.png");
        //disabledSprite = Sprite::createWithSpriteFrameName("item_4.png");
        ret = initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, nullptr);
        if (ret)
        {
            char iconFileName[25];
            if (s_playerConfig.fighterslocked[index])
            {
                sprintf(iconFileName,"icon_lock.png");
                this->setEnabled(false);
                _isLocked = true;
            }
            else
            {
                sprintf(iconFileName,"plain_%d_lv_%d.png",index + 1,s_playerConfig.fighterslevel[index] + 1);
                std::string fontFile = "DS-Digital.ttf";
                int fontSize = 25;
                stoneformake_text = Label::createWithTTF(Value(s_plainConfigs[index][s_playerConfig.fighterslevel[index]].sparForMake).asString(),fontFile,fontSize);
                stoneformake_text->setPosition(Point(44,28));
                Node::addChild(stoneformake_text,3);
                _isLocked = false;
            }
            fighter = Sprite::createWithSpriteFrameName(iconFileName);
            fighter->setPosition(Point(44,76));
            Node::addChild(fighter,1,0);
        }
    } 
    else
    {
        _isLocked = false;
        
        typeIndex = FIGHTER_MAX + index;
        auto interval = (s_visibleRect.visibleWidth - 40 - 65) / WEAPON_MAX;
        auto size = Size(interval - 30,131);
        size.width+=10;
        normalSprite = Scale9Sprite::createWithSpriteFrameName("item_0.png");
        normalSprite->setContentSize(size);
        selectedSprite = Scale9Sprite::createWithSpriteFrameName("item_1.png");
        selectedSprite->setContentSize(size);

        ret = initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, nullptr);

        if (ret)
        {
            char iconFileName[25];
            sprintf(iconFileName,"bomb_%d_%d.png",index + 1,s_playerConfig.weaponslevel[index] + 1);
            weapon = Sprite::createWithSpriteFrameName(iconFileName);
            weapon->setPosition(Point(size.width/2,76));
            weapon->setRotation(90);
            Node::addChild(weapon,1,0);
            
            count_text = TextSprite::create(s_gameStrings.base->weaponQuantity,GameConfig::defaultFontName,20);
            count_text->setPosition(Point(45,25));
            Node::addChild(count_text,1);
            
            std::string fontFile = "DS-Digital.ttf";
            int fontSize = 25;
            
            auto slash = Label::createWithTTF("/",fontFile,fontSize);
            slash->setAnchorPoint(Point::ANCHOR_MIDDLE);
            slash->setPosition(Point(size.width/2+18,26));
            Node::addChild(slash,1);
            
            int weapon_countNum = s_playerConfig.weaponCount[index];
            int weapon_maxNum = s_weaponConfigs[index][s_playerConfig.weaponslevel[index]].capacity;
            
            countNum = Label::createWithTTF(Value(weapon_countNum).asString(),fontFile,fontSize);
            countNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
            countNum->setPosition(Point(slash->getPositionX()-10,slash->getPositionY()));
            Node::addChild(countNum);
            
            stoneTatalNum = Label::createWithTTF(Value(weapon_maxNum).asString(),fontFile,fontSize);
            stoneTatalNum->setColor(Color3B::GRAY);
            stoneTatalNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            stoneTatalNum->setPosition(Point(slash->getPositionX()+10,slash->getPositionY()));
            Node::addChild(stoneTatalNum);

        }
    }

    auto activeCDListener = EventListenerCustom::create(GameConfig::eventactiveCD,
                                                       CC_CALLBACK_1(PlayerMenuItem::activeCD_callback,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(activeCDListener, this);
    
    auto unselectedallListener = EventListenerCustom::create(GameConfig::eventunseletedall,
                                                        CC_CALLBACK_1(PlayerMenuItem::unselectedall,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(unselectedallListener, this);
    
    auto updateflightDataListener = EventListenerCustom::create(GameConfig::eventUpdateMenuItemFlightData,
                                                          CC_CALLBACK_1(PlayerMenuItem::updateFlightData,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(updateflightDataListener, this);
    
    auto updateWeaponDataListener = EventListenerCustom::create(GameConfig::eventUpdateMenuItemWeaponData,
                                                                CC_CALLBACK_1(PlayerMenuItem::updateWeaponData,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(updateWeaponDataListener, this);
    
    auto flightAvaliableListener = EventListenerCustom::create(GameConfig::eventFlightAvaliable,
                                                                CC_CALLBACK_1(PlayerMenuItem::checkFlightAvaliable,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(flightAvaliableListener, this);
    
    auto weaponAvaliableListener = EventListenerCustom::create(GameConfig::eventWeaponAvaliable,
                                                                CC_CALLBACK_1(PlayerMenuItem::checkWeaponAvaliable,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(weaponAvaliableListener, this);
    
    auto languagelistener = EventListenerCustom::create(GameConfig::eventLanguageChange, [=](EventCustom* event)
                                                        {
                                                            if (playerType == Type::Weapon)
                                                                count_text->setText(s_gameStrings.base->weaponQuantity);
                                                        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(languagelistener, this);
    
    return ret;
}

void PlayerMenuItem::activate()
{
    MenuItemImage::activate();
    //
    if(s_gameConfig.isInBattle)
    {
        if (_type == Type::Fighter)
        {
            if(s_battleground->_battledata.curStone >= s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].sparForMake)
            {
                s_battleground->reduce_stone(s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].sparForMake);
                
                setEnabled(false);
                auto cd_sprite = Sprite::createWithSpriteFrameName("item_4.png");
                auto offset = Point(44,65);
                auto cdtime = s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].cd;
                cd_sprite->setOpacity(200);
                auto cd_progress = ProgressTimer::create(cd_sprite);
                cd_progress->setType(ProgressTimer::Type::RADIAL);
                cd_progress->setReverseProgress(true);
                cd_progress->setMidpoint(Point(0.5f, 0.5f));
                cd_progress->setBarChangeRate(Point(0, 1));
                cd_progress->setPosition(offset);
                Node::addChild(cd_progress,1,99);
                _isInProgress = true;
                cd_progress->runAction(Sequence::create(ProgressFromTo::create(cdtime, 100, 0),
                                                        RemoveSelf::create(),
                                                        CallFunc::create([&]()
                                                                         {
                                                                             _isInProgress = false;
                                                                             setEnabled(true);
                                                                         }),
                                                        nullptr));
            }
        }
    }
    else
    {
        _eventDispatcher->dispatchCustomEvent(GameConfig::eventunseletedall);
        selected();
    }
    _eventDispatcher->dispatchCustomEvent(PlayerBar::eventPlayerSelect,(void*)typeIndex);
}

void PlayerMenuItem::activeCD_callback(EventCustom* event)
{
    if (s_gameConfig.isInBattle) {
        if (_type == Type::Weapon) {
            int t_index = (uintptr_t)event->getUserData();
            if(t_index == _index)
            {
                setEnabled(false);
                auto cd_sprite = Sprite::createWithSpriteFrameName("itemB_4.png");
                auto offset = Point(80,65);
                auto cdtime = s_weaponConfigs[_index][s_playerConfig.weaponslevel[_index]].cd;
                cd_sprite->setOpacity(200);
                auto cd_progress = ProgressTimer::create(cd_sprite);
                cd_progress->setType(ProgressTimer::Type::RADIAL);
                cd_progress->setReverseProgress(true);
                cd_progress->setMidpoint(Point(0.5f, 0.5f));
                cd_progress->setBarChangeRate(Point(0, 1));
                cd_progress->setPosition(offset);
                Node::addChild(cd_progress,1,0);
                _isInProgress = true;
                cd_progress->runAction(Sequence::create(ProgressFromTo::create(cdtime, 100, 0),
                                                        RemoveSelf::create(),
                                                        CallFunc::create([&]()
                                                                         {
                                                                             _isInProgress = false;
                                                                             setEnabled(true);
                                                                         }),
                                                        nullptr));            }
        }
    }
    
}

void PlayerMenuItem::unselectedall(EventCustom* event)
{
    unselected();
}

void PlayerMenuItem::updateFlightData(EventCustom* event)
{
    int index = (uintptr_t)event->getUserData();
    if(!s_gameConfig.isInBattle && _index == index)
    {
        if (_type == Type::Fighter)
        {
            stoneformake_text->setString(Value(s_plainConfigs[index][s_playerConfig.fighterslevel[index]].sparForMake).asString().c_str());
            
            char iconFileName[30];
            sprintf(iconFileName,"plain_%d_lv_%d.png",index + 1,s_playerConfig.fighterslevel[index] + 1);
            fighter->setSpriteFrame(iconFileName);
        }

    }
}

void PlayerMenuItem::updateWeaponData(EventCustom* event)
{
    int index = (uintptr_t)event->getUserData();
    //if(!s_gameConfig.isInBattle)
    {
        if (_type == Type::Weapon && _index == index)
        {
            countNum->setString(Value(s_playerConfig.weaponCount[index]).asString());
            stoneTatalNum->setString(Value(s_weaponConfigs[index][s_playerConfig.weaponslevel[index]].capacity).asString());
            char iconFileName[25];
            sprintf(iconFileName,"bomb_%d_%d.png",index + 1,s_playerConfig.weaponslevel[index] + 1);
            weapon->setSpriteFrame(iconFileName);
        }
    }
}

void PlayerMenuItem::checkFlightAvaliable(EventCustom* event)
{
    if(s_gameConfig.isInBattle && _type == Type::Fighter && !_isLocked && !_isInProgress)
    {
        int have = (uintptr_t)event->getUserData();
        int cost = s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].sparForMake;
        if (have<cost) {
            if (!flight_avaliable)
            {
                setEnabled(false);
                flight_avaliable = Sprite::createWithSpriteFrameName("item_4.png");
                flight_avaliable->setOpacity(200);
                flight_avaliable->setPosition(Point(44,65));
                Node::addChild(flight_avaliable,88);
            }
        }
        else
        {
            if(flight_avaliable)
            {
                setEnabled(true);
                Node::removeChild(flight_avaliable);
                flight_avaliable = nullptr;
            }
        }
    }
}

void PlayerMenuItem::checkWeaponAvaliable(EventCustom* event)
{
    if(s_gameConfig.isInBattle && _type == Type::Weapon && !_isLocked && !_isInProgress)
    {
        int count = s_playerConfig.weaponCount[_index];
        if (count<=0) {
            if (!weapon_avaliable)
            {
                setEnabled(false);
                weapon_avaliable = Sprite::createWithSpriteFrameName("itemB_4.png");
                weapon_avaliable->setOpacity(200);
                weapon_avaliable->setPosition(Point(80,65));
                Node::addChild(weapon_avaliable,88);
            }
        }
        else
        {
            if(weapon_avaliable)
            {
                setEnabled(true);
                removeChild(weapon_avaliable);
                weapon_avaliable = nullptr;
            }
        }
    }}