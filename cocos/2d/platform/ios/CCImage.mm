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
#include "CCImageCommon_cpp.h"

#import "CCImage.h"
#import "CCFileUtils.h"
#import "platform/CCCommon.h"
#import <string>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#include<math.h>


typedef struct
{
    unsigned int height;
    unsigned int width;
    bool         isPremultipliedAlpha;
    bool         hasShadow;
    CGSize       shadowOffset;
    float        shadowBlur;
    float        shadowOpacity;
    bool         hasStroke;
    float        strokeColorR;
    float        strokeColorG;
    float        strokeColorB;
    float        strokeSize;
    float        tintColorR;
    float        tintColorG;
    float        tintColorB;
    
    unsigned char*  data;
    
} tImageInfo;

static CGSize _calculateStringSize(NSString *str, id font, CGSize *constrainSize)
{
    NSArray *listItems = [str componentsSeparatedByString: @"\n"];
    CGSize dim = CGSizeZero;
    CGSize textRect = CGSizeZero;
    textRect.width = constrainSize->width > 0 ? constrainSize->width
                                              : 0x7fffffff;
    textRect.height = constrainSize->height > 0 ? constrainSize->height
                                              : 0x7fffffff;
    
    
    for (NSString *s in listItems)
    {
        CGSize tmp = [s sizeWithFont:font constrainedToSize:textRect];
        
        if (tmp.width > dim.width)
        {
           dim.width = tmp.width; 
        }
        
        dim.height += tmp.height;
    }
    
    return dim;
}

// refer Image::ETextAlign
#define ALIGN_TOP    1
#define ALIGN_CENTER 3
#define ALIGN_BOTTOM 2

