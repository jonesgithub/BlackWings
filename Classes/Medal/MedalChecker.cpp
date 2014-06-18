//
//  MedalChecker.cpp
//  BlackWings
//
//  Created by Jacky on 14-5-28.
//
//

#include "MedalChecker.h"
#include "Configuration.h"
#include "TextSprite.h"
#include "GameStrings.h"
#include "VisibleRect.h"

MedalChecker* MedalChecker::m_pInstance=NULL;
MedalChecker::CGarbo MedalChecker::m_garbo;

MedalChecker::MedalChecker()
{
    new_medal_indexs.clear();
}

void MedalChecker::check()
{
    check_firstkill();
    check_killenemy();
    check_money();
    check_killbigenmey();
    check_usedspcweapon();
    check_unlockallfighter();
    check_stagevictory();
    check_fightermaxlevel();
    
    //show tips
    showTip();
    //save data
    s_gameConfig.saveConfig();
}

void MedalChecker::check_firstkill()
{
    if (s_playerConfig.firstkill & s_playerConfig.medallocked[0]) {
        s_playerConfig.medallocked[0] = false;
        s_playerConfig.medalget[0] = true;
        new_medal_indexs.push_back(0);
    }
}

void MedalChecker::check_killenemy()
{
    if (s_playerConfig.killenemy >= 100 && s_playerConfig.medallocked[1]) {
        s_playerConfig.medallocked[1] = false;
        s_playerConfig.medalget[1] = true;
        new_medal_indexs.push_back(1);
    }
    if (s_playerConfig.killenemy >= 1000 && s_playerConfig.medallocked[2]) {
        s_playerConfig.medallocked[2] = false;
        s_playerConfig.medalget[2] = true;
        new_medal_indexs.push_back(2);
    }
    if (s_playerConfig.killenemy >= 2000 && s_playerConfig.medallocked[3]) {
        s_playerConfig.medallocked[3] = false;
        s_playerConfig.medalget[3] = true;
        new_medal_indexs.push_back(3);
    }
    if (s_playerConfig.killenemy >= 5000 && s_playerConfig.medallocked[4]) {
        s_playerConfig.medallocked[4] = false;
        s_playerConfig.medalget[4] = true;
        new_medal_indexs.push_back(4);
    }
    if (s_playerConfig.killenemy >= 10000 && s_playerConfig.medallocked[5]) {
        s_playerConfig.medallocked[5] = false;
        s_playerConfig.medalget[5] = true;
        new_medal_indexs.push_back(5);
    }
}

void MedalChecker::check_money()
{
    if (s_playerConfig.gem >= 50000 && s_playerConfig.medallocked[6]) {
        s_playerConfig.medallocked[6] = false;
        s_playerConfig.medalget[6] = true;
        new_medal_indexs.push_back(6);
    }
    if (s_playerConfig.gem >= 100000 && s_playerConfig.medallocked[7]) {
        s_playerConfig.medallocked[7] = false;
        s_playerConfig.medalget[7] = true;
        new_medal_indexs.push_back(7);
    }
    if (s_playerConfig.gem >= 500000 && s_playerConfig.medallocked[8]) {
        s_playerConfig.medallocked[8] = false;
        s_playerConfig.medalget[8] = true;
        new_medal_indexs.push_back(8);
    }
    if (s_playerConfig.gem >= 1000000 && s_playerConfig.medallocked[9]) {
        s_playerConfig.medallocked[9] = false;
        s_playerConfig.medalget[9] = true;
        new_medal_indexs.push_back(9);
    }
    if (s_playerConfig.gem >= 5000000 && s_playerConfig.medallocked[10]) {
        s_playerConfig.medallocked[10] = false;
        s_playerConfig.medalget[10] = true;
        new_medal_indexs.push_back(10);
    }
}

void MedalChecker::check_killbigenmey()
{
    if (s_playerConfig.killbigenemy >= 10 && s_playerConfig.medallocked[11]) {
        s_playerConfig.medallocked[11] = false;
        s_playerConfig.medalget[11] = true;
        new_medal_indexs.push_back(11);
    }
    if (s_playerConfig.killbigenemy >= 50 && s_playerConfig.medallocked[12]) {
        s_playerConfig.medallocked[12] = false;
        s_playerConfig.medalget[12] = true;
        new_medal_indexs.push_back(12);
    }
}

void MedalChecker::check_usedspcweapon()
{
    if (s_playerConfig.usedweapon >= 100 && s_playerConfig.medallocked[13]) {
        s_playerConfig.medallocked[13] = false;
        s_playerConfig.medalget[13] = true;
        new_medal_indexs.push_back(13);
    }
    if (s_playerConfig.usedweapon >= 500 && s_playerConfig.medallocked[14]) {
        s_playerConfig.medallocked[14] = false;
        s_playerConfig.medalget[14] = true;
        new_medal_indexs.push_back(14);
    }
}

