

#include "TextAtlasReader.h"

#include "ui/UITextAtlas.h"
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
    static const char* P_StringValue = "stringValue";
    static const char* P_CharMapFileData = "charMapFileData";
    static const char* P_ItemWidth = "itemWidth";
    static const char* P_ItemHeight = "itemHeight";
    static const char* P_StartCharMap = "startCharMap";
    
    static TextAtlasReader* instanceTextAtalsReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(TextAtlasReader)
    
    TextAtlasReader::TextAtlasReader()
    {
        
    }
    
    TextAtlasReader::~TextAtlasReader()
    {
        
    }
    
    TextAtlasReader* TextAtlasReader::getInstance()
    {
        if (!instanceTextAtalsReader)
        {
            instanceTextAtalsReader = new (std::nothrow) TextAtlasReader();
        }
        return instanceTextAtalsReader;
    }
    
    void TextAtlasReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        TextAtlas* labelAtlas = static_cast<TextAtlas*>(widget);

        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        Widget::TextureResType type;
        std::string charMapFileName;
        std::string stringValue;
        std::string startCharMap;
        float itemWidth;
        float itemHeight;
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if (key == P_StringValue) {
                stringValue = value;
            }
            else if(key == P_CharMapFileData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                
                charMapFileName = backgroundValue;
                type  = imageFileNameType;
                
            }else if(key == P_ItemWidth){
                itemWidth = valueToFloat(value);
            }else if(key == P_ItemHeight){
                itemHeight = valueToFloat(value);
            }else if(key == P_StartCharMap){
                startCharMap = value;
            }
        } //end of for loop
        
        if (type == (Widget::TextureResType)0) {
            labelAtlas->setProperty(stringValue, charMapFileName, itemWidth, itemHeight, startCharMap);
        }
        this->endSetBasicProperties(widget);
    }
    
    void TextAtlasReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        TextAtlas* labelAtlas = static_cast<TextAtlas*>(widget);
//        bool sv = DICTOOL->checkObjectExist_json(options, P_StringValue);
//        bool cmf = DICTOOL->checkObjectExist_json(options, P_CharMapFile);
//        bool iw = DICTOOL->checkObjectExist_json(options, P_ItemWidth);
//        bool ih = DICTOOL->checkObjectExist_json(options, P_ItemHeight);
//        bool scm = DICTOOL->checkObjectExist_json(options, P_StartCharMap);
       
        const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, P_CharMapFileData);
        int cmfType = DICTOOL->getIntValue_json(cmftDic, P_ResourceType);
        switch (cmfType)
        {
            case 0:
            {
                std::string tp_c = jsonPath;
                const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, P_Path);
                const char* cmf_tp = tp_c.append(cmfPath).c_str();
                labelAtlas->setProperty(DICTOOL->getStringValue_json(options, P_StringValue,"12345678"),
                                        cmf_tp,
                                        DICTOOL->getIntValue_json(options, P_ItemWidth,24),
                                        DICTOOL->getIntValue_json(options,P_ItemHeight,32),
                                        DICTOOL->getStringValue_json(options, P_StartCharMap));
                break;
            }
            case 1:
                CCLOG("Wrong res type of LabelAtlas!");
                break;
            default:
                break;
        }
        
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }        
    
    Offset<Table> TextAtlasReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                                flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        std::string path = "";
        std::string plistFile = "";
        int resourceType = 0;
        
        std::string stringValue = "0123456789";
        int itemWidth = 0;
        int itemHeight = 0;
        std::string startCharMap = "";
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "LabelText")
            {
                stringValue = value;
            }
            else if (name == "CharWidth")
            {
                itemWidth = atoi(value.c_str());
            }
            else if (name == "CharHeight")
            {
                itemHeight = atoi(value.c_str());
            }
            else if (name == "StartChar")
            {
                startCharMap = value;
            }
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "LabelAtlasFileImage_CNB")
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
                        resourceType = 0;
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateTextAtlasOptions(*builder,
                                              widgetOptions,
                                              CreateResourceData(*builder,
                                                                 builder->CreateString(path),
                                                                 builder->CreateString(plistFile),
                                                                 resourceType),
                                              builder->CreateString(stringValue),
                                              builder->CreateString(startCharMap),
                                              itemWidth,
                                              itemHeight
                                              );
        
        return *(Offset<Table>*)(&options);
    }
    
    void TextAtlasReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *textAtlasOptions)
    {
        TextAtlas* labelAtlas = static_cast<TextAtlas*>(node);
        auto options = (TextAtlasOptions*)textAtlasOptions;
        
        auto cmftDic = options->charMapFileData();
        int cmfType = cmftDic->resourceType();
        switch (cmfType)
        {
            case 0:
            {
                const char* cmfPath = cmftDic->path()->c_str();
                std::string stringValue = options->stringValue()->c_str();
                int itemWidth = options->itemWidth();
                int itemHeight = options->itemHeight();
                labelAtlas->setProperty(stringValue,
                                        cmfPath,
                                        itemWidth,
                                        itemHeight,
                                        options->startCharMap()->c_str());
                break;
            }
            case 1:
                CCLOG("Wrong res type of LabelAtlas!");
                break;
            default:
                break;
        }
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
        
        labelAtlas->ignoreContentAdaptWithSize(true);
        
    }
    
    Node* TextAtlasReader::createNodeWithFlatBuffers(const flatbuffers::Table *textAtlasOptions)
    {
        TextAtlas* textAtlas = TextAtlas::create();
        
        setPropsWithFlatBuffers(textAtlas, (Table*)textAtlasOptions);
        
        return textAtlas;
    }
    
}
