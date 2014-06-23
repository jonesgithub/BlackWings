#include "NotificationLayer.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"

USING_NS_CC_EXT;

NotificationLayer* NotificationLayer::create(const std::string& notificationMsg,const Size& size /* = Size::ZERO */)
{
    auto ret = new NotificationLayer;
    if (ret && ret->init(notificationMsg,size))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool NotificationLayer::init(const std::string& notificationMsg,const Size& size)
{
    if (LayerColor::initWithColor(Color4B(0,0,0,0)))
    {
        this->runAction(FadeTo::create(0.5f,100));

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        auto panelSize = Size(s_visibleRect.visibleWidth - 97,400);
        if (! size.equals(Size::ZERO))
        {
            panelSize = size;
        }

        auto panel = Scale9Sprite::create("windowBox.png");
        panel->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        panel->setPosition(s_visibleRect.center.x,s_visibleRect.center.y);
        panel->setContentSize(panelSize);
        this->addChild(panel);

        auto itemClosed = MenuItemImageLabel::createWithFrameName("close_0.png","close_1.png",
            CC_CALLBACK_1(NotificationLayer::menuCallbackClosed,this));
        itemClosed->setPosition(panelSize.width,panelSize.height);
        
        auto itemConfirm = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
            CC_CALLBACK_1(NotificationLayer::menuCallbackClosed,this),s_gameStrings.mainMenu->settingResetConfirm);
        itemConfirm->setPosition(panelSize.width / 2, panelSize.height * 0.3f);

        auto menu = Menu::create( itemClosed, itemConfirm, nullptr);
        menu->setPosition(Point::ZERO);
        panel->addChild(menu);

        auto notificationText = TextSprite::create(notificationMsg,GameConfig::defaultFontName,GameConfig::defaultFontSize,
            Size(panelSize.width * 0.8f,panelSize.height * 0.3f));
        notificationText->setPosition(panelSize.width * 0.5f,panelSize.height * 0.75f);
        panel->addChild(notificationText);

        return true;
    }

    return false;
}

void NotificationLayer::menuCallbackClosed(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    this->removeFromParentAndCleanup(true);
}