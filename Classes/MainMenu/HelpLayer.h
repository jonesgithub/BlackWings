#pragma  once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelpLayer : public LayerColor,public TableViewDataSource,public TableViewDelegate
{
public:
    CREATE_FUNC(HelpLayer);

    virtual bool init();

    void menuCallbackClosed(Ref *sender);

    virtual void scrollViewDidScroll(extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(extension::ScrollView* view) {}
    virtual void tableCellTouched(extension::TableView* table, extension::TableViewCell* cell) {}
    virtual Size tableCellSizeForIndex(extension::TableView *table, ssize_t idx);
    virtual extension::TableViewCell* tableCellAtIndex(extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(extension::TableView *table);

private:

    Size _panelSize;
    Size _cellSize;
};
