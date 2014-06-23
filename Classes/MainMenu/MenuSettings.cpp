#include "MenuSettings.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "RedeemLayer.h"
#include "ResetGameLayer.h"
#include "SimpleAudioEngine.h"
#include "HelpLayer.h"
#include "MainMenu.h"
#include "Battleground.h"
#include "Base.h"
#include "ConfigManager.h"
#include "PromtWindow.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

MenuSettings* MenuSettings::create(GameInterface face /* = GameInterface::MainMenu */)
{
    auto ret = new MenuSettings;
    if (ret && ret->init(face))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool MenuSettings::init(GameInterface face)
{
    if (LayerColor::initWithColor(Color4B(0,0,0,0)))
    {
        gameFace = face;

        this->runAction(FadeTo::create(0.5f,100));

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        _panelSize = Size(s_visibleRect.visibleWidth - 97,600);
        auto bashY = _panelSize.height / 6;
        auto centerX = _panelSize.width / 2;
        
        if (face == GameInterface::Battle)
        {
            _panelSize.height = s_visibleRect.visibleHeight * 0.75f;
            bashY = _panelSize.height / 8;
        }
        auto itemY = _panelSize.height - bashY;

        _panel = Scale9Sprite::create("windowBox.png");
        _panel->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        _panel->setPosition(s_visibleRect.center.x,s_visibleRect.top.y + 300);
        _panel->setContentSize(_panelSize);
        this->addChild(_panel);

        auto action = Sequence::create( MoveTo::create(0.15f,Point(s_visibleRect.center.x,s_visibleRect.top.y - 60.0f)),
            MoveTo::create(0.07f,Point(s_visibleRect.center.x,s_visibleRect.top.y - 48.5)),nullptr);
        _panel->runAction(action);

        float iconLeft = 30.0f;
        float textLeft = 120.0f;
        auto btnX =  _panelSize.width * 0.96f - 120;

        auto musicIcon = Sprite::createWithSpriteFrameName("icon_music.png");
        musicIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        musicIcon->setPosition(iconLeft,itemY);
        _panel->addChild(musicIcon);

        _musicText = TextSprite::create(s_gameStrings.mainMenu->settingMusic);
        _musicText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _musicText->setPosition(textLeft,itemY);
        _panel->addChild(_musicText);

        itemY -= bashY;
        auto sfxIcon = Sprite::createWithSpriteFrameName("icon_sfx.png");
        sfxIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        sfxIcon->setPosition(iconLeft,itemY);
        _panel->addChild(sfxIcon);

        _sfxText = TextSprite::create(s_gameStrings.mainMenu->settingSFX);
        _sfxText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _sfxText->setPosition(textLeft,itemY);
        _panel->addChild(_sfxText);

        itemY -= bashY;
        _languageText = TextSprite::create(s_gameStrings.mainMenu->settingSelLanguage);
        _languageText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        _languageText->setPosition(iconLeft,itemY);
        _panel->addChild(_languageText);

        auto itemClosed = MenuItemImageLabel::createWithFrameName("back_0.png","back_1.png",
            CC_CALLBACK_1(MenuSettings::menuCallbackClosed,this));
        itemClosed->setPosition(_panelSize.height + 100,_panelSize.height + 100);
        auto action2 = Sequence::create( DelayTime::create(0.32f),
            MoveTo::create(0.15f,Point(_panelSize.width,_panelSize.height)),nullptr);
        itemClosed->runAction(action2);

        _languageItem = MenuItemImageLabel::createWithFrameName("btD_0.png","btD_1.png",
            CC_CALLBACK_1(MenuSettings::menuCallbackLanguage,this),s_gameStrings.mainMenu->settingLanguage);
        _languageItem->setPosition(btnX,itemY);

        switch (gameFace)
        {
        case GameInterface::MainMenu:
            {
                itemY -= bashY;
                _resetItem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                    CC_CALLBACK_1(MenuSettings::menuCallbackReset,this),s_gameStrings.mainMenu->settingReset);
                _resetItem->setPosition(centerX,itemY);
                _resetItem->setColor(Color3B::ORANGE);

                itemY -= bashY;
                _redeemCodeItem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                    CC_CALLBACK_1(MenuSettings::menuCallbackRedeemCode,this),s_gameStrings.mainMenu->settingRedeemCode);
                _redeemCodeItem->setPosition(centerX,itemY);
                _redeemCodeItem->setTextColor(Color3B::GREEN);

                auto menu = Menu::create( itemClosed, _languageItem, _resetItem, _redeemCodeItem,nullptr);
                menu->setPosition(Point::ZERO);
                _panel->addChild(menu);
            }
            break;
        case GameInterface::Base:
            {
                itemY -= bashY;
                _helpItem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                    CC_CALLBACK_1(MenuSettings::menuCallbackHelp,this),s_gameStrings.mainMenu->help);
                _helpItem->setPosition(centerX,itemY);

                itemY -= bashY;
                _backToMainMenuItem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                    CC_CALLBACK_1(MenuSettings::menuCallbackMainMenu,this),s_gameStrings.base->topBarMainMenu);
                _backToMainMenuItem->setPosition(centerX,itemY);

                auto menu = Menu::create( itemClosed, _languageItem, _helpItem, _backToMainMenuItem,nullptr);
                menu->setPosition(Point::ZERO);
                _panel->addChild(menu);
            }
            break;
        case GameInterface::Battle:
            {
                itemY -= bashY;
                _resumeGameItem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                    CC_CALLBACK_1(MenuSettings::menuCallbackClosed,this),s_gameStrings.mainMenu->settingResume);
                _resumeGameItem->setPosition(centerX,itemY);

                itemY -= bashY;
                _retryGameItem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                    [=](Ref *sender){
                        PLAY_BUTTON_EFFECT;
                        this->addChild(PromtWindow::create(ForWhat::Restart), 300);
                },s_gameStrings.mainMenu->settingRetry);
                _retryGameItem->setPosition(centerX,itemY);

                itemY -= bashY;
                _backToBaseItem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                    [=](Ref *sender){
                        PLAY_BUTTON_EFFECT;
                        this->addChild(PromtWindow::create(ForWhat::BackToBase),300);
                },s_gameStrings.mainMenu->settingBackToBase);
                _backToBaseItem->setPosition(centerX,itemY);

                itemY -= bashY;
                _backToMainMenuItem = MenuItemImageLabel::createWithFrameName("bt_main_0.png","bt_main_1.png",
                    [=](Ref *sender){
                        PLAY_BUTTON_EFFECT;
                        this->addChild(PromtWindow::create(ForWhat::BACKToMainMenu),300);
                },s_gameStrings.base->topBarMainMenu);
                _backToMainMenuItem->setPosition(centerX,itemY);

                auto menu = Menu::create( itemClosed, _languageItem,_resumeGameItem, _retryGameItem, 
                    _backToBaseItem, _backToMainMenuItem, nullptr);
                menu->setPosition(Point::ZERO);
                _panel->addChild(menu);
                
                this->scheduleOnce(schedule_selector(MenuSettings::pausegame), 0.5f);
            }
            break;
        default:
            break;
        }
        
        createSlider();
    }
    return true;
}

