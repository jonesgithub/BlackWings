#include "RedeemLayer.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"

USING_NS_CC_EXT;

bool RedeemLayer::init()
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

        auto panelSize = Size(s_visibleRect.visibleWidth - 97,300);

        auto panel = Scale9Sprite::create("windowBox.png");
        panel->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        panel->setPosition(s_visibleRect.center.x,s_visibleRect.center.y);
        panel->setContentSize(panelSize);
        this->addChild(panel);

        auto itemClosed = MenuItemImageLabel::createWithFrameName("close_0.png","close_1.png",
            CC_CALLBACK_1(RedeemLayer::menuCallbackClosed,this));
        itemClosed->setPosition(panelSize.width,panelSize.height);
        
        auto itemRedeem = MenuItemImageLabel::createWithFrameName("btD_0.png","btD_1.png",
            CC_CALLBACK_1(RedeemLayer::menuCallbackRedeem,this),s_gameStrings.mainMenu->settingRedeem);
        itemRedeem->setPosition(panelSize.width / 2, 60);

        auto menu = Menu::create( itemClosed, itemRedeem,nullptr);
        menu->setPosition(Point::ZERO);
        panel->addChild(menu);

        auto textBg = Scale9Sprite::createWithSpriteFrameName("sound_slider_bg_1.png");
        textBg->setPosition(panelSize.width / 2, panelSize.height * 0.75f);
        textBg->setContentSize(Size(300,60));
        panel->addChild(textBg);

        auto textField = TextFieldTTF::textFieldWithPlaceHolder(s_gameStrings.mainMenu->settingRedeemHintText,
            "Arial",
            30);
        textField->setPosition(panelSize.width / 2, panelSize.height * 0.75f);
        //textField->setColorSpaceHolder(Color3B::GRAY);
        panel->addChild(textField);
        textField->attachWithIME();

        return true;
    }

    return false;
}

void RedeemLayer::menuCallbackClosed(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    this->removeFromParentAndCleanup(true);
}

void RedeemLayer::menuCallbackRedeem(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
}