/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import "platform/CCImage.h"
#import "platform/CCCommon.h"
#import <string>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#include <math.h>

#if CC_USE_WEBP
#include "encode.h"
#include "decode.h"
#endif // CC_USE_WEBP

NS_CC_BEGIN

bool cocos2d::Image::saveToFile(const std::string& filename, bool isToRGB, float compressionQuality)
{
    //only support for Texture2D::PixelFormat::RGB888 or Texture2D::PixelFormat::RGBA8888 uncompressed data
    if (isCompressed() || (_renderFormat != Texture2D::PixelFormat::RGB888 && _renderFormat != Texture2D::PixelFormat::RGBA8888))
    {
        CCLOG("cocos2d: Image: saveToFile is only support for Texture2D::PixelFormat::RGB888 or Texture2D::PixelFormat::RGBA8888 uncompressed data for now");
        return false;
    }

    bool saveToJPG = false;
    bool saveToPNG = false;
    bool saveToWEBP = false;
    bool needToCopyPixels = false;

    std::string basename(filename);
    std::transform(basename.begin(), basename.end(), basename.begin(), ::tolower);
    
    if (std::string::npos != basename.find(".jpg"))
    {
        saveToJPG = true;
    }
    else if (std::string::npos != basename.find(".png"))
    {
        saveToPNG = true;
    }
    else if (std::string::npos != basename.find(".webp"))
    {
        saveToWEBP = true;
    }
    
    int bitsPerComponent = 8;            
    int bitsPerPixel = hasAlpha() ? 32 : 24;
    if (((! saveToPNG) && (! saveToWEBP)) || isToRGB)
    {
        bitsPerPixel = 24;
    }
    
    int bytesPerRow    = (bitsPerPixel/8) * _width;
    int myDataLength = bytesPerRow * _height;
    
    unsigned char *pixels    = _data;

    // The data has alpha channel, and want to save it with an RGB png file,
    // or want to save as jpg,  remove the alpha channel.
    if (hasAlpha() && bitsPerPixel == 24)
    {
        pixels = new (std::nothrow) unsigned char[myDataLength];
        
        for (int i = 0; i < _height; ++i)
        {
            for (int j = 0; j < _width; ++j)
            {
                pixels[(i * _width + j) * 3] = _data[(i * _width + j) * 4];
                pixels[(i * _width + j) * 3 + 1] = _data[(i * _width + j) * 4 + 1];
                pixels[(i * _width + j) * 3 + 2] = _data[(i * _width + j) * 4 + 2];
            }
        }
        
        needToCopyPixels = true;
    }
    
    // make data provider with data.
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    if (saveToPNG && hasAlpha() && (! isToRGB))
    {
        if (_hasPremultipliedAlpha)
        {
            bitmapInfo |= kCGImageAlphaPremultipliedLast;
        }
        else
        {
            bitmapInfo |= kCGImageAlphaLast;
        }
    }
    else if (saveToWEBP && hasAlpha() && (! isToRGB))
    {
        bitmapInfo |= kCGImageAlphaPremultipliedLast;
    }
    
    CGDataProviderRef provider        = CGDataProviderCreateWithData(nullptr, pixels, myDataLength, nullptr);
    CGColorSpaceRef colorSpaceRef     = CGColorSpaceCreateDeviceRGB();
    CGImageRef iref                   = CGImageCreate(_width, _height,
                                                        bitsPerComponent, bitsPerPixel, bytesPerRow,
                                                        colorSpaceRef, bitmapInfo, provider,
                                                        nullptr, false,
                                                        kCGRenderingIntentDefault);
        
    UIImage* image                    = [[UIImage alloc] initWithCGImage:iref];
        
    CGImageRelease(iref);    
    CGColorSpaceRelease(colorSpaceRef);
    CGDataProviderRelease(provider);

    // NOTE: Prevent memory leak. Requires ARC enabled.
    @autoreleasepool {
        NSData *data;
        if (saveToPNG) {
            data = UIImagePNGRepresentation(image);
        } else if (saveToWEBP) {
            NSData *dataPNG = UIImagePNGRepresentation(image);
            UIImage* imagePNG = [[UIImage alloc] initWithData:dataPNG];
                
            WebPPreset preset = WEBP_PRESET_DEFAULT;
                
            NSError *error = nil;
                
            CGImageRef webPImageRef = imagePNG.CGImage;
            size_t webPBytesPerRow = CGImageGetBytesPerRow(webPImageRef);
                
            size_t webPImageWidth = CGImageGetWidth(webPImageRef);
            size_t webPImageHeight = CGImageGetHeight(webPImageRef);
                
            CGDataProviderRef webPDataProviderRef = CGImageGetDataProvider(webPImageRef);
            CFDataRef webPImageDatRef = CGDataProviderCopyData(webPDataProviderRef);
                
            uint8_t *webPImageData = (uint8_t *)CFDataGetBytePtr(webPImageDatRef);
                
            WebPConfig config;
            
            int compressionLevel = (int)(compressionQuality-1.0f);
            float newCompressionQuality = compressionQuality * 100.0f;
            
            if(compressionLevel >= 0)
            {
                newCompressionQuality = 100.0f;
            }

            if (!WebPConfigPreset(&config, preset, newCompressionQuality)) {
                NSMutableDictionary *errorDetail = [NSMutableDictionary dictionary];
                [errorDetail setValue:@"Configuration preset failed to initialize." forKey:NSLocalizedDescriptionKey];
                if(error != NULL)
                CCLOG("WebPConfigPreset Configuration preset failed to initialize.");
                    
                CFRelease(webPImageDatRef);
                return nil;
            }
            
            //if compressionQuality >= 1.0f will use lossless preset, compressionLevel can be set with compressionQuality
            if(compressionLevel >= 0)
            {
                if(compressionLevel > 9) {
                    compressionLevel = 9;
                }

                if (!WebPConfigLosslessPreset(&config, compressionLevel)) {
                    NSMutableDictionary *errorDetail = [NSMutableDictionary dictionary];
                    [errorDetail setValue:@"Configuration preset failed to initialize." forKey:NSLocalizedDescriptionKey];
                    if(error != NULL)
                    CCLOG("WebPConfigLosslessPreset Configuration preset failed to initialize.");
                        
                    CFRelease(webPImageDatRef);
                    return nil;
                }
            }

            if (!WebPValidateConfig(&config)) {
                NSMutableDictionary *errorDetail = [NSMutableDictionary dictionary];
                [errorDetail setValue:@"One or more configuration parameters are beyond their valid ranges." forKey:NSLocalizedDescriptionKey];
                if(error != NULL)
                    CCLOG("One or more configuration parameters are beyond their valid ranges.");
                    
                CFRelease(webPImageDatRef);
                return nil;
            }

            WebPPicture pic;
            if (!WebPPictureInit(&pic)) {
                NSMutableDictionary *errorDetail = [NSMutableDictionary dictionary];
                    [errorDetail setValue:@"Failed to initialize structure. Version mismatch." forKey:NSLocalizedDescriptionKey];
                if(error != NULL)
                    CCLOG("Failed to initialize structure. Version mismatch.");
                    
                CFRelease(webPImageDatRef);
                return nil;
            }
            
            pic.width = (int)webPImageWidth;
            pic.height = (int)webPImageHeight;
            
            pic.use_argb = (compressionLevel >= 0) ? 1 : 0;
            pic.colorspace = WEBP_YUV420;

            if (hasAlpha())
            {
                WebPPictureImportRGBA(&pic, webPImageData, (int)webPBytesPerRow);
            }
            else
            {
                WebPPictureImportRGB(&pic, webPImageData, (int)webPBytesPerRow);
            }
            
            if(compressionLevel < 0)
            {
                WebPPictureARGBToYUVA(&pic, WEBP_YUV420);
                WebPCleanupTransparentArea(&pic);
            }
            
            WebPMemoryWriter writer;
            WebPMemoryWriterInit(&writer);
            pic.writer = WebPMemoryWrite;
            pic.custom_ptr = &writer;
            WebPEncode(&config, &pic);
                
            data = [NSData dataWithBytes:writer.mem length:writer.size];
                
            free(writer.mem);
            WebPPictureFree(&pic);
            CFRelease(webPImageDatRef);
        } else {
            data = UIImageJPEGRepresentation(image, compressionQuality);
        }
        [data writeToFile:[NSString stringWithUTF8String:filename.c_str()] atomically:YES];
    }

    [image release];

    if (needToCopyPixels)
    {
        delete [] pixels;
    }
    
    return true;
}

NS_CC_END

#endif // CC_PLATFORM_IOS

