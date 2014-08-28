

#include "PageViewReader.h"
#include "ui/UIPageView.h"
#include "ui/UILayout.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static PageViewReader* instancePageViewReader = nullptr;
    
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
            instancePageViewReader = new (std::nothrow) PageViewReader();
        }
        return instancePageViewReader;
    }
    
    void PageViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
	{
		LayoutReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
    }
    
    void PageViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        LayoutReader::setPropsFromJsonDictionary(widget, options);
    }
}
