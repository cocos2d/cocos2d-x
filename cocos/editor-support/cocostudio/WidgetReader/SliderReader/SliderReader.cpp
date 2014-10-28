

#include "SliderReader.h"
#include "ui/UISlider.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static const char* P_Scale9Enable = "scale9Enable";
    static const char* P_Percent = "percent";
    static const char* P_BarFileNameData = "barFileNameData";
    static const char* P_Length = "length";
    static const char* P_BallNormalData = "ballNormalData";
    static const char* P_BallPressedData = "ballPressedData";
    static const char* P_BallDisabledData = "ballDisabledData";
    static const char* P_ProgressBarData = "progressBarData";
    
    static SliderReader* instanceSliderReader = nullptr;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(SliderReader)
    
    SliderReader::SliderReader()
    {
        
    }
    
    SliderReader::~SliderReader()
    {
        
    }
    
    SliderReader* SliderReader::getInstance()
    {
        if (!instanceSliderReader)
        {
            instanceSliderReader = new (std::nothrow) SliderReader();
        }
        return instanceSliderReader;
    }
    
    void SliderReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode* cocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        Slider* slider = static_cast<Slider*>(widget);
        
        float barLength = 0.0f;
        int percent = slider->getPercent();
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            //control custom properties
            else if (key == P_Scale9Enable) {
                slider->setScale9Enabled(valueToBool(value));
            }
            else if(key == P_Percent){
                percent = valueToInt(value);
            }else if(key == P_BarFileNameData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadBarTexture(backgroundValue, imageFileNameType);
                
            }else if(key == P_Length){
                barLength = valueToFloat(value);
            }else if(key == P_BallNormalData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadSlidBallTextureNormal(backgroundValue, imageFileNameType);

            }else if(key == P_BallPressedData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadSlidBallTexturePressed(backgroundValue, imageFileNameType);
                
            }else if(key == P_BallDisabledData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadSlidBallTextureDisabled(backgroundValue, imageFileNameType);
                
            }else if(key == P_ProgressBarData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                slider->loadProgressBarTexture(backgroundValue, imageFileNameType);
                
            }
            
        } //end of for loop
        
        if (slider->isScale9Enabled()) {
            slider->setContentSize(Size(barLength, slider->getContentSize().height));
        }
        slider->setPercent(percent);
        
        this->endSetBasicProperties(widget);
    }
    
    void SliderReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
                
        Slider* slider = static_cast<Slider*>(widget);
        
        bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, P_Scale9Enable);
        slider->setScale9Enabled(barTextureScale9Enable);
        
        slider->setPercent(DICTOOL->getIntValue_json(options, P_Percent));

        
