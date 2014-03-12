

#include "ScrollViewReader.h"
#include "ui/UIScrollView.h"

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
    
    void ScrollViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        LayoutReader::setPropsFromJsonDictionary(widget, options);
        
        
        ScrollView* scrollView = static_cast<ScrollView*>(widget);
        float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
        float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
        int direction = DICTOOL->getFloatValue_json(options, "direction");
        scrollView->setDirection((SCROLLVIEW_DIR)direction);
        scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
        
        
        LayoutReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
