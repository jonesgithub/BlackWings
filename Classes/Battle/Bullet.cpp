#include "Bullet.h"
#include "Configuration.h"
#include "Battleground.h"
#include "Player.h"

USING_NS_CC;

extern Battleground* s_battleground;
const float PI = 3.1415926;

Bullet* Bullet::createBullet(Attacker attacker,int type,int level)
{
    auto ret = new (std::nothrow) Bullet;
    if (ret && ret->initBullet(attacker,type,level))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

Bullet::Bullet()
: _attTarget(nullptr)
, _fire(false)
, _attack(0)
{
}

Bullet::~Bullet()
{
}

bool Bullet::initBullet(Attacker attacker,int type,int level)
{
    bool ret = false;

    _attacker = attacker;
    _level = level;
    _type = type;

    char fileName[30];

    switch (attacker)
    {
        case Attacker::ENEMY:
            sprintf(fileName,"e_bullet_%d_%d.png",type + 1,level + 1);
            _attack = s_enemyConfigs[type][level].attack;
            break;
        case Attacker::BOSS:
            sprintf(fileName,"e_bullet_%d_%d.png",type + 1,level + 1);
            _attack = s_bossConfig[level].attack;
            break;
        case Attacker::TOWER:
            sprintf(fileName,"e_bullet_%d_%d.png",type + 1,level + 1);
            _attack = s_towerConfig[level].attack;
            break;
        case Attacker::PLAIN:
            sprintf(fileName,"p_bullet_%d_%d.png",type + 1,level + 1);
            _attack = s_plainConfigs[type][level].attack;
            switch (type)
        {
            case 0:
                _trace = false;
                _attackMode = AttackMode::SINGLE;
                break;
            case 1:
                _trace = false;
                _attackMode = AttackMode::SINGLE;
                break;
            case 2:
                _trace = true;
                _attackMode = AttackMode::RANG;
                break;
            case 3:
                _trace = false;
                _attackMode = AttackMode::SINGLE;
                break;
            case 4:
                _trace = false;
                _attackMode = AttackMode::DIFFUSION;
                break;
            case 5:
                _trace = true;
                _attackMode = AttackMode::SINGLE;
                break;
            default:
                break;
        }
            break;
        default:
            break;
    }
    
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
    ret = initWithSpriteFrame(frame);

    if (ret)
    {
        auto listener = EventListenerCustom::create(GameConfig::eventPlayerDestroy, [=](EventCustom* event){
            if (_attTarget == event->getUserData())
            {
                _attTarget = nullptr;
            }
        });

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }

    return ret;
}

void Bullet::attackLocations(Point& pos,Player* target)
{
    if (target)
    {
        _attTargetPos = target->getPosition();
    }
    else
    {
        _attTargetPos = pos;
    }
    
    _attTarget = target;
    
    float dx = _position.x - _attTargetPos.x;
    float dy = _position.y - _attTargetPos.y;
    float delta = atan(dx/dy)*180/PI;
    this->setRotation(delta);
    
    auto action = Sequence::create(MoveTo::create(0.3f,_attTargetPos),CallFuncN::create(
        [&](Node* node){
            switch (_attackMode)
            {
            case AttackMode::SINGLE:

                break;
            case AttackMode::RANG:
                break;
            case AttackMode::DIFFUSION:
                break;
            default:
                break;
            }
            auto explode = Sprite::create();
            auto action = Sequence::create(Animate::create(s_battleground->explode_A),
                CallFuncN::create([](Node* sender){
                    sender->removeFromParentAndCleanup(true);
            }),nullptr);
            explode->runAction(action);
            explode->setPosition(_position);
            _parent->addChild(explode); 

            if (_attTarget && _attTarget->getPosition().getDistance(_attTargetPos) < 30)
            {
                _attTarget->hurt(_attack);
            }
            else if(!_attTarget && _attTargetPos == s_PlayerBasePos)
            {
                _eventDispatcher->dispatchCustomEvent(GameConfig::eventPlayerBaseHurt,this);
            }
            else if(!_attTarget && _attTargetPos == s_EnemyBasePos)
            {
                _eventDispatcher->dispatchCustomEvent(GameConfig::eventEnemyBaseHurt,this);
            }
            node->removeFromParentAndCleanup(true);
    }  ),nullptr);

    this->runAction(action);
    PLAY_NORMALBULLET_EFFECT;
}

void Bullet::onEnter()
{
    Sprite::onEnter();
}