#include "AboutLayer.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"

USING_NS_CC_EXT;

bool AboutLayer::init()
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

        auto panelSize = Size(s_visibleRect.visibleWidth - 97,s_visibleRect.visibleHeight * 0.8f);
        auto panelCenterX = panelSize.width / 2.0f;

        _panel = Scale9Sprite::create("windowBox.png");
        _panel->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        //_panel->setPosition(s_visibleRect.center.x,s_visibleRect.top.y - 48.5f);
        _panel->setPosition(Point(s_visibleRect.center.x,s_visibleRect.top.y + panelSize.height));
        _panel->setContentSize(panelSize);
        this->addChild(_panel);
        _panel->runAction(MoveTo::create(0.15f,Point(s_visibleRect.center.x,s_visibleRect.top.y - 48.5f)));

        auto logo = Sprite::create("DL.png");
        logo->setPosition(Point(panelCenterX, panelSize.height * 0.8f));
        _panel->addChild(logo);

        auto versionText = TextSprite::create(s_gameStrings.mainMenu->aboutVersions);
        versionText->setPosition(Point(panelCenterX, panelSize.height * 0.65f));
        _panel->addChild(versionText);

        auto itemClosed = MenuItemImageLabel::createWithFrameName("back_0.png","back_1.png",
            CC_CALLBACK_1(AboutLayer::menuCallbackClosed,this));
        itemClosed->setPosition(panelSize.width,panelSize.height);
        
        auto itemMicroblog = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
            CC_CALLBACK_1(AboutLayer::menuCallbackMicroblog,this),s_gameStrings.mainMenu->aboutMicroblog);
        itemMicroblog->setPosition(panelCenterX, panelSize.height * 0.5f);

        auto itemEmail = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
            CC_CALLBACK_1(AboutLayer::menuCallbackEmail,this),s_gameStrings.mainMenu->aboutEmail);
        itemEmail->setPosition(panelCenterX, panelSize.height * 0.35f);

        auto itemRate = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
            CC_CALLBACK_1(AboutLayer::menuCallbackRate,this),s_gameStrings.mainMenu->aboutRate);
        itemRate->setTextColor(Color3B::YELLOW);
        itemRate->setPosition(panelCenterX, panelSize.height * 0.2f);

        auto menu = Menu::create( itemClosed, itemMicroblog, itemEmail, itemRate, nullptr);
        menu->setPosition(Point::ZERO);
        _panel->addChild(menu);

        auto rateAppreciation = TextSprite::create(s_gameStrings.mainMenu->aboutRateAppreciation,GameConfig::defaultFontName,GameConfig::defaultFontSize,
            Size(panelSize.width * 0.7f,panelSize.height * 0.2f),TextHAlignment::CENTER);
        rateAppreciation->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        rateAppreciation->setPosition(panelCenterX,panelSize.height * 0.12f);
        rateAppreciation->setColor(Color3B::BLUE);
        _panel->addChild(rateAppreciation);

        return true;
    }

    return false;
}

void AboutLayer::menuCallbackClosed(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    //this->removeFromParentAndCleanup(true);
    this->runAction(FadeTo::create(0.15f,0));
    auto action = Sequence::create(
        MoveBy::create(0.15f, Point(0,s_visibleRect.visibleHeight * 0.8f)),
        CallFunc::create(
        [&](){
            this->removeFromParentAndCleanup(true);
    }  ),nullptr);
    _panel->runAction(action);
}

void AboutLayer::menuCallbackMicroblog(Ref *sender)
{
    //todo:openURL
    PLAY_BUTTON_EFFECT;
}

void AboutLayer::menuCallbackEmail(Ref *sender)
{
    //todo:openURL
    PLAY_BUTTON_EFFECT;
}

void AboutLayer::menuCallbackRate(Ref *sender)
{
    //todo:openURL
    PLAY_BUTTON_EFFECT;
}