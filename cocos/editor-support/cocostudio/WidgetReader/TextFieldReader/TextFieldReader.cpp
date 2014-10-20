

#include "TextFieldReader.h"
#include "ui/UITextField.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static TextFieldReader* instanceTextFieldReader = nullptr;
    
    static const char* P_PlaceHolder = "placeHolder";
    static const char* P_Text = "text";
    static const char* P_FontSize = "fontSize";
    static const char* P_FontName = "fontName";
    static const char* P_TouchSizeWidth = "touchSizeWidth";
    static const char* P_TouchSizeHeight = "touchSizeHeight";
    static const char* P_MaxLengthEnable = "maxLengthEnable";
    static const char* P_MaxLength = "maxLength";
    static const char* P_PasswordEnable = "passwordEnable";
    static const char* P_PasswordStyleText = "passwordStyleText";
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(TextFieldReader)
    
    TextFieldReader::TextFieldReader()
    {
        
    }
    
    TextFieldReader::~TextFieldReader()
    {
        
    }
    
    TextFieldReader* TextFieldReader::getInstance()
    {
        if (!instanceTextFieldReader)
        {
            instanceTextFieldReader = new (std::nothrow) TextFieldReader();
        }
        return instanceTextFieldReader;
    }
    
    void TextFieldReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode* cocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        TextField* textField = static_cast<TextField*>(widget);
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if(key == P_PlaceHolder){
                textField->setPlaceHolder(value);
            }else if(key == P_Text){
                textField->setString(value);
            }else if(key == P_FontSize){
                textField->setFontSize(valueToInt(value));
            }else if(key == P_FontName){
                textField->setFontName(value);
            }else if(key == P_TouchSizeWidth){
                textField->setTouchSize(Size(valueToFloat(value), textField->getTouchSize().height));
            }else if(key == P_TouchSizeHeight){
                textField->setTouchSize(Size(textField->getTouchSize().width,  valueToFloat(value)));
            }else if (key == P_MaxLengthEnable){
                textField->setMaxLengthEnabled(valueToBool(value));
            }else if(key == P_MaxLength){
                textField->setMaxLength(valueToInt(value));
            }else if(key == P_PasswordEnable){
                textField->setPasswordEnabled(valueToBool(value));
            }else if(key == P_PasswordStyleText){
                textField->setPasswordStyleText(value.c_str());
            }
        } //end of for loop
        this->endSetBasicProperties(widget);
    }
    
    void TextFieldReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        TextField* textField = static_cast<TextField*>(widget);
        bool ph = DICTOOL->checkObjectExist_json(options, P_PlaceHolder);
        if (ph)
        {
            textField->setPlaceHolder(DICTOOL->getStringValue_json(options, P_PlaceHolder,"input words here"));
        }
        textField->setString(DICTOOL->getStringValue_json(options, P_Text,"Text Tield"));
       
        textField->setFontSize(DICTOOL->getIntValue_json(options, P_FontSize,20));
    
       
        textField->setFontName(DICTOOL->getStringValue_json(options, P_FontName,"微软雅黑"));
        
        bool tsw = DICTOOL->checkObjectExist_json(options, P_TouchSizeWidth);
        bool tsh = DICTOOL->checkObjectExist_json(options, P_TouchSizeHeight);
        if (tsw && tsh)
        {
            textField->setTouchSize(Size(DICTOOL->getFloatValue_json(options, P_TouchSizeWidth), DICTOOL->getFloatValue_json(options,P_TouchSizeHeight)));
        }
        
