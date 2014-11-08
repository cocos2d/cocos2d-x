

#include "WidgetReader.h"
#include "cocostudio/CocoLoader.h"
#include "ui/UIButton.h"
#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"
#include "../ActionTimeline/CCActionTimeline.h"

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
    _positionPercentX(0.0f),
    _positionPercentY(0.0f),
    _width(0.0f),
    _height(0.0f),
    _opacity(255),
    _isAdaptScreen(false)
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
    
    void WidgetReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        
        const protocolbuffers::WidgetOptions& options = nodeTree.widgetoptions();
        
        widget->setCascadeColorEnabled(true);
        widget->setCascadeOpacityEnabled(true);
        widget->setAnchorPoint(Vec2::ZERO);
        
        widget->setUnifySizeEnabled(true);
        
        bool ignoreSizeExsit = options.has_ignoresize();
        if (ignoreSizeExsit)
        {
            widget->ignoreContentAdaptWithSize(options.ignoresize());
        }
        
        widget->setSizeType((Widget::SizeType)options.sizetype());
        widget->setPositionType((Widget::PositionType)options.positiontype());
        
        widget->setSizePercent(Vec2(options.sizepercentx(), options.sizepercenty()));
        widget->setPositionPercent(Vec2(options.positionpercentx(), options.positionpercenty()));
        
        float w = options.width();
        float h = options.height();
        widget->setContentSize(Size(w, h));
        
        widget->setTag(options.tag());
        widget->setActionTag(options.actiontag());
        widget->setTouchEnabled(options.touchable());
        const char* name = options.name().c_str();
        const char* widgetName = name ? name : "default";
        widget->setName(widgetName);
        
        float x = options.x();
        float y = options.y();
        widget->setPosition(Vec2(x, y));
        
		if(options.has_alpha())
		{
			widget->setOpacity(options.alpha());
		}
        
        widget->setScaleX(options.has_scalex() ? options.scalex() : 1.0);
        
        
        widget->setScaleY(options.has_scaley() ? options.scaley() : 1.0);

		widget->setRotationSkewX(options.has_rotationskewx() ? options.rotationskewx() : 0.0);

		widget->setRotationSkewY(options.has_rotationskewy() ? options.rotationskewy() : 0.0);
        
        bool vb = options.has_visible();
        if (vb)
        {
            widget->setVisible(options.visible());
        }
        
        int z = options.zorder();
        widget->setLocalZOrder(z);        
        
        
        bool layout = options.has_layoutparameter();
        if (layout)
        {
            
            const protocolbuffers::LayoutParameter& layoutParameterDic = options.layoutparameter();;
            int paramType = layoutParameterDic.type();
            
            LayoutParameter* parameter = nullptr;
            switch (paramType)
            {
                case 0:
                    break;
                case 1:
                {
                    parameter = LinearLayoutParameter::create();
                    int gravity = layoutParameterDic.gravity();
                    ((LinearLayoutParameter*)parameter)->setGravity((cocos2d::ui::LinearLayoutParameter::LinearGravity)gravity);
                    break;
                }
                case 2:
                {
                    parameter = RelativeLayoutParameter::create();
                    RelativeLayoutParameter* rParameter = (RelativeLayoutParameter*)parameter;
                    const char* relativeName = layoutParameterDic.relativename().c_str();
                    rParameter->setRelativeName(relativeName);
                    const char* relativeToName = layoutParameterDic.relativetoname().c_str();
                    rParameter->setRelativeToWidgetName(relativeToName);
                    int align = layoutParameterDic.align();
                    rParameter->setAlign((cocos2d::ui::RelativeLayoutParameter::RelativeAlign)align);
                    break;
                }
                default:
                    break;
            }
            if (parameter)
            {
                float mgl = layoutParameterDic.marginleft();
                float mgt = layoutParameterDic.margintop();
                float mgr = layoutParameterDic.marginright();
                float mgb = layoutParameterDic.margindown();
                parameter->setMargin(Margin(mgl, mgt, mgr, mgb));
                widget->setLayoutParameter(parameter);
            }
        }
        
    }
    
    void WidgetReader::setColorPropsFromProtocolBuffers(cocos2d::ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        const protocolbuffers::WidgetOptions& options = nodeTree.widgetoptions();
        
       
        bool isColorRExists = options.has_colorr();
        bool isColorGExists = options.has_colorg();
        bool isColorBExists = options.has_colorb();
        
        int colorR = options.colorr();
        int colorG = options.colorg();
        int colorB = options.colorb();
        
        if (isColorRExists && isColorGExists && isColorBExists)
        {
            widget->setColor(Color3B(colorR, colorG, colorB));
        }
        
        setAnchorPointForWidget(widget, nodeTree);
        
        bool flipX = options.flipx();
        bool flipY = options.flipy();
        if (flipX)
        {
            widget->setFlippedX(flipX);
        }
        if (flipY)
        {
            widget->setFlippedY(flipY);
        }
    }
    
    void WidgetReader::setPropsFromXML(cocos2d::ui::Widget *widget, const tinyxml2::XMLElement *objectData)
    {
        widget->setTouchEnabled(false);
        
        widget->setCascadeColorEnabled(true);
        widget->setCascadeOpacityEnabled(true);
        
        widget->setUnifySizeEnabled(true);
        
        widget->setScale(0.0f, 0.0f);
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "Name")
            {
                const char* widgetName = value.c_str() ? value.c_str() :"default";
                widget->setName(widgetName);
            }
            else if (name == "ActionTag")
            {
                int actionTag = atoi(value.c_str());
                widget->setUserObject(timeline::ActionTimelineData::create(actionTag));
            }
            else if (name == "RotationSkewX")
            {
                widget->setRotationSkewX(atof(value.c_str()));
            }
            else if (name == "RotationSkewY")
            {
                widget->setRotationSkewY(atof(value.c_str()));
            }
            else if (name == "ZOrder")
            {
                widget->setLocalZOrder(atoi(value.c_str()));
            }
            else if (name == "VisibleForFrame")
            {
                widget->setVisible((value == "True") ? true : false);
            }
            else if (name == "Alpha")
            {
                widget->setOpacity(atoi(value.c_str()));
            }
            else if (name == "Tag")
            {
                widget->setTag(atoi(value.c_str()));
            }
            else if (name == "FlipX")
            {
                widget->setFlippedX((value == "True") ? true : false);
            }
            else if (name == "FlipY")
            {
                widget->setFlippedY((value == "True") ? true : false);
            }
            else if (name == "TouchEnable")
            {
                widget->setTouchEnabled((value == "True") ? true : false);
            }
            else if (name == "ControlSizeType")
            {
                widget->ignoreContentAdaptWithSize((value == "Auto") ? true : false);
            }
            
            attribute = attribute->Next();
        }
        
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            if (name == "Children")
            {
                break;
            }
            else if (name == "Position")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "X")
                    {
                        widget->setPositionX(atof(value.c_str()));
                    }
                    else if (name == "Y")
                    {
                        widget->setPositionY(atof(value.c_str()));
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "Scale")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "ScaleX")
                    {
                        widget->setScaleX(atof(value.c_str()));
                    }
                    else if (name == "ScaleY")
                    {
                        widget->setScaleY(atof(value.c_str()));
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "AnchorPoint")
            {
                attribute = child->FirstAttribute();
                float anchor_x = 0.0f, anchor_y = 0.0f;
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "ScaleX")
                    {
                        anchor_x = atof(value.c_str());
                    }
                    else if (name == "ScaleY")
                    {
                        anchor_y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
                
                widget->setAnchorPoint(Vec2(anchor_x, anchor_y));
            }
            else if (name == "CColor")
            {
                attribute = child->FirstAttribute();
                int red = 255, green = 255, blue = 255;
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "A")
                    {
                        widget->setOpacity(atoi(value.c_str()));
                    }
                    else if (name == "R")
                    {
                        red = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        green = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        blue = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
                
                widget->setColor(Color3B(red, green, blue));
            }
            else if (name == "Size")
            {
                attribute = child->FirstAttribute();
                float width = 0.0f, height = 0.0f;
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "X")
                    {
                        width = atof(value.c_str());
                    }
                    else if (name == "Y")
                    {
                        height = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
                
                widget->setContentSize(Size(width, height));
            }
            
            child = child->NextSiblingElement();
        }
        
    }
    
    void WidgetReader::setAnchorPointForWidget(cocos2d::ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        const protocolbuffers::WidgetOptions& options = nodeTree.widgetoptions();
        
        bool isAnchorPointXExists = options.has_anchorpointx();
        float anchorPointXInFile;
        if (isAnchorPointXExists)
        {
            anchorPointXInFile = options.anchorpointx();
        }
        else
        {
            anchorPointXInFile = widget->getAnchorPoint().x;
        }
        
        bool isAnchorPointYExists = options.has_anchorpointy();
        float anchorPointYInFile;
        if (isAnchorPointYExists)
        {
            anchorPointYInFile = options.anchorpointy();
        }
        else
        {
            anchorPointYInFile = widget->getAnchorPoint().y;
        }
        
        if (isAnchorPointXExists || isAnchorPointYExists)
        {
            widget->setAnchorPoint(Vec2(anchorPointXInFile, anchorPointYInFile));
        }
    }
    
    std::string WidgetReader::getResourcePath(const std::string &path, cocos2d::ui::Widget::TextureResType texType)
    {
        std::string filePath = GUIReader::getInstance()->getFilePath();
        const char* imageFileName = path.c_str();
        std::string imageFileName_tp;
        if (nullptr != imageFileName && 0 != strcmp("", imageFileName))
        {
            if (texType == ui::Widget::TextureResType::LOCAL) {
                imageFileName_tp = filePath + imageFileName;
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
    
}



