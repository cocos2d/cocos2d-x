

#include "editor-support/cocostudio/WidgetReader/ButtonReader/ButtonReader.h"

#include "ui/UIButton.h"
#include "2d/CCSpriteFrameCache.h"
#include "2d/CCLabel.h"
#include "platform/CCFileUtils.h"
#include "editor-support/cocostudio/CocoLoader.h"
#include "editor-support/cocostudio/CSParseBinary_generated.h"
#include "editor-support/cocostudio/FlatBuffersSerialize.h"
#include "editor-support/cocostudio/LocalizationManager.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

namespace cocostudio
{
    
    static const char* P_Scale9Enable = "scale9Enable";
    static const char* P_NormalData = "normalData";
    static const char* P_PressedData = "pressedData";
    static const char* P_DisabledData = "disabledData";
    static const char* P_Text = "text";
    static const char* P_CapInsetsX = "capInsetsX";
    static const char* P_CapInsetsY = "capInsetsY";
    static const char* P_CapInsetsWidth = "capInsetsWidth";
    static const char* P_CapInsetsHeight = "capInsetsHeight";
    static const char* P_Scale9Width = "scale9Width";
    static const char* P_Scale9Height = "scale9Height";
    static const char* P_TextColorR = "textColorR";
    static const char* P_TextColorG = "textColorG";
    static const char* P_TextColorB = "textColorB";
    static const char* P_FontSize = "fontSize";
    static const char* P_FontName = "fontName";
    
   
    
    static ButtonReader* instanceButtonReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(ButtonReader)
    
    ButtonReader::ButtonReader()
    {
        
    }
    
    ButtonReader::~ButtonReader()
    {
        
    }
    
    ButtonReader* ButtonReader::getInstance()
    {
        if (!instanceButtonReader)
        {
            instanceButtonReader = new (std::nothrow) ButtonReader();
        }
        return instanceButtonReader;
    }
    
    void ButtonReader::purge()
    {
        CC_SAFE_DELETE(instanceButtonReader);
    }
    
    void ButtonReader::destroyInstance()
    {
        CC_SAFE_DELETE(instanceButtonReader);
    }
    
    void ButtonReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        WidgetReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
        
        Button *button = static_cast<Button*>(widget);
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        this->beginSetBasicProperties(widget);
        
