//
//  MedalRewardsLayer.h
//  BlackWings
//
//  Created by Jacky on 14-5-28.
//
//

#ifndef __BlackWings__MedalRewardsLayer__
#define __BlackWings__MedalRewardsLayer__

#include "cocos2d.h"

class MedalRewardsLayer : public cocos2d::Layer
{
public:
    static MedalRewardsLayer* create(int money, int starboom, int laser, int blackhole);

    virtual bool init(int money, int starboom, int laser, int blackhole);
    
    void menuCallbackClosed(cocos2d::Ref *sender);
    
    MedalRewardsLayer():_money(0),_starboom(0),_laser(0),_blackhole(0){};
    
    void initRewards();
    
private:
    
    int _money;
    int _starboom;
    int _laser;
    int _blackhole;
};

#endif /* defined(__BlackWings__MedalRewardsLayer__) */