void MedalChecker::check_unlockallfighter()
{
    if (s_playerConfig.unlockallfighter && s_playerConfig.medallocked[15]) {
        s_playerConfig.medallocked[15] = false;
        s_playerConfig.medalget[15] = true;
        new_medal_indexs.push_back(15);
    }
}

void MedalChecker::check_stagevictory()
{
    if (s_playerConfig.overstage >= 29 && s_playerConfig.medallocked[16]) {
        s_playerConfig.medallocked[16] = false;
        s_playerConfig.medalget[16] = true;
        new_medal_indexs.push_back(16);
    }
    if (s_playerConfig.overstage >= 39 && s_playerConfig.medallocked[17]) {
        s_playerConfig.medallocked[17] = false;
        s_playerConfig.medalget[17] = true;
        new_medal_indexs.push_back(17);
    }
    if (s_playerConfig.overstage >= 49 && s_playerConfig.medallocked[18]) {
        s_playerConfig.medallocked[18] = false;
        s_playerConfig.medalget[18] = true;
        new_medal_indexs.push_back(18);
    }
}
void MedalChecker::check_fightermaxlevel()
{
    if (s_playerConfig.fighterslevel[0] == FIGHTER_LEVEL_MAX-1 && s_playerConfig.medallocked[19]) {
        s_playerConfig.medallocked[19] = false;
        s_playerConfig.medalget[19] = true;
        new_medal_indexs.push_back(19);
    }
    if (s_playerConfig.fighterslevel[1] == FIGHTER_LEVEL_MAX-1 && s_playerConfig.medallocked[20]) {
        s_playerConfig.medallocked[20] = false;
        s_playerConfig.medalget[20] = true;
        new_medal_indexs.push_back(20);
    }
    if (s_playerConfig.fighterslevel[2] == FIGHTER_LEVEL_MAX-1 && s_playerConfig.medallocked[21]) {
        s_playerConfig.medallocked[21] = false;
        s_playerConfig.medalget[21] = true;
        new_medal_indexs.push_back(21);
    }
    if (s_playerConfig.fighterslevel[3] == FIGHTER_LEVEL_MAX-1 && s_playerConfig.medallocked[22]) {
        s_playerConfig.medallocked[22] = false;
        s_playerConfig.medalget[22] = true;
        new_medal_indexs.push_back(22);
    }
    if (s_playerConfig.fighterslevel[4] == FIGHTER_LEVEL_MAX-1 && s_playerConfig.medallocked[23]) {
        s_playerConfig.medallocked[23] = false;
        s_playerConfig.medalget[23] = true;
        new_medal_indexs.push_back(23);
    }
    if (s_playerConfig.fighterslevel[5] == FIGHTER_LEVEL_MAX-1 && s_playerConfig.medallocked[24]) {
        s_playerConfig.medallocked[24] = false;
        s_playerConfig.medalget[24] = true;
        new_medal_indexs.push_back(24);
    }
}

void MedalChecker::showTip()
{
    for (int i = 0; i < new_medal_indexs.size(); ++i) {
        
        auto tip = Node::create();
        
        auto tip_bk = Sprite::create("newMedalTip_box.png");
        tip_bk->setAnchorPoint(Point::ANCHOR_MIDDLE);
        tip->addChild(tip_bk);
        
        auto icon_medal = Sprite::createWithSpriteFrameName("icon_medal.png");
        icon_medal->setAnchorPoint(Point::ANCHOR_MIDDLE);
        icon_medal->setPosition(0,tip_bk->getContentSize().height/2);
        tip_bk->addChild(icon_medal);
        
        auto newmedal_text = TextSprite::create(s_gameStrings.medalInfo->newmedal, "Arial", 20);
        newmedal_text->setColor(Color3B::BLACK);
        newmedal_text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        newmedal_text->setPosition(80,tip_bk->getContentSize().height/2);
        tip_bk->addChild(newmedal_text);
        
        auto newmedal_name = TextSprite::create(s_gameStrings.medalInfo->medalname[new_medal_indexs.at(i)]);
        newmedal_name->setColor(Color3B(128,42,42));
        newmedal_name->cocos2d::Node::setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        newmedal_name->setPosition(150,tip_bk->getContentSize().height/2);
        tip_bk->addChild(newmedal_name);
        
        tip->setAnchorPoint(Point::ANCHOR_MIDDLE);
        tip->setPosition(Point(1000,s_visibleRect.visibleHeight-150 - 100*i));
        Director::getInstance()->getRunningScene()->addChild(tip,1000);
        tip->runAction(Sequence::create(MoveTo::create(1.0f, Point(s_visibleRect.visibleWidth/2,s_visibleRect.visibleHeight-150 - 100*i)),
                                        DelayTime::create(2.0f),
                                        MoveTo::create(1.0f, Point(1000, s_visibleRect.visibleHeight-150 - 100*i)),
                                        RemoveSelf::create(),
                                        nullptr));
        
    }
    
    new_medal_indexs.clear();
}