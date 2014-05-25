#pragma once

#include "cocos2d.h"
#include "TextSprite.h"
#include "MenuItemImageLabel.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

enum class GameInterface
{
    MainMenu,
    Base,
    Battle
};
class MenuSettings : public LayerColor
{
public:

    static MenuSettings* create(GameInterface face = GameInterface::MainMenu);

    virtual bool init(GameInterface face);

    void menuCallbackClosed(Ref *sender);
    void menuCallbackLanguage(Ref *sender);
    void menuCallbackReset(Ref *sender);
    void menuCallbackRedeemCode(Ref *sender);
    void menuCallbackHelp(Ref *sender);
    void menuCallbackMainMenu(Ref *sender);

    void musicSliderEvent(Ref *sender, ui::SliderEventType type);
    void sfxSliderEvent(Ref *sender, ui::SliderEventType type);

private:
    void createSlider();

    GameInterface gameFace;

    Size _panelSize;

    Node* _panel;
    TextSprite* _musicText;
    TextSprite* _sfxText;
    TextSprite* _languageText;

    MenuItemImageLabel* _languageItem;
    MenuItemImageLabel* _resetItem;
    MenuItemImageLabel* _redeemCodeItem;

    MenuItemImageLabel* _helpItem;
    MenuItemImageLabel* _backToMainMenuItem;

    MenuItemImageLabel* _resumeGameItem;
    MenuItemImageLabel* _retryGameItem;
    MenuItemImageLabel* _backToBaseItem;
};
