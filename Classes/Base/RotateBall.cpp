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
    auto plane_ball = RotateBall::create();
    if (plane_ball) {
        plane_ball->initWithIdx(idx);
    }
    return plane_ball;
}

bool RotateBall::initWithIdx(int idx)
{
    Node::init();
    
    _isRotate = false;
    
    ClippingNode* clip = ClippingNode::create();
    clip->setInverted(false);
    clip->setAlphaThreshold(0.0f);
    this->addChild(clip);
    
    char name[30];
    sprintf(name, "icon_planet_%d.png",idx+1);
    
    ball1 = Sprite::createWithSpriteFrameName(name);
    ball1->getTexture()->setAliasTexParameters();
    clip->addChild(ball1);
    
    ball2 = Sprite::createWithSpriteFrameName(name);
    ball2->getTexture()->setAliasTexParameters();
    ball2->setFlippedX(true);
    ball2->setPosition(ball1->getPosition()-Point(ball1->getContentSize().width,0));
    clip->addChild(ball2);
    
    auto mask = Sprite::createWithSpriteFrameName("icon_planet_mask.png");
    clip->setStencil(mask);
    
    auto bk = Sprite::createWithSpriteFrameName("icon_planet_shadow.png");
    this->addChild(bk);
    
    this->setScale(0.8f);
    
    this->scheduleUpdate();
    return true;
}

void RotateBall::resetIdx(int idx)
{
    char name[30];
    sprintf(name, "icon_planet_%d.png",idx+1);
    ball1->setSpriteFrame(name);
    ball1->setPosition(Point(0,0));
    ball2->setSpriteFrame(name);
    ball2->setPosition(ball1->getPosition()-Point(ball1->getContentSize().width,0));
}

void RotateBall::setRotate(bool rotate)
{
//    if (_isRotate) {
//        if (!rotate) {
//            _isRotate = false;
//            this->setScale(0.8f);
//        }
//    }
//    else
//    {
//        if (rotate)
//        {
//            _isRotate = true;
//            this->setScale(0.9f);
//        }
//    }
    _isRotate = rotate;
}

void RotateBall::update(float dt)
{
    log("_isRotate is %d",_isRotate);
    if(_isRotate)
    {
        ball1->setPositionX(int(ball1->getPositionX())+2);
        ball2->setPositionX(int(ball2->getPositionX())+2);
        if (ball2->getPositionX() == 0)
        {
            ball1->setPositionX(-ball1->getContentSize().width);
        }
        if (ball1->getPositionX() == 0)
        {
            ball2->setPositionX(-ball1->getContentSize().width);
        }
    }
}