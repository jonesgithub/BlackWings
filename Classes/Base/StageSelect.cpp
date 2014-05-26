#include "StageSelect.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "MenuItemImageLabel.h"
#include "Battleground.h"

USING_NS_CC_EXT;

const std::string StageSelect::eventBack = "eventStageSelsctBack";

bool StageSelect::init()
{
    if (Layer::init())
    {
        _selectStage = 0;
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        auto panelSize = Size(506,s_visibleRect.visibleHeight * 0.8f);//s_visibleRect.visibleWidth - 97
        auto panelCenterX = panelSize.width / 2.0f;

        _cellSize.width = panelSize.width;
        _cellSize.height = 100;

        _panel = Scale9Sprite::create("mission.png");
        _panel->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        _panel->setPosition(Point(s_visibleRect.center.x,s_visibleRect.top.y + panelSize.height));
        _panel->setContentSize(panelSize);
        this->addChild(_panel);
        _panel->runAction(MoveTo::create(0.15f,s_visibleRect.top));

        auto tableView = TableView::create(this, Size(panelSize.width, panelSize.height - 335));
        tableView->setDirection(ScrollView::Direction::VERTICAL);
        tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
        tableView->setPosition(Point(0,132));
        tableView->setDelegate(this);
        tableView->reloadData();
        _panel->addChild(tableView);
        
        auto itemClosed = MenuItemImageLabel::createWithFrameName("back_0.png","back_1.png",
            CC_CALLBACK_1(StageSelect::menuCallbackClosed,this));
        itemClosed->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
        itemClosed->setPosition((s_visibleRect.visibleWidth + panelSize.width)/2,panelSize.height);

        auto itemFight = MenuItemImageLabel::createWithFrameName("btA_0.png","btA_1.png",
            CC_CALLBACK_1(StageSelect::menuCallbackFight,this));
        itemFight->setPosition(Point(panelSize.width / 2,77));
       
        auto menu = Menu::create( itemClosed, itemFight, nullptr);
        menu->setPosition(Point::ZERO);
        _panel->addChild(menu);

        return true;
    }

    return false;
}

cocos2d::extension::TableViewCell* StageSelect::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    auto cell = table->dequeueCell();

    char stageText[10];
    char iconFileName[25];

    sprintf(stageText,"stage %d",idx);

    if (!cell)
    {
        cell = TableViewCell::create();

        /*auto icon = Sprite::createWithSpriteFrameName(iconFileName);
        icon->setPosition(Point(50,_cellSize.height /2));
        cell->addChild(icon,0,10);*/

        auto infoSprite = TextSprite::create(stageText,GameConfig::defaultFontName,25,
            Size(_cellSize.width - 200,_cellSize.height - 50),TextHAlignment::LEFT,TextVAlignment::CENTER);
        infoSprite->setPosition(Point(_cellSize.width /2,_cellSize.height /2));
        cell->addChild(infoSprite,0,20);
    }
    else
    {
        auto icon = (Sprite*)cell->getChildByTag(10);
        if (icon)
        {
            //icon->setSpriteFrame(iconFileName);
        }

        auto label = (TextSprite*)cell->getChildByTag(20);
        if (label)
        {
            label->setText(stageText);
            //label->setColor(textColor);
        }
    }

    return cell;
}

void StageSelect::tableCellTouched(extension::TableView* table, extension::TableViewCell* cell)
{
    _selectStage = cell->getIdx();
}

void StageSelect::menuCallbackFight(Ref *sender)
{
    auto battle = Battleground::create(_selectStage);
    Director::getInstance()->replaceScene(battle);
}

cocos2d::Size StageSelect::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return _cellSize;
}

ssize_t StageSelect::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return 50;
}

void StageSelect::menuCallbackClosed(Ref *sender)
{
    this->runAction(FadeTo::create(0.15f,0));
    auto action = Sequence::create(
        MoveBy::create(0.15f, Point(0,s_visibleRect.visibleHeight * 0.8f)),
        CallFunc::create(
        [&](){
            _eventDispatcher->dispatchCustomEvent(StageSelect::eventBack);

            this->removeFromParentAndCleanup(true);
    }  ),nullptr);
    _panel->runAction(action);
}
