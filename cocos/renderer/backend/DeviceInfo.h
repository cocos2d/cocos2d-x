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

/**
 * @addtogroup _backend
 * @{
 */

/**
 * Used to query features and implementation limits
 */
class DeviceInfo
{
public:
    virtual ~DeviceInfo() = default;

    /**
     * Gather features and implementation limits
     */
    virtual bool init() = 0;

    /**
     * Get vendor device name.
     * @return Vendor device name.
     */
    virtual const char* getVendor() const = 0;

    /**
     * Get the full name of the vendor device.
     * @return The full name of the vendor device.
     */
    virtual const char* getRenderer() const = 0;

    /**
     * Get version name.
     * @return Version name.
     */
    virtual const char* getVersion() const = 0;

    /**
     * get extensions.
     * @return Extension supported by device.
     */
    virtual const char* getExtension() const = 0;

    /**
     * Check if feature supported by device.
     * @param feature Specify feature to be query.
     * @return true if the feature is supported, false otherwise.
     */
    virtual bool checkForFeatureSupported(FeatureType feature) = 0;
    
    /**
     * Get maximum texture size.
     * @return Maximum texture size.
     */
    inline int getMaxTextureSize() const { return _maxTextureSize; }

    /**
     * Get maximum attribute counts.
     * @return Maximum attribute counts.
     */
    inline int getMaxAttributes() const { return _maxAttributes; }

    /**
     * Get maximum texture unit.
     * @return Maximum texture unit.
     */
    inline int getMaxTextureUnits() const { return _maxTextureUnits; }

    /**
     * Get maximum sampler count.
     * @return Maximum sampler count.
     */
    inline int getMaxSamplesAllowed() const { return _maxSamplesAllowed; }
    
protected:
    DeviceInfo() = default;
    
    int _maxAttributes = 0; ///< Maximum attribute count.
    int _maxTextureSize = 0; ///< Maximum texture size.
    int _maxTextureUnits = 0; ///< Maximum texture unit.
    int _maxSamplesAllowed = 0; ///< Maximum sampler count.
};

//end of _backend group
/// @}
CC_BACKEND_END
