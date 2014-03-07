

#include "CustomImageViewReader.h"
#include "CustomImageView.h"

static CustomImageViewReader* _instanceCustomImageViewReader = NULL;

CustomImageViewReader::CustomImageViewReader()
{
    
}

CustomImageViewReader::~CustomImageViewReader()
{
    
}

CustomImageViewReader* CustomImageViewReader::getInstance()
{
    if (!_instanceCustomImageViewReader)
    {
        _instanceCustomImageViewReader = new CustomImageViewReader();
    }
    return _instanceCustomImageViewReader;
}

void CustomImageViewReader::setProperties(const std::string& classType, cocos2d::ui::Widget *widget, const rapidjson::Value &customOptions)
{
    CustomImageView* custom = static_cast<CustomImageView*>(widget);
    
    const char* StringTest = DICTOOL->getStringValue_json(customOptions, "StringTest");
    custom->setText(StringTest);
}



