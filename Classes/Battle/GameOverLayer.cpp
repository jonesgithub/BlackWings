//
//  GameOverLayer.cpp
//  BlackWings
//
//  Created by Jacky on 14-6-2.
//
//

#include "GameOverLayer.h"
#include "Configuration.h"
#include "VisibleRect.h"
#include "extensions/cocos-ext.h"
#include "TextSprite.h"
#include "MenuItemImageLabel.h"
#include "Base.h"
#include "Battleground.h"

USING_NS_CC;
USING_NS_CC_EXT;

GameOverLayer* GameOverLayer::create(bool win, int stage, int time, int kill, int loss, int newFlight)
{
    auto pRet = new GameOverLayer();
    if (pRet && pRet->init(win, stage, time, kill, loss, newFlight))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool GameOverLayer::init(bool win, int stage, int time, int kill, int loss, int newFlight)
{
    if(!Layer::init())
    {
        return false;
    }
    
    //init
    _stage = stage;
    
    std::string fontFile = "DS-Digital.ttf";//"arial.ttf";
    int fontSize = 25;
    auto infoColor = DIY_COLOR_BLUE5;
    
    //swallow touches
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //panel
    Size panelSize;
    if(win)
        panelSize = Size(s_visibleRect.visibleWidth-60,s_visibleRect.visibleHeight-280);
    else
        panelSize = Size(s_visibleRect.visibleWidth-60,s_visibleRect.visibleHeight-450);
    
    
    auto _panel = Scale9Sprite::create("windowBox.png");
    _panel->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _panel->setPosition(Point(s_visibleRect.center.x,s_visibleRect.top.y + panelSize.height));
    _panel->setContentSize(panelSize);
    this->addChild(_panel);
    _panel->runAction(MoveTo::create(0.15f,s_visibleRect.top-Point(0,80)));
    
    //title
    TextSprite* title;
    if(win)
    {
        title = TextSprite::create(s_gameStrings.battleInfo->gameovertitle_win.c_str(),s_gameConfig.defaultFontName,32);
        title->setColor(Color3B::YELLOW);
    }
    else
    {   title = TextSprite::create(s_gameStrings.battleInfo->gameovertitle_loss.c_str(),s_gameConfig.defaultFontName,32);
        title->setColor(Color3B::RED);
    }
    title->setAnchorPoint(Point::ANCHOR_MIDDLE);
    title->setPosition(Point(panelSize.width/2,panelSize.height-90));
    _panel->addChild(title,1);
    
    //info
    auto time_label = TextSprite::create(s_gameStrings.battleInfo->gameovertime, "Arial", fontSize);
    time_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    time_label->setPosition(Point(150,panelSize.height-150));
    _panel->addChild(time_label);
    
    time = time > 36000?3599:(time/10);
    int min = time/60;
    int sec = time - min*60;
    char p[10];
    sprintf(p,"%02d\'%02d\"",min,sec);
    
    auto time_content = TextSprite::create(p,fontFile, fontSize);
    time_content->setColor(infoColor);
    time_content->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    time_content->setPosition(Point(320,panelSize.height-150));
    _panel->addChild(time_content);
    
    auto kill_label = TextSprite::create(s_gameStrings.battleInfo->gameoverkill, "Arial", fontSize);
    kill_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kill_label->setPosition(Point(150,panelSize.height-200));
    _panel->addChild(kill_label);
    
    auto kill_content = TextSprite::create(Value(kill).asString(),fontFile, fontSize);
    kill_content->setColor(infoColor);
    kill_content->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kill_content->setPosition(Point(320,panelSize.height-200));
    _panel->addChild(kill_content);
    
    auto loss_label = TextSprite::create(s_gameStrings.battleInfo->gameoverloss, "Arial", fontSize);
    loss_label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    loss_label->setPosition(Point(150,panelSize.height-250));
    _panel->addChild(loss_label);
    
    auto loss_content = TextSprite::create(Value(loss).asString(), fontFile, fontSize);
    loss_content->setColor(infoColor);
    loss_content->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    loss_content->setPosition(Point(320,panelSize.height-250));
    _panel->addChild(loss_content);
    
    //rewards
    if (win)
    {
        //init rewards
        int _gem = s_stageRewards[_stage][0];
        int _starboom = s_stageRewards[_stage][1];
        int _laser = s_stageRewards[_stage][2];
        int _blackhole = s_stageRewards[_stage][3];
        
        auto rewards_label = TextSprite::create(s_gameStrings.battleInfo->gameoverreward, "Arial", fontSize);
        rewards_label->setColor(Color3B::GRAY);
        rewards_label->setAnchorPoint(Point::ANCHOR_MIDDLE);
        rewards_label->setPosition(Point(panelSize.width/2,panelSize.height-300));
        _panel->addChild(rewards_label);
        
        if(_starboom == 0 && _laser == 0 && _blackhole == 0)
        {
            auto icon = Sprite::createWithSpriteFrameName("icon_gem.png");
            icon->setPosition(panelSize.width/2-50, panelSize.height/2-10);
            _panel->addChild(icon);
            
            auto label = Label::createWithTTF(Value(_gem).asString().c_str(), s_gameConfig.defaultFontName, fontSize);
            label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            label->setPosition(Point(icon->getPositionX()+icon->getContentSize().width, icon->getPositionY()));
            label->setColor(Color3B::YELLOW);
            _panel->addChild(label);
        }
        else
        {
            auto icon1 = Sprite::createWithSpriteFrameName("icon_gem.png");
            icon1->setPosition(panelSize.width/2-130, panelSize.height/2-10);
            _panel->addChild(icon1);
            
            auto label1 = Label::createWithTTF(Value(_gem).asString().c_str(), s_gameConfig.defaultFontName, fontSize);
            label1->setPosition(icon1->getPositionX()+icon1->getContentSize().width+20, icon1->getPositionY());
            label1->setColor(Color3B::YELLOW);
            _panel->addChild(label1);
            if (_starboom > 0) {
                auto icon2 = Sprite::createWithSpriteFrameName("bomb_1_1.png");
                icon2->setScale(0.5f);icon2->setRotation(90);
                icon2->setPosition(panelSize.width/2+50, panelSize.height/2-10);
                _panel->addChild(icon2);
                
                std::string str = "x" + Value(_starboom).asString();
                auto label2 = Label::createWithTTF(str.c_str(), s_gameConfig.defaultFontName, fontSize);
                label2->setPosition(icon2->getPositionX()+icon2->getContentSize().width, icon2->getPositionY());
                label2->setColor(infoColor);
                _panel->addChild(label2);
            }
            else if (_laser > 0) {
                
                auto icon2 = Sprite::createWithSpriteFrameName("bomb_2_1.png");
                icon2->setScale(0.8f);icon2->setRotation(90);
                icon2->setPosition(panelSize.width/2+50, panelSize.height/2-10);
                _panel->addChild(icon2);
                
                std::string str = "x" + Value(_laser).asString();
                auto label2 = Label::createWithTTF(str.c_str(), s_gameConfig.defaultFontName, fontSize);
                label2->setPosition(icon2->getPositionX()+icon2->getContentSize().width, icon2->getPositionY());
                label2->setColor(infoColor);
                _panel->addChild(label2);
            }
            else if (_blackhole > 0) {
                
                auto icon2 = Sprite::createWithSpriteFrameName("bomb_3_1.png");
                icon2->setScale(0.6f);
                icon2->setPosition(panelSize.width/2+50, panelSize.height/2);
                _panel->addChild(icon2);
                
                std::string str = "x" + Value(_blackhole).asString();
                auto label2 = Label::createWithTTF(str.c_str(), s_gameConfig.defaultFontName, fontSize);
                label2->setPosition(icon2->getPositionX()+icon2->getContentSize().width, icon2->getPositionY());
                label2->setColor(infoColor);
                _panel->addChild(label2);
            }
        }
        
        if(newFlight)
        {
            auto newflight_label = TextSprite::create(s_gameStrings.battleInfo->gameovernewflight, "Arial", fontSize);
            newflight_label->setColor(Color3B::GRAY);
            newflight_label->setAnchorPoint(Point::ANCHOR_MIDDLE);
            newflight_label->setPosition(Point(panelSize.width/2,panelSize.height-400));
            _panel->addChild(newflight_label);
            
            char name[30];
            sprintf(name,"plain_%d_lv_%d.png",newFlight,1);
            auto newflight = Sprite::createWithSpriteFrameName(name);
            newflight->setScale(1.3f);
            newflight->setAnchorPoint(Point::ANCHOR_MIDDLE);
            newflight->setPosition(Point(panelSize.width/2,panelSize.height-480));
            _panel->addChild(newflight);
            
            auto newicon = Sprite::createWithSpriteFrameName("icon_new.png");
            newicon->setAnchorPoint(Point::ANCHOR_MIDDLE);
            newicon->setPosition(newflight->getPosition()+Point(0,-60));
            _panel->addChild(newicon);
            
        }
    }
    
    if(newFlight)
    {
        auto gotosee_menu = MenuItemImageLabel::createWithFrameName("bt_main_0.png", "bt_main_1.png", CC_CALLBACK_1(GameOverLayer::returnBase_callback, this), s_gameStrings.battleInfo->gotosee);
        gotosee_menu->setAnchorPoint(Point::ANCHOR_MIDDLE);
        gotosee_menu->setPosition(Point(panelSize.width/2, 60));
        
        auto menu = Menu::create(gotosee_menu, nullptr);
        menu->setPosition(Point::ZERO);
        _panel->addChild(menu);
        return true;
    }
    
    //menu
    auto returnBase_menu = MenuItemImageLabel::createWithFrameName("bt_main_0.png", "bt_main_1.png", CC_CALLBACK_1(GameOverLayer::returnBase_callback, this), s_gameStrings.battleInfo->returnbase);
    returnBase_menu->setAnchorPoint(Point::ANCHOR_MIDDLE);
    returnBase_menu->setPosition(Point(panelSize.width/2, 150));
    
    if (win && s_playerConfig.overstage<50) {
        auto nextStage_menu = MenuItemImageLabel::createWithFrameName("bt_main_0.png", "bt_main_1.png", CC_CALLBACK_1(GameOverLayer::nextStage_callback, this), s_gameStrings.battleInfo->nextstage);
        nextStage_menu->setAnchorPoint(Point::ANCHOR_MIDDLE);
        nextStage_menu->setPosition(Point(panelSize.width/2, 70));
        nextStage_menu->setColor(DIY_COLOR_BLUE5);
        
        auto menu = Menu::create(returnBase_menu, nextStage_menu, nullptr);
        menu->setPosition(Point::ZERO);
        _panel->addChild(menu);
    }
    else{
        auto restartStage_menu = MenuItemImageLabel::createWithFrameName("bt_main_0.png", "bt_main_1.png", CC_CALLBACK_1(GameOverLayer::restartStage_callback, this), s_gameStrings.battleInfo->restartstage);
        restartStage_menu->setAnchorPoint(Point::ANCHOR_MIDDLE);
        restartStage_menu->setPosition(Point(panelSize.width/2, 70));
        
        auto menu = Menu::create(returnBase_menu, restartStage_menu, nullptr);
        menu->setPosition(Point::ZERO);
        _panel->addChild(menu);
    }
    
    //this->scheduleOnce(schedule_selector(GameOverLayer::pausegame), 0.5f);

    return true;
}

void GameOverLayer::returnBase_callback(cocos2d::Ref* pSender)
{
//    if (Director::getInstance()->isPaused()) {
//        Director::getInstance()->resume();
//    }
    PLAY_BUTTON_EFFECT;
    auto base = Base::create();
    Director::getInstance()->replaceScene(base);
}

void GameOverLayer::nextStage_callback(cocos2d::Ref* pSender)
{
//    if (Director::getInstance()->isPaused()) {
//    Director::getInstance()->resume();
//    }
    PLAY_BUTTON_EFFECT;
    if(_stage < STAGE_COUNT-1)
    {
        auto battle = Battleground::create(_stage+1);
        Director::getInstance()->replaceScene(battle);
    }
    else
    {
        //通关了
    }
}

void GameOverLayer::restartStage_callback(cocos2d::Ref* pSender)
{
//    if (Director::getInstance()->isPaused()) {
//        Director::getInstance()->resume();
//    }
    PLAY_BUTTON_EFFECT;
    auto battle = Battleground::create(_stage);
    Director::getInstance()->replaceScene(battle);
}

void GameOverLayer::pausegame(float dt)
{
    Director::getInstance()->pause();
}
