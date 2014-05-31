#pragma once

#include "cocos2d.h"

class Base : public cocos2d::Scene
{
public:
    CREATE_FUNC(Base);

    virtual bool init();

    void menuCallbackMedal(Ref *sender);
    void menuCallbackSetting(Ref *sender);
    void menuCallbackBattle(Ref *sender);

    void menuCallbackUpgrade(Ref *sender);

private:
    void createBase(Ref *sender);
    
    void createUpgrade();
    void createTopPanel();

    void createFighterBottomInfo(Node* panel);
    void createFighterMiddleInfo(Node* panel);
    void createFighterTopInfo(Node* panel);
    
    Node* _playerBag;
    Node* _upgradePanel;
    Node* _topPanel;
/*
public:
    cocos2d::Label * _gen_level_label;
    cocos2d::Label * _gen_return_time_label;
    cocos2d::Label * _gen_upgrade_need_money_label;
    
    cocos2d::Label * _capcity_level_label;
    cocos2d::Label * _capcity_num_label;
    cocos2d::Label * _capcity_upgrade_need_money_label;
    
    cocos2d::Label * _flight_level_label;
    cocos2d::Label * _flight_life_label;
    cocos2d::Label * _flight_attack_label;
    cocos2d::Label * _flight_speed_label;
    cocos2d::Label * _flight_defend_label;
    cocos2d::Label * _flight_range_label;
    cocos2d::Label * _flight_upgrade_need_money_label;
    */
};
