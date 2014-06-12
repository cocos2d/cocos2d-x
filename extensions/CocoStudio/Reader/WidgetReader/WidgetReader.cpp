

#include "WidgetReader.h"
#include "../CocoLoader.h"
#include "../../../../cocos2dx/CCDirector.h"

NS_CC_EXT_BEGIN

static WidgetReader* instanceWidgetReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(WidgetReader)

WidgetReader::WidgetReader()
{
    _basicPropertyDict.insert(std::make_pair("__type", 0));
    _basicPropertyDict.insert(std::make_pair("classname", 1));
    _basicPropertyDict.insert(std::make_pair("name", 2));
    _basicPropertyDict.insert(std::make_pair("ZOrder", 3));
    _basicPropertyDict.insert(std::make_pair("actiontag", 4));
    _basicPropertyDict.insert(std::make_pair("anchorPointX", 5));
    _basicPropertyDict.insert(std::make_pair("anchorPointY", 6));
    _basicPropertyDict.insert(std::make_pair("classType", 7));
    _basicPropertyDict.insert(std::make_pair("colorB", 8));
    _basicPropertyDict.insert(std::make_pair("colorG", 9));
    _basicPropertyDict.insert(std::make_pair("colorR", 10));
    _basicPropertyDict.insert(std::make_pair("flipX", 11));
    _basicPropertyDict.insert(std::make_pair("flipY", 12));
    _basicPropertyDict.insert(std::make_pair("height", 13));
    _basicPropertyDict.insert(std::make_pair("ignoreSize", 14));
    _basicPropertyDict.insert(std::make_pair("layoutParameter", 15));
    _basicPropertyDict.insert(std::make_pair("opacity", 16));
    _basicPropertyDict.insert(std::make_pair("positionPercentX",17));
    _basicPropertyDict.insert(std::make_pair("positionPercentY", 18));
    _basicPropertyDict.insert(std::make_pair("positionType", 19));
    _basicPropertyDict.insert(std::make_pair("rotation", 20));
    _basicPropertyDict.insert(std::make_pair("scaleX", 21));
    _basicPropertyDict.insert(std::make_pair("scaleY", 22));
    _basicPropertyDict.insert(std::make_pair("sizePercentX", 23));
    _basicPropertyDict.insert(std::make_pair("sizePercentY", 24));
    _basicPropertyDict.insert(std::make_pair("sizeType", 25));
    _basicPropertyDict.insert(std::make_pair("tag", 26));
    _basicPropertyDict.insert(std::make_pair("touchAble", 27));
    _basicPropertyDict.insert(std::make_pair("visible", 29));
    _basicPropertyDict.insert(std::make_pair("width", 30));
    _basicPropertyDict.insert(std::make_pair("x", 31));
    _basicPropertyDict.insert(std::make_pair("y", 32));
    
    //
    _layoutParameterDict.insert(std::make_pair("classname", 0));
    _layoutParameterDict.insert(std::make_pair("name", 1));
    _layoutParameterDict.insert(std::make_pair("align", 2));
    _layoutParameterDict.insert(std::make_pair("gravity", 3));
    _layoutParameterDict.insert(std::make_pair("layoutEageType", 4));
    _layoutParameterDict.insert(std::make_pair("layoutNormalHorizontal", 5));
    _layoutParameterDict.insert(std::make_pair("layoutNormalVertical", 6));
    _layoutParameterDict.insert(std::make_pair("layoutParentHorizontal", 7));
    _layoutParameterDict.insert(std::make_pair("layoutParentVertical", 8));

    _layoutParameterDict.insert(std::make_pair("marginDown", 9));
    _layoutParameterDict.insert(std::make_pair("marginLeft", 10));
    _layoutParameterDict.insert(std::make_pair("marginRight", 11));
    _layoutParameterDict.insert(std::make_pair("marginTop", 12));
    _layoutParameterDict.insert(std::make_pair("relativeName", 13));
    _layoutParameterDict.insert(std::make_pair("relativeToName", 14));
    _layoutParameterDict.insert(std::make_pair("type", 15));


}

std::string WidgetReader::getProperty(std::map<std::string, int> &map, cocos2d::extension::stExpCocoNode *node, std::string key)
{
    return node[map[key]].GetValue();
}

