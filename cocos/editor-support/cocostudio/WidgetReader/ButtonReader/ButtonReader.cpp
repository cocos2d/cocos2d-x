

#include "ButtonReader.h"
#include "ui/UIButton.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"

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
            instanceButtonReader = new (std::nothrow) ButtonReader();
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
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        this->beginSetBasicProperties(widget);
        
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        int cri = 255, cgi = 255, cbi = 255;
        float scale9Width = 0.0f, scale9Height = 0.0f;
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
//            CCLOG("Button: key = %s, value = %d", key.c_str(), i);

            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
           
            else if (key == P_Scale9Enable) {
                button->setScale9Enabled(valueToBool(value));
            }
            else if (key == P_NormalData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTextureNormal(backgroundValue, imageFileNameType);
                
            }
            else if (key == P_PressedData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTexturePressed(backgroundValue, imageFileNameType);
                
            }
            else if (key == P_DisabledData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
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
            button->setContentSize(Size(scale9Width, scale9Height));
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
                button->setContentSize(Size(swf, shf));
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
        
     
        int cri = DICTOOL->getIntValue_json(options, P_TextColorR,255);
        int cgi = DICTOOL->getIntValue_json(options, P_TextColorG,255);
        int cbi = DICTOOL->getIntValue_json(options, P_TextColorB,255);
        button->setTitleColor(Color3B(cri,cgi,cbi));
  
        
        button->setTitleFontSize(DICTOOL->getIntValue_json(options, P_FontSize,14));
        

        button->setTitleFontName(DICTOOL->getStringValue_json(options, P_FontName,"微软雅黑"));
        
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
    
    void ButtonReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        
        Button* button = static_cast<Button*>(widget);
        const protocolbuffers::ButtonOptions& options = nodeTree.buttonoptions();
        
        std::string protocolBuffersPath = GUIReader::getInstance()->getFilePath();;
        
        bool scale9Enable = options.scale9enable();
        button->setScale9Enabled(scale9Enable);
        
        
		const protocolbuffers::ResourceData& normalDic = options.normaldata();
        int normalType = normalDic.resourcetype();
		if (normalType == 1)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(protocolBuffersPath + normalDic.plistfile());			
		}
        std::string normalTexturePath = this->getResourcePath(normalDic.path(), (Widget::TextureResType)normalType);		
        button->loadTextureNormal(normalTexturePath, (Widget::TextureResType)normalType);
        
        
        const protocolbuffers::ResourceData& pressedDic = options.presseddata();
        int pressedType = pressedDic.resourcetype();
		if (pressedType == 1)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(protocolBuffersPath + pressedDic.plistfile());			
		}
        std::string pressedTexturePath = this->getResourcePath(pressedDic.path(), (Widget::TextureResType)pressedType);
        button->loadTexturePressed(pressedTexturePath, (Widget::TextureResType)pressedType);
        
        
        const protocolbuffers::ResourceData& disabledDic = options.disableddata();
        int disabledType = disabledDic.resourcetype();
		if (disabledType == 1)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(protocolBuffersPath + disabledDic.plistfile());			
		}
        std::string disabledTexturePath = this->getResourcePath(disabledDic.path(), (Widget::TextureResType)disabledType);
        button->loadTextureDisabled(disabledTexturePath, (Widget::TextureResType)disabledType);
        
        if (scale9Enable)
        {
            button->setUnifySizeEnabled(false);
            button->ignoreContentAdaptWithSize(false);
            
            float cx = options.capinsetsx();
            float cy = options.capinsetsy();
            float cw = options.capinsetswidth();
            float ch = options.capinsetsheight();
            
            button->setCapInsets(Rect(cx, cy, cw, ch));
            bool sw = options.has_scale9width();
            bool sh = options.has_scale9height();
            if (sw && sh)
            {
                float swf = options.scale9width();
                float shf = options.scale9height();
                button->setContentSize(Size(swf, shf));
            }
        }
        bool tt = options.has_text();
        if (tt)
        {
            const char* text = options.text().c_str();
            if (text)
            {
                button->setTitleText(text);
            }
        }
        
        
        int cri = options.has_textcolorr() ? options.textcolorr() : 255;
        int cgi = options.has_textcolorg() ? options.textcolorg() : 255;
        int cbi = options.has_textcolorb() ? options.textcolorb() : 255;
        button->setTitleColor(Color3B(cri,cgi,cbi));
        
        
        int fontSize = options.has_fontsize() ? options.fontsize() : 14;
        button->setTitleFontSize(fontSize);
        
		bool displaystate = true;
		if(options.has_displaystate())
		{
			displaystate = options.displaystate();
		}
		button->setBright(displaystate);

        const char* fontName = options.has_fontname() ? options.fontname().c_str() : "微软雅黑";
        button->setTitleFontName(fontName);
        
        if (options.has_fontresource())
		{
			const protocolbuffers::ResourceData& resourceData = options.fontresource();
		    button->setTitleFontName(protocolBuffersPath + resourceData.path());
		}
        
        const protocolbuffers::WidgetOptions& widgetOption = nodeTree.widgetoptions();
        button->setColor(Color3B(widgetOption.colorr(), widgetOption.colorg(), widgetOption.colorb()));
        button->setOpacity(widgetOption.has_alpha() ? widgetOption.alpha() : 255);
        
        
        // other commonly protperties
        WidgetReader::setColorPropsFromProtocolBuffers(widget, nodeTree);
    }
    
    void ButtonReader::setPropsFromXML(cocos2d::ui::Widget *widget, const tinyxml2::XMLElement *objectData)
    {
        WidgetReader::setPropsFromXML(widget, objectData);
        
        Button* button = static_cast<Button*>(widget);
        
        std::string xmlPath = GUIReader::getInstance()->getFilePath();
        
        bool scale9Enabled = false;
        float cx = 0.0f, cy = 0.0f, cw = 0.0f, ch = 0.0f;
        float swf = 0.0f, shf = 0.0f;
        std::string text = "";
        std::string fontName = "微软雅黑";
        int fontSize = 0;
        int title_color_red = 255, title_color_green = 255, title_color_blue = 255;
        int cri = 255, cgi = 255, cbi = 255;
        int opacity = 255;
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "Scale9Enable")
            {
                if (value == "True")
                {
                    scale9Enabled = true;
                }
            }
            else if (name == "Scale9OriginX")
            {
                cx = atof(value.c_str());
            }
            else if (name == "Scale9OriginY")
            {
                cy = atof(value.c_str());
            }
            else if (name == "Scale9Width")
            {
                cw = atof(value.c_str());
            }
            else if (name == "Scale9Height")
            {
                ch = atof(value.c_str());
            }
            else if (name == "ButtonText")
            {
                text = value;
            }
            else if (name == "FontSize")
            {
                fontSize = atoi(value.c_str());
            }
            else if (name == "FontName")
            {
                fontName = value;
            }
            else if (name == "Alpha")
            {
                opacity = atoi(value.c_str());
            }
            else if (name == "DisplayState")
            {
                button->setBright((value == "True") ? true : false);
            }
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "Size" && scale9Enabled)
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    std::string name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "X")
                    {
                        swf = atof(value.c_str());
                    }
                    else if (name == "Y")
                    {
                        shf = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "CColor")
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                while (attribute)
                {
                    std::string name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        cri = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        cgi = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        cbi = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "TextColor")
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                while (attribute)
                {
                    std::string name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        title_color_red = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        title_color_green = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        title_color_blue = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "DisabledFileData")
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                int resourceType = 0;
                std::string path = "", plistFile = "";
                
                while (attribute)
                {
                    std::string name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        path = value;
                    }
                    else if (name == "Type")
                    {
                        resourceType = (value == "Normal" || value == "Default" || value == "MarkedSubImage") ? 0 : 1;
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                switch (resourceType)
                {
                    case 0:
                    {
                        button->loadTextureDisabled(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        button->loadTextureDisabled(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            else if (name == "PressedFileData")
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                int resourceType = 0;
                std::string path = "", plistFile = "";
                
                while (attribute)
                {
                    std::string name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        path = value;
                    }
                    else if (name == "Type")
                    {
                        resourceType = (value == "Normal" || value == "Default" || value == "MarkedSubImage") ? 0 : 1;
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                switch (resourceType)
                {
                    case 0:
                    {
                        button->loadTexturePressed(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        button->loadTexturePressed(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            else if (name == "NormalFileData")
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                int resourceType = 0;
                std::string path = "", plistFile = "";
                
                while (attribute)
                {
                    std::string name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        path = value;
                    }
                    else if (name == "Type")
                    {
                        resourceType = (value == "Normal" || value == "Default" || value == "MarkedSubImage") ? 0 : 1;
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                switch (resourceType)
                {
                    case 0:
                    {
                        button->loadTextureNormal(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        button->loadTextureNormal(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            else if (name == "FontResource")
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                int resourceType = 0;
                std::string path = "", plistFile = "";
                
                while (attribute)
                {
                    std::string name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        path = value;
                    }
                    else if (name == "Type")
                    {
                        resourceType = (value == "Normal" || value == "Default") ? 0 : 1;
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                switch (resourceType)
                {
                    case 0:
                    {
                        fontName = xmlPath + path;
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        button->setScale9Enabled(scale9Enabled);
        
        
        if (scale9Enabled)
        {
            button->setUnifySizeEnabled(false);
            button->ignoreContentAdaptWithSize(false);
            
            button->setCapInsets(Rect(cx, cy, cw, ch));
            button->setContentSize(Size(swf, shf));
        }
        
        button->setTitleText(text);
        button->setTitleColor(Color3B(title_color_red, title_color_green, title_color_blue));
        button->setTitleFontSize(fontSize);
        button->setTitleFontName(fontName);
        
        button->setColor(Color3B(cri,cgi,cbi));
        button->setOpacity(opacity);
    }
}
