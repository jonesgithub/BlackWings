#include "Battleground.h"
#include "PlayerBar.h"
#include "LoadResourceLayer.h"
#include "VisibleRect.h"
#include "MenuItemImageLabel.h"
#include "GameStrings.h"
#include "MenuSettings.h"
#include "Fighter.h"


USING_NS_CC;

Battleground* s_battleground = nullptr;

Battleground::Battleground()
{
    _stage = 0;
    
    //todo:配置基地血量
    _curPlayerBase_Blood = _playerBase_Blood = 1000;
    _curEnemyBase_Blood = _enemyBase_Blood = 1000;
    
    s_battleground = this;
    s_players.clear();
    s_enemys.clear();

    explode_A = nullptr;
    explode_B = nullptr;
    explode_C = nullptr;
}

Battleground::~Battleground()
{
    s_players.clear();
    s_enemys.clear();

    CC_SAFE_RELEASE_NULL(explode_A);
    CC_SAFE_RELEASE_NULL(explode_B);
    CC_SAFE_RELEASE_NULL(explode_C);
}

Battleground* Battleground::create(int stage)
{
    auto ret = new Battleground;

    if (ret && ret->init(stage))
    {
        ret->autorelease();

        return ret;
    }

    delete ret;
    return nullptr;
}

bool Battleground::init(int stage)
{
    if (Scene::init())
    {
        auto loadLayer = LoadResourceLayer::create(CC_CALLBACK_1(Battleground::createBattleground, this));
        loadLayer->addImage("battle/createBombTip_box.png");
        loadLayer->addPlist("map/map_clouds.plist","map/map_clouds.png");
        loadLayer->addPlist("battle/bases.plist","battle/bases.png");
        loadLayer->addPlist("battle/battle.plist","battle/battle.png");        
        loadLayer->addPlist("battle/e_bullets.plist","battle/e_bullets.png");
        loadLayer->addPlist("battle/explode_A.plist","battle/explode_A.png");
        loadLayer->addPlist("battle/explode_B.plist","battle/explode_B.png");
        loadLayer->addPlist("battle/explode_C.plist","battle/explode_C.png");
        loadLayer->addPlist("battle/p_bullets.plist","battle/p_bullets.png");
        loadLayer->addPlist("battle/plainFire.plist","battle/plainFire.png");
        loadLayer->addPlist("battle/enemys.plist","battle/enemys.png");
        this->addChild(loadLayer);
        loadLayer->startLoad();
        
        _stage = stage;

        return true;
    }

    return false;
}

void Battleground::eventCallbackPlayerSelect(EventCustom* event)
{
    int index = (uintptr_t)event->getUserData();

    if (index < 6)
    {
        //auto buildBox = Sprite::createWithSpriteFrameName("plain_progress_box.png");


        auto player = Fighter::createPlain(index);
        player->setPosition(Point(s_visibleRect.visibleOriginX + 100 + rand()%440,
            s_visibleRect.visibleOriginY + 100 + rand()% 50));
        _battleParallaxNode->addChild(player);
        
        this->addChild(player->potInRadar, 100);

        s_players.push_back(player);
    }
    else
    {

    }
}

void Battleground::battleLoop(float dt)
{
    
    plainFindTarget();

    enemyFindTarget();

}

void Battleground::plainFindTarget()
{
    Point bossPos(s_visibleRect.visibleWidth /2, s_visibleRect.visibleOriginY +_battlegroundHeight - 130);
    Point plainTargetPos;
    float nearestDistance,distance;

    for (auto player : s_players)
    {
        Player* attTarget = nullptr;

        if (player->state == FighterState::IDLE || player->state == FighterState::MOVE)
        {
            const auto& playerPos = player->getPosition();
            nearestDistance = bossPos.getDistance(playerPos);
            plainTargetPos = bossPos;

            for (auto enemy : s_enemys)
            {
                distance = enemy->getPosition().getDistance(playerPos);
                if (distance < nearestDistance)
                {
                    nearestDistance = distance;
                    plainTargetPos = enemy->getPosition();
                    attTarget = enemy;
                }
            }

            if (player->state == FighterState::IDLE)
            {
                player->moveTo(plainTargetPos,attTarget);
            } 
            else if(nearestDistance < player->plainConfig.range * 2)
            {
                player->attackLocations(plainTargetPos,attTarget);
                log("Player ======>>>> attack...");
                _enemyBase_Blood-=player->plainConfig.attack;
                if (_enemyBase_Blood>0) {
                    _enemyBloodBar->setPercent((float(_curEnemyBase_Blood))/_enemyBase_Blood);
                }
                else{
                    _enemyBloodBar->setPercent(0);
                    //win;
                }
            }
        }
    }
}

