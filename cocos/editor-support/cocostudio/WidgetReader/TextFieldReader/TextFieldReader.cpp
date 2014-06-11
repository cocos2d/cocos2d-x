

#include "TextFieldReader.h"
#include "ui/UITextField.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
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
    
    void TextFieldReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        TextField* textField = static_cast<TextField*>(widget);
        
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
                sizePercentX = valueToFloat(value);
            }else if(key == "sizePercentY"){
                sizePercentY = valueToFloat(value);
            }else if(key == "positionPercentX"){
                positionPercentX = valueToFloat(value);
            }else if(key == "positionPercentY"){
                positionPercentY = valueToFloat(value);
            }
            else if(key == "adaptScreen"){
                isAdaptScreen = valueToBool(value);
            }
            else if (key == "width"){
                width = valueToFloat(value);
            }else if(key == "height"){
                height = valueToFloat(value);
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
                position.x = valueToFloat(value);
            }else if(key == "y"){
                position.y = valueToFloat(value);
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
                widget->setOpacity(valueToInt(value));
            }else if(key == "colorR"){
                Color3B color = widget->getColor();
                widget->setColor(Color3B(valueToInt(value), color.g, color.b));
            }else if(key == "colorG"){
                Color3B color = widget->getColor();
                widget->setColor(Color3B( color.r, valueToInt(value), color.b));
            }else if(key == "colorB")
            {
                Color3B color = widget->getColor();
                widget->setColor(Color3B( color.r,  color.g , valueToInt(value)));
            }else if(key == "flipX"){
                widget->setFlippedX(valueToBool(value));
            }else if(key == "flipY"){
                widget->setFlippedY(valueToBool(value));
            }else if(key == "anchorPointX"){
                originalAnchorPoint.x = valueToFloat(value);
            }else if(key == "anchorPointY"){
                originalAnchorPoint.y = valueToFloat(value);
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
                textField->setTouchSize(Size(valueToFloat(value), textField->getTouchSize().height));
            }else if(key == "touchSizeHeight"){
                textField->setTouchSize(Size(textField->getTouchSize().width,  valueToFloat(value)));
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
    
    void TextFieldReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        TextField* textField = static_cast<TextField*>(widget);
        bool ph = DICTOOL->checkObjectExist_json(options, "placeHolder");
        if (ph)
        {
            textField->setPlaceHolder(DICTOOL->getStringValue_json(options, "placeHolder"));
        }
        textField->setText(DICTOOL->getStringValue_json(options, "text"));
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs)
        {
            textField->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
        if (fn)
        {
            textField->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
        }
        bool tsw = DICTOOL->checkObjectExist_json(options, "touchSizeWidth");
        bool tsh = DICTOOL->checkObjectExist_json(options, "touchSizeHeight");
        if (tsw && tsh)
        {
            textField->setTouchSize(Size(DICTOOL->getFloatValue_json(options, "touchSizeWidth"), DICTOOL->getFloatValue_json(options,"touchSizeHeight")));
        }
        
        float dw = DICTOOL->getFloatValue_json(options, "width");
        float dh = DICTOOL->getFloatValue_json(options, "height");
        if (dw > 0.0f || dh > 0.0f)
        {
            //textField->setSize(Size(dw, dh));
        }
        bool maxLengthEnable = DICTOOL->getBooleanValue_json(options, "maxLengthEnable");
        textField->setMaxLengthEnabled(maxLengthEnable);
        
        if (maxLengthEnable)
        {
            int maxLength = DICTOOL->getIntValue_json(options, "maxLength");
            textField->setMaxLength(maxLength);
        }
        bool passwordEnable = DICTOOL->getBooleanValue_json(options, "passwordEnable");
        textField->setPasswordEnabled(passwordEnable);
        if (passwordEnable)
        {
            textField->setPasswordStyleText(DICTOOL->getStringValue_json(options, "passwordStyleText"));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
