#ifndef __BW_Battleground_H__
#define __BW_Battleground_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CDItem.h"

USING_NS_CC;

class Fighter;
class Bullet;

const int RADARSCREEN_DOWN = 95;
const int RADARSCREEN_UP = 310;

//暂时设置最大的冷却项为8，差不多一排。
const Point CDItemsPos[8]=
{
    Point(60,240),Point(120,240),Point(180,240),Point(240,240),
    Point(300,240),Point(360,240),Point(420,240),Point(480,240)
};

const Point FlightItemsPos[6]=
{
    Point(65,70),Point(155,70),Point(245,70),Point(335,70),Point(425,70),Point(515,70)
};

const Point StonePos = Point(80,180);
const Point GemPos = Point(300,180);

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
    void dispatchEnemys_1(float dt);
    void dispatchEnemys_2(float dt);
    void dispatchBoss(float dt);
    void showPotInRadar(float dt);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
private:
    void createBattleground(Ref *sender);
    void createFlight(Ref* sender);

    void createFlightBase();
    void createHealthBar();
    void createRadarChart();

    void createAnimations();

    void plainFindTarget();
    void enemyFindTarget();
    void bossFindTarget();
    void towerFindTarget();

    void callbackPlayerDestroy(EventCustom* event);
    void callbackPlayerBaseHurt(EventCustom* event);
    void callbackEnemyBaseHurt(EventCustom* event);
    void callbackResortCDItems(EventCustom* event);
    
    void initNormalEnemy();
    void initTowerEnemy();
    void initBossEnemy();
    
    void win();
    void lost();
    
    void showStoneAndGem(Point pos, int stoneCount, int gemCount, int stone, int gem);

    Battleground();
    ~Battleground();

    cocos2d::Node* _battleParallaxNode;

    //touch
    Point _touchBegan;
    float _battlegroundHeight;

    std::vector<Fighter*> s_players;
    std::vector<Fighter*> s_enemys;
    std::vector<Fighter*> s_boss;
    std::vector<Fighter*> s_towers;
    std::vector<CDItem* > s_cditems;

    Animation* explode_A;
    Animation* explode_B;
    Animation* explode_C;

    friend class Bullet;
    
    int _stage;
    
    Sprite* radarScreen;
    Sprite* radarChart;
    
    int _playerBase_Blood;
    int _curPlayerBase_Blood;
    int _enemyBase_Blood;
    int _curEnemyBase_Blood;
    cocos2d::ui::LoadingBar* _playerBloodBar;
    cocos2d::ui::LoadingBar* _enemyBloodBar;
    
    //normal敌机出兵配置
    int _maxWaves;
    int _curWaves;
    
    //当前选择的飞机
    int _indexOfChooseFlight;
};

#endif
