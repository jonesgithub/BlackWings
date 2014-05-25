#pragma once

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    CREATE_FUNC(MainMenu);

    virtual bool init();

    void menuCallbackPlay(Ref *sender);
    void menuCallbackHelp(Ref *sender);
    void menuCallbackSettings(Ref *sender);
    void menuCallbackAbout(Ref *sender);

private:
    void createBg(Ref *sender);
    void createMenu();

    static bool showLogo;
};
