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
    
//    virtual void scrollViewDidScroll(extension::ScrollView* view) {}
//    virtual void scrollViewDidZoom(extension::ScrollView* view) {}
//    virtual void tableCellTouched(extension::TableView* table, extension::TableViewCell* cell);
//    virtual Size tableCellSizeForIndex(extension::TableView *table, ssize_t idx);
//    virtual extension::TableViewCell* tableCellAtIndex(extension::TableView *table, ssize_t idx);
//    virtual ssize_t numberOfCellsInTableView(extension::TableView *table);
//    
//    Node* getItemNode(int i);
    
private:
    
    ui::ListView* listView;
    
    Node* _panel;
    Size _cellSize;
    TableView* tableView;
    int _count;
};

#endif /* defined(__BlackWings__Medal__) */