void MenuSettings::menuCallbackClosed(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    if (Director::getInstance()->isPaused()) {
        Director::getInstance()->resume();
    }
    
    this->runAction(FadeTo::create(0.15f,0));
    auto action = Sequence::create(
        MoveBy::create(0.15f, Point(0,600)),
        CallFunc::create(
        [&](){
            this->removeFromParentAndCleanup(true);
    }  ),nullptr);
    _panel->runAction(action);
}

void MenuSettings::menuCallbackLanguage(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    if (s_playerConfig.language == (int)GameLanguage::English)
    {
        s_playerConfig.language = (int)GameLanguage::Chinese;
        s_gameConfig.GSInitLanguage(GameLanguage::Chinese);
    }
    else
    {
        s_playerConfig.language = (int)GameLanguage::English;
        s_gameConfig.GSInitLanguage(GameLanguage::English);

    }

    _musicText->setText(s_gameStrings.mainMenu->settingMusic);
    _sfxText->setText(s_gameStrings.mainMenu->settingSFX);
    _languageText->setText(s_gameStrings.mainMenu->settingSelLanguage);

    _languageItem->setText(s_gameStrings.mainMenu->settingLanguage);
    switch (gameFace)
    {
    case GameInterface::MainMenu:
        {
            _resetItem->setText(s_gameStrings.mainMenu->settingReset);
            _redeemCodeItem->setText(s_gameStrings.mainMenu->settingRedeemCode);
        }
        break;
    case GameInterface::Base:
        {
//            GSBaseInit(GameLanguage(s_playerConfig.language));
            _helpItem->setText(s_gameStrings.mainMenu->help);
            _backToMainMenuItem->setText(s_gameStrings.base->topBarMainMenu);
        }
        break;
    case GameInterface::Battle:
        {
//            GSBaseInit(GameLanguage(s_playerConfig.language));
            _resumeGameItem->setText(s_gameStrings.mainMenu->settingResume);
            _retryGameItem->setText(s_gameStrings.mainMenu->settingRetry);
            _backToBaseItem->setText(s_gameStrings.mainMenu->settingBackToBase);
            _backToMainMenuItem->setText(s_gameStrings.base->topBarMainMenu);
        }
        break;
    default:
        break;
    }
    
    ConfigManager::getInstance()->saveLanguage(s_playerConfig.language);
    _eventDispatcher->dispatchCustomEvent(GameConfig::eventLanguageChange);
}

