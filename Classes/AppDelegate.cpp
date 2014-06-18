#include "AppDelegate.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "Configuration.h"

USING_NS_CC;

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::createWithRect("BlackWings",Rect(0,0,400,600));
        //glview = GLView::create("BlackWings");
        director->setOpenGLView(glview);
    }
    director->setProjection(ccDirectorProjection::_2D);
    auto frameSize = glview->getFrameSize();

    int width = frameSize.width;

    glview->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
    
    director->setDisplayStats(true);

    /*
    if (width > 320)
    {
        FileUtils::getInstance()->addSearchPath("hd");
    }
    else
    {
        director->setContentScaleFactor(0.5f);
        FileUtils::getInstance()->addSearchPath("sd");
    }
     */
    FileUtils::getInstance()->addSearchPath("hd");
    s_gameConfig.lazyInit();

    director->runWithScene(MainMenu::create());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
