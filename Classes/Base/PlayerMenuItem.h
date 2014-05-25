#pragma once

#include "cocos2d.h"
#include "TextSprite.h"

USING_NS_CC;

class PlayerMenuItem : public MenuItemImage
{
public:
    enum class Type
    {
        Fighter,
        Weapon
    };
   static PlayerMenuItem* create(Type playerType,int index);

   bool init(Type playerType,int index);

   virtual void activate();

private:
    PlayerMenuItem();

    TextSprite * _label;
    int typeIndex;
};
