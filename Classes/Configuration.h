#pragma once

#include <string>

#define FIGHTER_MAX 6
#define FIGHTER_LEVEL_MAX 15

#define ENEMY_MAX 10
#define ENEMY_LEVEL_MAX 10

#define WEAPON_MAX 3
#define WEAPON_LEVEL_MAX 10

enum class Attacker
{
    ENEMY,
    PLAIN,
    WEAPON
};

class GameConfig
{
public:
    const static std::string defaultFontName;
    const static int defaultFontSize;

    const static std::string eventLanguageChange;
    const static std::string eventPlayerDestroy;

    void lazyInit();

    void setMusicVolume(float volume);
    void setSFXVolume(float volume);

    void saveConfig();

    float musicVolume;
    float sfxVolume;
    int language;

    bool fightersLocked[FIGHTER_MAX];
    int fightersLevle[FIGHTER_MAX];

    bool weaponLocked;
    int weaponsLevel[WEAPON_MAX];
};

extern GameConfig s_gameConfig;

typedef struct _plainConfig
{
    //建设所需晶石
    int sparForMake;
    //升级所需宝石
    int gemForUpgrade;
    //生命
    int life;
    //攻击
    int attack;
    //速度
    int speed;
    //防御力
    int defense;
    //射程
    int range;
}PlainConfig;

extern PlainConfig s_plainConfigs[FIGHTER_MAX][FIGHTER_LEVEL_MAX];

typedef struct _enemyConfig
{
    //生命
    int life;
    //攻击
    int attack;
    //速度
    int speed;
    //防御力
    int defense;
    //射程
    int range;
}EnemyConfig;

extern EnemyConfig s_enemyConfigs[ENEMY_MAX][ENEMY_LEVEL_MAX];

typedef struct _weaponConfig
{
    //购买所需宝石
    int costGem;
    //升级所需宝石
    int gemForUpgrade;
    //攻击
    int attack;
    //持续时间
    float duration; 
    //携带上限
    int capacity;
}WeaponConfig;

extern WeaponConfig s_weaponConfigs[WEAPON_MAX][WEAPON_LEVEL_MAX];