#pragma once

#include "../DeviceInfo.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class DeviceInfoMTL : public DeviceInfo
{
public:
    DeviceInfoMTL(id<MTLDevice> device);
	virtual ~DeviceInfoMTL() = default;

    virtual bool init() override;
    virtual const char* getVendor() const override;
    virtual const char* getRenderer() const override;
    virtual const char* getVersion() const override;
    virtual const char* getExtension() const override;
    virtual bool checkForFeatureSupported(const FeaturesInfo& feature) override;
    
private:
    std::string _deviceName;
};

CC_BACKEND_END
