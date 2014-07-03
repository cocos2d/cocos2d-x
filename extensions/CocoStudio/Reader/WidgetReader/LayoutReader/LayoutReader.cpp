

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
    
    int cr;
    int cg;
    int cb;
    int scr;
    int scg;
    int scb;
    int ecr;
    int ecg;
    int ecb;
    
    if (dynamic_cast<ui::PageView*>(widget)) {
        cr = DICTOOL->getIntValue_json(options, "bgColorR",150);
        cg = DICTOOL->getIntValue_json(options, "bgColorG",150);
        cb = DICTOOL->getIntValue_json(options, "bgColorB",100);
        
        scr = DICTOOL->getIntValue_json(options, "bgStartColorR",255);
        scg = DICTOOL->getIntValue_json(options, "bgStartColorG",255);
        scb = DICTOOL->getIntValue_json(options, "bgStartColorB",255);
        
        ecr = DICTOOL->getIntValue_json(options, "bgEndColorR",255);
        ecg = DICTOOL->getIntValue_json(options, "bgEndColorG",150);
        ecb = DICTOOL->getIntValue_json(options, "bgEndColorB",100);
    }else if(dynamic_cast<ui::ListView*>(widget)){
        cr = DICTOOL->getIntValue_json(options, "bgColorR",150);
        cg = DICTOOL->getIntValue_json(options, "bgColorG",150);
        cb = DICTOOL->getIntValue_json(options, "bgColorB",255);
        
        scr = DICTOOL->getIntValue_json(options, "bgStartColorR",255);
        scg = DICTOOL->getIntValue_json(options, "bgStartColorG",255);
        scb = DICTOOL->getIntValue_json(options, "bgStartColorB",255);
        
        ecr = DICTOOL->getIntValue_json(options, "bgEndColorR",150);
        ecg = DICTOOL->getIntValue_json(options, "bgEndColorG",150);
        ecb = DICTOOL->getIntValue_json(options, "bgEndColorB",255);
    }else if(dynamic_cast<ui::ScrollView*>(widget)){
        cr = DICTOOL->getIntValue_json(options, "bgColorR",255);
        cg = DICTOOL->getIntValue_json(options, "bgColorG",150);
        cb = DICTOOL->getIntValue_json(options, "bgColorB",100);
        
        scr = DICTOOL->getIntValue_json(options, "bgStartColorR",255);
        scg = DICTOOL->getIntValue_json(options, "bgStartColorG",255);
        scb = DICTOOL->getIntValue_json(options, "bgStartColorB",255);
        
        ecr = DICTOOL->getIntValue_json(options, "bgEndColorR",255);
        ecg = DICTOOL->getIntValue_json(options, "bgEndColorG",150);
        ecb = DICTOOL->getIntValue_json(options, "bgEndColorB",100);
    }else{
        cr = DICTOOL->getIntValue_json(options, "bgColorR",150);
        cg = DICTOOL->getIntValue_json(options, "bgColorG",200);
        cb = DICTOOL->getIntValue_json(options, "bgColorB",255);
        
        scr = DICTOOL->getIntValue_json(options, "bgStartColorR",255);
        scg = DICTOOL->getIntValue_json(options, "bgStartColorG",255);
        scb = DICTOOL->getIntValue_json(options, "bgStartColorB",255);
        
        ecr = DICTOOL->getIntValue_json(options, "bgEndColorR",150);
        ecg = DICTOOL->getIntValue_json(options, "bgEndColorG",200);
        ecb = DICTOOL->getIntValue_json(options, "bgEndColorB",255);
    }
   
    
    float bgcv1 = DICTOOL->getFloatValue_json(options, "vectorX");
    float bgcv2 = DICTOOL->getFloatValue_json(options, "vectorY",-0.5f);
    panel->setBackGroundColorVector(ccp(bgcv1, bgcv2));
    
    int co = DICTOOL->getIntValue_json(options, "bgColorOpacity",100);
    
    int colorType = DICTOOL->getIntValue_json(options, "colorType",1);
    
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
    
    
    int bgimgcr = DICTOOL->getIntValue_json(options, "colorR",255);
    int bgimgcg = DICTOOL->getIntValue_json(options, "colorG",255);
    int bgimgcb = DICTOOL->getIntValue_json(options, "colorB",255);
    panel->setBackGroundImageColor(ccc3(bgimgcr, bgimgcg, bgimgcb));

    int bgimgopacity = DICTOOL->getIntValue_json(options, "opacity",255);
    panel->setBackGroundImageOpacity(bgimgopacity);
    
    if (backGroundScale9Enable)
    {
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth",1);
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight",1);
        panel->setBackGroundImageCapInsets(CCRectMake(cx, cy, cw, ch));
    }
    panel->setLayoutType((ui::LayoutType)DICTOOL->getIntValue_json(options, "layoutType"));
    
    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

void LayoutReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    WidgetReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
    
    ui::Layout* panel = static_cast<ui::Layout*>(widget);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    this->beginSetBasicProperties(widget);
    
    int cr=0, cg = 0, cb = 0;
    int scr=0, scg=0, scb=0;
    int ecr=0, ecg=0, ecb= 0;
    float bgcv1 = 0.0f, bgcv2= 0.0f;
    float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
    ui::LayoutType layoutType = ui::LAYOUT_ABSOLUTE;
    ui::LayoutBackGroundColorType colorType = ui::LAYOUT_COLOR_NONE;
    int bgColorOpacity = 0;
    
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue(pCocoLoader);
        //            CCLOG("Layout: key = %s, value = %d", key.c_str(), i);
        if (key == "ignoreSize") {
            widget->ignoreContentAdaptWithSize(valueToBool(value));
        }else if(key == "sizeType"){
            widget->setSizeType((ui::SizeType)valueToInt(value));
        }else if(key == "positionType"){
            widget->setPositionType((ui::PositionType)valueToInt(value));
        }else if(key == "sizePercentX"){
            _sizePercentX = valueToFloat(value);
        }else if(key == "sizePercentY"){
            _sizePercentY = valueToFloat(value);
        }else if(key == "positionPercentX"){
            _positionPercentX = valueToFloat(value);
        }else if(key == "positionPercentY"){
            _positionPercentY = valueToFloat(value);
        }
        else if(key == "adaptScreen"){
            _isAdaptScreen = valueToBool(value);
        }
        else if (key == "width"){
            _width = valueToFloat(value);
        }else if(key == "height"){
            _height = valueToFloat(value);
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
            _position.x = valueToFloat(value);
        }else if(key == "y"){
            _position.y = valueToFloat(value);
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
        
        else if (key == "opacity") {
            _opacity = valueToInt(value);
        }
        else if(key == "colorR"){
            _color.r = valueToInt(value);
        }else if(key == "colorG"){
            _color.g = valueToInt(value);
        }else if(key == "colorB")
        {
            _color.b = valueToInt(value);
        }
        else if(key == "flipX"){
            widget->setFlipX(valueToBool(value));
        }else if(key == "flipY"){
            widget->setFlipY(valueToBool(value));
        }else if(key == "anchorPointX"){
            _originalAnchorPoint.x = valueToFloat(value);
        }else if(key == "anchorPointY"){
            _originalAnchorPoint.y = valueToFloat(value);
        }
        else if(key == "width"){
            _width = valueToFloat(value);
        }
        else if(key == "height"){
            _height = valueToFloat(value);
        }
        else if( key == "clipAble"){
            panel->setClippingEnabled(valueToBool(value));
        }else if(key == "backGroundScale9Enable"){
            panel->setBackGroundImageScale9Enabled(valueToBool(value));
        }else if(key == "bgColorR"){
            cr = valueToInt(value);
        }else if(key == "bgColorG"){
            cg = valueToInt(value);
        }else if(key == "bgColorB")
        {
            cb = valueToInt(value);
        }else if(key == "bgStartColorR"){
            scr = valueToInt(value);
        }else if(key == "bgStartColorG"){
            scg = valueToInt(value);
        }else if(key == "bgStartColorB")
        {
            scb = valueToInt(value);
        }
        else if(key == "bgEndColorR"){
            ecr = valueToInt(value);
        }else if(key == "bgEndColorG"){
            ecg = valueToInt(value);
        }else if(key == "bgEndColorB")
        {
            ecb = valueToInt(value);
        }else if (key == "vectorX"){
            bgcv1 = valueToFloat(value);
        }else if(key == "vectorY"){
            bgcv2 = valueToFloat(value);
        }else if(key == "bgColorOpacity"){
            bgColorOpacity = valueToInt(value);
        }else if( key == "colorType"){
            colorType = ui::LayoutBackGroundColorType(valueToInt(value));
        }else if (key == "backGroundImageData"){
            
            stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(pCocoLoader);
            if (backGroundChildren) {
                std::string resType = backGroundChildren[2].GetValue(pCocoLoader);
                
                ui::TextureResType imageFileNameType = (ui::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                panel->setBackGroundImage(backgroundValue.c_str(), imageFileNameType);
            }
            
        }else if(key == "capInsetsX"){
            capsx = valueToFloat(value);
        }else if(key == "capInsetsY"){
            capsy = valueToFloat(value);
        }else if(key == "capInsetsWidth"){
            capsWidth = valueToFloat(value);
        }else if(key == "capInsetsHeight"){
            capsHeight = valueToFloat(value);
        }else if (key == "layoutType"){
            layoutType = (ui::LayoutType)valueToInt(value);
        }
        
    }

    panel->setBackGroundColorVector(CCPoint(bgcv1, bgcv2));

    
    //TODO:FIXME  the calling order of the following two calls matters
    //The backgrouhnd color type must be setted first
    panel->setBackGroundColorType(colorType);
    
    panel->setBackGroundColor(ccc3(scr, scg, scb),ccc3(ecr, ecg, ecb));
    panel->setBackGroundColor(ccc3(cr, cg, cb));
    
    panel->setBackGroundColorOpacity(bgColorOpacity);
    
   
    panel->setBackGroundImageColor(ccc3(_color.r, _color.g, _color.b));
    
    panel->setBackGroundImageOpacity(_opacity);

    
    if (panel->isBackGroundImageScale9Enabled()) {
        panel->setBackGroundImageCapInsets(CCRect(capsx, capsy, capsWidth, capsHeight));
    }
    this->endSetBasicProperties(widget);

    panel->setLayoutType(layoutType);
    
}

NS_CC_EXT_END
