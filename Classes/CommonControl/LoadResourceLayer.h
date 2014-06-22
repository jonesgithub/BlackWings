#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;


const std::string allmusic[]=
{
    "music_battle.mp3",
    "music_home.mp3",
    "music_main.mp3",
    "bomb_bomb.wav",
    "bomb2_start.mp3",
    "boos_warning.mp3",
    "btBuild.wav",
    "btSelect.wav",
    "btSound_1.mp3",
    "btSound_3.wav",
    "bullet_5_light.mp3",
    "bullet_5_start.mp3",
    "bullet_6_end.mp3",
    "bullet_6_start.mp3",
    "bullet_light_enemy.mp3",
    "bullet_light.wav",
    "bullet_missile_bomb_enemy.mp3",
    "bullet_missile_bomb.mp3",
    "bullet_missile_enemy_start.mp3",
    "bullet_missile_plain_start.mp3",
    "bullet_normal.mp3",
    "createBomb.wav",
    "doolOpen.wav",
    "getGem.wav",
    "getSpar.mp3",
    "missionList.wav",
    "plain_bomb.wav",
    "readyBomb.wav",
    "upgrade.wav"
};

typedef std::function<void(Ref*)> LoadResourceCallback;

class LoadResourceLayer : public LayerColor
{
public:
    static LoadResourceLayer* create(const LoadResourceCallback& callback);

    bool init(const LoadResourceCallback& callback);

    void addImage(const std::string& file);
    void addPlist(const std::string& plistFile,const std::string& imageFile);

    void startLoad();

    virtual void update(float delta);

    void loadingCallBack(Texture2D* tex);

    void loadPlists();
    
    static bool preloadmusic;
            
private:
    LoadResourceLayer();

    std::vector<std::string> _images;
    std::vector<std::string> _plists;

    LoadResourceCallback _onFinish;
    ui::LoadingBar* _loadingBar;

    float _targetValue;
    float _currValue;
    int _speed;

    int _resourceAmount;
    int _finish;
};
