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
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

enum class FeatureSet : int32_t
{
    Unknown = -1,
    FeatureSet_iOS_GPUFamily1_v1 = 0,
    FeatureSet_iOS_GPUFamily2_v1 = 1,
    
    FeatureSet_iOS_GPUFamily1_v2 = 2,
    FeatureSet_iOS_GPUFamily2_v2 = 3,
    FeatureSet_iOS_GPUFamily3_v1 = 4,
    
    FeatureSet_iOS_GPUFamily1_v3 = 5,
    FeatureSet_iOS_GPUFamily2_v3 = 6,
    FeatureSet_iOS_GPUFamily3_v2 = 7,
    
    FeatureSet_iOS_GPUFamily1_v4 = 8,
    FeatureSet_iOS_GPUFamily2_v4 = 9,
    FeatureSet_iOS_GPUFamily3_v3 = 10,
    FeatureSet_iOS_GPUFamily4_v1 = 11,
    
    FeatureSet_iOS_GPUFamily1_v5 = 12,
    FeatureSet_iOS_GPUFamily2_v5 = 13,
    FeatureSet_iOS_GPUFamily3_v4 = 14,
    FeatureSet_iOS_GPUFamily4_v2 = 15,
    
    FeatureSet_macOS_GPUFamily1_v1 = 10000,
    
    FeatureSet_macOS_GPUFamily1_v2 = 10001,
    FeatureSet_macOS_ReadWriteTextureTier2 = 10002,
    
    FeatureSet_macOS_GPUFamily1_v3 = 10003,
    
    FeatureSet_macOS_GPUFamily1_v4 = 10004,
    FeatureSet_macOS_GPUFamily2_v1 = 10005,
};

inline FeatureSet operator--( FeatureSet& x ) { return x = (FeatureSet)(std::underlying_type<FeatureSet>::type(x) - 1); }

/**
 * @addtogroup _metal
 * @{
 */


/**
 * Used to query features and implementation limits
 */
class DeviceInfoMTL : public DeviceInfo
{
public:
    /// @name Constructor, Destructor and Initializers
    /**
     * @param device To query MTLDevice features and implementation limits in Metal.
     */
    DeviceInfoMTL(id<MTLDevice> device);
	virtual ~DeviceInfoMTL() = default;

    /**
     * Gather features and implementation limits
     */
    virtual bool init() override;
    
    /// @name Setters & Getters
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
     * Get featureSet name.
     * @return FeatureSet name.
     */
    virtual const char* getVersion() const override;
    
    /**
     * Get metal extensions.
     * @return Extension supported by Metal.
     */
    virtual const char* getExtension() const override;
    
    /**
     * Check if feature supported by Metal.
     * @param feature Specify feature to be query.
     * @return true if the feature is supported, false otherwise.
     */
    virtual bool checkForFeatureSupported(FeatureType feature) override;
    
private:
    std::string _deviceName;
    FeatureSet _featureSet = FeatureSet::Unknown;
    bool _isDepth24Stencil8PixelFormatSupported = false;
};

// end of _metal group
/// @}
CC_BACKEND_END
