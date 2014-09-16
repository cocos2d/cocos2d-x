

#include "SliderReader.h"
#include "ui/UISlider.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static const char* P_Scale9Enable = "scale9Enable";
    static const char* P_Percent = "percent";
    static const char* P_BarFileNameData = "barFileNameData";
    static const char* P_Length = "length";
    static const char* P_BallNormalData = "ballNormalData";
    static const char* P_BallPressedData = "ballPressedData";
    static const char* P_BallDisabledData = "ballDisabledData";
    static const char* P_ProgressBarData = "progressBarData";
    
    static SliderReader* instanceSliderReader = nullptr;
    
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
            instanceSliderReader = new (std::nothrow) SliderReader();
        }
        return instanceSliderReader;
    }
    
    void SliderReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode* cocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        Slider* slider = static_cast<Slider*>(widget);
        
        float barLength = 0.0f;
        int percent = slider->getPercent();
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            //control custom properties
            else if (key == P_Scale9Enable) {
                slider->setScale9Enabled(valueToBool(value));
            }
            else if(key == P_Percent){
                percent = valueToInt(value);
            }else if(key == P_BarFileNameData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadBarTexture(backgroundValue, imageFileNameType);
                
            }else if(key == P_Length){
                barLength = valueToFloat(value);
            }else if(key == P_BallNormalData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadSlidBallTextureNormal(backgroundValue, imageFileNameType);

            }else if(key == P_BallPressedData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadSlidBallTexturePressed(backgroundValue, imageFileNameType);
                
            }else if(key == P_BallDisabledData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadSlidBallTextureDisabled(backgroundValue, imageFileNameType);
                
            }else if(key == P_ProgressBarData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadProgressBarTexture(backgroundValue, imageFileNameType);
                
            }
            
        } //end of for loop
        
        if (slider->isScale9Enabled()) {
            slider->setContentSize(Size(barLength, slider->getContentSize().height));
        }
        slider->setPercent(percent);
        
        this->endSetBasicProperties(widget);
    }
    
    void SliderReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
                
        Slider* slider = static_cast<Slider*>(widget);
        
        bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, P_Scale9Enable);
        slider->setScale9Enabled(barTextureScale9Enable);
        
        slider->setPercent(DICTOOL->getIntValue_json(options, P_Percent));

        
//        bool bt = DICTOOL->checkObjectExist_json(options, P_BarFileName);
        float barLength = DICTOOL->getFloatValue_json(options, P_Length,290);
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, P_BarFileNameData);
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, P_ResourceType);
        std::string imageFileName = this->getResourcePath(imageFileNameDic, P_Path, (Widget::TextureResType)imageFileNameType);
        slider->loadBarTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
            
           
        
        if (barTextureScale9Enable)
        {
            slider->setContentSize(Size(barLength, slider->getContentSize().height));
        }
        
        //loading normal slider ball texture
        const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, P_BallNormalData);
        int normalType = DICTOOL->getIntValue_json(normalDic, P_ResourceType);
        imageFileName = this->getResourcePath(normalDic, P_Path, (Widget::TextureResType)normalType);
        slider->loadSlidBallTextureNormal(imageFileName, (Widget::TextureResType)normalType);
        
        
        //loading slider ball press texture
        const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, P_BallPressedData);
        int pressedType = DICTOOL->getIntValue_json(pressedDic, P_ResourceType);
        std::string pressedFileName = this->getResourcePath(pressedDic, P_Path, (Widget::TextureResType)pressedType);
        slider->loadSlidBallTexturePressed(pressedFileName, (Widget::TextureResType)pressedType);
        
        //loading silder ball disable texture
        const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, P_BallDisabledData);
        int disabledType = DICTOOL->getIntValue_json(disabledDic, P_ResourceType);
        std::string disabledFileName = this->getResourcePath(disabledDic, P_Path, (Widget::TextureResType)disabledType);
        slider->loadSlidBallTextureDisabled(disabledFileName, (Widget::TextureResType)disabledType);
        
        //load slider progress texture
        const rapidjson::Value& progressBarDic = DICTOOL->getSubDictionary_json(options, P_ProgressBarData);
        int progressBarType = DICTOOL->getIntValue_json(progressBarDic, P_ResourceType);
        std::string progressBarFileName = this->getResourcePath(progressBarDic, P_Path, (Widget::TextureResType)progressBarType);
        slider->loadProgressBarTexture(progressBarFileName, (Widget::TextureResType)progressBarType);
        
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
