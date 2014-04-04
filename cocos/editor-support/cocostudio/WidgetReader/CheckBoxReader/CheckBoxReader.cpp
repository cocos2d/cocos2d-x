

#include "CheckBoxReader.h"
#include "ui/UICheckBox.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static CheckBoxReader* instanceCheckBoxReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(CheckBoxReader)
    
    CheckBoxReader::CheckBoxReader()
    {
        
    }
    
    CheckBoxReader::~CheckBoxReader()
    {
        
    }
    
    CheckBoxReader* CheckBoxReader::getInstance()
    {
        if (!instanceCheckBoxReader)
        {
            instanceCheckBoxReader = new CheckBoxReader();
        }
        return instanceCheckBoxReader;
    }
    
    void CheckBoxReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        CheckBox* checkBox = static_cast<CheckBox*>(widget);
        
        const rapidjson::Value& backGroundDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxData");
        int backGroundType = DICTOOL->getIntValue_json(backGroundDic, "resourceType");
        switch (backGroundType)
        {
            case 0:
            {
                const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
                std::string backGroundFileName_tp;
                if (nullptr != backGroundFileName) {
                    backGroundFileName_tp = jsonPath + backGroundFileName;
                }
                checkBox->loadTextureBackGround(backGroundFileName_tp);
                break;
            }
            case 1:
            {
                std::string backGroundFileNameStr;
                const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
                if (nullptr != backGroundFileName) {
                    backGroundFileNameStr = std::string(backGroundFileName);
                }
                checkBox->loadTextureBackGround(backGroundFileNameStr,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        const rapidjson::Value& backGroundSelectedDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxSelectedData");
        int backGroundSelectedType = DICTOOL->getIntValue_json(backGroundSelectedDic, "resourceType");
        switch (backGroundSelectedType)
        {
            case 0:
            {
                const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
                std::string backGroundSelectedFileName_tp;
                if (nullptr != backGroundSelectedFileName) {
                    backGroundSelectedFileName_tp = jsonPath + backGroundSelectedFileName;
                }
                checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName_tp);
                break;
            }
            case 1:
            {
                const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
                std::string backGroundSelectedFileNameString;
                if (nullptr != backGroundSelectedFileName) {
                    backGroundSelectedFileNameString = std::string(backGroundSelectedFileName);
                }
                checkBox->loadTextureBackGroundSelected(backGroundSelectedFileNameString,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        const rapidjson::Value& frontCrossDic = DICTOOL->getSubDictionary_json(options, "frontCrossData");
        int frontCrossType = DICTOOL->getIntValue_json(frontCrossDic, "resourceType");
        switch (frontCrossType)
        {
            case 0:
            {
                const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
                std::string frontCrossFileName_tp;
                if (nullptr != frontCrossFileName) {
                    frontCrossFileName_tp = jsonPath + frontCrossFileName;
                }
                checkBox->loadTextureFrontCross(frontCrossFileName_tp);
                break;
            }
            case 1:
            {
                const char* frontCrossFileNamePath = DICTOOL->getStringValue_json(frontCrossDic, "path");
                std::string frontCrossFileName;
                if (nullptr != frontCrossFileNamePath) {
                    frontCrossFileName = std::string(frontCrossFileNamePath);
                }
                checkBox->loadTextureFrontCross(frontCrossFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        const rapidjson::Value& backGroundDisabledDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxDisabledData");
        int backGroundDisabledType = DICTOOL->getIntValue_json(backGroundDisabledDic, "resourceType");
        switch (backGroundDisabledType)
        {
            case 0:
            {
                const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
                std::string backGroundDisabledFileName_tp;
                if (nullptr != backGroundDisabledFileName) {
                    backGroundDisabledFileName_tp = jsonPath + backGroundDisabledFileName;
                }
                checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* backGroundDisabledFileNamePath = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
                std::string backGroundDisabledFileName;
                if (nullptr != backGroundDisabledFileNamePath) {
                    backGroundDisabledFileName = std::string(backGroundDisabledFileNamePath);
                }
                checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        const rapidjson::Value& frontCrossDisabledDic = DICTOOL->getSubDictionary_json(options, "frontCrossDisabledData");
        int frontCrossDisabledType = DICTOOL->getIntValue_json(frontCrossDisabledDic, "resourceType");
        switch (frontCrossDisabledType)
        {
            case 0:
            {
                const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
                std::string frontCrossDisabledFileName_tp;
                if (nullptr != frontCrossDisabledFileName) {
                    frontCrossDisabledFileName_tp = jsonPath + frontCrossDisabledFileName;
                }
                checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* frontCrossDisabledFileNamePath = DICTOOL->getStringValue_json(options, "path");
                std::string frontCrossDisabledFileName;
                if (nullptr != frontCrossDisabledFileNamePath) {
                    frontCrossDisabledFileName = std::string(frontCrossDisabledFileNamePath);
                }
                checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
