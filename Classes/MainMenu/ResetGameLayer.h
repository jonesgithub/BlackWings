#pragma once

#include "cocos2d.h"

USING_NS_CC;

class ResetGameLayer : public LayerColor
{
public:
    CREATE_FUNC(ResetGameLayer);

    virtual bool init();
    //关闭按钮回调
    void menuCallbackClosed(Ref *sender);
    //确认按钮回调--清除游戏存档
    void menuCallbackConfirm(Ref *sender);

private:

};
