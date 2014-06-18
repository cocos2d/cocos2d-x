

#include "ButtonReader.h"
#include "ui/UIButton.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static ButtonReader* instanceButtonReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(ButtonReader)
    
    ButtonReader::ButtonReader()
    {
        
    }
    
    ButtonReader::~ButtonReader()
    {
        
    }
    
    ButtonReader* ButtonReader::getInstance()
    {
        if (!instanceButtonReader)
        {
            instanceButtonReader = new ButtonReader();
        }
        return instanceButtonReader;
    }
    
    void ButtonReader::purge()
    {
        CC_SAFE_DELETE(instanceButtonReader);
    }
    
    void ButtonReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
        
        Button *button = static_cast<Button*>(widget);
        
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        
        this->beginSetBasicProperties(widget);
        
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        int cri = 255, cgi = 255, cbi = 255;
        float scale9Width = 0.0f, scale9Height = 0.0f;
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
//            CCLOG("Button: key = %s, value = %d", key.c_str(), i);

            if (key == "ignoreSize") {
                widget->ignoreContentAdaptWithSize(valueToBool(value));
            }else if(key == "sizeType"){
                widget->setSizeType((Widget::SizeType)valueToInt(value));
            }else if(key == "positionType"){
                widget->setPositionType((Widget::PositionType)valueToInt(value));
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
                widget->setName(widgetName);
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
                stExpCocoNode *layoutCocosNode = stChildArray[i].GetChildArray();
                
                LinearLayoutParameter *linearParameter = LinearLayoutParameter::create();
                RelativeLayoutParameter *relativeParameter = RelativeLayoutParameter::create();
                Margin mg;
                
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
            
            else if (key == "opacity") {
                _opacity = valueToInt(value);
            }else if(key == "colorR"){
                _color.r = valueToInt(value);
            }else if(key == "colorG"){
                _color.g = valueToInt(value);
            }else if(key == "colorB")
            {
                _color.b = valueToInt(value);
            }else if(key == "flipX"){
                widget->setFlippedX(valueToBool(value));
            }else if(key == "flipY"){
                widget->setFlippedY(valueToBool(value));
            }else if(key == "anchorPointX"){
                _originalAnchorPoint.x = valueToFloat(value);
            }else if(key == "anchorPointY"){
                _originalAnchorPoint.y = valueToFloat(value);
            }
            else if (key == "scale9Enable") {
                button->setScale9Enabled(valueToBool(value));
            }
            else if (key == "normalData"){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTextureNormal(backgroundValue, imageFileNameType);
                
            }
            else if (key == "pressedData"){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTexturePressed(backgroundValue, imageFileNameType);
                
            }
            else if (key == "disabledData"){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTextureDisabled(backgroundValue, imageFileNameType);
                
            }else if (key == "text"){
                button->setTitleText(value);
            }
            else if(key == "capInsetsX"){
                capsx = valueToFloat(value);
            }else if(key == "capInsetsY"){
                capsy = valueToFloat(value);
            }else if(key == "capInsetsWidth"){
                capsWidth = valueToFloat(value);
            }else if(key == "capInsetsHeight"){
                capsHeight = valueToFloat(value);
            }else if(key == "scale9Width"){
                scale9Width = valueToFloat(value);
            }else if(key == "scale9Height"){
                scale9Height = valueToFloat(value);
            }else if(key == "textColorR"){
                cri = valueToInt(value);
            }else if(key == "textColorG"){
                cgi = valueToInt(value);
            }else if(key == "textColorB"){
                cbi = valueToInt(value);
            }else if(key == "fontSize"){
                button->setTitleFontSize(valueToFloat(value));
            }else if(key == "fontName"){
                button->setTitleFontName(value);
            }
            
        } //end of for loop
        
        this->endSetBasicProperties(widget);

        if (button->isScale9Enabled()) {
            button->setCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
            button->setSize(Size(scale9Width, scale9Height));
        }
        
        button->setTitleColor(Color3B(cri, cgi, cbi));
        

    }
    
    void ButtonReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        Button* button = static_cast<Button*>(widget);
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        button->setScale9Enabled(scale9Enable);
        
        
        const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, "normalData");
        int normalType = DICTOOL->getIntValue_json(normalDic, "resourceType");
        std::string normalTexturePath = this->getResourcePath(normalDic, "path", (Widget::TextureResType)normalType);
        button->loadTextureNormal(normalTexturePath, (Widget::TextureResType)normalType);
        
        
        const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, "pressedData");
        int pressedType = DICTOOL->getIntValue_json(pressedDic, "resourceType");
        
        std::string pressedTexturePath = this->getResourcePath(pressedDic, "path", (Widget::TextureResType)pressedType);
        button->loadTexturePressed(pressedTexturePath, (Widget::TextureResType)pressedType);
        
        
        const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, "disabledData");
        int disabledType = DICTOOL->getIntValue_json(disabledDic, "resourceType");
        
        std::string disabledTexturePath = this->getResourcePath(disabledDic, "path", (Widget::TextureResType)disabledType);
        button->loadTextureDisabled(disabledTexturePath, (Widget::TextureResType)disabledType);
       
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            
            button->setCapInsets(Rect(cx, cy, cw, ch));
            bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
            bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                button->setSize(Size(swf, shf));
            }
        }
        bool tt = DICTOOL->checkObjectExist_json(options, "text");
        if (tt)
        {
            const char* text = DICTOOL->getStringValue_json(options, "text");
            if (text)
            {
                button->setTitleText(text);
            }
        }
        
        bool cr = DICTOOL->checkObjectExist_json(options, "textColorR");
        bool cg = DICTOOL->checkObjectExist_json(options, "textColorG");
        bool cb = DICTOOL->checkObjectExist_json(options, "textColorB");
        int cri = cr?DICTOOL->getIntValue_json(options, "textColorR"):255;
        int cgi = cg?DICTOOL->getIntValue_json(options, "textColorG"):255;
        int cbi = cb?DICTOOL->getIntValue_json(options, "textColorB"):255;
        button->setTitleColor(Color3B(cri,cgi,cbi));
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs)
        {
            button->setTitleFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
        if (fn)
        {
            button->setTitleFontName(DICTOOL->getStringValue_json(options, "fontName"));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
