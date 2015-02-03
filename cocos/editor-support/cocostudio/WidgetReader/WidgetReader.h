/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __TestCpp__WidgetReader__
#define __TestCpp__WidgetReader__

#include "WidgetReaderProtocol.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/GUIDefine.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReaderProtocol.h"
#include "cocostudio/WidgetReader/NodeReaderDefine.h"

namespace cocostudio
{
    class CocoLoader;
    struct stExpCocoNode;
    
    class CC_STUDIO_DLL WidgetReader : public cocos2d::Ref, public WidgetReaderProtocol, public NodeReaderProtocol
    {
        DECLARE_CLASS_NODE_READER_INFO
        
    public:
        WidgetReader();
        virtual ~WidgetReader();
        
        static WidgetReader* getInstance();
        static void purge();
        
        virtual void setPropsFromJsonDictionary(cocos2d::ui::Widget* widget,
                                                const rapidjson::Value& options);
        
        virtual void setColorPropsFromJsonDictionary(cocos2d::ui::Widget* widget,
                                                     const rapidjson::Value& options);
        
        virtual void setPropsFromBinary(cocos2d::ui::Widget* widget, CocoLoader* cocoLoader,  stExpCocoNode*	pCocoNode);        
        
        /* flatbuffers refactoring */
        flatbuffers::Offset<flatbuffers::Table> createOptionsWithFlatBuffers(const tinyxml2::XMLElement* objectData,
                                                                             flatbuffers::FlatBufferBuilder* builder);
        void setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* widgetOptions);
        void setLayoutComponentPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* widgetOptions);
        cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* widgetOptions);
        /**/
        
    protected:
        std::string getResourcePath(const rapidjson::Value& dict,
                                    const std::string& key,
                                    cocos2d::ui::Widget::TextureResType texType);
        void setAnchorPointForWidget(cocos2d::ui::Widget* widget, const rapidjson::Value&options);
        
        
        std::string getResourcePath(CocoLoader* cocoLoader,
                                    stExpCocoNode*	pCocoNode,
                                    cocos2d::ui::Widget::TextureResType texType);                
        
        std::string getResourcePath(const std::string& path,
                                    cocos2d::ui::Widget::TextureResType texType);

        void beginSetBasicProperties(cocos2d::ui::Widget *widget);
        void endSetBasicProperties(cocos2d::ui::Widget *widget);
        
        
        std::function<int(const std::string&)> valueToInt;
        std::function<bool(const std::string&)> valueToBool;
        std::function<float(const std::string&)> valueToFloat;
        
        float _sizePercentX;
        float _sizePercentY;
        float _positionPercentX;
        float _positionPercentY;
        float _width ;
        float _height;
        cocos2d::Color3B _color;
        int _opacity;
        cocos2d::Vec2 _position;
        bool _isAdaptScreen;
        cocos2d::Vec2 _originalAnchorPoint;

    };
    
    //property const define
    extern const char* P_IgnoreSize;
    extern const char* P_SizeType;
    extern const char* P_PositionType;
    extern const char* P_SizePercentX;
    extern const char* P_SizePercentY;
    extern const char* P_PositionPercentX;
    extern const char* P_PositionPercentY;
    extern const char* P_AdaptScreen;
    extern const char* P_Width;
    extern const char* P_Height;
    extern const char* P_Tag;
    extern const char* P_ActionTag;
    extern const char* P_TouchAble;
    extern const char* P_Name;
    extern const char* P_X;
    extern const char* P_Y;
    extern const char* P_ScaleX;
    extern const char* P_ScaleY;
    extern const char* P_Rotation;
    extern const char* P_Visbile;
    extern const char* P_ZOrder;
    extern const char* P_LayoutParameter;
    extern const char* P_Type;
    extern const char* P_Gravity;
    extern const char* P_RelativeName;
    extern const char* P_RelativeToName;
    extern const char* P_Align;
    extern const char* P_MarginLeft;
    extern const char* P_MarginRight;
    extern const char* P_MarginTop;
    extern const char* P_MarginDown;
    
    extern const char* P_Opacity;
    extern const char* P_ColorR;
    extern const char* P_ColorG;
    extern const char* P_ColorB;
    extern const char* P_FlipX;
    extern const char* P_FlipY;
    extern const char* P_AnchorPointX;
    extern const char* P_AnchorPointY;
    
    extern const char* P_ResourceType;
    extern const char* P_Path;
    
