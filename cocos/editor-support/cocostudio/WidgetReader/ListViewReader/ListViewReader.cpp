

#include "ListViewReader.h"
#include "ui/UIListView.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
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
    
    void ListViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        ScrollViewReader::setPropsFromJsonDictionary(widget, options);
        
        
        ListView* listView = static_cast<ListView*>(widget);
                
        int direction = DICTOOL->getFloatValue_json(options, "direction");
        listView->setDirection((ScrollView::Direction)direction);
        
        ListView::Gravity gravity = (ListView::Gravity)DICTOOL->getIntValue_json(options, "gravity");
        listView->setGravity(gravity);
        
        float itemMargin = DICTOOL->getFloatValue_json(options, "itemMargin");
        listView->setItemsMargin(itemMargin);
    }
}

