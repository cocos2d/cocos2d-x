/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
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
