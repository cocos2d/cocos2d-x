

#include "TextBMFontReader.h"

#include "2d/CCFontAtlasCache.h"
#include "ui/UITextBMFont.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary_generated.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

namespace cocostudio
{
    static const char* P_FileNameData = "fileNameData";
    static const char* P_Text = "text";
    
    static TextBMFontReader* instanceTextBMFontReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(TextBMFontReader)
    
    TextBMFontReader::TextBMFontReader()
    {
        
    }
    
    TextBMFontReader::~TextBMFontReader()
    {
        
    }
    
    TextBMFontReader* TextBMFontReader::getInstance()
    {
        if (!instanceTextBMFontReader)
        {
            instanceTextBMFontReader = new (std::nothrow) TextBMFontReader();
        }
        return instanceTextBMFontReader;
    }
    
    void TextBMFontReader::destroyInstance()
    {
        CC_SAFE_DELETE(instanceTextBMFontReader);
    }
    
    void TextBMFontReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        TextBMFont* labelBMFont = static_cast<TextBMFont*>(widget);
        
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if(key == P_FileNameData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
                std::string resType = backGroundChildren[2].GetValue(cocoLoader);;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
                if (imageFileNameType == (Widget::TextureResType)0) {
                    labelBMFont->setFntFile(backgroundValue);
                }
                
            }else if(key == P_Text){
                labelBMFont->setString(value);
            }
        } //end of for loop
        this->endSetBasicProperties(widget);
    }
    
    void TextBMFontReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        TextBMFont* labelBMFont = static_cast<TextBMFont*>(widget);
        
        const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, P_FileNameData);
        int cmfType = DICTOOL->getIntValue_json(cmftDic, P_ResourceType);
        switch (cmfType)
        {
            case 0:
            {
                std::string tp_c = jsonPath;
                const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, P_Path);
                const char* cmf_tp = tp_c.append(cmfPath).c_str();
                labelBMFont->setFntFile(cmf_tp);
                break;
            }
            case 1:
                CCLOG("Wrong res type of LabelAtlas!");
                break;
            default:
                break;
        }
        
        const char* text = DICTOOL->getStringValue_json(options, P_Text,"Text Label");
        labelBMFont->setString(text);
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }        
    
    Offset<Table> TextBMFontReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                                 flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        std::string text = "Fnt Text Label";
        
        std::string path = "";
        std::string plistFlie = "";
        int resourceType = 0;
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "LabelText")
            {
                text = value;
            }
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "LabelBMFontFile_CNB")
            {
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
                        plistFlie = value;
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateTextBMFontOptions(*builder,
                                               widgetOptions,
                                               CreateResourceData(*builder,
                                                                  builder->CreateString(path),
                                                                  builder->CreateString(plistFlie),
                                                                  resourceType),
                                               builder->CreateString(text));
        
        return *(Offset<Table>*)(&options);
    }
    
    void TextBMFontReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *textBMFontOptions)
    {
        TextBMFont* labelBMFont = static_cast<TextBMFont*>(node);
        auto options = (TextBMFontOptions*)textBMFontOptions;
        
        auto cmftDic = options->fileNameData();
        bool fileExist = false;
        std::string errorFilePath = "";
        std::string errorContent = "";
        std::string path = cmftDic->path()->c_str();
        int cmfType = cmftDic->resourceType();
        switch (cmfType)
        {
            case 0:
            {
                if (FileUtils::getInstance()->isFileExist(path))
                {
                    FontAtlas* newAtlas = FontAtlasCache::getFontAtlasFNT(path);
                    if (newAtlas)
                    {
                        fileExist = true;
                    }
                    else
                    {
                        errorContent = "has problem";
                        fileExist = false;
                    }
                }
                //else
                //{
                //    errorContent = "missed";
                //    fileExist = false;
                //}
                break;
            }
                
            default:
                break;
        }
        if (fileExist)
        {
            labelBMFont->setFntFile(path);
        }
        //else
        //{
        //    if (!errorContent.empty())
        //    {
        //        errorFilePath = path;
        //        auto label = Label::create();
        //        label->setString(__String::createWithFormat("%s %s", errorFilePath.c_str(), errorContent.c_str())->getCString());
        //        labelBMFont->addChild(label);
        //    }
        //}
        
        std::string text = options->text()->c_str();
        labelBMFont->setString(text);
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
        
        labelBMFont->ignoreContentAdaptWithSize(true);
    }
    
    Node* TextBMFontReader::createNodeWithFlatBuffers(const flatbuffers::Table *textBMFontOptions)
    {
        TextBMFont* textBMFont = TextBMFont::create();
        
        setPropsWithFlatBuffers(textBMFont, (Table*)textBMFontOptions);
        
        return textBMFont;
    }
    
}
