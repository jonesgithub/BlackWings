//
//  Medal.h
//  BlackWings
//
//  Created by Jacky on 14-5-27.
//
//

#ifndef __BlackWings__Medal__
#define __BlackWings__Medal__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "UIListview.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Medal : public cocos2d::Layer
{
public:
    const static std::string eventBack;
    
    CREATE_FUNC(Medal);
    
    virtual bool init();
    
    void initListviewItem();
    
    void menuCallbackClosed(Ref *sender);
    
    void selectedItemEvent(Ref *pSender, ui::ListViewEventType type);
    
    void refreshAllItems();
    
private:
    
    ui::ListView* listView;
    
    Node* _panel;
    Size _cellSize;
};

#endif /* defined(__BlackWings__Medal__) */
