

#include "LayoutReader.h"
#include "ui/UILayout.h"
#include "cocostudio/CocoLoader.h"

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
    
    static LayoutReader* instanceLayoutReader = NULL;
    
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

        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray();
        this->beginSetBasicProperties(widget);
        
        int cr=0, cg = 0, cb = 0;
        int scr=0, scg=0, scb=0;
        int ecr=0, ecg=0, ecb= 0;
        float bgcv1 = 0.0f, bgcv2= 0.0f;
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        Layout::Type layoutType;
        int bgColorOpacity = panel->getBackGroundColorOpacity();
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue();
            
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
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                if (backGroundChildren) {
                    std::string resType = backGroundChildren[2].GetValue();;
                    
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
        int cr = DICTOOL->getIntValue_json(options, P_BgColorR);
        int cg = DICTOOL->getIntValue_json(options, P_BgColorG);
        int cb = DICTOOL->getIntValue_json(options, P_BgColorB);
        
        int scr = DICTOOL->getIntValue_json(options, P_BgStartColorR);
        int scg = DICTOOL->getIntValue_json(options, P_BgStartColorG);
        int scb = DICTOOL->getIntValue_json(options, P_BgStartColorB);
        
        int ecr = DICTOOL->getIntValue_json(options, P_BgEndColorR);
        int ecg = DICTOOL->getIntValue_json(options, P_BgEndColorG);
        int ecb = DICTOOL->getIntValue_json(options, P_BgEndColorB);
        
        float bgcv1 = DICTOOL->getFloatValue_json(options, P_VectorX);
        float bgcv2 = DICTOOL->getFloatValue_json(options, P_VectorY);
        panel->setBackGroundColorVector(Vec2(bgcv1, bgcv2));
        
        int co = DICTOOL->getIntValue_json(options, P_BgColorOpacity);
        
        int colorType = DICTOOL->getIntValue_json(options, P_ColorType);
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
            float cw = DICTOOL->getFloatValue_json(options, P_CapInsetsWidth);
            float ch = DICTOOL->getFloatValue_json(options, P_CapInsetsHeight);
            panel->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
        }
        
        panel->setLayoutType((Layout::Type)DICTOOL->getIntValue_json(options, P_LayoutType));
        
        int bgimgcr = DICTOOL->getIntValue_json(options, P_ColorR);
        int bgimgcg = DICTOOL->getIntValue_json(options, P_ColorG);
        int bgimgcb = DICTOOL->getIntValue_json(options, P_ColorB);
        panel->setBackGroundImageColor(Color3B(bgimgcr, bgimgcg, bgimgcb));
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
