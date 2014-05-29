#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class StageSelect : public Layer, public extension::TableViewDataSource, public extension::TableViewDelegate
{
public:
    const static std::string eventBack;

    CREATE_FUNC(StageSelect);

    virtual bool init();
    
    void menuCallbackClosed(Ref *sender);
    void menuCallbackFight(Ref *sender);

    virtual void scrollViewDidScroll(extension::ScrollView* view) {}
    virtual void scrollViewDidZoom(extension::ScrollView* view) {}
    virtual void tableCellTouched(extension::TableView* table, extension::TableViewCell* cell);
//	virtual void tableCellHighlight(extension::TableView* table, extension::TableViewCell* cell);
//	virtual void tableCellUnhighlight(extension::TableView* table, extension::TableViewCell* cell);
    virtual Size tableCellSizeForIndex(extension::TableView *table, ssize_t idx);
    virtual extension::TableViewCell* tableCellAtIndex(extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(extension::TableView *table);

private:
    int _selectItem;
    
    Node* getItemNode(int i);
    
    extension::TableViewCell* selected_cell;
    Node* _panel;
    Size _cellSize;
    
    bool _noTouch;
};
