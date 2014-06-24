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
    
    _isRotate = true;
    
    auto bk = Sprite::createWithSpriteFrameName("icon_planet_shadow.png");
    bk->setScale(1.1f);
    this->addChild(bk);
    
    ClippingNode* clip = ClippingNode::create();
    clip->setInverted(false);
    clip->setAlphaThreshold(0.0f);
    this->addChild(clip);
    
    ball1 = Sprite::createWithSpriteFrameName("icon_planet_10.png");
    ball1->getTexture()->setAliasTexParameters();
    clip->addChild(ball1);
    
    ball2 = Sprite::createWithSpriteFrameName("icon_planet_10.png");
    ball2->getTexture()->setAliasTexParameters();
    ball2->setFlippedX(true);
    ball2->setPosition(ball1->getPosition()-Point(ball1->getContentSize().width,0));
    clip->addChild(ball2);
    
    auto mask = Sprite::createWithSpriteFrameName("icon_planet_mask.png");
    clip->setStencil(mask);
    
    this->scheduleUpdate();
    return true;
}

void RotateBall::setRotate(bool rotate)
{
    _isRotate = rotate;
}

void RotateBall::update(float dt)
{
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