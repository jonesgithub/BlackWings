#include "PlayerBar.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "PlayerMenuItem.h"

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
