#include "Configuration.h"
#include "GameStrings.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"

GameConfig s_gameConfig;
PlayerConfig s_playerConfig;

const std::string GameConfig::defaultFontName = "Arial";
const int GameConfig::defaultFontSize = 30;

const std::string GameConfig::eventLanguageChange = "eventLanguageChange";
const std::string GameConfig::eventPlayerDestroy = "eventPlayerDestroy";
const std::string GameConfig::eventPlayerBaseHurt = "eventPlayerBaseHurt";
const std::string GameConfig::eventEnemyBaseHurt = "eventEnemyBaseHurt";
const std::string GameConfig::eventResortCDItems = "eventResortCDItems";
const std::string GameConfig::eventStarbombHurt = "eventStarbombHurt";
const std::string GameConfig::eventLaserHurt = "eventLaserHurt";
const std::string GameConfig::eventBlackholeHurt = "eventBlackholeHurt";
const std::string GameConfig::eventactiveCD = "eventactiveCD";


void GameConfig::lazyInit()
{
    s_visibleRect.lazyInit();
    
    isInBattle = false;
    
    readConfig();
}

void GameConfig::readConfig()
{
    //todo
    
    auto userDef = UserDefault::getInstance();
    s_playerConfig.musicVolume = userDef->getFloatForKey("music",1.0f);
    s_playerConfig.sfxVolume = userDef->getFloatForKey("sfx",1.0f);
    s_playerConfig.language = userDef->getIntegerForKey("language",int(GameLanguage::English));
    
    auto data = userDef->getDataForKey("bw",Data::Null);
    if (data.isNull())
    {
        initConfig();
    }
    else
    {
        //todo:把配置读入s_playerConfig
        
        //        auto data = userDef->getDataForKey("bw");
        //        auto importantData = data.getBytes();
        //        auto levelStartIndex = FIGHTER_MAX * 2;
        //        int index;
        //        for (int i = 0; i < FIGHTER_MAX; ++i)
        //        {
        //            index = 2 * i;
        //            fightersLocked[i] = importantData[index];
        //            fightersLevle[i] = importantData[levelStartIndex + index];
        //        }
        //        auto weaponStartIndex = levelStartIndex * 2;
        //        for (int j = 0; j < WEAPON_MAX; ++j)
        //        {
        //            index = 2 * j;
        //            weaponsLevel[j] = importantData[weaponStartIndex + index];
        //        }
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(s_playerConfig.musicVolume);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(s_playerConfig.sfxVolume);
    GSInitLanguage((GameLanguage)s_playerConfig.language);
}

void GameConfig::GSInitLanguage(GameLanguage language)
{
    GSMainMenuInit(language);
    GSHelpInfoInit(language);
    GSBaseInit(language);
    GSMedalInfo(language);
    GSBattleInfo(language);
}

void GameConfig::initConfig()
{
    s_playerConfig.musicVolume = 1.0f;
    s_playerConfig.sfxVolume = 1.0f;
    s_playerConfig.language = (int)GameLanguage::English;
    
    s_playerConfig.stone = 200;
    s_playerConfig.stoneMax = 1000;
    s_playerConfig.gem = 1000;
    s_playerConfig.starbomb = 1;
    s_playerConfig.laser = 1;
    s_playerConfig.blackhole = 1;
    s_playerConfig.killenemy = 0;
    s_playerConfig.usedweapon = 0;
    s_playerConfig.overstage = 0;
    s_playerConfig.killbigenemy = 0;
    s_playerConfig.firstkill = false;
    s_playerConfig.unlockallfighter = false;
    s_playerConfig.stonespeedlevel = 1;
    s_playerConfig.stonecapacitylevel = 1;
    
    s_playerConfig.fighterslocked[0] = false;
    s_playerConfig.fighterslocked[1] = true;
    s_playerConfig.fighterslocked[2] = true;
    s_playerConfig.fighterslocked[3] = true;
    s_playerConfig.fighterslocked[4] = true;
    s_playerConfig.fighterslocked[5] = true;

    s_playerConfig.fighterslevel[0] = 0;
    s_playerConfig.fighterslevel[1] = 0;
    s_playerConfig.fighterslevel[2] = 0;
    s_playerConfig.fighterslevel[3] = 0;
    s_playerConfig.fighterslevel[4] = 0;
    s_playerConfig.fighterslevel[5] = 0;

    s_playerConfig.weaponlocked = true;
    s_playerConfig.weaponslevel[0] = 0;
    s_playerConfig.weaponslevel[1] = 0;
    s_playerConfig.weaponslevel[2] = 0;

    for (int i=0; i<MEDAL_MAX; ++i) {
    s_playerConfig.medallocked[i] = true;
    s_playerConfig.medalget[i] = false;
    }
    
    saveConfig();
}

void GameConfig::saveConfig()
{
    auto userDef = UserDefault::getInstance();
    userDef->setFloatForKey("music",s_playerConfig.musicVolume);
    userDef->setFloatForKey("sfx",s_playerConfig.sfxVolume);
    userDef->setIntegerForKey("language",int(s_playerConfig.language));
    //
    //    auto importantDataSize = sizeof(unsigned char) * (FIGHTER_MAX + FIGHTER_MAX + WEAPON_MAX + 1) * 2;
    //    auto importantData = (unsigned char*)malloc(importantDataSize);
    //    auto levelStartIndex = FIGHTER_MAX * 2;
    //    int index;
    //    for (int i = 0; i < FIGHTER_MAX; ++i)
    //    {
    //        index = 2 * i;
    //        importantData[index] = fightersLocked[i];
    //        importantData[index + 1] = rand();
    //
    //        importantData[levelStartIndex + index] = fightersLevle[i];
    //        importantData[levelStartIndex + index + 1] = rand();
    //    }
    //    auto weaponStartIndex = levelStartIndex * 2;
    //    for (int j = 0; j < WEAPON_MAX; ++j)
    //    {
    //        index = 2 * j;
    //        importantData[weaponStartIndex + index] = weaponsLevel[j];
    //        importantData[weaponStartIndex + index + 1] = rand();
    //    }
    //
    //    Data data;
    //    data.fastSet(importantData,importantDataSize);
    //
    //    userDef->setDataForKey("bw",data);
}


void GameConfig::setMusicVolume(float volume)
{
    UserDefault::getInstance()->setFloatForKey("music", volume);
}

void GameConfig::setSFXVolume(float volume)
{
    UserDefault::getInstance()->setFloatForKey("sfx", volume);
}

void GameConfig::setLanguage(GameLanguage languag)
{
    UserDefault::getInstance()->setFloatForKey("language", int(languag));
}


//写死数据
////////////////////////////////

StoneSpeed s_stoneSpeed[STONE_SPEED_LEVEL_MAX]=
{
    {4,500},{5,1000},{7,1800},{10,3500},{14,6200},
    {4,500},{5,1000},{7,1800},{10,3500},{14,6200},
    {4,500},{5,1000},{7,1800},{10,3500},{14,6200},
    {4,500},{5,1000},{7,1800},{10,3500},{14,6200}
};

StoneCapacity s_stoneCapacity[STONE_CAPACITY_LEVEL_MAX]=
{
    {200,1000,500},{3000,1200,1000},{400,1600,1800},{500,2200,1500},{700,3100,6200},
    {200,1000,500},{3000,1200,1000},{400,1600,1800},{500,2200,1500},{700,3100,6200},
    {200,1000,500},{3000,1200,1000},{400,1600,1800},{500,2200,1500},{700,3100,6200},
    {200,1000,500},{3000,1200,1000},{400,1600,1800},{500,2200,1500},{700,3100,6200}
};

PlainConfig s_plainConfigs[FIGHTER_MAX][FIGHTER_LEVEL_MAX] = {
    {//轻型战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程，buildtime, cd
        {100,100,100,  100,100,10,130,3,3},
        {100,100,100,  100,100,10,140,1,1},
        {100,100,100,  100,100,10,150,1,1},

        {100,100,100,  100,100,10,160,1,1},
        {100,100,100,  100,100,10,170,1,1},
        {100,100,100,  100,100,10,180,1,1},

        {100,100,100,  100,100,10,190,1,1},
        {100,100,100,  100,100,10,200,1,1},
        {100,100,100,  100,100,10,210,1,1},

        {100,100,100,  100,100,10,225,1,1},
        {100,100,100,  100,100,10,225,1,1},
        {100,100,100,  100,100,10,225,1,1},

        {100,100,100,  100,100,10,225,1,1},
        {100,100,100,  100,100,10,225,1,1},
        {100,100,100,  100,100,10,225,1,1}
    },
    {//合金甲战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,10,100,1,1},

        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,10,100,1,1},

        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,10,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1}
    },
    {//导弹战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1}
    },
    {//光束战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1}
    },
    {//磁力战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1}
    },
    {//黑色之翼，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {100,100,100,  100,100,10,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},

        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1},
        {100,100,100,  100,100,100,100,1,1}
    }
};
EnemyConfig s_enemyConfigs[ENEMY_MAX][ENEMY_LEVEL_MAX] = {
    {//1 生命，攻击，速度，防御，射程
        {100,100,100,  10,200},
        {100,100,100,  10,200},
        {100,100,100,  10,200},
        {100,100,100,  10,200},
        {100,100,100,  10,200},

        {100,100,100,  10,200},
        {100,100,100,  10,200},
        {100,100,100,  10,200},
        {100,100,100,  10,200},
        {100,100,100,  10,200}
    },
    {//2 生命，攻击，速度，防御，射程
        {100,100,100,  10,220},
        {100,100,100,  10,220},
        {100,100,100,  10,220},
        {100,100,100,  10,220},
        {100,100,100,  10,220},

        {100,100,100,  10,220},
        {100,100,100,  10,220},
        {100,100,100,  10,220},
        {100,100,100,  10,220},
        {100,100,100,  10,220}
    },
    {//3 生命，攻击，速度，防御，射程
        {100,100,100,  10,240},
        {100,100,100,  10,240},
        {100,100,100,  10,240},
        {100,100,100,  10,240},
        {100,100,100,  10,240},

        {100,100,100,  10,240},
        {100,100,100,  10,240},
        {100,100,100,  10,240},
        {100,100,100,  10,240},
        {100,100,100,  10,240}
    },
    {//4 生命，攻击，速度，防御，射程
        {100,100,100,  10,260},
        {100,100,100,  10,260},
        {100,100,100,  10,260},
        {100,100,100,  10,260},
        {100,100,100,  10,260},

        {100,100,100,  10,260},
        {100,100,100,  10,260},
        {100,100,100,  10,260},
        {100,100,100,  10,260},
        {100,100,100,  10,260}
    },
    {//5 生命，攻击，速度，防御，射程
        {100,100,100,  10,260},
        {100,100,100,  10,260},
        {100,100,100,  10,260},
        {100,100,100,  10,260},
        {100,100,100,  10,260},

        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100}
    },
    {//6 生命，攻击，速度，防御，射程
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},

        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100}
    },
    {//7 生命，攻击，速度，防御，射程
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},

        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100}
    },
    {//8 生命，攻击，速度，防御，射程
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},

        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100}
    },
    {//9 生命，攻击，速度，防御，射程
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},

        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100}
    },
    {//10 生命，攻击，速度，防御，射程
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},

        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100},
        {100,100,100,  10,100}
    }
};

