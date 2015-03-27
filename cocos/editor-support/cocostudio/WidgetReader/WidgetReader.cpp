

#include "WidgetReader.h"

#include "cocostudio/CocoLoader.h"
#include "ui/UIButton.h"
#include "../ActionTimeline/CCActionTimeline.h"
#include "cocostudio/CCObjectExtensionData.h"
#include "cocostudio/CSParseBinary_generated.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"
#include "ui/UILayoutComponent.h"
#include "cocostudio/ActionTimeline/CSLoader.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;
/**/



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

    const char* P_Layout_PositionPercentXEnabled = "PositionPercentXEnabled";
    const char* P_Layout_PositionPercentYEnabled = "PositionPercentYEnabled";
    const char* P_Layout_PercentWidthEnable = "PercentWidthEnabled";
    const char* P_Layout_PercentHeightEnable = "PercentHeightEnabled";
    const char* P_Layout_StretchWidthEnable = "StretchWidthEnable";
    const char* P_Layout_StretchHeightEnable = "StretchHeightEnable";
    const char* P_Layout_HorizontalEdge = "HorizontalEdge";
    const char* P_Layout_VerticalEdge = "VerticalEdge";
    const char* P_Layout_LeftMargin = "LeftMargin";
    const char* P_Layout_RightMargin = "RightMargin";
    const char* P_Layout_TopMargin = "TopMargin";
    const char* P_Layout_BottomMargin = "BottomMargin";
    const char* P_Layout_BothEdge = "BothEdge";
    const char* P_Layout_LeftEdge = "LeftEdge";
    const char* P_Layout_RightEdge = "RightEdge";
    const char* P_Layout_TopEdge = "TopEdge";
    const char* P_Layout_BottomEdge = "BottomEdge";

    
    static WidgetReader* instanceWidgetReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(WidgetReader)
    
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
    
    Offset<Table> WidgetReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData, flatbuffers::FlatBufferBuilder *builder)
    {
        std::string name = "";
        long actionTag = 0;
        Vec2 rotationSkew = Vec2::ZERO;
        int zOrder = 0;
        bool visible = true;
        GLubyte alpha = 255;
        int tag = 0;
        Vec2 position = Vec2::ZERO;
        Vec2 scale = Vec2(1.0f, 1.0f);
        Vec2 anchorPoint = Vec2::ZERO;
        Color4B color(255, 255, 255, 255);
        Vec2 size = Vec2::ZERO;
        bool flipX = false;
        bool flipY = false;
        bool ignoreSize = false;
        bool touchEnabled = false;
        std::string frameEvent = "";
        std::string customProperty = "";
        std::string callbackType = "";
        std::string callbackName = "";

        bool positionXPercentEnabled = false;
        bool positionYPercentEnabled = false;
        float positionXPercent = 0;
        float positionYPercent = 0;
        bool sizeXPercentEnable = false;
        bool sizeYPercentEnable = false;
        float sizeXPercent = 0;
        float sizeYPercent = 0;
        bool stretchHorizontalEnabled = false;
        bool stretchVerticalEnabled = false;
        std::string horizontalEdge;
        std::string verticalEdge;
        float leftMargin = 0;
        float rightMargin = 0;
        float topMargin = 0;
        float bottomMargin = 0;
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if (attriname == "Name")
            {
                name = value;
            }
            else if (attriname == "ActionTag")
            {
                actionTag = atol(value.c_str());
            }
            else if (attriname == "RotationSkewX")
            {
                rotationSkew.x = atof(value.c_str());
            }
            else if (attriname == "RotationSkewY")
            {
                rotationSkew.y = atof(value.c_str());
            }
            else if (attriname == "Rotation")
            {
                //            rotation = atoi(value.c_str());
            }
            else if (attriname == "FlipX")
            {
                flipX = (value == "True") ? true : false;
            }
            else if (attriname == "FlipY")
            {
                flipY = (value == "True") ? true : false;
            }
            else if (attriname == "ZOrder")
            {
                zOrder = atoi(value.c_str());
            }
            else if (attriname == "Visible")
            {
                //            visible = (value == "True") ? true : false;
            }
            else if (attriname == "VisibleForFrame")
            {
                visible = (value == "True") ? true : false;
            }
            else if (attriname == "Alpha")
            {
                alpha = atoi(value.c_str());
            }
            else if (attriname == "Tag")
            {
                tag = atoi(value.c_str());
            }
            else if (attriname == "TouchEnable")
            {
                touchEnabled = (value == "True") ? true : false;
            }
            else if (attriname == "UserData")
            {
                customProperty = value;
            }
            else if (attriname == "FrameEvent")
            {
                frameEvent = value;
            }
            else if (attriname == "CallBackType")
            {
                callbackType = value;
            }
            else if (attriname == "CallBackName")
            {
                callbackName = value;
            }
            else if (attriname == P_Layout_PositionPercentXEnabled)
            {
                positionXPercentEnabled = value == "True";
            }
            else if (attriname == P_Layout_PositionPercentYEnabled)
            {
                positionYPercentEnabled = value == "True";
            }
            else if (attriname == P_Layout_PercentWidthEnable)
            {
                sizeXPercentEnable = value == "True";
            }
            else if (attriname == P_Layout_PercentHeightEnable)
            {
                sizeYPercentEnable = value == "True";
            }
            else if (attriname == P_Layout_StretchWidthEnable)
            {
                stretchHorizontalEnabled = value == "True";
            }
            else if (attriname == P_Layout_StretchHeightEnable)
            {
                stretchVerticalEnabled = value == "True";
            }
            else if (attriname == P_Layout_HorizontalEdge)
            {
                horizontalEdge = value;
            }
            else if (attriname == P_Layout_VerticalEdge)
            {
                verticalEdge = value;
            }
            else if (attriname == P_Layout_LeftMargin)
            {
                leftMargin = atof(value.c_str());
            }
            else if (attriname == P_Layout_RightMargin)
            {
                rightMargin = atof(value.c_str());
            }
            else if (attriname == P_Layout_TopMargin)
            {
                topMargin = atof(value.c_str());
            }
            else if (attriname == P_Layout_BottomMargin)
            {
                bottomMargin = atof(value.c_str());
            }

            attribute = attribute->Next();
        }
        
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string attriname = child->Name();
            if (attriname == "Children")
            {
                break;
            }
            else if (attriname == "Position")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "X")
                    {
                        position.x = atof(value.c_str());
                    }
                    else if (attriname == "Y")
                    {
                        position.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (attriname == "Scale")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "ScaleX")
                    {
                        scale.x = atof(value.c_str());
                    }
                    else if (attriname == "ScaleY")
                    {
                        scale.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (attriname == "AnchorPoint")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "ScaleX")
                    {
                        anchorPoint.x = atof(value.c_str());
                    }
                    else if (attriname == "ScaleY")
                    {
                        anchorPoint.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (attriname == "CColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "A")
                    {
                        color.a = atoi(value.c_str());
                    }
                    else if (attriname == "R")
                    {
                        color.r = atoi(value.c_str());
                    }
                    else if (attriname == "G")
                    {
                        color.g = atoi(value.c_str());
                    }
                    else if (attriname == "B")
                    {
                        color.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (attriname == "Size")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "X")
                    {
                        size.x = atof(value.c_str());
                    }
                    else if (attriname == "Y")
                    {
                        size.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (attriname == "PrePosition")
            {
                attribute = child->FirstAttribute();

                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();

                    if (attriname == "X")
                    {
                        positionXPercent = atof(value.c_str());
                    }
                    else if (attriname == "Y")
                    {
                        positionYPercent = atof(value.c_str());
                    }

                    attribute = attribute->Next();
                }
            }
            else if (attriname == "PreSize")
            {
                attribute = child->FirstAttribute();

                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();

                    if (attriname == "X")
                    {
                        sizeXPercent = atof(value.c_str());
                    }
                    else if (attriname == "Y")
                    {
                        sizeYPercent = atof(value.c_str());
                    }

                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        RotationSkew f_rotationskew(rotationSkew.x, rotationSkew.y);
        Position f_position(position.x, position.y);
        Scale f_scale(scale.x, scale.y);
        AnchorPoint f_anchortpoint(anchorPoint.x, anchorPoint.y);
        Color f_color(color.a, color.r, color.g, color.b);
        FlatSize f_size(size.x, size.y);
        auto f_layoutComponent = CreateLayoutComponentTable(*builder,
                                                            positionXPercentEnabled,
                                                            positionYPercentEnabled,
                                                            positionXPercent,
                                                            positionYPercent,
                                                            sizeXPercentEnable,
                                                            sizeYPercentEnable,
                                                            sizeXPercent,
                                                            sizeYPercent,
                                                            stretchHorizontalEnabled,
                                                            stretchVerticalEnabled,
                                                            builder->CreateString(horizontalEdge),
                                                            builder->CreateString(verticalEdge),
                                                            leftMargin,
                                                            rightMargin,
                                                            topMargin,
                                                            bottomMargin);
        
        auto options = CreateWidgetOptions(*builder,
                                           builder->CreateString(name),
                                           (int32_t)actionTag,
                                           &f_rotationskew,
                                           zOrder,
                                           visible,
                                           alpha,
                                           tag,
                                           &f_position,
                                           &f_scale,
                                           &f_anchortpoint,
                                           &f_color,
                                           &f_size,
                                           flipX,
                                           flipY,
                                           ignoreSize,
                                           touchEnabled,
                                           builder->CreateString(frameEvent),
                                           builder->CreateString(customProperty),
                                           builder->CreateString(callbackType),
                                           builder->CreateString(callbackName),
                                           f_layoutComponent);
        
        return *(Offset<Table>*)(&options);
    }
    
    void WidgetReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *widgetOptions)
    {
        Widget* widget = static_cast<Widget*>(node);
        
        auto options = (WidgetOptions*)widgetOptions;
        
        widget->setCascadeColorEnabled(true);
        widget->setCascadeOpacityEnabled(true);
        widget->setAnchorPoint(Vec2::ZERO);
        
        widget->setUnifySizeEnabled(true);
        bool ignoreSize = options->ignoreSize() != 0;
        widget->ignoreContentAdaptWithSize(ignoreSize);

        widget->setUnifySizeEnabled(false);
        widget->setLayoutComponentEnabled(true);
        widget->ignoreContentAdaptWithSize(false);
        Size contentSize(options->size()->width(), options->size()->height());
        widget->setContentSize(contentSize);
        
        int tag = options->tag();
        widget->setTag(tag);
        
        int actionTag = options->actionTag();
        widget->setActionTag(actionTag);
        
        std::string customProperty = options->customProperty()->c_str();
        
        ObjectExtensionData* extensionData = ObjectExtensionData::create();
        extensionData->setCustomProperty(customProperty);
        extensionData->setActionTag(actionTag);
        node->setUserObject(extensionData);
        
        bool touchEnabled = options->touchEnabled() != 0;
        widget->setTouchEnabled(touchEnabled);
        
        std::string name = options->name()->c_str();
        widget->setName(name);
        
        Vec2 position(options->position()->x(), options->position()->y());
        widget->setPosition(position);
        
        float scaleX = options->scale()->scaleX();
        widget->setScaleX(scaleX);
        float scaleY = options->scale()->scaleY();
        widget->setScaleY(scaleY);
        
        float rotationSkewX = options->rotationSkew()->rotationSkewX();
        widget->setRotationSkewX(rotationSkewX);
        float rotationSkewY = options->rotationSkew()->rotationSkewY();
        widget->setRotationSkewY(rotationSkewY);
        
        bool visible = options->visible() != 0;
        widget->setVisible(visible);
        
        int zOrder = options->zOrder();
        widget->setLocalZOrder(zOrder);
        
        auto f_color = options->color();
        Color3B color(f_color->r(), f_color->g(), f_color->b());
        widget->setColor(color);
        
        int alpha = options->alpha();
        widget->setOpacity(alpha);
        
        auto f_anchorPoint = options->anchorPoint();
        Vec2 anchorPoint(f_anchorPoint->scaleX(), f_anchorPoint->scaleY());
        widget->setAnchorPoint(anchorPoint);
        
        bool flippedX = options->flipX() != 0;
        widget->setFlippedX(flippedX);
        bool flippedY = options->flipY() != 0;
        widget->setFlippedY(flippedY);
        
        std::string callbackType = options->callBackType()->c_str();
        widget->setCallbackType(callbackType);
        std::string callbackName = options->callBackName()->c_str();
        widget->setCallbackName(callbackName);
        
        setLayoutComponentPropsWithFlatBuffers(widget, widgetOptions);
    }

    void WidgetReader::setLayoutComponentPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* nodeOptions)
    {
        auto layoutComponentTable = ((WidgetOptions*)nodeOptions)->layoutComponent();
        if (!layoutComponentTable) return;

        auto layoutComponent = ui::LayoutComponent::bindLayoutComponent(node);

        bool positionXPercentEnabled = layoutComponentTable->positionXPercentEnabled() != 0;
        bool positionYPercentEnabled = layoutComponentTable->positionYPercentEnabled() != 0;
        float positionXPercent = layoutComponentTable->positionXPercent();
        float positionYPercent = layoutComponentTable->positionYPercent();
        bool sizeXPercentEnable = layoutComponentTable->sizeXPercentEnable() != 0;
        bool sizeYPercentEnable = layoutComponentTable->sizeYPercentEnable() != 0;
        float sizeXPercent = layoutComponentTable->sizeXPercent();
        float sizeYPercent = layoutComponentTable->sizeYPercent();
        bool stretchHorizontalEnabled = layoutComponentTable->stretchHorizontalEnabled() != 0;
        bool stretchVerticalEnabled = layoutComponentTable->stretchVerticalEnabled() != 0;
        std::string horizontalEdge = layoutComponentTable->horizontalEdge()->c_str();
        std::string verticalEdge = layoutComponentTable->verticalEdge()->c_str();
        float leftMargin = layoutComponentTable->leftMargin();
        float rightMargin = layoutComponentTable->rightMargin();
        float topMargin = layoutComponentTable->topMargin();
        float bottomMargin = layoutComponentTable->bottomMargin();

        layoutComponent->setPositionPercentXEnabled(positionXPercentEnabled);
        layoutComponent->setPositionPercentYEnabled(positionYPercentEnabled);
        layoutComponent->setPositionPercentX(positionXPercent);
        layoutComponent->setPositionPercentY(positionYPercent);
        layoutComponent->setPercentWidthEnabled(sizeXPercentEnable);
        layoutComponent->setPercentHeightEnabled(sizeYPercentEnable);
        layoutComponent->setPercentWidth(sizeXPercent);
        layoutComponent->setPercentHeight(sizeYPercent);
        layoutComponent->setStretchWidthEnabled(stretchHorizontalEnabled);
        layoutComponent->setStretchHeightEnabled(stretchVerticalEnabled);
        ui::LayoutComponent::HorizontalEdge horizontalEdgeType = ui::LayoutComponent::HorizontalEdge::None;
        if (horizontalEdge == P_Layout_LeftEdge)
        {
            horizontalEdgeType = ui::LayoutComponent::HorizontalEdge::Left;
        }
        else if (horizontalEdge == P_Layout_RightEdge)
        {
            horizontalEdgeType = ui::LayoutComponent::HorizontalEdge::Right;
        }
        else if (horizontalEdge == P_Layout_BothEdge)
        {
            horizontalEdgeType = ui::LayoutComponent::HorizontalEdge::Center;
        }
        layoutComponent->setHorizontalEdge(horizontalEdgeType);
        ui::LayoutComponent::VerticalEdge verticalEdgeType = ui::LayoutComponent::VerticalEdge::None;
        if (verticalEdge == P_Layout_TopEdge)
        {
            verticalEdgeType = ui::LayoutComponent::VerticalEdge::Top;
        }
        else if (verticalEdge == P_Layout_BottomEdge)
        {
            verticalEdgeType = ui::LayoutComponent::VerticalEdge::Bottom;
        }
        else if (verticalEdge == P_Layout_BothEdge)
        {
            verticalEdgeType = ui::LayoutComponent::VerticalEdge::Center;
        }
        layoutComponent->setVerticalEdge(verticalEdgeType);

        layoutComponent->setTopMargin(topMargin);
        layoutComponent->setBottomMargin(bottomMargin);
        layoutComponent->setLeftMargin(leftMargin);
        layoutComponent->setRightMargin(rightMargin);
    }
    
    Node* WidgetReader::createNodeWithFlatBuffers(const flatbuffers::Table *widgetOptions)
    {
        Widget* widget = Widget::create();
        
        setPropsWithFlatBuffers(widget, (Table*)widgetOptions);
        
        return widget;
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



