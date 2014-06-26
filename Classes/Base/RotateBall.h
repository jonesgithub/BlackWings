//
//  RotateBall.h
//  BlackWings
//
//  Created by cocos2dx on 14-5-31.
//
//

#ifndef __BlackWings__RotateBall__
#define __BlackWings__RotateBall__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RotateBall : public Node
{
public:
    CREATE_FUNC(RotateBall);
    static RotateBall* createWithIdx(int idx);
    void setRotate(bool rotate);
    virtual void update(float dt);
private:
    bool initWithIdx(int idx);
    bool _isRotate;
    Sprite* ball1;
    Sprite* ball2;
};

#endif /* defined(__BlackWings__RotateBall__) */
