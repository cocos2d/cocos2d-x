#pragma once

#include "../DeviceInfo.h"

CC_BACKEND_BEGIN

class DeviceInfoMTL : public DeviceInfo
{
public:
    DeviceInfoMTL() = default;
	virtual ~DeviceInfoMTL() = default;

    virtual bool init() override;
};

CC_BACKEND_END
