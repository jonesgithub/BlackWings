#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "UIListview.h"

USING_NS_CC;
USING_NS_CC_EXT;


class StageSelect : public Layer
{
public:
    const static std::string eventBack;

    CREATE_FUNC(StageSelect);

    virtual bool init();
    
    void menuCallbackClosed(Ref *sender);
    void menuCallbackFight(Ref *sender);
    
    void initListviewItem();
    void selectedItemEvent(Ref *pSender, ui::ListViewEventType type);

    void update(float dt);
private:
    
    int _selectItem;
    Node* _panel;
    Size _cellSize;
        
    Sprite* left_door;
    Sprite* right_door;
    
    bool isCloseClick;
    
    ui::ListView* listView;

};