

#include "CheckBoxReader.h"
#include "ui/UICheckBox.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static CheckBoxReader* instanceCheckBoxReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(CheckBoxReader)
    
    CheckBoxReader::CheckBoxReader()
    {
        
    }
    
    CheckBoxReader::~CheckBoxReader()
    {
        
    }
    
    CheckBoxReader* CheckBoxReader::getInstance()
    {
        if (!instanceCheckBoxReader)
        {
            instanceCheckBoxReader = new CheckBoxReader();
        }
        return instanceCheckBoxReader;
    }
    
    void CheckBoxReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        
        CheckBox *checkBox = static_cast<CheckBox*>(widget);
        this->beginSetBasicProperties(widget);
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
            CCLOG("key = %s, index : %d", key.c_str(), i);
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
            else if (key == "backGroundBoxData"){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureBackGround(backgroundValue, imageFileNameType);
            }else if(key == "backGroundBoxSelectedData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureBackGroundSelected(backgroundValue, imageFileNameType);
            }else if(key == "frontCrossData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureFrontCross(backgroundValue, imageFileNameType);
            }else if(key == "backGroundBoxDisabledData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureBackGroundDisabled(backgroundValue, imageFileNameType);
            }else if (key == "frontCrossDisabledData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureFrontCrossDisabled(backgroundValue, imageFileNameType);
            }
//            else if (key == "selectedState"){
//                checkBox->setSelectedState(valueToBool(value));
//            }
        }
        
        this->endSetBasicProperties(widget);
        
        
    }
    
    void CheckBoxReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        CheckBox* checkBox = static_cast<CheckBox*>(widget);
       
        //load background image
        const rapidjson::Value& backGroundDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxData");
        int backGroundType = DICTOOL->getIntValue_json(backGroundDic, "resourceType");
        std::string backGroundTexturePath = this->getResourcePath(backGroundDic, "path", (Widget::TextureResType)backGroundType);
         checkBox->loadTextureBackGround(backGroundTexturePath, (Widget::TextureResType)backGroundType);
        
       //load background selected image
        const rapidjson::Value& backGroundSelectedDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxSelectedData");
        int backGroundSelectedType = DICTOOL->getIntValue_json(backGroundSelectedDic, "resourceType");
        std::string backGroundSelectedTexturePath = this->getResourcePath(backGroundSelectedDic, "path", (Widget::TextureResType)backGroundSelectedType);
        checkBox->loadTextureBackGroundSelected(backGroundSelectedTexturePath, (Widget::TextureResType)backGroundSelectedType);
        
        //load frontCross image
        const rapidjson::Value& frontCrossDic = DICTOOL->getSubDictionary_json(options, "frontCrossData");
        int frontCrossType = DICTOOL->getIntValue_json(frontCrossDic, "resourceType");
        std::string frontCrossFileName = this->getResourcePath(frontCrossDic, "path", (Widget::TextureResType)frontCrossType);
        checkBox->loadTextureFrontCross(frontCrossFileName, (Widget::TextureResType)frontCrossType);
        
       //load backGroundBoxDisabledData
        const rapidjson::Value& backGroundDisabledDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxDisabledData");
        int backGroundDisabledType = DICTOOL->getIntValue_json(backGroundDisabledDic, "resourceType");
        std::string backGroundDisabledFileName = this->getResourcePath(backGroundDisabledDic, "path", (Widget::TextureResType)backGroundDisabledType);
        checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName, (Widget::TextureResType)backGroundDisabledType);
        
        ///load frontCrossDisabledData
        const rapidjson::Value& frontCrossDisabledDic = DICTOOL->getSubDictionary_json(options, "frontCrossDisabledData");
        int frontCrossDisabledType = DICTOOL->getIntValue_json(frontCrossDisabledDic, "resourceType");
        std::string frontCrossDisabledFileName = this->getResourcePath(frontCrossDisabledDic, "path", (Widget::TextureResType)frontCrossDisabledType);
        checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName, (Widget::TextureResType)frontCrossDisabledType);
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
