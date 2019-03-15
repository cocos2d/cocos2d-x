#pragma once

#include <string>

#include "Macros.h"

CC_BACKEND_BEGIN

class DeviceInfo
{
public:
    virtual ~DeviceInfo() = default;
    virtual bool init() = 0;
   
    inline int getMaxTextureSize() const { return _maxTextureSize; }
    inline int getMaxAttributes() const { return _maxAttributes; }
    
protected:
    DeviceInfo() = default;
    
    int _maxAttributes = 0;
    int _maxTextureSize = 0;
};

CC_BACKEND_END
