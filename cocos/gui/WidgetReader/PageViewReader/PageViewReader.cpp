

#include "PageViewReader.h"
#include "gui/UIPageView.h"

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
    
    void PageViewReader::setPropsFromJsonDictionary(gui::Widget *widget, const rapidjson::Value &options)
    {
        LayoutReader::setPropsFromJsonDictionary(widget, options);
    }
}
