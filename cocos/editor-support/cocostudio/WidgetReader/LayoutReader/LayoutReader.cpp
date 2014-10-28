

#include "LayoutReader.h"
#include "ui/UILayout.h"
#include "cocostudio/CocoLoader.h"
#include "ui/UIScrollView.h"
#include "ui/UIPageView.h"
#include "ui/UIListView.h"
#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace ui;

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
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(LayoutReader)
    
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


    void LayoutReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        
        Layout* panel = static_cast<Layout*>(widget);
		const protocolbuffers::PanelOptions& options = nodeTree.paneloptions();

		std::string protocolBuffersPath = GUIReader::getInstance()->getFilePath();
        
        panel->setClippingEnabled(options.clipable());
        
        bool backGroundScale9Enable = options.backgroundscale9enable();
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
        
        if (dynamic_cast<ui::PageView*>(widget))
        {
            cr = options.has_bgcolorr() ? options.bgcolorr() : 150;
            cg = options.has_bgcolorg() ? options.bgcolorg() : 150;
            cb = options.has_bgcolorb() ? options.bgcolorb() : 150;
            
            scr = options.has_bgstartcolorr() ? options.bgstartcolorr() : 255;
            scg = options.has_bgstartcolorg() ? options.bgstartcolorg() : 255;
            scb = options.has_bgstartcolorb() ? options.bgstartcolorb() : 255;
            
            ecr = options.has_bgendcolorr() ? options.bgendcolorr() : 255;
            ecg = options.has_bgendcolorg() ? options.bgendcolorg() : 150;
            ecb = options.has_bgendcolorb() ? options.bgendcolorb() : 100;
        }
        else if(dynamic_cast<ui::ListView*>(widget))
        {
            cr = options.has_bgcolorr() ? options.bgcolorr() : 150;
            cg = options.has_bgcolorg() ? options.bgcolorg() : 150;
            cb = options.has_bgcolorb() ? options.bgcolorb() : 255;
            
            scr = options.has_bgstartcolorr() ? options.bgstartcolorr() : 255;
            scg = options.has_bgstartcolorg() ? options.bgstartcolorg() : 255;
            scb = options.has_bgstartcolorb() ? options.bgstartcolorb() : 255;
            
            ecr = options.has_bgendcolorr() ? options.bgendcolorr() : 150;
            ecg = options.has_bgendcolorg() ? options.bgendcolorg() : 150;
            ecb = options.has_bgendcolorb() ? options.bgendcolorb() : 255;
        }
        else if(dynamic_cast<ui::ScrollView*>(widget))
        {
            cr = options.has_bgcolorr() ? options.bgcolorr() : 255;
            cg = options.has_bgcolorg() ? options.bgcolorg() : 150;
            cb = options.has_bgcolorb() ? options.bgcolorb() : 100;
            
            scr = options.has_bgstartcolorr() ? options.bgstartcolorr() : 255;
            scg = options.has_bgstartcolorg() ? options.bgstartcolorg() : 255;
            scb = options.has_bgstartcolorb() ? options.bgstartcolorb() : 255;
            
            ecr = options.has_bgendcolorr() ? options.bgendcolorr() : 255;
            ecg = options.has_bgendcolorg() ? options.bgendcolorg() : 150;
            ecb = options.has_bgendcolorb() ? options.bgendcolorb() : 100;
        }
        else
        {
            cr = options.has_bgcolorr() ? options.bgcolorr() : 150;
            cg = options.has_bgcolorg() ? options.bgcolorg() : 200;
            cb = options.has_bgcolorb() ? options.bgcolorb() : 255;
            
            scr = options.has_bgstartcolorr() ? options.bgstartcolorr() : 255;
            scg = options.has_bgstartcolorg() ? options.bgstartcolorg() : 255;
            scb = options.has_bgstartcolorb() ? options.bgstartcolorb() : 255;
            
            ecr = options.has_bgendcolorr() ? options.bgendcolorr() : 150;
            ecg = options.has_bgendcolorg() ? options.bgendcolorg() : 200;
            ecb = options.has_bgendcolorb() ? options.bgendcolorb() : 255;
        }
        
        float bgcv1 = 0.0f;
        float bgcv2 = -0.5f;
		if(options.has_vectorx())
		{
			bgcv1 = options.vectorx();
		}
		if(options.has_vectory())
		{
			bgcv2 = options.vectory();
		}
        panel->setBackGroundColorVector(Vec2(bgcv1, bgcv2));
        
        int co = options.has_bgcoloropacity() ? options.bgcoloropacity() : 100;
        
        int colorType = options.has_colortype() ? options.colortype() : 1;
        panel->setBackGroundColorType(Layout::BackGroundColorType(colorType));
        
        panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
        panel->setBackGroundColor(Color3B(cr, cg, cb));
        panel->setBackGroundColorOpacity(co);
        
        
		const protocolbuffers::ResourceData& imageFileNameDic = options.backgroundimagedata();
        int imageFileNameType = imageFileNameDic.resourcetype();
        std::string imageFileName = this->getResourcePath(imageFileNameDic.path(), (Widget::TextureResType)imageFileNameType);
        panel->setBackGroundImage(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        if (backGroundScale9Enable)
        {
            float cx = options.capinsetsx();
            float cy = options.capinsetsy();
            float cw = options.has_capinsetswidth() ? options.capinsetswidth() : 1;
            float ch = options.has_capinsetsheight() ? options.capinsetsheight() : 1;
            panel->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));

            bool sw = options.has_scale9width();
            bool sh = options.has_scale9height();
            if (sw && sh)
            {
                float swf = options.scale9width();
                float shf = options.scale9height();
                panel->setContentSize(Size(swf, shf));
            }
        }
        
        panel->setLayoutType((Layout::Type)options.layouttype());
        
        const protocolbuffers::WidgetOptions& widgetOptions = nodeTree.widgetoptions();
        
        int red = widgetOptions.has_colorr() ? widgetOptions.colorr() : 255;
        int green = widgetOptions.has_colorg() ? widgetOptions.colorg() : 255;
        int blue = widgetOptions.has_colorb() ? widgetOptions.colorb() : 255;
        panel->setColor(Color3B(red, green, blue));
        
        int opacity = widgetOptions.has_alpha() ? widgetOptions.alpha() : 255;
        panel->setOpacity(opacity);
        
        
        // other commonly protperties
        setAnchorPointForWidget(widget, nodeTree);
        
        bool flipX = widgetOptions.flipx();
        bool flipY = widgetOptions.flipy();
        if (flipX)
        {
            widget->setFlippedX(flipX);
        }
        if (flipY)
        {
            widget->setFlippedY(flipY);
        }
    }
    
    void LayoutReader::setPropsFromXML(cocos2d::ui::Widget *widget, const tinyxml2::XMLElement *objectData)
    {
        WidgetReader::setPropsFromXML(widget, objectData);
        
        Layout* panel = static_cast<Layout*>(widget);
        
        std::string xmlPath = GUIReader::getInstance()->getFilePath();
        
        bool scale9Enabled = false;
        float width = 0.0f, height = 0.0f;
        float cx = 0.0f, cy = 0.0f, cw = 0.0f, ch = 0.0f;
        
        Layout::BackGroundColorType colorType = Layout::BackGroundColorType::NONE;
        int color_opacity = 255, bgimg_opacity = 255, opacity = 255;
        int red = 255, green = 255, blue = 255;
        int bgimg_red = 255, bgimg_green = 255, bgimg_blue = 255;
        int singleRed = 255, singleGreen = 255, singleBlue = 255;
        int start_red = 255, start_green = 255, start_blue = 255;
        int end_red = 255, end_green = 255, end_blue = 255;
        float vector_color_x = 0.0f, vector_color_y = -0.5f;
        
        int resourceType = 0;
        std::string path = "", plistFile = "";
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "ClipAble")
            {
                panel->setClippingEnabled((value == "True") ? true : false);
            }
            else if (name == "ComboBoxIndex")
            {
                colorType = (Layout::BackGroundColorType)atoi(value.c_str());
            }
            else if (name == "BackColorAlpha")
            {
                color_opacity = atoi(value.c_str());
            }
            else if (name == "Alpha")
            {
                opacity = atoi(value.c_str());
                bgimg_opacity = atoi(value.c_str());
            }
            else if (name == "Scale9Enable")
            {
                scale9Enabled = (value == "True") ? true : false;
            }
            else if (name == "Scale9OriginX")
            {
                cx = atof(value.c_str());
            }
            else if (name == "Scale9OriginY")
            {
                cy = atof(value.c_str());
            }
            else if (name == "Scale9Width")
            {
                cw = atof(value.c_str());
            }
            else if (name == "Scale9Height")
            {
                ch = atof(value.c_str());
            }
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "Size")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "X")
                    {
                        width = atof(value.c_str());
                    }
                    else if (name == "Y")
                    {
                        height = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "CColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        red = atoi(value.c_str());
                        bgimg_red = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        green = atoi(value.c_str());
                        bgimg_green = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        blue = atoi(value.c_str());
                        bgimg_blue = atoi(value.c_str());
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
                        singleRed = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        singleGreen = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        singleBlue = atoi(value.c_str());
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
                        end_red = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        end_green = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        end_blue = atoi(value.c_str());
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
                        start_red = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        start_green = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        start_blue = atoi(value.c_str());
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
                        vector_color_x = atof(value.c_str());
                    }
                    else if (name == "ScaleY")
                    {
                        vector_color_y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "FileData")
            {
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
                        resourceType = (value == "Normal" || value == "Default" || value == "MarkedSubImage") ? 0 : 1;
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        panel->setBackGroundColorType(colorType);
        switch (colorType)
        {
            case Layout::BackGroundColorType::SOLID:
                panel->setBackGroundColor(Color3B(singleRed, singleGreen, singleBlue));
                break;
                
            case Layout::BackGroundColorType::GRADIENT:
                panel->setBackGroundColor(Color3B(start_red, start_green, start_blue),
                                          Color3B(end_red, end_green, end_blue));
                panel->setBackGroundColorVector(Vec2(vector_color_x, vector_color_y));
                break;
                
            default:
                break;
        }
        
        panel->setColor(Color3B(red, green, blue));
        panel->setOpacity(opacity);
        
        panel->setBackGroundColorOpacity(color_opacity);
        
        switch (resourceType)
        {
            case 0:
            {
                panel->setBackGroundImage(xmlPath + path, Widget::TextureResType::LOCAL);
                break;
            }
                
            case 1:
            {
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                panel->setBackGroundImage(path, Widget::TextureResType::PLIST);
                break;
            }
                
            default:
                break;
        }
        
        if (path != "")
        {
            if (scale9Enabled)
            {
                panel->setBackGroundImageScale9Enabled(scale9Enabled);
                panel->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
                panel->setContentSize(Size(width, height));
            }
        }
        
    }
}
