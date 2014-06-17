

#include "TextReader.h"
#include "ui/UIText.h"

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
            std::string fontName = DICTOOL->getStringValue_json(options, "fontName");
            std::string fontFilePath = jsonPath.append(fontName);
            label->setFontName(fontFilePath);
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