void WidgetReader::setBasicProperties(cocos2d::ui::Widget *widget, cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
  
    std::string value = this->getProperty(_basicPropertyDict, stChildArray, "ignoreSize");
    if (!value.empty()) {
        bool ignoreSize = valueToBool(value);
        widget->ignoreContentAdaptWithSize(ignoreSize);
    }
    
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "sizeType");
    widget->setSizeType((ui::SizeType)valueToInt(value));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "positionType");
    widget->setPositionType((ui::PositionType)valueToInt(value));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "sizePercentX");
    std::string value2 = this->getProperty(_basicPropertyDict, stChildArray, "sizePercentY");
    widget->setSizePercent(ccp(valueToFloat(value), valueToFloat(value2)));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "positionPercentX");
    value2 = this->getProperty(_basicPropertyDict, stChildArray, "positionPercentY");
    
    widget->setPositionPercent(ccp(valueToFloat(value), valueToFloat(value2)));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "width");
    value2 = this->getProperty(_basicPropertyDict, stChildArray, "height");

    widget->setSize(CCSizeMake(valueToFloat(value), valueToFloat(value2)));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "tag");
    
    widget->setTag(valueToInt(value));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "actiontag");
    widget->setActionTag(valueToInt(value));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "touchAble");
    
    widget->setTouchEnabled(valueToBool(value));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "name");
    
    std::string widgetName = value.empty() ? "default" : value;
    widget->setName(widgetName.c_str());
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "x");
    value2 = this->getProperty(_basicPropertyDict, stChildArray, "y");
   
    widget->setPosition(ccp(valueToFloat(value),valueToFloat(value2)));
    
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "scaleX");
    if (!value.empty()) {
        widget->setScaleX(valueToFloat(value));
    }
    value = this->getProperty(_basicPropertyDict, stChildArray, "scaleY");
    if (!value.empty())
    {
        widget->setScaleY(valueToFloat(value));
    }
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "rotation");
    if (!value.empty())
    {
        widget->setRotation(valueToFloat(value));
    }
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "visible");
    if (!value.empty())
    {
        widget->setVisible(valueToBool(value));
    }
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "ZOrder");
    widget->setZOrder(valueToInt(value));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "layoutParameter");
    
    stExpCocoNode *layoutCocosNode = stChildArray[_basicPropertyDict["layoutParameter"]].GetChildArray();

    if (layoutCocosNode)
    {
        value = this->getProperty(_layoutParameterDict, layoutCocosNode, "type");
        
        int paramType = valueToInt(value);
        
        cocos2d::ui::LayoutParameter* parameter = NULL;
        switch (paramType)
        {
            case 0:
                break;
            case 1:
            {
                parameter = ui::LinearLayoutParameter::create();
                value = this->getProperty(_layoutParameterDict, layoutCocosNode, "gravity");
                int gravity = valueToInt(value);
                ((ui::LinearLayoutParameter*)parameter)->setGravity((ui::LinearGravity)gravity);
                break;
            }
            case 2:
            {
                parameter = ui::RelativeLayoutParameter::create();
                ui::RelativeLayoutParameter* rParameter = (ui::RelativeLayoutParameter*)parameter;
                value = this->getProperty(_layoutParameterDict, layoutCocosNode, "relativeName");
                const char* relativeName = value.c_str();
                rParameter->setRelativeName(relativeName);
                value = this->getProperty(_layoutParameterDict, layoutCocosNode, "relativeToName");

                const char* relativeToName = value.c_str();
                rParameter->setRelativeToWidgetName(relativeToName);
                value = this->getProperty(_layoutParameterDict, layoutCocosNode, "align");

                int align = valueToInt(value);
                rParameter->setAlign((ui::RelativeAlign)align);
                break;
            }
            default:
                break;
        }
        if (parameter)
        {
            value = this->getProperty(_layoutParameterDict, layoutCocosNode, "marginLeft");
            float mgl = valueToFloat(value);
            value = this->getProperty(_layoutParameterDict, layoutCocosNode, "marginTop");
            float mgt = valueToFloat(value);
            value = this->getProperty(_layoutParameterDict, layoutCocosNode, "marginRight");
            float mgr = valueToFloat(value);
            value = this->getProperty(_layoutParameterDict, layoutCocosNode, "marginDown");
            float mgb = valueToFloat(value);
            parameter->setMargin(ui::Margin(mgl, mgt, mgr, mgb));
            widget->setLayoutParameter(parameter);
        }
    }
}

void WidgetReader::setColorProperties(cocos2d::ui::Widget *widget, cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
    
    std::string value = this->getProperty(_basicPropertyDict, stChildArray, "opacity");
    if (!value.empty()) {
        widget->setOpacity(valueToInt(value));
    }
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "colorR");
    std::string value2 = this->getProperty(_basicPropertyDict, stChildArray, "colorG");
    std::string value3 = this->getProperty(_basicPropertyDict, stChildArray, "colorB");

    int colorR = !value.empty() ? valueToInt(value) : 255;
    int colorG = !value2.empty() ? valueToInt(value2) : 255;
    int colorB = !value3.empty() ? valueToInt(value3) : 255;
    widget->setColor(ccc3(colorR, colorG, colorB));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "anchorPointX");
    
    float apxf = !value.empty() ? valueToFloat(value) : ((widget->getWidgetType() == ui::WidgetTypeWidget) ? 0.5f : 0.0f);
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "anchorPointY");

    float apyf = !value.empty() ? valueToFloat(value) : ((widget->getWidgetType() == ui::WidgetTypeWidget) ? 0.5f : 0.0f);
    widget->setAnchorPoint(ccp(apxf, apyf));
    
    value = this->getProperty(_basicPropertyDict, stChildArray, "flipX");
    value2 = this->getProperty(_basicPropertyDict, stChildArray, "flipY");
    
    widget->setFlipX(valueToBool(value));
    widget->setFlipY(valueToBool(value2));
}

