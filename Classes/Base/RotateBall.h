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

enum {
	kTagTitleLabel = 1,
	kTagSubtitleLabel = 2,
	kTagStencilNode = 100,
	kTagClipperNode = 101,
	kTagContentNode = 102,
};

class RotateBall : public Node
{
private:
    bool b_rotate;
    Sprite* ball;
    float b_w;
    void update(float dt);
    bool initWithIdx(int idx);
public:
    CREATE_FUNC(RotateBall);
    static RotateBall* createWithIdx(int idx);
    void setRotate(bool rotate);
};

#endif /* defined(__BlackWings__RotateBall__) */
