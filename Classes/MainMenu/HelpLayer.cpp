#include "HelpLayer.h"
#include "Configuration.h"
#include "GameStrings.h"
#include "VisibleRect.h"
#include "MenuItemImageLabel.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool HelpLayer::init()
{
    if (LayerColor::initWithColor(Color4B(255,255,255,0)))
    {
        GSHelpInfoInit((GameLanguage)s_gameConfig.language);

        this->runAction(FadeTo::create(0.5f,100));

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        _panelSize.width = s_visibleRect.visibleWidth - 97;
        _panelSize.height = s_visibleRect.visibleHeight - 130;
        _cellSize.width = _panelSize.width;
        _cellSize.height = 200;

        auto panel = Scale9Sprite::create("windowBox.png");
        panel->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        panel->setPosition(s_visibleRect.center.x,s_visibleRect.top.y + 300);
        panel->setContentSize(_panelSize);
        this->addChild(panel);

        auto action = Sequence::create( MoveTo::create(0.15f,Point(s_visibleRect.center.x,s_visibleRect.top.y - 60.0f)),
            MoveTo::create(0.07f,Point(s_visibleRect.center.x,s_visibleRect.top.y - 48.5f)),nullptr);
        panel->runAction(action);

        auto tableView = TableView::create(this, Size(_panelSize.width, _panelSize.height - 57));
        tableView->setDirection(ScrollView::Direction::VERTICAL);
        tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
        tableView->setPosition(Point(0,7));
        tableView->setDelegate(this);
        tableView->reloadData();
        panel->addChild(tableView);

        auto titleBg = Scale9Sprite::create("helpTitleBG.png");
        titleBg->setContentSize(Size(_cellSize.width - 6,50));
        titleBg->setPosition(_panelSize.width /2, _panelSize.height - 27);
        panel->addChild(titleBg);

        auto titleText = TextSprite::create(s_gameStrings.mainMenu->helpTitle);
        titleText->setPosition(_panelSize.width /2, _panelSize.height - 27);
        panel->addChild(titleText);

        auto itemClosed = MenuItemImageLabel::createWithFrameName("back_0.png","back_1.png",
            CC_CALLBACK_1(HelpLayer::menuCallbackClosed,this));
        itemClosed->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
        itemClosed->setPosition(s_visibleRect.rightTop);

        auto menu = Menu::create( itemClosed, nullptr);
        menu->setPosition(Point::ZERO);
        this->addChild(menu);

        return true;
    }

    return false;
}

void HelpLayer::menuCallbackClosed(Ref *sender)
{
    this->removeFromParentAndCleanup(true);
}

extension::TableViewCell* HelpLayer::tableCellAtIndex(extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();

    std::string text;
    char iconFileName[25];
    Color3B textColor;

    switch (idx)
    {
    case 0:
        text = s_gameStrings.helpInfo->sparInfo;
        sprintf(iconFileName,"icon_stone.png");
        textColor = Color3B::BLUE;
        break;
    case 1:
        text = s_gameStrings.helpInfo->gemInfo;
        sprintf(iconFileName,"icon_gem.png");
        textColor = Color3B::BLUE;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        if (s_gameConfig.fightersLocked[idx - 2])
        {
            sprintf(iconFileName,"icon_unknown.png");
            text = s_gameStrings.helpInfo->fighterLocked;
            textColor = Color3B::GRAY;
        } 
        else
        {
            sprintf(iconFileName,"plain_%d_lv_%d.png",idx - 1,s_gameConfig.fightersLevle[idx - 2] + 1);
            text = s_gameStrings.helpInfo->fighter[idx - 2];
            textColor = Color3B::YELLOW;
        }
        break;
    case 8: 
    case 9:
    case 10:
        if (s_gameConfig.weaponLocked)
        {
            sprintf(iconFileName,"icon_unknown.png");
            text = s_gameStrings.helpInfo->weaponLocked;
            textColor = Color3B::GRAY;
        } 
        else
        {
            sprintf(iconFileName,"bomb_%d_%d.png",idx - 7,s_gameConfig.weaponsLevel[idx - 8] + 1);
            text = s_gameStrings.helpInfo->weapon[idx - 8];
            textColor = Color3B::ORANGE;
        }
        break;
    default:
        break;
    }

    if (!cell) 
    {
        cell = TableViewCell::create();

        auto cellBg = Scale9Sprite::create("helpCellBG.png");
        cellBg->setContentSize(Size(_cellSize.width - 6,_cellSize.height - 30));
        cellBg->setPosition(_cellSize.width /2, _cellSize.height / 2);
        cell->addChild(cellBg);

        auto icon = Sprite::createWithSpriteFrameName(iconFileName);
        icon->setPosition(Point(50,_cellSize.height /2));
        cell->addChild(icon,0,10);
        
        auto infoSprite = TextSprite::create(text,GameConfig::defaultFontName,25,
            Size(_cellSize.width - 200,_cellSize.height - 50),TextHAlignment::LEFT,TextVAlignment::CENTER);
        infoSprite->setPosition(Point(_cellSize.width /2,_cellSize.height /2));
        cell->addChild(infoSprite,0,20);
        infoSprite->setColor(textColor);
    }
    else
    {
        auto icon = (Sprite*)cell->getChildByTag(10);
        if (icon)
        {
            icon->setSpriteFrame(iconFileName);
        }

        auto label = (TextSprite*)cell->getChildByTag(20);
        if (label)
        {
            label->setText(text);
            label->setColor(textColor);
        }
    }

    return cell;
}

Size HelpLayer::tableCellSizeForIndex(extension::TableView *table, ssize_t idx)
{
    return _cellSize;
}

ssize_t HelpLayer::numberOfCellsInTableView(extension::TableView *table)
{
    return 2 + FIGHTER_MAX + WEAPON_MAX;
}