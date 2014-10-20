

#include "TextReader.h"
#include "ui/UIText.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static const char* P_TouchScaleEnable = "touchScaleEnable";
    static const char* P_Text = "text";
    static const char* P_FontSize = "fontSize";
    static const char* P_FontName = "fontName";
    static const char* P_AreaWidth = "areaWidth";
    static const char* P_AreaHeight = "areaHeight";
    static const char* P_HAlignment = "hAlignment";
    static const char* P_VAlignment = "vAlignment";
    
    static TextReader* instanceTextReader = nullptr;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(TextReader)
    
    TextReader::TextReader()
    {
        
    }
    
    TextReader::~TextReader()
    {
        
    }
    
    TextReader* TextReader::getInstance()
    {
        if (!instanceTextReader)
        {
            instanceTextReader = new (std::nothrow) TextReader();
        }
        return instanceTextReader;
    }
    
    void TextReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        Text* label = static_cast<Text*>(widget);
        
        std::string binaryFilePath = GUIReader::getInstance()->getFilePath();

        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER

            else if (key == P_TouchScaleEnable) {
                label->setTouchScaleChangeEnabled(valueToBool(value));
            }
            
            else if(key == P_Text){
                label->setString(value);
            }else if(key == P_FontSize){
                label->setFontSize(valueToInt(value));
            }else if(key == P_FontName){
                std::string fontFilePath;
                fontFilePath = binaryFilePath.append(value);
                if (FileUtils::getInstance()->isFileExist(fontFilePath)) {
                    label->setFontName(fontFilePath);
                }else{
                    label->setFontName(value);
                }
            }else if(key == P_AreaWidth){
                label->setTextAreaSize(Size(valueToFloat(value), label->getTextAreaSize().height));
            }else if(key == P_AreaHeight){
                label->setTextAreaSize(Size(label->getTextAreaSize().width, valueToFloat(value)));
            }else if(key == P_HAlignment){
                label->setTextHorizontalAlignment((TextHAlignment)valueToInt(value));
            }else if(key == P_VAlignment){
                label->setTextVerticalAlignment((TextVAlignment)valueToInt(value));
            }
            
        } //end of for loop
        this->endSetBasicProperties(widget);
    }
    
    void TextReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        Text* label = static_cast<Text*>(widget);
        bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, P_TouchScaleEnable);
        label->setTouchScaleChangeEnabled(touchScaleChangeAble);
        const char* text = DICTOOL->getStringValue_json(options, P_Text,"Text Label");
        label->setString(text);
      
        label->setFontSize(DICTOOL->getIntValue_json(options, P_FontSize,20));
       
        std::string fontName = DICTOOL->getStringValue_json(options, P_FontName, "微软雅黑");
        
        std::string fontFilePath = jsonPath.append(fontName);
		if (FileUtils::getInstance()->isFileExist(fontFilePath))
		{
			label->setFontName(fontFilePath);
		}
		else{
			label->setFontName(fontName);
		}
        
        bool aw = DICTOOL->checkObjectExist_json(options, P_AreaWidth);
        bool ah = DICTOOL->checkObjectExist_json(options, P_AreaHeight);
        if (aw && ah)
        {
            Size size = Size(DICTOOL->getFloatValue_json(options, P_AreaWidth),DICTOOL->getFloatValue_json(options,P_AreaHeight));
            label->setTextAreaSize(size);
        }
        bool ha = DICTOOL->checkObjectExist_json(options, P_HAlignment);
        if (ha)
        {
            label->setTextHorizontalAlignment((TextHAlignment)DICTOOL->getIntValue_json(options, P_HAlignment));
        }
        bool va = DICTOOL->checkObjectExist_json(options, P_VAlignment);
        if (va)
        {
            label->setTextVerticalAlignment((TextVAlignment)DICTOOL->getIntValue_json(options, P_VAlignment));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
    
    void TextReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
		Text* label = static_cast<Text*>(widget);
        const protocolbuffers::TextOptions& options = nodeTree.textoptions();
        
		bool IsCustomSize = options.iscustomsize();
		label->ignoreContentAdaptWithSize(!IsCustomSize);

        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        
        label->setUnifySizeEnabled(false);
        
        std::string protocolBuffersPath = GUIReader::getInstance()->getFilePath();
        
        bool touchScaleChangeAble = options.touchscaleenable();
        label->setTouchScaleChangeEnabled(touchScaleChangeAble);
        const char* text = options.has_text() ? options.text().c_str() : "Text Label";
        label->setString(text);
        
        int fontSize = options.has_fontsize() ? options.fontsize() : 20;
        label->setFontSize(fontSize);
        
        std::string fontName = options.has_fontname() ? options.fontname() : "微软雅黑";
        
        std::string fontFilePath = protocolBuffersPath.append(fontName);
		if (FileUtils::getInstance()->isFileExist(fontFilePath))
		{
			label->setFontName(fontFilePath);
		}
		else{
			label->setFontName(fontName);
		}
        
        bool aw = options.has_areawidth();
        bool ah = options.has_areaheight();
        if (aw && ah)
        {
            Size size = Size(options.areawidth(), options.areaheight());
            label->setTextAreaSize(size);
        }
        bool ha = options.has_halignment();
        if (ha)
        {
            label->setTextHorizontalAlignment((TextHAlignment)options.halignment());
        }
        bool va = options.has_valignment();
        if (va)
        {
            label->setTextVerticalAlignment((TextVAlignment)options.valignment());
        }

		if (options.has_fontresource())
		{
			const protocolbuffers::ResourceData& resourceData = options.fontresource();
		    label->setFontName(protocolBuffersPath + resourceData.path());
		}
        


        // other commonly protperties
        WidgetReader::setColorPropsFromProtocolBuffers(widget, nodeTree);
    }
    
    void TextReader::setPropsFromXML(cocos2d::ui::Widget *widget, const tinyxml2::XMLElement *objectData)
    {
        WidgetReader::setPropsFromXML(widget, objectData);
        
        Text* label = static_cast<Text*>(widget);
        
        std::string xmlPath = GUIReader::getInstance()->getFilePath();
        
        float areaWidth = 0.0f, areaHeight = 0.0f;
        int halignment = 0, valignment = 0;
        
        int opacity = 255;
        
        label->setUnifySizeEnabled(false);
        
        label->setFontName("微软雅黑");
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "TouchScaleChangeAble")
            {
                label->setTouchScaleChangeEnabled((value == "True") ? true : false);
            }
            else if (name == "LabelText")
            {
                label->setString(value);
            }
            else if (name == "FontSize")
            {
                label->setFontSize(atoi(value.c_str()));
            }
            else if (name == "FontName")
            {
                label->setFontName(value);
            }
            else if (name == "AreaWidth")
            {
                areaWidth = atoi(value.c_str());
            }
            else if (name == "AreaHeight")
            {
                areaHeight = atoi(value.c_str());
            }
            else if (name == "HorizontalAlignmentType")
            {
                if (value == "HT_Left")
                {
                    halignment = 0;
                }
                else if (value == "HT_Center")
                {
                    halignment = 1;
                }
                else if (value == "HT_Right")
                {
                    halignment = 2;
                }
            }
            else if (name == "VerticalAlignmentType")
            {
                if (value == "VT_Top")
                {
                    valignment = 0;
                }
                else if (value == "VT_Center")
                {
                    valignment = 1;
                }
                else if (value == "VT_Bottom")
                {
                    valignment = 2;
                }
            }
            else if (name == "Alpha")
            {
                opacity = atoi(value.c_str());
            }
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "Size")
            {
                attribute = child->FirstAttribute();
                float width = 0.0f, height = 0.0f;
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "X")
                    {
                        width = atof(value.c_str());
                    }
                    else if (name == "Y")
                    {
                        height = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
                
                label->ignoreContentAdaptWithSize(false);
                label->setContentSize(Size(width, height));
            }
            else if (name == "FontResource")
            {
                attribute = child->FirstAttribute();
                int resourceType = 0;
                std::string path = "", plistFile = "";
                
                while (attribute)
                {
                    name = attribute->Name();
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
                        label->setFontName(xmlPath + path);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        if (areaWidth != 0 || areaHeight != 0)
        {
            label->setTextAreaSize(Size(areaWidth, areaHeight));
        }
        
        label->setTextHorizontalAlignment((TextHAlignment)halignment);
        label->setTextVerticalAlignment((TextVAlignment)valignment);
        
        label->setOpacity(opacity);
    }
    
}
