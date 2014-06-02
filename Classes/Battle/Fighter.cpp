#include "Fighter.h"
#include "Configuration.h"
#include "Bullet.h"

USING_NS_CC;

Fighter* Fighter::createPlain(int type)
{
    auto ret = new (std::nothrow) Fighter;
    if (ret && ret->initFighter(Attacker::PLAIN,type))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

Fighter* Fighter::createEnemy(int type,int level)
{
    auto ret = new (std::nothrow) Fighter;
    if (ret && ret->initFighter(Attacker::ENEMY,type,level))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

Fighter* Fighter::createBoss(int level)
{
    auto ret = new (std::nothrow) Fighter;
    if (ret && ret->initFighter(Attacker::BOSS,9,level))
    {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}

Fighter* Fighter::createTower(int level)
{
    auto ret = new (std::nothrow) Fighter;
    if (ret && ret->initFighter(Attacker::TOWER,9,level))
    {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}


Fighter::Fighter()
: state(FighterState::IDLE)
, _attTarget(nullptr)
,potInRadar(nullptr),
gun(nullptr),
_bloodbar(nullptr),
_maxlife(0),
_curlife(0)
{
}

Fighter::~Fighter()
{
}

bool Fighter::initFighter(Attacker attacker,int type,int level /* = 0 */)
{
    bool ret = false;

    char fileName[30];
    _attacker = attacker;
    switch (attacker)
    {
        case Attacker::ENEMY:
            sprintf(fileName,"enemy_%d_lv_%d.png",type + 1,level + 1);
            enemyConfig = s_enemyConfigs[type][level];
            _curlife = _maxlife = enemyConfig.life;
            potInRadar = Sprite::createWithSpriteFrameName("map_enemy.png");
            potInRadar->retain();
            break;
        case Attacker::BOSS:
            sprintf(fileName,"boos_%d.png",level + 1);
            bossConfig = s_bossConfig[level];
            _curlife = _maxlife = bossConfig.life;
            potInRadar = Sprite::createWithSpriteFrameName("map_enemy.png");
            potInRadar->retain();
            break;
        case Attacker::TOWER:
            sprintf(fileName,"fixed_enemy_%d.png",level + 1);
            towerConfig = s_towerConfig[level];
            _curlife = _maxlife = towerConfig.life;
            potInRadar = Sprite::createWithSpriteFrameName("map_enemy.png");
            potInRadar->retain();
            break;
        case Attacker::PLAIN:
            level = s_playerConfig.fighterslevel[type];
            sprintf(fileName,"plain_%d_lv_%d.png",type + 1,level + 1);
            plainConfig = s_plainConfigs[type][level];
            _curlife = _maxlife = plainConfig.life;
            potInRadar = Sprite::createWithSpriteFrameName("map_plain.png");
            potInRadar->retain();
            break;
            
        default:
            break;
    }
    
    _fighterIcon = Sprite::createWithSpriteFrameName(fileName);
    auto iconSize = _fighterIcon->getContentSize();
    _fighterIcon->setPosition(Point(iconSize.width/2, iconSize.height/2));
    this->setContentSize(_fighterIcon->getContentSize());
    this->addChild(_fighterIcon);
    
    if (attacker == Attacker::ENEMY || attacker == Attacker::BOSS || attacker == Attacker::TOWER )
    {
        _bloodbar = ui::LoadingBar::create("battle_life_enemy.png");
        _bloodbar->setAnchorPoint(Point::ANCHOR_MIDDLE);
        _bloodbar->setPosition(Point(_fighterIcon->getContentSize().width/2,_fighterIcon->getContentSize().height+10));
        _fighterIcon->addChild(_bloodbar);
        _bloodbar->setScale(0.3f);
    }
    else if(attacker == Attacker::PLAIN)
    {
        _bloodbar = ui::LoadingBar::create("battle_life_plain.png");
        _bloodbar->setAnchorPoint(Point::ANCHOR_MIDDLE);
        _bloodbar->setPosition(Point(_fighterIcon->getContentSize().width/2,-10));
        _fighterIcon->addChild(_bloodbar);
        _bloodbar->setScale(0.3f);
    }
    
    if(_attacker == Attacker::TOWER)
    {
        sprintf(fileName,"fixed_enemy_%d_gun.png",level + 1);
        gun = Sprite::createWithSpriteFrameName(fileName);
        gun->setAnchorPoint(Point::ANCHOR_MIDDLE);
        gun->setPosition(_fighterIcon->getContentSize().width/2,_fighterIcon->getContentSize().height/2);
        _fighterIcon->addChild(gun);
        this->scheduleUpdate();
    }

    ret = true;

    _fighterType = type;
    _fighterLevel = level;

    auto listener = EventListenerCustom::create(GameConfig::eventPlayerDestroy, [=](EventCustom* event){
        if (_attTarget == event->getUserData())
        {
            this->stopAllActions();
            this->unschedule(schedule_selector(Fighter::fire));
            state = FighterState::IDLE;
            _attTarget = nullptr;
        }
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return ret;
}

void Fighter::moveTo(Point& pos,Player* target)
{
    state = FighterState::MOVE;
    _attTarget = target;
    float dx = _position.x - pos.x;
    float dy = _position.y - pos.y;
    auto dis = sqrtf(dx*dx + dy*dy);
    
    switch (_attacker) {
        case Attacker::ENEMY:
            this->runAction(Sequence::create(MoveTo::create(dis / enemyConfig.speed,pos), CallFunc::create(
                                                                                                           [&](){
                                                                                                               state = FighterState::IDLE;
                                                                                                           }  ),nullptr));
            break;
        case Attacker::BOSS:
            this->runAction(Sequence::create(MoveTo::create(dis / bossConfig.speed,pos), CallFunc::create(
                                                                                                           [&](){
                                                                                                               state = FighterState::IDLE;
                                                                                                           }  ),nullptr));
            break;
        case Attacker::PLAIN:
            this->runAction(Sequence::create(MoveTo::create(dis / plainConfig.speed,pos), CallFunc::create(
                                                                                                           [&](){
                                                                                                               state = FighterState::IDLE;
                                                                                                           }  ),nullptr));
            break;
        case Attacker::TOWER:
            break;
        default:
            break;
    }
}

void Fighter::attackLocations(Point& pos,Player* target)
{
    state = FighterState::ATTACK;
    _attTargetPos = pos;
    _attTarget = target;

    this->stopAllActions();

    this->unschedule(schedule_selector(Fighter::fire));
    fire(0.0f);
    this->schedule(schedule_selector(Fighter::fire),3.0f);

    //this->runAction(RotateTo::create(0.2f,_position.getAngle(_attTargetPos) * 180));
    log("ang:%f",_position.getAngle(_attTargetPos) * 180);
    
    if(_attacker == Attacker::TOWER && gun)
    {
        gun->setRotation((_position.getAngle(_attTargetPos)) * 180+180);
    }
    
}

void Fighter::fire(float dt)
{
    switch (_attacker)
    {
        case Attacker::ENEMY:
        {
            auto bullet = Bullet::createBullet(Attacker::ENEMY,_fighterType,_fighterLevel);
            bullet->setPosition(_position);
            _parent->addChild(bullet);
            bullet->attackLocations(_attTargetPos,_attTarget);
            log("fire_pos:%f,%f",_attTargetPos.x,_attTargetPos.y);
        }
            break;
        case Attacker::BOSS:
        {
            auto bullet = Bullet::createBullet(Attacker::BOSS,9,_fighterLevel);
            bullet->setPosition(_position);
            _parent->addChild(bullet);
            bullet->attackLocations(_attTargetPos,_attTarget);
            log("fire_pos:%f,%f",_attTargetPos.x,_attTargetPos.y);
        }
            break;
        case Attacker::TOWER:
        {
            auto bullet = Bullet::createBullet(Attacker::TOWER,9,_fighterLevel);
            bullet->setPosition(_position);
            _parent->addChild(bullet);
            bullet->attackLocations(_attTargetPos,_attTarget);
            log("fire_pos:%f,%f",_attTargetPos.x,_attTargetPos.y);
        }
            break;
        case Attacker::PLAIN:
        {
            auto bullet = Bullet::createBullet(Attacker::PLAIN,_fighterType,_fighterLevel);
            bullet->setPosition(_position);
            _parent->addChild(bullet);
            bullet->attackLocations(_attTargetPos,_attTarget);
        }
            break;
        default:
            break;
    }
}

void Fighter::hurt(int ATK)
{
    switch (_attacker)
    {
        case Attacker::ENEMY:
            if (ATK > enemyConfig.defense)
            {
                _curlife -= ATK;
            }
            break;
        case Attacker::BOSS:
            if (ATK > bossConfig.defense)
            {
                _curlife -= ATK;
            }
            break;
        case Attacker::TOWER:
            if (ATK > towerConfig.defense)
            {
                _curlife -= ATK;
            }
            break;
        case Attacker::PLAIN:
            if (ATK > plainConfig.defense)
            {
                _curlife -= ATK - plainConfig.defense;
            }
            break;
        default:
            break;
    }

    if (_curlife > 0) {
        _bloodbar->setPercent((float(_curlife*100))/_maxlife);
    }
    else
    {
        state = FighterState::DESTROY;
        _bloodbar->setPercent(0);
        potInRadar->removeFromParent();
        CC_SAFE_RELEASE(potInRadar);
        this->unschedule(schedule_selector(Fighter::fire));
        _eventDispatcher->dispatchCustomEvent(GameConfig::eventPlayerDestroy,this);
        this->removeFromParentAndCleanup(true);
    }
}

void Fighter::update(float dt)
{
    if(_attacker == Attacker::TOWER && gun)
    {
        if (state == FighterState::IDLE)
        {
            int curangel = (int)gun->getRotation();
            gun->setRotation(++curangel%360);
        }
    }
}