

#include "CheckBoxReader.h"
#include "ui/UICheckBox.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{
    static CheckBoxReader* instanceCheckBoxReader = NULL;
    
    IMPLEMENT_CLASS_WIDGET_READER_INFO(CheckBoxReader)
    
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
            instanceCheckBoxReader = new CheckBoxReader();
        }
        return instanceCheckBoxReader;
    }
    
    void CheckBoxReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        CheckBox* checkBox = static_cast<CheckBox*>(widget);
        
       
        //load background image
        const rapidjson::Value& backGroundDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxData");
        int backGroundType = DICTOOL->getIntValue_json(backGroundDic, "resourceType");
        std::string backGroundTexturePath = this->getResourcePath(backGroundDic, "path", (TextureResType)backGroundType);
         checkBox->loadTextureBackGround(backGroundTexturePath, (TextureResType)backGroundType);
        
       //load background selected image
        const rapidjson::Value& backGroundSelectedDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxSelectedData");
        int backGroundSelectedType = DICTOOL->getIntValue_json(backGroundSelectedDic, "resourceType");
        std::string backGroundSelectedTexturePath = this->getResourcePath(backGroundSelectedDic, "path", (TextureResType)backGroundSelectedType);
        checkBox->loadTextureBackGroundSelected(backGroundSelectedTexturePath, (TextureResType)backGroundSelectedType);
        
        //load frontCross image
        const rapidjson::Value& frontCrossDic = DICTOOL->getSubDictionary_json(options, "frontCrossData");
        int frontCrossType = DICTOOL->getIntValue_json(frontCrossDic, "resourceType");
        std::string frontCrossFileName = this->getResourcePath(frontCrossDic, "path", (TextureResType)frontCrossType);
        checkBox->loadTextureFrontCross(frontCrossFileName, (TextureResType)frontCrossType);
        
       //load backGroundBoxDisabledData
        const rapidjson::Value& backGroundDisabledDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxDisabledData");
        int backGroundDisabledType = DICTOOL->getIntValue_json(backGroundDisabledDic, "resourceType");
        std::string backGroundDisabledFileName = this->getResourcePath(backGroundDisabledDic, "path", (TextureResType)backGroundDisabledType);
        checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName, (TextureResType)backGroundDisabledType);
        
        ///load frontCrossDisabledData
        const rapidjson::Value& frontCrossDisabledDic = DICTOOL->getSubDictionary_json(options, "frontCrossDisabledData");
        int frontCrossDisabledType = DICTOOL->getIntValue_json(frontCrossDisabledDic, "resourceType");
        std::string frontCrossDisabledFileName = this->getResourcePath(frontCrossDisabledDic, "path", (TextureResType)frontCrossDisabledType);
        checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName, (TextureResType)frontCrossDisabledType);
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }
}
