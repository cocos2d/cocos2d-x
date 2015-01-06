

#include "CheckBoxReader.h"

#include "ui/UICheckBox.h"
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
    static const char* P_BackGroundBoxData = "backGroundBoxData";
    static const char* P_BackGroundBoxSelectedData = "backGroundBoxSelectedData";
    static const char* P_FrontCrossData = "frontCrossData";
    static const char* P_BackGroundBoxDisabledData = "backGroundBoxDisabledData";
    static const char* P_FrontCrossDisabledData = "frontCrossDisabledData";
    
    static CheckBoxReader* instanceCheckBoxReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(CheckBoxReader)
    
    CheckBoxReader::CheckBoxReader()
    {
        
    }
    
    CheckBoxReader::~CheckBoxReader()
    {
        
    }
    
    CheckBoxReader* CheckBoxReader::getInstance()
    {
        if (!instanceCheckBoxReader)
        {
            instanceCheckBoxReader = new (std::nothrow) CheckBoxReader();
        }
        return instanceCheckBoxReader;
    }
    
    void CheckBoxReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        
        CheckBox *checkBox = static_cast<CheckBox*>(widget);
        this->beginSetBasicProperties(widget);
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
//            CCLOG("key = %s, index : %d", key.c_str(), i);
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if (key == P_BackGroundBoxData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureBackGround(backgroundValue, imageFileNameType);
            }else if(key == P_BackGroundBoxSelectedData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureBackGroundSelected(backgroundValue, imageFileNameType);
            }else if(key == P_FrontCrossData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureFrontCross(backgroundValue, imageFileNameType);
            }else if(key == P_BackGroundBoxDisabledData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureBackGroundDisabled(backgroundValue, imageFileNameType);
            }else if (key == P_FrontCrossDisabledData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                checkBox->loadTextureFrontCrossDisabled(backgroundValue, imageFileNameType);
            }