EnemyConfig s_bossConfig[ENEMY_LEVEL_MAX] =
{
    //Boss 生命，攻击，速度，防御，射程
    {1000,100,100,  10,100},
    {100,100,100,  10,100},
    {100,100,100,  10,100},
    {100,100,100,  10,100},
    {100,100,100,  10,100},
    
    {100,100,100,  10,100},
    {100,100,100,  10,100},
    {100,100,100,  10,100},
    {100,100,100,  10,100},
    {100,100,100,  10,100}
};

EnemyConfig s_towerConfig[ENEMY_LEVEL_MAX]=
{
    //Tower 生命，攻击，速度，防御，射程
    {1000,100,0,  10,100},
    {100,100,0,  10,100},
    {100,100,0,  10,100},
    {100,100,0,  10,100},
    {100,100,0,  10,100},
    
    {100,100,0,  10,100},
    {100,100,0,  10,100},
    {100,100,0,  10,100},
    {100,100,0,  10,100},
    {100,100,0,  10,100}
};


WeaponConfig s_weaponConfigs[WEAPON_MAX][WEAPON_LEVEL_MAX] = {
    {//星际炸弹，购买所需宝石，升级所需宝石，攻击，持续时间（0.1s为单位），携带上限，攻击范围,cd
        {100,100,  100,1,100,100,1},
        {100,100,  100,1,100,100,1},
        {100,100,  100,1,100,100,1},
        {100,100,  100,1,100,100,1},
        {100,100,  100,1,100,100,1},

        {100,100,  100,1,100,100,1},
        {100,100,  100,1,100,100,1},
        {100,100,  100,1,100,100,1},
        {100,100,  100,1,100,100,1},
        {100,100,  100,1,100,100,1}
    },
    {//激光发射器，购买所需宝石，升级所需宝石，攻击，持续时间（0.1s为单位），携带上限，攻击范围
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},

        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1}
    },
    {////黑洞，购买所需宝石，升级所需宝石，攻击，持续时间（0.1s为单位），携带上限，攻击范围
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},

        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1},
        {100,100,  100,100,100,100,1}
    }
};

