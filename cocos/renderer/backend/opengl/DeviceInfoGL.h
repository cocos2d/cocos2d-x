#pragma once

#include "../DeviceInfo.h"

CC_BACKEND_BEGIN

class DeviceInfoGL: public DeviceInfo
{
public:
    DeviceInfoGL() = default;
	virtual ~DeviceInfoGL() = default;

    virtual bool init() override;
    
private:
};

CC_BACKEND_END
