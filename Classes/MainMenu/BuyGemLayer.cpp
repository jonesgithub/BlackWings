//
//  BuyGemLayer.cpp
//  BlackWings
//
//  Created by cocos2dx on 14-6-1.
//
//

#include "BuyGemLayer.h"
#include "VisibleRect.h"
#include "MenuItemImageLabel.h"
#include <stdlib.h>
#include <stdio.h>

bool BuyGemLayer::init()
{
    //add back
    
    //add title
    
    //add free gem
    
    //add items
    for (int i=0; i<7; i++) {
        auto item = GemItem::createWithIdx(i);
        addChild(item);
        item->setPosition(70, 800 - i*i);
    }
    
    //item return
    auto itemClosed = MenuItemImageLabel::createWithFrameName("back_0.png","back_1.png",
                                                              CC_CALLBACK_1(BuyGemLayer::menuCallbackClosed,this));
    itemClosed->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    itemClosed->setPosition(s_visibleRect.rightTop);
    
    auto menu = Menu::create( itemClosed, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    return true;
}

void BuyGemLayer::menuCallbackClosed(Ref *sender)
{
    this->removeFromParentAndCleanup(true);
    
}


///////
GemItem* GemItem::createWithIdx(int idx)
{
    auto gem = GemItem::create();
    gem->initWithIdx(idx);
    return gem;
}


void GemItem::initWithIdx(int idx)
{
    //add back
    auto spbk = Sprite::createWithSpriteFrameName("medal_minibox_0.png");
    addChild(spbk);
    
    char szName[32];
    sprintf(szName, "icon_buyGemList_%d.png", idx+1);
    auto spGem = Sprite::createWithSpriteFrameName(szName);
    addChild(spGem);
    
    auto mv1 = MoveBy::create(1, Point(-10, 0));
    auto mv2 = mv1->reverse();
    auto action = Sequence::create(mv1 ,mv2, NULL);
    spGem->runAction(RepeatForever::create(action));
    
    //add title]
    char gemCount[32];
    sprintf(gemCount, "宝石：%d", 1000000);
    
    auto lbCount = TextSprite::create(gemCount);
    addChild(lbCount);
    lbCount->setPosition(200, 10);
    
    char gemValue[16];
    sprintf(gemValue, "$ %f", 6.00);
    
    auto lbValue = TextSprite::create(gemValue);
    addChild(lbValue);
    lbValue->setPosition(420, 10);
    
}