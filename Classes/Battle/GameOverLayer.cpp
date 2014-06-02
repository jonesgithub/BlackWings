//
//  GameOverLayer.cpp
//  BlackWings
//
//  Created by Jacky on 14-6-2.
//
//

#include "GameOverLayer.h"
#include "Configuration.h"
#include "VisibleRect.h"
#include "extensions/cocos-ext.h"
#include "TextSprite.h"

USING_NS_CC;
USING_NS_CC_EXT;

GameOverLayer* GameOverLayer::create(bool win, int stage, int time, int kill, int loss)
{
    auto pRet = new GameOverLayer();
    if (pRet && pRet->init(win, stage, time, kill, loss))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool GameOverLayer::init(bool win, int stage, int time, int kill, int loss)
{
    if(cocos2d::Layer::init())
    {
        return false;
    }
    
    //panel
    Size panelSize;
    if(win)
        Size(s_visibleRect.visibleWidth-40,s_visibleRect.visibleHeight-200);
    else
        Size(s_visibleRect.visibleWidth-40,s_visibleRect.visibleHeight-300);
    
    auto _panel = Scale9Sprite::create("windowBox.png");
    _panel->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _panel->setPosition(Point(s_visibleRect.center.x,s_visibleRect.top.y + panelSize.height));
    _panel->setContentSize(panelSize);
    this->addChild(_panel);
    _panel->runAction(MoveTo::create(0.15f,s_visibleRect.top));
    
    //title
//    auto title = TextSprite::create("")
    
    
    return true;
}

void GameOverLayer::returnBase_callback(cocos2d::Ref* pSender)
{
    
}

void GameOverLayer::nextStage_callback(cocos2d::Ref* pSender)
{
    
}

void GameOverLayer::restartStage_callback(cocos2d::Ref* pSender)
{
    
}
