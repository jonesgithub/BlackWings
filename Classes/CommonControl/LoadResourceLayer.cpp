#include "LoadResourceLayer.h"
#include<thread>

#include "VisibleRect.h"
#include "GameStrings.h"
#include "TextSprite.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool LoadResourceLayer::preloadmusic = true;

LoadResourceLayer* LoadResourceLayer::create(const LoadResourceCallback& callback)
{
    auto ret = new LoadResourceLayer;
    if (ret && ret->init(callback))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

LoadResourceLayer::LoadResourceLayer()
: _onFinish(nullptr)
, _targetValue(0)
, _currValue(0)
, _speed(0)
, _resourceAmount(0)
, _finish(0)
{

}

bool LoadResourceLayer::init(const LoadResourceCallback& callback)
{
    if (LayerColor::initWithColor(Color4B(60,60,60,255)))
    {
        _onFinish = callback;
        this->scheduleUpdateWithPriority(0);

        auto logo = Sprite::create("logo.png");
        logo->setPosition(Point(s_visibleRect.center.x,s_visibleRect.visibleOriginY + s_visibleRect.visibleHeight * 0.75f));
        this->addChild(logo);

        auto loadBg = Sprite::create("loading_bar_a.png");
        loadBg->setPosition(s_visibleRect.center);
        this->addChild(loadBg);

        _loadingBar = ui::LoadingBar::create("loading_bar_b.png");
        _loadingBar->setPosition(s_visibleRect.center);
        this->addChild(_loadingBar);

        srand((unsigned)time(NULL));
        auto helpfulTips = TextSprite::create(s_gameStrings.helpInfo->helptips[rand()%5]);
        helpfulTips->setPosition(Point(s_visibleRect.center.x,s_visibleRect.center.y - 80));
        this->addChild(helpfulTips);

        return true;

    }

    return false;
}

void LoadResourceLayer::update(float delta)
{
    _currValue += _speed * delta;
    _loadingBar->setPercent(_currValue);
    if (_currValue >= _targetValue)
    {
        _speed = 0;
    }

    if (_currValue >= 100.0f)
    {
        this->unscheduleUpdate();
        if (_onFinish)
        {
            preloadmusic = false;
            _onFinish(this);
        }
    }
    
    if(preloadmusic)
    {
        for (int i=0; i<3; ++i) {
            SimpleAudioEngine::getInstance()->preloadBackgroundMusic(allmusic[i].c_str());
        }
        for (int i=3; i<29; ++i) {
            SimpleAudioEngine::getInstance()->preloadEffect(allmusic[i].c_str());
        }
    }
}

void LoadResourceLayer::addImage(const std::string& file)
{
    _images.push_back(file);
    _resourceAmount++;
}

void LoadResourceLayer::addPlist(const std::string& plistFile,const std::string& imageFile)
{
    _plists.push_back(plistFile);
    _images.push_back(imageFile);
    _resourceAmount += 2;
}

void LoadResourceLayer::startLoad()
{
    if (_images.empty())
    {
        loadingCallBack(nullptr);
    }
    else
    {
        auto instance = Director::getInstance()->getTextureCache();
        for (const auto& image:_images)
        {
            instance->addImageAsync(image,CC_CALLBACK_1(LoadResourceLayer::loadingCallBack, this));
        }
    }
}

void LoadResourceLayer::loadingCallBack(Texture2D* tex)
{
    if (_resourceAmount > 0)
    {
        _finish++;
        _targetValue = 100.0f * _finish / _resourceAmount;
        _speed = (_targetValue - _currValue) * 5;

        if (_finish == _images.size() && _plists.size() > 0)
        {
            std::thread  t1(&LoadResourceLayer::loadPlists,this);
            t1.detach();
        }
    }
    else
    {
        _targetValue = 100;
        _speed = 150;
    }
}

void LoadResourceLayer::loadPlists()
{
    auto frameCache = SpriteFrameCache::getInstance();
    for (const auto& file:_plists)
    {
        frameCache->addSpriteFramesWithFile(file);
        _finish++;
        _targetValue = 100.0f * _finish / _resourceAmount;
        _speed = (_targetValue - _currValue) * 5;
    }
}
