

#include "LoadingBarReader.h"
#include "../../../GUI/UIWidgets/UILoadingBar.h"

NS_CC_EXT_BEGIN

static LoadingBarReader* instanceLoadingBar = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(LoadingBarReader)

LoadingBarReader::LoadingBarReader()
{
    
}

LoadingBarReader::~LoadingBarReader()
{
    
}

LoadingBarReader* LoadingBarReader::getInstance()
{
    if (!instanceLoadingBar)
    {
        instanceLoadingBar = new LoadingBarReader();
    }
    return instanceLoadingBar;
}

void LoadingBarReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    {
        ui::LoadingBar* loadingBar = (ui::LoadingBar*)widget;
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "textureData");
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
        switch (imageFileNameType)
        {
            case 0:
            {
                std::string tp_i = jsonPath;
                const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
                const char* imageFileName_tp = NULL;
                if (imageFileName && (strcmp(imageFileName, "") != 0))
                {
                    imageFileName_tp = tp_i.append(imageFileName).c_str();
                    loadingBar->loadTexture(imageFileName_tp);
                }
                break;
            }
            case 1:
            {
                const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
                loadingBar->loadTexture(imageFileName, ui::UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        loadingBar->setScale9Enabled(scale9Enable);
        
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth",1);
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight",1);
            
            loadingBar->setCapInsets(CCRectMake(cx, cy, cw, ch));
            
            float width = DICTOOL->getFloatValue_json(options, "width");
            float height = DICTOOL->getFloatValue_json(options, "height");
            loadingBar->setSize(CCSizeMake(width, height));
        }
        
        loadingBar->setDirection(ui::LoadingBarType(DICTOOL->getIntValue_json(options, "direction")));
        loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent",100));
    }
    
    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

void LoadingBarReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    WidgetReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
    
    ui::LoadingBar* loadingBar = static_cast<ui::LoadingBar*>(widget);
    this->beginSetBasicProperties(widget);
    float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    int percent = 0;
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
        else if (key == "scale9Enable") {
            loadingBar->setScale9Enabled(valueToBool(value));
        }
        else if (key == "textureData"){
            
            stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(pCocoLoader);
            std::string resType = backGroundChildren[2].GetValue(pCocoLoader);;
            
            ui::TextureResType imageFileNameType = (ui::TextureResType)valueToInt(resType);
            
            std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
            
            loadingBar->loadTexture(backgroundValue.c_str(), imageFileNameType);
            
        }
        else if(key == "capInsetsX"){
            capsx = valueToFloat(value);
        }else if(key == "capInsetsY"){
            capsy = valueToFloat(value);
        }else if(key == "capInsetsWidth"){
            capsWidth = valueToFloat(value);
        }else if(key == "capInsetsHeight"){
            capsHeight = valueToFloat(value);
        }else if(key == "direction"){
            loadingBar->setDirection((ui::LoadingBarType)valueToInt(value));
        }else if(key == "percent"){
            percent = valueToInt(value);
        }
        
    } //end of for loop
    
    //the call order of this function matters
    this->endSetBasicProperties(widget);

    
    loadingBar->setPercent(percent);
    if (loadingBar->isScale9Enabled()) {
        loadingBar->setCapInsets(CCRect(capsx, capsy, capsWidth, capsHeight));
    }
    
}

NS_CC_EXT_END
