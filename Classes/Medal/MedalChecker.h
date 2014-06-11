//
//  MedalChecker.h
//  BlackWings
//
//  Created by Jacky on 14-5-28.
//
//

#ifndef __BlackWings__MedalChecker__
#define __BlackWings__MedalChecker__

#include "Medal.h"

class MedalChecker
{
public:
    
    static MedalChecker* getInstance()
    {
        if ( m_pInstance == NULL )
            m_pInstance = new MedalChecker();
        return m_pInstance;
    }
    
    void check();
    void check_firstkill();
    void check_killenemy();
    void check_money();
    void check_killbigenmey();
    void check_usedspcweapon();
    void check_unlockallfighter();
    void check_stagevictory();
    void check_fightermaxlevel();
    
    void showTip();
    std::vector<int> new_medal_indexs;
private:
    
    MedalChecker();
    
    static MedalChecker* m_pInstance;
    
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if (MedalChecker::m_pInstance!=NULL)
            {
                delete MedalChecker::m_pInstance;
            }
        }
    };
    
    static CGarbo m_garbo;
};

#endif /* defined(__BlackWings__MedalChecker__) */
