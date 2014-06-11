

#include "TextReader.h"
#include "ui/UIText.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static TextReader* instanceTextReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(TextReader)
    
    TextReader::TextReader()
    {
        
    }
    
    TextReader::~TextReader()
    {
        
    }
    
    TextReader* TextReader::getInstance()
    {
        if (!instanceTextReader)
        {
            instanceTextReader = new TextReader();
        }
        return instanceTextReader;
    }
    
    void TextReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        
        Text* label = static_cast<Text*>(widget);
    
        
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
//            CCLOG("Text: key = %s, value = %s", key.c_str(), value.c_str());

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
            else if (key == "touchScaleEnable") {
                label->setTouchScaleChangeEnabled(valueToBool(value));
            }
            
            else if(key == "text"){
                label->setString(value);
            }else if(key == "fontSize"){
                label->setFontSize(valueToInt(value));
            }else if(key == "fontName"){
                label->setFontName(value);
            }else if(key == "areaWidth"){
                label->setTextAreaSize(Size(valueToFloat(value), label->getTextAreaSize().height));
            }else if(key == "areaHeight"){
                label->setTextAreaSize(Size(label->getTextAreaSize().width, valueToFloat(value)));
            }else if(key == "hAlignment"){
                label->setTextHorizontalAlignment((TextHAlignment)valueToInt(value));
            }else if(key == "vAlignment"){
                label->setTextVerticalAlignment((TextVAlignment)valueToInt(value));
            }
            
        } //end of for loop
        this->endSetBasicProperties(widget);
    }
    
    void TextReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        Text* label = static_cast<Text*>(widget);
        bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, "touchScaleEnable");
        label->setTouchScaleChangeEnabled(touchScaleChangeAble);
        const char* text = DICTOOL->getStringValue_json(options, "text");
        label->setString(text);
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs)
        {
            label->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
        if (fn)
        {
            label->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
        }
        bool aw = DICTOOL->checkObjectExist_json(options, "areaWidth");
        bool ah = DICTOOL->checkObjectExist_json(options, "areaHeight");
        if (aw && ah)
        {
            Size size = Size(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
            label->setTextAreaSize(size);
        }
        bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
        if (ha)
        {
            label->setTextHorizontalAlignment((TextHAlignment)DICTOOL->getIntValue_json(options, "hAlignment"));
        }
        bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
        if (va)
        {
            label->setTextVerticalAlignment((TextVAlignment)DICTOOL->getIntValue_json(options, "vAlignment"));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
