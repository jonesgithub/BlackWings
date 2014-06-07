#pragma once

#include "cocos2d.h"
#include "PlayerBar.h"
#include "extensions/cocos-ext.h"

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
    void updatePanelStatus();
    
private:
    void createBase(Ref *sender);
    
    void createUpgrade();
    void createTopPanel();
    void createBottomPanel();
    
    void createFighterBottomInfo(Node* panel, int t_index);
    void createWeaponBottomInfo(Node* panel, int t_index);
    void createFighterMiddleInfo(Node* panel);
    void createFighterTopInfo(Node* panel);
    
    PlayerBar* _playerBag;
    Node* _upgradePanel;
    Node* _topPanel;
    Node* _bottomPanel;
    
    bool _isInFilghtUpgradeUI;
    
    cocos2d::Sprite* _curSelectedFlight;
    int _curSeletedIndex;
    
    cocos2d::extension::Scale9Sprite* upgradeFighter;
    
    Node * _fighterPic;
    
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

};
