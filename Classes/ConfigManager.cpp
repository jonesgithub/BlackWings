#include "ConfigManager.h"
#include "Configuration.h"


ConfigManager* ConfigManager::m_pInstance = nullptr;
ConfigManager::CGarbo ConfigManager::m_garbo;

ConfigManager::ConfigManager()
{
}

bool ConfigManager::isHaveSaveFile()
{
    if(!UserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
    {
        initConfig();
        saveConfig();
        
        return false;
    }
    else return true;
}


void ConfigManager::readConfig()
{
    if (isHaveSaveFile())
    {
        //system
        s_playerConfig.musicVolume = UserDefault::getInstance()->getFloatForKey("musicVolume");
        s_playerConfig.sfxVolume = UserDefault::getInstance()->getFloatForKey("sfxVolume");
        s_playerConfig.language = UserDefault::getInstance()->getIntegerForKey("language");
        
        //player
        s_playerConfig.stone = UserDefault::getInstance()->getIntegerForKey("stone");
        s_playerConfig.stoneMax = UserDefault::getInstance()->getIntegerForKey("stoneMax");
        s_playerConfig.gem = UserDefault::getInstance()->getIntegerForKey("gem");
        s_playerConfig.stonespeedlevel = UserDefault::getInstance()->getIntegerForKey("stonespeedlevel");
        s_playerConfig.stonecapacitylevel = UserDefault::getInstance()->getIntegerForKey("stonecapacitylevel");
        s_playerConfig.usedweapon = UserDefault::getInstance()->getIntegerForKey("usedweapon");
        s_playerConfig.overstage = UserDefault::getInstance()->getIntegerForKey("overstage");
        s_playerConfig.killbigenemy = UserDefault::getInstance()->getIntegerForKey("killbigenemy");
        s_playerConfig.firstkill = UserDefault::getInstance()->getBoolForKey("firstkill");
        s_playerConfig.unlockallfighter = UserDefault::getInstance()->getBoolForKey("unlockallfighter");
        
        //fighter
        for (int i = 0; i < FIGHTER_MAX; ++i) {
            char name[30];
            sprintf(name,"fighterslocked_%d",i);
            s_playerConfig.fighterslocked[i] = UserDefault::getInstance()->getBoolForKey(name);
            sprintf(name,"fighterslevel_%d",i);
            s_playerConfig.fighterslevel[i] = UserDefault::getInstance()->getIntegerForKey(name);
        }
        
        //weapon
        s_playerConfig.weaponlocked = true;
        for(int i = 0; i < WEAPON_MAX; ++i){
            char name[30];
            sprintf(name, "weaponslevel_%d",i);
            s_playerConfig.weaponslevel[i] = UserDefault::getInstance()->getIntegerForKey(name);
            sprintf(name, "weaponCount_%d", i);
            s_playerConfig.weaponCount[i] = UserDefault::getInstance()->getIntegerForKey(name);
        }
        
        //medal
        for (int i=0; i<MEDAL_MAX; ++i)
        {
            char name[30];
            sprintf(name, "medallocked_%d",i);
            s_playerConfig.medallocked[i] = UserDefault::getInstance()->getBoolForKey(name);
            sprintf(name, "medalget_%d",i);
            s_playerConfig.medalget[i] = UserDefault::getInstance()->getBoolForKey(name);
        }
    }
}

void ConfigManager::initConfig()
{
    s_playerConfig.musicVolume = 1.0f;
    s_playerConfig.sfxVolume = 1.0f;
    s_playerConfig.language = (int)GameLanguage::Chinese;
    
    s_playerConfig.stone = 200;
    s_playerConfig.stoneMax = 1000;
    s_playerConfig.gem = 1000000;
    s_playerConfig.stonespeedlevel = 18;
    s_playerConfig.stonecapacitylevel = 18;
    s_playerConfig.usedweapon = 0;
    s_playerConfig.overstage = 0;
    s_playerConfig.killbigenemy = 0;
    s_playerConfig.firstkill = false;
    s_playerConfig.unlockallfighter = false;
    
    s_playerConfig.fighterslocked[0] = false;
    s_playerConfig.fighterslocked[1] = false;
    s_playerConfig.fighterslocked[2] = false;
    s_playerConfig.fighterslocked[3] = false;
    s_playerConfig.fighterslocked[4] = true;
    s_playerConfig.fighterslocked[5] = true;
    
    s_playerConfig.fighterslevel[0] = 13;
    s_playerConfig.fighterslevel[1] = 0;
    s_playerConfig.fighterslevel[2] = 0;
    s_playerConfig.fighterslevel[3] = 0;
    s_playerConfig.fighterslevel[4] = 0;
    s_playerConfig.fighterslevel[5] = 0;
    
    s_playerConfig.weaponlocked = true;
    s_playerConfig.weaponslevel[0] = 0;
    s_playerConfig.weaponslevel[1] = 8;
    s_playerConfig.weaponslevel[2] = 0;
    s_playerConfig.weaponCount[0] = 20;
    s_playerConfig.weaponCount[1] = 20;
    s_playerConfig.weaponCount[2] = 20;
    
    for (int i=0; i<MEDAL_MAX; ++i)
    {
        s_playerConfig.medallocked[i] = true;
        s_playerConfig.medalget[i] = false;
    }
    
    UserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);
}