//        float dw = DICTOOL->getFloatValue_json(options, "width");
//        float dh = DICTOOL->getFloatValue_json(options, "height");
//        if (dw > 0.0f || dh > 0.0f)
//        {
//            //textField->setSize(Size(dw, dh));
//        }
        bool maxLengthEnable = DICTOOL->getBooleanValue_json(options, P_MaxLengthEnable);
        textField->setMaxLengthEnabled(maxLengthEnable);
        
        if (maxLengthEnable)
        {
            int maxLength = DICTOOL->getIntValue_json(options, P_MaxLength,10);
            textField->setMaxLength(maxLength);
        }
        bool passwordEnable = DICTOOL->getBooleanValue_json(options, P_PasswordEnable);
        textField->setPasswordEnabled(passwordEnable);
        if (passwordEnable)
        {
            textField->setPasswordStyleText(DICTOOL->getStringValue_json(options, P_PasswordStyleText,"*"));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
    
    void TextFieldReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        TextField* textField = static_cast<TextField*>(widget);
        const protocolbuffers::TextFieldOptions& options = nodeTree.textfieldoptions();
        
        std::string protocolBuffersPath = GUIReader::getInstance()->getFilePath();
        
		bool IsCustomSize = options.iscustomsize();
		widget->ignoreContentAdaptWithSize(!IsCustomSize);
        
        if (IsCustomSize)
        {
            const protocolbuffers::WidgetOptions& widgetOptions = nodeTree.widgetoptions();
            textField->setContentSize(Size(widgetOptions.width(), widgetOptions.height()));
        }

        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        WidgetReader::setAnchorPointForWidget(widget, nodeTree);
        
        textField->setUnifySizeEnabled(false);
        
        bool ph = options.has_placeholder();
        if (ph)
        {
            std::string placeholder = options.has_placeholder() ? options.placeholder() : "inputs words here";
            textField->setPlaceHolder(placeholder);
        }
        std::string text = options.has_text() ? options.text() : "Text Field";
        textField->setString(text);
        
        int fontSize = options.has_fontsize() ? options.fontsize() : 20;
        textField->setFontSize(fontSize);
        
        
        std::string fontName = options.has_fontname() ? options.fontname() : "微软雅黑";
        textField->setFontName(fontName);
        

        bool maxLengthEnable = options.maxlengthenable();
        textField->setMaxLengthEnabled(maxLengthEnable);
        
        if (maxLengthEnable)
        {
            int maxLength = options.has_maxlength() ? options.maxlength() : 10;
            textField->setMaxLength(maxLength);
        }
        bool passwordEnable = options.passwordenable();
        textField->setPasswordEnabled(passwordEnable);
        if (passwordEnable)
        {
            std::string passwordStyleText = options.has_passwordstyletext() ? options.passwordstyletext() : "*";
            textField->setPasswordStyleText(passwordStyleText.c_str());
        }
        
		if (options.has_fontresource())
		{
			const protocolbuffers::ResourceData& resourceData = options.fontresource();
		    textField->setFontName(protocolBuffersPath + resourceData.path());
		}
        
        // other commonly protperties
        WidgetReader::setColorPropsFromProtocolBuffers(widget, nodeTree);

    }
    
    void TextFieldReader::setPropsFromXML(cocos2d::ui::Widget *widget, const tinyxml2::XMLElement *objectData)
    {
        WidgetReader::setPropsFromXML(widget, objectData);
        
        TextField* textField = static_cast<TextField*>(widget);
        
        std::string xmlPath = GUIReader::getInstance()->getFilePath();
        
        bool isCustomSize = false;
        float width = 0.0f, height = 0.0f;
        
        int opacity = 255;
        
        textField->setUnifySizeEnabled(false);
        
        textField->setFontName("微软雅黑");
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "PlaceHolderText")
            {
                textField->setPlaceHolder(value);
            }
            else if (name == "LabelText")
            {
                textField->setString(value);
            }
            else if (name == "FontSize")
            {
                textField->setFontSize(atoi(value.c_str()));
            }
            else if (name == "FontName")
            {
                textField->setFontName(value);
            }
            else if (name == "MaxLengthEnable")
            {
                textField->setMaxLengthEnabled((value == "True") ? true : false);
            }
            else if (name == "MaxLengthText")
            {
                textField->setMaxLength(atoi(value.c_str()));
            }
            else if (name == "PasswordEnable")
            {
                textField->setPasswordEnabled((value == "True") ? true : false);
            }
            else if (name == "PasswordStyleText")
            {
                textField->setPasswordStyleText(value.c_str());
            }
            else if (name == "IsCustomSize")
            {
                isCustomSize = ((value == "True") ? true : false);
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
                        textField->setFontName(xmlPath + path);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        if (isCustomSize)
        {
            textField->ignoreContentAdaptWithSize(!isCustomSize);
            textField->setContentSize(Size(width, height));
        }
        
        textField->setOpacity(opacity);
    }
    
}
