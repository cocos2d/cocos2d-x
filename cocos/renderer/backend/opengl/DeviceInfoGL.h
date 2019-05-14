#pragma once

#include "../DeviceInfo.h"

CC_BACKEND_BEGIN

class DeviceInfoGL: public DeviceInfo
{
public:
    DeviceInfoGL() = default;
    virtual ~DeviceInfoGL() = default;

    virtual bool init() override;
    virtual const char* getVendor() const override;
    virtual const char* getRenderer() const override;
    virtual const char* getVersion() const override;
    virtual const char* getExtension() const override;
    virtual bool checkForFeatureSupported(const FeaturesInfo& feature) override;
    
private:
    bool checkForGLExtension(const std::string &searchName) const;

    std::string _glExtensions;
};

CC_BACKEND_END
