#include "Configuration.h"
#include "GameStrings.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"
#include "ConfigManager.h"

GameConfig s_gameConfig;
PlayerConfig s_playerConfig;

const std::string GameConfig::defaultFontName = "DS-Digital.ttf";//"Arial";
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
const std::string GameConfig::eventunseletedall = "eventunseletedall";
const std::string GameConfig::eventUpdateBaseData = "eventUpdateBaseData";
const std::string GameConfig::eventUpdateMenuItemFlightData = "eventUpdateMenuItemFlightData";
const std::string GameConfig::eventUpdateMenuItemWeaponData = "eventUpdateMenuItemWeaponData";
const std::string GameConfig::eventUpdateGem = "eventUpdateGem";
const std::string GameConfig::eventShowWeaponMenu = "eventShowWeaponMenu";
const std::string GameConfig::eventShowHideMedalLogo = "eventShowHideMedalLogo";
const std::string GameConfig::eventFlightAvaliable = "eventFlightAvaliable";
const std::string GameConfig::eventWeaponAvaliable = "eventWeaponAvaliable";


void GameConfig::lazyInit()
{
    s_visibleRect.lazyInit();
    
    isInBattle = false;
    
    ConfigManager::getInstance()->readConfig();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(s_playerConfig.musicVolume);
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

void GameConfig::setMusicVolume(float volume)
{
    ConfigManager::getInstance()->saveMusicVolume(volume);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

void GameConfig::setSFXVolume(float volume)
{
    ConfigManager::getInstance()->saveSFXVolume(volume);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
}

//void GameConfig::readConfig()
//{
//    //todo
//    
//    auto userDef = UserDefault::getInstance();
//    
//    s_playerConfig.musicVolume = userDef->getFloatForKey("music",1.0f);
//    s_playerConfig.sfxVolume = userDef->getFloatForKey("sfx",1.0f);
//    s_playerConfig.language = userDef->getIntegerForKey("language",int(GameLanguage::English));
//    
// 
//    // initConfig();
//    
//    auto data = userDef->getDataForKey("bw",Data::Null);
//    if (data.isNull())
//    {
//        initConfig();
//    }
//    else
//    {
//        //todo:把配置读入s_playerConfig
//        
//        auto importantData = data.getBytes();
//        auto levelStartIndex = FIGHTER_MAX * 2;
//        int index;
//        for (int i = 0; i < FIGHTER_MAX; ++i)
//        {
//            index = 2 * i;
//            s_playerConfig.fighterslocked[i] = importantData[index];
//            s_playerConfig.fighterslevel[i] = importantData[levelStartIndex + index];
//        }
//        auto weaponStartIndex = FIGHTER_MAX * 4;
//        for (int j = 0; j < WEAPON_MAX; ++j)
//        {
//            index = 2 * j;
//            s_playerConfig.weaponslevel[j] = importantData[weaponStartIndex + index];
//        }
//        
//        auto medallockedIndex = weaponStartIndex + WEAPON_MAX * 2;
//        
//        for (int i = 0; i < MEDAL_MAX; ++i)
//        {
//            index = 4 * i;
//            s_playerConfig.medallocked[i] = importantData[medallockedIndex + index];
//            s_playerConfig.medalget[i] = importantData[medallockedIndex + index + 2];
//        }
//        
//        auto otherDataIndex = medallockedIndex + MEDAL_MAX * 4;
//        for (int i = 0; i < OTHER_DATA; ++i)
//        {
//            index = 2 * i;
//            
//            switch (i)
//            {
//                case 0:
//                    s_playerConfig.musicVolume = importantData[otherDataIndex+index];
//                    break;
//                case 1:
//                    s_playerConfig.sfxVolume = importantData[otherDataIndex+index];
//                    break;
//                case 2:
//                    s_playerConfig.language = importantData[otherDataIndex+index];
//                    log("%d",s_playerConfig.language);
//                    break;
//                case 3:
//                    s_playerConfig.stone = importantData[otherDataIndex+index];
//                    break;
//                case 4:
//                    s_playerConfig.stoneMax = importantData[otherDataIndex+index];
//                    break;
//                case 5:
//                    s_playerConfig.gem = importantData[otherDataIndex+index];
//                    break;
//                case 6:
//                    s_playerConfig.weaponCount[0] = importantData[otherDataIndex+index];
//                    break;
//                case 7:
//                    s_playerConfig.weaponCount[1] = importantData[otherDataIndex+index];
//                    break;
//                case 8:
//                    s_playerConfig.weaponCount[2] = importantData[otherDataIndex+index];
//                    break;
//                case 9:
//                    s_playerConfig.killenemy = importantData[otherDataIndex+index];
//                    break;
//                case 10:
//                    s_playerConfig.usedweapon = importantData[otherDataIndex+index];
//                    break;
//                case 11:
//                    s_playerConfig.overstage = importantData[otherDataIndex+index];
//                    break;
//                case 12:
//                    s_playerConfig.killbigenemy = importantData[otherDataIndex+index];
//                    break;
//                case 13:
//                    s_playerConfig.firstkill = importantData[otherDataIndex+index];
//                    break;
//                case 14:
//                    s_playerConfig.unlockallfighter = importantData[otherDataIndex+index];
//                    break;
//                case 15:
//                    s_playerConfig.stonespeedlevel = importantData[otherDataIndex+index];
//                    break;
//                    
//                case 16:
//                    s_playerConfig.stonecapacitylevel = importantData[otherDataIndex+index];
//                    
//                default:
//                    break;
//            }
//            
//        }
//    }
//    
//
// 
//    
//
//}

//void GameConfig::initConfig()
//{
//    s_playerConfig.musicVolume = 1.0f;
//    s_playerConfig.sfxVolume = 1.0f;
//    s_playerConfig.language = (int)GameLanguage::Chinese;
//    
//    s_playerConfig.stone = 200;
//    s_playerConfig.stoneMax = 1000;
//    s_playerConfig.gem = 1000000;
//    s_playerConfig.weaponCount[0] = 20;
//    s_playerConfig.weaponCount[1] = 20;
//    s_playerConfig.weaponCount[2] = 20;
//    s_playerConfig.usedweapon = 0;
//    s_playerConfig.overstage = 0;
//    s_playerConfig.killbigenemy = 0;
//    s_playerConfig.firstkill = false;
//    s_playerConfig.unlockallfighter = false;
//    s_playerConfig.stonespeedlevel = 18;
//    s_playerConfig.stonecapacitylevel = 18;
//    
//    s_playerConfig.fighterslocked[0] = false;
//    s_playerConfig.fighterslocked[1] = false;
//    s_playerConfig.fighterslocked[2] = false;
//    s_playerConfig.fighterslocked[3] = false;
//    s_playerConfig.fighterslocked[4] = true;
//    s_playerConfig.fighterslocked[5] = true;
//
//    s_playerConfig.fighterslevel[0] = 13;
//    s_playerConfig.fighterslevel[1] = 0;
//    s_playerConfig.fighterslevel[2] = 0;
//    s_playerConfig.fighterslevel[3] = 0;
//    s_playerConfig.fighterslevel[4] = 0;
//    s_playerConfig.fighterslevel[5] = 0;
//
//    s_playerConfig.weaponlocked = true;
//    s_playerConfig.weaponslevel[0] = 0;
//    s_playerConfig.weaponslevel[1] = 8;
//    s_playerConfig.weaponslevel[2] = 0;
//
//    for (int i=0; i<MEDAL_MAX; ++i)
//    {
//        s_playerConfig.medallocked[i] = true;
//        s_playerConfig.medalget[i] = false;
//    }
//    
//    saveConfig();
//}

//void GameConfig::saveConfig()
//{
//    auto userDef = UserDefault::getInstance();
//    
//    userDef->setFloatForKey("music",s_playerConfig.musicVolume);
//    userDef->setFloatForKey("sfx",s_playerConfig.sfxVolume);
//
//    userDef->setIntegerForKey("language",int(s_playerConfig.language));
//    
//    
//    auto importantDataSize = sizeof(unsigned char) * (FIGHTER_MAX * 2 + WEAPON_MAX + MEDAL_MAX * 2 + OTHER_DATA) * 2;
//    auto importantData = (unsigned char*)malloc(importantDataSize);
//    auto levelStartIndex = FIGHTER_MAX * 2;
//    int index;
//    for (int i = 0; i < FIGHTER_MAX; ++i)
//    {
//        index = 2 * i;
//        importantData[index] = s_playerConfig.fighterslocked[i];
//        importantData[index + 1] = rand();
//        
//        importantData[levelStartIndex + index] = s_playerConfig.fighterslevel[i];
//        importantData[levelStartIndex + index + 1] = rand();
//    }
//    auto weaponStartIndex = FIGHTER_MAX * 4;
//    for (int j = 0; j < WEAPON_MAX; ++j)
//    {
//        index = 2 * j;
//        importantData[weaponStartIndex + index] = s_playerConfig.weaponslevel[j];
//        importantData[weaponStartIndex + index + 1] = rand();
//    }
//    
//    auto medallockedIndex = weaponStartIndex + WEAPON_MAX * 2;
//    
//    for (int i = 0; i < MEDAL_MAX; ++i)
//    {
//        index = 4 * i;
//        importantData[medallockedIndex + index] =  s_playerConfig.medallocked[i];
//        importantData[medallockedIndex + index + 1] = rand();
//        
//        importantData[medallockedIndex + index + 2] = s_playerConfig.medalget[i];
//        importantData[medallockedIndex + index + 3] = rand();
//    }
//    
//    auto otherDataIndex = medallockedIndex + MEDAL_MAX * 4;
//    for (int i = 0; i < OTHER_DATA; ++i)
//    {
//        index = 2 * i;
//        
//        switch (i)
//        {
//            case 0:
//                importantData[otherDataIndex + index] = s_playerConfig.musicVolume;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 1:
//                importantData[otherDataIndex + index] = s_playerConfig.sfxVolume;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 2:
//                log("%d",s_playerConfig.language);
//                importantData[otherDataIndex + index] = s_playerConfig.language;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 3:
//                importantData[otherDataIndex + index] = s_playerConfig.stone;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 4:
//                importantData[otherDataIndex + index] = s_playerConfig.stoneMax;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 5:
//                importantData[otherDataIndex + index] = s_playerConfig.gem;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 6:
//                importantData[otherDataIndex + index] = s_playerConfig.weaponCount[0];
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 7:
//                importantData[otherDataIndex + index] = s_playerConfig.weaponCount[1];
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 8:
//                importantData[otherDataIndex + index] = s_playerConfig.weaponCount[2];
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 9:
//                importantData[otherDataIndex + index] = s_playerConfig.killenemy;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 10:
//                importantData[otherDataIndex + index] = s_playerConfig.usedweapon;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 11:
//                importantData[otherDataIndex + index] = s_playerConfig.overstage;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 12:
//                importantData[otherDataIndex + index] = s_playerConfig.killbigenemy;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 13:
//                importantData[otherDataIndex + index] = s_playerConfig.firstkill;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 14:
//                importantData[otherDataIndex + index] = s_playerConfig.unlockallfighter;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//            case 15:
//                importantData[otherDataIndex + index] = s_playerConfig.stonespeedlevel;
//                importantData[otherDataIndex + index + 1] = rand();
//                break;
//                
//            case 16:
//                importantData[otherDataIndex + index] =  s_playerConfig.stonecapacitylevel;
//                importantData[otherDataIndex + index + 1] = rand();
//                
//            default:
//                break;
//        }
//        
//    }
//    
//    Data data;
//    data.fastSet(importantData,importantDataSize);
//    
//    userDef->setDataForKey("bw",data);
//}


//写死数据
////////////////////////////////

//解锁飞机的关卡(从0开始)，第一架默认解锁
int s_UnlockflightStage[6]=
{
    0,1,2,3,4,5
};

StoneSpeed s_stoneSpeed[STONE_SPEED_LEVEL_MAX]=
{
    {20,500},{5,1000},{7,1800},{10,3500},{14,6200},//1
    {4,500},{5,1000},{7,1800},{10,3500},{14,6200},//2
    {4,500},{5,1000},{7,1800},{10,3500},{14,6200},//3
    {4,500},{5,1000},{7,1800},{100,3500},{14,6200}//4
};

StoneCapacity s_stoneCapacity[STONE_CAPACITY_LEVEL_MAX]=
{
    {200,1000,500},{3000,1200,1000},{400,1600,1800},{500,2200,1500},{700,3100,6200},//1
    {200,1000,500},{3000,1200,1000},{400,1600,1800},{500,2200,1500},{700,3100,6200},//2
    {200,1000,500},{3000,1200,1000},{400,1600,1800},{500,2200,1500},{700,3100,6200},//3
    {200,1000,500},{3000,1200,1000},{400,1600,1800},{500,2200,1500},{700,3100,6200}//4
};

PlainConfig s_plainConfigs[FIGHTER_MAX][FIGHTER_LEVEL_MAX] = {
    {//轻型战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程，buildtime, cd
        {100,100,100,  100,100,10,130,3,3},//1
        {100,100,100,  100,100,10,140,1,1},//2
        {100,100,100,  100,100,10,150,1,1},//3

        {100,100,100,  100,100,10,160,1,1},//4
        {100,100,100,  100,100,10,170,1,1},//5
        {100,100,100,  100,100,10,180,1,1},//6

        {100,100,100,  100,100,10,190,1,1},//7
        {100,100,100,  100,100,10,200,1,1},//8
        {100,100,100,  100,100,10,210,1,1},//9

        {100,100,100,  100,100,10,225,1,1},//10
        {100,100,100,  100,100,10,225,1,1},//11
        {100,100,100,  100,100,10,225,1,1},//12

        {100,100,100,  100,100,10,225,1,1},//13
        {100,100,100,  100,100,10,225,1,1},//14
        {100,100,100,  100,100,10,225,1,1}//15
    },
    {//合金甲战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {200,200,100,  100,100,10,100,1,1},//1
        {100,100,100,  100,100,10,100,1,1},//2
        {100,100,100,  100,100,10,100,1,1},//3

        {100,100,100,  100,100,10,100,1,1},//4
        {100,100,100,  100,100,10,100,1,1},//5
        {100,100,100,  100,100,10,100,1,1},//6

        {100,100,100,  100,100,10,100,1,1},//7
        {100,100,100,  100,100,10,100,1,1},//8
        {100,100,100,  100,100,10,100,1,1},//9

        {100,100,100,  100,100,100,100,1,1},//10
        {100,100,100,  100,100,100,100,1,1},//11
        {100,100,100,  100,100,100,100,1,1},//12

        {100,100,100,  100,100,100,100,1,1},//13
        {100,100,100,  100,100,100,100,1,1},//14
        {100,100,100,  100,100,100,100,1,1}//15
    },
    {//导弹战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {300,300,100,  100,100,10,100,1,1},//1
        {100,100,100,  100,100,100,100,1,1},//2
        {100,100,100,  100,100,100,100,1,1},//3

        {100,100,100,  100,100,100,100,1,1},//4
        {100,100,100,  100,100,100,100,1,1},//5
        {100,100,100,  100,100,100,100,1,1},//6

        {100,100,100,  100,100,100,100,1,1},//7
        {100,100,100,  100,100,100,100,1,1},//8
        {100,100,100,  100,100,100,100,1,1},//9

        {100,100,100,  100,100,100,100,1,1},//10
        {100,100,100,  100,100,100,100,1,1},//11
        {100,100,100,  100,100,100,100,1,1},//12

        {100,100,100,  100,100,100,100,1,1},//13
        {100,100,100,  100,100,100,100,1,1},//14
        {100,100,100,  100,100,100,100,1,1}//15
    },
    {//光束战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {400,400,100,  100,100,10,100,1,1},//1
        {100,100,100,  100,100,100,100,1,1},//2
        {100,100,100,  100,100,100,100,1,1},//3

        {100,100,100,  100,100,100,100,1,1},//4
        {100,100,100,  100,100,100,100,1,1},//5
        {100,100,100,  100,100,100,100,1,1},//6

        {100,100,100,  100,100,100,100,1,1},//7
        {100,100,100,  100,100,100,100,1,1},//8
        {100,100,100,  100,100,100,100,1,1},//9

        {100,100,100,  100,100,100,100,1,1},//10
        {100,100,100,  100,100,100,100,1,1},//11
        {100,100,100,  100,100,100,100,1,1},//12

        {100,100,100,  100,100,100,100,1,1},//13
        {100,100,100,  100,100,100,100,1,1},//14
        {100,100,100,  100,100,100,100,1,1}//15
    },
    {//磁力战机，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {100,400,100,  100,100,10,100,1,1},//1
        {100,100,100,  100,100,100,100,1,1},//2
        {100,100,100,  100,100,100,100,1,1},//3

        {100,100,100,  100,100,100,100,1,1},//4
        {100,100,100,  100,100,100,100,1,1},//5
        {100,100,100,  100,100,100,100,1,1},//6

        {100,100,100,  100,100,100,100,1,1},//7
        {100,100,100,  100,100,100,100,1,1},//8
        {100,100,100,  100,100,100,100,1,1},//9

        {100,100,100,  100,100,100,100,1,1},//10
        {100,100,100,  100,100,100,100,1,1},//11
        {100,100,100,  100,100,100,100,1,1},//12

        {100,100,100,  100,100,100,100,1,1},//13
        {100,100,100,  100,100,100,100,1,1},//14
        {100,100,100,  100,100,100,100,1,1}//15
    },
    {//黑色之翼，建设所需的晶石，升级所需宝石，生命，攻击，速度，防御，射程
        {100,100,100,  100,100,10,100,1,1},//1
        {100,100,100,  100,100,100,100,1,1},//2
        {100,100,100,  100,100,100,100,1,1},//3

        {100,100,100,  100,100,100,100,1,1},//4
        {100,100,100,  100,100,100,100,1,1},//5
        {100,100,100,  100,100,100,100,1,1},//6

        {100,100,100,  100,100,100,100,1,1},//7
        {100,100,100,  100,100,100,100,1,1},//8
        {100,100,100,  100,100,100,100,1,1},//9

        {100,100,100,  100,100,100,100,1,1},//10
        {100,100,100,  100,100,100,100,1,1},//11
        {100,100,100,  100,100,100,100,1,1},//12

        {100,100,100,  100,100,100,100,1,1},//13
        {100,100,100,  100,100,100,100,1,1},//14
        {100,100,100,  100,100,100,100,1,1}//15
    }
};
EnemyConfig s_enemyConfigs[ENEMY_MAX][ENEMY_LEVEL_MAX] = {
    {//1 生命，攻击，速度，防御，射程，死亡丢失晶石，死亡丢失宝石
        {100,100,100,  10,200,20,10},//1
        {100,100,100,  10,200,20,10},//2
        {100,100,100,  10,200,20,10},//3
        {100,100,100,  10,200,20,10},//4
        {100,100,100,  10,200,20,10},//5

        {100,100,100,  10,200,20,10},//6
        {100,100,100,  10,200,20,10},//7
        {100,100,100,  10,200,20,10},//8
        {100,100,100,  10,200,20,10},//9
        {100,100,100,  10,200,20,10}//10
    },
    {//2 生命，攻击，速度，防御，射程
        {100,100,100,  10,220,20,10},//1
        {100,100,100,  10,220,20,10},//2
        {100,100,100,  10,220,20,10},//3
        {100,100,100,  10,220,20,10},//4
        {100,100,100,  10,220,20,10},//5

        {100,100,100,  10,220,20,10},//6
        {100,100,100,  10,220,20,10},//7
        {100,100,100,  10,220,20,10},//8
        {100,100,100,  10,220,20,10},//9
        {100,100,100,  10,220,20,10}//10
    },
    {//3 生命，攻击，速度，防御，射程
        {100,100,100,  10,240,20,10},//1
        {100,100,100,  10,240,20,10},//2
        {100,100,100,  10,240,20,10},//3
        {100,100,100,  10,240,20,10},//3
        {100,100,100,  10,240,20,10},//4

        {100,100,100,  10,240,20,10},//5
        {100,100,100,  10,240,20,10},//6
        {100,100,100,  10,240,20,10},//7
        {100,100,100,  10,240,20,10},//8
        {100,100,100,  10,240,20,10}//9
    },
    {//4 生命，攻击，速度，防御，射程
        {100,100,100,  10,260,20,10},//1
        {100,100,100,  10,260,20,10},//2
        {100,100,100,  10,260,20,10},//3
        {100,100,100,  10,260,20,10},//4
        {100,100,100,  10,260,20,10},//5

        {100,100,100,  10,260,20,10},//6
        {100,100,100,  10,260,20,10},//7
        {100,100,100,  10,260,20,10},//8
        {100,100,100,  10,260,20,10},//9
        {100,100,100,  10,260,20,10}//10
    },
    {//5 生命，攻击，速度，防御，射程
        {100,100,100,  10,260,20,10},//1
        {100,100,100,  10,260,20,10},//2
        {100,100,100,  10,260,20,10},//3
        {100,100,100,  10,260,20,10},//4
        {100,100,100,  10,260,20,10},//5

        {100,100,100,  10,100,20,10},//6
        {100,100,100,  10,100,20,10},//7
        {100,100,100,  10,100,20,10},//8
        {100,100,100,  10,100,20,10},//9
        {100,100,100,  10,100,20,10}//10
    },
    {//6 生命，攻击，速度，防御，射程
        {100,100,100,  10,100,20,10},//1
        {100,100,100,  10,100,20,10},//2
        {100,100,100,  10,100,20,10},//3
        {100,100,100,  10,100,20,10},//4
        {100,100,100,  10,100,20,10},//5

        {100,100,100,  10,100,20,10},//6
        {100,100,100,  10,100,20,10},//7
        {100,100,100,  10,100,20,10},//8
        {100,100,100,  10,100,20,10},//9
        {100,100,100,  10,100,20,10}//10
    },
    {//7 生命，攻击，速度，防御，射程
        {100,100,100,  10,100,20,10},//1
        {100,100,100,  10,100,20,10},//2
        {100,100,100,  10,100,20,10},//3
        {100,100,100,  10,100,20,10},//4
        {100,100,100,  10,100,20,10},//5

        {100,100,100,  10,100,20,10},//6
        {100,100,100,  10,100,20,10},//7
        {100,100,100,  10,100,20,10},//8
        {100,100,100,  10,100,20,10},//9
        {100,100,100,  10,100,20,10}
    },
    {//8 生命，攻击，速度，防御，射程
        {100,100,100,  10,100,20,10},//1
        {100,100,100,  10,100,20,10},//2
        {100,100,100,  10,100,20,10},//3
        {100,100,100,  10,100,20,10},//4
        {100,100,100,  10,100,20,10},//5

        {100,100,100,  10,100,20,10},//6
        {100,100,100,  10,100,20,10},//7
        {100,100,100,  10,100,20,10},//8
        {100,100,100,  10,100,20,10},//9
        {100,100,100,  10,100,20,10}//10
    },
    {//9 生命，攻击，速度，防御，射程
        {100,100,100,  10,100,20,10},//1
        {100,100,100,  10,100,20,10},//2
        {100,100,100,  10,100,20,10},//3
        {100,100,100,  10,100,20,10},//4
        {100,100,100,  10,100,20,10},//5

        {100,100,100,  10,100,20,10},//6
        {100,100,100,  10,100,20,10},//7
        {100,100,100,  10,100,20,10},//8
        {100,100,100,  10,100,20,10},//9
        {100,100,100,  10,100,20,10}//10
    },
    {//10 生命，攻击，速度，防御，射程
        {100,100,100,  10,100,20,10},//1
        {100,100,100,  10,100,20,10},//2
        {100,100,100,  10,100,20,10},//3
        {100,100,100,  10,100,20,10},//4
        {100,100,100,  10,100,20,10},//5

        {100,100,100,  10,100,20,10},//6
        {100,100,100,  10,100,20,10},//7
        {100,100,100,  10,100,20,10},//8
        {100,100,100,  10,100,20,10},//9
        {100,100,100,  10,100,20,10}//10
    }
};

EnemyConfig s_bossConfig[ENEMY_LEVEL_MAX] =
{
    //Boss 生命，攻击，速度，防御，射程
    {1000,1000,100,  10,100,20,10},//1
    {100,1000,100,  10,100,20,10},//2
    {100,1000,100,  10,100,20,10},//3
    {100,1000,100,  10,100,20,10},//4
    {100,1000,100,  10,100,20,10},//5
    
    {100,1000,100,  10,100,20,10},//6
    {100,1000,100,  10,100,20,10},//7
    {100,1000,100,  10,100,20,10},//8
    {100,1000,100,  10,100,20,10},//9
    {100,1000,100,  10,100,20,10}//10
};

EnemyConfig s_towerConfig[ENEMY_LEVEL_MAX]=
{
    //Tower 生命，攻击，速度，防御，射程
    {1000,100,0,  10,100,20,10},//1
    {100,100,0,  10,100,20,10},//2
    {100,100,0,  10,100,20,10},//3
    {100,100,0,  10,100,20,10},//4
    {100,100,0,  10,100,20,10},//5
    
    {100,100,0,  10,100,20,10},//6
    {100,100,0,  10,100,20,10},//7
    {100,100,0,  10,100,20,10},//8
    {100,100,0,  10,100,20,10},//9
    {100,100,0,  10,100,20,10}//10
};


WeaponConfig s_weaponConfigs[WEAPON_MAX][WEAPON_LEVEL_MAX] = {
    {//星际炸弹，购买所需宝石，升级所需宝石，攻击，持续时间，携带上限，攻击范围,cd
        {100,100,  100,1,100,100,1},//1
        {100,100,  100,1,100,100,1},//2
        {100,100,  100,1,100,100,1},//3
        {100,100,  100,1,100,100,1},//4
        {100,100,  100,1,100,100,1},//5

        {100,100,  100,1,100,100,1},//6
        {100,100,  100,1,100,100,1},//7
        {100,100,  100,1,100,100,1},//8
        {100,100,  100,1,100,100,1},//9
        {100,100,  100,1,100,100,1}//10
    },
    {//激光发射器，购买所需宝石，升级所需宝石，攻击，持续时间，携带上限，攻击范围,cd
        {100,100,  100,10,100,15,1},//1
        {100,100,  100,10,100,15,1},//2
        {100,100,  100,10,100,15,1},//3
        {100,100,  100,10,100,15,1},//4
        {100,100,  100,10,100,15,1},//5

        {100,100,  100,10,100,15,1},//6
        {100,100,  100,10,100,15,1},//7
        {100,100,  100,10,100,15,1},//8
        {100,100,  100,10,100,15,1},//9
        {100,100,  100,10,100,15,1}//10
    },
    {////黑洞，购买所需宝石，升级所需宝石，攻击，持续时间，携带上限，攻击范围,cd
        {100,100,  999999,5,100,150,1},//1
        {100,100,  999999,5,100,150,1},//2
        {100,100,  999999,5,100,150,1},//3
        {100,100,  999999,5,100,150,1},//4
        {100,100,  999999,5,100,150,1},//5

        {100,100,  999999,5,100,150,1},//6
        {100,100,  999999,5,100,150,1},//7
        {100,100,  999999,5,100,150,1},//8
        {100,100,  999999,5,100,150,1},//9
        {100,100,  999999,5,100,150,1}//10
    }
};

//勋章奖励：宝石，星际炸弹，激光，黑洞（宝石必须有，后者3选1）
int s_medalRewards[MEDAL_MAX][MEDAL_REWARDS_COUNT]=
{
    {300, 0, 0, 0},//1
    {1000, 2, 0, 0},//2
    {6000, 2, 0, 0},//3
    {12000, 5, 0, 0},//4
    {50000, 0, 2, 0},//5
    {100000, 8, 0, 0},//6
    {5000, 0, 0, 0},//7
    {10000, 0, 0, 0},//8
    {50000, 0, 0, 0},//9
    {100000, 0, 0, 0},//10
    {500000, 0, 0, 0},//11
    {10000, 0, 2, 0},//12
    {60000, 0, 0, 3},//13
    {7000, 0, 2, 0},//14
    {35000, 0, 0, 3},//15
    {50000, 0, 0, 2},//16
    {100000, 0, 0, 3},//17
    {250000, 0, 0, 3},//18
    {500000, 0, 0, 3},//19
    {100000, 0, 0, 0},//20
    {200000, 0, 0, 0},//21
    {400000, 0, 2, 0},//22
    {650000, 0, 3, 0},//23
    {900000, 0, 0, 3},//24
    {1200000, 0, 0, 3}//25
};

//关卡奖励：宝石，星际炸弹，激光，黑洞（宝石必须有，后者3选1）
int s_stageRewards[STAGE_COUNT][STAGE_REWAEDS_COUNT]=
{
    {300, 0, 0, 0},//1
    {1000, 2, 0, 0},//2
    {6000, 2, 0, 0},//3
    {12000, 5, 0, 0},//4
    {50000, 0, 2, 0},//5
    {100000, 8, 0, 0},//6
    {5000, 0, 0, 0},//7
    {10000, 0, 0, 0},//8
    {50000, 0, 0, 0},//9
    {100000, 0, 0, 0},//10
    {500000, 0, 0, 0},//11
    {10000, 0, 2, 0},//12
    {60000, 0, 0, 3},//13
    {7000, 0, 2, 0},//14
    {35000, 0, 0, 3},//15
    {50000, 0, 0, 2},//16
    {100000, 0, 0, 3},//17
    {250000, 0, 0, 3},//18
    {500000, 0, 0, 3},//19
    {100000, 0, 0, 0},//20
    {200000, 0, 0, 0},//21
    {400000, 0, 2, 0},//22
    {650000, 0, 3, 0},//23
    {900000, 0, 0, 3},//24
    {1200000, 0, 0, 3},//25
    {300, 0, 0, 0},//26
    {1000, 2, 0, 0},//27
    {6000, 2, 0, 0},//28
    {12000, 5, 0, 0},//29
    {50000, 0, 2, 0},//30
    {100000, 8, 0, 0},//31
    {5000, 0, 0, 0},//32
    {10000, 0, 0, 0},//33
    {50000, 0, 0, 0},//34
    {100000, 0, 0, 0},//35
    {500000, 0, 0, 0},//36
    {10000, 0, 2, 0},//37
    {60000, 0, 0, 3},//38
    {7000, 0, 2, 0},//39
    {35000, 0, 0, 3},//40
    {50000, 0, 0, 2},//41
    {100000, 0, 0, 3},//42
    {250000, 0, 0, 3},//43
    {500000, 0, 0, 3},//44
    {100000, 0, 0, 0},//45
    {200000, 0, 0, 0},//46
    {400000, 0, 2, 0},//47
    {650000, 0, 3, 0},//48
    {900000, 0, 0, 3},//49
    {1200000, 0, 0, 3}//50
};


//每关敌人基地血量
int s_enemyBaseBlood[STAGE_COUNT]=
{
    1000, 2000, 3000, 4000, 5000,//1
    1000, 2000, 3000, 4000, 5000,//2
    1000, 2000, 3000, 4000, 5000,//3
    1000, 2000, 3000, 4000, 5000,//4
    1000, 2000, 3000, 4000, 5000,//5
    1000, 2000, 3000, 4000, 5000,//6
    1000, 2000, 3000, 4000, 5000,//7
    1000, 2000, 3000, 4000, 5000,//8
    1000, 2000, 3000, 4000, 5000,//9
    1000, 2000, 3000, 4000, 5000//10
};

//每关玩家基地血量
int s_playerBaseBlood[STAGE_COUNT]=
{
    1000, 2000, 3000, 4000, 5000,//1
    1000, 2000, 3000, 4000, 5000,//2
    1000, 2000, 3000, 4000, 5000,//3
    1000, 2000, 3000, 4000, 5000,//4
    1000, 2000, 3000, 4000, 5000,//5
    1000, 2000, 3000, 4000, 5000,//6
    1000, 2000, 3000, 4000, 5000,//7
    1000, 2000, 3000, 4000, 5000,//8
    1000, 2000, 3000, 4000, 5000,//9
    1000, 2000, 3000, 4000, 5000//10
};

cocos2d::Point s_EnemyBasePos;
cocos2d::Point s_PlayerBasePos;

