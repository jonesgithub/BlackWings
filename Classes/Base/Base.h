#pragma once

#include "cocos2d.h"
#include "PlayerBar.h"
#include "extensions/cocos-ext.h"
#include "TextSprite.h"
#include "MenuItemImageLabel.h"

enum class BasePanel
{
    Toppanel,
    MiddlePanel,
    FlightPanel,
    WeaponPanel
};

class Base : public cocos2d::Scene
{
public:
    CREATE_FUNC(Base);
    
    virtual bool init();
    
    void menuCallbackMedal(Ref *sender);
    void menuCallbackSetting(Ref *sender);
    void menuCallbackBattle(Ref *sender);
    
    void upgradeStoneSpeed(Ref* sender);
    void upgradeStoneMax(Ref* sender);
    void upgradeFlight(Ref* sender);
    void upgradeWeapon(Ref* sender);
    
    void buyWeapon(Ref* sender);
    
    void showUpgradeUI(BasePanel basePanel);
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    void createBase(Ref *sender);
    
    void createUpgrade();
    void createTopPanel();
    void createBottomPanel();
    
    void createFighterBottomInfo(Node* panel, int t_index);
    void createWeaponBottomInfo(Node* panel, int t_index);
    void createFighterMiddleInfo(Node* panel);
    void createFighterTopInfo(Node* panel);
    
    void showGemTip(int num, bool isCost);
    
    void showOrHideMedalLogo(EventCustom* event);
    
    PlayerBar* _playerBag;
    Node* _upgradePanel;
    Node* _topPanel;
    Node* _bottomPanel;
    
    bool _isInFilghtUpgradeUI;
    
    cocos2d::Sprite* _curSelectedFlight;
    int _curSeletedIndex;
    
    cocos2d::extension::Scale9Sprite* upgradeFighter;
    
    MenuItemImageLabel* medalItem;
    Sprite* medalLogo;
    
    cocos2d::Label* top_level;
    cocos2d::Label* top_speed;
    cocos2d::Label* top_leveUpCost;
    cocos2d::Label* top_plus;
    cocos2d::Label* top_slash;
    TextSprite* top_second;
    
    cocos2d::Label* middle_level;
    cocos2d::Label* middle_init;
    cocos2d::Label* middle_slash;
    cocos2d::Label* middle_total;
    cocos2d::Label* middle_leveUpCost;

    
    cocos2d::Label * _flight_level_label;
    cocos2d::Label * _flight_life_label;
    cocos2d::Label * _flight_attack_label;
    cocos2d::Label * _flight_speed_label;
    cocos2d::Label * _flight_defend_label;
    cocos2d::Label * _flight_range_label;
    cocos2d::Label * _flight_upgradeforgem_label;
    
    cocos2d::Label* _weapon_level_label;
    cocos2d::Label* _weapon_attack_label;
    cocos2d::Label* _weapon_duration_label;
    cocos2d::Label* _weapon_upgradeforgem_label;
    cocos2d::Label* _weapon_costgem_label;
    TextSprite* _buy_gem;

};
