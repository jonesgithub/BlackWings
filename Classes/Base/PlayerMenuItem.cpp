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
            if (s_gameConfig.fightersLocked[index])
            {
                sprintf(iconFileName,"icon_lock.png");
                this->setEnabled(false);
            }
            else
            {
                sprintf(iconFileName,"plain_%d_lv_%d.png",index + 1,s_gameConfig.fightersLevle[index] + 1);
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
        normalSprite = Scale9Sprite::createWithSpriteFrameName("item_0.png");
        normalSprite->setContentSize(size);
        selectedSprite = Scale9Sprite::createWithSpriteFrameName("item_1.png");
        selectedSprite->setContentSize(size);

        ret = initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, nullptr);

        if (ret)
        {
            char iconFileName[25];
            sprintf(iconFileName,"bomb_%d_%d.png",index + 1,s_gameConfig.weaponsLevel[index] + 1);
            auto weapon = Sprite::createWithSpriteFrameName(iconFileName);
            weapon->setPosition(Point(size.width/2,76));
            weapon->setRotation(90);
            Node::addChild(weapon,1,0);
            //disabledSprite = Sprite::createWithSpriteFrameName("item_4.png");
        }
    }

    return ret;
}

void PlayerMenuItem::activate()
{
    MenuItemImage::activate();
    //
    _eventDispatcher->dispatchCustomEvent(PlayerBar::eventPlayerSelect,(void*)typeIndex);
}
