#pragma once

#include "cocos2d.h"

USING_NS_CC;

class ResetGameLayer : public LayerColor
{
public:
    CREATE_FUNC(ResetGameLayer);

    virtual bool init();
    //�رհ�ť�ص�
    void menuCallbackClosed(Ref *sender);
    //ȷ�ϰ�ť�ص�--�����Ϸ�浵
    void menuCallbackConfirm(Ref *sender);

private:

};
