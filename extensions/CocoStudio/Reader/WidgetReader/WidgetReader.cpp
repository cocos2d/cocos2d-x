

#include "WidgetReader.h"

NS_CC_EXT_BEGIN

static WidgetReader* instanceWidgetReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(WidgetReader)

WidgetReader::WidgetReader()
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

NS_CC_EXT_END
