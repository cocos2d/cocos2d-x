

#include "WidgetReader.h"
#include "cocostudio/CocoLoader.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static WidgetReader* instanceWidgetReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(WidgetReader)
    
    WidgetReader::WidgetReader()
    :_sizePercentX(0.0f),
    _sizePercentY(0.0f),
    _isAdaptScreen(false),
    _width(0.0f),
    _height(0.0f),
    _positionPercentX(0.0f),
    _positionPercentY(0.0f),
    _opacity(255)
    {
        valueToInt = [=](std::string str) -> int{
            return atoi(str.c_str());
        };
        
        valueToBool = [=](std::string str) -> bool{
            int intValue = valueToInt(str);
            if (1 == intValue) {
                return true;
            }else{
                return false;
            }
        };
        
        valueToFloat = [=](std::string str) -> float{
            return atof(str.c_str());
        };
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
    
    void WidgetReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {        
        bool ignoreSizeExsit = DICTOOL->checkObjectExist_json(options, "ignoreSize");
        if (ignoreSizeExsit)
        {
            widget->ignoreContentAdaptWithSize(DICTOOL->getBooleanValue_json(options, "ignoreSize"));
        }
        
        widget->setSizeType((Widget::SizeType)DICTOOL->getIntValue_json(options, "sizeType"));
        widget->setPositionType((Widget::PositionType)DICTOOL->getIntValue_json(options, "positionType"));
        
        widget->setSizePercent(Vec2(DICTOOL->getFloatValue_json(options, "sizePercentX"), DICTOOL->getFloatValue_json(options, "sizePercentY")));
        widget->setPositionPercent(Vec2(DICTOOL->getFloatValue_json(options, "positionPercentX"), DICTOOL->getFloatValue_json(options, "positionPercentY")));
        
        /* adapt screen */
        float w = 0, h = 0;
        bool adaptScrenn = DICTOOL->getBooleanValue_json(options, "adaptScreen");
        if (adaptScrenn)
        {
            Size screenSize = CCDirector::getInstance()->getWinSize();
            w = screenSize.width;
            h = screenSize.height;
        }
        else
        {
            w = DICTOOL->getFloatValue_json(options, "width");
            h = DICTOOL->getFloatValue_json(options, "height");
        }
        widget->setSize(Size(w, h));
        // before
        /*
         float w = DICTOOL->getFloatValue_json(options, "width");
         float h = DICTOOL->getFloatValue_json(options, "height");
         widget->setSize(CCSizeMake(w, h));
         */
        /**/
        
        widget->setTag(DICTOOL->getIntValue_json(options, "tag"));
        widget->setActionTag(DICTOOL->getIntValue_json(options, "actiontag"));
        widget->setTouchEnabled(DICTOOL->getBooleanValue_json(options, "touchAble"));
        const char* name = DICTOOL->getStringValue_json(options, "name");
        const char* widgetName = name?name:"default";
        widget->setName(widgetName);
        float x = DICTOOL->getFloatValue_json(options, "x");
        float y = DICTOOL->getFloatValue_json(options, "y");
        widget->setPosition(Vec2(x,y));
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
        widget->setLocalZOrder(z);
        
        bool layout = DICTOOL->checkObjectExist_json(options, "layoutParameter");
        if (layout)
        {
            const rapidjson::Value& layoutParameterDic = DICTOOL->getSubDictionary_json(options, "layoutParameter");
            int paramType = DICTOOL->getIntValue_json(layoutParameterDic, "type");
            LayoutParameter* parameter = nullptr;
            switch (paramType)
            {
                case 0:
                    break;
                case 1:
                {
                    parameter = LinearLayoutParameter::create();
                    int gravity = DICTOOL->getIntValue_json(layoutParameterDic, "gravity");
                    ((LinearLayoutParameter*)parameter)->setGravity((cocos2d::ui::LinearLayoutParameter::LinearGravity)gravity);
                    break;
                }
                case 2:
                {
                    parameter = RelativeLayoutParameter::create();
                    RelativeLayoutParameter* rParameter = (RelativeLayoutParameter*)parameter;
                    const char* relativeName = DICTOOL->getStringValue_json(layoutParameterDic, "relativeName");
                    rParameter->setRelativeName(relativeName);
                    const char* relativeToName = DICTOOL->getStringValue_json(layoutParameterDic, "relativeToName");
                    rParameter->setRelativeToWidgetName(relativeToName);
                    int align = DICTOOL->getIntValue_json(layoutParameterDic, "align");
                    rParameter->setAlign((cocos2d::ui::RelativeLayoutParameter::RelativeAlign)align);
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
                parameter->setMargin(Margin(mgl, mgt, mgr, mgb));
                widget->setLayoutParameter(parameter);
            }
        }
    }
    
    void WidgetReader::setColorPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
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
        widget->setColor(Color3B(colorR, colorG, colorB));
        
        this->setAnchorPointForWidget(widget, options);
        
        bool flipX = DICTOOL->getBooleanValue_json(options, "flipX");
        bool flipY = DICTOOL->getBooleanValue_json(options, "flipY");
        widget->setFlippedX(flipX);
        widget->setFlippedY(flipY);
    }
    
    void WidgetReader::beginSetBasicProperties(cocos2d::ui::Widget *widget)
    {
        _position = widget->getPosition();
        //set default color
        _color = Color3B(255,255,255);
        widget->setColor(_color);
        _opacity = widget->getOpacity();
        _originalAnchorPoint = widget->getAnchorPoint();
    }
    
    void WidgetReader::endSetBasicProperties(Widget *widget)
    {
        Size screenSize = Director::getInstance()->getWinSize();
        
        widget->setPositionPercent(Vec2(_positionPercentX, _positionPercentY));
        widget->setSizePercent(Vec2(_sizePercentX, _sizePercentY));
        if (_isAdaptScreen) {
            _width = screenSize.width;
            _height = screenSize.height;
        }
        widget->setColor(_color);
        widget->setOpacity(_opacity);
        widget->setSize(Size(_width, _height));
        widget->setPosition(_position);
        widget->setAnchorPoint(_originalAnchorPoint);
    }
    
    std::string WidgetReader::getResourcePath(const rapidjson::Value &dict,
                                              const std::string &key,
                                              cocos2d::ui::Widget::TextureResType texType)
    {
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        const char* imageFileName = DICTOOL->getStringValue_json(dict, key.c_str());
        std::string imageFileName_tp;
        if (nullptr != imageFileName)
        {
            if (texType == ui::Widget::TextureResType::LOCAL) {
                imageFileName_tp = jsonPath + imageFileName;
            }
            else if(texType == ui::Widget::TextureResType::PLIST){
                imageFileName_tp = imageFileName;
            }
            else{
                CCASSERT(0, "invalid TextureResType!!!");
            }
        }
        return imageFileName_tp;
    }
    
    std::string WidgetReader::getResourcePath(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, cocos2d::ui::Widget::TextureResType texType)
    {
        stExpCocoNode *backGroundChildren = pCocoNode->GetChildArray();
        std::string backgroundValue = backGroundChildren[0].GetValue();

        if (backgroundValue.size() < 3) {
            return "";
        }
       
        std::string binaryPath = GUIReader::getInstance()->getFilePath();
        
        std::string imageFileName_tp;
        if (!backgroundValue.empty())
        {
            if (texType == ui::Widget::TextureResType::LOCAL) {
                imageFileName_tp = binaryPath + backgroundValue;
            }
            else if(texType == ui::Widget::TextureResType::PLIST){
                imageFileName_tp = backgroundValue;
            }
            else{
                CCASSERT(0, "invalid TextureResType!!!");
            }
        }
        return imageFileName_tp;
    }
    
    void WidgetReader::setAnchorPointForWidget(cocos2d::ui::Widget *widget, const rapidjson::Value &options)
    {
        bool isAnchorPointXExists = DICTOOL->checkObjectExist_json(options, "anchorPointX");
        float anchorPointXInFile;
        if (isAnchorPointXExists) {
            anchorPointXInFile = DICTOOL->getFloatValue_json(options, "anchorPointX");
        }else{
            anchorPointXInFile = widget->getAnchorPoint().x;
        }
        
        bool isAnchorPointYExists = DICTOOL->checkObjectExist_json(options, "anchorPointY");
        float anchorPointYInFile;
        if (isAnchorPointYExists) {
            anchorPointYInFile = DICTOOL->getFloatValue_json(options, "anchorPointY");
        }
        else{
            anchorPointYInFile = widget->getAnchorPoint().y;
        }
        
        if (isAnchorPointXExists || isAnchorPointYExists) {
            widget->setAnchorPoint(Vec2(anchorPointXInFile, anchorPointYInFile));
        }
    }
    
    void WidgetReader::setPropsFromBinary(cocos2d::ui::Widget *widget, cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
    {
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        
        
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
            
            if (key == "ignoreSize") {
                widget->ignoreContentAdaptWithSize(valueToBool(value));
            }else if(key == "sizeType"){
                widget->setSizeType((Widget::SizeType)valueToInt(value));
            }else if(key == "positionType"){
                widget->setPositionType((Widget::PositionType)valueToInt(value));
            }else if(key == "sizePercentX"){
                widget->setSizePercent(Vec2(valueToFloat(value), widget->getSizePercent().y));
            }else if(key == "sizePercentY"){
                widget->setSizePercent(Vec2(widget->getSizePercent().x, valueToFloat(value)));
            }else if(key == "positionPercentX"){
                widget->setPositionPercent(Vec2(valueToFloat(value), widget->getPositionPercent().y));
            }else if(key == "positionPercentY"){
                widget->setPositionPercent(Vec2(widget->getPositionPercent().x, valueToFloat(value)));
            }else if (key == "width"){
                widget->setSize(Size(valueToFloat(value), widget->getSize().height));
            }else if(key == "height"){
                widget->setSize(Size(widget->getSize().width, valueToFloat(value)));
            }else if(key == "tag"){
                widget->setTag(valueToInt(value));
            }else if(key == "actiontag"){
                widget->setActionTag(valueToInt(value));
            }else if(key == "touchAble"){
                widget->setTouchEnabled(valueToBool(value));
            }else if(key == "name"){
                std::string widgetName = value.empty() ? "default" : value;
                widget->setName(widgetName);
            }else if(key == "x"){
                widget->setPosition(Vec2(valueToFloat(value), widget->getPosition().y));
            }else if(key == "y"){
                widget->setPosition(Vec2(widget->getPosition().x, valueToFloat(value)));
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
                stExpCocoNode *layoutCocosNode = stChildArray[i].GetChildArray();
                
                ui::LinearLayoutParameter *linearParameter = ui::LinearLayoutParameter::create();
                ui::RelativeLayoutParameter *relativeParameter = ui::RelativeLayoutParameter::create();
                ui::Margin mg;
                
                int paramType = -1;
                for (int j = 0; j < stChildArray[i].GetChildNum(); ++j) {
                    std::string innerKey = layoutCocosNode[j].GetName(pCocoLoader);
                    std::string innerValue = layoutCocosNode[j].GetValue();
                    
                    if (innerKey == "type") {
                        paramType = valueToInt(innerValue);
                    }else if(innerKey == "gravity"){
                        linearParameter->setGravity((cocos2d::ui::LinearLayoutParameter::LinearGravity)valueToInt(innerValue));
                    }else if(innerKey == "relativeName"){
                        relativeParameter->setRelativeName(innerValue);
                    }else if(innerKey == "relativeToName"){
                        relativeParameter->setRelativeToWidgetName(innerValue);
                    }else if(innerKey == "align"){
                        relativeParameter->setAlign((cocos2d::ui::RelativeLayoutParameter::RelativeAlign)valueToInt(innerValue));
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
    
}



