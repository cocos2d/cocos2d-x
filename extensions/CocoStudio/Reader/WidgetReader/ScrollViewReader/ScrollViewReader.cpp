

#include "ScrollViewReader.h"
#include "../../../GUI/UIWidgets/ScrollWidget/UIScrollView.h"

NS_CC_EXT_BEGIN

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



void ScrollViewReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    LayoutReader::setPropsFromJsonDictionary(widget, options);
    
    
    ui::ScrollView* scrollView = (ui::ScrollView*)widget;
    
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth",200);
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight",200);
    scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
    
	int direction = DICTOOL->getFloatValue_json(options, "direction",1);
	scrollView->setDirection((ui::SCROLLVIEW_DIR)direction);
    
    scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
    
    
    LayoutReader::setColorPropsFromJsonDictionary(widget, options);
}

void ScrollViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    //TODO::need to refactor...
    LayoutReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
    
    ui::ScrollView* scrollView = static_cast<ui::ScrollView*>(widget);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    float innerWidth = 0.0f;
    float innerHeight = 0.0f;
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue(pCocoLoader);
        if (key == "innerWidth") {
            innerWidth = valueToFloat(value);
        }
        else if(key == "innerHeight"){
            innerHeight = valueToFloat(value);
        }else if(key == "direction"){
            scrollView->setDirection((ui::SCROLLVIEW_DIR)valueToInt(value));
        }else if(key == "bounceEnable"){
            scrollView->setBounceEnabled(valueToBool(value));
        }
        
    } //end of for loop
    scrollView->setInnerContainerSize(CCSize(innerWidth, innerHeight));
    
}

NS_CC_EXT_END
