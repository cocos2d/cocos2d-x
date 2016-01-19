/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include "platform/CCDevice.h"
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <string>
#include "base/ccTypes.h"

NS_CC_BEGIN

int Device::getDPI()
{
    NSScreen *screen = [NSScreen mainScreen];
    NSDictionary *description = [screen deviceDescription];
    NSSize displayPixelSize = [[description objectForKey:NSDeviceSize] sizeValue];
    CGSize displayPhysicalSize = CGDisplayScreenSize([[description objectForKey:@"NSScreenNumber"] unsignedIntValue]);
    
    return ((displayPixelSize.width / displayPhysicalSize.width) * 25.4f);
}

void Device::setAccelerometerEnabled(bool isEnabled)
{

}

void Device::setAccelerometerInterval(float interval)
{

}

typedef struct
{
    int height;
    int width;
    bool hasAlpha;
    bool isPremultipliedAlpha;
    unsigned char* data;
} tImageInfo;

static NSSize _calculateStringSize(NSString *str, id font, CGSize *constrainSize)
{
    NSSize textRect = NSZeroSize;
    textRect.width = constrainSize->width > 0 ? constrainSize->width
    : 0x7fffffff;
    textRect.height = constrainSize->height > 0 ? constrainSize->height
    : 0x7fffffff;
    
    NSSize dim;
    NSDictionary *attibutes = @{NSFontAttributeName:font};
#ifdef __MAC_10_11
    #if __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_11
    dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin) attributes:attibutes context:nil].size;
    #else
    dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin) attributes:attibutes].size;
    #endif
#else
    dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin) attributes:attibutes].size;
#endif
    
    dim.width = ceilf(dim.width);
    dim.height = ceilf(dim.height);

    return dim;
}

static bool _initWithString(const char * text, Device::TextAlign align, const char * fontName, int size, tImageInfo* info, const Color3B* fontColor, int fontAlpha)
{
    bool ret = false;
    
    CCASSERT(text, "Invalid text");
    CCASSERT(info, "Invalid info");
    
    do {
        NSString * string  = [NSString stringWithUTF8String:text];
        NSString * fntName = [NSString stringWithUTF8String:fontName];
        fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
        
        // font
        NSFont *font = [[NSFontManager sharedFontManager]
                        fontWithFamily:fntName
                        traits:NSUnboldFontMask | NSUnitalicFontMask
                        weight:0
                        size:size];
        if (font == nil) {
            font = [[NSFontManager sharedFontManager]
                    fontWithFamily:@"Arial"
                    traits:NSUnboldFontMask | NSUnitalicFontMask
                    weight:0
                    size:size];
        }
        CC_BREAK_IF(!font);
        
        // color
        NSColor* foregroundColor;
        if (fontColor) {
            foregroundColor = [NSColor colorWithDeviceRed:fontColor->r/255.0 green:fontColor->g/255.0 blue:fontColor->b/255.0 alpha:fontAlpha/255.0];
        } else {
            foregroundColor = [NSColor whiteColor];
        }
        
        // alignment
        unsigned horiFlag = (int)align & 0x0f;
        NSTextAlignment textAlign = NSLeftTextAlignment;
        switch (horiFlag) {
            case 2:
                textAlign = NSRightTextAlignment;
                break;
            case 3:
                textAlign = NSCenterTextAlignment;
                break;
            default:
                break;
        }
        
        NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
        [paragraphStyle setParagraphStyle:[NSParagraphStyle defaultParagraphStyle]];
        [paragraphStyle setLineBreakMode:NSLineBreakByWordWrapping];
        [paragraphStyle setAlignment:textAlign];
        
        // attribute
        NSDictionary* tokenAttributesDict = [NSDictionary dictionaryWithObjectsAndKeys:
                                             foregroundColor,NSForegroundColorAttributeName,
                                             font, NSFontAttributeName,
                                             paragraphStyle, NSParagraphStyleAttributeName, nil];
        NSAttributedString *stringWithAttributes =[[[NSAttributedString alloc] initWithString:string
                                                                                   attributes:tokenAttributesDict] autorelease];
        
        CGSize dimensions = CGSizeMake(info->width, info->height);
        NSSize realDimensions = _calculateStringSize(string, font, &dimensions);
        // Mac crashes if the width or height is 0
        CC_BREAK_IF(realDimensions.width <= 0 || realDimensions.height <= 0);
        
        if(dimensions.width <= 0.f) {
            dimensions.width = realDimensions.width;
        }
        if (dimensions.height <= 0.f) {
            dimensions.height = realDimensions.height;
        }
        
        //Alignment
        CGFloat xPadding = 0;
        switch (textAlign) {
            case NSLeftTextAlignment: xPadding = 0; break;
            case NSCenterTextAlignment: xPadding = (dimensions.width - realDimensions.width) / 2.0f; break;
            case NSRightTextAlignment: xPadding = dimensions.width - realDimensions.width; break;
            default: break;
        }
        
        CGFloat yPadding = 0.f;
        unsigned vertFlag = ((int)align >> 4) & 0x0f;
        switch (vertFlag) {
            // align to top
            case 1: yPadding = dimensions.height - realDimensions.height; break;
            // align to bottom
            case 2: yPadding = 0.f; break;
            // align to center
            case 3: yPadding = (dimensions.height - realDimensions.height) / 2.0f; break;
            default: break;
        }
        
        NSInteger POTWide = dimensions.width;
        NSInteger POTHigh = dimensions.height;
        NSRect textRect = NSMakeRect(xPadding, POTHigh - dimensions.height + yPadding, realDimensions.width, realDimensions.height);
        [[NSGraphicsContext currentContext] setShouldAntialias:NO];
        
        NSImage *image = [[NSImage alloc] initWithSize:NSMakeSize(POTWide, POTHigh)];
        [image lockFocus];
        // patch for mac retina display and lableTTF
        [[NSAffineTransform transform] set];
        [stringWithAttributes drawInRect:textRect];
        NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect (0.0f, 0.0f, POTWide, POTHigh)];
        [image unlockFocus];
        
        auto data = (unsigned char*) [bitmap bitmapData];  //Use the same buffer to improve the performance.
        
        NSUInteger textureSize = POTWide * POTHigh * 4;
        auto dataNew = (unsigned char*)malloc(sizeof(unsigned char) * textureSize);
        if (dataNew) {
            memcpy(dataNew, data, textureSize);
            // output params
            info->width = static_cast<int>(POTWide);
            info->height = static_cast<int>(POTHigh);
            info->data = dataNew;
            info->hasAlpha = true;
            info->isPremultipliedAlpha = true;
            ret = true;
        }
        [bitmap release];
        [image release];
    } while (0);
    return ret;
}

Data Device::getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha)
{
    Data ret;
    do {
        tImageInfo info = {0};
        info.width = textDefinition._dimensions.width;
        info.height = textDefinition._dimensions.height;
        
        if (! _initWithString(text, align, textDefinition._fontName.c_str(), textDefinition._fontSize, &info, &textDefinition._fontFillColor, textDefinition._fontAlpha))
        {
            break;
        }
        height = (short)info.height;
        width = (short)info.width;
        ret.fastSet(info.data,width * height * 4);
        hasPremultipliedAlpha = true;
    } while (0);
    
    return ret;
}

void Device::setKeepScreenOn(bool value)
{
    CC_UNUSED_PARAM(value);
}

void Device::vibrate(float duration)
{
    CC_UNUSED_PARAM(duration);
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC