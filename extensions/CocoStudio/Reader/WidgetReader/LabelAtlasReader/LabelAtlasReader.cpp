

#include "LabelAtlasReader.h"
#include "../../../GUI/UIWidgets/UILabelAtlas.h"

NS_CC_EXT_BEGIN

static LabelAtlasReader* instanceLabelAtalsReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(LabelAtlasReader)

LabelAtlasReader::LabelAtlasReader()
{
    
}

LabelAtlasReader::~LabelAtlasReader()
{
    
}

LabelAtlasReader* LabelAtlasReader::getInstance()
{
    if (!instanceLabelAtalsReader)
    {
        instanceLabelAtalsReader = new LabelAtlasReader();
    }
    return instanceLabelAtalsReader;
}

void LabelAtlasReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();

    ui::LabelAtlas* labelAtlas = (ui::LabelAtlas*)widget;
   
    const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, "charMapFileData");
    int cmfType = DICTOOL->getIntValue_json(cmftDic, "resourceType");
    switch (cmfType)
    {
        case 0:
        {
            std::string tp_c = jsonPath;
            const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, "path");
            const char* cmf_tp = tp_c.append(cmfPath).c_str();
            labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue","0123456789"),
                                    cmf_tp,
                                    DICTOOL->getIntValue_json(options, "itemWidth",24),
                                    DICTOOL->getIntValue_json(options,"itemHeight",32),
                                    DICTOOL->getStringValue_json(options, "startCharMap"));
            break;
        }
        case 1:
            CCLOG("Wrong res type of LabelAtlas!");
            break;
        default:
            break;
    }
    
    
    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

void LabelAtlasReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    this->beginSetBasicProperties(widget);
    
    ui::LabelAtlas* labelAtlas = static_cast<ui::LabelAtlas*>(widget);
    
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    ui::TextureResType type = ui::UI_TEX_TYPE_LOCAL;
    std::string charMapFileName;
    std::string stringValue;
    std::string startCharMap;
    float itemWidth = 0.0f;
    float itemHeight = 0.0f;
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue(pCocoLoader);
        //            CCLOG("LabelAtlas: key = %s, value = %s", key.c_str(), value.c_str());
        
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
        else if (key == "stringValue") {
            stringValue = value;
        }
        else if(key == "charMapFileData"){
            stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(pCocoLoader);
            std::string resType = backGroundChildren[2].GetValue(pCocoLoader);
            
            ui::TextureResType imageFileNameType = (ui::TextureResType)valueToInt(resType);
            
            std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
            
            charMapFileName = backgroundValue;
            type  = imageFileNameType;
            
        }else if(key == "itemWidth"){
            itemWidth = valueToFloat(value);
        }else if(key == "itemHeight"){
            itemHeight = valueToFloat(value);
        }else if(key == "startCharMap"){
            startCharMap = value;
        }
    } //end of for loop
    
    if (type == (ui::TextureResType)0) {
        labelAtlas->setProperty(stringValue, charMapFileName, itemWidth, itemHeight, startCharMap);
    }
    this->endSetBasicProperties(widget);
}

NS_CC_EXT_END