void ConfigManager::saveConfig()
{
    //system
    UserDefault::getInstance()->setFloatForKey("musicVolume", s_playerConfig.musicVolume);
    UserDefault::getInstance()->setFloatForKey("sfxVolume", s_playerConfig.sfxVolume);
    UserDefault::getInstance()->setIntegerForKey("language", (int)s_playerConfig.language);
    
    //player
    UserDefault::getInstance()->setIntegerForKey("stone", s_playerConfig.stone);
    UserDefault::getInstance()->setIntegerForKey("stoneMax", s_playerConfig.stoneMax);
    UserDefault::getInstance()->setIntegerForKey("gem", s_playerConfig.gem);
    UserDefault::getInstance()->setIntegerForKey("stonespeedlevel", s_playerConfig.stonespeedlevel);
    UserDefault::getInstance()->setIntegerForKey("stonecapacitylevel", s_playerConfig.stonecapacitylevel);
    UserDefault::getInstance()->setIntegerForKey("usedweapon", s_playerConfig.usedweapon);
    UserDefault::getInstance()->setIntegerForKey("overstage", s_playerConfig.overstage);
    UserDefault::getInstance()->setIntegerForKey("killbigenemy", s_playerConfig.killbigenemy);
    UserDefault::getInstance()->setBoolForKey("firstkill", s_playerConfig.firstkill);
    UserDefault::getInstance()->setBoolForKey("unlockallfighter", s_playerConfig.unlockallfighter);
    
    //fighter
    for (int i = 0; i < FIGHTER_MAX; ++i) {
        char name[30];
        sprintf(name,"fighterslocked_%d",i);
        UserDefault::getInstance()->setBoolForKey(name, s_playerConfig.fighterslocked[i]);
        sprintf(name,"fighterslevel_%d",i);
        UserDefault::getInstance()->setIntegerForKey(name, s_playerConfig.fighterslevel[i]);
    }
    
    //weapon
    s_playerConfig.weaponlocked = true;
    for(int i = 0; i < WEAPON_MAX; ++i){
        char name[30];
        sprintf(name, "weaponslevel_%d",i);
        UserDefault::getInstance()->setIntegerForKey(name, s_playerConfig.weaponslevel[i]);
        sprintf(name, "weaponCount_%d", i);
        UserDefault::getInstance()->setIntegerForKey(name, s_playerConfig.weaponCount[i]);
    }
    
    //medal
    for (int i=0; i<MEDAL_MAX; ++i)
    {
        char name[30];
        sprintf(name, "medallocked_%d",i);
        UserDefault::getInstance()->setBoolForKey(name, s_playerConfig.medallocked[i]);
        sprintf(name, "medalget_%d",i);
        UserDefault::getInstance()->setBoolForKey(name, s_playerConfig.medalget[i]);
    }
    
    UserDefault::getInstance()->flush();
}

void ConfigManager::saveMusicVolume(float volume)
{
    s_playerConfig.musicVolume = volume;
    UserDefault::getInstance()->setFloatForKey("musicVolume", volume);
}

void ConfigManager::saveSFXVolume(float volume)
{
    s_playerConfig.sfxVolume = volume;
    UserDefault::getInstance()->setFloatForKey("sfxVolume", volume);
}

void ConfigManager::saveLanguage(GameLanguage language)
{
    s_playerConfig.language = (int)language;
    UserDefault::getInstance()->setFloatForKey("language", (int)language);
}