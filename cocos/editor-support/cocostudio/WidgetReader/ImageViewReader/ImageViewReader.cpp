

#include "ImageViewReader.h"
#include "ui/UIImageView.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static const char* P_Scale9Enable = "scale9Enable";
    static const char* P_FileNameData = "fileNameData";
    static const char* P_CapInsetsX = "capInsetsX";
    static const char* P_CapInsetsY = "capInsetsY";
    static const char* P_CapInsetsWidth = "capInsetsWidth";
    static const char* P_CapInsetsHeight = "capInsetsHeight";
    static const char* P_Scale9Width = "scale9Width";
    static const char* P_Scale9Height = "scale9Height";

    
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
    
    void ImageViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        ImageView* imageView = static_cast<ImageView*>(widget);
        this->beginSetBasicProperties(widget);
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray();

        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue();

            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if (key == P_Scale9Enable) {
                imageView->setScale9Enabled(valueToBool(value));
            }
            else if (key == P_FileNameData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);

                imageView->loadTexture(backgroundValue, imageFileNameType);
                
            }
            else if(key == P_Scale9Width){
                imageView->setContentSize(Size(valueToFloat(value), imageView->getContentSize().height));
            }else if(key == P_Scale9Height){
                imageView->setContentSize(Size(imageView->getContentSize().width, valueToFloat(value)));
            }
            else if(key == P_CapInsetsX){
                capsx = valueToFloat(value);
            }else if(key == P_CapInsetsY){
                capsy = valueToFloat(value);
            }else if(key == P_CapInsetsWidth){
                capsWidth = valueToFloat(value);
            }else if(key == P_CapInsetsHeight){
                capsHeight = valueToFloat(value);
            }
            
        } //end of for loop
        
        if (imageView->isScale9Enabled()) {
            imageView->setCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
        }
        
        this->endSetBasicProperties(widget);

    }
    
    void ImageViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        
        ImageView* imageView = static_cast<ImageView*>(widget);
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, P_FileNameData);
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, P_ResourceType);
        std::string imageFileName = this->getResourcePath(imageFileNameDic, P_Path, (Widget::TextureResType)imageFileNameType);
        imageView->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        bool scale9EnableExist = DICTOOL->checkObjectExist_json(options, P_Scale9Enable);
        bool scale9Enable = false;
        if (scale9EnableExist)
        {
            scale9Enable = DICTOOL->getBooleanValue_json(options, P_Scale9Enable);
        }
        imageView->setScale9Enabled(scale9Enable);
        
        
        if (scale9Enable)
        {
            bool sw = DICTOOL->checkObjectExist_json(options, P_Scale9Width);
            bool sh = DICTOOL->checkObjectExist_json(options, P_Scale9Height);
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, P_Scale9Width);
                float shf = DICTOOL->getFloatValue_json(options, P_Scale9Height);
                imageView->setSize(Size(swf, shf));
            }
            
            float cx = DICTOOL->getFloatValue_json(options, P_CapInsetsX);
            float cy = DICTOOL->getFloatValue_json(options, P_CapInsetsY);
            float cw = DICTOOL->getFloatValue_json(options, P_CapInsetsWidth);
            float ch = DICTOOL->getFloatValue_json(options, P_CapInsetsHeight);
            
            imageView->setCapInsets(Rect(cx, cy, cw, ch));
            
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
