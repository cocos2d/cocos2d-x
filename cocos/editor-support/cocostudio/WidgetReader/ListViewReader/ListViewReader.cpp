

#include "ListViewReader.h"
#include "ui/UIListView.h"
#include "cocostudio/CocoLoader.h"

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
    
    void ListViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        ScrollViewReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
        
        ListView* listView = static_cast<ListView*>(widget);
        
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
            
            if (key == "direction") {
                listView->setDirection((ScrollView::Direction)valueToFloat(value));
            }
            else if(key == "gravity"){
                listView->setGravity((ListView::Gravity)valueToInt(value));
            }else if(key == "itemMargin"){
                listView->setItemsMargin(valueToFloat(value));
            }
            
        } //end of for loop
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

