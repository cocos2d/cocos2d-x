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

#include "../DeviceInfo.h"

CC_BACKEND_BEGIN
/**
 * @addtogroup _opengl
 * @{
 */

/**
 * Used to query features and implementation limits
 */
class DeviceInfoGL: public DeviceInfo
{
public:
    DeviceInfoGL() = default;
    virtual ~DeviceInfoGL() = default;

    /**
     * Gather features and implementation limits
     */
    virtual bool init() override;

    /**
     * Get vendor device name.
     * @return Vendor device name.
     */
    virtual const char* getVendor() const override;

    /**
     * Get the full name of the vendor device.
     * @return The full name of the vendor device.
     */
    virtual const char* getRenderer() const override;

    /**
     * Get version name.
     * @return Version name.
     */
    virtual const char* getVersion() const override;

    /**
     * get OpenGL ES extensions.
     * @return Extension supported by OpenGL ES.
     */
    virtual const char* getExtension() const override;

    /**
     * Check if feature supported by OpenGL ES.
     * @param feature Specify feature to be query.
     * @return true if the feature is supported, false otherwise.
     */
    virtual bool checkForFeatureSupported(FeatureType feature) override;
    
private:
    bool checkForGLExtension(const std::string &searchName) const;

    std::string _glExtensions;
};

//end of _opengl group
/// @}
CC_BACKEND_END
