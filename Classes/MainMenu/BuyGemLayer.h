//
//  BuyGemLayer.h
//  BlackWings
//
//  Created by cocos2dx on 14-6-1.
//
//

#ifndef __BlackWings__BuyGemLayer__
#define __BlackWings__BuyGemLayer__


#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GemItem : public Layer
{
public:
    CREATE_FUNC(GemItem);
    static GemItem* createWithIdx(int idx);
    
    
    void initWithIdx(int idx);
};

class BuyGemLayer : public Layer
{
public:
    CREATE_FUNC(BuyGemLayer);
    
    virtual bool init();
    
    void menuCallbackClosed(Ref *sender);
    void onClick(Ref *sender);
private:
};

#endif /* defined(__BlackWings__BuyGemLayer__) */
