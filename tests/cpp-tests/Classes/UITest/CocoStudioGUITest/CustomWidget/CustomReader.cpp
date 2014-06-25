

#include "CustomReader.h"
#include "CustomImageView.h"

static CustomReader* _instanceCustomReader = NULL;

CustomReader::CustomReader()
{
    
}

CustomReader::~CustomReader()
{
    
}

CustomReader* CustomReader::getInstance()
{
    if (!_instanceCustomReader)
    {
        _instanceCustomReader = new CustomReader();
    }
    return _instanceCustomReader;
}

void CustomReader::setProperties(const std::string &classType, Widget *widget, const rapidjson::Value &customOptions)
{
    if (classType.compare("CustomImageView") == 0)
    {
        CustomImageView* customImageView = static_cast<CustomImageView*>(widget);
        
        bool isExistText = DICTOOL->getBooleanValue_json(customOptions, "text");
        if (isExistText)
        {
            const char* text = DICTOOL->getStringValue_json(customOptions, "text");
            customImageView->setText(text);
        }
    }
}
