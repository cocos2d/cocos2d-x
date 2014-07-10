

#include "LayoutReader.h"
#include "ui/UILayout.h"
#include "cocostudio/CocoLoader.h"
#include "ui/UIScrollView.h"
#include "ui/UIPageView.h"
#include "ui/UIListView.h"

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
            instanceLayoutReader = new LayoutReader();
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
            cr = DICTOOL->getIntValue_json(options, "bgColorR",150);
            cg = DICTOOL->getIntValue_json(options, "bgColorG",150);
            cb = DICTOOL->getIntValue_json(options, "bgColorB",100);
            
            scr = DICTOOL->getIntValue_json(options, "bgStartColorR",255);
            scg = DICTOOL->getIntValue_json(options, "bgStartColorG",255);
            scb = DICTOOL->getIntValue_json(options, "bgStartColorB",255);
            
            ecr = DICTOOL->getIntValue_json(options, "bgEndColorR",255);
            ecg = DICTOOL->getIntValue_json(options, "bgEndColorG",150);
            ecb = DICTOOL->getIntValue_json(options, "bgEndColorB",100);
        }else if(dynamic_cast<ui::ListView*>(widget)){
            cr = DICTOOL->getIntValue_json(options, "bgColorR",150);
            cg = DICTOOL->getIntValue_json(options, "bgColorG",150);
            cb = DICTOOL->getIntValue_json(options, "bgColorB",255);
            
            scr = DICTOOL->getIntValue_json(options, "bgStartColorR",255);
            scg = DICTOOL->getIntValue_json(options, "bgStartColorG",255);
            scb = DICTOOL->getIntValue_json(options, "bgStartColorB",255);
            
            ecr = DICTOOL->getIntValue_json(options, "bgEndColorR",150);
            ecg = DICTOOL->getIntValue_json(options, "bgEndColorG",150);
            ecb = DICTOOL->getIntValue_json(options, "bgEndColorB",255);
        }else if(dynamic_cast<ui::ScrollView*>(widget)){
            cr = DICTOOL->getIntValue_json(options, "bgColorR",255);
            cg = DICTOOL->getIntValue_json(options, "bgColorG",150);
            cb = DICTOOL->getIntValue_json(options, "bgColorB",100);
            
            scr = DICTOOL->getIntValue_json(options, "bgStartColorR",255);
            scg = DICTOOL->getIntValue_json(options, "bgStartColorG",255);
            scb = DICTOOL->getIntValue_json(options, "bgStartColorB",255);
            
            ecr = DICTOOL->getIntValue_json(options, "bgEndColorR",255);
            ecg = DICTOOL->getIntValue_json(options, "bgEndColorG",150);
            ecb = DICTOOL->getIntValue_json(options, "bgEndColorB",100);
        }else{
            cr = DICTOOL->getIntValue_json(options, "bgColorR",150);
            cg = DICTOOL->getIntValue_json(options, "bgColorG",200);
            cb = DICTOOL->getIntValue_json(options, "bgColorB",255);
            
            scr = DICTOOL->getIntValue_json(options, "bgStartColorR",255);
            scg = DICTOOL->getIntValue_json(options, "bgStartColorG",255);
            scb = DICTOOL->getIntValue_json(options, "bgStartColorB",255);
            
            ecr = DICTOOL->getIntValue_json(options, "bgEndColorR",150);
            ecg = DICTOOL->getIntValue_json(options, "bgEndColorG",200);
            ecb = DICTOOL->getIntValue_json(options, "bgEndColorB",255);
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
        
        int bgimgopacity = DICTOOL->getIntValue_json(options, "opacity",255);
        panel->setBackGroundImageOpacity(bgimgopacity);
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
