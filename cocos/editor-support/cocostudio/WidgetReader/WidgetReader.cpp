

#include "WidgetReader.h"
#include "cocostudio/CocoLoader.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;



namespace cocostudio
{
    
    
    const char* P_IgnoreSize = "ignoreSize";
    const char* P_SizeType = "sizeType";
    const char* P_PositionType = "positionType";
    const char* P_SizePercentX = "sizePercentX";
    const char* P_SizePercentY = "sizePercentY";
    const char* P_PositionPercentX = "positionPercentX";
    const char* P_PositionPercentY = "positionPercentY";
    const char* P_AdaptScreen = "adaptScreen";
    const char* P_Width = "width";
    const char* P_Height = "height";
    const char* P_Tag = "tag";
    const char* P_ActionTag = "actiontag";
    const char* P_TouchAble = "touchAble";
    const char* P_Name = "name";
    const char* P_X = "x";
    const char* P_Y = "y";
    const char* P_ScaleX = "scaleX";
    const char* P_ScaleY = "scaleY";
    const char* P_Rotation = "rotation";
    const char* P_Visbile = "visible";
    const char* P_ZOrder = "ZOrder";
    const char* P_LayoutParameter = "layoutParameter";
    const char* P_Type = "type";
    const char* P_Gravity = "gravity";
    const char* P_RelativeName = "relativeName";
    const char* P_RelativeToName = "relativeToName";
    const char* P_Align = "align";
    const char* P_MarginLeft = "marginLeft";
    const char* P_MarginRight = "marginRight";
    const char* P_MarginTop = "marginTop";
    const char* P_MarginDown = "marginDown";
    
    const char* P_Opacity = "opacity";
    const char* P_ColorR = "colorR";
    const char* P_ColorG = "colorG";
    const char* P_ColorB = "colorB";
    const char* P_FlipX = "flipX";
    const char* P_FlipY = "flipY";
    const char* P_AnchorPointX = "anchorPointX";
    const char* P_AnchorPointY = "anchorPointY";
    
    
    const char* P_ResourceType = "resourceType";
    const char* P_Path = "path";

    
    static WidgetReader* instanceWidgetReader = nullptr;
    
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
        valueToInt = [=](const std::string& str) -> int{
            return atoi(str.c_str());
        };
        
        valueToBool = [=](const std::string& str) -> bool{
            int intValue = valueToInt(str);
            if (1 == intValue) {
                return true;
            }else{
                return false;
            }
        };
        
