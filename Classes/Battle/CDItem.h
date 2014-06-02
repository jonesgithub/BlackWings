//
//  CDItem.h
//  BlackWings
//
//  Created by Jacky on 14-6-1.
//
//

#ifndef __BlackWings__CDItem__
#define __BlackWings__CDItem__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

typedef std::function<void(cocos2d::Ref*)> CDEndCallback;

class CDItem : public cocos2d::Node
{
public:
    static CDItem* create(int index, const CDEndCallback& callback);
    
    virtual bool init(int index, const CDEndCallback& callback);
  
    void update(float dt);
    
    bool _isMove;
    
private:
    
    CDEndCallback _onFinish;
    
    int _index;
    
    int _cdtime;
    
    int _curcdtime;
    
    cocos2d::ui::LoadingBar* _cdBar;
    
};

#endif /* defined(__BlackWings__CDItem__) */
