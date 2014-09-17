

#include "TextFieldReader.h"
#include "ui/UITextField.h"
#include "cocostudio/CocoLoader.h"

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
}
