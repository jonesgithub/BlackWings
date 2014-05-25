#pragma once

#include "cocos2d.h"

USING_NS_CC;

class AboutLayer : public LayerColor
{
public:
    CREATE_FUNC(AboutLayer);

    virtual bool init();
    
    void menuCallbackClosed(Ref *sender);
    
    void menuCallbackMicroblog(Ref *sender);
    
    void menuCallbackEmail(Ref *sender);
    
    void menuCallbackRate(Ref *sender);

private:
    Node* _panel;
};
