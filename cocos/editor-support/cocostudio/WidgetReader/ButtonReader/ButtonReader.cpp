

#include "ButtonReader.h"
#include "ui/UIButton.h"
#include "cocostudio/CocoLoader.h"
#include "../../CSParseBinary.pb.h"

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
		/* peterson */
		if (normalType == 1)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(protocolBuffersPath + normalDic.plistfile());			
		}
		/**/
        std::string normalTexturePath = this->getResourcePath(normalDic.path(), (Widget::TextureResType)normalType);		
        button->loadTextureNormal(normalTexturePath, (Widget::TextureResType)normalType);
        
        
        const protocolbuffers::ResourceData& pressedDic = options.presseddata();
        int pressedType = pressedDic.resourcetype();
        /* peterson */
		if (pressedType == 1)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(protocolBuffersPath + pressedDic.plistfile());			
		}
		/**/
        std::string pressedTexturePath = this->getResourcePath(pressedDic.path(), (Widget::TextureResType)pressedType);
        button->loadTexturePressed(pressedTexturePath, (Widget::TextureResType)pressedType);
        
        
        const protocolbuffers::ResourceData& disabledDic = options.disableddata();
        int disabledType = disabledDic.resourcetype();
        /* peterson */
		if (disabledType == 1)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(protocolBuffersPath + disabledDic.plistfile());			
		}
		/**/
        std::string disabledTexturePath = this->getResourcePath(disabledDic.path(), (Widget::TextureResType)disabledType);
        button->loadTextureDisabled(disabledTexturePath, (Widget::TextureResType)disabledType);
        
        if (scale9Enable)
        {
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
        
        
        // other commonly protperties
        WidgetReader::setColorPropsFromProtocolBuffers(widget, nodeTree);
    }
}