//        bool bt = DICTOOL->checkObjectExist_json(options, P_BarFileName);
        float barLength = DICTOOL->getFloatValue_json(options, P_Length,290);
        const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, P_BarFileNameData);
        int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, P_ResourceType);
        std::string imageFileName = this->getResourcePath(imageFileNameDic, P_Path, (Widget::TextureResType)imageFileNameType);
        slider->loadBarTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
            
           
        
        if (barTextureScale9Enable)
        {
            slider->setContentSize(Size(barLength, slider->getContentSize().height));
        }
        
        //loading normal slider ball texture
        const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, P_BallNormalData);
        int normalType = DICTOOL->getIntValue_json(normalDic, P_ResourceType);
        imageFileName = this->getResourcePath(normalDic, P_Path, (Widget::TextureResType)normalType);
        slider->loadSlidBallTextureNormal(imageFileName, (Widget::TextureResType)normalType);
        
        
        //loading slider ball press texture
        const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, P_BallPressedData);
        int pressedType = DICTOOL->getIntValue_json(pressedDic, P_ResourceType);
        std::string pressedFileName = this->getResourcePath(pressedDic, P_Path, (Widget::TextureResType)pressedType);
        slider->loadSlidBallTexturePressed(pressedFileName, (Widget::TextureResType)pressedType);
        
        //loading silder ball disable texture
        const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, P_BallDisabledData);
        int disabledType = DICTOOL->getIntValue_json(disabledDic, P_ResourceType);
        std::string disabledFileName = this->getResourcePath(disabledDic, P_Path, (Widget::TextureResType)disabledType);
        slider->loadSlidBallTextureDisabled(disabledFileName, (Widget::TextureResType)disabledType);
        
        //load slider progress texture
        const rapidjson::Value& progressBarDic = DICTOOL->getSubDictionary_json(options, P_ProgressBarData);
        int progressBarType = DICTOOL->getIntValue_json(progressBarDic, P_ResourceType);
        std::string progressBarFileName = this->getResourcePath(progressBarDic, P_Path, (Widget::TextureResType)progressBarType);
        slider->loadProgressBarTexture(progressBarFileName, (Widget::TextureResType)progressBarType);
        
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
    
    void SliderReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        
        Slider* slider = static_cast<Slider*>(widget);
        const protocolbuffers::SliderOptions& options = nodeTree.slideroptions();

		std::string protocolBuffersPath = GUIReader::getInstance()->getFilePath();
        
        bool barTextureScale9Enable = options.scale9enable();
        if (barTextureScale9Enable)
        {
            slider->setUnifySizeEnabled(false);
        }
        slider->setScale9Enabled(barTextureScale9Enable);
        
        slider->setPercent(options.percent());
        
        
        //        bool bt = DICTOOL->checkObjectExist_json(options, P_BarFileName);
        float barLength = options.has_length() ? options.length() : 290;
        
		const protocolbuffers::ResourceData& imageFileNameDic = options.barfilenamedata();
        int imageFileNameType = imageFileNameDic.resourcetype();
        std::string imageFileName = this->getResourcePath(imageFileNameDic.path(), (Widget::TextureResType)imageFileNameType);
        slider->loadBarTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
        
        
        
        if (barTextureScale9Enable)
        {
            slider->setContentSize(Size(barLength, slider->getContentSize().height));
        }
        
        //loading normal slider ball texture
        const protocolbuffers::ResourceData& normalDic = options.ballnormaldata();
        int normalType = normalDic.resourcetype();
        imageFileName = this->getResourcePath(normalDic.path(), (Widget::TextureResType)normalType);
        slider->loadSlidBallTextureNormal(imageFileName, (Widget::TextureResType)normalType);
        
        
        //loading slider ball press texture
        const protocolbuffers::ResourceData& pressedDic = options.ballpresseddata();
        int pressedType = pressedDic.resourcetype();
        std::string pressedFileName = this->getResourcePath(pressedDic.path(), (Widget::TextureResType)pressedType);
        slider->loadSlidBallTexturePressed(pressedFileName, (Widget::TextureResType)pressedType);
        
        //loading silder ball disable texture
        const protocolbuffers::ResourceData& disabledDic = options.balldisableddata();
        int disabledType = disabledDic.resourcetype();
        std::string disabledFileName = this->getResourcePath(disabledDic.path(), (Widget::TextureResType)disabledType);
        slider->loadSlidBallTextureDisabled(disabledFileName, (Widget::TextureResType)disabledType);
        
        //load slider progress texture
        const protocolbuffers::ResourceData& progressBarDic = options.progressbardata();
        int progressBarType = progressBarDic.resourcetype();
        std::string progressBarFileName = this->getResourcePath(progressBarDic.path(), (Widget::TextureResType)progressBarType);
        slider->loadProgressBarTexture(progressBarFileName, (Widget::TextureResType)progressBarType);
        
        bool displaystate = true;
		if(options.has_displaystate())
		{
			displaystate = options.displaystate();
		}
		slider->setBright(displaystate);

        // other commonly protperties
        WidgetReader::setColorPropsFromProtocolBuffers(widget, nodeTree);
    }
    
    void SliderReader::setPropsFromXML(cocos2d::ui::Widget *widget, const tinyxml2::XMLElement *objectData)
    {
        WidgetReader::setPropsFromXML(widget, objectData);
        
        Slider* slider = static_cast<Slider*>(widget);
        
        std::string xmlPath = GUIReader::getInstance()->getFilePath();
        
        bool scale9Enabled = false;
        float cx = 0.0f, cy = 0.0f, cw = 0.0f, ch = 0.0f;
        float swf = 0.0f, shf = 0.0f;
        
        int percent = 0;
        
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
            else if (name == "Length")
            {
                
            }
            else if (name == "PercentInfo")
            {
                percent = atoi(value.c_str());
            }
            else if (name == "DisplayState")
            {
                slider->setBright((value == "True") ? true : false);
                if (value == "False")
                {
                    slider->setTouchEnabled(false);
                }
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
            
            if (name == "BackGroundData")
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
                        slider->loadBarTexture(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        slider->loadBarTexture(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            else if (name == "BallNormalData")
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
                        slider->loadSlidBallTextureNormal(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        slider->loadSlidBallTextureNormal(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            else if (name == "BallPressedData")
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
                        slider->loadSlidBallTexturePressed(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        slider->loadSlidBallTexturePressed(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            else if (name == "BallDisabledData")
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
                        slider->loadSlidBallTextureDisabled(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        slider->loadSlidBallTextureDisabled(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            else if (name == "ProgressBarData")
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
                        slider->loadProgressBarTexture(xmlPath + path, Widget::TextureResType::LOCAL);
                        break;
                    }
                        
                    case 1:
                    {
                        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(xmlPath + plistFile);
                        slider->loadProgressBarTexture(path, Widget::TextureResType::PLIST);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        slider->setScale9Enabled(scale9Enabled);
        
        if (scale9Enabled)
        {
            slider->setCapInsets(Rect(cx, cy, cw, ch));
            slider->setContentSize(Size(swf, shf));
        }
        
        slider->setPercent(percent);
        
        slider->setOpacity(opacity);
    }
    
}
