#pragma once

#include <string>
#include <vector>
#include <functional>
#include "GameStrings.h"
#include "cocos2d.h"

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

#define STAGE_ENEMY_WAVES_00 3
#define STAGE_ENEMY_WAVES_01 2

#define STAGE_TOWER_COUNTS_00 1

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
    int starbomb;//星际炸弹数量
    int laser;//镭射数量
    int blackhole;//黑洞数量
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
    
    void lazyInit();
    
    void readConfig();
    void initConfig();
    void saveConfig();

    void setMusicVolume(float volume);
    void setSFXVolume(float volume);
    void setLanguage(GameLanguage languag);
    void GSInitLanguage(GameLanguage language);
    
    //global var
    bool isInBattle;
};

extern GameConfig s_gameConfig;


//写死数据
////////////////////////////////////

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

extern BattleNormalEnemyInfo s_battleNormalEnemyInfo[2];

extern BattleNormalEnemyConfig s_battleNormalEnemyConfig_0[STAGE_ENEMY_WAVES_00];
extern BattleNormalEnemyConfig s_battleNormalEnemyConfig_1[STAGE_ENEMY_WAVES_01];

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

extern BattleTowerEnemyInfo s_battleTowerEnemyInfo[1];

extern BattleTowerEnemyConfig s_battleTowerEnemyConfig_0[STAGE_TOWER_COUNTS_00];

//BossEnemy
typedef struct _battleBossEnemyInfo
{
    int level;
    int duration;
}BattleBossEnemyInfo;

extern BattleBossEnemyInfo s_battleBossEnemyInfo[STAGE_COUNT];


