

#include "ImageViewReader.h"
#include "ui/UIImageView.h"
#include "cocostudio/CocoLoader.h"

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
    
    void ImageViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, pCocoLoader, pCocoNode);
        
        ImageView* imageView = static_cast<ImageView*>(widget);
        
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();

        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
            
            if (key == "scale9Enable") {
                imageView->setScale9Enabled(valueToBool(value));
            }
            else if (key == "fileNameData"){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                imageView->loadTexture(backgroundValue, imageFileNameType);
                
            }
            else if(key == "scale9Width"){
                imageView->setSize(Size(valueToFloat(value), imageView->getSize().height));
            }else if(key == "scale9Height"){
                imageView->setSize(Size(imageView->getSize().width, valueToFloat(value)));
            }
            else if(key == "capInsetsX"){
                capsx = valueToFloat(value);
            }else if(key == "capInsetsY"){
                capsy = valueToFloat(value);
            }else if(key == "capInsetsWidth"){
                capsWidth = valueToFloat(value);
            }else if(key == "capInsetsHeight"){
                capsHeight = valueToFloat(value);
            }
            
        } //end of for loop
        
        if (imageView->isScale9Enabled()) {
            imageView->setCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
        }

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
