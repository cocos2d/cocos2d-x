

#include "LayoutReader.h"
#include "ui/UILayout.h"

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
        panel->setBackGroundColorVector(Point(bgcv1, bgcv2));
        
        int co = DICTOOL->getIntValue_json(options, "bgColorOpacity");
        
        int colorType = DICTOOL->getIntValue_json(options, "colorType");
        panel->setBackGroundColorType(LayoutBackGroundColorType(colorType));
        panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
        panel->setBackGroundColor(Color3B(cr, cg, cb));
        panel->setBackGroundColorOpacity(co);
        
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "backGroundImageData");
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
        std::string imageFileName = this->getResourcePath(imageFileNameDic, "path", (TextureResType)imageFileNameType);
        panel->setBackGroundImage(imageFileName, (TextureResType)imageFileNameType);
        
        
        if (backGroundScale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            panel->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
        }
        panel->setLayoutType((LayoutType)DICTOOL->getIntValue_json(options, "layoutType"));
        
        int bgimgcr = DICTOOL->getIntValue_json(options, "colorR");
        int bgimgcg = DICTOOL->getIntValue_json(options, "colorG");
        int bgimgcb = DICTOOL->getIntValue_json(options, "colorB");
        panel->setBackGroundImageColor(Color3B(bgimgcr, bgimgcg, bgimgcb));
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
