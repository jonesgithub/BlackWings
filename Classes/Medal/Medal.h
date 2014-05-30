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

USING_NS_CC;
USING_NS_CC_EXT;

class Medal : public cocos2d::Layer, public extension::TableViewDataSource, public extension::TableViewDelegate
{
public:
    const static std::string eventBack;
    
    CREATE_FUNC(Medal);
    
    virtual bool init();
    
    void menuCallbackClosed(Ref *sender);
    
    virtual void scrollViewDidScroll(extension::ScrollView* view) {}
    virtual void scrollViewDidZoom(extension::ScrollView* view) {}
    virtual void tableCellTouched(extension::TableView* table, extension::TableViewCell* cell);
    virtual Size tableCellSizeForIndex(extension::TableView *table, ssize_t idx);
    virtual extension::TableViewCell* tableCellAtIndex(extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(extension::TableView *table);
    
    Node* getItemNode(int i);
    
private:
    Node* _panel;
    Size _cellSize;
};

#endif /* defined(__BlackWings__Medal__) */
