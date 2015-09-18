#ifndef __TABLEVIEWTESTSCENE_H__
#define __TABLEVIEWTESTSCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "BaseTest.h"

DEFINE_TEST_SUITE(TableViewTests);

class TableViewTest : public TestCase, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    CREATE_FUNC(TableViewTest);

    virtual bool init() override;  
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override {}
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table)override;
};

#endif // __TABLEVIEWTESTSCENE_H__