        valueToFloat = [=](const std::string& str) -> float{
            return utils::atof(str.c_str());
        };
    }
    
    WidgetReader::~WidgetReader()
   
    {
        
    }
    
    WidgetReader* WidgetReader::getInstance()
    {
        if (!instanceWidgetReader)
        {
            instanceWidgetReader = new (std::nothrow) WidgetReader();
        }
        return instanceWidgetReader;
    }
    
    void WidgetReader::purge()
    {
        CC_SAFE_DELETE(instanceWidgetReader);
    }
    
    void WidgetReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {        
   
        bool ignoreSizeExsit = DICTOOL->checkObjectExist_json(options, P_IgnoreSize);
        if (ignoreSizeExsit) {
            widget->ignoreContentAdaptWithSize(DICTOOL->getBooleanValue_json(options, P_IgnoreSize));
        }
        
        widget->setSizeType((Widget::SizeType)DICTOOL->getIntValue_json(options, P_SizeType));
        widget->setPositionType((Widget::PositionType)DICTOOL->getIntValue_json(options, P_PositionType));
        
        widget->setSizePercent(Vec2(DICTOOL->getFloatValue_json(options, P_SizePercentX), DICTOOL->getFloatValue_json(options, P_SizePercentY)));
        widget->setPositionPercent(Vec2(DICTOOL->getFloatValue_json(options, P_PositionPercentX), DICTOOL->getFloatValue_json(options, P_PositionPercentY)));
        
        /* adapt screen */
        float w = 0, h = 0;
        bool adaptScrenn = DICTOOL->getBooleanValue_json(options, P_AdaptScreen);
        if (adaptScrenn)
        {
            Size screenSize = CCDirector::getInstance()->getWinSize();
            w = screenSize.width;
            h = screenSize.height;
        }
        else
        {
            w = DICTOOL->getFloatValue_json(options, P_Width);
            h = DICTOOL->getFloatValue_json(options, P_Height);
        }
        widget->setContentSize(Size(w, h));
        
        widget->setTag(DICTOOL->getIntValue_json(options, P_Tag));
        widget->setActionTag(DICTOOL->getIntValue_json(options, P_ActionTag));
        widget->setTouchEnabled(DICTOOL->getBooleanValue_json(options, P_TouchAble));
        const char* name = DICTOOL->getStringValue_json(options, P_Name);
        const char* widgetName = name?name:"default";
        widget->setName(widgetName);
        
        float x = DICTOOL->getFloatValue_json(options, P_X);
        float y = DICTOOL->getFloatValue_json(options, P_Y);
        widget->setPosition(Vec2(x,y));
      
        widget->setScaleX(DICTOOL->getFloatValue_json(options, P_ScaleX,1.0));
        
       
        widget->setScaleY(DICTOOL->getFloatValue_json(options, P_ScaleY,1.0));
        
      
        widget->setRotation(DICTOOL->getFloatValue_json(options, P_Rotation,0));
        
        bool vb = DICTOOL->checkObjectExist_json(options, P_Visbile);
        if (vb)
        {
            widget->setVisible(DICTOOL->getBooleanValue_json(options, P_Visbile));
        }
        int z = DICTOOL->getIntValue_json(options, P_ZOrder);
        widget->setLocalZOrder(z);
        
        bool layout = DICTOOL->checkObjectExist_json(options, P_LayoutParameter);
        if (layout)
        {
            const rapidjson::Value& layoutParameterDic = DICTOOL->getSubDictionary_json(options, P_LayoutParameter);
            int paramType = DICTOOL->getIntValue_json(layoutParameterDic, P_Type);
            LayoutParameter* parameter = nullptr;
            switch (paramType)
            {
                case 0:
                    break;
                case 1:
                {
                    parameter = LinearLayoutParameter::create();
                    int gravity = DICTOOL->getIntValue_json(layoutParameterDic, P_Gravity);
                    ((LinearLayoutParameter*)parameter)->setGravity((cocos2d::ui::LinearLayoutParameter::LinearGravity)gravity);
                    break;
                }
                case 2:
                {
                    parameter = RelativeLayoutParameter::create();
                    RelativeLayoutParameter* rParameter = (RelativeLayoutParameter*)parameter;
                    const char* relativeName = DICTOOL->getStringValue_json(layoutParameterDic, P_RelativeName);
                    rParameter->setRelativeName(relativeName);
                    const char* relativeToName = DICTOOL->getStringValue_json(layoutParameterDic, P_RelativeToName);
                    rParameter->setRelativeToWidgetName(relativeToName);
                    int align = DICTOOL->getIntValue_json(layoutParameterDic, P_Align);
                    rParameter->setAlign((cocos2d::ui::RelativeLayoutParameter::RelativeAlign)align);
                    break;
                }
                default:
                    break;
            }
            if (parameter)
            {
                float mgl = DICTOOL->getFloatValue_json(layoutParameterDic, P_MarginLeft);
                float mgt = DICTOOL->getFloatValue_json(layoutParameterDic, P_MarginTop);
                float mgr = DICTOOL->getFloatValue_json(layoutParameterDic, P_MarginRight);
                float mgb = DICTOOL->getFloatValue_json(layoutParameterDic, P_MarginDown);
                parameter->setMargin(Margin(mgl, mgt, mgr, mgb));
                widget->setLayoutParameter(parameter);
            }
        }
    }
    
    void WidgetReader::setColorPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        bool op = DICTOOL->checkObjectExist_json(options, P_Opacity);
        if (op)
        {
            widget->setOpacity(DICTOOL->getIntValue_json(options, P_Opacity));
        }
        bool cr = DICTOOL->checkObjectExist_json(options, P_ColorR);
        bool cg = DICTOOL->checkObjectExist_json(options, P_ColorG);
        bool cb = DICTOOL->checkObjectExist_json(options, P_ColorB);
        int colorR = cr ? DICTOOL->getIntValue_json(options, P_ColorR) : 255;
        int colorG = cg ? DICTOOL->getIntValue_json(options, P_ColorG) : 255;
        int colorB = cb ? DICTOOL->getIntValue_json(options, P_ColorB) : 255;
        widget->setColor(Color3B(colorR, colorG, colorB));
        
        this->setAnchorPointForWidget(widget, options);
        
        bool flipX = DICTOOL->getBooleanValue_json(options, P_FlipX);
        bool flipY = DICTOOL->getBooleanValue_json(options, P_FlipY);
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
        //the setSize method will be conflict with scale9Width & scale9Height
        if (!widget->isIgnoreContentAdaptWithSize()) {
            widget->setContentSize(Size(_width, _height));
        }
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
    
    std::string WidgetReader::getResourcePath(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, cocos2d::ui::Widget::TextureResType texType)
    {
        stExpCocoNode *backGroundChildren = cocoNode->GetChildArray(cocoLoader);
        std::string backgroundValue = backGroundChildren[0].GetValue(cocoLoader);

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
        bool isAnchorPointXExists = DICTOOL->checkObjectExist_json(options, P_AnchorPointX);
        float anchorPointXInFile;
        if (isAnchorPointXExists) {
            anchorPointXInFile = DICTOOL->getFloatValue_json(options, P_AnchorPointX);
        }else{
            anchorPointXInFile = widget->getAnchorPoint().x;
        }
        
        bool isAnchorPointYExists = DICTOOL->checkObjectExist_json(options, P_AnchorPointY);
        float anchorPointYInFile;
        if (isAnchorPointYExists) {
            anchorPointYInFile = DICTOOL->getFloatValue_json(options, P_AnchorPointY);
        }
        else{
            anchorPointYInFile = widget->getAnchorPoint().y;
        }
        
        if (isAnchorPointXExists || isAnchorPointYExists) {
            widget->setAnchorPoint(Vec2(anchorPointXInFile, anchorPointYInFile));
        }
    }
    
    void WidgetReader::setPropsFromBinary(cocos2d::ui::Widget *widget, cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode)
    {
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        this->beginSetBasicProperties(widget);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            CC_BASIC_PROPERTY_BINARY_READER
        }
        
        this->endSetBasicProperties(widget);
    }
    
}



