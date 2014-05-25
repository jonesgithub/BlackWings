#pragma once

#include "cocos2d.h"

class Base : public cocos2d::Scene
{
public:
    CREATE_FUNC(Base);

    virtual bool init();

    void menuCallbackMeadl(Ref *sender);
    void menuCallbackSetting(Ref *sender);
    void menuCallbackBattle(Ref *sender);

    void menuCallbackUpgrade(Ref *sender);

private:
    void createBase(Ref *sender);
    
    void createUpgrade();
    void createTopPanel();

    void createFighterInfo(Node* panel);

    Node* _playerBag;
    Node* _upgradePanel;
    Node* _topPanel;
};
