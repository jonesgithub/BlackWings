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
    auto scale9 = Scale9Sprite::createWithSpriteFrameName("btD_1.png");
    scale9->setContentSize(Size(620, 860));
    addChild(scale9);
    scale9->setPosition(s_visibleRect.center.x-100, s_visibleRect.center.y+30);
    
    //add title
    auto t_y = 910;
    auto spTitleBg = Scale9Sprite::createWithSpriteFrameName("sound_slider_bg_1.png");
    spTitleBg->setContentSize(Size(614, 55));
    addChild(spTitleBg);
    spTitleBg->setPosition(220, t_y);
    auto spIcon = Sprite::createWithSpriteFrameName("icon_gem.png");
    spIcon->setPosition(80, t_y);
    addChild(spIcon);
    auto lbBuy = TextSprite::create("购买宝石");
    lbBuy->setPosition(190, t_y);
    addChild(lbBuy);
    
    //add free gem
    auto f_y = 850;
    auto freeBk = Scale9Sprite::createWithSpriteFrameName("sound_slider_bg_1.png");
    addChild(freeBk);
    freeBk->setPosition(220, f_y-30);
    freeBk->setContentSize(Size(580, 120));
    auto lb_1 = TextSprite::create("你有");
    addChild(lb_1);
    lb_1->setPosition(-20, f_y);
    auto lb_2 = TextSprite::create("13");
    lb_2->setColor(Color3B(200, 200, 0));
    addChild(lb_2);
    lb_2->setPosition(40, f_y);
    auto lb_3 = TextSprite::create("个宝石未领取");
    addChild(lb_3);
    lb_3->setPosition(220, f_y);
    
    auto btnGetGem = MenuItemImageLabel::createWithFrameName("bt_buy_gem_0.png","bt_buy_gem_1.png",
                                                             CC_CALLBACK_1(BuyGemLayer::onClick,this), "领取宝石");
    btnGetGem->setTag(13);
    btnGetGem->setPosition(416, f_y);
    auto spFreeGem = Scale9Sprite::createWithSpriteFrameName("btA_0.png");
    spFreeGem->setContentSize(Size(580, 95));
    auto spFreeGem1 = Scale9Sprite::createWithSpriteFrameName("btA_1.png");
    spFreeGem1->setContentSize(Size(580, 95));
    auto btnGetFreeGem= MenuItemSprite::create( spFreeGem, spFreeGem1, CC_CALLBACK_1(BuyGemLayer::onClick,this));
    btnGetFreeGem->setTag(14);
    btnGetFreeGem->setPosition(220, f_y-50);
    auto icon_gem = Sprite::createWithSpriteFrameName("icon_buyGemList_1.png");
    addChild(icon_gem);
    icon_gem->setScale(0.6);
    icon_gem->setPosition(30, f_y - 50);
    auto lbfreeGem = TextSprite::create("获取免费宝石");
    lbfreeGem->setColor(Color3B(0, 212, 255));
    addChild(lbfreeGem);
    lbfreeGem->setPosition(230, f_y-50);
    
    //add items
    for (int i=0; i<7; i++) {
        auto item = GemItem::createWithIdx(i);
        addChild(item);
        item->setPosition(220, 703 - i*94);
    }
    
    //item return
    auto itemClosed = MenuItemImageLabel::createWithFrameName("back_0.png","back_1.png",
                                                              CC_CALLBACK_1(BuyGemLayer::menuCallbackClosed,this));
    itemClosed->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    itemClosed->setPosition(s_visibleRect.right.x-100, s_visibleRect.top.y);
    
    auto menu = Menu::create( btnGetFreeGem, btnGetGem, itemClosed, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    CCLOG("gem layer init.");
    
    return true;
}

void BuyGemLayer::menuCallbackClosed(Ref *sender)
{
    this->removeFromParentAndCleanup(true);
    
}
void BuyGemLayer::onClick(Ref *sender)
{
    auto tag = ((Node*)sender)->getTag();
    if (tag == 13) {
        CCLOG("领取宝石");
    }
    if (tag == 14) {
        CCLOG("获得免费宝石");
    }
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
    spbk->setScaleY(0.7);
    
    char szName[32];
    sprintf(szName, "icon_buyGemList_%d.png", idx+1);
    auto spGem = Sprite::createWithSpriteFrameName(szName);
    addChild(spGem);
    spGem->setPosition(-200, 10);
    
    auto mv1 = MoveBy::create(1, Point(0, -10));
    auto mv2 = mv1->reverse();
    auto action = Sequence::create(mv1 ,mv2, NULL);
    spGem->runAction(RepeatForever::create(action));
    
    //add title]
    char gemCount[32];
    sprintf(gemCount, "宝石：%d", 1000000);
    
    auto lbCount = TextSprite::create(gemCount);
    addChild(lbCount);
    lbCount->setPosition(-40, 5);
    lbCount->setColor(Color3B(215, 216, 0));
    
    char gemValue[16];
    sprintf(gemValue, "$ %f", 6.00);
    
    auto lbValue = TextSprite::create(gemValue);
    addChild(lbValue);
    lbValue->setPosition(170, 5);
    
}