//勋章奖励：宝石，星际炸弹，激光，黑洞（宝石必须有，后者3选1）
int s_medalRewards[MEDAL_MAX][MEDAL_REWARDS_COUNT]=
{
    {300, 0, 0, 0},
    {1000, 2, 0, 0},
    {6000, 2, 0, 0},
    {12000, 5, 0, 0},
    {50000, 0, 2, 0},
    {100000, 8, 0, 0},
    {5000, 0, 0, 0},
    {10000, 0, 0, 0},
    {50000, 0, 0, 0},
    {100000, 0, 0, 0},
    {500000, 0, 0, 0},
    {10000, 0, 2, 0},
    {60000, 0, 0, 3},
    {7000, 0, 2, 0},
    {35000, 0, 0, 3},
    {50000, 0, 0, 2},
    {100000, 0, 0, 3},
    {250000, 0, 0, 3},
    {500000, 0, 0, 3},
    {100000, 0, 0, 0},
    {200000, 0, 0, 0},
    {400000, 0, 2, 0},
    {650000, 0, 3, 0},
    {900000, 0, 0, 3},
    {1200000, 0, 0, 3}
};

//关卡奖励：宝石，星际炸弹，激光，黑洞（宝石必须有，后者3选1）
int s_stageRewards[STAGE_COUNT][STAGE_REWAEDS_COUNT]=
{
    {300, 0, 0, 0},
    {1000, 2, 0, 0},
    {6000, 2, 0, 0},
    {12000, 5, 0, 0},
    {50000, 0, 2, 0},
    {100000, 8, 0, 0},
    {5000, 0, 0, 0},
    {10000, 0, 0, 0},
    {50000, 0, 0, 0},
    {100000, 0, 0, 0},
    {500000, 0, 0, 0},
    {10000, 0, 2, 0},
    {60000, 0, 0, 3},
    {7000, 0, 2, 0},
    {35000, 0, 0, 3},
    {50000, 0, 0, 2},
    {100000, 0, 0, 3},
    {250000, 0, 0, 3},
    {500000, 0, 0, 3},
    {100000, 0, 0, 0},
    {200000, 0, 0, 0},
    {400000, 0, 2, 0},
    {650000, 0, 3, 0},
    {900000, 0, 0, 3},
    {1200000, 0, 0, 3},
    {300, 0, 0, 0},
    {1000, 2, 0, 0},
    {6000, 2, 0, 0},
    {12000, 5, 0, 0},
    {50000, 0, 2, 0},
    {100000, 8, 0, 0},
    {5000, 0, 0, 0},
    {10000, 0, 0, 0},
    {50000, 0, 0, 0},
    {100000, 0, 0, 0},
    {500000, 0, 0, 0},
    {10000, 0, 2, 0},
    {60000, 0, 0, 3},
    {7000, 0, 2, 0},
    {35000, 0, 0, 3},
    {50000, 0, 0, 2},
    {100000, 0, 0, 3},
    {250000, 0, 0, 3},
    {500000, 0, 0, 3},
    {100000, 0, 0, 0},
    {200000, 0, 0, 0},
    {400000, 0, 2, 0},
    {650000, 0, 3, 0},
    {900000, 0, 0, 3},
    {1200000, 0, 0, 3}
};


