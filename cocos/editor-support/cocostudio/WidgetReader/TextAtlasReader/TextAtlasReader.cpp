

#include "TextAtlasReader.h"
#include "ui/UITextAtlas.h"
#include "cocostudio/CocoLoader.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
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
    
    void TextAtlasReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        TextAtlas* labelAtlas = static_cast<TextAtlas*>(widget);

        
        stExpCocoNode *stChildArray = pCocoNode->GetChildArray();
        Widget::TextureResType type;
        std::string charMapFileName;
        std::string stringValue;
        std::string startCharMap;
        float itemWidth;
        float itemHeight;
        for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(pCocoLoader);
            std::string value = stChildArray[i].GetValue();
            
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER
            
            else if(key == "anchorPointX"){
                _originalAnchorPoint.x = valueToFloat(value);
            }else if(key == "anchorPointY"){
                _originalAnchorPoint.y = valueToFloat(value);
            }
            else if (key == "stringValue") {
                stringValue = value;
            }
            else if(key == "charMapFileData"){
                stExpCocoNode *backGroundChildren = stChildArray[i].GetChildArray();
                std::string resType = backGroundChildren[2].GetValue();;
                
                Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);
                
                std::string backgroundValue = this->getResourcePath(pCocoLoader, &stChildArray[i], imageFileNameType);
                
                charMapFileName = backgroundValue;
                type  = imageFileNameType;
                
            }else if(key == "itemWidth"){
                itemWidth = valueToFloat(value);
            }else if(key == "itemHeight"){
                itemHeight = valueToFloat(value);
            }else if(key == "startCharMap"){
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
        bool sv = DICTOOL->checkObjectExist_json(options, "stringValue");
        bool cmf = DICTOOL->checkObjectExist_json(options, "charMapFile");
        bool iw = DICTOOL->checkObjectExist_json(options, "itemWidth");
        bool ih = DICTOOL->checkObjectExist_json(options, "itemHeight");
        bool scm = DICTOOL->checkObjectExist_json(options, "startCharMap");
        if (sv && cmf && iw && ih && scm)
        {
            const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, "charMapFileData");
            int cmfType = DICTOOL->getIntValue_json(cmftDic, "resourceType");
            switch (cmfType)
            {
                case 0:
                {
                    std::string tp_c = jsonPath;
                    const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, "path");
                    const char* cmf_tp = tp_c.append(cmfPath).c_str();
                    labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),cmf_tp,DICTOOL->getIntValue_json(options, "itemWidth"),DICTOOL->getIntValue_json(options,"itemHeight"), DICTOOL->getStringValue_json(options, "startCharMap"));
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
