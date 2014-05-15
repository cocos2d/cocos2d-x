

#include "LoadingBarReader.h"
#include "ui/UILoadingBar.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static LoadingBarReader* instanceLoadingBar = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(LoadingBarReader)
    
    LoadingBarReader::LoadingBarReader()
    {
        
    }
    
    LoadingBarReader::~LoadingBarReader()
    {
        
    }
    
    LoadingBarReader* LoadingBarReader::getInstance()
    {
        if (!instanceLoadingBar)
        {
            instanceLoadingBar = new LoadingBarReader();
        }
        return instanceLoadingBar;
    }
    
    void LoadingBarReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        LoadingBar* loadingBar = static_cast<LoadingBar*>(widget);
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "textureData");
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
        std::string imageFileName = this->getResourcePath(imageFileNameDic, "path", (Widget::TextureResType)imageFileNameType);
        loadingBar->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);

        
        /* gui mark add load bar scale9 parse */
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        loadingBar->setScale9Enabled(scale9Enable);
        
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            
            loadingBar->setCapInsets(Rect(cx, cy, cw, ch));
            
            float width = DICTOOL->getFloatValue_json(options, "width");
            float height = DICTOOL->getFloatValue_json(options, "height");
            loadingBar->setSize(Size(width, height));
        }
        /**/
        
        loadingBar->setDirection(LoadingBar::Direction(DICTOOL->getIntValue_json(options, "direction")));
        loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent"));
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
