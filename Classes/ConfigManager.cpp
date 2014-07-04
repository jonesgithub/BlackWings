#include "ConfigManager.h"
#include "Configuration.h"
#include "EncryptUserDefault.h"

ConfigManager* ConfigManager::m_pInstance = nullptr;
ConfigManager::CGarbo ConfigManager::m_garbo;

ConfigManager::ConfigManager()
{
}

bool ConfigManager::isHaveSaveFile()
{
    if(!EncryptUserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
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
        s_playerConfig.musicVolume = EncryptUserDefault::getInstance()->getFloatForKey("musicVolume");
        s_playerConfig.sfxVolume = EncryptUserDefault::getInstance()->getFloatForKey("sfxVolume");
        s_playerConfig.language = EncryptUserDefault::getInstance()->getIntegerForKey("language");
        
        //player
        s_playerConfig.stone = EncryptUserDefault::getInstance()->getIntegerForKey("stone");
        s_playerConfig.stoneMax = EncryptUserDefault::getInstance()->getIntegerForKey("stoneMax");
        s_playerConfig.gem = EncryptUserDefault::getInstance()->getIntegerForKey("gem");
        s_playerConfig.stonespeedlevel = EncryptUserDefault::getInstance()->getIntegerForKey("stonespeedlevel");
        s_playerConfig.stonecapacitylevel = EncryptUserDefault::getInstance()->getIntegerForKey("stonecapacitylevel");
        s_playerConfig.usedweapon = EncryptUserDefault::getInstance()->getIntegerForKey("usedweapon");
        s_playerConfig.overstage = EncryptUserDefault::getInstance()->getIntegerForKey("overstage");
        s_playerConfig.killbigenemy = EncryptUserDefault::getInstance()->getIntegerForKey("killbigenemy");
        s_playerConfig.firstkill = EncryptUserDefault::getInstance()->getBoolForKey("firstkill");
        s_playerConfig.unlockallfighter = EncryptUserDefault::getInstance()->getBoolForKey("unlockallfighter");
        
        //fighter
        for (int i = 0; i < FIGHTER_MAX; ++i) {
            char name[30];
            sprintf(name,"fighterslocked_%d",i);
            s_playerConfig.fighterslocked[i] = EncryptUserDefault::getInstance()->getBoolForKey(name);
            sprintf(name,"fighterslevel_%d",i);
            s_playerConfig.fighterslevel[i] = EncryptUserDefault::getInstance()->getIntegerForKey(name);
        }
        
        //weapon
        s_playerConfig.weaponlocked = EncryptUserDefault::getInstance()->getBoolForKey("weaponlocked");
        for(int i = 0; i < WEAPON_MAX; ++i){
            char name[30];
            sprintf(name, "weaponslevel_%d",i);
            s_playerConfig.weaponslevel[i] = EncryptUserDefault::getInstance()->getIntegerForKey(name);
            sprintf(name, "weaponCount_%d", i);
            s_playerConfig.weaponCount[i] = EncryptUserDefault::getInstance()->getIntegerForKey(name);
        }
        
        //medal
        for (int i=0; i<MEDAL_MAX; ++i)
        {
            char name[30];
            sprintf(name, "medallocked_%d",i);
            s_playerConfig.medallocked[i] = EncryptUserDefault::getInstance()->getBoolForKey(name);
            sprintf(name, "medalget_%d",i);
            s_playerConfig.medalget[i] = EncryptUserDefault::getInstance()->getBoolForKey(name);
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
    s_playerConfig.fighterslocked[3] = true;
    s_playerConfig.fighterslocked[4] = true;
    s_playerConfig.fighterslocked[5] = true;
    
    s_playerConfig.fighterslevel[0] = 13;
    s_playerConfig.fighterslevel[1] = 0;
    s_playerConfig.fighterslevel[2] = 0;
    s_playerConfig.fighterslevel[3] = 0;
    s_playerConfig.fighterslevel[4] = 0;
    s_playerConfig.fighterslevel[5] = 0;
    
    s_playerConfig.weaponlocked = false;
    s_playerConfig.weaponslevel[0] = 0;
    s_playerConfig.weaponslevel[1] = 8;
    s_playerConfig.weaponslevel[2] = 0;
    s_playerConfig.weaponCount[0] = 5;
    s_playerConfig.weaponCount[1] = 5;
    s_playerConfig.weaponCount[2] = 5;
    
    for (int i=0; i<MEDAL_MAX; ++i)
    {
        s_playerConfig.medallocked[i] = true;
        s_playerConfig.medalget[i] = false;
    }
    
    EncryptUserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);
}

void ConfigManager::saveConfig()
{
    //system
    EncryptUserDefault::getInstance()->setFloatForKey("musicVolume", s_playerConfig.musicVolume);
    EncryptUserDefault::getInstance()->setFloatForKey("sfxVolume", s_playerConfig.sfxVolume);
    EncryptUserDefault::getInstance()->setIntegerForKey("language", (int)s_playerConfig.language);
    
    //player
    EncryptUserDefault::getInstance()->setIntegerForKey("stone", s_playerConfig.stone);
    EncryptUserDefault::getInstance()->setIntegerForKey("stoneMax", s_playerConfig.stoneMax);
    EncryptUserDefault::getInstance()->setIntegerForKey("gem", s_playerConfig.gem);
    EncryptUserDefault::getInstance()->setIntegerForKey("stonespeedlevel", s_playerConfig.stonespeedlevel);
    EncryptUserDefault::getInstance()->setIntegerForKey("stonecapacitylevel", s_playerConfig.stonecapacitylevel);
    EncryptUserDefault::getInstance()->setIntegerForKey("usedweapon", s_playerConfig.usedweapon);
    EncryptUserDefault::getInstance()->setIntegerForKey("overstage", s_playerConfig.overstage);
    EncryptUserDefault::getInstance()->setIntegerForKey("killbigenemy", s_playerConfig.killbigenemy);
    EncryptUserDefault::getInstance()->setBoolForKey("firstkill", s_playerConfig.firstkill);
    EncryptUserDefault::getInstance()->setBoolForKey("unlockallfighter", s_playerConfig.unlockallfighter);
    
    //fighter
    for (int i = 0; i < FIGHTER_MAX; ++i) {
        char name[30];
        sprintf(name,"fighterslocked_%d",i);
        EncryptUserDefault::getInstance()->setBoolForKey(name, s_playerConfig.fighterslocked[i]);
        sprintf(name,"fighterslevel_%d",i);
        EncryptUserDefault::getInstance()->setIntegerForKey(name, s_playerConfig.fighterslevel[i]);
    }
    
    //weapon
    EncryptUserDefault::getInstance()->setBoolForKey("weaponlocked",s_playerConfig.weaponlocked);
    for(int i = 0; i < WEAPON_MAX; ++i){
        char name[30];
        sprintf(name, "weaponslevel_%d",i);
        EncryptUserDefault::getInstance()->setIntegerForKey(name, s_playerConfig.weaponslevel[i]);
        sprintf(name, "weaponCount_%d", i);
        EncryptUserDefault::getInstance()->setIntegerForKey(name, s_playerConfig.weaponCount[i]);
    }
    
    //medal
    for (int i=0; i<MEDAL_MAX; ++i)
    {
        char name[30];
        sprintf(name, "medallocked_%d",i);
        EncryptUserDefault::getInstance()->setBoolForKey(name, s_playerConfig.medallocked[i]);
        sprintf(name, "medalget_%d",i);
        EncryptUserDefault::getInstance()->setBoolForKey(name, s_playerConfig.medalget[i]);
    }
    
    UserDefault::getInstance()->flush();
}

void ConfigManager::saveMusicVolume(float volume)
{
    s_playerConfig.musicVolume = volume;
    EncryptUserDefault::getInstance()->setFloatForKey("musicVolume", volume);
    UserDefault::getInstance()->flush();
}

void ConfigManager::saveSFXVolume(float volume)
{
    s_playerConfig.sfxVolume = volume;
    EncryptUserDefault::getInstance()->setFloatForKey("sfxVolume", volume);
    UserDefault::getInstance()->flush();
}

void ConfigManager::saveLanguage(int language)
{
    s_playerConfig.language = language;
    EncryptUserDefault::getInstance()->setFloatForKey("language", language);
    UserDefault::getInstance()->flush();
}