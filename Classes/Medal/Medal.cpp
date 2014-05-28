//
//  Medal.cpp
//  BlackWings
//
//  Created by Jacky on 14-5-27.
//
//

#include "Medal.h"
#include "VisibleRect.h"
#include "TextSprite.h"
#include "MenuItemImageLabel.h"
#include "GameStrings.h"

USING_NS_CC;

const std::string Medal::eventBack = "eventMedalBack";

bool Medal::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    GSMedalInfo((GameLanguage)s_gameConfig.language);
    
    readINI();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto panelSize = Size(s_visibleRect.visibleWidth,s_visibleRect.visibleHeight-60);
    
    _cellSize.width = 546;
    _cellSize.height = 140;
    
    _panel = Scale9Sprite::create("windowBox.png");
    _panel->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    _panel->setPosition(Point(s_visibleRect.center.x,s_visibleRect.top.y + panelSize.height));
    _panel->setContentSize(panelSize);
    this->addChild(_panel);
    _panel->runAction(MoveTo::create(0.15f,s_visibleRect.top));
    
    auto tableView = TableView::create(this, Size(panelSize.width, panelSize.height - 100));
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setPosition(Point(50,20));
    tableView->setDelegate(this);
    tableView->reloadData();
    _panel->addChild(tableView, 1);
    
    auto itemClosed = MenuItemImageLabel::createWithFrameName("back_0.png","back_1.png",
                                                              CC_CALLBACK_1(Medal::menuCallbackClosed,this));
    itemClosed->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    itemClosed->setPosition((s_visibleRect.visibleWidth + panelSize.width)/2,panelSize.height);
    
    
    auto menu = Menu::create( itemClosed, nullptr);
    menu->setPosition(Point::ZERO);
    _panel->addChild(menu,3);
    return true;
}

cocos2d::extension::TableViewCell* Medal::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    auto cell = table->dequeueCell();
    
    if (!cell)
    {
        cell = TableViewCell::create();
        
        /*auto icon = Sprite::createWithSpriteFrameName(iconFileName);
         icon->setPosition(Point(50,_cellSize.height /2));
         cell->addChild(icon,0,10);*/
        
        auto cell_node = getItemNode(idx);
        cell->addChild(cell_node,0,10);
    }
    else
    {
        auto icon_bk = (Sprite*)cell->getChildByTag(10)->getChildByTag(30);
        if (icon_bk) {
            if (medal_lock[idx]) {
                icon_bk->setSpriteFrame("icon_medal_box_1.png");
            }
            else{
                icon_bk->setSpriteFrame("icon_medal_box_0.png");
            }
        }
        auto icon = (Sprite*)cell->getChildByTag(10)->getChildByTag(40);
        if (icon)
        {
            char iconFileName[30];
            sprintf(iconFileName,"icon_medal_%d.png",idx+1);
            icon->setSpriteFrame(iconFileName);
        }
        
        auto label_name = (TextSprite*)cell->getChildByTag(10)->getChildByTag(50);
        if (label_name)
        {
            label_name->setText(s_gameStrings.medalInfo->medalname[idx]);
            //label->setColor(textColor);
        }
        
        auto label_dscr = (TextSprite*)cell->getChildByTag(10)->getChildByTag(60);
        if (label_dscr) {
            label_dscr->setText(s_gameStrings.medalInfo->medaldscr[idx]);
        }
    }
    
    return cell;
}

void Medal::tableCellTouched(extension::TableView* table, extension::TableViewCell* cell)
{
    log("%d",cell->getIdx());
    
}

cocos2d::Size Medal::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return _cellSize;
}

ssize_t Medal::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return 25;
}

void Medal::menuCallbackClosed(Ref *sender)
{
    this->runAction(FadeTo::create(0.15f,0));
    auto action = Sequence::create(
                                   MoveBy::create(0.15f, Point(0,s_visibleRect.visibleHeight * 0.8f)),
                                   CallFunc::create(
                                                    [&](){
                                                        _eventDispatcher->dispatchCustomEvent(Medal::eventBack);
                                                        
                                                        this->removeFromParentAndCleanup(true);
                                                    }  ),nullptr);
    _panel->runAction(action);
}

Node* Medal::getItemNode(int i)
{
	auto item = Node::create();
	auto item_bk = Sprite::createWithSpriteFrameName("medal_minibox_0.png");
	item_bk->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	item->addChild(item_bk,0,20);
    
    Sprite* item_image_bk = nullptr;
    if (medal_lock[i]) {
        item_image_bk = Sprite::createWithSpriteFrameName("icon_medal_box_1.png");
    }
    else{
        item_image_bk = Sprite::createWithSpriteFrameName("icon_medal_box_0.png");
    }
    item_image_bk->setAnchorPoint(Point::ANCHOR_MIDDLE);
	item_image_bk->setPosition(Point(70,_cellSize.height/2-10));
	item->addChild(item_image_bk,0,30);
    
    char iconFileName[30];
    sprintf(iconFileName,"icon_medal_%d.png",i+1);

	auto item_image=Sprite::createWithSpriteFrameName(iconFileName);
	item_image->setAnchorPoint(Point::ANCHOR_MIDDLE);
	item_image->setPosition(Point(70,_cellSize.height/2-5));
	item->addChild(item_image,0,40);
    
    auto infoSprite_1 = TextSprite::create(s_gameStrings.medalInfo->medalname[i],GameConfig::defaultFontName,25,
                                         Size(_cellSize.width - 200,_cellSize.height - 30),TextHAlignment::LEFT,TextVAlignment::CENTER);
    infoSprite_1->setPosition(Point(_cellSize.width /2+50,_cellSize.height /2+30));
    infoSprite_1->setColor(Color3B(255, 255, 0));
    item->addChild(infoSprite_1,0,50);
    
    auto infoSprite_2 = TextSprite::create(s_gameStrings.medalInfo->medaldscr[i],GameConfig::defaultFontName,20,
                                           Size(_cellSize.width - 200,_cellSize.height - 30),TextHAlignment::LEFT,TextVAlignment::CENTER);
    infoSprite_2->setPosition(Point(_cellSize.width /2+50,_cellSize.height /2-10));
    item->addChild(infoSprite_2,0,60);
    
	return item;
}

void Medal::readINI()
{
    for (int i=0; i<25; ++i) {
        medal_lock[i] = true;
        medal_get[i] = false;
    }
    
    medal_lock[10] = false;
}
