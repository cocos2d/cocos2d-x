

#include "LoadingBarReader.h"
#include "ui/UILoadingBar.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace cocostudio
{
    static const char* P_Scale9Enable = "scale9Enable";
    static const char* P_CapInsetsX = "capInsetsX";
    static const char* P_CapInsetsY = "capInsetsY";
    static const char* P_CapInsetsWidth = "capInsetsWidth";
    static const char* P_CapInsetsHeight = "capInsetsHeight";
    static const char* P_TextureData = "textureData";
    static const char* P_Direction = "direction";
    static const char* P_Percent = "percent";
    
    static LoadingBarReader* instanceLoadingBar = nullptr;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(LoadingBarReader)
    
    LoadingBarReader::LoadingBarReader()
    {
        
    }
    
    LoadingBarReader::~LoadingBarReader()
    {
        
    }
    
    LoadingBarReader* LoadingBarReader::getInstance()
    {
        if (!instanceLoadingBar)
        {
            instanceLoadingBar = new (std::nothrow) LoadingBarReader();
        }
        return instanceLoadingBar;
    }
    
    void LoadingBarReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        LoadingBar* loadingBar = static_cast<LoadingBar*>(widget);
        this->beginSetBasicProperties(widget);
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        int percent = loadingBar->getPercent();
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if (key == P_Scale9Enable) {
                loadingBar->setScale9Enabled(valueToBool(value));
            }
            else if (key == P_TextureData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                loadingBar->loadTexture(backgroundValue, imageFileNameType);
                
            }
            else if(key == P_CapInsetsX){
                capsx = valueToFloat(value);
            }else if(key == P_CapInsetsY){
                capsy = valueToFloat(value);
            }else if(key == P_CapInsetsWidth){
                capsWidth = valueToFloat(value);
            }else if(key == P_CapInsetsHeight){
                capsHeight = valueToFloat(value);
            }else if(key == P_Direction){
                loadingBar->setDirection((LoadingBar::Direction)valueToInt(value));
            }else if(key == P_Percent){
                percent = valueToInt(value);
            }
            
        } //end of for loop
        
        if (loadingBar->isScale9Enabled()) {
            loadingBar->setCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
        }
        loadingBar->setPercent(percent);
        this->endSetBasicProperties(widget);
    }
    
    void LoadingBarReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        LoadingBar* loadingBar = static_cast<LoadingBar*>(widget);
        
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, P_TextureData);
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, P_ResourceType);
        std::string imageFileName = this->getResourcePath(imageFileNameDic, P_Path, (Widget::TextureResType)imageFileNameType);
        loadingBar->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);

        
        /* gui mark add load bar scale9 parse */
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, P_Scale9Enable);
        loadingBar->setScale9Enabled(scale9Enable);
        
        
        float cx = DICTOOL->getFloatValue_json(options, P_CapInsetsX);
        float cy = DICTOOL->getFloatValue_json(options, P_CapInsetsY);
        float cw = DICTOOL->getFloatValue_json(options, P_CapInsetsWidth,1);
        float ch = DICTOOL->getFloatValue_json(options, P_CapInsetsHeight,1);
        
        if (scale9Enable) {
            loadingBar->setCapInsets(Rect(cx, cy, cw, ch));

        }
        
        float width = DICTOOL->getFloatValue_json(options, P_Width);
        float height = DICTOOL->getFloatValue_json(options, P_Height);
        loadingBar->setContentSize(Size(width, height));
        
        /**/
        
        loadingBar->setDirection(LoadingBar::Direction(DICTOOL->getIntValue_json(options, P_Direction)));
        loadingBar->setPercent(DICTOOL->getIntValue_json(options, P_Percent,100));
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
    
    void LoadingBarReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        
        LoadingBar* loadingBar = static_cast<LoadingBar*>(widget);
        const protocolbuffers::LoadingBarOptions& options = nodeTree.loadingbaroptions();

		std::string protocolBuffersPath = GUIReader::getInstance()->getFilePath();
        
		const protocolbuffers::ResourceData& imageFileNameDic = options.texturedata();
        int imageFileNameType = imageFileNameDic.resourcetype();
        std::string imageFileName = this->getResourcePath(imageFileNameDic.path(), (Widget::TextureResType)imageFileNameType);
        loadingBar->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        /* gui mark add load bar scale9 parse */
        bool scale9Enable = options.scale9enable();
        loadingBar->setScale9Enabled(scale9Enable);
        
        
        float cx = options.capinsetsx();
        float cy = options.capinsetsy();
        float cw = options.has_capinsetswidth() ? options.capinsetswidth() : 1;
        float ch = options.has_capinsetsheight() ? options.capinsetsheight() : 1;
        
        if (scale9Enable) {
            loadingBar->setCapInsets(Rect(cx, cy, cw, ch));
            
        }
        
		const protocolbuffers::WidgetOptions& widgetOptions = nodeTree.widgetoptions();
        float width = widgetOptions.width();
        float height = widgetOptions.height();
        loadingBar->setContentSize(Size(width, height));
        
        /**/
        
        loadingBar->setDirection(LoadingBar::Direction(options.direction()));
        int percent = options.has_percent() ? options.percent() : 100;
        loadingBar->setPercent(percent);
        
        
        // other commonly protperties
        WidgetReader::setColorPropsFromProtocolBuffers(widget, nodeTree);
    }
    
    void LoadingBarReader::setPropsFromXML(cocos2d::ui::Widget *widget, const tinyxml2::XMLElement *objectData)
    {
        WidgetReader::setPropsFromXML(widget, objectData);
        
        LoadingBar* loadingBar = static_cast<LoadingBar*>(widget);
        
        std::string xmlPath = GUIReader::getInstance()->getFilePath();
        
        bool scale9Enabled = false;
        float cx = 0.0f, cy = 0.0f, cw = 0.0f, ch = 0.0f;
        int direction = 0;
        
        int percent = 0;
        
        int opacity = 255;
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "ProgressType")
            {
                direction = (value == "Left_To_Right") ? 0 : 1;
            }
            else if (name == "ProgressInfo")
            {
                percent = atoi(value.c_str());
            }
            else if (name == "Scale9Enable")
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
            
            if (name == "ImageFileData")
            {
                attribute = child->FirstAttribute();
                int resourceType = 0;
                std::string path = "", plistFile = "";
                
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
                
                switch (resourceType)
                {
                    case 0:
                    {
                        loadingBar->loadTexture(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        loadingBar->loadTexture(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        loadingBar->setDirection((LoadingBar::Direction)direction);
        loadingBar->setPercent(percent);
        
        loadingBar->setOpacity(opacity);
    }
    
}
