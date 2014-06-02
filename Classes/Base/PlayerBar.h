#pragma once

#include "cocos2d.h"

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
    
private:
    bool _showFighter;
    Node* _playerMenu;
    
    Label* stoneNum;
    Label* stoneTatalNum;
    Label* sparNum;
};
