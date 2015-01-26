

#include "SliderReader.h"

#include "ui/UISlider.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/FlatBuffersSerialize.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

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
    
    IMPLEMENT_CLASS_NODE_READER_INFO(SliderReader)
    
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
    
    Offset<Table> SliderReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                             flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        std::string barFileNamePath = "";
        std::string barFileNamePlistFile = "";
        int barFileNameResourceType = 0;
        
        std::string ballNormalPath = "";
        std::string ballNormalPlistFile = "";
        int ballNormalResourceType = 0;
        
        std::string ballPressedPath = "";
        std::string ballPressedPlistFile = "";
        int ballPressedResourceType = 0;
        
        std::string ballDisabledPath = "";
        std::string ballDisabledPlistFile = "";
        int ballDisabledResourceType = 0;
        
        std::string progressBarPath = "";
        std::string progressBarPlistFile = "";
        int progressBarResourceType = 0;
        
        int percent = 0;
        bool displaystate = true;
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "PercentInfo")
            {
                percent = atoi(value.c_str());
            }
            else if (name == "DisplayState")
            {
                displaystate = (value == "True") ? true : false;
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
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        barFileNamePath = value;
                    }
                    else if (name == "Type")
                    {
                        barFileNameResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        barFileNamePlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (barFileNameResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "BallNormalData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        ballNormalPath = value;
                    }
                    else if (name == "Type")
                    {
                        ballNormalResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        ballNormalPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (ballNormalResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "BallPressedData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        ballPressedPath = value;
                    }
                    else if (name == "Type")
                    {
                        ballPressedResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        ballPressedPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (ballPressedResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "BallDisabledData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        ballDisabledPath = value;
                    }
                    else if (name == "Type")
                    {
                        ballDisabledResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        ballDisabledPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (ballDisabledResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "ProgressBarData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        progressBarPath = value;
                    }
                    else if (name == "Type")
                    {
                        progressBarResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        progressBarPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (progressBarResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));                    
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateSliderOptions(*builder,
                                           widgetOptions,
                                           CreateResourceData(*builder,
                                                              builder->CreateString(barFileNamePath),
                                                              builder->CreateString(barFileNamePlistFile),
                                                              barFileNameResourceType),
                                           CreateResourceData(*builder,
                                                              builder->CreateString(ballNormalPath),
                                                              builder->CreateString(ballNormalPlistFile),
                                                              ballNormalResourceType),
                                           CreateResourceData(*builder,
                                                              builder->CreateString(ballPressedPath),
                                                              builder->CreateString(ballPressedPlistFile),
                                                              ballPressedResourceType),
                                           CreateResourceData(*builder,
                                                              builder->CreateString(ballDisabledPath),
                                                              builder->CreateString(ballDisabledPlistFile),
                                                              ballDisabledResourceType),
                                           CreateResourceData(*builder,
                                                              builder->CreateString(progressBarPath),
                                                              builder->CreateString(progressBarPlistFile),
                                                              progressBarResourceType),
                                           percent,
                                           displaystate);
        
        return *(Offset<Table>*)(&options);
    }
    
    void SliderReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *sliderOptions)
    {
        Slider* slider = static_cast<Slider*>(node);
        auto options = (SliderOptions*)sliderOptions;
        
        int percent = options->percent();
        slider->setPercent(percent);
        
        bool imageFileExist = false;
        std::string imageErrorFilePath = "";
        auto imageFileNameDic = options->barFileNameData();
        int imageFileNameType = imageFileNameDic->resourceType();
        std::string imageFileName = imageFileNameDic->path()->c_str();
        switch (imageFileNameType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(imageFileName))
                {
                    imageFileExist = true;
                }
                else
                {
                    imageErrorFilePath = imageFileName;
                    imageFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = imageFileNameDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageFileName);
                if (spriteFrame)
                {
                    imageFileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            imageErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        imageErrorFilePath = plist;
                    }
                    imageFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (imageFileExist)
        {
            slider->loadBarTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", imageErrorFilePath.c_str())->getCString());
            slider->addChild(label);
        }
        
        //loading normal slider ball texture
        bool normalFileExist = false;
        std::string normalErrorFilePath = "";
        auto normalDic = options->ballNormalData();
        int normalType = normalDic->resourceType();
        std::string normalFileName = normalDic->path()->c_str();
        switch (normalType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(normalFileName))
                {
                    normalFileExist = true;
                }
                else
                {
                    normalErrorFilePath = normalFileName;
                    normalFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = normalDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(normalFileName);
                if (spriteFrame)
                {
                    normalFileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            normalErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        normalErrorFilePath = plist;
                    }
                    normalFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (normalFileExist)
        {
            slider->loadSlidBallTextureNormal(normalFileName, (Widget::TextureResType)normalType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", normalErrorFilePath.c_str())->getCString());
            slider->addChild(label);
        }
        
        //loading slider ball press texture
        bool pressedFileExist = false;
        std::string pressedErrorFilePath = "";
        auto pressedDic = options->ballPressedData();
        int pressedType = pressedDic->resourceType();
        std::string pressedFileName = pressedDic->path()->c_str();
        switch (pressedType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(pressedFileName))
                {
                    pressedFileExist = true;
                }
                else
                {
                    pressedErrorFilePath = pressedFileName;
                    pressedFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = pressedDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pressedFileName);
                if (spriteFrame)
                {
                    pressedFileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            pressedErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        pressedErrorFilePath = plist;
                    }
                    pressedFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (pressedFileExist)
        {
            slider->loadSlidBallTexturePressed(pressedFileName, (Widget::TextureResType)pressedType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", pressedErrorFilePath.c_str())->getCString());
            slider->addChild(label);
        }
        
        //loading silder ball disable texture
        bool disabledFileExist = false;
        std::string disabledErrorFilePath = "";
        auto disabledDic = options->ballDisabledData();
        int disabledType = disabledDic->resourceType();
        std::string disabledFileName = disabledDic->path()->c_str();
        switch (disabledType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(disabledFileName))
                {
                    disabledFileExist = true;
                }
                else
                {
                    disabledErrorFilePath = disabledFileName;
                    disabledFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = disabledDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(disabledFileName);
                if (spriteFrame)
                {
                    disabledFileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            disabledErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        disabledErrorFilePath = plist;
                    }
                    disabledFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (disabledFileExist)
        {
            slider->loadSlidBallTextureDisabled(disabledFileName, (Widget::TextureResType)disabledType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", disabledErrorFilePath.c_str())->getCString());
            slider->addChild(label);
        }
        
        //load slider progress texture
        bool progressFileExist = false;
        std::string progressErrorFilePath = "";
        auto progressBarDic = options->progressBarData();
        int progressBarType = progressBarDic->resourceType();
        std::string progressBarFileName = progressBarDic->path()->c_str();
        switch (progressBarType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(progressBarFileName))
                {
                    progressFileExist = true;
                }
                else
                {
                    progressErrorFilePath = progressBarFileName;
                    progressFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = progressBarDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(progressBarFileName);
                if (spriteFrame)
                {
                    progressFileExist = true;
                }
                else
                {
                    if (FileUtils::getInstance()->isFileExist(plist))
                    {
                        ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                        ValueMap metadata = value["metadata"].asValueMap();
                        std::string textureFileName = metadata["textureFileName"].asString();
                        if (!FileUtils::getInstance()->isFileExist(textureFileName))
                        {
                            progressErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        progressErrorFilePath = plist;
                    }
                    progressFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (progressFileExist)
        {
            slider->loadProgressBarTexture(progressBarFileName, (Widget::TextureResType)progressBarType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", progressErrorFilePath.c_str())->getCString());
            slider->addChild(label);
        }
        
        bool displaystate = options->displaystate() != 0;
        slider->setBright(displaystate);
        slider->setEnabled(displaystate);
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
        
    }
    
    Node* SliderReader::createNodeWithFlatBuffers(const flatbuffers::Table *sliderOptions)
    {
        Slider* slider = Slider::create();
        
        setPropsWithFlatBuffers(slider, (Table*)sliderOptions);
        
        return slider;
    }
    
    int SliderReader::getResourceType(std::string key)
    {
        if(key == "Normal" || key == "Default")
        {
            return 	0;
        }
        
        FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
        if(fbs->_isSimulator)
        {
            if(key == "MarkedSubImage")
            {
                return 0;
            }
        }
        return 1;
    }
    
}