void Battleground::enemyFindTarget()
{
    Point basePos(s_visibleRect.visibleWidth /2, s_visibleRect.visibleOriginY + 280);
    Point enemyTargetPos;
    float nearestDistance,distance;

    for (auto enemy : s_enemys)
    {
        if (enemy->state == FighterState::IDLE || enemy->state == FighterState::MOVE)
        {
            Player* attTarget = nullptr;
            const auto& enemyPos = enemy->getPosition();
            nearestDistance = basePos.getDistance(enemyPos);
            enemyTargetPos = basePos;

            for (auto player : s_players)
            {
                distance = player->getPosition().getDistance(enemyPos);
                if (distance < nearestDistance)
                {
                    nearestDistance = distance;
                    enemyTargetPos = player->getPosition();
                    attTarget = player;
                }
            }

            if (enemy->state == FighterState::IDLE)
            {
                enemy->moveTo(enemyTargetPos,attTarget);
            } 
            else if(nearestDistance < enemy->enemyConfig.range * 2)
            {
                enemy->attackLocations(enemyTargetPos,attTarget);
                log("Enemy=======>>>> attack ");
                _curPlayerBase_Blood-=enemy->plainConfig.attack;
                _enemyBloodBar->setPercent((float(_curPlayerBase_Blood))/_playerBase_Blood);
                if (_curPlayerBase_Blood<0) {
                    //lost;
                }
            }
        }
    }
}

void Battleground::dispatchEnemys(float dt)
{
    int dispatchNum = 1;//rand()%5 + 1;
    for (int index = 0; index < dispatchNum; ++index)
    {
        //
        int type = rand() %  10;
        int level = 2;

        auto enemy = Fighter::createEnemy(type,level);
        enemy->setPosition(Point(s_visibleRect.visibleOriginX + 100 + rand()%440,
            s_visibleRect.visibleOriginY + _battlegroundHeight));
        _battleParallaxNode->addChild(enemy);
        
        enemy->potInRadar->setPosition(Point(-100,-100));
        this->addChild(enemy->potInRadar,100);

        s_enemys.push_back(enemy);
    }
}

