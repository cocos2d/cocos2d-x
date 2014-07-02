

#include "CheckBoxReader.h"
#include "../../../GUI/UIWidgets/UICheckBox.h"

NS_CC_EXT_BEGIN

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

void CheckBoxReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    

    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    ui::CheckBox* checkBox = (ui::CheckBox*)widget;
    
    const rapidjson::Value& backGroundDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxData");
    int backGroundType = DICTOOL->getIntValue_json(backGroundDic, "resourceType");
    switch (backGroundType)
    {
        case 0:
        {
            std::string tp_b = jsonPath;
            const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
            const char* backGroundFileName_tp = (backGroundFileName && (strcmp(backGroundFileName, "") != 0))?tp_b.append(backGroundFileName).c_str():NULL;
            checkBox->loadTextureBackGround(backGroundFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
            checkBox->loadTextureBackGround(backGroundFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& backGroundSelectedDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxSelectedData");
    int backGroundSelectedType = DICTOOL->getIntValue_json(backGroundSelectedDic, "resourceType");
    switch (backGroundSelectedType)
    {
        case 0:
        {
            std::string tp_bs = jsonPath;
            const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
            const char* backGroundSelectedFileName_tp = (backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))?tp_bs.append(backGroundSelectedFileName).c_str():NULL;
            checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
            checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& frontCrossDic = DICTOOL->getSubDictionary_json(options, "frontCrossData");
    int frontCrossType = DICTOOL->getIntValue_json(frontCrossDic, "resourceType");
    switch (frontCrossType)
    {
        case 0:
        {
            std::string tp_c = jsonPath;
            const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
            const char* frontCrossFileName_tp = (frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))?tp_c.append(frontCrossFileName).c_str():NULL;
            checkBox->loadTextureFrontCross(frontCrossFileName_tp);
            break;
        }
        case 1:
        {
            const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
            checkBox->loadTextureFrontCross(frontCrossFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& backGroundDisabledDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxDisabledData");
    int backGroundDisabledType = DICTOOL->getIntValue_json(backGroundDisabledDic, "resourceType");
    switch (backGroundDisabledType)
    {
        case 0:
        {
            std::string tp_bd = jsonPath;
            const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
            const char* backGroundDisabledFileName_tp = (backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))?tp_bd.append(backGroundDisabledFileName).c_str():NULL;
            checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
            checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& frontCrossDisabledDic = DICTOOL->getSubDictionary_json(options, "frontCrossDisabledData");
    int frontCrossDisabledType = DICTOOL->getIntValue_json(frontCrossDisabledDic, "resourceType");
    switch (frontCrossDisabledType)
    {
        case 0:
        {
            std::string tp_cd = jsonPath;
            const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
            const char* frontCrossDisabledFileName_tp = (frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))?tp_cd.append(frontCrossDisabledFileName).c_str():NULL;
            checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
            checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName, ui::UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }

    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

void CheckBoxReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    
    ui::CheckBox *checkBox = static_cast<ui::CheckBox*>(widget);
    this->beginSetBasicProperties(widget);
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
        else if (key == "backGroundBoxData"){
            
            stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(pCocoLoader);
            std::string resType = backGroundChildren[2].GetValue(pCocoLoader);;
            
            ui::TextureResType imageFileNameType = (ui::TextureResType)valueToInt(resType);
            
            std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
            
            checkBox->loadTextureBackGround(backgroundValue.c_str(), imageFileNameType);
        }else if(key == "backGroundBoxSelectedData"){
            stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(pCocoLoader);
            std::string resType = backGroundChildren[2].GetValue(pCocoLoader);;
            
            ui::TextureResType imageFileNameType = (ui::TextureResType)valueToInt(resType);
            
            std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
            
            checkBox->loadTextureBackGroundSelected(backgroundValue.c_str(), imageFileNameType);
        }else if(key == "frontCrossData"){
            stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(pCocoLoader);
            std::string resType = backGroundChildren[2].GetValue(pCocoLoader);;
            
            ui::TextureResType imageFileNameType = (ui::TextureResType)valueToInt(resType);
            
            std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
            
            checkBox->loadTextureFrontCross(backgroundValue.c_str(), imageFileNameType);
        }else if(key == "backGroundBoxDisabledData"){
            stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(pCocoLoader);
            std::string resType = backGroundChildren[2].GetValue(pCocoLoader);;
            
            ui::TextureResType imageFileNameType = (ui::TextureResType)valueToInt(resType);
            
            std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
            
            checkBox->loadTextureBackGroundDisabled(backgroundValue.c_str(), imageFileNameType);
        }else if (key == "frontCrossDisabledData"){
            stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(pCocoLoader);
            std::string resType = backGroundChildren[2].GetValue(pCocoLoader);;
            
            ui::TextureResType imageFileNameType = (ui::TextureResType)valueToInt(resType);
            
            std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
            
            checkBox->loadTextureFrontCrossDisabled(backgroundValue.c_str(), imageFileNameType);
        }
        //            else if (key == "selectedState"){
        //                checkBox->setSelectedState(valueToBool(value));
        //            }
    }
    
    this->endSetBasicProperties(widget);
}



NS_CC_EXT_END
