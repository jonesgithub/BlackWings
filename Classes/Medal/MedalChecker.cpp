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
    if (!s_playerConfig.firstkill & s_playerConfig.medallocked[0]) {
        s_playerConfig.medallocked[0] = false;
        s_playerConfig.medalget[0] = true;
    }
}

void MedalChecker::check_killenemy()
{
    if (s_playerConfig.killenemy >= 100 && s_playerConfig.medallocked[1]) {
        s_playerConfig.medallocked[1] = false;
        s_playerConfig.medalget[1] = true;
    }
    if (s_playerConfig.killenemy >= 1000 && s_playerConfig.medallocked[2]) {
        s_playerConfig.medallocked[2] = false;
        s_playerConfig.medalget[2] = true;
    }
    if (s_playerConfig.killenemy >= 2000 && s_playerConfig.medallocked[3]) {
        s_playerConfig.medallocked[3] = false;
        s_playerConfig.medalget[3] = true;
    }
    if (s_playerConfig.killenemy >= 5000 && s_playerConfig.medallocked[4]) {
        s_playerConfig.medallocked[4] = false;
        s_playerConfig.medalget[4] = true;
    }
    if (s_playerConfig.killenemy >= 10000 && s_playerConfig.medallocked[5]) {
        s_playerConfig.medallocked[5] = false;
        s_playerConfig.medalget[5] = true;
    }
}

void MedalChecker::check_money()
{
    if (s_playerConfig.gem >= 50000 && s_playerConfig.medallocked[6]) {
        s_playerConfig.medallocked[6] = false;
        s_playerConfig.medalget[6] = true;
    }
    if (s_playerConfig.gem >= 100000 && s_playerConfig.medallocked[7]) {
        s_playerConfig.medallocked[7] = false;
        s_playerConfig.medalget[7] = true;
    }
    if (s_playerConfig.gem >= 500000 && s_playerConfig.medallocked[8]) {
        s_playerConfig.medallocked[8] = false;
        s_playerConfig.medalget[8] = true;
    }
    if (s_playerConfig.gem >= 1000000 && s_playerConfig.medallocked[9]) {
        s_playerConfig.medallocked[9] = false;
        s_playerConfig.medalget[9] = true;
    }
    if (s_playerConfig.gem >= 5000000 && s_playerConfig.medallocked[10]) {
        s_playerConfig.medallocked[10] = false;
        s_playerConfig.medalget[10] = true;
    }
}

void MedalChecker::check_killbigenmey()
{
    if (s_playerConfig.killbigenemy >= 10 && s_playerConfig.medallocked[11]) {
        s_playerConfig.medallocked[11] = false;
        s_playerConfig.medalget[11] = true;
    }
    if (s_playerConfig.killbigenemy >= 50 && s_playerConfig.medallocked[12]) {
        s_playerConfig.medallocked[12] = false;
        s_playerConfig.medalget[12] = true;
    }
}

void MedalChecker::check_usedspcweapon()
{
    if (s_playerConfig.usedweapon >= 100 && s_playerConfig.medallocked[13]) {
        s_playerConfig.medallocked[13] = false;
        s_playerConfig.medalget[13] = true;
    }
    if (s_playerConfig.usedweapon >= 500 && s_playerConfig.medallocked[14]) {
        s_playerConfig.medallocked[14] = false;
        s_playerConfig.medalget[14] = true;
    }
}

void MedalChecker::check_unlockallfighter()
{
    if (s_playerConfig.unlockallfighter && s_playerConfig.medallocked[15]) {
        s_playerConfig.medallocked[15] = false;
        s_playerConfig.medalget[15] = true;
    }
}

void MedalChecker::check_stagevictory()
{
    if (s_playerConfig.overstage >= 30 && s_playerConfig.medallocked[16]) {
        s_playerConfig.medallocked[16] = false;
        s_playerConfig.medalget[16] = true;
    }
    if (s_playerConfig.overstage >= 40 && s_playerConfig.medallocked[17]) {
        s_playerConfig.medallocked[17] = false;
        s_playerConfig.medalget[17] = true;
    }
    if (s_playerConfig.overstage >= 50 && s_playerConfig.medallocked[18]) {
        s_playerConfig.medallocked[18] = false;
        s_playerConfig.medalget[18] = true;
    }
}
void MedalChecker::check_fightermaxlevel()
{
    if (s_playerConfig.fighterslevel[0] == FIGHTER_LEVEL_MAX && s_playerConfig.medallocked[19]) {
        s_playerConfig.medallocked[19] = false;
        s_playerConfig.medalget[19] = true;
    }
    if (s_playerConfig.fighterslevel[1] == FIGHTER_LEVEL_MAX && s_playerConfig.medallocked[20]) {
        s_playerConfig.medallocked[20] = false;
        s_playerConfig.medalget[20] = true;
    }
    if (s_playerConfig.fighterslevel[2] == FIGHTER_LEVEL_MAX && s_playerConfig.medallocked[21]) {
        s_playerConfig.medallocked[21] = false;
        s_playerConfig.medalget[21] = true;
    }
    if (s_playerConfig.fighterslevel[3] == FIGHTER_LEVEL_MAX && s_playerConfig.medallocked[22]) {
        s_playerConfig.medallocked[22] = false;
        s_playerConfig.medalget[22] = true;
    }
    if (s_playerConfig.fighterslevel[4] == FIGHTER_LEVEL_MAX && s_playerConfig.medallocked[23]) {
        s_playerConfig.medallocked[23] = false;
        s_playerConfig.medalget[23] = true;
    }
    if (s_playerConfig.fighterslevel[5] == FIGHTER_LEVEL_MAX && s_playerConfig.medallocked[24]) {
        s_playerConfig.medallocked[24] = false;
        s_playerConfig.medalget[24] = true;
    }
}