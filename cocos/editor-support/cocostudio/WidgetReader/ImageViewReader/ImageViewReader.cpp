

#include "ImageViewReader.h"
#include "ui/UIImageView.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static ImageViewReader* instanceImageViewReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(ImageViewReader)
    
    ImageViewReader::ImageViewReader()
    {
        
    }
    
    ImageViewReader::~ImageViewReader()
    {
        
    }
    
    ImageViewReader* ImageViewReader::getInstance()
    {
        if (!instanceImageViewReader)
        {
            instanceImageViewReader = new ImageViewReader();
        }
        return instanceImageViewReader;
    }
    
    void ImageViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        
        ImageView* imageView = static_cast<ImageView*>(widget);
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "fileNameData");
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
        std::string imageFileName = this->getResourcePath(imageFileNameDic, "path", (Widget::TextureResType)imageFileNameType);
        imageView->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        bool scale9EnableExist = DICTOOL->checkObjectExist_json(options, "scale9Enable");
        bool scale9Enable = false;
        if (scale9EnableExist)
        {
            scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        }
        imageView->setScale9Enabled(scale9Enable);
        
        
        if (scale9Enable)
        {
            bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
            bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                imageView->setSize(Size(swf, shf));
            }
            
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            
            imageView->setCapInsets(Rect(cx, cy, cw, ch));
            
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
