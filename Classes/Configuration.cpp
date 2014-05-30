#include "Configuration.h"
#include "GameStrings.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"

GameConfig s_gameConfig;

const std::string GameConfig::defaultFontName = "Arial";
const int GameConfig::defaultFontSize = 30;

const std::string GameConfig::eventLanguageChange = "eventLanguageChange";
const std::string GameConfig::eventPlayerDestroy = "eventPlayerDestroy";

void GameConfig::lazyInit()
{
    s_visibleRect.lazyInit();
    initMedalRewards();

    auto userDef = UserDefault::getInstance();
    musicVolume = userDef->getFloatForKey("music",1.0f);
    sfxVolume = userDef->getFloatForKey("sfx",1.0f);
    language = userDef->getIntegerForKey("language",int(GameLanguage::English));

    auto data = userDef->getDataForKey("bw",Data::Null);
    if (data.isNull())
    {
        fightersLocked[0] = false;
        fightersLocked[1] = true;
        fightersLocked[2] = true;
        fightersLocked[3] = true;
        fightersLocked[4] = true;
        fightersLocked[5] = true;

        fightersLevle[0] = 0;
        fightersLevle[1] = 0;
        fightersLevle[2] = 0;
        fightersLevle[3] = 0;
        fightersLevle[4] = 0;
        fightersLevle[5] = 0;

        weaponLocked = true;
        weaponsLevel[0] = 0;
        weaponsLevel[1] = 0;
        weaponsLevel[2] = 0;
        
        for (int i=0; i<MEDAL_MAX; ++i) {
            medal_lock[i] = true;
            medal_get[i] = false;
        }
        
        treasure.money = 1000;
        treasure.starboom = 1;
        treasure.laser = 1;
        treasure.blackhole = 1;
        treasure.killEnemy = 0;
        treasure.usedSpcWeapon = 0;
        treasure.overStage = 0;
        treasure.killBigEnemy = 0;
        treasure.firstKill = false;
        treasure.unlockAllFighter = false;
    }
    else
    {
        auto data = userDef->getDataForKey("bw");
        auto importantData = data.getBytes();
        auto levelStartIndex = FIGHTER_MAX * 2;
        int index;
        for (int i = 0; i < FIGHTER_MAX; ++i)
        {
            index = 2 * i;
            fightersLocked[i] = importantData[index];
            fightersLevle[i] = importantData[levelStartIndex + index];
        }
        auto weaponStartIndex = levelStartIndex * 2;
        for (int j = 0; j < WEAPON_MAX; ++j)
        {
            index = 2 * j;
            weaponsLevel[j] = importantData[weaponStartIndex + index];
        }
    }
    

    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(musicVolume);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(sfxVolume);
    GSMainMenuInit((GameLanguage)language);
}

void GameConfig::saveConfig()
{
    auto userDef = UserDefault::getInstance();
    userDef->setFloatForKey("music",musicVolume);
    userDef->setFloatForKey("sfx",sfxVolume);
    userDef->setIntegerForKey("language",int(language));

    auto importantDataSize = sizeof(unsigned char) * (FIGHTER_MAX + FIGHTER_MAX + WEAPON_MAX + 1) * 2;
    auto importantData = (unsigned char*)malloc(importantDataSize);
    auto levelStartIndex = FIGHTER_MAX * 2;
    int index;
    for (int i = 0; i < FIGHTER_MAX; ++i)
    {
        index = 2 * i;
        importantData[index] = fightersLocked[i];
        importantData[index + 1] = rand();
        
        importantData[levelStartIndex + index] = fightersLevle[i];
        importantData[levelStartIndex + index + 1] = rand();
    }
    auto weaponStartIndex = levelStartIndex * 2;
    for (int j = 0; j < WEAPON_MAX; ++j)
    {
        index = 2 * j;
        importantData[weaponStartIndex + index] = weaponsLevel[j];
        importantData[weaponStartIndex + index + 1] = rand();
    }

    Data data;
    data.fastSet(importantData,importantDataSize);

    userDef->setDataForKey("bw",data);
}

void GameConfig::setMusicVolume(float volume)
{
    UserDefault::getInstance()->setFloatForKey("music", volume);
}

void GameConfig::setSFXVolume(float volume)
{
    UserDefault::getInstance()->setFloatForKey("sfx", volume);
}

