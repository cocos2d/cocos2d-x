#ifndef __TABLEVIEWTESTSCENE_H__
#define __TABLEVIEWTESTSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

void runTableViewTest();

class TableViewTestLayer : public cc::Layer, public cc::extension::TableViewDataSource, public cc::extension::TableViewDelegate
{
public:
    virtual bool init();  
   
	void toExtensionsMainLayer(cc::Object *sender);

    CREATE_FUNC(TableViewTestLayer);
    
    virtual void scrollViewDidScroll(cc::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cc::extension::ScrollView* view) {}
    virtual void tableCellTouched(cc::extension::TableView* table, cc::extension::TableViewCell* cell);
    virtual cc::Size tableCellSizeForIndex(cc::extension::TableView *table, unsigned int idx);
    virtual cc::extension::TableViewCell* tableCellAtIndex(cc::extension::TableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cc::extension::TableView *table);
};

#endif // __TABLEVIEWTESTSCENE_H__
