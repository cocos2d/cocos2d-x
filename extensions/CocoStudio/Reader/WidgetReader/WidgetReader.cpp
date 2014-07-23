

#include "WidgetReader.h"
#include "../../../../cocos2dx/CCDirector.h"
#include "CocoStudio/ActionTimeline/CCNodeReader.h"

NS_CC_EXT_BEGIN

static WidgetReader* instanceWidgetReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(WidgetReader)

WidgetReader::WidgetReader()
:_sizePercentX(0.0f),
_isAdaptScreen(false),
_sizePercentY(0.0f),
_width(0.0f),
_height(0.0f),
_positionPercentX(0.0f),
_positionPercentY(0.0f),
_opacity(0)
{
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
    bool ignoreSizeExsits = DICTOOL->checkObjectExist_json(options, "ignoreSize");
    if (ignoreSizeExsits) {
        widget->ignoreContentAdaptWithSize(DICTOOL->getBooleanValue_json(options, "ignoreSize",false));
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
    
    int actionTag = DICTOOL->getIntValue_json(options, "actionTag");
    widget->setUserObject(cocostudio::timeline::TimelineActionData::create(actionTag));
    
    widget->setTouchEnabled(DICTOOL->getBooleanValue_json(options, "touchAble"));
    const char* name = DICTOOL->getStringValue_json(options, "name");
    const char* widgetName = name?name:"default";
    widget->setName(widgetName);
    float x = DICTOOL->getFloatValue_json(options, "x");
    float y = DICTOOL->getFloatValue_json(options, "y");
    widget->setPosition(ccp(x,y));
   
    widget->setScaleX(DICTOOL->getFloatValue_json(options, "scaleX",1.0));
    
    widget->setScaleY(DICTOOL->getFloatValue_json(options, "scaleY",1.0));
    
    widget->setRotation(DICTOOL->getFloatValue_json(options, "rotation",0));
    
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
    widget->setOpacity(DICTOOL->getIntValue_json(options, "opacity",255));
   
    bool isColorRExists = DICTOOL->checkObjectExist_json(options, "colorR");
    bool isColorGExists = DICTOOL->checkObjectExist_json(options, "colorG");
    bool isColorBExists = DICTOOL->checkObjectExist_json(options, "colorB");
   
    int colorR = DICTOOL->getIntValue_json(options, "colorR");
    int colorG = DICTOOL->getIntValue_json(options, "colorG");
    int colorB = DICTOOL->getIntValue_json(options, "colorB");
    
    if (isColorRExists && isColorGExists && isColorBExists) {
        widget->setColor(ccc3(colorR, colorG, colorB));
    }
    
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
    _position = widget->getPosition();
    //set default color
    _color = ccc3(255,255,255);
    widget->setColor(_color);
    _opacity = widget->getOpacity();
    _originalAnchorPoint = widget->getAnchorPoint();
}

void WidgetReader::endSetBasicProperties(cocos2d::ui::Widget *widget)
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    widget->setPositionPercent(CCPoint(_positionPercentX, _positionPercentY));
    widget->setSizePercent(CCPoint(_sizePercentX, _sizePercentY));
    if (_isAdaptScreen) {
        _width = screenSize.width;
        _height = screenSize.height;
    }
    widget->setOpacity(_opacity);
    widget->setColor(_color);
    widget->setSize(CCSize(_width, _height));
    widget->setAnchorPoint(_originalAnchorPoint);
    widget->setPosition(_position);
}

