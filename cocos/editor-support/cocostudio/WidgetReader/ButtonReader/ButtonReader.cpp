

#include "ButtonReader.h"
#include "ui/UIButton.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    
    static const char* P_Scale9Enable = "scale9Enable";
    static const char* P_NormalData = "normalData";
    static const char* P_PressedData = "pressedData";
    static const char* P_DisabledData = "disabledData";
    static const char* P_Text = "text";
    static const char* P_CapInsetsX = "capInsetsX";
    static const char* P_CapInsetsY = "capInsetsY";
    static const char* P_CapInsetsWidth = "capInsetsWidth";
    static const char* P_CapInsetsHeight = "capInsetsHeight";
    static const char* P_Scale9Width = "scale9Width";
    static const char* P_Scale9Height = "scale9Height";
    static const char* P_TextColorR = "textColorR";
    static const char* P_TextColorG = "textColorG";
    static const char* P_TextColorB = "textColorB";
    static const char* P_FontSize = "fontSize";
    static const char* P_FontName = "fontName";
    
   
    
    static ButtonReader* instanceButtonReader = nullptr;
    
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
    
    void ButtonReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        Button *button = static_cast<Button*>(widget);
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray();
        
        this->beginSetBasicProperties(widget);
        
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        int cri = 255, cgi = 255, cbi = 255;
        float scale9Width = 0.0f, scale9Height = 0.0f;
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue();
//            CCLOG("Button: key = %s, value = %d", key.c_str(), i);

            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
           
            else if (key == P_Scale9Enable) {
                button->setScale9Enabled(valueToBool(value));
            }
            else if (key == P_NormalData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTextureNormal(backgroundValue, imageFileNameType);
                
            }
            else if (key == P_PressedData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTexturePressed(backgroundValue, imageFileNameType);
                
            }
            else if (key == P_DisabledData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTextureDisabled(backgroundValue, imageFileNameType);
                
            }else if (key == P_Text){
                button->setTitleText(value);
            }
            else if(key == P_CapInsetsX){
                capsx = valueToFloat(value);
            }else if(key == P_CapInsetsY){
                capsy = valueToFloat(value);
            }else if(key == P_CapInsetsWidth){
                capsWidth = valueToFloat(value);
            }else if(key == P_CapInsetsHeight){
                capsHeight = valueToFloat(value);
            }else if(key == P_Scale9Width){
                scale9Width = valueToFloat(value);
            }else if(key == P_Scale9Height){
                scale9Height = valueToFloat(value);
            }else if(key == P_TextColorR){
                cri = valueToInt(value);
            }else if(key == P_TextColorG){
                cgi = valueToInt(value);
            }else if(key == P_TextColorB){
                cbi = valueToInt(value);
            }else if(key == P_FontSize){
                button->setTitleFontSize(valueToFloat(value));
            }else if(key == P_FontName){
                button->setTitleFontName(value);
            }
            
        } //end of for loop
        
        this->endSetBasicProperties(widget);

        if (button->isScale9Enabled()) {
            button->setCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
            button->setSize(Size(scale9Width, scale9Height));
        }
        
        button->setTitleColor(Color3B(cri, cgi, cbi));
        

    }
    
    void ButtonReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        Button* button = static_cast<Button*>(widget);
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, P_Scale9Enable);
        button->setScale9Enabled(scale9Enable);
        
        
        const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, P_NormalData);
        int normalType = DICTOOL->getIntValue_json(normalDic, P_ResourceType);
        std::string normalTexturePath = this->getResourcePath(normalDic, P_Path, (Widget::TextureResType)normalType);
        button->loadTextureNormal(normalTexturePath, (Widget::TextureResType)normalType);
        
        
        const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, P_PressedData);
        int pressedType = DICTOOL->getIntValue_json(pressedDic, P_ResourceType);
        
        std::string pressedTexturePath = this->getResourcePath(pressedDic, P_Path, (Widget::TextureResType)pressedType);
        button->loadTexturePressed(pressedTexturePath, (Widget::TextureResType)pressedType);
        
        
        const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, P_DisabledData);
        int disabledType = DICTOOL->getIntValue_json(disabledDic, P_ResourceType);
        
        std::string disabledTexturePath = this->getResourcePath(disabledDic, P_Path, (Widget::TextureResType)disabledType);
        button->loadTextureDisabled(disabledTexturePath, (Widget::TextureResType)disabledType);
       
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, P_CapInsetsX);
            float cy = DICTOOL->getFloatValue_json(options, P_CapInsetsY);
            float cw = DICTOOL->getFloatValue_json(options, P_CapInsetsWidth);
            float ch = DICTOOL->getFloatValue_json(options, P_CapInsetsHeight);
            
            button->setCapInsets(Rect(cx, cy, cw, ch));
            bool sw = DICTOOL->checkObjectExist_json(options, P_Scale9Width);
            bool sh = DICTOOL->checkObjectExist_json(options, P_Scale9Height);
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, P_Scale9Width);
                float shf = DICTOOL->getFloatValue_json(options, P_Scale9Height);
                button->setSize(Size(swf, shf));
            }
        }
        bool tt = DICTOOL->checkObjectExist_json(options, P_Text);
        if (tt)
        {
            const char* text = DICTOOL->getStringValue_json(options, P_Text);
            if (text)
            {
                button->setTitleText(text);
            }
        }
        
        bool cr = DICTOOL->checkObjectExist_json(options, P_TextColorR);
        bool cg = DICTOOL->checkObjectExist_json(options, P_TextColorG);
        bool cb = DICTOOL->checkObjectExist_json(options, P_TextColorB);
        int cri = cr?DICTOOL->getIntValue_json(options, P_TextColorR):255;
        int cgi = cg?DICTOOL->getIntValue_json(options, P_TextColorG):255;
        int cbi = cb?DICTOOL->getIntValue_json(options, P_TextColorB):255;
        button->setTitleColor(Color3B(cri,cgi,cbi));
        bool fs = DICTOOL->checkObjectExist_json(options, P_FontSize);
        if (fs)
        {
            button->setTitleFontSize(DICTOOL->getIntValue_json(options, P_FontSize));
        }
        bool fn = DICTOOL->checkObjectExist_json(options, P_FontName);
        if (fn)
        {
            button->setTitleFontName(DICTOOL->getStringValue_json(options, P_FontName));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
