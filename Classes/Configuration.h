#pragma once

#include <string>
#include <vector>
#include <functional>
#include "GameStrings.h"

#define FIGHTER_MAX 6
#define FIGHTER_LEVEL_MAX 15

#define ENEMY_MAX 10
#define ENEMY_LEVEL_MAX 10

#define WEAPON_MAX 3
#define WEAPON_LEVEL_MAX 10

#define MEDAL_MAX 25
#define MEDAL_REWARDS_COUNT 4

#define STONE_SPEED_LEVEL_MAX 15
#define STONE_CAPACITY_LEVEL_MAX 15

enum class Attacker
{
    ENEMY,
    PLAIN,
    WEAPON
};

typedef struct _playerconfig
{
    //by Jacky
    float musicVolume;//音量
    float sfxVolume;//音效
    int language;//语言
    
    int stone;//晶石，游戏中的生成
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

    void lazyInit();
    
    void readConfig();
    void initConfig();
    void saveConfig();

    void setMusicVolume(float volume);
    void setSFXVolume(float volume);
    void setLanguage(GameLanguage languag);
};

extern GameConfig s_gameConfig;


//写死数据
////////////////////////////////////


typedef struct _plainConfig
{
    int sparForMake;
    int gemForUpgrade;
    int life;
    int attack;
    int speed;
    int defense;
    int range;
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

typedef struct _weaponConfig
{
    int costGem;
    int gemForUpgrade;
    int attack;
    float duration;
    int capacity;
}WeaponConfig;

extern WeaponConfig s_weaponConfigs[WEAPON_MAX][WEAPON_LEVEL_MAX];

extern int s_medalRewards[MEDAL_MAX][MEDAL_REWARDS_COUNT];