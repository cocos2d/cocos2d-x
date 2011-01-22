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
#import <Foundation/Foundation.h>
#include <UIKit/UIKit.h>

#include <cstring>
#include "CCXBitmapDC.h"
#include "CCXApplication_iphone.h"
#include "CCDirector.h"
#include "platform/platform.h"

#include <string.h>

static bool isValidFontName(const char *fontName)
{
        bool ret = false;
        
        NSString *fontNameNS = [NSString stringWithUTF8String:fontName];
        
        for (NSString *familiName in [UIFont familyNames]) {
                if ([familiName isEqualToString:fontNameNS]) {
                        ret = true;
                        goto out;
                }
             
                for(NSString *font in [UIFont fontNamesForFamilyName: familiName]){
                        if ([font isEqualToString: fontNameNS]){
                                ret = true;
                                goto out;
                        }
                }
        }
        
out:
        return ret;
}

static void initWithString(const char *content, const char *fontName, float size, /*input params*/
						   int *pWidth, int *pHeight, unsigned char** ppData)  /*output params*/
{
	NSUInteger			width, height;
	unsigned char*			data;
	CGContextRef			context;
	CGColorSpaceRef		colorSpace;
	id				uiFont;
	NSString                *string;
	CGSize                  dimensions;
	UITextAlignment   alignment;
	NSString                *name;
    
	if (!pWidth || !pHeight || !ppData)
	{
		return;
	}
	
	alignment = UITextAlignmentCenter;
	string = [[NSString alloc] initWithUTF8String:content];
                //name = isValidFontName(fontName) ? [[NSString alloc] initWithUTF8String:fontName] : @"Thonburi";
        name = isValidFontName(fontName) ? [[NSString alloc] initWithUTF8String:fontName] : @"MarkerFelt-Wide";
	dimensions = [string sizeWithFont:[UIFont fontWithName:name size:size]];
    
	width = dimensions.width;
	height = dimensions.height;
	
	colorSpace = CGColorSpaceCreateDeviceRGB();
	data = new unsigned char[height * width * 4];
	
	memset(data, 0, height * width * 4);
	context = CGBitmapContextCreate(data, width, height, 8, width * 4, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
	CGColorSpaceRelease(colorSpace);
		
	CGContextSetRGBFillColor(context, 1, 1, 1, 1);
	CGContextTranslateCTM(context, 0.0f, height);
	CGContextScaleCTM(context, 1.0f, -1.0f); //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
	UIGraphicsPushContext(context);
    
	uiFont = [UIFont fontWithName:name size:size];
	CGRect rect;
	rect.origin.x = 0;
	rect.origin.y = 0;
	rect.size.width = dimensions.width;
	rect.size.height = dimensions.height;
	[string drawInRect:rect withFont:uiFont lineBreakMode:UILineBreakModeWordWrap alignment:alignment];

	UIGraphicsPopContext();
	
	CGContextRelease(context);
    
	[string release];
	[name release];
	
	// output params
	*pWidth = width;
	*pHeight = height;
	*ppData = data;
}

namespace cocos2d {

	CCXBitmapDC::CCXBitmapDC()
	:m_nWidth(0)
	,m_nHeight(0)
	,m_pData(NULL)
	{
	}
	
	CCXBitmapDC::CCXBitmapDC(const char *text, CGSize dimensions, UITextAlignment alignment, const char *fontName, float fontSize)
	{	
		initWithString(text, fontName, fontSize, &m_nWidth, &m_nHeight, &m_pData);
	}
	
	CCXBitmapDC::~CCXBitmapDC()
	{
		if (m_pData)
		{
			delete[] m_pData;
		}
	}
	
	int CCXBitmapDC::getWidth()
    {
    	return m_nWidth;
    }
    
    int CCXBitmapDC::getHeight()
    {
    	return m_nHeight;
    }
    
    unsigned char* CCXBitmapDC::getData()
    {
    	return m_pData;
    }
	
}
