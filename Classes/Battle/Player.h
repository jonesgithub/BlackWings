#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Player : public Node
{
public:
    Player();
    virtual ~Player();

    virtual void hurt(int ATK){}

private:

};
