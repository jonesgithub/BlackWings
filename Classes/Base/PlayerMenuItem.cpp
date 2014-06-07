#include "PlayerMenuItem.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "TextSprite.h"
#include "PlayerBar.h"

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
: _label(nullptr)
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
            }
            else
            {
                sprintf(iconFileName,"plain_%d_lv_%d.png",index + 1,s_playerConfig.fighterslevel[index] + 1);
            }
            auto fighter = Sprite::createWithSpriteFrameName(iconFileName);
            fighter->setPosition(Point(44,76));
            Node::addChild(fighter,1,0);
        }
    } 
    else
    {
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
            auto weapon = Sprite::createWithSpriteFrameName(iconFileName);
            weapon->setPosition(Point(size.width/2,76));
            weapon->setRotation(90);
            Node::addChild(weapon,1,0);
            //disabledSprite = Sprite::createWithSpriteFrameName("item_4.png");
        }
    }

    auto activeCDListener = EventListenerCustom::create(GameConfig::eventactiveCD,
                                                       CC_CALLBACK_1(PlayerMenuItem::activeCD_callback,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(activeCDListener, this);
    
    auto unselectedallListener = EventListenerCustom::create(GameConfig::eventunseletedall,
                                                        CC_CALLBACK_1(PlayerMenuItem::unselectedall,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(unselectedallListener, this);
    
    return ret;
}

void PlayerMenuItem::activate()
{
    MenuItemImage::activate();
    //
    if(s_gameConfig.isInBattle)
    {
        if (_type == Type::Fighter) {
            setEnabled(false);
            auto cd_sprite = Sprite::createWithSpriteFrameName("item_4.png");
            auto offset = Point(44,65);
            auto cdtime = s_plainConfigs[_index][s_playerConfig.fighterslevel[_index]].cd;
            cd_sprite->setOpacity(200);
            auto cd_progress = ProgressTimer::create(cd_sprite);
            cd_progress->setType(ProgressTimer::Type::RADIAL);
            cd_progress->setMidpoint(Point(0.5f, 0.5f));
            cd_progress->setBarChangeRate(Point(0, 1));
            cd_progress->setPosition(offset);
            Node::addChild(cd_progress,1,0);
            cd_progress->runAction(Sequence::create(ProgressTo::create(cdtime, 100),
                                                    RemoveSelf::create(),
                                                    CallFunc::create([&]()
                                                                     {
                                                                         setEnabled(true);
                                                                     }),
                                                    nullptr));
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
                cd_progress->setMidpoint(Point(0.5f, 0.5f));
                cd_progress->setBarChangeRate(Point(0, 1));
                cd_progress->setPosition(offset);
                Node::addChild(cd_progress,1,0);
                cd_progress->runAction(Sequence::create(ProgressTo::create(cdtime, 100),
                                                        RemoveSelf::create(),
                                                        CallFunc::create([&]()
                                                                         {
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