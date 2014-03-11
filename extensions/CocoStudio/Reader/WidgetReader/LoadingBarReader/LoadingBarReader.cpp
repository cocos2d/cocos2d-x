

#include "LoadingBarReader.h"
#include "../../../GUI/UIWidgets/UILoadingBar.h"

NS_CC_EXT_BEGIN

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

void LoadingBarReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    {
        ui::LoadingBar* loadingBar = (ui::LoadingBar*)widget;
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "textureData");
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
        switch (imageFileNameType)
        {
            case 0:
            {
                std::string tp_i = jsonPath;
                const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
                const char* imageFileName_tp = NULL;
                if (imageFileName && (strcmp(imageFileName, "") != 0))
                {
                    imageFileName_tp = tp_i.append(imageFileName).c_str();
                    loadingBar->loadTexture(imageFileName_tp);
                }
                break;
            }
            case 1:
            {
                const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
                loadingBar->loadTexture(imageFileName, ui::UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        loadingBar->setScale9Enabled(scale9Enable);
        
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            
            loadingBar->setCapInsets(CCRectMake(cx, cy, cw, ch));
            
            float width = DICTOOL->getFloatValue_json(options, "width");
            float height = DICTOOL->getFloatValue_json(options, "height");
            loadingBar->setSize(CCSizeMake(width, height));
        }
        
        loadingBar->setDirection(ui::LoadingBarType(DICTOOL->getIntValue_json(options, "direction")));
        loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent"));
    }
    
    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

NS_CC_EXT_END
