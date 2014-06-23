#include "Fighter.h"
#include "Configuration.h"
#include "Bullet.h"

USING_NS_CC;

const float PI = 3.1415926;

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

//特别要同时传入类型和等级
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
    if (ret && ret->initFighter(Attacker::BOSS,9,level))//9会被忽略
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
    if (ret && ret->initFighter(Attacker::TOWER,9,level))//9会被忽略
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
_curlife(0),
isInBlackhole(false),
_isRotating(false),
_isDogging(false)
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
        {
            sprintf(fileName,"enemy_%d_lv_%d.png",type + 1,level + 1);
            enemyConfig = s_enemyConfigs[type][level];
            _curlife = _maxlife = enemyConfig.life;
            potInRadar = Sprite::createWithSpriteFrameName("map_enemy.png");
            potInRadar->retain();
        }
            break;
        case Attacker::BOSS:
        {
            sprintf(fileName,"boos_%d.png",level + 1);
            bossConfig = s_bossConfig[level];
            _curlife = _maxlife = bossConfig.life;
            potInRadar = Sprite::createWithSpriteFrameName("map_enemy.png");
            potInRadar->retain();
        }
            break;
        case Attacker::TOWER:
        {
            sprintf(fileName,"fixed_enemy_%d.png",level + 1);
            towerConfig = s_towerConfig[level];
            _curlife = _maxlife = towerConfig.life;
            potInRadar = Sprite::createWithSpriteFrameName("map_enemy.png");
            potInRadar->retain();
        }
            break;
        case Attacker::PLAIN:
        {
            level = s_playerConfig.fighterslevel[type];
            sprintf(fileName,"plain_%d_lv_%d.png",type + 1,level + 1);
            plainConfig = s_plainConfigs[type][level];
            _curlife = _maxlife = plainConfig.life;
            potInRadar = Sprite::createWithSpriteFrameName("map_plain.png");
            potInRadar->retain();
        }
            break;
        default:
            break;
    }
    
    _fighterIcon = Sprite::createWithSpriteFrameName(fileName);
    auto iconSize = _fighterIcon->getContentSize();
    _fighterIcon->setPosition(Point(iconSize.width/2, iconSize.height/2));
    this->setContentSize(_fighterIcon->getContentSize());
    this->addChild(_fighterIcon,1,1);
    if(attacker != Attacker::PLAIN)
        _fighterIcon->setRotation(180);
    
    //飞机尾部带火
    if (attacker == Attacker::PLAIN) {
        
        auto plainfire = Sprite::createWithSpriteFrameName("plainFire_0.png");
        plainfire->setScale(0.8f);
        plainfire->setAnchorPoint(Point::ANCHOR_MIDDLE);
        plainfire->setPosition(_fighterIcon->getPosition().x,5);
        _fighterIcon->addChild(plainfire,-1,2);
        
        auto plainfireanimation = Animation::create();
        plainfireanimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plainFire_0.png"));
        plainfireanimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plainFire_1.png"));
        plainfireanimation->setDelayPerUnit(0.3f);
        plainfire->runAction(RepeatForever::create(Animate::create(plainfireanimation)));
    }
    
    //血条
    if (attacker == Attacker::ENEMY || attacker == Attacker::BOSS || attacker == Attacker::TOWER )
    {
        _bloodbar = ui::LoadingBar::create("enemy_life_pro.png");
        _bloodbar->setAnchorPoint(Point::ANCHOR_MIDDLE);
        _bloodbar->setPosition(Point(_fighterIcon->getContentSize().width/2,_fighterIcon->getContentSize().height+10));
        this->addChild(_bloodbar);
        _bloodbar->setPercent(100);
    }
    else if(attacker == Attacker::PLAIN)
    {
        _bloodbar = ui::LoadingBar::create("plain_life_pro.png");
        _bloodbar->setAnchorPoint(Point::ANCHOR_MIDDLE);
        _bloodbar->setPosition(Point(_fighterIcon->getContentSize().width/2,-10));
        this->addChild(_bloodbar);
        _bloodbar->setPercent(100);
    }
    
    //守卫塔带炮
    if(_attacker == Attacker::TOWER)
    {
        sprintf(fileName,"fixed_enemy_%d_gun.png",level + 1);
        gun = Sprite::createWithSpriteFrameName(fileName);
        gun->setAnchorPoint(Point::ANCHOR_MIDDLE);
        gun->setPosition(_fighterIcon->getContentSize().width/2,_fighterIcon->getContentSize().height/2);
        _fighterIcon->addChild(gun);
        gun->setRotation(90);
    }

    ret = true;

    _fighterType = type;
    _fighterLevel = level;

    //攻击对象死亡，停止射击
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

    this->scheduleUpdate();

    return ret;
}

