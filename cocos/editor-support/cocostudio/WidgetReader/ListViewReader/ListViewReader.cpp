

#include "ListViewReader.h"
#include "ui/UIListView.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static const char* P_Direction = "direction";
    static const char* P_ItemMargin = "itemMargin";
    
    static ListViewReader* instanceListViewReader = nullptr;
    
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
            instanceListViewReader = new (std::nothrow) ListViewReader();
        }
        return instanceListViewReader;
    }
    
    void ListViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode* cocoNode)
    {
        ScrollViewReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        ListView* listView = static_cast<ListView*>(widget);
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            if (key == P_Direction) {
                listView->setDirection((ScrollView::Direction)valueToInt(value));
            }
            else if(key == P_Gravity){
                listView->setGravity((ListView::Gravity)valueToInt(value));
            }else if(key == P_ItemMargin){
                listView->setItemsMargin(valueToFloat(value));
            }
            
        } //end of for loop
    }
    
    void ListViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        ScrollViewReader::setPropsFromJsonDictionary(widget, options);
        
        
        ListView* listView = static_cast<ListView*>(widget);
                
        int direction = DICTOOL->getFloatValue_json(options, P_Direction,2);
        listView->setDirection((ScrollView::Direction)direction);
        
        ListView::Gravity gravity = (ListView::Gravity)DICTOOL->getIntValue_json(options, P_Gravity,3);
        listView->setGravity(gravity);
        
        float itemMargin = DICTOOL->getFloatValue_json(options, P_ItemMargin);
        listView->setItemsMargin(itemMargin);
    }
}

