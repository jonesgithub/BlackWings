#pragma once

#include "cocos2d.h"

USING_NS_CC;

class NotificationLayer : public LayerColor
{
public:
    static NotificationLayer* create(const std::string& notificationMsg,const Size& size = Size::ZERO);

    virtual bool init(const std::string& notificationMsg,const Size& size);

    void menuCallbackClosed(Ref *sender);

private:

};
