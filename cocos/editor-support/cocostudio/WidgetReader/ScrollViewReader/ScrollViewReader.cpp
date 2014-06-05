

#include "ScrollViewReader.h"
#include "ui/UIScrollView.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static ScrollViewReader* instanceScrollViewReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(ScrollViewReader)
    
    ScrollViewReader::ScrollViewReader()
    {
        
    }
    
    ScrollViewReader::~ScrollViewReader()
    {
        
    }
    
    ScrollViewReader* ScrollViewReader::getInstance()
    {
        if (!instanceScrollViewReader)
        {
            instanceScrollViewReader = new ScrollViewReader();
        }
        return instanceScrollViewReader;
    }
    
    void ScrollViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        LayoutReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
        
        ScrollView* scrollView = static_cast<ScrollView*>(widget);

        
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
            
            if (key == "innerWidth") {
                scrollView->setInnerContainerSize(Size(valueToFloat(value), scrollView->getInnerContainerSize().height));
            }
            else if(key == "innerHeight"){
                scrollView->setInnerContainerSize(Size(scrollView->getInnerContainerSize().height, valueToFloat(value) ));
            }else if(key == "direction"){
                scrollView->setDirection((ScrollView::Direction)valueToInt(value));
            }else if(key == "bounceEnable"){
                scrollView->setBounceEnabled(valueToBool(value));
            }
            
        } //end of for loop

    }
    
    void ScrollViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        LayoutReader::setPropsFromJsonDictionary(widget, options);
        
        
        ScrollView* scrollView = static_cast<ScrollView*>(widget);
        float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
        float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
        int direction = DICTOOL->getFloatValue_json(options, "direction");
        scrollView->setDirection((ScrollView::Direction)direction);
        scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
        
        
        LayoutReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
