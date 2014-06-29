#pragma once

#include "cocos2d.h"
#include "TextSprite.h"
#include "Battleground.h"

extern Battleground* s_battleground;

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
    
    void activeCD_callback(EventCustom* event);
    
    void unselectedall(EventCustom* event);
    
    void updateFlightData(EventCustom* event);
    void updateWeaponData(EventCustom* event);
    
    void checkFlightAvaliable(EventCustom* event);
    void checkWeaponAvaliable(EventCustom* event);

    TextSprite * _label;
    int typeIndex;
    
    Type _type;
    int _index;
    
    Label* stoneformake_text;
    Label* countNum;
    Label* stoneTatalNum;
    
    Sprite* flight_avaliable;
    Sprite* weapon_avaliable;
    
    bool _isLocked;
    bool _isInProgress;
    
    Sprite* fighter;
    Sprite* weapon;
    
    TextSprite* count_text;
};