void GameConfig::initMedalRewards()
{
    medal_reward_callbacks[0]=[&](){treasure.money+=300;};
    medal_reward_callbacks[1]=[&](){treasure.money+=1000; treasure.starboom+=2;};
    medal_reward_callbacks[2]=[&](){treasure.money+=6000; treasure.starboom+=2;};
    medal_reward_callbacks[3]=[&](){treasure.money+=12000; treasure.starboom+=5;};
    medal_reward_callbacks[4]=[&](){treasure.money+=50000; treasure.laser+=2;};
    medal_reward_callbacks[5]=[&](){treasure.money+=100000; treasure.starboom+=8;};
    medal_reward_callbacks[6]=[&](){treasure.money+=5000;};
    medal_reward_callbacks[7]=[&](){treasure.money+=10000;};
    medal_reward_callbacks[8]=[&](){treasure.money+=50000;};
    medal_reward_callbacks[9]=[&](){treasure.money+=100000;};
    medal_reward_callbacks[10]=[&](){treasure.money+=500000;};
    medal_reward_callbacks[11]=[&](){treasure.money+=10000; treasure.laser+=2;};
    medal_reward_callbacks[12]=[&](){treasure.money+=60000; treasure.blackhole+=3;};
    medal_reward_callbacks[13]=[&](){treasure.money+=7000; treasure.laser+=2;};
    medal_reward_callbacks[14]=[&](){treasure.money+=35000; treasure.blackhole+=3;};
    medal_reward_callbacks[15]=[&](){treasure.money+=50000; treasure.blackhole+=2;};
    medal_reward_callbacks[16]=[&](){treasure.money+=100000; treasure.blackhole+=3;};
    medal_reward_callbacks[17]=[&](){treasure.money+=250000; treasure.blackhole+=3;};
    medal_reward_callbacks[18]=[&](){treasure.money+=500000; treasure.blackhole+=3;};
    medal_reward_callbacks[19]=[&](){treasure.money+=100000;};
    medal_reward_callbacks[20]=[&](){treasure.money+=200000;};
    medal_reward_callbacks[21]=[&](){treasure.money+=400000; treasure.laser+=2;};
    medal_reward_callbacks[22]=[&](){treasure.money+=650000; treasure.laser+=3;};
    medal_reward_callbacks[23]=[&](){treasure.money+=900000; treasure.blackhole+=3;};
    medal_reward_callbacks[24]=[&](){treasure.money+=1200000;treasure.blackhole+=3;};
}

PlainConfig s_plainConfigs[FIGHTER_MAX][FIGHTER_LEVEL_MAX] = {
    {//«·–Õ’Ωª˙£∫ Ω®…ËÀ˘–Ëæß Ø,…˝º∂À˘–Ë±¶ Ø,…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
        {100,100,100,  100,100,10,130},
        {100,100,100,  100,100,10,140},
        {100,100,100,  100,100,10,150},

        {100,100,100,  100,100,10,160},
        {100,100,100,  100,100,10,170},
        {100,100,100,  100,100,10,180},

        {100,100,100,  100,100,10,190},
        {100,100,100,  100,100,10,200},
        {100,100,100,  100,100,10,210},

        {100,100,100,  100,100,10,225},
        {100,100,100,  100,100,10,225},
        {100,100,100,  100,100,10,225},

        {100,100,100,  100,100,10,225},
        {100,100,100,  100,100,10,225},
        {100,100,100,  100,100,10,225}
    },
    {//∫œΩº◊’Ωª˙£∫ Ω®…ËÀ˘–Ëæß Ø,…˝º∂À˘–Ë±¶ Ø,…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,10,100},

        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,10,100},

        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,10,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100}
    },
    {//µºµØ’Ωª˙£∫ Ω®…ËÀ˘–Ëæß Ø,…˝º∂À˘–Ë±¶ Ø,…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100}
    },
    {//π‚ ¯’Ωª˙£∫ Ω®…ËÀ˘–Ëæß Ø,…˝º∂À˘–Ë±¶ Ø,…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100}
    },
    {//¥≈¡¶’Ωª˙£∫ Ω®…ËÀ˘–Ëæß Ø,…˝º∂À˘–Ë±¶ Ø,…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100}
    },
    {//∫⁄…´÷Æ“Ì£∫ Ω®…ËÀ˘–Ëæß Ø,…˝º∂À˘–Ë±¶ Ø,…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
        {100,100,100,  100,100,10,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},

        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100},
        {100,100,100,  100,100,100,100}
    }
};
EnemyConfig s_enemyConfigs[ENEMY_MAX][ENEMY_LEVEL_MAX] = {
    {//1 …˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
    {//2…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
    {//3…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
    {//4…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
    {//5…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
    {//6…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
    {//7…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
    {//8…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
    {//9…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
    {//10…˙√¸£¨π•ª˜£¨ÀŸ∂»£¨∑¿”˘£¨…‰≥Ã
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
WeaponConfig s_weaponConfigs[WEAPON_MAX][WEAPON_LEVEL_MAX] = {
    {//–«º ’®µØ£∫π∫¬ÚÀ˘–Ë±¶ Ø£¨…˝º∂À˘–Ë±¶ Ø,π•ª˜,≥÷–¯ ±º‰,–Ø¥¯…œœﬁ
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},

        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100}
    },
    {//º§π‚∑¢…‰∆˜£∫π∫¬ÚÀ˘–Ë±¶ Ø£¨…˝º∂À˘–Ë±¶ Ø,π•ª˜,≥÷–¯ ±º‰,–Ø¥¯…œœﬁ
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},

        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100}
    },
    {//∫⁄∂¥£∫π∫¬ÚÀ˘–Ë±¶ Ø£¨…˝º∂À˘–Ë±¶ Ø,π•ª˜,≥÷–¯ ±º‰,–Ø¥¯…œœﬁ
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},

        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100},
        {100,100,  100,100,100}
    }
};

//钱，星际炸弹，激光，黑洞
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