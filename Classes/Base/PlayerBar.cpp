#include "PlayerBar.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "PlayerMenuItem.h"
#include "PersonalApi.h"

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
    
    //Add by Jacky.
//    _playerMenu = Node::create();

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
        playerPos.x += interval;
        _playerMenu->addChild(player,0,i);
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
            playerPos.x += interval;
            _playerMenu->addChild(player,0,i);
        }
    }

    _playerMenu->setPosition(Point::ZERO);
    this->addChild(_playerMenu);

    auto leftSidebar = Sprite::createWithSpriteFrameName("dijia2.png");
    leftSidebar->getTexture()->setAliasTexParameters();
    leftSidebar->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    leftSidebar->setPosition(s_visibleRect.leftBottom);
    this->addChild(leftSidebar);

    auto rightSidebar = Sprite::createWithSpriteFrameName("dijia2.png");
    rightSidebar->getTexture()->setAliasTexParameters();
    rightSidebar->setFlippedX(true);
    rightSidebar->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    rightSidebar->setPosition(s_visibleRect.rightBottom);
    this->addChild(rightSidebar);

    auto stoneIcon = Sprite::createWithSpriteFrameName("icon_stone.png");
    stoneIcon->setPosition(Point(s_visibleRect.center.x - 282,s_visibleRect.visibleOriginY + 165));
    stoneIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(stoneIcon);

    auto numBg = Sprite::createWithSpriteFrameName("numBackground.png");
    numBg->setPosition(Point(s_visibleRect.center.x - 237,s_visibleRect.visibleOriginY + 165));
    numBg->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(numBg);

    auto gemIcon = Sprite::createWithSpriteFrameName("icon_gem.png");
    gemIcon->setPosition(Point(s_visibleRect.center.x - 43,s_visibleRect.visibleOriginY + 165));
    gemIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(gemIcon);
    
    std::string fontFile = "arial.ttf";
    int fontSize = 20;
    
    auto slash = Label::createWithTTF("/",fontFile,fontSize);
    slash->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    slash->setPosition(Point(numBg->getContentSize().width/2,6));
    slash->setColor(Color3B(169,169,169));
    numBg->addChild(slash);
    
    auto stoneNum = Label::createWithTTF(PersonalApi::convertIntToString(s_playerConfig.stone).c_str(),fontFile,fontSize);
    stoneNum->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    stoneNum->setPosition(Point(slash->getPositionX()-10,slash->getPositionY()));
    numBg->addChild(stoneNum);
    
    auto stoneTatalNum = Label::createWithTTF(PersonalApi::convertIntToString(s_playerConfig.stoneMax).c_str(),fontFile,fontSize);
    stoneTatalNum->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    stoneTatalNum->setPosition(Point(slash->getPositionX()+10,slash->getPositionY()));
    stoneTatalNum->setColor(Color3B(169,169,169));
    numBg->addChild(stoneTatalNum);
    
    auto sparNum = Label::createWithTTF(PersonalApi::convertIntToString(s_playerConfig.gem).c_str(),fontFile,fontSize);
    sparNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    sparNum->setPosition(Point(gemIcon->getPositionX()+gemIcon->getContentSize().width+5,gemIcon->getPositionY()));
    sparNum->setColor(Color3B(255,255,0));
    this->addChild(sparNum);
    
    auto listener = EventListenerCustom::create(PlayerBar::eventPlayerSelect, [=](EventCustom* event)
                                                {
                                                    stoneNum->setString( PersonalApi::convertIntToString(s_playerConfig.stone).c_str());
                                                    stoneNum->setPosition(Point(slash->getPositionX()-10,slash->getPositionY()));
                                                    stoneTatalNum->setString(PersonalApi::convertIntToString(s_playerConfig.stoneMax).c_str());
                                                    stoneTatalNum->setPosition(Point(slash->getPositionX()+10,slash->getPositionY()));
                                                    sparNum->setString(PersonalApi::convertIntToString(s_playerConfig.gem).c_str());
                                                });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void PlayerBar::menuCallbackArrow(Ref *sender)
{
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
