

#include "TextAtlasReader.h"
#include "ui/UITextAtlas.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static const char* P_StringValue = "stringValue";
    static const char* P_CharMapFileData = "charMapFileData";
    static const char* P_ItemWidth = "itemWidth";
    static const char* P_ItemHeight = "itemHeight";
    static const char* P_StartCharMap = "startCharMap";
    
    
    static const char* P_CharMapFile = "charMapFile";
    
    static TextAtlasReader* instanceTextAtalsReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(TextAtlasReader)
    
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
            instanceTextAtalsReader = new TextAtlasReader();
        }
        return instanceTextAtalsReader;
    }
    
    void TextAtlasReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        TextAtlas* labelAtlas = static_cast<TextAtlas*>(widget);

        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray();
        Widget::TextureResType type;
        std::string charMapFileName;
        std::string stringValue;
        std::string startCharMap;
        float itemWidth;
        float itemHeight;
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue();
            
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if (key == P_StringValue) {
                stringValue = value;
            }
            else if(key == P_CharMapFileData){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
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
        bool sv = DICTOOL->checkObjectExist_json(options, P_StringValue);
        bool cmf = DICTOOL->checkObjectExist_json(options, P_CharMapFile);
        bool iw = DICTOOL->checkObjectExist_json(options, P_ItemWidth);
        bool ih = DICTOOL->checkObjectExist_json(options, P_ItemHeight);
        bool scm = DICTOOL->checkObjectExist_json(options, P_StartCharMap);
        if (sv && cmf && iw && ih && scm)
        {
            const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, P_CharMapFileData);
            int cmfType = DICTOOL->getIntValue_json(cmftDic, P_ResourceType);
            switch (cmfType)
            {
                case 0:
                {
                    std::string tp_c = jsonPath;
                    const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, P_Path);
                    const char* cmf_tp = tp_c.append(cmfPath).c_str();
                    labelAtlas->setProperty(DICTOOL->getStringValue_json(options, P_StringValue),cmf_tp,DICTOOL->getIntValue_json(options, P_ItemWidth),DICTOOL->getIntValue_json(options,P_ItemHeight), DICTOOL->getStringValue_json(options, P_StartCharMap));
                    break;
                }
                case 1:
                    CCLOG("Wrong res type of LabelAtlas!");
                    break;
                default:
                    break;
            }
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
