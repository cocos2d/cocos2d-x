

#include "editor-support/cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.h"

#include "ui/UILoadingBar.h"
#include "2d/CCSpriteFrameCache.h"
#include "platform/CCFileUtils.h"

#include "editor-support/cocostudio/CocoLoader.h"
#include "editor-support/cocostudio/CSParseBinary_generated.h"
#include "editor-support/cocostudio/FlatBuffersSerialize.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

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
    
    IMPLEMENT_CLASS_NODE_READER_INFO(LoadingBarReader)
    
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
    
    void LoadingBarReader::destroyInstance()
    {
        CC_SAFE_DELETE(instanceLoadingBar);
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
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);
                
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
    
    Offset<Table> LoadingBarReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                                 flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        std::string path = "";
        std::string plistFile = "";
        int resourceType = 0;
        
        int percent = 80;
        int direction = 0;
        
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
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "ImageFileData")
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
                        path = value;
                    }
                    else if (name == "Type")
                    {
                        resourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (resourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));                    
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateLoadingBarOptions(*builder,
                                               widgetOptions,
                                               CreateResourceData(*builder,
                                                                  builder->CreateString(path),
                                                                  builder->CreateString(plistFile),
                                                                  resourceType),
                                               percent,
                                               direction);
        
        return *(Offset<Table>*)(&options);
    }
    
    void LoadingBarReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *loadingBarOptions)
    {
        LoadingBar* loadingBar = static_cast<LoadingBar*>(node);
        auto options = (LoadingBarOptions*)loadingBarOptions;
        
        bool fileExist = false;
        std::string errorFilePath = "";
        auto imageFileNameDic = options->textureData();
        int imageFileNameType = imageFileNameDic->resourceType();
        std::string imageFileName = imageFileNameDic->path()->c_str();
        switch (imageFileNameType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(imageFileName))
                {
                    fileExist = true;
                }
                else if (SpriteFrameCache::getInstance()->getSpriteFrameByName(imageFileName))
                {
                    fileExist = true;
                    imageFileNameType = 1;
                }
                else
                {
                    errorFilePath = imageFileName;
                    fileExist = false;
                }
                break;
            }
                
            case 1:
            {
                std::string plist = imageFileNameDic->plistFile()->c_str();
                SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageFileName);
                if (spriteFrame)
                {
                    fileExist = true;
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
                            errorFilePath = textureFileName;
                        }
                    }
                    else
                    {
                        errorFilePath = plist;
                    }
                    fileExist = false;
                }
                break;
            }
                
            default:
                break;
        }
        if (fileExist)
        {
            loadingBar->loadTexture(imageFileName, (Widget::TextureResType)imageFileNameType);
        }
        
        int direction = options->direction();
        loadingBar->setDirection(LoadingBar::Direction(direction));
        
        int percent = options->percent();
        loadingBar->setPercent(percent);
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
    }
    
    Node* LoadingBarReader::createNodeWithFlatBuffers(const flatbuffers::Table *loadingBarOptions)
    {
        LoadingBar* loadingBar = LoadingBar::create();
        
        setPropsWithFlatBuffers(loadingBar, (Table*)loadingBarOptions);
        
        return loadingBar;
    }
    
    int LoadingBarReader::getResourceType(std::string key)
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
