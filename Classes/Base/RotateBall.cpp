//
//  RotateBall.cpp
//  BlackWings
//
//  Created by cocos2dx on 14-5-31.
//
//

#include "RotateBall.h"

///////////
RotateBall* RotateBall::createWithIdx(int idx)
{
    auto ball = RotateBall::create();
    if (ball) {
        ball->initWithIdx(idx);
    }
    return ball;
}

bool RotateBall::initWithIdx(int idx)
{
    Node::init();
    //add ball
    ball = Sprite::createWithSpriteFrameName("icon_planet_3.png");
    addChild(ball);
    //add back
    auto bk = Sprite::createWithSpriteFrameName("icon_planet_shadow.png");
    addChild(bk);
    auto size = bk->getContentSize();
    CCLOG("size:%f, %f.", size.width, size.height);
    
//    Lens3D* lens = Lens3D::create(5, Size(86,86), Point(43,43), 43);
//    
//    auto _bgNode = NodeGrid::create();
//    _bgNode->setAnchorPoint(Point(0.5,0.5));
//    addChild(_bgNode);
//    _bgNode->setPosition(0, 0);
    
//    auto _target2 = NodeGrid::create();
//    _target2->setAnchorPoint(Point(0.5,0.5));
//    _target2->addChild(ball);
//    _bgNode->addChild(_target2);
//    _bgNode->runAction(lens);
//
//    b_w = ball->getContentSize().width;
//    
//    setRotate(true);
//    
//    this->scheduleUpdate();
//    
//    auto clipper = ClippingNode::create(bk);
//    clipper->setTag( kTagClipperNode );
//    clipper->setContentSize(  bk->getContentSize() );
//    clipper->setAnchorPoint(  Point(0.5, 0.5) );
//    clipper->setPosition( Point(this->getContentSize().width / 2, this->getContentSize().height / 2) );
//    clipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
//    this->addChild(clipper);
//
//    auto stencil = DrawNode::create();
//    Point rectangle[4];
//    rectangle[0] = Point(0, 0);
//    rectangle[1] = Point(clipper->getContentSize().width, 0);
//    rectangle[2] = Point(clipper->getContentSize().width, clipper->getContentSize().height);
//    rectangle[3] = Point(0, clipper->getContentSize().height);
//    
//    Color4F white(1, 1, 1, 1);
//    stencil->drawPolygon(rectangle, 4, white, 1, white);
//    clipper->setStencil(stencil);
//    
//    auto content = Sprite::createWithSpriteFrameName("icon_planet_3.png");
//    content->setTag( kTagContentNode );
//    content->setAnchorPoint(  Point(0.5, 0.5) );
//    content->setPosition( Point(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2) );
//    clipper->addChild(content);
    
    return true;
}

void RotateBall::setRotate(bool rotate)
{
    b_rotate = rotate;
    if (rotate) {
        CCLOG("aaa");
    }
    else{
        CCLOG("bbb");
    }
}

void RotateBall::update(float dt)
{
    if (b_rotate) {
        CCLOG("abc");
//        auto p_x = ball->getPositionX() + 0.6;
//        if (p_x > b_w) {
//            p_x -= b_w;
//        }
//        ball->setPositionX(p_x);
    }
}