//            else if (key == "selectedState"){
//                checkBox->setSelectedState(valueToBool(value));
//            }
        }
        
        this->endSetBasicProperties(widget);
        
        
    }
    
    void CheckBoxReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        CheckBox* checkBox = static_cast<CheckBox*>(widget);
       
        //load background image
        const rapidjson::Value& backGroundDic = DICTOOL->getSubDictionary_json(options, P_BackGroundBoxData);
        int backGroundType = DICTOOL->getIntValue_json(backGroundDic,P_ResourceType);
        std::string backGroundTexturePath = this->getResourcePath(backGroundDic, P_Path, (Widget::TextureResType)backGroundType);
         checkBox->loadTextureBackGround(backGroundTexturePath, (Widget::TextureResType)backGroundType);
        
       //load background selected image
        const rapidjson::Value& backGroundSelectedDic = DICTOOL->getSubDictionary_json(options, P_BackGroundBoxSelectedData);
        int backGroundSelectedType = DICTOOL->getIntValue_json(backGroundSelectedDic, P_ResourceType);
        std::string backGroundSelectedTexturePath = this->getResourcePath(backGroundSelectedDic, P_Path, (Widget::TextureResType)backGroundSelectedType);
        checkBox->loadTextureBackGroundSelected(backGroundSelectedTexturePath, (Widget::TextureResType)backGroundSelectedType);
        
        //load frontCross image
        const rapidjson::Value& frontCrossDic = DICTOOL->getSubDictionary_json(options, P_FrontCrossData);
        int frontCrossType = DICTOOL->getIntValue_json(frontCrossDic, P_ResourceType);
        std::string frontCrossFileName = this->getResourcePath(frontCrossDic, P_Path, (Widget::TextureResType)frontCrossType);
        checkBox->loadTextureFrontCross(frontCrossFileName, (Widget::TextureResType)frontCrossType);
        
       //load backGroundBoxDisabledData
        const rapidjson::Value& backGroundDisabledDic = DICTOOL->getSubDictionary_json(options, P_BackGroundBoxDisabledData);
        int backGroundDisabledType = DICTOOL->getIntValue_json(backGroundDisabledDic, P_ResourceType);
        std::string backGroundDisabledFileName = this->getResourcePath(backGroundDisabledDic, P_Path, (Widget::TextureResType)backGroundDisabledType);
        checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName, (Widget::TextureResType)backGroundDisabledType);
        
        ///load frontCrossDisabledData
        const rapidjson::Value& frontCrossDisabledDic = DICTOOL->getSubDictionary_json(options, P_FrontCrossDisabledData);
        int frontCrossDisabledType = DICTOOL->getIntValue_json(frontCrossDisabledDic, P_ResourceType);
        std::string frontCrossDisabledFileName = this->getResourcePath(frontCrossDisabledDic, P_Path, (Widget::TextureResType)frontCrossDisabledType);
        checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName, (Widget::TextureResType)frontCrossDisabledType);
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }        
    
    Offset<Table> CheckBoxReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                               flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        bool selectedState = false;
        bool displaystate = true;
        
        int backgroundboxResourceType = 0;
        std::string backgroundboxPath = "";
        std::string backgroundboxPlistFile = "";
        
        int backGroundBoxSelectedResourceType = 0;
        std::string backGroundBoxSelectedPath = "";
        std::string backGroundBoxSelectedPlistFile = "";
        
        int frontCrossResourceType = 0;
        std::string frontCrossPath = "";
        std::string frontCrossPlistFile = "";
        
        int backGroundBoxDisabledResourceType = 0;
        std::string backGroundBoxDisabledPath = "";
        std::string backGroundBoxDisabledPlistFile = "";
        
        
        int frontCrossDisabledResourceType = 0;
        std::string frontCrossDisabledPath = "";
        std::string frontCrossDisabledPlistFile = "";
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "CheckedState")
            {
                selectedState = (value == "True") ? true : false;
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
            
            if (name == "NormalBackFileData")
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
                        backgroundboxPath = value;
                    }
                    else if (name == "Type")
                    {
                        backgroundboxResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        backgroundboxPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (backgroundboxResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "PressedBackFileData")
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
                        backGroundBoxSelectedPath = value;
                    }
                    else if (name == "Type")
                    {
                        backGroundBoxSelectedResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        backGroundBoxSelectedPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (backGroundBoxSelectedResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "NodeNormalFileData")
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
                        frontCrossPath = value;
                    }
                    else if (name == "Type")
                    {
                        frontCrossResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        frontCrossPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (frontCrossResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "DisableBackFileData")
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
                        backGroundBoxDisabledPath = value;
                    }
                    else if (name == "Type")
                    {
                        backGroundBoxDisabledResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        backGroundBoxDisabledPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (backGroundBoxDisabledResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));                    
                }
            }
            else if (name == "NodeDisableFileData")
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
                        frontCrossDisabledPath = value;
                    }
                    else if (name == "Type")
                    {
                        frontCrossDisabledResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        frontCrossDisabledPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (frontCrossDisabledResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));                    
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateCheckBoxOptions(*builder,
                                             widgetOptions,
                                             CreateResourceData(*builder,
                                                                builder->CreateString(backgroundboxPath),
                                                                builder->CreateString(backgroundboxPlistFile),
                                                                backgroundboxResourceType),
                                             CreateResourceData(*builder,
                                                                builder->CreateString(backGroundBoxSelectedPath),
                                                                builder->CreateString(backGroundBoxSelectedPlistFile),
                                                                backGroundBoxSelectedResourceType),
                                             CreateResourceData(*builder,
                                                                builder->CreateString(frontCrossPath),
                                                                builder->CreateString(frontCrossPlistFile),
                                                                frontCrossResourceType),
                                             CreateResourceData(*builder,
                                                                builder->CreateString(backGroundBoxDisabledPath),
                                                                builder->CreateString(backGroundBoxDisabledPlistFile),
                                                                backGroundBoxDisabledResourceType),
                                             CreateResourceData(*builder,
                                                                builder->CreateString(frontCrossDisabledPath),
                                                                builder->CreateString(frontCrossDisabledPlistFile),
                                                                frontCrossDisabledResourceType),
                                             selectedState,
                                             displaystate
                                             );
        
        return *(Offset<Table>*)&options;
    }
    
    void CheckBoxReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *checkBoxOptions)
    {
        
        
        auto options = (CheckBoxOptions*)checkBoxOptions;
        
        CheckBox* checkBox = static_cast<CheckBox*>(node);
        
        //load background image
        bool backGroundFileExist = false;
        std::string backGroundErrorFilePath = "";
        auto backGroundDic = options->backGroundBoxData();
        int backGroundType = backGroundDic->resourceType();
        std::string backGroundTexturePath = backGroundDic->path()->c_str();
        switch (backGroundType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(backGroundTexturePath))
                {
                    backGroundFileExist = true;
                }
                else
                {
                    backGroundErrorFilePath = backGroundTexturePath;
                    backGroundFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = backGroundDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(backGroundTexturePath);
                if (spriteFrame)
                {
                    backGroundFileExist = true;
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
                            backGroundErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        backGroundErrorFilePath = plist;
                    }
                    backGroundFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (backGroundFileExist)
        {
            checkBox->loadTextureBackGround(backGroundTexturePath, (Widget::TextureResType)backGroundType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", backGroundErrorFilePath.c_str())->getCString());
            checkBox->addChild(label);
        }
        
        //load background selected image
        bool backGroundSelectedfileExist = false;
        std::string backGroundSelectedErrorFilePath = "";
        auto backGroundSelectedDic = options->backGroundBoxSelectedData();
        int backGroundSelectedType = backGroundSelectedDic->resourceType();
        std::string backGroundSelectedTexturePath = backGroundSelectedDic->path()->c_str();
        switch (backGroundSelectedType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(backGroundSelectedTexturePath))
                {
                    backGroundSelectedfileExist = true;
                }
                else
                {
                    backGroundSelectedErrorFilePath = backGroundSelectedTexturePath;
                    backGroundSelectedfileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = backGroundSelectedDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(backGroundSelectedTexturePath);
                if (spriteFrame)
                {
                    backGroundSelectedfileExist = true;
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
                            backGroundSelectedErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        backGroundSelectedErrorFilePath = plist;
                    }
                    backGroundSelectedfileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (backGroundSelectedfileExist)
        {
            checkBox->loadTextureBackGroundSelected(backGroundSelectedTexturePath, (Widget::TextureResType)backGroundSelectedType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", backGroundSelectedErrorFilePath.c_str())->getCString());
            checkBox->addChild(label);
        }
        
        //load frontCross image
        bool frontCrossFileExist = false;
        std::string frontCrossErrorFilePath = "";
        auto frontCrossDic = options->frontCrossData();
        int frontCrossType = frontCrossDic->resourceType();
        std::string frontCrossFileName = frontCrossDic->path()->c_str();
        switch (frontCrossType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(frontCrossFileName))
                {
                    frontCrossFileExist = true;
                }
                else
                {
                    frontCrossErrorFilePath = frontCrossFileName;
                    frontCrossFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = frontCrossDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frontCrossFileName);
                if (spriteFrame)
                {
                    frontCrossFileExist = true;
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
                            frontCrossErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        frontCrossErrorFilePath = plist;
                    }
                    frontCrossFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (frontCrossFileExist)
        {
            checkBox->loadTextureFrontCross(frontCrossFileName, (Widget::TextureResType)frontCrossType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", frontCrossErrorFilePath.c_str())->getCString());
            checkBox->addChild(label);
        }
        
        //load backGroundBoxDisabledData
        bool backGroundBoxDisabledFileExist = false;
        std::string backGroundBoxDisabledErrorFilePath = "";
        auto backGroundDisabledDic = options->backGroundBoxDisabledData();
        int backGroundDisabledType = backGroundDisabledDic->resourceType();
        std::string backGroundDisabledFileName = backGroundDisabledDic->path()->c_str();
        switch (backGroundDisabledType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(backGroundDisabledFileName))
                {
                    backGroundBoxDisabledFileExist = true;
                }
                else
                {
                    backGroundBoxDisabledErrorFilePath = backGroundDisabledFileName;
                    backGroundBoxDisabledFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = backGroundDisabledDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(backGroundDisabledFileName);
                if (spriteFrame)
                {
                    backGroundBoxDisabledFileExist = true;
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
                            backGroundBoxDisabledErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        backGroundBoxDisabledErrorFilePath = plist;
                    }
                    backGroundBoxDisabledFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (backGroundBoxDisabledFileExist)
        {
            checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName, (Widget::TextureResType)backGroundDisabledType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", backGroundBoxDisabledErrorFilePath.c_str())->getCString());
            checkBox->addChild(label);
        }
        
        ///load frontCrossDisabledData
        bool frontCrossDisabledFileExist = false;
        std::string frontCrossDisabledErrorFilePath = "";
        auto frontCrossDisabledDic = options->frontCrossDisabledData();
        int frontCrossDisabledType = frontCrossDisabledDic->resourceType();
        std::string frontCrossDisabledFileName = frontCrossDisabledDic->path()->c_str();
        switch (frontCrossDisabledType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(frontCrossDisabledFileName))
                {
                    frontCrossDisabledFileExist = true;
                }
                else
                {
                    frontCrossDisabledErrorFilePath = frontCrossDisabledFileName;
                    frontCrossDisabledFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = frontCrossDisabledDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frontCrossDisabledFileName);
                if (spriteFrame)
                {
                    frontCrossDisabledFileExist = true;
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
                            frontCrossDisabledErrorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        frontCrossDisabledErrorFilePath = plist;
                    }
                    frontCrossDisabledFileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (frontCrossDisabledFileExist)
        {
            checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName, (Widget::TextureResType)frontCrossDisabledType);
        }
        else
        {
            auto label = Label::create();
            label->setString(__String::createWithFormat("%s missed", frontCrossDisabledErrorFilePath.c_str())->getCString());
            checkBox->addChild(label);
        }
        
        bool selectedstate = options->selectedState();
        checkBox->setSelected(selectedstate);
        
        bool displaystate = options->displaystate();
        checkBox->setBright(displaystate);
        checkBox->setEnabled(displaystate);
        
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
        
    }
    
    Node* CheckBoxReader::createNodeWithFlatBuffers(const flatbuffers::Table *checkBoxOptions)
    {
        CheckBox* checkBox = CheckBox::create();
        
        setPropsWithFlatBuffers(checkBox, (Table*)checkBoxOptions);
        
        return checkBox;
    }

    int CheckBoxReader::getResourceType(std::string key)
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
