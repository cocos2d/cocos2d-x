

#include "ScrollViewReader.h"

#include "ui/UIScrollView.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/FlatBuffersSerialize.h"

#include "tinyxml2/tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

namespace cocostudio
{
    static const char* P_InnerWidth = "innerWidth";
    static const char* P_InnerHeight = "innerHeight";
    static const char* P_Direction = "direction";
    static const char* P_BounceEnable = "bounceEnable";
    
    static ScrollViewReader* instanceScrollViewReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(ScrollViewReader)
    
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
            instanceScrollViewReader = new (std::nothrow) ScrollViewReader();
        }
        return instanceScrollViewReader;
    }
    
    void ScrollViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode* cocoNode)
    {
        //TODO: need to refactor...
        LayoutReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        ScrollView* scrollView = static_cast<ScrollView*>(widget);
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        float innerWidth;
        float innerHeight;
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            if (key == P_InnerWidth) {
                innerWidth = valueToFloat(value);
            }
            else if(key == P_InnerHeight){
                innerHeight = valueToFloat(value);
            }else if(key == P_Direction){
                scrollView->setDirection((ScrollView::Direction)valueToInt(value));
            }else if(key == P_BounceEnable){
                scrollView->setBounceEnabled(valueToBool(value));
            }
            
        } //end of for loop
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));

    }
    
    void ScrollViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        LayoutReader::setPropsFromJsonDictionary(widget, options);
        
        
        ScrollView* scrollView = static_cast<ScrollView*>(widget);
        float innerWidth = DICTOOL->getFloatValue_json(options, P_InnerWidth,200);
        float innerHeight = DICTOOL->getFloatValue_json(options, P_InnerHeight,200);
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
        int direction = DICTOOL->getFloatValue_json(options, P_Direction,1);
        scrollView->setDirection((ScrollView::Direction)direction);
        scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, P_BounceEnable));
        
        
        LayoutReader::setColorPropsFromJsonDictionary(widget, options);
    }        
    
    Offset<Table> ScrollViewReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                                 flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        std::string path = "";
        std::string plistFile = "";
        int resourceType = 0;
        
        bool clipEnabled = false;
        Color3B bgColor;
        Color3B bgStartColor;
        Color3B bgEndColor;
        int colorType = 0;
        GLubyte bgColorOpacity = 255;
        Vec2 colorVector(0.0f, -0.5f);
        Rect capInsets;
        Size scale9Size;
        bool backGroundScale9Enabled = false;
        Size innerSize(200, 300);
        int direction = 0;
        bool bounceEnabled = false;
        
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "ClipAble")
            {
                clipEnabled = (value == "True") ? true : false;
            }
            else if (name == "ComboBoxIndex")
            {
                colorType = atoi(value.c_str());
            }
            else if (name == "BackColorAlpha")
            {
                bgColorOpacity = atoi(value.c_str());
            }
            else if (name == "Scale9Enable")
            {
                if (value == "True")
                {
                    backGroundScale9Enabled = true;
                }
            }
            else if (name == "Scale9OriginX")
            {
                capInsets.origin.x = atof(value.c_str());
            }
            else if (name == "Scale9OriginY")
            {
                capInsets.origin.y = atof(value.c_str());
            }
            else if (name == "Scale9Width")
            {
                capInsets.size.width = atof(value.c_str());
            }
            else if (name == "Scale9Height")
            {
                capInsets.size.height = atof(value.c_str());
            }
            else if (name == "ScrollDirectionType")
            {
                if (value == "Vertical")
                {
                    direction = 1;
                }
                else if (value == "Horizontal")
                {
                    direction = 2;
                }
                else if (value == "Vertical_Horizontal")
                {
                    direction = 3;
                }
            }
            else if (name == "IsBounceEnabled")
            {
                bounceEnabled = (value == "True") ? true : false;
            }
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "InnerNodeSize")
            {
                attribute = child->FirstAttribute();
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Width")
                    {
                        innerSize.width = atof(value.c_str());
                    }
                    else if (name == "Height")
                    {
                        innerSize.height = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "Size" && backGroundScale9Enabled)
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "X")
                    {
                        scale9Size.width = atof(value.c_str());
                    }
                    else if (name == "Y")
                    {
                        scale9Size.height = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "SingleColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        bgColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        bgColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        bgColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "EndColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        bgEndColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        bgEndColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        bgEndColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "FirstColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        bgStartColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        bgStartColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        bgStartColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "ColorVector")
            {
                attribute = child->FirstAttribute();
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "ScaleX")
                    {
                        colorVector.x = atof(value.c_str());
                    }
                    else if (name == "ScaleY")
                    {
                        colorVector.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "FileData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        path = value;
                    }
                    else if (name == "Type")
                    {
                        resourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (resourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                    
                    texturePng = texture.substr(0, texture.find_last_of('.')).append(".png");
                    fbs->_texturePngs.push_back(builder->CreateString(texturePng));
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        Color f_bgColor(255, bgColor.r, bgColor.g, bgColor.b);
        Color f_bgStartColor(255, bgStartColor.r, bgStartColor.g, bgStartColor.b);
        Color f_bgEndColor(255, bgEndColor.r, bgEndColor.g, bgEndColor.b);
        ColorVector f_colorVector(colorVector.x, colorVector.y);
        CapInsets f_capInsets(capInsets.origin.x, capInsets.origin.y, capInsets.size.width, capInsets.size.height);
        FlatSize f_scale9Size(scale9Size.width, scale9Size.height);
        FlatSize f_innerSize(innerSize.width, innerSize.height);
        
        auto options = CreateScrollViewOptions(*builder,
                                               widgetOptions,
                                               CreateResourceData(*builder,
                                                                  builder->CreateString(path),
                                                                  builder->CreateString(plistFile),
                                                                  resourceType),
                                               clipEnabled,
                                               &f_bgColor,
                                               &f_bgStartColor,
                                               &f_bgEndColor,
                                               colorType,
                                               bgColorOpacity,
                                               &f_colorVector,
                                               &f_capInsets,
                                               &f_scale9Size,
                                               backGroundScale9Enabled,
                                               &f_innerSize,
                                               direction,
                                               bounceEnabled);
        
        return *(Offset<Table>*)(&options);
    }
    
    void ScrollViewReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *scrollViewOptions)
    {
        ScrollView* scrollView = static_cast<ScrollView*>(node);
        auto options = (ScrollViewOptions*)scrollViewOptions;
        
        bool clipEnabled = options->clipEnabled();
        scrollView->setClippingEnabled(clipEnabled);
        
        bool backGroundScale9Enabled = options->backGroundScale9Enabled();
        scrollView->setBackGroundImageScale9Enabled(backGroundScale9Enabled);
        
        
        auto f_bgColor = options->bgColor();
        Color3B bgColor(f_bgColor->r(), f_bgColor->g(), f_bgColor->b());
        auto f_bgStartColor = options->bgStartColor();
        Color3B bgStartColor(f_bgStartColor->r(), f_bgStartColor->g(), f_bgStartColor->b());
        auto f_bgEndColor = options->bgEndColor();
        Color3B bgEndColor(f_bgEndColor->r(), f_bgEndColor->g(), f_bgEndColor->b());
        
        auto f_colorVecor = options->colorVector();
        Vec2 colorVector(f_colorVecor->vectorX(), f_colorVecor->vectorY());
        scrollView->setBackGroundColorVector(colorVector);
        
        int bgColorOpacity = options->bgColorOpacity();
        
        int colorType = options->colorType();
        scrollView->setBackGroundColorType(Layout::BackGroundColorType(colorType));
        
        scrollView->setBackGroundColor(bgStartColor, bgEndColor);
        scrollView->setBackGroundColor(bgColor);
        scrollView->setBackGroundColorOpacity(bgColorOpacity);
        
        
        auto imageFileNameDic = options->backGroundImageData();
        int imageFileNameType = imageFileNameDic->resourceType();
        std::string imageFileName = imageFileNameDic->path()->c_str();
        scrollView->setBackGroundImage(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        if (backGroundScale9Enabled)
        {
            auto f_capInsets = options->capInsets();
            Rect capInsets(f_capInsets->x(), f_capInsets->y(), f_capInsets->width(), f_capInsets->height());
            scrollView->setBackGroundImageCapInsets(capInsets);
            
            auto f_scale9Size = options->scale9Size();
            Size scale9Size(f_scale9Size->width(), f_scale9Size->height());
            scrollView->setContentSize(scale9Size);
        }
        
        auto widgetOptions = options->widgetOptions();
        auto f_color = widgetOptions->color();
        Color3B color(f_color->r(), f_color->g(), f_color->b());
        scrollView->setColor(color);
        
        int opacity = widgetOptions->alpha();
        scrollView->setOpacity(opacity);
        
        auto f_innerSize = options->innerSize();
        Size innerSize(f_innerSize->width(), f_innerSize->height());
        scrollView->setInnerContainerSize(innerSize);
        int direction = options->direction();
        scrollView->setDirection((ScrollView::Direction)direction);
        bool bounceEnabled = options->bounceEnabled();
        scrollView->setBounceEnabled(bounceEnabled);
        
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
        
    }
    
    Node* ScrollViewReader::createNodeWithFlatBuffers(const flatbuffers::Table *scrollViewOptions)
    {
        ScrollView* scrollView = ScrollView::create();
        
        setPropsWithFlatBuffers(scrollView, (Table*)scrollViewOptions);
        
        return scrollView;
    }
    
    int ScrollViewReader::getResourceType(std::string key)
    {
        if(key == "Normal" || key == "Default")
        {
            return 	0;
        }
        
        FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
        if(fbs->_isSimulator)
        {
            if(key == "MarkedSubImage")
            {
                return 0;
            }
        }
        return 1;
    }
    
}
