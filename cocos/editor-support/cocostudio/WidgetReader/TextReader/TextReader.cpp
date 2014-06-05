

#include "TextReader.h"
#include "ui/UIText.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static TextReader* instanceTextReader = NULL;
    
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
            instanceTextReader = new TextReader();
        }
        return instanceTextReader;
    }
    
    void TextReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
        
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        
        Text* label = static_cast<Text*>(widget);
    
        
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
            
            if (key == "touchScaleEnable") {
                label->setTouchScaleChangeEnabled(valueToBool(value));
            }
            
            else if(key == "text"){
                label->setString(value);
            }else if(key == "fontSize"){
                label->setFontSize(valueToInt(value));
            }else if(key == "fontName"){
                label->setFontName(value);
            }else if(key == "areaWidth"){
                label->setTextAreaSize(Size(valueToFloat(value), label->getTextAreaSize().height));
            }else if(key == "areaHeight"){
                label->setTextAreaSize(Size(label->getTextAreaSize().width, valueToFloat(value)));
            }else if(key == "hAlignment"){
                label->setTextHorizontalAlignment((TextHAlignment)valueToInt(value));
            }else if(key == "vAlignment"){
                label->setTextVerticalAlignment((TextVAlignment)valueToInt(value));
            }
            
        } //end of for loop
    }
    
    void TextReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        Text* label = static_cast<Text*>(widget);
        bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, "touchScaleEnable");
        label->setTouchScaleChangeEnabled(touchScaleChangeAble);
        const char* text = DICTOOL->getStringValue_json(options, "text");
        label->setString(text);
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs)
        {
            label->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
        if (fn)
        {
            label->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
        }
        bool aw = DICTOOL->checkObjectExist_json(options, "areaWidth");
        bool ah = DICTOOL->checkObjectExist_json(options, "areaHeight");
        if (aw && ah)
        {
            Size size = Size(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
            label->setTextAreaSize(size);
        }
        bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
        if (ha)
        {
            label->setTextHorizontalAlignment((TextHAlignment)DICTOOL->getIntValue_json(options, "hAlignment"));
        }
        bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
        if (va)
        {
            label->setTextVerticalAlignment((TextVAlignment)DICTOOL->getIntValue_json(options, "vAlignment"));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
