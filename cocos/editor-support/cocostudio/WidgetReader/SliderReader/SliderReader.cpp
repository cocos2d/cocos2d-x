

#include "SliderReader.h"
#include "ui/UISlider.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static SliderReader* instanceSliderReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(SliderReader)
    
    SliderReader::SliderReader()
    {
        
    }
    
    SliderReader::~SliderReader()
    {
        
    }
    
    SliderReader* SliderReader::getInstance()
    {
        if (!instanceSliderReader)
        {
            instanceSliderReader = new SliderReader();
        }
        return instanceSliderReader;
    }
    
    void SliderReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
                
        Slider* slider = static_cast<Slider*>(widget);
        
        bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        slider->setScale9Enabled(barTextureScale9Enable);
        
        slider->setPercent(DICTOOL->getIntValue_json(options, "percent"));

        
        bool bt = DICTOOL->checkObjectExist_json(options, "barFileName");
        float barLength = DICTOOL->getFloatValue_json(options, "length");
        if (bt)
        {
            const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "barFileNameData");
            int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
            std::string imageFileName = this->getResourcePath(imageFileNameDic, "path", (Widget::TextureResType)imageFileNameType);
            slider->loadBarTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
            
            if (barTextureScale9Enable)
            {
                slider->setSize(Size(barLength, slider->getContentSize().height));
            }
        }
        
        //loading normal slider ball texture
        const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, "ballNormalData");
        int normalType = DICTOOL->getIntValue_json(normalDic, "resourceType");
        std::string imageFileName = this->getResourcePath(normalDic, "path", (Widget::TextureResType)normalType);
        slider->loadSlidBallTextureNormal(imageFileName, (Widget::TextureResType)normalType);
        
        
        //loading slider ball press texture
        const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, "ballPressedData");
        int pressedType = DICTOOL->getIntValue_json(pressedDic, "resourceType");
        std::string pressedFileName = this->getResourcePath(pressedDic, "path", (Widget::TextureResType)pressedType);
        slider->loadSlidBallTexturePressed(pressedFileName, (Widget::TextureResType)pressedType);
        
        //loading silder ball disable texture
        const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, "ballDisabledData");
        int disabledType = DICTOOL->getIntValue_json(disabledDic, "resourceType");
        std::string disabledFileName = this->getResourcePath(disabledDic, "path", (Widget::TextureResType)disabledType);
        slider->loadSlidBallTextureDisabled(disabledFileName, (Widget::TextureResType)disabledType);
        
        //load slider progress texture
        const rapidjson::Value& progressBarDic = DICTOOL->getSubDictionary_json(options, "progressBarData");
        int progressBarType = DICTOOL->getIntValue_json(progressBarDic, "resourceType");
        std::string progressBarFileName = this->getResourcePath(progressBarDic, "path", (Widget::TextureResType)progressBarType);
        slider->loadProgressBarTexture(progressBarFileName, (Widget::TextureResType)progressBarType);
        
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
