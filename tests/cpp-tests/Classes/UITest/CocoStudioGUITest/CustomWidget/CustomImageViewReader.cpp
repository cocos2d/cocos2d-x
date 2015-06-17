

#include "CustomImageViewReader.h"
#include "CustomImageView.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;

static CustomImageViewReader* _instanceCustomImageViewReader = nullptr;

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
        _instanceCustomImageViewReader = new (std::nothrow) CustomImageViewReader();
    }
    return _instanceCustomImageViewReader;
}

void CustomImageViewReader::setProperties(const std::string& classType, cocos2d::ui::Widget *widget, const rapidjson::Value &customOptions)
{
    CustomImageView* custom = static_cast<CustomImageView*>(widget);
    
    const char* StringTest = DICTOOL->getStringValue_json(customOptions, "StringTest");
    if (StringTest) {
        custom->setText(StringTest);
    }
}



