

#include "LayoutReader.h"
#include "../../../GUI/Layouts/UILayout.h"

NS_CC_EXT_BEGIN

static LayoutReader* instanceLayoutReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(LayoutReader)

LayoutReader::LayoutReader()
{
    
}

LayoutReader::~LayoutReader()
{
    
}

LayoutReader* LayoutReader::getInstance()
{
    if (!instanceLayoutReader)
    {
        instanceLayoutReader = new LayoutReader();
    }
    return instanceLayoutReader;
}

void LayoutReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    ui::Layout* panel = (ui::Layout*)widget;
    
    float w = 0, h = 0;
    bool adaptScrenn = DICTOOL->getBooleanValue_json(options, "adaptScreen");
    if (adaptScrenn)
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        w = screenSize.width;
        h = screenSize.height;
    }
    else
    {
        w = DICTOOL->getFloatValue_json(options, "width");
        h = DICTOOL->getFloatValue_json(options, "height");
    }
    panel->setSize(CCSizeMake(w, h));
    
    panel->setClippingEnabled(DICTOOL->getBooleanValue_json(options, "clipAble"));
    
    bool backGroundScale9Enable = DICTOOL->getBooleanValue_json(options, "backGroundScale9Enable");
    panel->setBackGroundImageScale9Enabled(backGroundScale9Enable);
    int cr = DICTOOL->getIntValue_json(options, "bgColorR");
    int cg = DICTOOL->getIntValue_json(options, "bgColorG");
    int cb = DICTOOL->getIntValue_json(options, "bgColorB");
    
    int scr = DICTOOL->getIntValue_json(options, "bgStartColorR");
    int scg = DICTOOL->getIntValue_json(options, "bgStartColorG");
    int scb = DICTOOL->getIntValue_json(options, "bgStartColorB");
    
    int ecr = DICTOOL->getIntValue_json(options, "bgEndColorR");
    int ecg = DICTOOL->getIntValue_json(options, "bgEndColorG");
    int ecb = DICTOOL->getIntValue_json(options, "bgEndColorB");
    
    float bgcv1 = DICTOOL->getFloatValue_json(options, "vectorX");
    float bgcv2 = DICTOOL->getFloatValue_json(options, "vectorY");
    panel->setBackGroundColorVector(ccp(bgcv1, bgcv2));
    
    int co = DICTOOL->getIntValue_json(options, "bgColorOpacity");
    
    int colorType = DICTOOL->getIntValue_json(options, "colorType");
    panel->setBackGroundColorType(ui::LayoutBackGroundColorType(colorType));
    panel->setBackGroundColor(ccc3(scr, scg, scb),ccc3(ecr, ecg, ecb));
    panel->setBackGroundColor(ccc3(cr, cg, cb));
    panel->setBackGroundColorOpacity(co);
    
    
    const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "backGroundImageData");
    int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_b = jsonPath;
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
            panel->setBackGroundImage(imageFileName_tp);
            break;
        }
        case 1:
        {
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            panel->setBackGroundImage(imageFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    
    int bgimgcr = DICTOOL->getIntValue_json(options, "colorR");
    int bgimgcg = DICTOOL->getIntValue_json(options, "colorG");
    int bgimgcb = DICTOOL->getIntValue_json(options, "colorB");
    panel->setBackGroundImageColor(ccc3(bgimgcr, bgimgcg, bgimgcb));
    
    if (backGroundScale9Enable)
    {
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        panel->setBackGroundImageCapInsets(CCRectMake(cx, cy, cw, ch));
    }
    panel->setLayoutType((ui::LayoutType)DICTOOL->getIntValue_json(options, "layoutType"));
    
    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

void LayoutReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    WidgetReader::setBasicProperties(widget, pCocoLoader, pCocoNode);
    
    ui::Layout* panel = static_cast<ui::Layout*>(widget);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
    
    
    std::map<std::string, int>  layoutMap;
    layoutMap.insert(std::make_pair("adaptScreen", 34));
    layoutMap.insert(std::make_pair("width", 30));
    layoutMap.insert(std::make_pair("height", 13));
    layoutMap.insert(std::make_pair("clipAble", 50));
    layoutMap.insert(std::make_pair("backGroundScale9Enable",35));
    layoutMap.insert(std::make_pair("bgColorR", 36));
    layoutMap.insert(std::make_pair("bgColorG", 37));
    layoutMap.insert(std::make_pair("bgColorB", 39));
    layoutMap.insert(std::make_pair("bgStartColorR", 45));
    layoutMap.insert(std::make_pair("bgStartColorG", 44));
    layoutMap.insert(std::make_pair("bgStartColorB", 43));
    layoutMap.insert(std::make_pair("bgEndColorR", 42));
    layoutMap.insert(std::make_pair("bgEndColorG", 41));
    layoutMap.insert(std::make_pair("bgEndColorB", 40));
    layoutMap.insert(std::make_pair("vectorX", 53));
    layoutMap.insert(std::make_pair("vectorY", 54));
    layoutMap.insert(std::make_pair("bgColorOpacity", 38));
    layoutMap.insert(std::make_pair("colorType", 51));
    layoutMap.insert(std::make_pair("backGroundImageData", 34));
    layoutMap.insert(std::make_pair("colorR", 10));
    layoutMap.insert(std::make_pair("colorG", 9));
    layoutMap.insert(std::make_pair("colorB", 8));
    layoutMap.insert(std::make_pair("capInsetsHeight", 33));
    layoutMap.insert(std::make_pair("capInsetsWidth", 34));
    layoutMap.insert(std::make_pair("capInsetsX", 35));
    layoutMap.insert(std::make_pair("capInsetsY", 36));
    layoutMap.insert(std::make_pair("layoutType", 36));
    
    
    std::map<std::string, int>  resourceMap;
    resourceMap.insert(std::make_pair("path", 0));
    resourceMap.insert(std::make_pair("plistFile", 1));
    resourceMap.insert(std::make_pair("resourceType", 2));
    
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    float w = 0, h = 0;
    
    std::string value1 = this->getProperty(layoutMap, stChildArray, "adaptScreen");
    std::string value2;
    std::string value3;
    std::string value4;
    
    bool adaptScrenn = valueToBool(value1);
    if (adaptScrenn)
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        w = screenSize.width;
        h = screenSize.height;
    }
    else
    {
        value1 = this->getProperty(layoutMap, stChildArray, "width");
        value2 = this->getProperty(layoutMap, stChildArray, "height");

        w = valueToFloat(value1);
        h =valueToFloat(value2);
    }
    panel->setSize(CCSizeMake(w, h));
    
    value1 = this->getProperty(layoutMap, stChildArray, "clipAble");
    panel->setClippingEnabled(valueToBool(value1));
    
    value1 = this->getProperty(layoutMap, stChildArray, "backGroundScale9Enable");

    bool backGroundScale9Enable = valueToBool(value1);
    panel->setBackGroundImageScale9Enabled(backGroundScale9Enable);
    
    value1 = this->getProperty(layoutMap, stChildArray, "bgColorR");
    value2 = this->getProperty(layoutMap, stChildArray, "bgColorG");
    value3 = this->getProperty(layoutMap, stChildArray, "bgColorB");

    int cr = valueToInt(value1);
    int cg = valueToInt(value2);
    int cb = valueToInt(value3);
    
    
    value1 = this->getProperty(layoutMap, stChildArray, "bgStartColorR");
    value2 = this->getProperty(layoutMap, stChildArray, "bgStartColorG");
    value3 = this->getProperty(layoutMap, stChildArray, "bgStartColorB");
    int scr = valueToInt(value1);
    int scg = valueToInt(value2);
    int scb = valueToInt(value3);
    
    value1 = this->getProperty(layoutMap, stChildArray, "bgEndColorR");
    value2 = this->getProperty(layoutMap, stChildArray, "bgEndColorG");
    value3 = this->getProperty(layoutMap, stChildArray, "bgEndColorB");
    int ecr = valueToInt(value1);
    int ecg = valueToInt(value2);
    int ecb = valueToInt(value3);
    
    value1 = this->getProperty(layoutMap, stChildArray, "vectorX");
    value2 = this->getProperty(layoutMap, stChildArray, "vectorY");
    float bgcv1 = valueToFloat(value1);
    float bgcv2 = valueToFloat(value2);
    panel->setBackGroundColorVector(ccp(bgcv1, bgcv2));
    
    value1 = this->getProperty(layoutMap, stChildArray, "bgColorOpacity");

    int co = valueToInt(value1);
    
    value1 = this->getProperty(layoutMap, stChildArray, "colorType");
    int colorType = valueToInt(value1);
    panel->setBackGroundColorType(ui::LayoutBackGroundColorType(colorType));
    panel->setBackGroundColor(ccc3(scr, scg, scb),ccc3(ecr, ecg, ecb));
    panel->setBackGroundColor(ccc3(cr, cg, cb));
    panel->setBackGroundColorOpacity(co);
    
    stExpCocoNode *resourceCocosNode = stChildArray[layoutMap["backGroundImageData"]].GetChildArray();
    
    if (resourceCocosNode) {
        
        value2 = this->getProperty(resourceMap, resourceCocosNode, "resourceType");
        int imageFileNameType = valueToInt(value2);
        
        switch (imageFileNameType)
        {
            case 0:
            {
                std::string tp_b = jsonPath;
                value1 = this->getProperty(resourceMap, resourceCocosNode, "path");
                const char* imageFileName = value1.c_str();
                const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
                panel->setBackGroundImage(imageFileName_tp);
                break;
            }
            case 1:
            {
                value1 = this->getProperty(resourceMap, resourceCocosNode, "path");
                const char* imageFileName = value1.c_str();
                panel->setBackGroundImage(imageFileName, ui::UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
    }
    
    
    
    value1 = this->getProperty(layoutMap, stChildArray, "colorR");
    value2 = this->getProperty(layoutMap, stChildArray, "colorG");
    value3 = this->getProperty(layoutMap, stChildArray, "colorB");
    int bgimgcr = valueToInt(value1);
    int bgimgcg = valueToInt(value2);
    int bgimgcb = valueToInt(value3);
    panel->setBackGroundImageColor(ccc3(bgimgcr, bgimgcg, bgimgcb));
    
    if (backGroundScale9Enable)
    {
        value1 = this->getProperty(layoutMap, stChildArray, "capInsetsX");
        value2 = this->getProperty(layoutMap, stChildArray, "capInsetsY");
        value3 = this->getProperty(layoutMap, stChildArray, "capInsetsWidth");
        value3 = this->getProperty(layoutMap, stChildArray, "capInsetsHeight");

        float cx = valueToFloat(value1);
        float cy = valueToFloat(value2);
        float cw = valueToFloat(value3);
        float ch = valueToFloat(value4);
        panel->setBackGroundImageCapInsets(CCRectMake(cx, cy, cw, ch));
    }
    
    value1 = this->getProperty(layoutMap, stChildArray, "layoutType");

    panel->setLayoutType((ui::LayoutType)valueToInt(value1));
    
    
    WidgetReader::setColorProperties(widget, pCocoLoader, pCocoNode);
}

NS_CC_EXT_END
