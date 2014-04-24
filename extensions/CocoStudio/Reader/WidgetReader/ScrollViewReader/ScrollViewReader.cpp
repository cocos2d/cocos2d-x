

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
    
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
    scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
    
	int direction = DICTOOL->getFloatValue_json(options, "direction");
	scrollView->setDirection((ui::SCROLLVIEW_DIR)direction);
    
    scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
    
    
    LayoutReader::setColorPropsFromJsonDictionary(widget, options);
}

NS_CC_EXT_END
