#ifndef __BW_Battleground_H__
#define __BW_Battleground_H__

#include "cocos2d.h"

USING_NS_CC;

class Fighter;
class Bullet;

class Battleground : public cocos2d::Scene
{
public:
    static Battleground* create(int stage);

    virtual bool init(int stage);

    void menuCallbackPause(Ref *sender);

    void eventCallbackPlayerSelect(cocos2d::EventCustom* event);

    virtual void onEnter();
    virtual void onExit();

    void battleLoop(float dt);
    void dispatchEnemys(float dt);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

private:
    void createBattleground(Ref *sender);

    void createFighterBase();
    void createHealthBar();
    void createRadarChart();

    void createAnimations();

    void plainFindTarget();
    void enemyFindTarget();

    void callbackPlayerDestroy(EventCustom* event);

    Battleground();
    ~Battleground();

    cocos2d::Node* _battleParallaxNode;

    //touch
    Point _touchBegan;
    float _battlegroundHeight;

    std::vector<Fighter*> s_players;
    std::vector<Fighter*> s_enemys;

    Animation* explode_A;
    Animation* explode_B;
    Animation* explode_C;

    friend class Bullet;
};

#endif