//每关敌人基地血量
int s_enemyBaseBlood[STAGE_COUNT]=
{
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000
};

//每关玩家基地血量
int s_playerBaseBlood[STAGE_COUNT]=
{
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000,
    1000, 2000, 3000, 4000, 5000
};

cocos2d::Point s_EnemyBasePos;
cocos2d::Point s_PlayerBasePos;

//普通敌人出兵配置
BattleNormalEnemyInfo s_battleNormalEnemyInfo[2]=
{
    {s_battleNormalEnemyConfig_0, STAGE_ENEMY_WAVES_00},
    {s_battleNormalEnemyConfig_1, STAGE_ENEMY_WAVES_01}
};

//时间间隔，类型，等级，数量
BattleNormalEnemyConfig s_battleNormalEnemyConfig_0[STAGE_ENEMY_WAVES_00] =
{
    {2,1,2,1},
    {5,3,2,2},
    {2,4,5,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_1[STAGE_ENEMY_WAVES_01] =
{
    {2,1,2,1},
    {5,3,2,2}
};

//炮塔配置
BattleTowerEnemyInfo s_battleTowerEnemyInfo[1]=
{
    {s_battleTowerEnemyConfig_0, STAGE_TOWER_COUNTS_00}
};

//等级，x，y
BattleTowerEnemyConfig s_battleTowerEnemyConfig_0[STAGE_TOWER_COUNTS_00] =
{
//    {2,300,1300},
    {0,400,1800}
};

//Boss配置
BattleBossEnemyInfo s_battleBossEnemyInfo[STAGE_COUNT] =
{
    //等级，出现时间间隔
    {0,10},{2,10},{3,10},{4,10},{5,10},
    {1,10},{2,10},{3,10},{4,10},{5,10},
    {1,10},{2,10},{3,10},{4,10},{5,10},
    {1,10},{2,10},{3,10},{4,10},{5,10},
    {1,10},{2,10},{3,10},{4,10},{5,10},
    {1,10},{2,10},{3,10},{4,10},{5,10},
    {1,10},{2,10},{3,10},{4,10},{5,10},
    {1,10},{2,10},{3,10},{4,10},{5,10},
    {1,10},{2,10},{3,10},{4,10},{5,10},
    {1,10},{2,10},{3,10},{4,10},{5,10}
};


