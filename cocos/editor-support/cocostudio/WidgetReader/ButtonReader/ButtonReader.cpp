

#include "ButtonReader.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static ButtonReader* instanceButtonReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(ButtonReader)
    
    ButtonReader::ButtonReader()
    {
        
    }
    
    ButtonReader::~ButtonReader()
    {
        
    }
    
    ButtonReader* ButtonReader::getInstance()
    {
        if (!instanceButtonReader)
        {
            instanceButtonReader = new ButtonReader();
        }
        return instanceButtonReader;
    }
    
    void ButtonReader::purge()
    {
        CC_SAFE_DELETE(instanceButtonReader);
    }
    
    void ButtonReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        Button* button = static_cast<Button*>(widget);
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        button->setScale9Enabled(scale9Enable);
        
        const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, "normalData");
        int normalType = DICTOOL->getIntValue_json(normalDic, "resourceType");
        switch (normalType)
        {
            case 0:
            {
                std::string tp_n = jsonPath;
                const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
                const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():nullptr;
                button->loadTextureNormal(normalFileName_tp);
                break;
            }
            case 1:
            {
                const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
                button->loadTextureNormal(normalFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, "pressedData");
        int pressedType = DICTOOL->getIntValue_json(pressedDic, "resourceType");
        switch (pressedType)
        {
            case 0:
            {
                std::string tp_p = jsonPath;
                const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
                const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():nullptr;
                button->loadTexturePressed(pressedFileName_tp);
                break;
            }
            case 1:
            {
                const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
                button->loadTexturePressed(pressedFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, "disabledData");
        int disabledType = DICTOOL->getIntValue_json(disabledDic, "resourceType");
        switch (disabledType)
        {
            case 0:
            {
                std::string tp_d = jsonPath;
                const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
                const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():nullptr;
                button->loadTextureDisabled(disabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
                button->loadTextureDisabled(disabledFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            
            button->setCapInsets(Rect(cx, cy, cw, ch));
            bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
            bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                button->setSize(Size(swf, shf));
            }
        }
        bool tt = DICTOOL->checkObjectExist_json(options, "text");
        if (tt)
        {
            const char* text = DICTOOL->getStringValue_json(options, "text");
            if (text)
            {
                button->setTitleText(text);
            }
        }
        
        bool cr = DICTOOL->checkObjectExist_json(options, "textColorR");
        bool cg = DICTOOL->checkObjectExist_json(options, "textColorG");
        bool cb = DICTOOL->checkObjectExist_json(options, "textColorB");
        int cri = cr?DICTOOL->getIntValue_json(options, "textColorR"):255;
        int cgi = cg?DICTOOL->getIntValue_json(options, "textColorG"):255;
        int cbi = cb?DICTOOL->getIntValue_json(options, "textColorB"):255;
        button->setTitleColor(Color3B(cri,cgi,cbi));
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs)
        {
            button->setTitleFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
        if (fn)
        {
            button->setTitleFontName(DICTOOL->getStringValue_json(options, "fontName"));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
