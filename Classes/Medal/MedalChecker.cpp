//
//  MedalChecker.cpp
//  BlackWings
//
//  Created by Jacky on 14-5-28.
//
//

#include "MedalChecker.h"
#include "Configuration.h"

MedalChecker* MedalChecker::m_pInstance=NULL;
MedalChecker::CGarbo MedalChecker::m_garbo;

MedalChecker::MedalChecker()
{
    
}

void MedalChecker::check()
{
    check_firstkill();
    check_killenemy();
    check_money();
    check_killbigenmey();
    check_usedspcweapon();
    check_unlockallfighter();
    check_stagevictory();
    check_fightermaxlevel();
}

void MedalChecker::check_firstkill()
{
    if (!s_gameConfig.treasure.firstKill & s_gameConfig.medal_lock[0]) {
        s_gameConfig.medal_lock[0] = false;
        s_gameConfig.medal_get[0] = true;
    }
}

void MedalChecker::check_killenemy()
{
    if (s_gameConfig.treasure.killEnemy >= 100 && s_gameConfig.medal_lock[1]) {
        s_gameConfig.medal_lock[1] = false;
        s_gameConfig.medal_get[1] = true;
    }
    if (s_gameConfig.treasure.killEnemy >= 1000 && s_gameConfig.medal_lock[2]) {
        s_gameConfig.medal_lock[2] = false;
        s_gameConfig.medal_get[2] = true;
    }
    if (s_gameConfig.treasure.killEnemy >= 2000 && s_gameConfig.medal_lock[3]) {
        s_gameConfig.medal_lock[3] = false;
        s_gameConfig.medal_get[3] = true;
    }
    if (s_gameConfig.treasure.killEnemy >= 5000 && s_gameConfig.medal_lock[4]) {
        s_gameConfig.medal_lock[4] = false;
        s_gameConfig.medal_get[4] = true;
    }
    if (s_gameConfig.treasure.killEnemy >= 10000 && s_gameConfig.medal_lock[5]) {
        s_gameConfig.medal_lock[5] = false;
        s_gameConfig.medal_get[5] = true;
    }
}

void MedalChecker::check_money()
{
    if (s_gameConfig.treasure.money >= 50000 && s_gameConfig.medal_lock[6]) {
        s_gameConfig.medal_lock[6] = false;
        s_gameConfig.medal_get[6] = true;
    }
    if (s_gameConfig.treasure.killEnemy >= 100000 && s_gameConfig.medal_lock[7]) {
        s_gameConfig.medal_lock[7] = false;
        s_gameConfig.medal_get[7] = true;
    }
    if (s_gameConfig.treasure.killEnemy >= 500000 && s_gameConfig.medal_lock[8]) {
        s_gameConfig.medal_lock[8] = false;
        s_gameConfig.medal_get[8] = true;
    }
    if (s_gameConfig.treasure.killEnemy >= 1000000 && s_gameConfig.medal_lock[9]) {
        s_gameConfig.medal_lock[9] = false;
        s_gameConfig.medal_get[9] = true;
    }
    if (s_gameConfig.treasure.killEnemy >= 5000000 && s_gameConfig.medal_lock[10]) {
        s_gameConfig.medal_lock[10] = false;
        s_gameConfig.medal_get[10] = true;
    }
}

void MedalChecker::check_killbigenmey()
{
    if (s_gameConfig.treasure.killBigEnemy >= 10 && s_gameConfig.medal_lock[11]) {
        s_gameConfig.medal_lock[11] = false;
        s_gameConfig.medal_get[11] = true;
    }
    if (s_gameConfig.treasure.killBigEnemy >= 50 && s_gameConfig.medal_lock[12]) {
        s_gameConfig.medal_lock[12] = false;
        s_gameConfig.medal_get[12] = true;
    }
}

void MedalChecker::check_usedspcweapon()
{
    if (s_gameConfig.treasure.usedSpcWeapon >= 100 && s_gameConfig.medal_lock[13]) {
        s_gameConfig.medal_lock[13] = false;
        s_gameConfig.medal_get[13] = true;
    }
    if (s_gameConfig.treasure.usedSpcWeapon >= 500 && s_gameConfig.medal_lock[14]) {
        s_gameConfig.medal_lock[14] = false;
        s_gameConfig.medal_get[14] = true;
    }
}

void MedalChecker::check_unlockallfighter()
{
    if (s_gameConfig.treasure.unlockAllFighter && s_gameConfig.medal_lock[15]) {
        s_gameConfig.medal_lock[15] = false;
        s_gameConfig.medal_get[15] = true;
    }
}

void MedalChecker::check_stagevictory()
{
    if (s_gameConfig.treasure.overStage >= 30 && s_gameConfig.medal_lock[16]) {
        s_gameConfig.medal_lock[16] = false;
        s_gameConfig.medal_get[16] = true;
    }
    if (s_gameConfig.treasure.overStage >= 40 && s_gameConfig.medal_lock[17]) {
        s_gameConfig.medal_lock[17] = false;
        s_gameConfig.medal_get[17] = true;
    }
    if (s_gameConfig.treasure.overStage >= 50 && s_gameConfig.medal_lock[18]) {
        s_gameConfig.medal_lock[18] = false;
        s_gameConfig.medal_get[18] = true;
    }
}
void MedalChecker::check_fightermaxlevel()
{
    if (s_gameConfig.fightersLevle[0] == FIGHTER_LEVEL_MAX && s_gameConfig.medal_lock[19]) {
        s_gameConfig.medal_lock[19] = false;
        s_gameConfig.medal_get[19] = true;
    }
    if (s_gameConfig.fightersLevle[1] == FIGHTER_LEVEL_MAX && s_gameConfig.medal_lock[20]) {
        s_gameConfig.medal_lock[20] = false;
        s_gameConfig.medal_get[20] = true;
    }
    if (s_gameConfig.fightersLevle[2] == FIGHTER_LEVEL_MAX && s_gameConfig.medal_lock[21]) {
        s_gameConfig.medal_lock[21] = false;
        s_gameConfig.medal_get[21] = true;
    }
    if (s_gameConfig.fightersLevle[3] == FIGHTER_LEVEL_MAX && s_gameConfig.medal_lock[22]) {
        s_gameConfig.medal_lock[22] = false;
        s_gameConfig.medal_get[22] = true;
    }
    if (s_gameConfig.fightersLevle[4] == FIGHTER_LEVEL_MAX && s_gameConfig.medal_lock[23]) {
        s_gameConfig.medal_lock[23] = false;
        s_gameConfig.medal_get[23] = true;
    }
    if (s_gameConfig.fightersLevle[5] == FIGHTER_LEVEL_MAX && s_gameConfig.medal_lock[24]) {
        s_gameConfig.medal_lock[24] = false;
        s_gameConfig.medal_get[24] = true;
    }
}