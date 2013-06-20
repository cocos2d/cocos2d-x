#include "TableViewTestScene.h"
#include "CustomTableViewCell.h"
#include "../ExtensionsTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

void runTableViewTest()
{
	Scene *pScene = Scene::create();
	TableViewTestLayer *pLayer = TableViewTestLayer::create();
	pScene->addChild(pLayer);
	Director::sharedDirector()->replaceScene(pScene);
}

// on "init" you need to initialize your instance
bool TableViewTestLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Size winSize = Director::sharedDirector()->getWinSize();

    TableView* tableView = TableView::create(this, CCSizeMake(250, 60));
    tableView->setDirection(kScrollViewDirectionHorizontal);
    tableView->setPosition(ccp(20,winSize.height/2-30));
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();

	tableView = TableView::create(this, CCSizeMake(60, 250));
	tableView->setDirection(kScrollViewDirectionVertical);
	tableView->setPosition(ccp(winSize.width-150,winSize.height/2-120));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();

	// Back Menu
	MenuItemFont *itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(TableViewTestLayer::toExtensionsMainLayer, this));
	itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
	Menu *menuBack = Menu::create(itemBack, NULL);
	menuBack->setPosition(PointZero);
	addChild(menuBack);

    return true;
}

void TableViewTestLayer::toExtensionsMainLayer(cocos2d::Object *sender)
{
	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}

void TableViewTestLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

Size TableViewTestLayer::tableCellSizeForIndex(TableView *table, unsigned int idx)
{
    if (idx == 2) {
        return CCSizeMake(100, 100);
    }
    return CCSizeMake(60, 60);
}

TableViewCell* TableViewTestLayer::tableCellAtIndex(TableView *table, unsigned int idx)
{
    String *string = String::createWithFormat("%d", idx);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        Sprite *sprite = Sprite::create("Images/Icon.png");
        sprite->setAnchorPoint(PointZero);
        sprite->setPosition(ccp(0, 0));
        cell->addChild(sprite);

        LabelTTF *label = LabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(PointZero);
		label->setAnchorPoint(PointZero);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        LabelTTF *label = (LabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }


    return cell;
}

unsigned int TableViewTestLayer::numberOfCellsInTableView(TableView *table)
{
    return 20;
}
