

#include "TextReader.h"
#include "ui/UIText.h"
#include "cocostudio/CocoLoader.h"

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
            instanceTextReader = new TextReader();
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
}
