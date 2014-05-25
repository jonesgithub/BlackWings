#pragma once

#include "cocos2d.h"

USING_NS_CC;

class RedeemLayer : public LayerColor
{
public:
    CREATE_FUNC(RedeemLayer);

    virtual bool init();

    void menuCallbackClosed(Ref *sender);
    void menuCallbackRedeem(Ref *sender);

private:

};
