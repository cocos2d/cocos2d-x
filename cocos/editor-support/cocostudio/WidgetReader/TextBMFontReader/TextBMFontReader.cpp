

#include "TextBMFontReader.h"
#include "ui/UITextBMFont.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary.pb.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static const char* P_FileNameData = "fileNameData";
    static const char* P_Text = "text";
    
    static TextBMFontReader* instanceTextBMFontReader = nullptr;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(TextBMFontReader)
    
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
    
    void TextBMFontReader::setPropsFromProtocolBuffers(ui::Widget *widget, const protocolbuffers::NodeTree &nodeTree)
    {
        WidgetReader::setPropsFromProtocolBuffers(widget, nodeTree);
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        TextBMFont* labelBMFont = static_cast<TextBMFont*>(widget);
        const protocolbuffers::TextBMFontOptions& options = nodeTree.textbmfontoptions();
        
        
        const protocolbuffers::ResourceData& cmftDic = options.filenamedata();
        int cmfType = cmftDic.resourcetype();
        switch (cmfType)
        {
            case 0:
            {
                std::string tp_c = jsonPath;
                const char* cmfPath = cmftDic.path().c_str();
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
        
        const char* text = (options.has_text()) ? options.text().c_str() : "Text Label";
        labelBMFont->setString(text);
        
        
        // other commonly protperties
        WidgetReader::setColorPropsFromProtocolBuffers(widget, nodeTree);
    }
    
    void TextBMFontReader::setPropsFromXML(cocos2d::ui::Widget *widget, const tinyxml2::XMLElement *objectData)
    {
        WidgetReader::setPropsFromXML(widget, objectData);
        
        TextBMFont* labelBMFont = static_cast<TextBMFont*>(widget);
        
        std::string xmlPath = GUIReader::getInstance()->getFilePath();
        
        std::string text = "";
        
        int opacity = 255;
        
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
            
            if (name == "LabelBMFontFile_CNB")
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
                        labelBMFont->setFntFile(xmlPath + path);
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        labelBMFont->setString(text);
        
        labelBMFont->setOpacity(opacity);
    }
    
}
