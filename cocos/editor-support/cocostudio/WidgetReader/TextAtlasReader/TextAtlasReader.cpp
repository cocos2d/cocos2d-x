

#include "TextAtlasReader.h"
#include "ui/UITextAtlas.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static TextAtlasReader* instanceTextAtalsReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(TextAtlasReader)
    
    TextAtlasReader::TextAtlasReader()
    {
        
    }
    
    TextAtlasReader::~TextAtlasReader()
    {
        
    }
    
    TextAtlasReader* TextAtlasReader::getInstance()
    {
        if (!instanceTextAtalsReader)
        {
            instanceTextAtalsReader = new TextAtlasReader();
        }
        return instanceTextAtalsReader;
    }
    
    void TextAtlasReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        TextAtlas* labelAtlas = static_cast<TextAtlas*>(widget);

        
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        Widget::TextureResType type;
        std::string charMapFileName;
        std::string stringValue;
        std::string startCharMap;
        float itemWidth;
        float itemHeight;
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
//            CCLOG("LabelAtlas: key = %s, value = %s", key.c_str(), value.c_str());

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
            else if (key == "stringValue") {
                stringValue = value;
            }
            else if(key == "charMapFileData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
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
        
        if (type == (Widget::TextureResType)0) {
            labelAtlas->setProperty(stringValue, charMapFileName, itemWidth, itemHeight, startCharMap);
        }
        this->endSetBasicProperties(widget);
    }
    
    void TextAtlasReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        TextAtlas* labelAtlas = static_cast<TextAtlas*>(widget);
        bool sv = DICTOOL->checkObjectExist_json(options, "stringValue");
        bool cmf = DICTOOL->checkObjectExist_json(options, "charMapFile");
        bool iw = DICTOOL->checkObjectExist_json(options, "itemWidth");
        bool ih = DICTOOL->checkObjectExist_json(options, "itemHeight");
        bool scm = DICTOOL->checkObjectExist_json(options, "startCharMap");
        if (sv && cmf && iw && ih && scm)
        {
            const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, "charMapFileData");
            int cmfType = DICTOOL->getIntValue_json(cmftDic, "resourceType");
            switch (cmfType)
            {
                case 0:
                {
                    std::string tp_c = jsonPath;
                    const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, "path");
                    const char* cmf_tp = tp_c.append(cmfPath).c_str();
                    labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),cmf_tp,DICTOOL->getIntValue_json(options, "itemWidth"),DICTOOL->getIntValue_json(options,"itemHeight"), DICTOOL->getStringValue_json(options, "startCharMap"));
                    break;
                }
                case 1:
                    CCLOG("Wrong res type of LabelAtlas!");
                    break;
                default:
                    break;
            }
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
