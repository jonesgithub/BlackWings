//
//  Weapon.cpp
//  BlackWings
//
//  Created by Jacky on 14-6-2.
//
//

#include "Weapon.h"
#include "VisibleRect.h"

USING_NS_CC;

Weapon* Weapon::createStarBomb(const cocos2d::Point& pos)
{
    auto ret = new (std::nothrow) Weapon;
    if (ret && ret->initWeapon(WeaponType::STARBOMB,pos))
    {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}

Weapon* Weapon::createLaser(const cocos2d::Point& pos)
{
    auto ret = new (std::nothrow) Weapon;
    if (ret && ret->initWeapon(WeaponType::LASER,pos))
    {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}

Weapon* Weapon::createBlackhole(const cocos2d::Point& pos)
{
    auto ret = new (std::nothrow) Weapon;
    if (ret && ret->initWeapon(WeaponType::BLACKHOLE,pos))
    {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}

bool Weapon::initWeapon(WeaponType weapontype, const cocos2d::Point& pos)
{
    _weaponType = weapontype;
    _pos = pos;

    auto target = Sprite::createWithSpriteFrameName("targetPosition.png");
    target->setAnchorPoint(Point::ANCHOR_MIDDLE);
    target->setPosition(_pos);
    target->setScale(3.0f);
    target->setOpacity(0);
    this->addChild(target);
    
    target->runAction(Sequence::create(
                                       Spawn::create(
                                                     FadeIn::create(0.5f),
                                                     ScaleTo::create(0.5f, 1.0f),
                                                     RotateBy::create(0.5f, 180),
                                                     nullptr),
                                       CallFunc::create([this](){createWeapon();}),
                                       RemoveSelf::create(),
                                       nullptr));
    
    return true;
}

void Weapon::createWeapon()
{
    char fileName[30];
    switch (_weaponType) {
        case WeaponType::STARBOMB:
        {
            sprintf(fileName,"bomb_1_%d.png",s_playerConfig.weaponslevel[0]+1);
            _weaponConfig = s_weaponConfigs[0][s_playerConfig.weaponslevel[0]];
            auto starbomb = Sprite::createWithSpriteFrameName(fileName);
            starbomb->setAnchorPoint(Point::ANCHOR_MIDDLE);
            starbomb->setPosition(Point(_pos.x, -100));
            this->addChild(starbomb);
            starbomb->runAction(Sequence::create(MoveTo::create(1.0f, _pos),
                                                 RemoveSelf::create(),
                                                 CallFunc::create([=]()
                                                                  {
                                                                      //显示粒子特效
                                                                      auto bomb_1_effectB = ParticleSystemQuad::create("bomb_1_effectB.plist");
                                                                      bomb_1_effectB->setPosition(_pos);
                                                                      this->addChild(bomb_1_effectB);
                                                                      bomb_1_effectB->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), nullptr));
                                                                      bomb_1_effectB->setPositionType(ParticleSystem::PositionType::GROUPED);
                                                                      _eventDispatcher->dispatchCustomEvent(GameConfig::eventStarbombHurt,this);
                                                                  }),
                                                 nullptr));
        }
            break;
        case WeaponType::LASER:
        {
            sprintf(fileName,"bomb_2_%d.png",s_playerConfig.weaponslevel[1]+1);
            _weaponConfig = s_weaponConfigs[1][s_playerConfig.weaponslevel[1]];
            auto laser = Sprite::createWithSpriteFrameName(fileName);
            laser->setAnchorPoint(Point::ANCHOR_MIDDLE);
            laser->setPosition(Point(_pos.x, -100));
            this->addChild(laser);
            laser->runAction(Sequence::create(MoveTo::create(1.0f, _pos-Point(0,100)),
                                                 RemoveSelf::create(),
                                                 CallFunc::create([&]()
                                                                  {
                                                                      char fileName_0[30];
                                                                      sprintf(fileName_0,"bomb_2_%d_A.png",s_playerConfig.weaponslevel[1]+1);
                                                                      auto bulletA = Sprite::createWithSpriteFrameName(fileName_0);
                                                                      bulletA->setAnchorPoint(Point::ANCHOR_MIDDLE);
                                                                      bulletA->setPosition(Point(_pos-Point(0,100)));
                                                                      bulletA->runAction(Sequence::create(
                                                                                                          Spawn::create(MoveBy::create(0.2f, Point(-50,50)),
                                                                                                                        RotateBy::create(0.2f, 45),
                                                                                                                        nullptr),
                                                                                                          Spawn::create(MoveTo::create(0.4f, Point(0,_pos.y)),
                                                                                                                        RotateBy::create(0.2f, 45),
                                                                                                                        nullptr),
                                                                                                          CallFunc::create([&]()
                                                                      {
                                                                          auto bomb_2_effectB = ParticleSystemQuad::create("bomb_2_effect.plist");
                                                                          bomb_2_effectB->setPositionType(ParticleSystem::PositionType::GROUPED);
                                                                          bomb_2_effectB->setPosition(Point(s_visibleRect.visibleWidth/2,_pos.y));
                                                                          getParent()->addChild(bomb_2_effectB);
                                                                          log("weapon config ....duration is %f",_weaponConfig.duration/10);                                                                          bomb_2_effectB->runAction(Sequence::create(DelayTime::create(_weaponConfig.duration/10), RemoveSelf::create(), nullptr));
                                                                          _eventDispatcher->dispatchCustomEvent(GameConfig::eventLaserHurt,this);
                                                                      }),
                                                                                                          nullptr));
                                                                      this->addChild(bulletA);
                                                                      
                                                                      sprintf(fileName_0,"bomb_2_%d_B.png",s_playerConfig.weaponslevel[1]+1);
                                                                      auto bulletB = Sprite::createWithSpriteFrameName(fileName_0);
                                                                      bulletB->setAnchorPoint(Point::ANCHOR_MIDDLE);
                                                                      bulletB->setPosition(Point(_pos-Point(0,100)));
                                                                      bulletB->runAction(Sequence::create(
                                                                                                          Spawn::create(MoveBy::create(0.2f, Point(50,50)),
                                                                                                                        RotateBy::create(0.2f, -45),
                                                                                                                        nullptr),
                                                                                                          Spawn::create(MoveTo::create(0.4f, Point(s_visibleRect.visibleWidth,_pos.y)),
                                                                                                                        RotateBy::create(0.2f, -45),
                                                                                                                        nullptr),
                                                                                                          nullptr));                                                                      this->addChild(bulletB);
                                                                      
                                                                  }),
                                                 nullptr));
        }
            break;
        case WeaponType::BLACKHOLE:
        {
            sprintf(fileName,"bomb_3_%d.png",s_playerConfig.weaponslevel[2]+1);
            _weaponConfig = s_weaponConfigs[2][s_playerConfig.weaponslevel[2]];
            auto blackhole = Sprite::createWithSpriteFrameName(fileName);
            blackhole->setAnchorPoint(Point::ANCHOR_MIDDLE);
            blackhole->setPosition(Point(_pos.x, -100));
            this->addChild(blackhole);
            blackhole->runAction(Sequence::create(MoveTo::create(1.0f, _pos),
                                                 RemoveSelf::create(),
                                                 CallFunc::create([this]()
                                                                  {
                                                                      //显示粒子特效
                                                                      auto bomb_3_effectB = ParticleSystemQuad::create("bomb_3_effect.plist");
                                                                      bomb_3_effectB->setPositionType(ParticleSystem::PositionType::GROUPED);
                                                                      bomb_3_effectB->setPosition(_pos);
                                                                      this->addChild(bomb_3_effectB);
                                                                      bomb_3_effectB->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), nullptr));
                                                                      _eventDispatcher->dispatchCustomEvent(GameConfig::eventBlackholeHurt,this);
                                                                  }),
                                                 nullptr));
        }
            break;
        default:
            break;
    }
}