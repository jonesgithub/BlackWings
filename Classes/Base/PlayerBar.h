#pragma once

#include "cocos2d.h"
#include "MenuItemImageLabel.h"

USING_NS_CC;

class PlayerBar : public Node
{
public:
    static const std::string eventPlayerSelect;

    CREATE_FUNC(PlayerBar);

    virtual bool init();
      
    void menuCallbackArrow(Ref *sender);
    
    void setStone(int num);
    
    void setStoneMax(int num);
    
    void setGem(int num);
    
    void shakeStone();
    
    void shakeGem();
    
    Node* _playerMenu;
    
    cocos2d::MenuItemSprite * fighterCopy;
    
    void getmoregem(Ref* sender);
    
private:
    bool _showFighter;
    
    Label* stoneNum;
    Label* stoneTatalNum;
    Label* sparNum;
    
    MenuItemImageLabel* menuitem_getmore;
    
    bool _isStoneShaking;
    bool _isGemShaking;
    
    Sprite* stoneIcon;
    Sprite* gemIcon;
};
