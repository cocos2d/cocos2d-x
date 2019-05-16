#pragma once

#include <string>

#include "Macros.h"

CC_BACKEND_BEGIN

enum class FeatureType : uint32_t
{
    ETC1,
    S3TC,
    AMD_COMPRESSED_ATC,
    PVRTC,
    IMG_FORMAT_BGRA8888,
    DISCARD_FRAMEBUFFER,
    PACKED_DEPTH_STENCIL,
    VAO,
    MAPBUFFER,
    DEPTH24,
    ASTC
};

class DeviceInfo
{
public:
    virtual ~DeviceInfo() = default;
    virtual bool init() = 0;
    virtual const char* getVendor() const = 0;
    virtual const char* getRenderer() const = 0;
    virtual const char* getVersion() const = 0;
    virtual const char* getExtension() const = 0;
    virtual bool checkForFeatureSupported(FeatureType feature) = 0;
    
    inline int getMaxTextureSize() const { return _maxTextureSize; }
    inline int getMaxAttributes() const { return _maxAttributes; }
    inline int getMaxTextureUnits() const { return _maxTextureUnits; }
    inline int getMaxSamplesAllowed() const { return _maxSamplesAllowed; }
    
protected:
    DeviceInfo() = default;
    
    int _maxAttributes = 0;
    int _maxTextureSize = 0;
    int _maxTextureUnits = 0;
    int _maxSamplesAllowed = 0;
};

CC_BACKEND_END
