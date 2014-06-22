#include "PlayerBar.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "PlayerMenuItem.h"
#include "PersonalApi.h"
#include "MedalChecker.h"

USING_NS_CC_EXT;

const std::string PlayerBar::eventPlayerSelect = "eventPlayerSelect";

bool PlayerBar::init()
{
    bool weaponEnable = true;
    _showFighter = true;

    auto leftBar = Sprite::createWithSpriteFrameName("dijia.png");
    leftBar->getTexture()->setAliasTexParameters();
    leftBar->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    leftBar->setPosition(s_visibleRect.bottom);
    this->addChild(leftBar);

    auto rightBar = Sprite::createWithSpriteFrameName("dijia.png");
    rightBar->getTexture()->setAliasTexParameters();
    rightBar->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    rightBar->setFlippedX(true);
    rightBar->setPosition(s_visibleRect.bottom);
    this->addChild(rightBar);

    float interval;
    if (weaponEnable)
    {
        interval = (s_visibleRect.visibleWidth - 40 - 65) / FIGHTER_MAX;
    } 
    else
    {
        interval = (s_visibleRect.visibleWidth - 40) / FIGHTER_MAX;
    }
    auto playerPos = Point(s_visibleRect.visibleOriginX + 20 + interval/2, s_visibleRect.visibleOriginY + 68);

    _playerMenu = Menu::create();
    
    for (int i = 0; i < FIGHTER_MAX; ++i)
    {
        auto player = PlayerMenuItem::create(PlayerMenuItem::Type::Fighter,i);
        player->setPosition(playerPos);
        player->setTag(1000+i);
        playerPos.x += interval;
        _playerMenu->addChild(player,1);

    }
    
    
    if (weaponEnable)
    {
        auto arrowItem = MenuItemImageLabel::createWithFrameName("bt_arrow_0.png","bt_arrow_1.png",
            CC_CALLBACK_1(PlayerBar::menuCallbackArrow,this));
        arrowItem->setPosition(Point(s_visibleRect.right.x - 15,playerPos.y));
        _playerMenu->addChild(arrowItem,0,0);

        interval = (s_visibleRect.visibleWidth - 105) / WEAPON_MAX;
        playerPos.x = s_visibleRect.visibleOriginX + s_visibleRect.visibleWidth + 50 + interval/2;
        for (int i = 0; i < WEAPON_MAX; ++i)
        {
            auto player = PlayerMenuItem::create(PlayerMenuItem::Type::Weapon,i);
            player->setPosition(playerPos);
            player->setTag(1000+FIGHTER_MAX+i);
            playerPos.x += interval;
            _playerMenu->addChild(player,0);
        }
    }

    _playerMenu->setPosition(Point::ZERO);
    this->addChild(_playerMenu,3);

    auto leftSidebar = Sprite::createWithSpriteFrameName("dijia2.png");
    leftSidebar->getTexture()->setAliasTexParameters();
    leftSidebar->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    leftSidebar->setPosition(s_visibleRect.leftBottom);
    this->addChild(leftSidebar,2);

    auto rightSidebar = Sprite::createWithSpriteFrameName("dijia2.png");
    rightSidebar->getTexture()->setAliasTexParameters();
    rightSidebar->setFlippedX(true);
    rightSidebar->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    rightSidebar->setPosition(s_visibleRect.rightBottom);
    this->addChild(rightSidebar,2);

    auto stoneIcon = Sprite::createWithSpriteFrameName("icon_stone.png");
    stoneIcon->setPosition(Point(s_visibleRect.center.x - 282,s_visibleRect.visibleOriginY + 165));
    stoneIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(stoneIcon,2);

    auto numBg = Sprite::createWithSpriteFrameName("numBackground.png");
    numBg->setPosition(Point(s_visibleRect.center.x - 237,s_visibleRect.visibleOriginY + 165));
    numBg->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(numBg,2);

    auto gemIcon = Sprite::createWithSpriteFrameName("icon_gem.png");
    gemIcon->setPosition(Point(s_visibleRect.center.x - 43,s_visibleRect.visibleOriginY + 165));
    gemIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(gemIcon,2);
    
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    
    auto slash = Label::createWithTTF("/",fontFile,fontSize);
    slash->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    slash->setPosition(Point(numBg->getContentSize().width/2,6));
    slash->setColor(Color3B(169,169,169));
    numBg->addChild(slash);
    
    stoneNum = Label::createWithTTF(PersonalApi::convertIntToString(s_stoneCapacity[s_playerConfig.stonecapacitylevel].initstone).c_str(),fontFile,fontSize);
    stoneNum->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    stoneNum->setPosition(Point(slash->getPositionX()-10,slash->getPositionY()));
    numBg->addChild(stoneNum);
    
    stoneTatalNum = Label::createWithTTF(PersonalApi::convertIntToString(s_stoneCapacity[s_playerConfig.stonecapacitylevel].maxstone).c_str(),fontFile,fontSize);
    stoneTatalNum->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    stoneTatalNum->setPosition(Point(slash->getPositionX()+10,slash->getPositionY()));
    stoneTatalNum->setColor(Color3B(169,169,169));
    numBg->addChild(stoneTatalNum);
    
    sparNum = Label::createWithTTF(PersonalApi::convertIntToString(s_playerConfig.gem).c_str(),fontFile,fontSize);
    sparNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    sparNum->setPosition(Point(gemIcon->getPositionX()+gemIcon->getContentSize().width+5,gemIcon->getPositionY()));
    sparNum->setColor(Color3B(255,255,0));
    this->addChild(sparNum,2);
    
    if(s_playerConfig.overstage >= STAGEOFCANBUYGEM)
    {
        menuitem_getmore = MenuItemImageLabel::createWithFrameName("bt_buy_gem_0.png", "bt_buy_gem_1.png", CC_CALLBACK_1(PlayerBar::getmoregem, this),s_gameStrings.base->getmoregem);
        menuitem_getmore->setColor(Color3B::YELLOW);
        menuitem_getmore->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        menuitem_getmore->setPosition(gemIcon->getPositionX()+gemIcon->getContentSize().width+280,gemIcon->getPositionY());
        
        auto menu_getmore = Menu::create(menuitem_getmore, nullptr);
        menu_getmore->setPosition(Point::ZERO);
        this->addChild(menu_getmore,2);
    }
    
    auto listener = EventListenerCustom::create(GameConfig::eventShowWeaponMenu, [=](EventCustom* event)
                                                {
                                                    if (_showFighter)
                                                    {
                                                        _showFighter = false;
                                                        _playerMenu->runAction(Sequence::create( MoveBy::create(0.25f,Point(-s_visibleRect.visibleWidth,0)),
                                                                                                MoveBy::create(0.1f,Point(30,0)), nullptr) );
                                                    }
                                                });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    auto updategemlistener = EventListenerCustom::create(GameConfig::eventUpdateGem, [=](EventCustom* event){setGem(s_playerConfig.gem);});
    _eventDispatcher->addEventListenerWithSceneGraphPriority(updategemlistener, this);
    
    auto languagelistener = EventListenerCustom::create(GameConfig::eventLanguageChange, [=](EventCustom* event)
                                                        {
                                                            menuitem_getmore->setText(s_gameStrings.base->getmoregem);
                                                        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(languagelistener, this);

    return true;
}

void PlayerBar::menuCallbackArrow(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    if (_showFighter)
    {
        _showFighter = false;
        _playerMenu->runAction(Sequence::create( MoveBy::create(0.25f,Point(-s_visibleRect.visibleWidth,0)),
            MoveBy::create(0.1f,Point(30,0)), nullptr) );
    } 
    else
    {
        _showFighter = true;
        _playerMenu->runAction(Sequence::create( MoveBy::create(0.25f,Point(s_visibleRect.visibleWidth,0)),
            MoveBy::create(0.1f,Point(-30,0)), nullptr) );
    }
}

void PlayerBar::setStone(int num)
{
    stoneNum->setString(Value(num).asString().c_str());
}

void PlayerBar::setStoneMax(int num)
{
    stoneTatalNum->setString(Value(num).asString().c_str());
}

void PlayerBar::setGem(int num)
{
    sparNum->setString(Value(num).asString().c_str());
    MedalChecker::getInstance()->check();
}

void PlayerBar::getmoregem(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    //enter buy gem ui.
}