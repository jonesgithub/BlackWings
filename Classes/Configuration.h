#pragma once

#include <string>
#include <vector>
#include <functional>
#include "GameStrings.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#define FIGHTER_MAX 6
#define FIGHTER_LEVEL_MAX 15

#define ENEMY_MAX 10
#define ENEMY_LEVEL_MAX 10

#define WEAPON_MAX 3
#define WEAPON_LEVEL_MAX 10

#define MEDAL_MAX 25
#define MEDAL_REWARDS_COUNT 4

#define OTHER_DATA 17

#define STAGE_REWAEDS_COUNT 4

#define STONE_SPEED_LEVEL_MAX 20
#define STONE_CAPACITY_LEVEL_MAX 20

#define STAGE_COUNT 50

#define STAGEOFCANBUYGEM -2

#define STAGE_ENEMY_WAVES_00 1
#define STAGE_ENEMY_WAVES_01 1
#define STAGE_ENEMY_WAVES_02 3


#define STAGE_TOWER_COUNTS_00 1
#define STAGE_TOWER_COUNTS_01 1
#define STAGE_TOWER_COUNTS_02 2

//music
#define STOP_ALL_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();//停止所有背景音乐
#define PLAY_MAIN_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music_main.mp3",true);//菜单背景音乐
#define PLAY_BASE_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music_home.mp3",true);//基地背景音乐
#define PLAY_BATTLE_MUSIC CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music_battle.mp3",true);//战斗背景音乐
//effect
#define PLAY_BUTTON_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("btSound_1.mp3",false);//按键声音
#define PLAY_TOUCH_ITEM_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("btSelect.wav",false);//Item声音
#define PLAY_TOUCH_ARROW_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("btSound_3.wav",false);//arrow声音
#define PLAY_UPGRADE_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("upgrade.wav",false);//arrow声音
#define PLAY_GETGEM_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("getGem.wav",false);//获得宝石声音
#define PLAY_GETSTONE_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("getSpar.mp3",false);//获得晶石声音
#define PLAY_OPENDOOR_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("doolOpen.wav",false);//开关门声音
#define PLAY_STAGELIST_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("missionList.wav",false);//关卡列表声音
#define PLAY_BUILDPLAIN_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("btBuild.wav",false);//关卡列表声音
#define PLAY_WEAPONREADY_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("readyBomb.wav",false);//武器已准备声音
#define PLAY_WEAPONCREATE_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("createBomb.wav",false);//武器点击屏幕声音
#define PLAY_STARBOMB_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bomb_bomb.wav",false);//星际炸弹声音
#define PLAY_LASER_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bomb2_start.mp3",false);//镭射声音
#define PLAY_NORMALBULLET_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bullet_normal.mp3",false);//普通子弹声音
#define PLAY_BOMB_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("plain_bomb.wav",false);//爆炸声音
#define PLAY_WARNING_EFFECT CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boos_warning.mp3",false);//boss警告声音

//TextColor
//帮助
#define DIY_COLOR_BLUE1 Color3B(99, 218, 208)
#define DIY_COLOR_YELLOW1  Color3B(189, 189, 142)
#define DIY_COLOR_GRAY1 Color3B(168, 168, 168)
#define DIY_COLOR_ORANGE1 Color3B(210, 161, 125)
//勋章-顶部
#define DIY_COLOR_GRAY2 Color3B(200, 200, 200)
#define DIY_COLOR_BLUE2 Color3B(67, 207, 195)
//勋章-item
#define DIY_COLOR_YELLOW2 Color3B(210, 174, 78)
#define DIY_COLOR_GRAY3 Color3B(173, 173, 173)
//勋章-按钮
#define DIY_COLOR_YELLOW3 Color3B(219, 227, 0)
//base
#define DIY_COLOR_YELLOW4 Color3B(217, 198, 149)
#define DIY_COLOR_BLUE3 Color4B(100, 255, 255, 255)
#define DIY_COLOR_BLUE5
//升级
#define DIY_COLOR_YELLOW5 Color3B(220, 200, 150)
//button
#define DIY_COLOR_BLUE4 Color3B(106, 200, 238)

#define DIY_COLOR_BLUE5 Color3B(100, 255, 255)
enum class Attacker
{
    ENEMY,
    PLAIN,
    TOWER,
    BOSS
};

typedef struct _playerconfig
{
    //by Jacky
    float musicVolume;//音量
    float sfxVolume;//音效
    int language;//语言
    
    int stone;//晶石，游戏中的生成
    int stoneMax;//石头上限
    int gem;//宝石，花钱购买的
    int weaponCount[3];//三种炸弹数量
    int killenemy;//已杀死敌人数量
    int killbigenemy;//已杀死大型敌人数量
    int usedweapon;//已使用特殊武器数量
    int overstage;//已过关数
    bool firstkill;//第一场胜利
    bool unlockallfighter;//已解锁所有敌机，已解锁true，未解锁false
    int stonespeedlevel;//晶石回复等级
    int stonecapacitylevel;//晶石最大容量等级
    
    bool medallocked[MEDAL_MAX];//锁住true，解锁false
    bool medalget[MEDAL_MAX];//可领奖true，不可领奖false
    
    bool fighterslocked[FIGHTER_MAX];//锁住true，解锁false
    int fighterslevel[FIGHTER_MAX];//战机等级
    
    bool weaponlocked;//锁住true，解锁false
    int weaponslevel[WEAPON_MAX];//武器等级
    
    
    //By Yuye
    
    
    //By Qiao
    
    //如果有添加新的参数，记得到initConfig()中进行初始化
    
}PlayerConfig;

