

#include "LoadingBarReader.h"
#include "ui/UILoadingBar.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace cocostudio
{
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
    
    void LoadingBarReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
        
        LoadingBar* loadingBar = static_cast<LoadingBar*>(widget);
        this->beginSetBasicProperties(widget);
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        
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
            else if (key == "scale9Enable") {
                loadingBar->setScale9Enabled(valueToBool(value));
            }
            else if (key == "textureData"){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                loadingBar->loadTexture(backgroundValue, imageFileNameType);
                
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
                loadingBar->setDirection((LoadingBar::Direction)valueToInt(value));
            }else if(key == "percent"){
                loadingBar->setPercent(valueToInt(value));
            }
            
        } //end of for loop
        
        if (loadingBar->isScale9Enabled()) {
            loadingBar->setCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
        }
        
        this->endSetBasicProperties(widget);
    }
    
    void LoadingBarReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        LoadingBar* loadingBar = static_cast<LoadingBar*>(widget);
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "textureData");
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
        std::string imageFileName = this->getResourcePath(imageFileNameDic, "path", (Widget::TextureResType)imageFileNameType);
        loadingBar->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);

        
        /* gui mark add load bar scale9 parse */
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        loadingBar->setScale9Enabled(scale9Enable);
        
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            
            loadingBar->setCapInsets(Rect(cx, cy, cw, ch));
            
            float width = DICTOOL->getFloatValue_json(options, "width");
            float height = DICTOOL->getFloatValue_json(options, "height");
            loadingBar->setSize(Size(width, height));
        }
        /**/
        
        loadingBar->setDirection(LoadingBar::Direction(DICTOOL->getIntValue_json(options, "direction")));
        loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent"));
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
