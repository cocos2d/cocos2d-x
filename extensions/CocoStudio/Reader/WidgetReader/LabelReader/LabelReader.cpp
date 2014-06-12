

#include "LabelReader.h"
#include "../../../GUI/UIWidgets/UILabel.h"

NS_CC_EXT_BEGIN

static LabelReader* instanceLabelReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(LabelReader)

LabelReader::LabelReader()
{
    
}

LabelReader::~LabelReader()
{
    
}

LabelReader* LabelReader::getInstance()
{
    if (!instanceLabelReader)
    {
        instanceLabelReader = new LabelReader();
    }
    return instanceLabelReader;
}

void LabelReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    ui::Label* label = (ui::Label*)widget;
    bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, "touchScaleEnable");
    label->setTouchScaleChangeEnabled(touchScaleChangeAble);
    const char* text = DICTOOL->getStringValue_json(options, "text");
    label->setText(text);
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
        CCSize size = CCSize(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
        label->setTextAreaSize(size);
    }
    bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
    if (ha)
    {
        label->setTextHorizontalAlignment((CCTextAlignment)DICTOOL->getIntValue_json(options, "hAlignment"));
    }
    bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
    if (va)
    {
        label->setTextVerticalAlignment((CCVerticalTextAlignment)DICTOOL->getIntValue_json(options, "vAlignment"));
    }
    
    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

void LabelReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    WidgetReader::setBasicProperties(widget, pCocoLoader, pCocoNode);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
    
    ui::Label* label = static_cast<ui::Label*>(widget);
    
    std::map<std::string, int>  labelMap;
    
   labelMap.insert(std::make_pair("useMergedTexture", 28));
   labelMap.insert(std::make_pair("areaHeight", 33));
   labelMap.insert(std::make_pair("areaWidth", 34));
   labelMap.insert(std::make_pair("fontFile", 35));
   labelMap.insert(std::make_pair("fontName", 36));
   labelMap.insert(std::make_pair("fontSize", 37));
   labelMap.insert(std::make_pair("hAlignment",38));
   labelMap.insert(std::make_pair("text", 39));
   labelMap.insert(std::make_pair("touchScaleEnable", 40));
   labelMap.insert(std::make_pair("vAlignment", 41));
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    std::string value1;
    std::string value2;

    
    value1 = this->getProperty(labelMap, stChildArray, "touchScaleEnable");
    bool touchScaleChangeAble = valueToBool(value1);
    label->setTouchScaleChangeEnabled(touchScaleChangeAble);
    value1 = this->getProperty(labelMap, stChildArray, "text");

    const char* text = value1.c_str();
    label->setText(text);
    
    value1 = this->getProperty(labelMap, stChildArray, "fontSize");
    if (!value1.empty())
    {
        label->setFontSize(valueToInt(value1));
    }
    
    value1 = this->getProperty(labelMap, stChildArray, "fontName");

    if (!value1.empty())
    {
        label->setFontName(value1.c_str());
    }
    
    value1 = this->getProperty(labelMap, stChildArray, "areaWidth");
    value2 = this->getProperty(labelMap, stChildArray, "areaHeight");

    bool aw = !value1.empty();
    bool ah = !value2.empty();
    if (aw && ah)
    {
        CCSize size = CCSize(valueToFloat(value1),valueToFloat(value2));
        label->setTextAreaSize(size);
    }
    
    value1 = this->getProperty(labelMap, stChildArray, "hAlignment");
    bool ha = !value1.empty();
    if (ha)
    {
        label->setTextHorizontalAlignment((CCTextAlignment)valueToInt(value1));
    }
    
    value1 = this->getProperty(labelMap, stChildArray, "vAlignment");

    bool va = !value1.empty();
    if (va)
    {
        label->setTextVerticalAlignment((CCVerticalTextAlignment)valueToInt(value1));
    }
    

 
    
    WidgetReader::setColorProperties(widget, pCocoLoader, pCocoNode);

}

NS_CC_EXT_END
