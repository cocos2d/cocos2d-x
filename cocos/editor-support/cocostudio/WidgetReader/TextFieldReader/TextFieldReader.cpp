

#include "TextFieldReader.h"
#include "ui/UITextField.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static TextFieldReader* instanceTextFieldReader = NULL;
    
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
            instanceTextFieldReader = new TextFieldReader();
        }
        return instanceTextFieldReader;
    }
    
    void TextFieldReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        TextField* textField = static_cast<TextField*>(widget);
        bool ph = DICTOOL->checkObjectExist_json(options, "placeHolder");
        if (ph)
        {
            textField->setPlaceHolder(DICTOOL->getStringValue_json(options, "placeHolder"));
        }
        textField->setText(DICTOOL->getStringValue_json(options, "text"));
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs)
        {
            textField->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
        if (fn)
        {
            textField->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
        }
        bool tsw = DICTOOL->checkObjectExist_json(options, "touchSizeWidth");
        bool tsh = DICTOOL->checkObjectExist_json(options, "touchSizeHeight");
        if (tsw && tsh)
        {
            textField->setTouchSize(Size(DICTOOL->getFloatValue_json(options, "touchSizeWidth"), DICTOOL->getFloatValue_json(options,"touchSizeHeight")));
        }
        
        float dw = DICTOOL->getFloatValue_json(options, "width");
        float dh = DICTOOL->getFloatValue_json(options, "height");
        if (dw > 0.0f || dh > 0.0f)
        {
            //textField->setSize(Size(dw, dh));
        }
        bool maxLengthEnable = DICTOOL->getBooleanValue_json(options, "maxLengthEnable");
        textField->setMaxLengthEnabled(maxLengthEnable);
        
        if (maxLengthEnable)
        {
            int maxLength = DICTOOL->getIntValue_json(options, "maxLength");
            textField->setMaxLength(maxLength);
        }
        bool passwordEnable = DICTOOL->getBooleanValue_json(options, "passwordEnable");
        textField->setPasswordEnabled(passwordEnable);
        if (passwordEnable)
        {
            textField->setPasswordStyleText(DICTOOL->getStringValue_json(options, "passwordStyleText"));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
