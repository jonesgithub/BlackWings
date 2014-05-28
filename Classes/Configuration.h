#pragma once

#include <string>
#include <vector>
#include <functional>

#define FIGHTER_MAX 6
#define FIGHTER_LEVEL_MAX 15

#define ENEMY_MAX 10
#define ENEMY_LEVEL_MAX 10

#define WEAPON_MAX 3
#define WEAPON_LEVEL_MAX 10

#define MEDAL_MAX 25
#define MEDAL_REWARDS_COUNT 4

enum class Attacker
{
    ENEMY,
    PLAIN,
    WEAPON
};

typedef struct _treasure
{
    int money;//钱
    int starboom;//星际炸弹数量
    int laser;//镭射数量
    int blackhole;//黑洞数量
    int killEnemy;//已杀死敌人数量
    int usedSpcWeapon;//已使用特殊武器数量
    int overStage;//已过关数
    int killBigEnemy;//已杀死大型敌人数量
    bool firstKill;//第一场胜利
    bool unlockAllFighter;//已解锁所有敌机
}Treasure;

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
    
    void initMedalRewards();

    float musicVolume;
    float sfxVolume;
    int language;

    bool fightersLocked[FIGHTER_MAX];
    int fightersLevle[FIGHTER_MAX];

    bool weaponLocked;
    int weaponsLevel[WEAPON_MAX];
    
    bool medal_lock[MEDAL_MAX];
    bool medal_get[MEDAL_MAX];
    
    Treasure treasure;
    std::function<void()> medal_reward_callbacks[MEDAL_MAX];
};

extern GameConfig s_gameConfig;

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