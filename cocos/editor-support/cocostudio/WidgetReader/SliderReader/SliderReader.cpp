

#include "SliderReader.h"
#include "gui/UISlider.h"

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
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        Slider* slider = static_cast<Slider*>(widget);
        
        bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, "barTextureScale9Enable");
        slider->setScale9Enabled(barTextureScale9Enable);
        bool bt = DICTOOL->checkObjectExist_json(options, "barFileName");
        float barLength = DICTOOL->getFloatValue_json(options, "length");
        if (bt)
        {
            if (barTextureScale9Enable)
            {
                
                const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "barFileNameData");
                int imageFileType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
                switch (imageFileType)
                {
                    case 0:
                    {
                        std::string tp_b = jsonPath;
                        const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
                        const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
                        slider->loadBarTexture(imageFileName_tp);
                        break;
                    }
                    case 1:
                    {
                        const char* imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                        slider->loadBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
                        break;
                    }
                    default:
                        break;
                }
                
                slider->setSize(Size(barLength, slider->getContentSize().height));
            }
            else
            {
                const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "barFileNameData");
                int imageFileType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
                switch (imageFileType)
                {
                    case 0:
                    {
                        std::string tp_b = jsonPath;
                        const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                        const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
                        slider->loadBarTexture(imageFileName_tp);
                        break;
                    }
                    case 1:
                    {
                        const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                        slider->loadBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        
        const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, "ballNormalData");
        int normalType = DICTOOL->getIntValue_json(normalDic, "resourceType");
        switch (normalType)
        {
            case 0:
            {
                std::string tp_n = jsonPath;
                const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
                const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():nullptr;
                slider->loadSlidBallTextureNormal(normalFileName_tp);
                break;
            }
            case 1:
            {
                const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
                slider->loadSlidBallTextureNormal(normalFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, "ballPressedData");
        int pressedType = DICTOOL->getIntValue_json(pressedDic, "resourceType");
        switch (pressedType)
        {
            case 0:
            {
                std::string tp_p = jsonPath;
                const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
                const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():nullptr;
                slider->loadSlidBallTexturePressed(pressedFileName_tp);
                break;
            }
            case 1:
            {
                const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
                slider->loadSlidBallTexturePressed(pressedFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, "ballDisabledData");
        int disabledType = DICTOOL->getIntValue_json(disabledDic, "resourceType");
        switch (disabledType)
        {
            case 0:
            {
                std::string tp_d = jsonPath;
                const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
                const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():nullptr;
                slider->loadSlidBallTextureDisabled(disabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
                slider->loadSlidBallTextureDisabled(disabledFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        slider->setPercent(DICTOOL->getIntValue_json(options, "percent"));
        
        const rapidjson::Value& progressBarDic = DICTOOL->getSubDictionary_json(options, "progressBarData");
        int progressBarType = DICTOOL->getIntValue_json(progressBarDic, "resourceType");
        switch (progressBarType)
        {
            case 0:
            {
                std::string tp_b = jsonPath;
                const char* imageFileName = DICTOOL->getStringValue_json(progressBarDic, "path");
                const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
                slider->loadProgressBarTexture(imageFileName_tp);
                break;
            }
            case 1:
            {
                const char* imageFileName = DICTOOL->getStringValue_json(progressBarDic, "path");
                slider->loadProgressBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