#define CC_BASIC_PROPERTY_BINARY_READER  \
    if (key == P_IgnoreSize) {   \
        widget->ignoreContentAdaptWithSize(valueToBool(value)); \
    }else if(key == P_SizeType){  \
        widget->setSizeType((Widget::SizeType)valueToInt(value)); \
    }else if(key == P_PositionType){   \
        widget->setPositionType((Widget::PositionType)valueToInt(value));  \
    }else if(key == P_SizePercentX){  \
        _sizePercentX = valueToFloat(value);  \
    }else if(key == P_SizePercentY){  \
        _sizePercentY = valueToFloat(value); \
    }else if(key == P_PositionPercentX){  \
        _positionPercentX = valueToFloat(value); \
    }else if(key == P_PositionPercentY){  \
        _positionPercentY = valueToFloat(value);  \
    } \
    else if (key == P_Width){  \
        _width = valueToFloat(value);  \
    }else if(key == P_Height){  \
        _height = valueToFloat(value);  \
    }else if(key == P_Tag){  \
        widget->setTag(valueToInt(value));  \
    }else if(key == P_ActionTag){  \
        widget->setActionTag(valueToInt(value));  \
    }else if(key == P_TouchAble){  \
        widget->setTouchEnabled(valueToBool(value)); \
    }else if(key == P_Name){  \
        std::string widgetName = value.empty() ? "default" : value; \
        widget->setName(widgetName); \
    }else if(key == P_X){  \
        _position.x = valueToFloat(value); \
    }else if(key == P_Y){  \
        _position.y = valueToFloat(value); \
    }else if(key == P_ScaleX){ \
        widget->setScaleX(valueToFloat(value)); \
    }else if(key == P_ScaleY){ \
        widget->setScaleY(valueToFloat(value)); \
    }else if(key == P_Rotation){ \
        widget->setRotation(valueToFloat(value)); \
    }else if(key == P_Visbile){ \
        widget->setVisible(valueToBool(value)); \
    }else if(key == P_ZOrder){ \
        widget->setLocalZOrder(valueToInt(value));  \
    }else if(key == P_LayoutParameter){ \
        stExpCocoNode *layoutCocosNode = stChildArray[i].GetChildArray(cocoLoader); \
        ui::LinearLayoutParameter *linearParameter = ui::LinearLayoutParameter::create();  \
        ui::RelativeLayoutParameter *relativeParameter = ui::RelativeLayoutParameter::create();  \
        ui::Margin mg;  \
        int paramType = -1;  \
        for (int j = 0; j < stChildArray[i].GetChildNum(); ++j) {  \
            std::string innerKey = layoutCocosNode[j].GetName(cocoLoader);  \
            std::string innerValue = layoutCocosNode[j].GetValue(cocoLoader); \
            if (innerKey == P_Type) {  \
                paramType = valueToInt(innerValue); \
            }else if(innerKey == P_Gravity){ \
                linearParameter->setGravity((cocos2d::ui::LinearLayoutParameter::LinearGravity)valueToInt(innerValue));  \
            }else if(innerKey == P_RelativeName){  \
                relativeParameter->setRelativeName(innerValue);  \
            }else if(innerKey == P_RelativeToName){  \
                relativeParameter->setRelativeToWidgetName(innerValue);  \
            }else if(innerKey == P_Align){  \
                relativeParameter->setAlign((cocos2d::ui::RelativeLayoutParameter::RelativeAlign)valueToInt(innerValue)); \
            }else if(innerKey == P_MarginLeft){ \
                mg.left = valueToFloat(innerValue);  \
            }else if(innerKey == P_MarginTop){ \
                mg.top = valueToFloat(innerValue);  \
            }else if(innerKey == P_MarginRight){  \
                mg.right = valueToFloat(innerValue); \
            }else if(innerKey == P_MarginDown){  \
                mg.bottom = valueToFloat(innerValue); \
            } \
        } \
        linearParameter->setMargin(mg); \
        relativeParameter->setMargin(mg); \
        switch (paramType) { \
            case 1: \
                widget->setLayoutParameter(linearParameter); \
                break; \
            case 2: \
                widget->setLayoutParameter(relativeParameter); \
            default: \
                break;\
        }\
      }

    
#define CC_COLOR_PROPERTY_BINARY_READER \
    else if (key == P_Opacity) { \
        _opacity = valueToInt(value); \
    }else if(key == P_ColorR){ \
        _color.r = valueToInt(value);  \
    }else if(key == P_ColorG){  \
        _color.g = valueToInt(value);  \
    }else if(key == P_ColorB)  \
    {\
        _color.b = valueToInt(value);\
    }else if(key == P_FlipX){\
        widget->setFlippedX(valueToBool(value));\
    }else if(key == P_FlipY){\
        widget->setFlippedY(valueToBool(value));\
    } \
    else if(key == P_AnchorPointX){ \
        _originalAnchorPoint.x = valueToFloat(value); \
    }else if(key == P_AnchorPointY){ \
        _originalAnchorPoint.y = valueToFloat(value); \
    }


}

#endif /* defined(__TestCpp__WidgetReader__) */
