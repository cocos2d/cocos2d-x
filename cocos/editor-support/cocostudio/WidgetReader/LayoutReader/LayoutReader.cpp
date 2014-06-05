

#include "LayoutReader.h"
#include "ui/UILayout.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
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
    
    void LayoutReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
        
        Layout* panel = static_cast<Layout*>(widget);

        float w = 0, h= 0;
        
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        
        int cr=0, cg = 0, cb = 0;
        int scr=0, scg=0, scb=0;
        int ecr=0, ecg=0, ecb= 0;
        float bgcv1 = 0.0f, bgcv2= 0.0f;
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        Layout::Type layoutType;
        
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
            
            if (key == "adaptScreen") {
                bool adptScreen = valueToBool(value);
                if (adptScreen) {
                    Size screenSize = CCDirector::getInstance()->getWinSize();
                    w = screenSize.width;
                    h = screenSize.height;
                }else{
                    w = widget->getSize().width;
                    h = widget->getSize().height;
                }
                panel->setSize(Size(w,h));
            }else if( key == "clipAble"){
                panel->setClippingEnabled(valueToBool(value));
            }else if(key == "backGroundScale9Enable"){
                panel->setBackGroundImageScale9Enabled(valueToBool(value));
            }else if(key == "bgColorR"){
                cr = valueToInt(value);
            }else if(key == "bgColorG"){
                cg = valueToInt(value);
            }else if(key == "bgColorB")
            {
                cb = valueToInt(value);
            }else if(key == "bgStartColorR"){
                scr = valueToInt(value);
            }else if(key == "bgStartColorG"){
                scg = valueToInt(value);
            }else if(key == "bgStartColorB")
            {
                scb = valueToInt(value);
            }
            else if(key == "bgEndColorR"){
                ecr = valueToInt(value);
            }else if(key == "bgEndColorG"){
                ecg = valueToInt(value);
            }else if(key == "bgEndColorB")
            {
                ecb = valueToInt(value);
            }else if (key == "vectorX"){
                bgcv1 = valueToFloat(value);
            }else if(key == "vectorY"){
                bgcv2 = valueToFloat(value);
            }else if(key == "bgColorOpacity"){
                panel->setBackGroundColorOpacity(valueToInt(value));
            }else if( key == "colorType"){
                panel->setBackGroundColorType(Layout::BackGroundColorType(valueToInt(value)));
            }else if (key == "backGroundImageData"){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                if (backGroundChildren) {
                    std::string resType = backGroundChildren[2].GetValue();;
                    
                    Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                    
                    std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                    
                    panel->setBackGroundImage(backgroundValue,imageFileNameType);
                }
                
            }else if(key == "capInsetsX"){
                capsx = valueToFloat(value);
            }else if(key == "capInsetsY"){
                capsy = valueToFloat(value);
            }else if(key == "capInsetsWidth"){
                capsWidth = valueToFloat(value);
            }else if(key == "capInsetsHeight"){
                capsHeight = valueToFloat(value);
            }else if (key == "layoutType"){
                layoutType = (Layout::Type)valueToInt(value);
            }
            
        }
        
        panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
        panel->setBackGroundColor(Color3B(cr, cg, cb));
        panel->setBackGroundColorVector(Vec2(bgcv1, bgcv2));
        
        if (panel->isBackGroundImageScale9Enabled()) {
            panel->setBackGroundImageCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
        }
        
        panel->setLayoutType(layoutType);

    }
    
    void LayoutReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        Layout* panel = static_cast<Layout*>(widget);
        
        /* adapt screen gui */
        float w = 0, h = 0;
        bool adaptScrenn = DICTOOL->getBooleanValue_json(options, "adaptScreen");
        if (adaptScrenn)
        {
            Size screenSize = CCDirector::getInstance()->getWinSize();
            w = screenSize.width;
            h = screenSize.height;
        }
        else
        {
            w = DICTOOL->getFloatValue_json(options, "width");
            h = DICTOOL->getFloatValue_json(options, "height");
        }
        panel->setSize(Size(w, h));
        /**/
        
        panel->setClippingEnabled(DICTOOL->getBooleanValue_json(options, "clipAble"));
        
        bool backGroundScale9Enable = DICTOOL->getBooleanValue_json(options, "backGroundScale9Enable");
        panel->setBackGroundImageScale9Enabled(backGroundScale9Enable);
        int cr = DICTOOL->getIntValue_json(options, "bgColorR");
        int cg = DICTOOL->getIntValue_json(options, "bgColorG");
        int cb = DICTOOL->getIntValue_json(options, "bgColorB");
        
        int scr = DICTOOL->getIntValue_json(options, "bgStartColorR");
        int scg = DICTOOL->getIntValue_json(options, "bgStartColorG");
        int scb = DICTOOL->getIntValue_json(options, "bgStartColorB");
        
        int ecr = DICTOOL->getIntValue_json(options, "bgEndColorR");
        int ecg = DICTOOL->getIntValue_json(options, "bgEndColorG");
        int ecb = DICTOOL->getIntValue_json(options, "bgEndColorB");
        
        float bgcv1 = DICTOOL->getFloatValue_json(options, "vectorX");
        float bgcv2 = DICTOOL->getFloatValue_json(options, "vectorY");
        panel->setBackGroundColorVector(Vec2(bgcv1, bgcv2));
        
        int co = DICTOOL->getIntValue_json(options, "bgColorOpacity");
        
        int colorType = DICTOOL->getIntValue_json(options, "colorType");
        panel->setBackGroundColorType(Layout::BackGroundColorType(colorType));
        panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
        panel->setBackGroundColor(Color3B(cr, cg, cb));
        panel->setBackGroundColorOpacity(co);
        
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "backGroundImageData");
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
        std::string imageFileName = this->getResourcePath(imageFileNameDic, "path", (Widget::TextureResType)imageFileNameType);
        panel->setBackGroundImage(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        if (backGroundScale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            panel->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
        }
        panel->setLayoutType((Layout::Type)DICTOOL->getIntValue_json(options, "layoutType"));
        
        int bgimgcr = DICTOOL->getIntValue_json(options, "colorR");
        int bgimgcg = DICTOOL->getIntValue_json(options, "colorG");
        int bgimgcb = DICTOOL->getIntValue_json(options, "colorB");
        panel->setBackGroundImageColor(Color3B(bgimgcr, bgimgcg, bgimgcb));
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
