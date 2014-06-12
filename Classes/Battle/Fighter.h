#pragma once

#include "cocos2d.h"
#include "Configuration.h"
#include "Player.h"
#include "ui/CocosGUI.h"

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
    
    static Fighter* createBoss(int level);
    
    static Fighter* createTower(int level);


    void moveTo(Point& pos,Player* target);

    void attackLocations(Point& pos,Player* target);

    void hurt(int ATK);

    void fire(float dt);
    
    void update(float dt);

    FighterState state;
    PlainConfig plainConfig;
    EnemyConfig enemyConfig;
    EnemyConfig bossConfig;
    EnemyConfig towerConfig;

    Attacker _attacker;
    
    Sprite* potInRadar;
    Sprite* gun;
    cocos2d::ui::LoadingBar* _bloodbar;

    bool isInBlackhole;
    Point offsetWithBlackhole;
private:
    Fighter();
    ~Fighter();

    bool initFighter(Attacker attacker,int type,int level = 0);

    Sprite* _fighterIcon;

    Player* _attTarget;
    Point _attTargetPos;

    int _fighterType;
    int _fighterLevel;
    
    int _maxlife;
    int _curlife;

};
