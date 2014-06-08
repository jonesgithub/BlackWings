#pragma once

#include "cocos2d.h"

USING_NS_CC;

class ResetGameLayer : public LayerColor
{
public:
    CREATE_FUNC(ResetGameLayer);

    virtual bool init();

    void menuCallbackClosed(Ref *sender);

    void menuCallbackConfirm(Ref *sender);

private:

};