WidgetReader::~WidgetReader()
{
    
}

WidgetReader* WidgetReader::getInstance()
{
    if (!instanceWidgetReader)
    {
        instanceWidgetReader = new WidgetReader();
    }
    return instanceWidgetReader;
}

int WidgetReader::valueToInt(std::string& value)
{
    return atoi(value.c_str());
}
bool WidgetReader::valueToBool(std::string& value)
{
    int intValue = valueToInt(value);
    if (1 == intValue) {
        return true;
    }else{
        return false;
    }
}
float WidgetReader::valueToFloat(std::string& value)
{
    return atof(value.c_str());
}

void WidgetReader::purge()
{
    CC_SAFE_DELETE(instanceWidgetReader);
}

void WidgetReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    bool ignoreSizeExsit = DICTOOL->checkObjectExist_json(options, "ignoreSize");
    if (ignoreSizeExsit)
    {
        widget->ignoreContentAdaptWithSize(DICTOOL->getBooleanValue_json(options, "ignoreSize"));
    }
    
    widget->setSizeType((ui::SizeType)DICTOOL->getIntValue_json(options, "sizeType"));
    widget->setPositionType((ui::PositionType)DICTOOL->getIntValue_json(options, "positionType"));
    
    widget->setSizePercent(ccp(DICTOOL->getFloatValue_json(options, "sizePercentX"), DICTOOL->getFloatValue_json(options, "sizePercentY")));
    widget->setPositionPercent(ccp(DICTOOL->getFloatValue_json(options, "positionPercentX"), DICTOOL->getFloatValue_json(options, "positionPercentY")));
    
    float w = DICTOOL->getFloatValue_json(options, "width");
    float h = DICTOOL->getFloatValue_json(options, "height");
    widget->setSize(CCSizeMake(w, h));
    
    widget->setTag(DICTOOL->getIntValue_json(options, "tag"));
    widget->setActionTag(DICTOOL->getIntValue_json(options, "actiontag"));
    widget->setTouchEnabled(DICTOOL->getBooleanValue_json(options, "touchAble"));
    const char* name = DICTOOL->getStringValue_json(options, "name");
    const char* widgetName = name?name:"default";
    widget->setName(widgetName);
    float x = DICTOOL->getFloatValue_json(options, "x");
    float y = DICTOOL->getFloatValue_json(options, "y");
    widget->setPosition(ccp(x,y));
    bool sx = DICTOOL->checkObjectExist_json(options, "scaleX");
    if (sx)
    {
        widget->setScaleX(DICTOOL->getFloatValue_json(options, "scaleX"));
    }
    bool sy = DICTOOL->checkObjectExist_json(options, "scaleY");
    if (sy)
    {
        widget->setScaleY(DICTOOL->getFloatValue_json(options, "scaleY"));
    }
    bool rt = DICTOOL->checkObjectExist_json(options, "rotation");
    if (rt)
    {
        widget->setRotation(DICTOOL->getFloatValue_json(options, "rotation"));
    }
    bool vb = DICTOOL->checkObjectExist_json(options, "visible");
    if (vb)
    {
        widget->setVisible(DICTOOL->getBooleanValue_json(options, "visible"));
    }
    int z = DICTOOL->getIntValue_json(options, "ZOrder");
    widget->setZOrder(z);
    
    bool layout = DICTOOL->checkObjectExist_json(options, "layoutParameter");
    if (layout)
    {
        const rapidjson::Value& layoutParameterDic = DICTOOL->getSubDictionary_json(options, "layoutParameter");
        int paramType = DICTOOL->getIntValue_json(layoutParameterDic, "type");
        cocos2d::ui::LayoutParameter* parameter = NULL;
        switch (paramType)
        {
            case 0:
                break;
            case 1:
            {
                parameter = ui::LinearLayoutParameter::create();
                int gravity = DICTOOL->getIntValue_json(layoutParameterDic, "gravity");
                ((ui::LinearLayoutParameter*)parameter)->setGravity((ui::LinearGravity)gravity);
                break;
            }
            case 2:
            {
                parameter = ui::RelativeLayoutParameter::create();
                ui::RelativeLayoutParameter* rParameter = (ui::RelativeLayoutParameter*)parameter;
                const char* relativeName = DICTOOL->getStringValue_json(layoutParameterDic, "relativeName");
                rParameter->setRelativeName(relativeName);
                const char* relativeToName = DICTOOL->getStringValue_json(layoutParameterDic, "relativeToName");
                rParameter->setRelativeToWidgetName(relativeToName);
                int align = DICTOOL->getIntValue_json(layoutParameterDic, "align");
                rParameter->setAlign((ui::RelativeAlign)align);
                break;
            }
            default:
                break;
        }
        if (parameter)
        {
            float mgl = DICTOOL->getFloatValue_json(layoutParameterDic, "marginLeft");
            float mgt = DICTOOL->getFloatValue_json(layoutParameterDic, "marginTop");
            float mgr = DICTOOL->getFloatValue_json(layoutParameterDic, "marginRight");
            float mgb = DICTOOL->getFloatValue_json(layoutParameterDic, "marginDown");
            parameter->setMargin(ui::Margin(mgl, mgt, mgr, mgb));
            widget->setLayoutParameter(parameter);
        }
    }
}

