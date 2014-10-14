

#include "ImageViewReader.h"
#include "ui/UIImageView.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"

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

    
    static ImageViewReader* instanceImageViewReader = nullptr;
    
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
            instanceImageViewReader = new (std::nothrow) ImageViewReader();
        }
        return instanceImageViewReader;
    }
    
    void ImageViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        ImageView* imageView = static_cast<ImageView*>(widget);
        this->beginSetBasicProperties(widget);
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);

        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);

            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if (key == P_Scale9Enable) {
                imageView->setScale9Enabled(valueToBool(value));
            }
            else if (key == P_FileNameData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
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
        const std::string& imageFilePath = DICTOOL->getStringValue_json(imageFileNameDic, P_Path);

        if (!imageFilePath.empty()) {
        	std::string imageFileName = this->getResourcePath(imageFileNameDic, P_Path, (Widget::TextureResType)imageFileNameType);
        	imageView->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
        }
                
        
        bool scale9EnableExist = DICTOOL->checkObjectExist_json(options, P_Scale9Enable);
        bool scale9Enable = false;
        if (scale9EnableExist)
        {
            scale9Enable = DICTOOL->getBooleanValue_json(options, P_Scale9Enable);
        }
        imageView->setScale9Enabled(scale9Enable);
        
        
        if (scale9Enable)
        {
          
            float swf = DICTOOL->getFloatValue_json(options, P_Scale9Width,80.0f);
            float shf = DICTOOL->getFloatValue_json(options, P_Scale9Height,80.0f);
            imageView->setContentSize(Size(swf, shf));
            
            
            float cx = DICTOOL->getFloatValue_json(options, P_CapInsetsX);
            float cy = DICTOOL->getFloatValue_json(options, P_CapInsetsY);
            float cw = DICTOOL->getFloatValue_json(options, P_CapInsetsWidth,1.0f);
            float ch = DICTOOL->getFloatValue_json(options, P_CapInsetsHeight,1.0f);
            
            imageView->setCapInsets(Rect(cx, cy, cw, ch));
            
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
    
    void ImageViewReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        
        const protocolbuffers::ImageViewOptions& options = nodeTree.imageviewoptions();        
        ImageView* imageView = static_cast<ImageView*>(widget);

		std::string protocolBuffersPath = GUIReader::getInstance()->getFilePath();
        
        const protocolbuffers::ResourceData& imageFileNameDic = options.filenamedata();
        int imageFileNameType = imageFileNameDic.resourcetype();
		if (imageFileNameType == 1)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(protocolBuffersPath + imageFileNameDic.plistfile());			
		}
        std::string imageFileName = this->getResourcePath(imageFileNameDic.path(), (Widget::TextureResType)imageFileNameType);
        imageView->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        bool scale9EnableExist = options.has_scale9enable();
        bool scale9Enable = false;
        if (scale9EnableExist)
        {
            scale9Enable = options.scale9enable();
        }
        imageView->setScale9Enabled(scale9Enable);
        
        
        if (scale9Enable)
        {
            imageView->setUnifySizeEnabled(false);
            imageView->ignoreContentAdaptWithSize(false);
            
            float swf = options.has_scale9width() ? options.scale9width() : 80.0f;
            float shf = options.has_scale9height() ? options.scale9height() : 80.0f;
            imageView->setContentSize(Size(swf, shf));
            
            
            float cx = options.capinsetsx();
            float cy = options.capinsetsy();
            float cw = options.has_capinsetswidth() ? options.capinsetswidth() : 1.0;
            float ch = options.has_capinsetsheight() ? options.capinsetsheight() : 1.0;
            
            imageView->setCapInsets(Rect(cx, cy, cw, ch));
            
        }
        
        // other commonly protperties
        WidgetReader::setColorPropsFromProtocolBuffers(widget, nodeTree);

		bool flipX   = options.flippedx();
		bool flipY   = options.flippedy();
    
		if(flipX != false)
			imageView->setFlippedX(flipX);
		if(flipY != false)
			imageView->setFlippedY(flipY);
    }
    
    void ImageViewReader::setPropsFromXML(cocos2d::ui::Widget *widget, const tinyxml2::XMLElement *objectData)
    {
        WidgetReader::setPropsFromXML(widget, objectData);
        
        ImageView* imageView = static_cast<ImageView*>(widget);
        
        std::string xmlPath = GUIReader::getInstance()->getFilePath();
        
        bool scale9Enabled = false;
        float cx = 0.0f, cy = 0.0f, cw = 0.0f, ch = 0.0f;
        float swf = 0.0f, shf = 0.0f;
        
        int opacity = 255;
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "Scale9Enable")
            {
                if (value == "True")
                {
                    scale9Enabled = true;
                }
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
            else if (name == "Alpha")
            {
                opacity = atoi(value.c_str());
            }
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "Size" && scale9Enabled)
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    std::string name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "X")
                    {
                        swf = atof(value.c_str());
                    }
                    else if (name == "Y")
                    {
                        shf = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "FileData")
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
                int resourceType = 0;
                std::string path = "", plistFile = "";
                
                while (attribute)
                {
                    std::string name = attribute->Name();
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
                
                switch (resourceType)
                {
                    case 0:
                    {
                        imageView->loadTexture(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        imageView->loadTexture(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        imageView->setScale9Enabled(scale9Enabled);
        
        if (scale9Enabled)
        {
            imageView->setCapInsets(Rect(cx, cy, cw, ch));
            imageView->setContentSize(Size(swf, shf));
        }
        
        imageView->setOpacity(opacity);
    }
    
}
