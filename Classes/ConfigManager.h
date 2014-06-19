#pragma once

#include "cocos2d.h"
#include "GameStrings.h"

USING_NS_CC;

class ConfigManager
{
public:
    
    static ConfigManager* getInstance()
    {
        if ( m_pInstance == nullptr )
            m_pInstance = new ConfigManager();
        return m_pInstance;
    }
    
private:
    
    ConfigManager();
    
    static ConfigManager* m_pInstance;
    
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if (ConfigManager::m_pInstance!= nullptr)
            {
                delete ConfigManager::m_pInstance;
            }
        }
    };
    
    static CGarbo m_garbo;
    
public:
    
    bool isHaveSaveFile();
    void readConfig();
    void initConfig();
    void saveConfig();
    
    void saveMusicVolume(float volume);
    void saveSFXVolume(float volume);
    void saveLanguage(GameLanguage language);
};