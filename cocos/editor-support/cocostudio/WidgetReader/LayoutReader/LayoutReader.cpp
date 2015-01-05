

#include "LayoutReader.h"

#include "ui/UILayout.h"
#include "cocostudio/CocoLoader.h"
#include "ui/UIScrollView.h"
#include "ui/UIPageView.h"
#include "ui/UIListView.h"
#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/FlatBuffersSerialize.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

namespace cocostudio
{
    static const char* P_CapInsetsX = "capInsetsX";
    static const char* P_CapInsetsY = "capInsetsY";
    static const char* P_CapInsetsWidth = "capInsetsWidth";
    static const char* P_CapInsetsHeight = "capInsetsHeight";
    static const char* P_ClipAble = "clipAble";
    static const char* P_BackGroundScale9Enable = "backGroundScale9Enable";
    static const char* P_BgColorR = "bgColorR";
    static const char* P_BgColorG = "bgColorG";
    static const char* P_BgColorB = "bgColorB";
    static const char* P_BgStartColorR = "bgStartColorR";
    static const char* P_BgStartColorG = "bgStartColorG";
    static const char* P_BgStartColorB = "bgStartColorB";
    static const char* P_BgEndColorR = "bgEndColorR";
    static const char* P_BgEndColorG = "bgEndColorG";
    static const char* P_BgEndColorB = "bgEndColorB";
    static const char* P_VectorX = "vectorX";
    static const char* P_VectorY = "vectorY";
    static const char* P_BgColorOpacity = "bgColorOpacity";
    static const char* P_ColorType = "colorType";
    static const char* P_BackGroundImageData = "backGroundImageData";
    static const char* P_LayoutType = "layoutType";
    
    static LayoutReader* instanceLayoutReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(LayoutReader)
    
    LayoutReader::LayoutReader()
    {
        
    }
    
    LayoutReader::~LayoutReader()
    {
        
    }
    
    LayoutReader* LayoutReader::getInstance()
    {
        if (!instanceLayoutReader)
        {
            instanceLayoutReader = new (std::nothrow) LayoutReader();
        }
        return instanceLayoutReader;
    }
    
    void LayoutReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        Layout* panel = static_cast<Layout*>(widget);

        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        this->beginSetBasicProperties(widget);
        
