

#include "LabelReader.h"
#include "../../../GUI/UIWidgets/UILabel.h"

#include <algorithm>    // std::transform

NS_CC_EXT_BEGIN

using namespace cocos2d::ui;

static LabelReader* instanceLabelReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(LabelReader)

LabelReader::LabelReader()
{
    
}

LabelReader::~LabelReader()
{
    
}

LabelReader* LabelReader::getInstance()
{
    if (!instanceLabelReader)
    {
        instanceLabelReader = new LabelReader();
    }
    return instanceLabelReader;
}

void LabelReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    ui::Label* label = (ui::Label*)widget;
    bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, "touchScaleEnable");
    label->setTouchScaleChangeEnabled(touchScaleChangeAble);
    const char* text = DICTOOL->getStringValue_json(options, "text","Text Label");
    label->setText(text);
   
    label->setFontSize(DICTOOL->getIntValue_json(options, "fontSize",20));
    
    std::string fontName = DICTOOL->getStringValue_json(options, "fontName","微软雅黑");
    std::string file_extension = "";
    size_t pos = fontName.find_last_of('.');
    if (pos != std::string::npos)
    {
        file_extension = fontName.substr(pos, fontName.length());
        std::transform(file_extension.begin(),file_extension.end(), file_extension.begin(), (int(*)(int))toupper);
    }
    
    if (file_extension.compare(".TTF") == 0)
    {
        std::string fontFilePath = jsonPath.append(fontName);
        label->setFontName(fontFilePath);
    }
    else
    {
        label->setFontName(fontName);
    }
    
    bool aw = DICTOOL->checkObjectExist_json(options, "areaWidth");
    bool ah = DICTOOL->checkObjectExist_json(options, "areaHeight");
    if (aw && ah)
    {
        CCSize size = CCSize(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
        label->setTextAreaSize(size);
    }
    bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
    if (ha)
    {
        label->setTextHorizontalAlignment((CCTextAlignment)DICTOOL->getIntValue_json(options, "hAlignment"));
    }
    bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
    if (va)
    {
        label->setTextVerticalAlignment((CCVerticalTextAlignment)DICTOOL->getIntValue_json(options, "vAlignment"));
    }
    
    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

void LabelReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    this->beginSetBasicProperties(widget);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    
    ui::Label* label = static_cast<ui::Label*>(widget);
    
    
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue(pCocoLoader);
        //            CCLOG("Text: key = %s, value = %s", key.c_str(), value.c_str());
        
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
            
            LinearLayoutParameter *linearParameter = LinearLayoutParameter::create();
            RelativeLayoutParameter *relativeParameter = RelativeLayoutParameter::create();
            Margin mg;
            
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
        else if (key == "touchScaleEnable") {
            label->setTouchScaleChangeEnabled(valueToBool(value));
        }
        
        else if(key == "text"){
            label->setText(value);
        }else if(key == "fontSize"){
            label->setFontSize(valueToInt(value));
        }else if(key == "fontName"){
            std::string jsonPath = GUIReader::shareReader()->getFilePath();
            std::string fontFilePath = jsonPath.append(value);
            label->setFontName(fontFilePath);
        }else if(key == "areaWidth"){
            label->setTextAreaSize(CCSize(valueToFloat(value), label->getTextAreaSize().height));
        }else if(key == "areaHeight"){
            label->setTextAreaSize(CCSize(label->getTextAreaSize().width, valueToFloat(value)));
        }else if(key == "hAlignment"){
            label->setTextHorizontalAlignment((CCTextAlignment)valueToInt(value));
        }else if(key == "vAlignment"){
            label->setTextVerticalAlignment((CCVerticalTextAlignment)valueToInt(value));
        }
        
    } //end of for loop
    this->endSetBasicProperties(widget);
}

NS_CC_EXT_END
