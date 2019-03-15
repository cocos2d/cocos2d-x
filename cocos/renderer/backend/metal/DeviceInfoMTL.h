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
    
private:
    void getTextureSizeInfo();
    
    //MTLFeatureSet _currentFeatureSet;
};

CC_BACKEND_END
