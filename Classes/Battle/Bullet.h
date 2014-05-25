#pragma once

#include "cocos2d.h"
#include "Configuration.h"

USING_NS_CC;

class Player;

class Bullet : public cocos2d::Sprite
{
public:
    
    static Bullet* createBullet(Attacker attacker,int type,int level);

    void attackLocations(Point& pos,Player* target);

    virtual void onEnter();
    //virtual void onExit();
private:
    enum class AttackMode
    {
        //µ¥Ìå¹¥»÷
        SINGLE,
        //·¶Î§ÉËº¦
        RANG,
        //À©É¢¹¥»÷
        DIFFUSION
    };
    Bullet();
    ~Bullet();

    bool initBullet(Attacker attacker,int type,int level);

    Player* _attTarget;
    Point _attTargetPos;

    AttackMode _attackMode;
    Attacker _attacker;
    int _type;
    int _level;

    bool _fire;
    //
    int _attack;
    //×·×Ù¹¥»÷
    bool _trace;
    //¹¥»÷·¶Î§  0-¹¥»÷
    int _attRang;

    Animation* explode_A;
    Animation* explode_B;
    Animation* explode_C;
};
