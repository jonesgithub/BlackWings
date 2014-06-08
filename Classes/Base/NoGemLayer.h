//
//  NoGemLayer.h
//  BlackWings
//
//  Created by Jacky on 14-6-8.
//
//

#ifndef __BlackWings__NoGemLayer__
#define __BlackWings__NoGemLayer__

#include "cocos2d.h"

USING_NS_CC;

class NoGemLayer : public LayerColor
{
public:
    CREATE_FUNC(NoGemLayer);
    
    virtual bool init();
    
    void menuCallbackClosed(Ref *sender);
    
    void menuCallbackConfirm(Ref *sender);
    
private:
    
};


#endif /* defined(__BlackWings__NoGemLayer__) */