extern PlayerConfig s_playerConfig;

class GameConfig
{
public:
    const static std::string defaultFontName;
    const static int defaultFontSize;

    const static std::string eventLanguageChange;
    const static std::string eventPlayerDestroy;
    const static std::string eventPlayerBaseHurt;
    const static std::string eventEnemyBaseHurt;
    const static std::string eventResortCDItems;
    const static std::string eventStarbombHurt;
    const static std::string eventLaserHurt;
    const static std::string eventBlackholeHurt;
    const static std::string eventactiveCD;
    const static std::string eventunseletedall;
    const static std::string eventUpdateBaseData;
    const static std::string eventUpdateMenuItemData;
    const static std::string eventUpdateMenuItemFlightData;
    const static std::string eventUpdateMenuItemWeaponData;
    const static std::string eventUpdateGem;
    const static std::string eventShowWeaponMenu;
    const static std::string eventShowHideMedalLogo;
    const static std::string eventFlightAvaliable;
    const static std::string eventWeaponAvaliable;
    
    void lazyInit();
    
//    void readConfig();
//    void initConfig();
//    void saveConfig();

    void setMusicVolume(float volume);
    void setSFXVolume(float volume);
    void GSInitLanguage(GameLanguage language);
    
    //global var
    bool isInBattle;
};

extern GameConfig s_gameConfig;


//写死数据
////////////////////////////////////

//解锁飞机关卡
extern int s_UnlockflightStage[6];

//stone
typedef struct _stoneSpeed
{
    int speed;//回复速度
    int gemForUpgrade;//升级所需gem
}StoneSpeed;

extern StoneSpeed s_stoneSpeed[STONE_SPEED_LEVEL_MAX];

typedef struct _stoneCapacity
{
    int initstone;//初始stone
    int maxstone;//最大stone
    int gemForUpgrade;//升级所需gem
}StoneCapacity;

extern StoneCapacity s_stoneCapacity[STONE_CAPACITY_LEVEL_MAX];


//Plain.Enemy.Weapon Cofig
typedef struct _plainConfig
{
    int sparForMake;
    int gemForUpgrade;
    int life;
    int attack;
    int speed;
    int defense;
    int range;
    float buildtime;
    float cd;
}PlainConfig;

extern PlainConfig s_plainConfigs[FIGHTER_MAX][FIGHTER_LEVEL_MAX];

typedef struct _enemyConfig
{
    int life;
    int attack;
    int speed;
    int defense;
    int range;
    int deadlossstone;//死亡丢失晶石
    int deadlossgem;//死亡丢失宝石
}EnemyConfig;

extern EnemyConfig s_enemyConfigs[ENEMY_MAX][ENEMY_LEVEL_MAX];
extern EnemyConfig s_bossConfig[ENEMY_LEVEL_MAX];
extern EnemyConfig s_towerConfig[ENEMY_LEVEL_MAX];

typedef struct _weaponConfig
{
    int costGem;
    int gemForUpgrade;
    int attack;
    float duration;
    int capacity;
    int range;
    float cd;
}WeaponConfig;

extern WeaponConfig s_weaponConfigs[WEAPON_MAX][WEAPON_LEVEL_MAX];

//MedalRewards
extern int s_medalRewards[MEDAL_MAX][MEDAL_REWARDS_COUNT];
//StageRewardss
extern int s_stageRewards[STAGE_COUNT][STAGE_REWAEDS_COUNT];

//Battle
extern int s_enemyBaseBlood[STAGE_COUNT];
extern int s_playerBaseBlood[STAGE_COUNT];
extern cocos2d::Point s_EnemyBasePos;
extern cocos2d::Point s_PlayerBasePos;

//NormalEnemy
typedef struct _battleNormalEnemyConfig
{
    int duration;
    int type;
    int level;
    int count;
}BattleNormalEnemyConfig;

typedef struct _battleNormalEnemyInfo
{
    BattleNormalEnemyConfig* _bnec;
    int waves;
}BattleNormalEnemyInfo;

extern BattleNormalEnemyInfo s_battleNormalEnemyInfo[3];

extern BattleNormalEnemyConfig s_battleNormalEnemyConfig_0[STAGE_ENEMY_WAVES_00];
extern BattleNormalEnemyConfig s_battleNormalEnemyConfig_1[STAGE_ENEMY_WAVES_01];
extern BattleNormalEnemyConfig s_battleNormalEnemyConfig_2[STAGE_ENEMY_WAVES_02];


//TowerEnemy
typedef struct _battleTowerEnemyConfig
{
    int level;
    int x;
    int y;
}BattleTowerEnemyConfig;

typedef struct _battleTowerEnemyInfo
{
    BattleTowerEnemyConfig* _btec;
    int counts;
}BattleTowerEnemyInfo;

extern BattleTowerEnemyInfo s_battleTowerEnemyInfo[3];

extern BattleTowerEnemyConfig s_battleTowerEnemyConfig_0[STAGE_TOWER_COUNTS_00];
extern BattleTowerEnemyConfig s_battleTowerEnemyConfig_1[STAGE_TOWER_COUNTS_01];
extern BattleTowerEnemyConfig s_battleTowerEnemyConfig_2[STAGE_TOWER_COUNTS_02];

//BossEnemy
typedef struct _battleBossEnemyInfo
{
    int level;
    int duration;
}BattleBossEnemyInfo;

extern BattleBossEnemyInfo s_battleBossEnemyInfo[STAGE_COUNT];


