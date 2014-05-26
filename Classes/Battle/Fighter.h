#pragma once

#include "cocos2d.h"
#include "Configuration.h"
#include "Player.h"

USING_NS_CC;

enum class FighterState
{
    IDLE,
    MOVE,
    ATTACK,
    DESTROY
};
class Fighter : public Player
{
public:
    static Fighter* createPlain(int type);

    static Fighter* createEnemy(int type,int level);

    void moveTo(Point& pos,Player* target);

    void attackLocations(Point& pos,Player* target);

    void hurt(int ATK);

    void fire(float dt);

    FighterState state;
    PlainConfig plainConfig;
    EnemyConfig enemyConfig;

    Attacker _attacker;
    
    Sprite* potInRadar;

private:
    Fighter();
    ~Fighter();

    bool initFighter(Attacker attacker,int type,int level = 0);

    Sprite* _fighterIcon;

    Player* _attTarget;
    Point _attTargetPos;

    int _fighterType;
    int _fighterLevel;
};
