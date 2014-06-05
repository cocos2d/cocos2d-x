

#include "PageViewReader.h"
#include "ui/UIPageView.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
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
    
    void PageViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        LayoutReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
    }
    
    void PageViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        LayoutReader::setPropsFromJsonDictionary(widget, options);
    }
}
