//
//  GameOverLayer.h
//  BlackWings
//
//  Created by Jacky on 14-6-2.
//
//

#ifndef __BlackWings__GameOverLayer__
#define __BlackWings__GameOverLayer__

#include "cocos2d.h"

class GameOverLayer : public cocos2d::Layer
{
public:
    static GameOverLayer* create(bool win, int stage, int time, int kill, int loss, int newFlight);
    
    virtual bool init(bool win, int stage, int time, int kill, int loss, int newFlight);
    
    void returnBase_callback(cocos2d::Ref* pSender);
    
    void nextStage_callback(cocos2d::Ref* pSender);

    void restartStage_callback(cocos2d::Ref* pSender);
    
    void pausegame(float dt);
    
private:
    
    int _stage;

};

#endif /* defined(__BlackWings__GameOverLayer__) */
