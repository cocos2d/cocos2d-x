//
//  CustomParticleWidgetReader.cpp
//  CustomUI
//
//  Created by cai wenzhi on 14-3-7.
//
//

#include "CustomParticleWidgetReader.h"
#include "CustomParticleWidget.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

CustomParticleWidgetReader::CustomParticleWidgetReader()
{
    
}

CustomParticleWidgetReader::~CustomParticleWidgetReader()
{
    
}

static CustomParticleWidgetReader* _instanceCustomParticleWidgetReader = NULL;

CustomParticleWidgetReader* CustomParticleWidgetReader::getInstance()
{
    if (!_instanceCustomParticleWidgetReader)
    {
        _instanceCustomParticleWidgetReader = new CustomParticleWidgetReader();
    }
    return _instanceCustomParticleWidgetReader;
}

void CustomParticleWidgetReader::setProperties(const std::string& classType,
                                          Widget *widget,
                                          const rapidjson::Value &customOptions)
{    
    GUIReader* guiReader = GUIReader::shareReader();
    
    CustomParticleWidget* custom = static_cast<CustomParticleWidget*>(widget);
    
    bool isExistPlistFile = DICTOOL->checkObjectExist_json(customOptions, "PlistFile");
    if (isExistPlistFile)
    {
        const char* PlistFile = DICTOOL->getStringValue_json(customOptions, "PlistFile");
        std::string PlistFilePath = guiReader->getFilePath();
        PlistFilePath.append(PlistFile);
        custom->setParticlePlist(PlistFilePath.c_str());
    }
}
