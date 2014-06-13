

#include "ScrollViewReader.h"
#include "../../../GUI/UIWidgets/ScrollWidget/UIScrollView.h"

NS_CC_EXT_BEGIN

static ScrollViewReader* instanceScrollViewReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(ScrollViewReader)

ScrollViewReader::ScrollViewReader()
{
    
}

ScrollViewReader::~ScrollViewReader()
{
    
}

ScrollViewReader* ScrollViewReader::getInstance()
{
    if (!instanceScrollViewReader)
    {
        instanceScrollViewReader = new ScrollViewReader();
    }
    return instanceScrollViewReader;
}



void ScrollViewReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    LayoutReader::setPropsFromJsonDictionary(widget, options);
    
    
    ui::ScrollView* scrollView = (ui::ScrollView*)widget;
    
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
    scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
    
	int direction = DICTOOL->getFloatValue_json(options, "direction");
	scrollView->setDirection((ui::SCROLLVIEW_DIR)direction);
    
    scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
    
    
    LayoutReader::setColorPropsFromJsonDictionary(widget, options);
}

void ScrollViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
    //TODO::need to refactor...
    LayoutReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
    
    ui::ScrollView* scrollView = static_cast<ui::ScrollView*>(widget);
    
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
    float innerWidth;
    float innerHeight;
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue();
        if (key == "ignoreSize") {
            widget->ignoreContentAdaptWithSize(valueToBool(value));
        }else if(key == "sizeType"){
            widget->setSizeType((ui::SizeType)valueToInt(value));
        }else if(key == "positionType"){
            widget->setPositionType((ui::PositionType)valueToInt(value));
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
            widget->setName(widgetName.c_str());
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
            
            ui::LinearLayoutParameter *linearParameter = ui::LinearLayoutParameter::create();
            ui::RelativeLayoutParameter *relativeParameter = ui::RelativeLayoutParameter::create();
            ui::Margin mg;
            
            int paramType = -1;
            for (int j = 0; j < stChildArray[i].GetChildNum(); ++j) {
                std::string innerKey = layoutCocosNode[j].GetName(pCocoLoader);
                std::string innerValue = layoutCocosNode[j].GetValue();
                
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
            widget->setOpacity(valueToInt(value));
        }else if(key == "colorR"){
            ccColor3B color = widget->getColor();
            widget->setColor(ccc3(valueToInt(value), color.g, color.b));
        }else if(key == "colorG"){
            ccColor3B color = widget->getColor();
            widget->setColor(ccc3( color.r, valueToInt(value), color.b));
        }else if(key == "colorB")
        {
            ccColor3B color = widget->getColor();
            widget->setColor(ccc3( color.r,  color.g , valueToInt(value)));
        }else if(key == "flipX"){
            widget->setFlipX(valueToBool(value));
        }else if(key == "flipY"){
            widget->setFlipY(valueToBool(value));
        }else if(key == "anchorPointX"){
            originalAnchorPoint.x = valueToFloat(value);
        }else if(key == "anchorPointY"){
            originalAnchorPoint.y = valueToFloat(value);
        }
        else if (key == "innerWidth") {
            innerWidth = valueToFloat(value);
        }
        else if(key == "innerHeight"){
            innerHeight = valueToFloat(value);
        }else if(key == "direction"){
            scrollView->setDirection((ui::SCROLLVIEW_DIR)valueToInt(value));
        }else if(key == "bounceEnable"){
            scrollView->setBounceEnabled(valueToBool(value));
        }
        
    } //end of for loop
    scrollView->setInnerContainerSize(CCSize(innerWidth, innerHeight));
    
}

NS_CC_EXT_END
