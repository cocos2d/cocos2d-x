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

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include "platform/CCDevice.h"
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <string>
#include "ccTypes.h"

NS_CC_BEGIN

int Device::getDPI()
{
//TODO: 
    return 160;
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
    bool        hasAlpha;
    bool        isPremultipliedAlpha;
    unsigned char*  data;
} tImageInfo;

static bool _initWithString(const char * text, Device::TextAlign align, const char * fontName, int size, tImageInfo* info, Color3B* strokeColor)
{
    bool ret = false;
    
	CCASSERT(text, "Invalid pText");
	CCASSERT(info, "Invalid pInfo");
	
	do {
		NSString * string  = [NSString stringWithUTF8String:text];
		
		// font
		NSFont *font = [[NSFontManager sharedFontManager]
                        fontWithFamily:[NSString stringWithUTF8String:fontName]
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
		if (strokeColor) {
			foregroundColor = [NSColor colorWithDeviceRed:strokeColor->r/255.0 green:strokeColor->g/255.0 blue:strokeColor->b/255.0 alpha:1];
		} else {
			foregroundColor = [NSColor whiteColor];
		}
		
		
		// alignment, linebreak
		unsigned horiFlag = (int)align & 0x0f;
		unsigned vertFlag = ((int)align >> 4) & 0x0f;
		NSTextAlignment textAlign = (2 == horiFlag) ? NSRightTextAlignment
        : (3 == horiFlag) ? NSCenterTextAlignment
        : NSLeftTextAlignment;
		
		NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
		[paragraphStyle setParagraphStyle:[NSParagraphStyle defaultParagraphStyle]];
		[paragraphStyle setLineBreakMode:NSLineBreakByCharWrapping];
		[paragraphStyle setAlignment:textAlign];
        
		// attribute
		NSDictionary* tokenAttributesDict = [NSDictionary dictionaryWithObjectsAndKeys:
											 foregroundColor,NSForegroundColorAttributeName,
											 font, NSFontAttributeName,
											 paragraphStyle, NSParagraphStyleAttributeName, nil];
        
        // linebreak
		if (info->width > 0) {
			if ([string sizeWithAttributes:tokenAttributesDict].width > info->width) {
				NSMutableString *lineBreak = [[[NSMutableString alloc] init] autorelease];
				NSUInteger length = [string length];
				NSRange range = NSMakeRange(0, 1);
                CGSize textSize;
				NSUInteger lastBreakLocation = 0;
                NSUInteger insertCount = 0;
				for (NSUInteger i = 0; i < length; i++) {
					range.location = i;
					NSString *character = [string substringWithRange:range];
					[lineBreak appendString:character];
					if ([@"!?.,-= " rangeOfString:character].location != NSNotFound) {
                        lastBreakLocation = i + insertCount;
                    }
                    textSize = [lineBreak sizeWithAttributes:tokenAttributesDict];
                    if(textSize.height > info->height)
                        break;
					if (textSize.width > info->width) {
                        if(lastBreakLocation > 0) {
                            [lineBreak insertString:@"\r" atIndex:lastBreakLocation];
                            lastBreakLocation = 0;
                        }
                        else {
                            [lineBreak insertString:@"\r" atIndex:[lineBreak length] - 1];
                        }
                        insertCount += 1;
					}
				}
                
				string = lineBreak;
			}
		}
        
		NSAttributedString *stringWithAttributes =[[[NSAttributedString alloc] initWithString:string
                                                                                   attributes:tokenAttributesDict] autorelease];
        
		NSSize realDimensions = [stringWithAttributes size];
		// Mac crashes if the width or height is 0
		CC_BREAK_IF(realDimensions.width <= 0 || realDimensions.height <= 0);
        
		CGSize dimensions = CGSizeMake(info->width, info->height);
		
        
		if(dimensions.width <= 0 && dimensions.height <= 0) {
			dimensions.width = realDimensions.width;
			dimensions.height = realDimensions.height;
		} else if (dimensions.height <= 0) {
			dimensions.height = realDimensions.height;
		}
        
		NSInteger POTWide = dimensions.width;
		NSInteger POTHigh = MAX(dimensions.height, realDimensions.height);
		unsigned char*			data;
		//Alignment
        
		CGFloat xPadding = 0;
		switch (textAlign) {
			case NSLeftTextAlignment: xPadding = 0; break;
			case NSCenterTextAlignment: xPadding = (dimensions.width-realDimensions.width)/2.0f; break;
			case NSRightTextAlignment: xPadding = dimensions.width-realDimensions.width; break;
			default: break;
		}
        
		// 1: TOP
		// 2: BOTTOM
		// 3: CENTER
		CGFloat yPadding = (1 == vertFlag || realDimensions.height >= dimensions.height) ? (dimensions.height - realDimensions.height)	// align to top
		: (2 == vertFlag) ? 0																	// align to bottom
		: (dimensions.height - realDimensions.height) / 2.0f;									// align to center
		
		
		NSRect textRect = NSMakeRect(xPadding, POTHigh - dimensions.height + yPadding, realDimensions.width, realDimensions.height);
		//Disable antialias
		
		[[NSGraphicsContext currentContext] setShouldAntialias:NO];
		
		NSImage *image = [[NSImage alloc] initWithSize:NSMakeSize(POTWide, POTHigh)];
        
		[image lockFocus];
        
        // patch for mac retina display and lableTTF
        [[NSAffineTransform transform] set];
		
		//[stringWithAttributes drawAtPoint:NSMakePoint(xPadding, offsetY)]; // draw at offset position
		[stringWithAttributes drawInRect:textRect];
		//[stringWithAttributes drawInRect:textRect withAttributes:tokenAttributesDict];
		NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect (0.0f, 0.0f, POTWide, POTHigh)];
		[image unlockFocus];
		
		data = (unsigned char*) [bitmap bitmapData];  //Use the same buffer to improve the performance.
		
		NSUInteger textureSize = POTWide*POTHigh*4;
		
		unsigned char* dataNew = (unsigned char*)malloc(sizeof(unsigned char) * textureSize);
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

Data Device::getTextureDataForText(const char * text,const FontDefinition& textDefinition,TextAlign align,int &width,int &height)
{
    Data ret;
    do {
        tImageInfo info = {0};
        info.width = textDefinition._dimensions.width;
        info.height = textDefinition._dimensions.height;
        
        if (! _initWithString(text, align, textDefinition._fontName.c_str(), textDefinition._fontSize, &info, nullptr)) //pStrokeColor))
        {
            break;
        }
        height = (short)info.height;
        width = (short)info.width;
        ret.fastSet(info.data,width * height * 4);
    } while (0);
    
    return ret;
}
NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_MAC
