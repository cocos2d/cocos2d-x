

#include "PageViewReader.h"
#include "../../../GUI/UIWidgets/ScrollWidget/UIPageView.h"

NS_CC_EXT_BEGIN

static PageViewReader* instancePageViewReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(PageViewReader)

PageViewReader::PageViewReader()
{
    
}

PageViewReader::~PageViewReader()
{
    
}

PageViewReader* PageViewReader::getInstance()
{
    if (!instancePageViewReader)
    {
        instancePageViewReader = new PageViewReader();
    }
    return instancePageViewReader;
}

void PageViewReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    LayoutReader::setPropsFromJsonDictionary(widget, options);
}

void PageViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    LayoutReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
}



NS_CC_EXT_END