//taget为nullptr代表对方基地
void Fighter::moveTo(Point& pos,Player* target)
{
    state = FighterState::MOVE;
    _attTarget = target;
    _attTargetPos = pos;
    float dx = _position.x - pos.x;
    float dy = _position.y - pos.y;
    auto dis = sqrtf(dx*dx + dy*dy);
    
    auto targetdelta = atanf((_position.x-_attTargetPos.x)/(_position.y-_attTargetPos.y))*180/PI;
    if(_attacker != Attacker::PLAIN)
        targetdelta += 180;
    _isRotating = true;
    
    switch (_attacker) {
        case Attacker::ENEMY:
            this->runAction(Sequence::create(CallFunc::create([=](){this->getChildByTag(1)->runAction(RotateTo::create(0.6f, targetdelta));}), DelayTime::create(0.6f),MoveTo::create(dis / enemyConfig.speed,pos), CallFunc::create(
                                                                                                           [&](){
                                                                                                               state = FighterState::IDLE;
                                                                                                               _isRotating = false;
                                                                                                           }  ),nullptr));
            break;
        case Attacker::BOSS:
            this->runAction(Sequence::create(CallFunc::create([=](){this->getChildByTag(1)->runAction(RotateTo::create(0.6f, targetdelta));}), DelayTime::create(0.6f), MoveTo::create(dis / bossConfig.speed,pos), CallFunc::create(
                                                                                                           [&](){
                                                                                                               state = FighterState::IDLE;
                                                                                                               _isRotating = false;
                                                                                                           }  ),nullptr));
            break;
        case Attacker::PLAIN:
            this->runAction(Sequence::create(CallFunc::create([=](){this->getChildByTag(1)->runAction(RotateTo::create(0.6f, targetdelta));}), DelayTime::create(0.6f), MoveTo::create(dis / plainConfig.speed,pos), CallFunc::create(
                                                                                                           [&](){
                                                                                                               state = FighterState::IDLE;
                                                                                                               _isRotating = false;
                                                                                                           }  ),nullptr));
            break;
        case Attacker::TOWER://守卫塔无法移动，speed是无效的
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

    if(_attacker != Attacker::TOWER)
    {
        auto targetdelta = atanf((_position.x-_attTargetPos.x)/(_position.y-_attTargetPos.y))*180/PI;
        if(_attacker != Attacker::PLAIN)
            targetdelta += 180;
        _isRotating = true;
        this->getChildByTag(1)->runAction(Sequence::create(RotateTo::create(0.6f, targetdelta),
                                                           CallFunc::create([=]()
                                                                            {
                                                                                _isRotating = false;
                                                                                this->unschedule(schedule_selector(Fighter::fire));
                                                                                fire(0.0f);
                                                                                this->schedule(schedule_selector(Fighter::fire),3.0f);
                                                                            }),
                                                           nullptr));
    }
    else //守卫塔需要先将炮头转过来再射击，时间要重新算
    {
        auto targetdelta = atanf((_position.x-_attTargetPos.x)/(_position.y-_attTargetPos.y))*180/PI+180;
        gun->runAction(Sequence::create(RotateTo::create(0.3f, targetdelta),
                                        CallFunc::create([=]()
                                                         {
                                                             this->unschedule(schedule_selector(Fighter::fire));
                                                             fire(0.0f);
                                                             this->schedule(schedule_selector(Fighter::fire),3.0f);
                                                         }),
                                        nullptr));
    }
    
}

//开火允许_attTarget为nullptr
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
//            log("fire_pos:%f,%f",_attTargetPos.x,_attTargetPos.y);
        }
            break;
        case Attacker::BOSS:
        {
            auto bullet = Bullet::createBullet(Attacker::BOSS,9,_fighterLevel);
            bullet->setPosition(_position);
            _parent->addChild(bullet);
            bullet->attackLocations(_attTargetPos,_attTarget);
//            log("fire_pos:%f,%f",_attTargetPos.x,_attTargetPos.y);
        }
            break;
        case Attacker::TOWER:
        {
            auto bullet = Bullet::createBullet(Attacker::TOWER,9,_fighterLevel);
            bullet->setPosition(_position);
            _parent->addChild(bullet);
            bullet->attackLocations(_attTargetPos,_attTarget);
//            log("fire_pos:%f,%f",_attTargetPos.x,_attTargetPos.y);
        }
            break;
        case Attacker::PLAIN:
        {
            log("Attacker::PLAIN::fire....");
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

//简单的受伤判断方式
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
        //判断是否是在黑洞中
        if(state == FighterState::MOVE)
            this->stopAllActions();
        this->unschedule(schedule_selector(Fighter::fire));
        state = FighterState::DESTROY;

        if(isInBlackhole)
        {
            //this->runAction(RotateTo::create(0.3f, 90));
            this->setRotation(this->getRotation()+360);
            this->runAction(Sequence::create(Spawn::create(MoveBy::create(0.3f, offsetWithBlackhole),
                                                           ScaleTo::create(0.3f, 0.2f),
                                                           RotateBy::create(0.3f, 120),
                                                           nullptr),
                                             CallFunc::create([=]()
            {
                _bloodbar->setPercent(0);
                potInRadar->removeFromParent();
                CC_SAFE_RELEASE(potInRadar);
                _eventDispatcher->dispatchCustomEvent(GameConfig::eventPlayerDestroy,this);
                this->removeFromParentAndCleanup(true);
            }),
                                             NULL));
        }
        else
        {
            _bloodbar->setPercent(0);
            potInRadar->removeFromParent();
            CC_SAFE_RELEASE(potInRadar);
            _eventDispatcher->dispatchCustomEvent(GameConfig::eventPlayerDestroy,this);
            this->removeFromParentAndCleanup(true);
        }
    }
}

//守卫塔idle时旋转炮塔
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
    else
    {
        if(state == FighterState::MOVE && !_isRotating)
        {
            float dx = _position.x - _attTargetPos.x;
            float dy = _position.y - _attTargetPos.y;
            float delta = atan(dx/dy)*180/PI;
            if (_attacker != Attacker::PLAIN) {
                delta += 180;
            }
            //this->setRotation(delta);
            this->getChildByTag(1)->setRotation(delta);
        }
    }
}