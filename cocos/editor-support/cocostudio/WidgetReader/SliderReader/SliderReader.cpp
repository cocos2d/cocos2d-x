

#include "SliderReader.h"
#include "ui/UISlider.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static SliderReader* instanceSliderReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(SliderReader)
    
    SliderReader::SliderReader()
    {
        
    }
    
    SliderReader::~SliderReader()
    {
        
    }
    
    SliderReader* SliderReader::getInstance()
    {
        if (!instanceSliderReader)
        {
            instanceSliderReader = new SliderReader();
        }
        return instanceSliderReader;
    }
    
    void SliderReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        Slider* slider = static_cast<Slider*>(widget);
        
        float barLength = 0.0f;
        int percent = slider->getPercent();
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
            //control custom properties
            else if (key == "scale9Enable") {
                slider->setScale9Enabled(valueToBool(value));
            }
            else if(key == "percent"){
                percent = valueToInt(value);
            }else if(key == "barFileNameData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadBarTexture(backgroundValue, imageFileNameType);
                
            }else if(key == "length"){
                barLength = valueToFloat(value);
            }else if(key == "ballNormalData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadSlidBallTextureNormal(backgroundValue, imageFileNameType);

            }else if(key == "ballPressedData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadSlidBallTexturePressed(backgroundValue, imageFileNameType);
                
            }else if(key == "ballDisabledData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadSlidBallTextureDisabled(backgroundValue, imageFileNameType);
                
            }else if(key == "progressBarData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadProgressBarTexture(backgroundValue, imageFileNameType);
                
            }
            
        } //end of for loop
        
        if (slider->isScale9Enabled()) {
            slider->setSize(Size(barLength, slider->getContentSize().height));
        }
        slider->setPercent(percent);
        
        this->endSetBasicProperties(widget);
    }
    
    void SliderReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
                
        Slider* slider = static_cast<Slider*>(widget);
        
        bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        slider->setScale9Enabled(barTextureScale9Enable);
        
        slider->setPercent(DICTOOL->getIntValue_json(options, "percent"));

        
        bool bt = DICTOOL->checkObjectExist_json(options, "barFileName");
        float barLength = DICTOOL->getFloatValue_json(options, "length");
        if (bt)
        {
            const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "barFileNameData");
            int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
            std::string imageFileName = this->getResourcePath(imageFileNameDic, "path", (Widget::TextureResType)imageFileNameType);
            slider->loadBarTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
            
            if (barTextureScale9Enable)
            {
                slider->setSize(Size(barLength, slider->getContentSize().height));
            }
        }
        
        //loading normal slider ball texture
        const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, "ballNormalData");
        int normalType = DICTOOL->getIntValue_json(normalDic, "resourceType");
        std::string imageFileName = this->getResourcePath(normalDic, "path", (Widget::TextureResType)normalType);
        slider->loadSlidBallTextureNormal(imageFileName, (Widget::TextureResType)normalType);
        
        
        //loading slider ball press texture
        const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, "ballPressedData");
        int pressedType = DICTOOL->getIntValue_json(pressedDic, "resourceType");
        std::string pressedFileName = this->getResourcePath(pressedDic, "path", (Widget::TextureResType)pressedType);
        slider->loadSlidBallTexturePressed(pressedFileName, (Widget::TextureResType)pressedType);
        
        //loading silder ball disable texture
        const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, "ballDisabledData");
        int disabledType = DICTOOL->getIntValue_json(disabledDic, "resourceType");
        std::string disabledFileName = this->getResourcePath(disabledDic, "path", (Widget::TextureResType)disabledType);
        slider->loadSlidBallTextureDisabled(disabledFileName, (Widget::TextureResType)disabledType);
        
        //load slider progress texture
        const rapidjson::Value& progressBarDic = DICTOOL->getSubDictionary_json(options, "progressBarData");
        int progressBarType = DICTOOL->getIntValue_json(progressBarDic, "resourceType");
        std::string progressBarFileName = this->getResourcePath(progressBarDic, "path", (Widget::TextureResType)progressBarType);
        slider->loadProgressBarTexture(progressBarFileName, (Widget::TextureResType)progressBarType);
        
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