std::string WidgetReader::getResourcePath(CocoLoader *pCocoLoader,
                                          stExpCocoNode *pCocoNode,
                                          cocos2d::ui::TextureResType texType)
{
    stExpCocoNode *backGroundChildren = pCocoNode->GetChildArray(pCocoLoader);
    std::string backgroundValue = backGroundChildren[0].GetValue(pCocoLoader);
    
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

void WidgetReader::setPropsFromBinary(cocos2d::ui::Widget *widget, cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    
    
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue(pCocoLoader);
        
        if (key == "ignoreSize") {
            widget->ignoreContentAdaptWithSize(valueToBool(value));
        }else if(key == "sizeType"){
            widget->setSizeType((ui::SizeType)valueToInt(value));
        }else if(key == "positionType"){
            widget->setPositionType((ui::PositionType)valueToInt(value));
        }else if(key == "sizePercentX"){
            widget->setSizePercent(CCPoint(valueToFloat(value), widget->getSizePercent().y));
        }else if(key == "sizePercentY"){
            widget->setSizePercent(CCPoint(widget->getSizePercent().x, valueToFloat(value)));
        }else if(key == "positionPercentX"){
            widget->setPositionPercent(CCPoint(valueToFloat(value), widget->getPositionPercent().y));
        }else if(key == "positionPercentY"){
            widget->setPositionPercent(CCPoint(widget->getPositionPercent().x, valueToFloat(value)));
        }else if (key == "width"){
            widget->setSize(CCSize(valueToFloat(value), widget->getSize().height));
        }else if(key == "height"){
            widget->setSize(CCSize(widget->getSize().width, valueToFloat(value)));
        }else if(key == "tag"){
            widget->setTag(valueToInt(value));
        }else if(key == "actiontag"){
            widget->setActionTag(valueToInt(value));
        }else if(key == "touchAble"){
            widget->setTouchEnabled(valueToBool(value));
        }else if(key == "name"){
            std::string widgetName = value.empty() ? "default" : value;
            widget->setName(widgetName.c_str());
        }else if(key == "x"){
            widget->setPosition(CCPoint(valueToFloat(value), widget->getPosition().y));
        }else if(key == "y"){
            widget->setPosition(CCPoint(widget->getPosition().x, valueToFloat(value)));
        }else if(key == "scaleX"){
            widget->setScaleX(valueToFloat(value));
        }else if(key == "scaleY"){
            widget->setScaleY(valueToFloat(value));
        }else if(key == "rotation"){
            widget->setRotation(valueToFloat(value));
        }else if(key == "visible"){
            widget->setVisible(valueToBool(value));
        }else if(key == "ZOrder"){
            widget->setZOrder(valueToInt(value));
        }else if(key == "layoutParameter"){
            stExpCocoNode *layoutCocosNode = stChildArray[i].GetChildArray(pCocoLoader);
            
            ui::LinearLayoutParameter *linearParameter = ui::LinearLayoutParameter::create();
            ui::RelativeLayoutParameter *relativeParameter = ui::RelativeLayoutParameter::create();
            ui::Margin mg;
            
            int paramType = -1;
            for (int j = 0; j < stChildArray[i].GetChildNum(); ++j) {
                std::string innerKey = layoutCocosNode[j].GetName(pCocoLoader);
                std::string innerValue = layoutCocosNode[j].GetValue(pCocoLoader);
                
                if (innerKey == "type") {
                    paramType = valueToInt(innerValue);
                }else if(innerKey == "gravity"){
                    linearParameter->setGravity((cocos2d::ui::LinearGravity)valueToInt(innerValue));
                }else if(innerKey == "relativeName"){
                    relativeParameter->setRelativeName(innerValue.c_str());
                }else if(innerKey == "relativeToName"){
                    relativeParameter->setRelativeToWidgetName(innerValue.c_str());
                }else if(innerKey == "align"){
                    relativeParameter->setAlign((cocos2d::ui::RelativeAlign)valueToInt(innerValue));
                }else if(innerKey == "marginLeft"){
                    mg.left = valueToFloat(innerValue);
                }else if(innerKey == "marginTop"){
                    mg.top = valueToFloat(innerValue);
                }else if(innerKey == "marginRight"){
                    mg.right = valueToFloat(innerValue);
                }else if(innerKey == "marginDown"){
                    mg.bottom = valueToFloat(innerValue);
                }
            }
            
            linearParameter->setMargin(mg);
            relativeParameter->setMargin(mg);
            
            switch (paramType) {
                case 1:
                    widget->setLayoutParameter(linearParameter);
                    break;
                case 2:
                    widget->setLayoutParameter(relativeParameter);
                default:
                    break;
            }
        }
        
    }
}


NS_CC_EXT_END