void Battleground::createBattleground(Ref *sender)
{
    this->removeChild((LoadResourceLayer*)sender,true);

    _battlegroundHeight = s_visibleRect.visibleHeight * 3;
    _battleParallaxNode = Node::create();
    this->addChild(_battleParallaxNode);
    
    auto map = Sprite::createWithSpriteFrameName("startLayer.png");
    map->setPosition(s_visibleRect.center);
    map->setScale(2.0f, 5.0f);
    _battleParallaxNode->addChild(map);

    createFighterBase();

    createRadarChart();

    createHealthBar();

    auto playerBag = PlayerBar::create();
    this->addChild(playerBag);

    this->schedule(schedule_selector(Battleground::battleLoop),0.1f);

    this->schedule(schedule_selector(Battleground::dispatchEnemys),5.0f);
    
    this->schedule(schedule_selector(Battleground::showPotInRadar), 0.1f);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(Battleground::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Battleground::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Battleground::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto destroyListener = EventListenerCustom::create(GameConfig::eventPlayerDestroy, 
        CC_CALLBACK_1(Battleground::callbackPlayerDestroy,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(destroyListener, this);

    createAnimations();
}

void Battleground::createFighterBase()
{
    auto playerBaseLeft = Sprite::createWithSpriteFrameName("base_1.png");
    playerBaseLeft->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    playerBaseLeft->setPosition(Point(s_visibleRect.bottom.x,s_visibleRect.bottom.y + 160));
    _battleParallaxNode->addChild(playerBaseLeft);
    auto playerBaseRight = Sprite::createWithSpriteFrameName("base_1.png");
    playerBaseRight->setFlippedX(true);
    playerBaseRight->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    playerBaseRight->setPosition(Point(s_visibleRect.bottom.x,s_visibleRect.bottom.y + 160));
    _battleParallaxNode->addChild(playerBaseRight);

    auto enemyBaseLeft = Sprite::createWithSpriteFrameName("base_2.png");
    enemyBaseLeft->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    enemyBaseLeft->setPosition(Point(s_visibleRect.top.x,s_visibleRect.visibleOriginY + _battlegroundHeight));
    _battleParallaxNode->addChild(enemyBaseLeft);
    auto enemyBaseRight = Sprite::createWithSpriteFrameName("base_2.png");
    enemyBaseRight->setFlippedX(true);
    enemyBaseRight->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    enemyBaseRight->setPosition(Point(s_visibleRect.top.x,s_visibleRect.visibleOriginY + _battlegroundHeight));
    _battleParallaxNode->addChild(enemyBaseRight);
}

void Battleground::createAnimations()
{
    explode_A = Animation::create();
    explode_A->retain();
    explode_B = Animation::create();
    explode_B->retain();
    explode_C = Animation::create();
    explode_C->retain();

    char szName[100] = {0};
    auto frameCache = SpriteFrameCache::getInstance();
    for( int i = 1; i < 17; i++)
    {
        sprintf(szName, "explode_A_%d.png", i);
        Battleground::explode_A->addSpriteFrame(frameCache->getSpriteFrameByName(szName));
    }
    explode_A->setDelayPerUnit(0.042f);//1/24

    for( int i = 1; i < 20; i++)
    {
        sprintf(szName, "explode_B_%d.png", i);
        explode_B->addSpriteFrame(frameCache->getSpriteFrameByName(szName));

        sprintf(szName, "explode_C_%d.png", i);
        explode_C->addSpriteFrame(frameCache->getSpriteFrameByName(szName));
    }
    explode_B->setDelayPerUnit(0.042f);
    explode_C->setDelayPerUnit(0.042f);

    /*for( int i = 1; i < 20; i++)
    {
        sprintf(szName, "explode_C_%d.png", i);
        explode_C->addSpriteFrameWithFileName(szName);
    }
    explode_C->setDelayPerUnit(2.8f / 14.0f);*/
}

void Battleground::onEnter()
{
    Scene::onEnter();
    _eventDispatcher->addCustomEventListener(PlayerBar::eventPlayerSelect,
        std::bind(&Battleground::eventCallbackPlayerSelect, this, std::placeholders::_1));
}

void Battleground::onExit()
{
    _eventDispatcher->removeCustomEventListeners(PlayerBar::eventPlayerSelect);
    Scene::onExit();
}

void Battleground::createHealthBar()
{
    auto bar = Sprite::createWithSpriteFrameName("battle_box.png");
    bar->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bar->setPosition(s_visibleRect.top);
    this->addChild(bar);

    auto itemPause = MenuItemImageLabel::createWithFrameName("battle_pause_0.png","battle_pause_1.png",
        CC_CALLBACK_1(Battleground::menuCallbackPause,this),s_gameStrings.mainMenu->settings,
        "Arial",16);
    itemPause->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    itemPause->setPosition(s_visibleRect.top);

    auto menu = Menu::createWithItem(itemPause);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    auto player_icon = Sprite::createWithSpriteFrameName("icon_plain.png");
    player_icon->setPosition(Point(35,27));
    bar->addChild(player_icon);
    
    auto enemy_icon = Sprite::createWithSpriteFrameName("icon_enemy.png");
    enemy_icon->setPosition(Point(595,27));
    bar->addChild(enemy_icon);
    
    auto _playerBkBar = Sprite::createWithSpriteFrameName("battle_lifeBox.png");
    _playerBkBar->setPosition(Point(160,27));
    bar->addChild(_playerBkBar);
    
    _playerBloodBar = ui::LoadingBar::create("battle_life_plain.png");
    _playerBloodBar->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    _playerBloodBar->setPositionY(3);
    _playerBkBar->addChild(_playerBloodBar);
    
    auto _enmeyBkBar = Sprite::createWithSpriteFrameName("battle_lifeBox.png");
    _enmeyBkBar->setPosition(Point(475,27));
    bar->addChild(_enmeyBkBar);
    
    _enemyBloodBar = ui::LoadingBar::create("battle_life_enemy.png");
    _enemyBloodBar->setPositionY(3);
    _enemyBloodBar->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    _enmeyBkBar->addChild(_enemyBloodBar);

    
    //_battleParallaxNode->addChild(bar,1,Point(1,1),Point(s_visibleRect.center.x,s_visibleRect.visibleHeight * 3));
}

void Battleground::menuCallbackPause(Ref *sender)
{
    auto settingLayer = MenuSettings::create(GameInterface::Battle);
    addChild(settingLayer);
}

void Battleground::createRadarChart()
{
    //radar
    radarChart = Sprite::createWithSpriteFrameName("map_box.png");
    radarChart->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    radarChart->setPosition(Point(s_visibleRect.visibleOriginX + 15,s_visibleRect.top.y - 60));
    this->addChild(radarChart);
    
    radarScreen = Sprite::createWithSpriteFrameName("map_screen.png");
    radarScreen->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    radarScreen->setPosition(Point(0, 95));//down:95; up:310
    radarChart->addChild(radarScreen);
    
    //text
    auto stageTextBox = Sprite::createWithSpriteFrameName("stageName_box.png");
    stageTextBox->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    stageTextBox->setPosition(Point(s_visibleRect.visibleOriginX + 15,
        s_visibleRect.top.y - 50 - radarChart->getContentSize().height));
    this->addChild(stageTextBox);
    
    std::string str = "STAGE" + Value(_stage).asString();
    auto stageText = Label::createWithTTF(str,"fonts/arial.ttf",12);
    stageText->setAnchorPoint(Point::ANCHOR_MIDDLE);
    stageText->setPosition(Point(stageTextBox->getContentSize().width/2,stageTextBox->getContentSize().height/2));
    stageTextBox->addChild(stageText);

 }

bool Battleground::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void Battleground::onTouchMoved(Touch* touch, Event* event)
{
    auto op = _battleParallaxNode->getPosition();
    op.y += touch->getLocation().y - touch->getPreviousLocation().y;
    if (op.y < s_visibleRect.visibleHeight - _battlegroundHeight)
    {
        op.y = s_visibleRect.visibleHeight - _battlegroundHeight;
    }
    else if(op.y > 0)
    {
        op.y = 0;
    }
    
    auto ratio  = - (op.y/(s_visibleRect.visibleHeight*2));
    auto radarscreenposY = RADARSCREEN_DOWN + (RADARSCREEN_UP - RADARSCREEN_DOWN) * ratio;
    radarScreen->setPositionY(radarscreenposY);
    
    _battleParallaxNode->setPosition(op);
}

void Battleground::onTouchEnded(Touch* touch, Event* event)
{

}

void Battleground::callbackPlayerDestroy(EventCustom* event)
{
    Fighter* player = (Fighter*)event->getUserData();

    switch (player->_attacker)
    {
    case Attacker::ENEMY:
        {
            const auto& it = std::find(s_enemys.begin(),s_enemys.end(),player);
            if (it != s_enemys.end())
            {
                s_enemys.erase(it);
            }
            break;
        }
    case Attacker::PLAIN:
        {
            const auto& it = std::find(s_players.begin(),s_players.end(),player);
            if (it != s_players.end())
            {
                s_players.erase(it);
            }
            break;
        }
    default:
        break;
    }

    if (player)
    {
        auto explode = Sprite::create();
        auto action = Sequence::create(Animate::create(s_battleground->explode_C),
            CallFuncN::create([](Node* sender){
                sender->removeFromParentAndCleanup(true);
        }),nullptr);
        explode->runAction(action);
        explode->setPosition(player->getPosition());
        _battleParallaxNode->addChild(explode); 
    }
}

void Battleground::showPotInRadar(float dt)
{
    for (auto player : s_players)
    {
        auto ratioX = player->getPositionX()/s_visibleRect.visibleWidth;
        auto ratioY = player->getPositionY()/(s_visibleRect.visibleHeight*3);
        
        auto actualX = 15 + radarChart->getContentSize().width * ratioX;
        auto actualY = 590 + radarChart->getContentSize().height * ratioY;
        
        player->potInRadar->setPosition(Point(actualX,actualY));

    }
    
    for (auto enemy : s_enemys)
    {
        auto ratioX = enemy->getPositionX()/s_visibleRect.visibleWidth;
        auto ratioY = enemy->getPositionY()/(s_visibleRect.visibleHeight*3);
        
        auto actualX = 15 + radarChart->getContentSize().width * ratioX;
        auto actualY = 590 + radarChart->getContentSize().height * ratioY;
        
        enemy->potInRadar->setPosition(Point(actualX,actualY));
    }
}
