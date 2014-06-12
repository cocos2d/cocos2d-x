

#include "ButtonReader.h"
#include "../../../GUI/UIWidgets/UIButton.h"

NS_CC_EXT_BEGIN

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

void ButtonReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    ui::Button* button = (ui::Button*)widget;
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
            const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():NULL;
            button->loadTextureNormal(normalFileName_tp);
            break;
        }
        case 1:
        {
            const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
            button->loadTextureNormal(normalFileName,ui::UI_TEX_TYPE_PLIST);
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
            const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():NULL;
            button->loadTexturePressed(pressedFileName_tp);
            break;
        }
        case 1:
        {
            const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
            button->loadTexturePressed(pressedFileName,ui::UI_TEX_TYPE_PLIST);
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
            const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():NULL;
            button->loadTextureDisabled(disabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
            button->loadTextureDisabled(disabledFileName,ui::UI_TEX_TYPE_PLIST);
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
        
        button->setCapInsets(CCRectMake(cx, cy, cw, ch));
        bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
        bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
            float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
            button->setSize(CCSizeMake(swf, shf));
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
    
    button->setTitleColor(ccc3(cri,cgi,cbi));
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

void ButtonReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    WidgetReader::setBasicProperties(widget, pCocoLoader, pCocoNode);
    
    ui::Button *button = static_cast<ui::Button*>(widget);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
    
    
    std::map<std::string, int>  buttonMap;
    buttonMap.insert(std::make_pair("scale9Enable", 46));
    buttonMap.insert(std::make_pair("normalData", 43));
    buttonMap.insert(std::make_pair("pressedData", 45));
    buttonMap.insert(std::make_pair("capInsetsHeight", 33));
    buttonMap.insert(std::make_pair("capInsetsWidth", 34));
    buttonMap.insert(std::make_pair("capInsetsX", 35));
    buttonMap.insert(std::make_pair("capInsetsY", 36));
    buttonMap.insert(std::make_pair("disabled", 37));
    buttonMap.insert(std::make_pair("disabledData", 38));
    buttonMap.insert(std::make_pair("fontName", 39));
    buttonMap.insert(std::make_pair("fontSize", 40));
    buttonMap.insert(std::make_pair("fontType", 41));
    buttonMap.insert(std::make_pair("normal", 42));
    buttonMap.insert(std::make_pair("scale9Height", 47));
    buttonMap.insert(std::make_pair("scale9Width", 48));
    buttonMap.insert(std::make_pair("text", 49));
    buttonMap.insert(std::make_pair("textColorB", 50));
    buttonMap.insert(std::make_pair("textColorG", 51));
    buttonMap.insert(std::make_pair("textColorR", 52));
    
    std::map<std::string, int>  resourceMap;
    resourceMap.insert(std::make_pair("path", 0));
    resourceMap.insert(std::make_pair("plistFile", 1));
    resourceMap.insert(std::make_pair("resourceType", 2));
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    std::string value = this->getProperty(buttonMap, stChildArray, "scale9Enable");
    std::string value2;
    bool scale9Enable = valueToBool(value);
    button->setScale9Enabled(scale9Enable);
    
//    value = this->getProperty(buttonMap, stChildArray, "normalData");
    stExpCocoNode *resourceCocosNode = stChildArray[buttonMap["normalData"]].GetChildArray();
    if (resourceCocosNode) {
        value2 = this->getProperty(resourceMap, resourceCocosNode, "resourceType");
        int normalType = valueToInt(value2);
        switch (normalType)
        {
            case 0:
            {
                std::string tp_n = jsonPath;
                value = this->getProperty(resourceMap, resourceCocosNode, "path");
                const char* normalFileName = value.c_str();
                const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?
                tp_n.append(normalFileName).c_str():NULL;
                button->loadTextureNormal(normalFileName_tp);
                break;
            }
            case 1:
            {
                value = this->getProperty(resourceMap, resourceCocosNode, "path");
                const char* normalFileName = value.c_str();
                button->loadTextureNormal(normalFileName,ui::UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }

    }
    
    
    resourceCocosNode = stChildArray[buttonMap["pressedData"]].GetChildArray();
    if (resourceCocosNode) {
        value2 = this->getProperty(resourceMap, resourceCocosNode, "resourceType");
        
        int pressedType = valueToInt(value2);
        switch (pressedType)
        {
            case 0:
            {
                std::string tp_p = jsonPath;
                value = this->getProperty(resourceMap, resourceCocosNode, "path");
                
                const char* pressedFileName = value.c_str();
                const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():NULL;
                button->loadTexturePressed(pressedFileName_tp);
                break;
            }
            case 1:
            {
                value = this->getProperty(resourceMap, resourceCocosNode, "path");
                const char* pressedFileName = value.c_str();
                button->loadTexturePressed(pressedFileName,ui::UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
    }
  
    
    resourceCocosNode = stChildArray[buttonMap["disabledData"]].GetChildArray();
    
    if (resourceCocosNode) {
        value2 = this->getProperty(resourceMap, resourceCocosNode, "resourceType");
        
        int disabledType = valueToInt(value2);
        switch (disabledType)
        {
            case 0:
            {
                std::string tp_d = jsonPath;
                value = this->getProperty(resourceMap, resourceCocosNode, "path");
                const char* disabledFileName = value.c_str();
                const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():NULL;
                button->loadTextureDisabled(disabledFileName_tp);
                break;
            }
            case 1:
            {
                value = this->getProperty(resourceMap, resourceCocosNode, "path");
                const char* disabledFileName = value.c_str();
                button->loadTextureDisabled(disabledFileName,ui::UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
    }
    
    
    
    if (scale9Enable)
    {
        value = this->getProperty(buttonMap, stChildArray, "capInsetsX");
        float cx =valueToFloat(value);
        value = this->getProperty(buttonMap, stChildArray, "capInsetsY");

        float cy = valueToFloat(value);
        value = this->getProperty(buttonMap, stChildArray, "capInsetsWidth");

        float cw = valueToFloat(value);
        value = this->getProperty(buttonMap, stChildArray, "capInsetsHeight");

        float ch = valueToFloat(value);
        
        button->setCapInsets(CCRectMake(cx, cy, cw, ch));
        
        value = this->getProperty(buttonMap, stChildArray, "scale9Width");
        value2 = this->getProperty(buttonMap, stChildArray, "scale9Height");

        if (!value.empty() && !value2.empty())
        {
            float swf = valueToFloat(value);
            float shf = valueToFloat(value2);
            button->setSize(CCSizeMake(swf, shf));
        }
    }
    
    value = this->getProperty(buttonMap, stChildArray, "text");

    bool tt = !value.empty();
    if (tt)
    {
        const char* text = value.c_str();
        if (text)
        {
            button->setTitleText(text);
        }
    }
    
    value = this->getProperty(buttonMap, stChildArray, "textColorR");
    value2 = this->getProperty(buttonMap, stChildArray, "textColorG");
    std::string value3 = this->getProperty(buttonMap, stChildArray, "textColorB");
    
    int cri = !value.empty()?valueToInt(value):255;
    int cgi = !value2.empty()?valueToInt(value2):255;
    int cbi = !value3.empty()?valueToInt(value3):255;
    
    button->setTitleColor(ccc3(cri,cgi,cbi));
    
    value = this->getProperty(buttonMap, stChildArray, "fontSize");

    bool fs = !value.empty();
    if (fs)
    {
        button->setTitleFontSize(valueToInt(value));
    }
    
    value = this->getProperty(buttonMap, stChildArray, "fontName");

    bool fn = !value.empty();
    if (fn)
    {
        button->setTitleFontName(value.c_str());
    }
    
    
    WidgetReader::setColorProperties(widget, pCocoLoader, pCocoNode);
    
}

NS_CC_EXT_END