static bool _initWithString(const char * text, cocos2d::Image::TextAlign align, const char * fontName, int size, tImageInfo* info)
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! text || ! info);
        
        NSString * str          = [NSString stringWithUTF8String:text];
        NSString * fntName      = [NSString stringWithUTF8String:fontName];
        
        CGSize dim, constrainSize;
        
        constrainSize.width     = info->width;
        constrainSize.height    = info->height;
        
        // On iOS custom fonts must be listed beforehand in the App info.plist (in order to be usable) and referenced only the by the font family name itself when
        // calling [UIFont fontWithName]. Therefore even if the developer adds 'SomeFont.ttf' or 'fonts/SomeFont.ttf' to the App .plist, the font must
        // be referenced as 'SomeFont' when calling [UIFont fontWithName]. Hence we strip out the folder path components and the extension here in order to get just
        // the font family name itself. This stripping step is required especially for references to user fonts stored in CCB files; CCB files appear to store
        // the '.ttf' extensions when referring to custom fonts.
        fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
        
        // create the font   
        id font = [UIFont fontWithName:fntName size:size];
        
        if (font)
        {
            dim = _calculateStringSize(str, font, &constrainSize);
        }
        else
        {
            if (!font)
            {
                font = [UIFont systemFontOfSize:size];
            }
                
            if (font)
            {
                dim = _calculateStringSize(str, font, &constrainSize);
            }
        }

        CC_BREAK_IF(! font);
        
        // compute start point
        int startH = 0;
        if (constrainSize.height > dim.height)
        {
            // vertical alignment
            unsigned int vAlignment = ((int)align >> 4) & 0x0F;
            if (vAlignment == ALIGN_TOP)
            {
                startH = 0;
            }
            else if (vAlignment == ALIGN_CENTER)
            {
                startH = (constrainSize.height - dim.height) / 2;
            }
            else 
            {
                startH = constrainSize.height - dim.height;
            }
        }
        
        // adjust text rect
        if (constrainSize.width > 0 && constrainSize.width > dim.width)
        {
            dim.width = constrainSize.width;
        }
        if (constrainSize.height > 0 && constrainSize.height > dim.height)
        {
            dim.height = constrainSize.height;
        }
        
        
        // compute the padding needed by shadow and stroke
        float shadowStrokePaddingX = 0.0f;
        float shadowStrokePaddingY = 0.0f;
        
        if ( info->hasStroke )
        {
            shadowStrokePaddingX = ceilf(info->strokeSize);
            shadowStrokePaddingY = ceilf(info->strokeSize);
        }
        
        if ( info->hasShadow )
        {
            shadowStrokePaddingX = std::max(shadowStrokePaddingX, (float)fabs(info->shadowOffset.width));
            shadowStrokePaddingY = std::max(shadowStrokePaddingY, (float)fabs(info->shadowOffset.height));
        }
        
        // add the padding (this could be 0 if no shadow and no stroke)
        dim.width  += shadowStrokePaddingX;
        dim.height += shadowStrokePaddingY;
        
        
        unsigned char* data = new unsigned char[(int)(dim.width * dim.height * 4)];
        memset(data, 0, (int)(dim.width * dim.height * 4));
        
        // draw text
        CGColorSpaceRef colorSpace  = CGColorSpaceCreateDeviceRGB();
        CGContextRef context        = CGBitmapContextCreate(data,
                                                            dim.width,
                                                            dim.height,
                                                            8,
                                                            (int)(dim.width) * 4,
                                                            colorSpace,
                                                            kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);                
        if (!context)
        {
            CGColorSpaceRelease(colorSpace);
            delete[] data;
            break;
        }

        // text color
        CGContextSetRGBFillColor(context, info->tintColorR, info->tintColorG, info->tintColorB, 1);
        // move Y rendering to the top of the image
        CGContextTranslateCTM(context, 0.0f, (dim.height - shadowStrokePaddingY) );
        CGContextScaleCTM(context, 1.0f, -1.0f); //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
        
        // store the current context
        UIGraphicsPushContext(context);
        
        // measure text size with specified font and determine the rectangle to draw text in
        unsigned uHoriFlag = (int)align & 0x0f;
        UITextAlignment testAlign = (UITextAlignment)((2 == uHoriFlag) ? UITextAlignmentRight
                                : (3 == uHoriFlag) ? UITextAlignmentCenter
                                : UITextAlignmentLeft);

        
        // take care of stroke if needed
        if ( info->hasStroke )
        {
            CGContextSetTextDrawingMode(context, kCGTextFillStroke);
            CGContextSetRGBStrokeColor(context, info->strokeColorR, info->strokeColorG, info->strokeColorB, 1);
            CGContextSetLineWidth(context, info->strokeSize);
        }
        
        // take care of shadow if needed
        if ( info->hasShadow )
        {
            CGSize offset;
            offset.height = info->shadowOffset.height;
            offset.width  = info->shadowOffset.width;
            CGFloat shadowColorValues[] = {0, 0, 0, info->shadowOpacity};
            CGColorRef shadowColor = CGColorCreate (colorSpace, shadowColorValues);
            
            CGContextSetShadowWithColor(context, offset, info->shadowBlur, shadowColor);
            
            CGColorRelease (shadowColor);
        }
        
        CGColorSpaceRelease(colorSpace);        
        
        
        // normal fonts
        //if( [font isKindOfClass:[UIFont class] ] )
        //{
        //    [str drawInRect:CGRectMake(0, startH, dim.width, dim.height) withFont:font lineBreakMode:(UILineBreakMode)UILineBreakModeWordWrap alignment:align];
        //}
        //else // ZFont class
        //{
        //    [FontLabelStringDrawingHelper drawInRect:str rect:CGRectMake(0, startH, dim.width, dim.height) withZFont:font lineBreakMode:(UILineBreakMode)UILineBreakModeWordWrap 
        ////alignment:align];
        //}
    
        
        
        // compute the rect used for rendering the text
        // based on wether shadows or stroke are enabled
        
        float textOriginX  = 0.0;
        float textOrigingY = 0.0;
        
        float textWidth    = dim.width  - shadowStrokePaddingX;
        float textHeight   = dim.height - shadowStrokePaddingY;
        
        
        if ( info->shadowOffset.width < 0 )
        {
            textOriginX = shadowStrokePaddingX;
        }
        else
        {
            textOriginX = 0.0;
        }
        
        if (info->shadowOffset.height > 0)
        {
            textOrigingY = startH;
        }
        else
        {
            textOrigingY = startH - shadowStrokePaddingY;
        }
        
        CGRect rect = CGRectMake(textOriginX, textOrigingY, textWidth, textHeight);
        
        CGContextBeginTransparencyLayerWithRect(context, rect, nullptr);
        // actually draw the text in the context
		// XXX: ios7 casting
        [str drawInRect: rect withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:(NSTextAlignment)testAlign];

        CGContextEndTransparencyLayer(context);
        
        // pop the context
        UIGraphicsPopContext();
        
        // release the context
        CGContextRelease(context);
               
        // output params
        info->data                 = data;
        info->isPremultipliedAlpha = true;
        info->width                = dim.width;
        info->height               = dim.height;
        bRet                        = true;
        
    } while (0);

    return bRet;
}

