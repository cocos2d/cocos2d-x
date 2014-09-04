

#include "LoadingBarReader.h"
#include "ui/UILoadingBar.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace cocostudio
{
    static const char* P_Scale9Enable = "scale9Enable";
    static const char* P_CapInsetsX = "capInsetsX";
    static const char* P_CapInsetsY = "capInsetsY";
    static const char* P_CapInsetsWidth = "capInsetsWidth";
    static const char* P_CapInsetsHeight = "capInsetsHeight";
    static const char* P_TextureData = "textureData";
    static const char* P_Direction = "direction";
    static const char* P_Percent = "percent";
    
    static LoadingBarReader* instanceLoadingBar = nullptr;
    
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
            instanceLoadingBar = new (std::nothrow) LoadingBarReader();
        }
        return instanceLoadingBar;
    }
    
    void LoadingBarReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        LoadingBar* loadingBar = static_cast<LoadingBar*>(widget);
        this->beginSetBasicProperties(widget);
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        int percent = loadingBar->getPercent();
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if (key == P_Scale9Enable) {
                loadingBar->setScale9Enabled(valueToBool(value));
            }
            else if (key == P_TextureData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                loadingBar->loadTexture(backgroundValue, imageFileNameType);
                
            }
            else if(key == P_CapInsetsX){
                capsx = valueToFloat(value);
            }else if(key == P_CapInsetsY){
                capsy = valueToFloat(value);
            }else if(key == P_CapInsetsWidth){
                capsWidth = valueToFloat(value);
            }else if(key == P_CapInsetsHeight){
                capsHeight = valueToFloat(value);
            }else if(key == P_Direction){
                loadingBar->setDirection((LoadingBar::Direction)valueToInt(value));
            }else if(key == P_Percent){
                percent = valueToInt(value);
            }
            
        } //end of for loop
        
        if (loadingBar->isScale9Enabled()) {
            loadingBar->setCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
        }
        loadingBar->setPercent(percent);
        this->endSetBasicProperties(widget);
    }
    
    void LoadingBarReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        LoadingBar* loadingBar = static_cast<LoadingBar*>(widget);
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, P_TextureData);
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, P_ResourceType);
        std::string imageFileName = this->getResourcePath(imageFileNameDic, P_Path, (Widget::TextureResType)imageFileNameType);
        loadingBar->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);

        
        /* gui mark add load bar scale9 parse */
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, P_Scale9Enable);
        loadingBar->setScale9Enabled(scale9Enable);
        
        
        float cx = DICTOOL->getFloatValue_json(options, P_CapInsetsX);
        float cy = DICTOOL->getFloatValue_json(options, P_CapInsetsY);
        float cw = DICTOOL->getFloatValue_json(options, P_CapInsetsWidth,1);
        float ch = DICTOOL->getFloatValue_json(options, P_CapInsetsHeight,1);
        
        if (scale9Enable) {
            loadingBar->setCapInsets(Rect(cx, cy, cw, ch));

        }
        
        float width = DICTOOL->getFloatValue_json(options, P_Width);
        float height = DICTOOL->getFloatValue_json(options, P_Height);
        loadingBar->setContentSize(Size(width, height));
        
        /**/
        
        loadingBar->setDirection(LoadingBar::Direction(DICTOOL->getIntValue_json(options, P_Direction)));
        loadingBar->setPercent(DICTOOL->getIntValue_json(options, P_Percent,100));
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
