//
//  Weapon.h
//  BlackWings
//
//  Created by Jacky on 14-6-2.
//
//

#ifndef __BlackWings__Weapon__
#define __BlackWings__Weapon__

#include "cocos2d.h"
#include "Configuration.h"

enum class WeaponType
{
    STARBOMB,
    LASER,
    BLACKHOLE
};

class Weapon : public cocos2d::Node
{
public:
    
    static Weapon* createStarBomb(const cocos2d::Point& pos);
    static Weapon* createLaser(const cocos2d::Point& pos);
    static Weapon* createBlackhole(const cocos2d::Point& pos);
    
    bool initWeapon(WeaponType weapontype, const cocos2d::Point& pos);
    
    void createWeapon();

    WeaponType _weaponType;
    cocos2d::Point _pos;
    WeaponConfig _weaponConfig;
    
    cocos2d::ParticleSystemQuad* bomb_2_effect;
    cocos2d::ParticleSystemQuad* bomb_2_effectB;
    
};
#endif /* defined(__BlackWings__Weapon__) */