        float capsx = 0.0f, capsy = 0.0, capsWidth = 0.0, capsHeight = 0.0f;
        int cri = 255, cgi = 255, cbi = 255;
        float scale9Width = 0.0f, scale9Height = 0.0f;
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);

            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
           
            else if (key == P_Scale9Enable) {
                button->setScale9Enabled(valueToBool(value));
            }
            else if (key == P_NormalData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTextureNormal(backgroundValue, imageFileNameType);
                
            }
            else if (key == P_PressedData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTexturePressed(backgroundValue, imageFileNameType);
                
            }
            else if (key == P_DisabledData){
                
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                button->loadTextureDisabled(backgroundValue, imageFileNameType);
                
            }else if (key == P_Text){
                button->setTitleText(value);
            }
            else if(key == P_CapInsetsX){
                capsx = valueToFloat(value);
            }else if(key == P_CapInsetsY){
                capsy = valueToFloat(value);
            }else if(key == P_CapInsetsWidth){
                capsWidth = valueToFloat(value);
            }else if(key == P_CapInsetsHeight){
                capsHeight = valueToFloat(value);
            }else if(key == P_Scale9Width){
                scale9Width = valueToFloat(value);
            }else if(key == P_Scale9Height){
                scale9Height = valueToFloat(value);
            }else if(key == P_TextColorR){
                cri = valueToInt(value);
            }else if(key == P_TextColorG){
                cgi = valueToInt(value);
            }else if(key == P_TextColorB){
                cbi = valueToInt(value);
            }else if(key == P_FontSize){
                button->setTitleFontSize(valueToFloat(value));
            }else if(key == P_FontName){
                button->setTitleFontName(value);
            }
            
        } //end of for loop
        
        this->endSetBasicProperties(widget);

        if (button->isScale9Enabled()) {
            button->setCapInsets(Rect(capsx, capsy, capsWidth, capsHeight));
            button->setContentSize(Size(scale9Width, scale9Height));
        }
        
        button->setTitleColor(Color3B(cri, cgi, cbi));
        

    }
    
    void ButtonReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        Button* button = static_cast<Button*>(widget);
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, P_Scale9Enable);
        button->setScale9Enabled(scale9Enable);
        
        
        const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, P_NormalData);
        int normalType = DICTOOL->getIntValue_json(normalDic, P_ResourceType);
        std::string normalTexturePath = this->getResourcePath(normalDic, P_Path, (Widget::TextureResType)normalType);
        button->loadTextureNormal(normalTexturePath, (Widget::TextureResType)normalType);
        
        
        const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, P_PressedData);
        int pressedType = DICTOOL->getIntValue_json(pressedDic, P_ResourceType);
        
        std::string pressedTexturePath = this->getResourcePath(pressedDic, P_Path, (Widget::TextureResType)pressedType);
        button->loadTexturePressed(pressedTexturePath, (Widget::TextureResType)pressedType);
        
        
        const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, P_DisabledData);
        int disabledType = DICTOOL->getIntValue_json(disabledDic, P_ResourceType);
        
        std::string disabledTexturePath = this->getResourcePath(disabledDic, P_Path, (Widget::TextureResType)disabledType);
        button->loadTextureDisabled(disabledTexturePath, (Widget::TextureResType)disabledType);
       
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, P_CapInsetsX);
            float cy = DICTOOL->getFloatValue_json(options, P_CapInsetsY);
            float cw = DICTOOL->getFloatValue_json(options, P_CapInsetsWidth);
            float ch = DICTOOL->getFloatValue_json(options, P_CapInsetsHeight);
            
            button->setCapInsets(Rect(cx, cy, cw, ch));
            bool sw = DICTOOL->checkObjectExist_json(options, P_Scale9Width);
            bool sh = DICTOOL->checkObjectExist_json(options, P_Scale9Height);
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, P_Scale9Width);
                float shf = DICTOOL->getFloatValue_json(options, P_Scale9Height);
                button->setContentSize(Size(swf, shf));
            }
        }
        bool tt = DICTOOL->checkObjectExist_json(options, P_Text);
        if (tt)
        {
            const char* text = DICTOOL->getStringValue_json(options, P_Text);
            if (text)
            {
                button->setTitleText(text);
            }
        }
        
     
        int cri = DICTOOL->getIntValue_json(options, P_TextColorR,255);
        int cgi = DICTOOL->getIntValue_json(options, P_TextColorG,255);
        int cbi = DICTOOL->getIntValue_json(options, P_TextColorB,255);
        button->setTitleColor(Color3B(cri,cgi,cbi));
  
        
        button->setTitleFontSize(DICTOOL->getIntValue_json(options, P_FontSize,14));
        

        button->setTitleFontName(DICTOOL->getStringValue_json(options, P_FontName, ""));
        
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }    
    
    Offset<Table> ButtonReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData, flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        bool displaystate = true;
        bool scale9Enabled = false;
        Rect capInsets;
        std::string text = "";
        bool isLocalized = false;
        int fontSize = 14;
        std::string fontName = "";
        cocos2d::Size scale9Size;
        Color4B textColor(255, 255, 255, 255);
        
        std::string normalPath = "";
        std::string normalPlistFile = "";
        int normalResourceType = 0;
        
        std::string pressedPath = "";
        std::string pressedPlistFile = "";
        int pressedResourceType = 0;
        
        std::string disabledPath = "";
        std::string disabledPlistFile = "";
        int disabledResourceType = 0;
        
        std::string fontResourcePath = "";
        std::string fontResourcePlistFile = "";
        int fontResourceResourceType = 0;
        
        bool outlineEnabled = false;
        Color4B outlineColor = Color4B::BLACK;
        int outlineSize = 1;
        bool shadowEnabled = false;
        Color4B shadowColor = Color4B::BLACK;
        Size shadowOffset = Size(2, -2);
        int shadowBlurRadius = 0;
        
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
                capInsets.origin.x = atof(value.c_str());
            }
            else if (name == "Scale9OriginY")
            {
                capInsets.origin.y = atof(value.c_str());
            }
            else if (name == "Scale9Width")
            {
                capInsets.size.width = atof(value.c_str());
            }
            else if (name == "Scale9Height")
            {
                capInsets.size.height = atof(value.c_str());
            }
            else if (name == "ButtonText")
            {
                text = value;
            }
            else if (name == "IsLocalized")
            {
                isLocalized = (value == "True") ? true : false;
            }
            else if (name == "FontSize")
            {
                fontSize = atoi(value.c_str());
            }
            else if (name == "FontName")
            {
                fontName = value;
            }
            else if (name == "DisplayState")
            {
                displaystate = (value == "True") ? true : false;
            }
            else if (name == "OutlineEnabled")
            {
                outlineEnabled = (value == "True") ? true : false;
            }
            else if (name == "OutlineSize")
            {
                outlineSize = atoi(value.c_str());
            }
            else if (name == "ShadowEnabled")
            {
                shadowEnabled = (value == "True") ? true : false;
            }
            else if (name == "ShadowOffsetX")
            {
                shadowOffset.width = atof(value.c_str());
            }
            else if (name == "ShadowOffsetY")
            {
                shadowOffset.height = atof(value.c_str());
            }
            else if (name == "ShadowBlurRadius")
            {
                shadowBlurRadius = atoi(value.c_str());
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
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "X")
                    {
                        scale9Size.width = atof(value.c_str());
                    }
                    else if (name == "Y")
                    {
                        scale9Size.height = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "TextColor")
            {
                attribute = child->FirstAttribute();
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        textColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        textColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        textColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "DisabledFileData")
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
                        disabledPath = value;
                    }
                    else if (name == "Type")
                    {
                        disabledResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        disabledPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (disabledResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "PressedFileData")
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
                        pressedPath = value;
                    }
                    else if (name == "Type")
                    {
                        pressedResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        pressedPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (pressedResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));                    
                }
            }
            else if (name == "NormalFileData")
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
                        normalPath = value;
                    }
                    else if (name == "Type")
                    {
                        normalResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        normalPlistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (normalResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));                    
                }
            }
            else if (name == "FontResource")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        fontResourcePath = value;
                    }
                    else if (name == "Type")
                    {
                        fontResourceResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        fontResourcePlistFile = value;
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "OutlineColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "A")
                    {
                        outlineColor.a = atoi(value.c_str());
                    }
                    else if (name == "R")
                    {
                        outlineColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        outlineColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        outlineColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "ShadowColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "A")
                    {
                        shadowColor.a = atoi(value.c_str());
                    }
                    else if (name == "R")
                    {
                        shadowColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        shadowColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        shadowColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        Color f_textColor(255, textColor.r, textColor.g, textColor.b);
        CapInsets f_capInsets(capInsets.origin.x, capInsets.origin.y, capInsets.size.width, capInsets.size.height);
        FlatSize f_scale9Size(scale9Size.width, scale9Size.height);
        flatbuffers::Color f_outlineColor(outlineColor.a, outlineColor.r, outlineColor.g, outlineColor.b);
        flatbuffers::Color f_shadowColor(shadowColor.a, shadowColor.r, shadowColor.g, shadowColor.b);
        
        auto options = CreateButtonOptions(*builder,
                                           widgetOptions,
                                           CreateResourceData(*builder,
                                                              builder->CreateString(normalPath),
                                                              builder->CreateString(normalPlistFile),
                                                              normalResourceType),
                                           CreateResourceData(*builder,
                                                              builder->CreateString(pressedPath),
                                                              builder->CreateString(pressedPlistFile),
                                                              pressedResourceType),
                                           CreateResourceData(*builder,
                                                              builder->CreateString(disabledPath),
                                                              builder->CreateString(disabledPlistFile),
                                                              disabledResourceType),
                                           CreateResourceData(*builder,
                                                              builder->CreateString(fontResourcePath),
                                                              builder->CreateString(fontResourcePlistFile),
                                                              fontResourceResourceType),
                                           builder->CreateString(text),
                                           builder->CreateString(fontName),
                                           fontSize,
                                           &f_textColor,
                                           &f_capInsets,
                                           &f_scale9Size,
                                           scale9Enabled,
                                           displaystate,
                                           outlineEnabled,
                                           &f_outlineColor,
                                           outlineSize,
                                           shadowEnabled,
                                           &f_shadowColor,
                                           shadowOffset.width,
                                           shadowOffset.height,
                                           shadowBlurRadius,
                                           isLocalized);
        
        return *(Offset<Table>*)(&options);
    }
    
    void ButtonReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *buttonOptions)
    {
        Button* button = static_cast<Button*>(node);
        auto options = (ButtonOptions*)buttonOptions;
        
        bool scale9Enabled = options->scale9Enabled() != 0;
        button->setScale9Enabled(scale9Enabled);
        
        bool normalFileExist = false;
        std::string normalErrorFilePath = "";
        auto normalDic = options->normalData();
        int normalType = normalDic->resourceType();
        std::string normalTexturePath = normalDic->path()->c_str();
        switch (normalType)
        {
            case 0:
                if (FileUtils::getInstance()->isFileExist(normalTexturePath))
                {
                    normalFileExist = true;
                }
                else if (SpriteFrameCache::getInstance()->getSpriteFrameByName(normalTexturePath))
                {
                    normalFileExist = true;
                    normalType = 1;
                }
                else
                {
                    normalErrorFilePath = normalTexturePath;
                    normalFileExist = false;
                }
                break;
                
            case 1:
            {
                std::string plist = normalDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(normalTexturePath);
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
            button->loadTextureNormal(normalTexturePath, (Widget::TextureResType)normalType);
        }
        
        bool pressedFileExist = false;
        std::string pressedErrorFilePath = "";
        auto pressedDic = options->pressedData();
        int pressedType = pressedDic->resourceType();
        std::string pressedTexturePath = pressedDic->path()->c_str();
        switch (pressedType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(pressedTexturePath))
                {
                    pressedFileExist = true;
                }
                else
                {
                    pressedErrorFilePath = pressedTexturePath;
                    pressedFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = pressedDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pressedTexturePath);
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
            button->loadTexturePressed(pressedTexturePath, (Widget::TextureResType)pressedType);
        }
        
        bool disabledFileExist = false;
        std::string disabledErrorFilePath = "";
        auto disabledDic = options->disabledData();
        int disabledType = disabledDic->resourceType();
        std::string disabledTexturePath = disabledDic->path()->c_str();
        switch (disabledType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(disabledTexturePath))
                {
                    disabledFileExist = true;
                }
                else
                {
                    disabledErrorFilePath = disabledTexturePath;
                    disabledFileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = disabledDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(disabledTexturePath);
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
            button->loadTextureDisabled(disabledTexturePath, (Widget::TextureResType)disabledType);
        }
        
        std::string titleText = options->text()->c_str();
        bool isLocalized = options->isLocalized() != 0;
        if (isLocalized)
        {
            ILocalizationManager* lm = LocalizationHelper::getCurrentManager();
            button->setTitleText(lm->getLocalizationString(titleText));
        }
        else
        {
            button->setTitleText(titleText);
        }
        
        auto textColor = options->textColor();
        Color3B titleColor(textColor->r(), textColor->g(), textColor->b());
        button->setTitleColor(titleColor);
        
        int titleFontSize = options->fontSize();
        button->setTitleFontSize(titleFontSize);
        
        std::string titleFontName = options->fontName()->c_str();
        button->setTitleFontName(titleFontName);
        
        auto resourceData = options->fontResource();
        bool fileExist = false;
        std::string errorFilePath = "";
        std::string path = resourceData->path()->c_str();
        if (path != "")
        {
            if (FileUtils::getInstance()->isFileExist(path))
            {
                fileExist = true;
            }
            else
            {
                errorFilePath = path;
                fileExist = false;
            }
            if (fileExist)
            {
                button->setTitleFontName(path);
            }
        }
        
        bool displaystate = options->displaystate() != 0;
        button->setBright(displaystate);
        button->setEnabled(displaystate);
        
        bool outlineEnabled = options->outlineEnabled() != 0;
        if (outlineEnabled)
        {
            auto f_outlineColor = options->outlineColor();
            if (f_outlineColor)
            {
                Color4B outlineColor(f_outlineColor->r(), f_outlineColor->g(), f_outlineColor->b(), f_outlineColor->a());
                auto label = button->getTitleRenderer();
                label->enableOutline(outlineColor, options->outlineSize());
            }
        }
        
        bool shadowEnabled = options->shadowEnabled() != 0;
        if (shadowEnabled)
        {
            auto f_shadowColor = options->shadowColor();
            if (f_shadowColor)
            {
                Color4B shadowColor(f_shadowColor->r(), f_shadowColor->g(), f_shadowColor->b(), f_shadowColor->a());
                auto label = button->getTitleRenderer();
                label->enableShadow(shadowColor, Size(options->shadowOffsetX(), options->shadowOffsetY()), options->shadowBlurRadius());
            }
        }
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
        
        if (scale9Enabled)
        {
            button->setUnifySizeEnabled(false);
            button->ignoreContentAdaptWithSize(false);
            
            auto f_capInsets = options->capInsets();
            Rect capInsets(f_capInsets->x(), f_capInsets->y(), f_capInsets->width(), f_capInsets->height());
            button->setCapInsets(capInsets);
            
            Size scale9Size(options->scale9Size()->width(), options->scale9Size()->height());
            button->setContentSize(scale9Size);
        }
        else
        {
            Size contentSize(options->widgetOptions()->size()->width(), options->widgetOptions()->size()->height());
            button->setContentSize(contentSize);
        }

        button->setBright(displaystate);
    }
    
    Node* ButtonReader::createNodeWithFlatBuffers(const flatbuffers::Table *buttonOptions)
    {
        Button* button = Button::create();
        
        setPropsWithFlatBuffers(button, (Table*)buttonOptions);
        
        return button;
    }
    
    int ButtonReader::getResourceType(std::string key)
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
