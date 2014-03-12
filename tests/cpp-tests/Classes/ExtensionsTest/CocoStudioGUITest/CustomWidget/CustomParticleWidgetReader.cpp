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
using namespace cocostudio;

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
    
    CustomParticleWidget* custom = static_cast<CustomParticleWidget*>(widget);
    
    bool isExistParticlePlist = DICTOOL->checkObjectExist_json(customOptions, "ParticlePlist");
    if (isExistParticlePlist)
    {
        const char* ParticlePlist = DICTOOL->getStringValue_json(customOptions, "ParticlePlist");
        custom->setParticlePlist(ParticlePlist);
    }
}