void WidgetReader::setColorPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    bool op = DICTOOL->checkObjectExist_json(options, "opacity");
    if (op)
    {
        widget->setOpacity(DICTOOL->getIntValue_json(options, "opacity"));
    }
    bool cr = DICTOOL->checkObjectExist_json(options, "colorR");
    bool cg = DICTOOL->checkObjectExist_json(options, "colorG");
    bool cb = DICTOOL->checkObjectExist_json(options, "colorB");
    int colorR = cr ? DICTOOL->getIntValue_json(options, "colorR") : 255;
    int colorG = cg ? DICTOOL->getIntValue_json(options, "colorG") : 255;
    int colorB = cb ? DICTOOL->getIntValue_json(options, "colorB") : 255;
    widget->setColor(ccc3(colorR, colorG, colorB));
    bool apx = DICTOOL->checkObjectExist_json(options, "anchorPointX");
    float apxf = apx ? DICTOOL->getFloatValue_json(options, "anchorPointX") : ((widget->getWidgetType() == ui::WidgetTypeWidget) ? 0.5f : 0.0f);
    bool apy = DICTOOL->checkObjectExist_json(options, "anchorPointY");
    float apyf = apy ? DICTOOL->getFloatValue_json(options, "anchorPointY") : ((widget->getWidgetType() == ui::WidgetTypeWidget) ? 0.5f : 0.0f);
    widget->setAnchorPoint(ccp(apxf, apyf));
    bool flipX = DICTOOL->getBooleanValue_json(options, "flipX");
    bool flipY = DICTOOL->getBooleanValue_json(options, "flipY");
    widget->setFlipX(flipX);
    widget->setFlipY(flipY);
}

void WidgetReader::beginSetBasicProperties(cocos2d::ui::Widget *widget)
{
    position = widget->getPosition();
    //set default color
    widget->setColor(ccc3(255,255,255));
    originalAnchorPoint = widget->getAnchorPoint();
}

void WidgetReader::endSetBasicProperties(cocos2d::ui::Widget *widget)
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    widget->setPositionPercent(CCPoint(positionPercentX, positionPercentY));
    widget->setSizePercent(CCPoint(sizePercentX, sizePercentY));
    if (isAdaptScreen) {
        width = screenSize.width;
        height = screenSize.height;
    }
    widget->setSize(CCSize(width, height));
    widget->setPosition(position);
    widget->setAnchorPoint(originalAnchorPoint);
}

std::string WidgetReader::getResourcePath(CocoLoader *pCocoLoader,
                                          stExpCocoNode *pCocoNode,
                                          cocos2d::ui::TextureResType texType)
{
    stExpCocoNode *backGroundChildren = pCocoNode->GetChildArray();
    std::string backgroundValue = backGroundChildren[0].GetValue();
    
    if (backgroundValue.size() < 3) {
        return "";
    }
    
    std::string binaryPath = GUIReader::shareReader()->getFilePath();
    
    std::string imageFileName_tp;
    if (!backgroundValue.empty())
    {
        if (texType == cocos2d::ui::UI_TEX_TYPE_LOCAL) {
            imageFileName_tp = binaryPath + backgroundValue;
        }
        else if(texType == cocos2d::ui::UI_TEX_TYPE_PLIST){
            imageFileName_tp = backgroundValue;
        }
        else{
            CCAssert(0, "invalid TextureResType!!!");
        }
    }
    return imageFileName_tp;
}


NS_CC_EXT_END