        int cr=0, cg = 0, cb = 0;
        int scr=0, scg=0, scb=0;
        int ecr=0, ecg=0, ecb= 0;
        float bgcv1 = 0.0f, bgcv2= 0.0f;
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        Layout::Type layoutType = Layout::Type::ABSOLUTE;
        int bgColorOpacity = panel->getBackGroundColorOpacity();
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if(key == P_AdaptScreen){
                _isAdaptScreen = valueToBool(value);
            }
            else if( key == P_ClipAble){
                panel->setClippingEnabled(valueToBool(value));
            }else if(key == P_BackGroundScale9Enable){
                panel->setBackGroundImageScale9Enabled(valueToBool(value));
            }else if(key == P_BgColorR){
                cr = valueToInt(value);
            }else if(key == P_BgColorG){
                cg = valueToInt(value);
            }else if(key == P_BgColorB)
            {
                cb = valueToInt(value);
            }else if(key == P_BgStartColorR){
                scr = valueToInt(value);
            }else if(key == P_BgStartColorG){
                scg = valueToInt(value);
            }else if(key == P_BgStartColorB)
            {
                scb = valueToInt(value);
            }
            else if(key == P_BgEndColorR){
                ecr = valueToInt(value);
            }else if(key == P_BgEndColorG){
                ecg = valueToInt(value);
            }else if(key == P_BgEndColorB)
            {
                ecb = valueToInt(value);
            }else if (key == P_VectorX){
                bgcv1 = valueToFloat(value);
            }else if(key == P_VectorY){
                bgcv2 = valueToFloat(value);
            }else if(key == P_BgColorOpacity){
                bgColorOpacity = valueToInt(value);
            }else if( key == P_ColorType){
                panel->setBackGroundColorType(Layout::BackGroundColorType(valueToInt(value)));
            }else if (key == P_BackGroundImageData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                if (backGroundChildren) {
                    std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                    
                    Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                    
                    std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                    
                    panel->setBackGroundImage(backgroundValue, imageFileNameType);
                }
                
            }else if(key == P_CapInsetsX){
                capsx = valueToFloat(value);
            }else if(key == P_CapInsetsY){
                capsy = valueToFloat(value);
            }else if(key == P_CapInsetsWidth){
                capsWidth = valueToFloat(value);
            }else if(key == P_CapInsetsHeight){
                capsHeight = valueToFloat(value);
            }else if (key == P_LayoutType){
                layoutType = (Layout::Type)valueToInt(value);
            }
            
        }

        
        panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
        panel->setBackGroundColor(Color3B(cr, cg, cb));
        panel->setBackGroundColorVector(Vec2(bgcv1, bgcv2));
        
        
        panel->setBackGroundColorOpacity(bgColorOpacity);
        
        
        panel->setBackGroundImageColor(Color3B(_color.r, _color.g, _color.b));
        
        panel->setBackGroundImageOpacity(_opacity);
        
        if (panel->isBackGroundImageScale9Enabled()) {
            panel->setBackGroundImageCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
        }
        
        panel->setLayoutType(layoutType);
        this->endSetBasicProperties(widget);

    }
    
    void LayoutReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        Layout* panel = static_cast<Layout*>(widget);
        
        /* adapt screen gui */
        float w = 0, h = 0;
        bool adaptScrenn = DICTOOL->getBooleanValue_json(options, P_AdaptScreen);
        if (adaptScrenn)
        {
            Size screenSize = CCDirector::getInstance()->getWinSize();
            w = screenSize.width;
            h = screenSize.height;
        }
        else
        {
            w = DICTOOL->getFloatValue_json(options, P_Width);
            h = DICTOOL->getFloatValue_json(options, P_Height);
        }
        panel->setContentSize(Size(w, h));
        /**/
        
        panel->setClippingEnabled(DICTOOL->getBooleanValue_json(options, P_ClipAble));
        
        bool backGroundScale9Enable = DICTOOL->getBooleanValue_json(options, P_BackGroundScale9Enable);
        panel->setBackGroundImageScale9Enabled(backGroundScale9Enable);
        
        
        int cr;
        int cg;
        int cb;
        int scr;
        int scg;
        int scb;
        int ecr;
        int ecg;
        int ecb;
     
        if (dynamic_cast<ui::PageView*>(widget)) {
            cr = DICTOOL->getIntValue_json(options, P_BgColorR,150);
            cg = DICTOOL->getIntValue_json(options, P_BgColorG,150);
            cb = DICTOOL->getIntValue_json(options, P_BgColorB,100);
            
            scr = DICTOOL->getIntValue_json(options, P_BgStartColorR,255);
            scg = DICTOOL->getIntValue_json(options, P_BgStartColorG,255);
            scb = DICTOOL->getIntValue_json(options, P_BgStartColorB,255);
            
            ecr = DICTOOL->getIntValue_json(options, P_BgEndColorR,255);
            ecg = DICTOOL->getIntValue_json(options, P_BgEndColorG,150);
            ecb = DICTOOL->getIntValue_json(options, P_BgEndColorB,100);
        }else if(dynamic_cast<ui::ListView*>(widget)){
            cr = DICTOOL->getIntValue_json(options, P_BgColorR,150);
            cg = DICTOOL->getIntValue_json(options, P_BgColorG,150);
            cb = DICTOOL->getIntValue_json(options, P_BgColorB,255);
            
            scr = DICTOOL->getIntValue_json(options, P_BgStartColorR,255);
            scg = DICTOOL->getIntValue_json(options, P_BgStartColorG,255);
            scb = DICTOOL->getIntValue_json(options, P_BgStartColorB,255);
            
            ecr = DICTOOL->getIntValue_json(options, P_BgEndColorR,150);
            ecg = DICTOOL->getIntValue_json(options, P_BgEndColorG,150);
            ecb = DICTOOL->getIntValue_json(options, P_BgEndColorB,255);
        }else if(dynamic_cast<ui::ScrollView*>(widget)){
            cr = DICTOOL->getIntValue_json(options, P_BgColorR,255);
            cg = DICTOOL->getIntValue_json(options, P_BgColorG,150);
            cb = DICTOOL->getIntValue_json(options, P_BgColorB,100);
            
            scr = DICTOOL->getIntValue_json(options, P_BgStartColorR,255);
            scg = DICTOOL->getIntValue_json(options, P_BgStartColorG,255);
            scb = DICTOOL->getIntValue_json(options, P_BgStartColorB,255);
            
            ecr = DICTOOL->getIntValue_json(options, P_BgEndColorR,255);
            ecg = DICTOOL->getIntValue_json(options, P_BgEndColorG,150);
            ecb = DICTOOL->getIntValue_json(options, P_BgEndColorB,100);
        }else{
            cr = DICTOOL->getIntValue_json(options, P_BgColorR,150);
            cg = DICTOOL->getIntValue_json(options, P_BgColorG,200);
            cb = DICTOOL->getIntValue_json(options, P_BgColorB,255);
            
            scr = DICTOOL->getIntValue_json(options, P_BgStartColorR,255);
            scg = DICTOOL->getIntValue_json(options, P_BgStartColorG,255);
            scb = DICTOOL->getIntValue_json(options, P_BgStartColorB,255);
            
            ecr = DICTOOL->getIntValue_json(options, P_BgEndColorR,150);
            ecg = DICTOOL->getIntValue_json(options, P_BgEndColorG,200);
            ecb = DICTOOL->getIntValue_json(options, P_BgEndColorB,255);
        }
        
        float bgcv1 = DICTOOL->getFloatValue_json(options, P_VectorX);
        float bgcv2 = DICTOOL->getFloatValue_json(options, P_VectorY,-0.5);
        panel->setBackGroundColorVector(Vec2(bgcv1, bgcv2));
        
        int co = DICTOOL->getIntValue_json(options, P_BgColorOpacity,100);
        
        int colorType = DICTOOL->getIntValue_json(options, P_ColorType,1);
        panel->setBackGroundColorType(Layout::BackGroundColorType(colorType));
        
        panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
        panel->setBackGroundColor(Color3B(cr, cg, cb));
        panel->setBackGroundColorOpacity(co);
        
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, P_BackGroundImageData);
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, P_ResourceType);
        std::string imageFileName = this->getResourcePath(imageFileNameDic, P_Path, (Widget::TextureResType)imageFileNameType);
        panel->setBackGroundImage(imageFileName, (Widget::TextureResType)imageFileNameType);
        

        if (backGroundScale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, P_CapInsetsX);
            float cy = DICTOOL->getFloatValue_json(options, P_CapInsetsY);
            float cw = DICTOOL->getFloatValue_json(options, P_CapInsetsWidth,1);
            float ch = DICTOOL->getFloatValue_json(options, P_CapInsetsHeight,1);
            panel->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
        }
        
        panel->setLayoutType((Layout::Type)DICTOOL->getIntValue_json(options, P_LayoutType));
        
        int bgimgcr = DICTOOL->getIntValue_json(options, P_ColorR,255);
        int bgimgcg = DICTOOL->getIntValue_json(options, P_ColorG,255);
        int bgimgcb = DICTOOL->getIntValue_json(options, P_ColorB,255);
        panel->setBackGroundImageColor(Color3B(bgimgcr, bgimgcg, bgimgcb));
        
        int bgimgopacity = DICTOOL->getIntValue_json(options, P_Opacity, 255);
        panel->setBackGroundImageOpacity(bgimgopacity);
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }    
    
    Offset<Table> LayoutReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
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
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "Size" && backGroundScale9Enabled)
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
        
        auto options = CreatePanelOptions(*builder,
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
                                          backGroundScale9Enabled);
        
        return *(Offset<Table>*)(&options);
    }
    
    void LayoutReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *layoutOptions)
    {
        Layout* panel = static_cast<Layout*>(node);
        auto options = (PanelOptions*)layoutOptions;
        
        bool clipEnabled = options->clipEnabled();
        panel->setClippingEnabled(clipEnabled);
        
        bool backGroundScale9Enabled = options->backGroundScale9Enabled();
        panel->setBackGroundImageScale9Enabled(backGroundScale9Enabled);
        
        
        auto f_bgColor = options->bgColor();
        Color3B bgColor(f_bgColor->r(), f_bgColor->g(), f_bgColor->b());
        auto f_bgStartColor = options->bgStartColor();
        Color3B bgStartColor(f_bgStartColor->r(), f_bgStartColor->g(), f_bgStartColor->b());
        auto f_bgEndColor = options->bgEndColor();
        Color3B bgEndColor(f_bgEndColor->r(), f_bgEndColor->g(), f_bgEndColor->b());
        
        auto f_colorVecor = options->colorVector();
        Vec2 colorVector(f_colorVecor->vectorX(), f_colorVecor->vectorY());
        panel->setBackGroundColorVector(colorVector);
        
        int bgColorOpacity = options->bgColorOpacity();
        
        int colorType = options->colorType();
        panel->setBackGroundColorType(Layout::BackGroundColorType(colorType));
        
        panel->setBackGroundColor(bgStartColor, bgEndColor);
        panel->setBackGroundColor(bgColor);
        panel->setBackGroundColorOpacity(bgColorOpacity);
        
        
        bool fileExist = false;
        std::string errorFilePath = "";
        auto imageFileNameDic = options->backGroundImageData();
        int imageFileNameType = imageFileNameDic->resourceType();
        std::string imageFileName = imageFileNameDic->path()->c_str();
        if (imageFileName != "")
        {
            switch (imageFileNameType)
            {
                case 0:
                {
                    if (FileUtils::getInstance()->isFileExist(imageFileName))
                    {
                        fileExist = true;
                    }
                    else
                    {
                        errorFilePath = imageFileName;
                        fileExist = false;
                    }
                    break;
                }
                    
                case 1:
                {
                    std::string plist = imageFileNameDic->plistFile()->c_str();
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageFileName);
                    if (spriteFrame)
                    {
                        fileExist = true;
                    }
                    else
                    {
                        if (FileUtils::getInstance()->isFileExist(plist))
                        {
                            ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                            ValueMap metadata = value["metadata"].asValueMap();
                            std::string textureFileName = metadata["textureFileName"].asString();
                            if (!FileUtils::getInstance()->isFileExist(textureFileName))
                            {
                                errorFilePath = textureFileName;
                            }
                        }
                        else
                        {
                            errorFilePath = plist;
                        }
                        fileExist = false;
                    }
                    break;
                }
                    
                default:
                    break;
            }
            if (fileExist)
            {
                panel->setBackGroundImage(imageFileName, (Widget::TextureResType)imageFileNameType);
            }
            else
            {
                auto label = Label::create();
                label->setString(__String::createWithFormat("%s missed", errorFilePath.c_str())->getCString());
                panel->addChild(label);
            }
        }
        
        auto widgetOptions = options->widgetOptions();
        auto f_color = widgetOptions->color();
        Color3B color(f_color->r(), f_color->g(), f_color->b());
        panel->setColor(color);
        
        int opacity = widgetOptions->alpha();
        panel->setOpacity(opacity);
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
        
        
        if (backGroundScale9Enabled)
        {
            auto f_capInsets = options->capInsets();
            Rect capInsets(f_capInsets->x(), f_capInsets->y(), f_capInsets->width(), f_capInsets->height());
            panel->setBackGroundImageCapInsets(capInsets);
            
            auto f_scale9Size = options->scale9Size();
            Size scale9Size(f_scale9Size->width(), f_scale9Size->height());
            panel->setContentSize(scale9Size);
        }
        else
        {
            if (!panel->isIgnoreContentAdaptWithSize())
            {
                Size contentSize(widgetOptions->size()->width(), widgetOptions->size()->height());
                panel->setContentSize(contentSize);
            }
        }
        
    }
    
    Node* LayoutReader::createNodeWithFlatBuffers(const flatbuffers::Table *layoutOptions)
    {
        Layout* layout = Layout::create();
        
        setPropsWithFlatBuffers(layout, (Table*)layoutOptions);
        
        return layout;
    }
    
    int LayoutReader::getResourceType(std::string key)
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
