

#include "TextAtlasReader.h"
#include "ui/UITextAtlas.h"

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
