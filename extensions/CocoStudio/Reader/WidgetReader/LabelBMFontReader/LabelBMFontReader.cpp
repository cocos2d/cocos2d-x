

#include "LabelBMFontReader.h"
#include "../../../GUI/UIWidgets/UILabelBMFont.h"

NS_CC_EXT_BEGIN

static LabelBMFontReader* instanceLabelBMFontReader = NULL;

IMPLEMENT_CLASS_WIDGET_READER_INFO(LabelBMFontReader)

LabelBMFontReader::LabelBMFontReader()
{
    
}

LabelBMFontReader::~LabelBMFontReader()
{
    
}

LabelBMFontReader* LabelBMFontReader::getInstance()
{
    if (!instanceLabelBMFontReader)
    {
        instanceLabelBMFontReader = new LabelBMFontReader();
    }
    return instanceLabelBMFontReader;
}

void LabelBMFontReader::setPropsFromJsonDictionary(ui::Widget *widget, const rapidjson::Value &options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);
    
    
    std::string jsonPath = GUIReader::shareReader()->getFilePath();
    
    ui::LabelBMFont* labelBMFont = (ui::LabelBMFont*)widget;
    
    const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, "fileNameData");
    int cmfType = DICTOOL->getIntValue_json(cmftDic, "resourceType");
    switch (cmfType)
    {
        case 0:
        {
            std::string tp_c = jsonPath;
            const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, "path");
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
    
    const char* text = DICTOOL->getStringValue_json(options, "text");
    labelBMFont->setText(text);
    
    
    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

NS_CC_EXT_END