NS_CC_BEGIN

bool Image::initWithString(
                            const char * pText,
                            int         nWidth /* = 0 */,
                            int         nHeight /* = 0 */,
                            TextAlign   eAlignMask /* = kAlignCenter */,
                            const char * pFontName /* = nil */,
                            int         nSize /* = 0 */)
{
    return initWithStringShadowStroke(pText, nWidth, nHeight, eAlignMask , pFontName, nSize);
}

bool Image::initWithStringShadowStroke(
                                         const char * text,
                                         int         width ,
                                         int         height ,
                                         TextAlign   alignMask ,
                                         const char * fontName ,
                                         int         size ,
                                         float       textTintR,
                                         float       textTintG,
                                         float       textTintB,
                                         bool shadow,
                                         float shadowOffsetX,
                                         float shadowOffsetY,
                                         float shadowOpacity,
                                         float shadowBlur,
                                         bool  stroke,
                                         float strokeR,
                                         float strokeG,
                                         float strokeB,
                                         float strokeSize)
{
    
    
    
    tImageInfo info = {0};
    info.width                  = width;
    info.height                 = height;
    info.hasShadow              = shadow;
    info.shadowOffset.width     = shadowOffsetX;
    info.shadowOffset.height    = shadowOffsetY;
    info.shadowBlur             = shadowBlur;
    info.shadowOpacity          = shadowOpacity;
    info.hasStroke              =  stroke;
    info.strokeColorR           =  strokeR;
    info.strokeColorG           = strokeG;
    info.strokeColorB           = strokeB;
    info.strokeSize             = strokeSize;
    info.tintColorR             = textTintR;
    info.tintColorG             = textTintG;
    info.tintColorB             = textTintB;
    
    
    if (! _initWithString(text, alignMask, fontName, size, &info))
    {
        return false;
    }
    _height = (short)info.height;
    _width = (short)info.width;
    _renderFormat = Texture2D::PixelFormat::RGBA8888;
    _preMulti = info.isPremultipliedAlpha;
    _data = info.data;
    _dataLen = _width * _height * 4;
    
    return true;
}

bool Image::saveToFile(const std::string& filename, bool isToRGB)
{
    bool saveToPNG = false;
    bool needToCopyPixels = false;

    if (std::string::npos != filename.find(".png"))
    {
        saveToPNG = true;
    }
        
    int bitsPerComponent = 8;            
    int bitsPerPixel = hasAlpha() ? 32 : 24;
    if ((! saveToPNG) || isToRGB)
    {
        bitsPerPixel = 24;
    }            
    
    int bytesPerRow    = (bitsPerPixel/8) * _width;
    int myDataLength = bytesPerRow * _height;
    
    unsigned char *pixels    = _data;
    
    // The data has alpha channel, and want to save it with an RGB png file,
    // or want to save as jpg,  remove the alpha channel.
    if ((saveToPNG && hasAlpha() && isToRGB)
       || (! saveToPNG))
    {
        pixels = new unsigned char[myDataLength];
        
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
        bitmapInfo |= kCGImageAlphaPremultipliedLast;
    }
    CGDataProviderRef provider        = CGDataProviderCreateWithData(nullptr, pixels, myDataLength, nullptr);
    CGColorSpaceRef colorSpaceRef    = CGColorSpaceCreateDeviceRGB();
    CGImageRef iref                    = CGImageCreate(_width, _height,
                                                        bitsPerComponent, bitsPerPixel, bytesPerRow,
                                                        colorSpaceRef, bitmapInfo, provider,
                                                        nullptr, false,
                                                        kCGRenderingIntentDefault);
        
    UIImage* image                    = [[UIImage alloc] initWithCGImage:iref];
        
    CGImageRelease(iref);    
    CGColorSpaceRelease(colorSpaceRef);
    CGDataProviderRelease(provider);
    
    NSData *data;
                
    if (saveToPNG)
    {
        data = UIImagePNGRepresentation(image);
    }
    else
    {
        data = UIImageJPEGRepresentation(image, 1.0f);
    }
    
    [data writeToFile:[NSString stringWithUTF8String:filename.c_str()] atomically:YES];
        
    [image release];
        
    if (needToCopyPixels)
    {
        delete [] pixels;
    }
    
    return true;
}

NS_CC_END

