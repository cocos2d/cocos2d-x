

#include "TextFieldReader.h"
#include "../../../GUI/UIWidgets/UITextField.h"

NS_CC_EXT_BEGIN

static TextFieldReader* instanceTextFieldReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(TextFieldReader)

TextFieldReader::TextFieldReader()
{
    
}

TextFieldReader::~TextFieldReader()
{
    
}

TextFieldReader* TextFieldReader::getInstance()
{
    if (!instanceTextFieldReader)
    {
        instanceTextFieldReader = new TextFieldReader();
    }
    return instanceTextFieldReader;
}

void TextFieldReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    
    
    ui::TextField* textField = (ui::TextField*)widget;
   
    textField->setPlaceHolder(DICTOOL->getStringValue_json(options, "placeHolder","inputs words here"));
    
    textField->setText(DICTOOL->getStringValue_json(options, "text","Text Field"));
   
    textField->setFontSize(DICTOOL->getIntValue_json(options, "fontSize",20));
   
    textField->setFontName(DICTOOL->getStringValue_json(options, "fontName","微软雅黑"));
    
    bool tsw = DICTOOL->checkObjectExist_json(options, "touchSizeWidth");
    bool tsh = DICTOOL->checkObjectExist_json(options, "touchSizeHeight");
    if (tsw && tsh)
    {
        textField->setTouchSize(CCSizeMake(DICTOOL->getFloatValue_json(options, "touchSizeWidth"), DICTOOL->getFloatValue_json(options,"touchSizeHeight")));
    }
    
    float dw = DICTOOL->getFloatValue_json(options, "width");
    float dh = DICTOOL->getFloatValue_json(options, "height");
    if (dw > 0.0f || dh > 0.0f)
    {
        //textField->setSize(CCSizeMake(dw, dh));
    }
    bool maxLengthEnable = DICTOOL->getBooleanValue_json(options, "maxLengthEnable");
    textField->setMaxLengthEnabled(maxLengthEnable);
    
    if (maxLengthEnable)
    {
        int maxLength = DICTOOL->getIntValue_json(options, "maxLength",10);
        textField->setMaxLength(maxLength);
    }
    bool passwordEnable = DICTOOL->getBooleanValue_json(options, "passwordEnable");
    textField->setPasswordEnabled(passwordEnable);
    if (passwordEnable)
    {
        textField->setPasswordStyleText(DICTOOL->getStringValue_json(options, "passwordStyleText","*"));
    }
    
    bool aw = DICTOOL->checkObjectExist_json(options, "areaWidth");
    bool ah = DICTOOL->checkObjectExist_json(options, "areaHeight");
    if (aw && ah)
    {
        CCSize size = CCSize(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
        textField->setTextAreaSize(size);        
    }
    bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
    if (ha)
    {
        textField->setTextHorizontalAlignment((CCTextAlignment)DICTOOL->getIntValue_json(options, "hAlignment"));
    }
    bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
    if (va)
    {
        textField->setTextVerticalAlignment((CCVerticalTextAlignment)DICTOOL->getIntValue_json(options, "vAlignment"));
    }
    
    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

void TextFieldReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    this->beginSetBasicProperties(widget);
    
    ui::TextField* textField = static_cast<ui::TextField*>(widget);
    
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
        else if(key == "placeHolder"){
            textField->setPlaceHolder(value);
        }else if(key == "text"){
            textField->setText(value);
        }else if(key == "fontSize"){
            textField->setFontSize(valueToInt(value));
        }else if(key == "fontName"){
            textField->setFontName(value);
        }else if(key == "touchSizeWidth"){
            textField->setTouchSize(CCSize(valueToFloat(value), textField->getTouchSize().height));
        }else if(key == "touchSizeHeight"){
            textField->setTouchSize(CCSize(textField->getTouchSize().width,  valueToFloat(value)));
        }else if (key == "maxLengthEnable"){
            textField->setMaxLengthEnabled(valueToBool(value));
        }else if(key == "maxLength"){
            textField->setMaxLength(valueToInt(value));
        }else if(key == "passwordEnable"){
            textField->setPasswordEnabled(valueToBool(value));
        }else if(key == "passwordStyleText"){
            textField->setPasswordStyleText(value.c_str());
        }
    } //end of for loop
    this->endSetBasicProperties(widget);
}


NS_CC_EXT_END
