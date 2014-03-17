

#include "ListViewReader.h"
#include "../../../GUI/UIWidgets/ScrollWidget/UIListView.h"

NS_CC_EXT_BEGIN

static ListViewReader* instanceListViewReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(ListViewReader)

ListViewReader::ListViewReader()
{
    
}

ListViewReader::~ListViewReader()
{
    
}

ListViewReader* ListViewReader::getInstance()
{
    if (!instanceListViewReader)
    {
        instanceListViewReader = new ListViewReader();
    }
    return instanceListViewReader;
}

void ListViewReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    ScrollViewReader::setPropsFromJsonDictionary(widget, options);
    
    
    ui::ListView* listView = (ui::ListView*)widget;
    
	int direction = DICTOOL->getFloatValue_json(options, "direction");
	listView->setDirection((ui::SCROLLVIEW_DIR)direction);
    
    ui::ListViewGravity gravity = (ui::ListViewGravity)DICTOOL->getIntValue_json(options, "gravity");
    listView->setGravity(gravity);
    
    float itemMargin = DICTOOL->getFloatValue_json(options, "itemMargin");
    listView->setItemsMargin(itemMargin);
}

NS_CC_EXT_END