void MenuSettings::menuCallbackReset(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    auto resetLayer = ResetGameLayer::create();
    this->addChild(resetLayer);
}

void MenuSettings::menuCallbackRedeemCode(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    auto redeemLayer = RedeemLayer::create();
    this->addChild(redeemLayer);
}

void MenuSettings::menuCallbackHelp(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    this->removeFromParentAndCleanup(true);

    auto helpLayer = HelpLayer::create();
    Director::getInstance()->getRunningScene()->addChild(helpLayer,999);
}

void MenuSettings::menuCallbackMainMenu(Ref *sender)
{
    PLAY_BUTTON_EFFECT;
    Director::getInstance()->replaceScene(MainMenu::create());
}

void MenuSettings::createSlider()
{
    auto musicSlider = ui::Slider::create();
    musicSlider->setTouchEnabled(true);
    musicSlider->loadBarTexture("sound_slider_bg_1.png",ui::TextureResType::UI_TEX_TYPE_PLIST);
    musicSlider->loadSlidBallTextures("sound_slider_bt_0.png", "sound_slider_bt_1.png", "",ui::TextureResType::UI_TEX_TYPE_PLIST);
    musicSlider->loadProgressBarTexture("sound_slider_bg_0.png",ui::TextureResType::UI_TEX_TYPE_PLIST);
    musicSlider->setPosition(Point(_panelSize.width * 0.96f - 120,_musicText->getPositionY()));
    musicSlider->setPercent(s_playerConfig.musicVolume * 100);
    musicSlider->addEventListenerSlider(this, sliderpercentchangedselector(MenuSettings::musicSliderEvent));
    _panel->addChild(musicSlider);

    auto sfxSlider = ui::Slider::create();
    sfxSlider->setTouchEnabled(true);
    sfxSlider->loadBarTexture("sound_slider_bg_1.png",ui::TextureResType::UI_TEX_TYPE_PLIST);
    sfxSlider->loadSlidBallTextures("sound_slider_bt_0.png", "sound_slider_bt_1.png", "",ui::TextureResType::UI_TEX_TYPE_PLIST);
    sfxSlider->loadProgressBarTexture("sound_slider_bg_0.png",ui::TextureResType::UI_TEX_TYPE_PLIST);
    sfxSlider->setPosition(Point(_panelSize.width * 0.96f - 120,_sfxText->getPositionY()));
    sfxSlider->setPercent(s_playerConfig.sfxVolume * 100);
    sfxSlider->addEventListenerSlider(this, sliderpercentchangedselector(MenuSettings::sfxSliderEvent));
    _panel->addChild(sfxSlider);
}

void MenuSettings::musicSliderEvent(Ref *sender, ui::SliderEventType type)
{
    s_playerConfig.musicVolume = ((Slider*)sender)->getPercent() / 100.0f;
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(s_playerConfig.musicVolume);
    ConfigManager::getInstance()->saveMusicVolume(s_playerConfig.musicVolume);
}

void MenuSettings::sfxSliderEvent(Ref *sender, ui::SliderEventType type)
{
    s_playerConfig.sfxVolume = ((Slider*)sender)->getPercent() / 100.0f;
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(s_playerConfig.sfxVolume);
    ConfigManager::getInstance()->saveSFXVolume(s_playerConfig.sfxVolume);
}

void MenuSettings::pausegame(float dt)
{
    Director::getInstance()->pause();
}