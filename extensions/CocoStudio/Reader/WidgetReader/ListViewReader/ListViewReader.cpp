

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
    
	int direction = DICTOOL->getFloatValue_json(options, "direction",2);
	listView->setDirection((ui::SCROLLVIEW_DIR)direction);
    
    ui::ListViewGravity gravity = (ui::ListViewGravity)DICTOOL->getIntValue_json(options, "gravity",3);
    listView->setGravity(gravity);
    
    float itemMargin = DICTOOL->getFloatValue_json(options, "itemMargin");
    listView->setItemsMargin(itemMargin);
}

void ListViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    ScrollViewReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
    
    ui::ListView* listView = static_cast<ui::ListView*>(widget);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue(pCocoLoader);
        
        if (key == "direction") {
            listView->setDirection((ui::SCROLLVIEW_DIR)valueToInt(value));
        }
        else if(key == "gravity"){
            listView->setGravity((ui::ListViewGravity)valueToInt(value));
        }else if(key == "itemMargin"){
            listView->setItemsMargin(valueToFloat(value));
        }
        
    } //end of for loop
}


NS_CC_EXT_END
