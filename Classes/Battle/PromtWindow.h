//
//  PromtWindow.h
//  BlackWings
//
//  Created by Jacky on 14-6-21.
//
//

#pragma once

#include "cocos2d.h"

enum class ForWhat
{
    Restart,
    BackToBase,
    BACKToMainMenu
};

USING_NS_CC;

class PromtWindow : public LayerColor
{
public:
    
    static PromtWindow* create(ForWhat forwhat);
    
    virtual bool init(ForWhat forwhat);
    
    void menuCallbackClosed(Ref *sender);
    
    void menuCallbackConfirm(Ref *sender);
    
    ForWhat _forWhat;
    
private:
    
};
