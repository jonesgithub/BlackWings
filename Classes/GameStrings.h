#pragma once

#include <string>

typedef struct _mainMenuStrings
{
    std::string play;
    std::string help;
    std::string settings;
    std::string about;

    std::string settingMusic;
    std::string settingSFX;
    std::string settingSelLanguage;
    std::string settingLanguage;
    std::string settingReset;
    std::string settingRedeemCode;
    std::string settingRedeem;
    std::string settingRedeemHintText;
    std::string settingResetTipTitle;
    std::string settingResetTipContent;
    std::string settingResetConfirm;
    std::string settingResetCancel;
    std::string settingResetNotification;

    std::string settingResume;
    std::string settingRetry;
    std::string settingBackToBase;

    std::string helpTitle;

    std::string aboutVersions;
    std::string aboutMicroblog;
    std::string aboutEmail;
    std::string aboutRate;
    std::string aboutRateAppreciation;
    
    std::string stageselect;
    std::string stagetext;
    std::string stage_fight;
}MainMenuStrings;

typedef struct _helpInfoStrings{
    std::string sparInfo;
    std::string gemInfo;

    std::string fighter[6];
    std::string fighterLocked;

    std::string weapon[3];
    std::string weaponLocked;
}HelpInfoStrings;

typedef struct _baseStrings{
    std::string topBarMedal;
    std::string topBarBattle;
    std::string topBarMainMenu;

    std::string upgrade;
    std::string upgradeLevel;
    std::string upgradeAtt;
    std::string upgradeDef;
    std::string upgradeLife;
    std::string upgradeSpd;
    std::string upgradeRange;

    std::string weaponQuantity;
    
    std::string sparCapacity;
    std::string sparRecoverRate;
    std::string second;
    
}BaseStrings;

typedef struct _medalStrings{
    std::string medalname[25];
    std::string medaldscr[25];
    std::string medalrewardstip;
    std::string medalrewardok;
    std::string medaloverstage;
    std::string medalusedspcweapon;
    std::string medalkillenemy;
    std::string medalkillbigenemy;
}MedalStrings;

typedef struct _gameStrings
{
    MainMenuStrings *mainMenu;
    HelpInfoStrings *helpInfo;
    BaseStrings *base;
    MedalStrings *medalInfo;
}GameStrings;

extern GameStrings s_gameStrings;

enum class GameLanguage {
    Chinese = 0,
    English
};

extern void GSMainMenuInit(GameLanguage language);
extern void GSHelpInfoInit(GameLanguage language);
extern void GSBaseInit(GameLanguage language);
extern void GSMedalInfo(GameLanguage language);
