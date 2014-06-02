#include "VisibleRect.h"
#include "Configuration.h"

USING_NS_CC;

VisibleRect s_visibleRect;

void VisibleRect::lazyInit()
{
    // no lazy init
    // Useful if we change the resolution in runtime
    auto visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();

    visibleWidth = visibleRect.size.width;
    visibleHeight = visibleRect.size.height;
    visibleOriginX = visibleRect.origin.x;
    visibleOriginY = visibleRect.origin.y;

    center.x = visibleOriginX + visibleWidth / 2;
    center.y = visibleOriginY + visibleHeight / 2;

    left.x = visibleOriginX;
    left.y = center.y;

    right.x = visibleOriginX + visibleWidth;
    right.y = center.y;

    top.x = center.x;
    top.y = visibleOriginY + visibleHeight;

    bottom.x = center.x;
    bottom.y = visibleOriginY;

    leftTop.x = left.x;
    leftTop.y = top.y;

    rightTop.x = right.x;
    rightTop.y = top.y;

    leftBottom.x = left.x;
    leftBottom.y = bottom.y;

    rightBottom.x = right.x;
    rightBottom.y = bottom.y;
    
    s_EnemyBasePos = cocos2d::Point(s_visibleRect.visibleWidth /2, s_visibleRect.visibleOriginY +s_visibleRect.visibleHeight * 3 - 130);
    s_PlayerBasePos = cocos2d::Point(s_visibleRect.visibleWidth /2, s_visibleRect.visibleOriginY + 280);
}

