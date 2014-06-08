//
//  UpgradeUILayer.h
//  BlackWings
//
//  Created by Jacky on 14-6-7.
//
//

#ifndef __BlackWings__UpgradeUILayer__
#define __BlackWings__UpgradeUILayer__

#include "cocos2d.h"
#include "Base.h"

class UpgradeUILayer : public cocos2d::Layer
{
public:
    static UpgradeUILayer* create(BasePanel basePanel, int index);
    
    virtual bool init(BasePanel basePanel, int index);
    
    void menuCallbackUpgrade(cocos2d::Ref *sender);
    
    void menuCallbackClosed(cocos2d::Ref *sender);
    
    void createStoneSpeedUI();
    
    void createStoneMaxUI();
    
    void createFlightUI();
    
    void createWeaponUI();
    
    cocos2d::extension::Scale9Sprite* _panel;
    Size panelSize;
    
private:
    
    BasePanel _basePanel;
    int _index;
    int _needgem;
};

#endif /* defined(__BlackWings__UpgradeUILayer__) */
