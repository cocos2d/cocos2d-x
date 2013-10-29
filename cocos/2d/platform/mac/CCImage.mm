/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCImageCommon_cpp.h"
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "CCDirector.h"
#include "ccMacros.h"
#include "CCImage.h"
#include "CCFileUtils.h"
#include "CCTexture2D.h"
#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

NS_CC_BEGIN

typedef struct
{
    unsigned int height;
    unsigned int width;
    bool        hasAlpha;
    bool        isPremultipliedAlpha;
    unsigned char*  data;
} tImageInfo;

static bool _initWithString(const char * pText, cocos2d::Image::TextAlign eAlign, const char * pFontName, int nSize, tImageInfo* pInfo, cocos2d::Color3B* pStrokeColor)
{
    bool bRet = false;

	CCASSERT(pText, "Invalid pText");
	CCASSERT(pInfo, "Invalid pInfo");
	
	do {
		NSString * string  = [NSString stringWithUTF8String:pText];
		
		// font
		NSFont *font = [[NSFontManager sharedFontManager]
						 fontWithFamily:[NSString stringWithUTF8String:pFontName]
						traits:NSUnboldFontMask | NSUnitalicFontMask
						 weight:0
						 size:nSize];
		
		if (font == nil) {
			font = [[NSFontManager sharedFontManager]
					fontWithFamily:@"Arial"
					traits:NSUnboldFontMask | NSUnitalicFontMask
					weight:0
					size:nSize];
		}
		CC_BREAK_IF(!font);
		
		// color
		NSColor* foregroundColor;
		if (pStrokeColor) {
			foregroundColor = [NSColor colorWithDeviceRed:pStrokeColor->r/255.0 green:pStrokeColor->g/255.0 blue:pStrokeColor->b/255.0 alpha:1];
		} else {
			foregroundColor = [NSColor whiteColor];
		}
		
		
		// alignment, linebreak
		unsigned uHoriFlag = (int)eAlign & 0x0f;
		unsigned uVertFlag = ((int)eAlign >> 4) & 0x0f;
		NSTextAlignment align = (2 == uHoriFlag) ? NSRightTextAlignment
			: (3 == uHoriFlag) ? NSCenterTextAlignment
			: NSLeftTextAlignment;
		
		NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
		[paragraphStyle setParagraphStyle:[NSParagraphStyle defaultParagraphStyle]];
		[paragraphStyle setLineBreakMode:NSLineBreakByCharWrapping];
		[paragraphStyle setAlignment:align];

		// attribute
		NSDictionary* tokenAttributesDict = [NSDictionary dictionaryWithObjectsAndKeys:
											 foregroundColor,NSForegroundColorAttributeName,
											 font, NSFontAttributeName,
											 paragraphStyle, NSParagraphStyleAttributeName, nil];

		// linebreak
		if (pInfo->width > 0) {
			if ([string sizeWithAttributes:tokenAttributesDict].width > pInfo->width) {
				NSMutableString *lineBreak = [[[NSMutableString alloc] init] autorelease];
				NSUInteger length = [string length];
				NSRange range = NSMakeRange(0, 1);
				NSUInteger width = 0;
				NSUInteger lastBreakLocation = 0;
				for (NSUInteger i = 0; i < length; i++) {
					range.location = i;
					NSString *character = [string substringWithRange:range];
					[lineBreak appendString:character];
					if ([@"!?.,-= " rangeOfString:character].location != NSNotFound) { lastBreakLocation = i; }
					width = [lineBreak sizeWithAttributes:tokenAttributesDict].width;
					if (width > pInfo->width) {
						[lineBreak insertString:@"\r\n" atIndex:(lastBreakLocation > 0) ? lastBreakLocation : [lineBreak length] - 1];
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
				
		CGSize dimensions = CGSizeMake(pInfo->width, pInfo->height);
		
	
		if(dimensions.width <= 0 && dimensions.height <= 0) {
			dimensions.width = realDimensions.width;
			dimensions.height = realDimensions.height;
		} else if (dimensions.height <= 0) {
			dimensions.height = realDimensions.height;
		}

		NSUInteger POTWide = (NSUInteger)dimensions.width;
		NSUInteger POTHigh = (NSUInteger)(MAX(dimensions.height, realDimensions.height));
		unsigned char*			data;
		//Alignment
			
		CGFloat xPadding = 0;
		switch (align) {
			case NSLeftTextAlignment: xPadding = 0; break;
			case NSCenterTextAlignment: xPadding = (dimensions.width-realDimensions.width)/2.0f; break;
			case NSRightTextAlignment: xPadding = dimensions.width-realDimensions.width; break;
			default: break;
		}

		// 1: TOP
		// 2: BOTTOM
		// 3: CENTER
		CGFloat yPadding = (1 == uVertFlag || realDimensions.height >= dimensions.height) ? (dimensions.height - realDimensions.height)	// align to top
		: (2 == uVertFlag) ? 0																	// align to bottom
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
		
		unsigned char* dataNew = new unsigned char[textureSize];
		if (dataNew) {
			memcpy(dataNew, data, textureSize);
			// output params
			pInfo->width = POTWide;
			pInfo->height = POTHigh;
			pInfo->data = dataNew;
			pInfo->hasAlpha = true;
			pInfo->isPremultipliedAlpha = true;
			bRet = true;
		}
		[bitmap release];
		[image release];
	} while (0);
    return bRet;
}

bool Image::initWithString(
	const char *    pText, 
	int             nWidth, 
	int             nHeight,
	TextAlign      eAlignMask,
	const char *    pFontName,
	int             nSize)
{
    tImageInfo info = {0};
    info.width = nWidth;
    info.height = nHeight;
	
    if (! _initWithString(pText, eAlignMask, pFontName, nSize, &info, NULL)) //pStrokeColor))
    {
        return false;
    }
    _height = (short)info.height;
    _width = (short)info.width;
    _renderFormat = Texture2D::PixelFormat::RGBA8888;
    _preMulti = info.isPremultipliedAlpha;
	if (_data) {
		CC_SAFE_DELETE_ARRAY(_data);
	}
    _data = info.data;
    _dataLen = _width * _height * 4;

    return true;
}


NS_CC_END

