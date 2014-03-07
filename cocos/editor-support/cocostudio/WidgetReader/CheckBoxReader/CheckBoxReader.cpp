

#include "CheckBoxReader.h"
#include "gui/UICheckBox.h"

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
                std::string tp_b = jsonPath;
                const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
                const char* backGroundFileName_tp = (backGroundFileName && (strcmp(backGroundFileName, "") != 0))?tp_b.append(backGroundFileName).c_str():nullptr;
                checkBox->loadTextureBackGround(backGroundFileName_tp);
                break;
            }
            case 1:
            {
                const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
                checkBox->loadTextureBackGround(backGroundFileName,UI_TEX_TYPE_PLIST);
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
                std::string tp_bs = jsonPath;
                const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
                const char* backGroundSelectedFileName_tp = (backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))?tp_bs.append(backGroundSelectedFileName).c_str():nullptr;
                checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName_tp);
                break;
            }
            case 1:
            {
                const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
                checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName,UI_TEX_TYPE_PLIST);
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
                std::string tp_c = jsonPath;
                const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
                const char* frontCrossFileName_tp = (frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))?tp_c.append(frontCrossFileName).c_str():nullptr;
                checkBox->loadTextureFrontCross(frontCrossFileName_tp);
                break;
            }
            case 1:
            {
                const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
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
                std::string tp_bd = jsonPath;
                const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
                const char* backGroundDisabledFileName_tp = (backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))?tp_bd.append(backGroundDisabledFileName).c_str():nullptr;
                checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
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
                std::string tp_cd = jsonPath;
                const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
                const char* frontCrossDisabledFileName_tp = (frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))?tp_cd.append(frontCrossDisabledFileName).c_str():nullptr;
                checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
                checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
