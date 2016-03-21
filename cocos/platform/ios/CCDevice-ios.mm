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
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "platform/CCDevice.h"
#include "base/ccTypes.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventAcceleration.h"
#include "base/CCDirector.h"
#import <UIKit/UIKit.h>

// Accelerometer
#if !defined(CC_TARGET_OS_TVOS)
#import<CoreMotion/CoreMotion.h>
#endif
#import<CoreFoundation/CoreFoundation.h>

// Vibrate
#import <AudioToolbox/AudioToolbox.h>

#define SENSOR_DELAY_GAME 0.02

#if !defined(CC_TARGET_OS_TVOS)
@interface CCAccelerometerDispatcher : NSObject<UIAccelerometerDelegate>
{
    cocos2d::Acceleration *_acceleration;
    CMMotionManager *_motionManager;
}

+ (id) sharedAccelerometerDispatcher;
- (id) init;
- (void) setAccelerometerEnabled: (bool) isEnabled;
- (void) setAccelerometerInterval:(float) interval;

@end

@implementation CCAccelerometerDispatcher

static CCAccelerometerDispatcher* s_pAccelerometerDispatcher;

+ (id) sharedAccelerometerDispatcher
{
    if (s_pAccelerometerDispatcher == nil) {
        s_pAccelerometerDispatcher = [[self alloc] init];
    }
    
    return s_pAccelerometerDispatcher;
}

- (id) init
{
    if( (self = [super init]) ) {
        _acceleration = new (std::nothrow) cocos2d::Acceleration();
        _motionManager = [[CMMotionManager alloc] init];
        _motionManager.accelerometerUpdateInterval = SENSOR_DELAY_GAME;
    }
    return self;
}

- (void) dealloc
{
    s_pAccelerometerDispatcher = nullptr;
    delete _acceleration;
    [_motionManager release];
    [super dealloc];
}

- (void) setAccelerometerEnabled: (bool) isEnabled
{
    if (isEnabled)
    {
        [_motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue] withHandler:^(CMAccelerometerData *accelerometerData, NSError *error) {
            [self accelerometer:accelerometerData];
        }];
    }
    else
    {
        [_motionManager stopAccelerometerUpdates];
    }
}

-(void) setAccelerometerInterval:(float)interval
{
    _motionManager.accelerometerUpdateInterval = interval;
}

- (void)accelerometer:(CMAccelerometerData *)accelerometerData
{
    _acceleration->x = accelerometerData.acceleration.x;
    _acceleration->y = accelerometerData.acceleration.y;
    _acceleration->z = accelerometerData.acceleration.z;
    _acceleration->timestamp = accelerometerData.timestamp;
    
    double tmp = _acceleration->x;
    
    switch ([[UIApplication sharedApplication] statusBarOrientation])
    {
        case UIInterfaceOrientationLandscapeRight:
            _acceleration->x = -_acceleration->y;
            _acceleration->y = tmp;
            break;
            
        case UIInterfaceOrientationLandscapeLeft:
            _acceleration->x = _acceleration->y;
            _acceleration->y = -tmp;
            break;
            
        case UIInterfaceOrientationPortraitUpsideDown:
            _acceleration->x = -_acceleration->y;
            _acceleration->y = -tmp;
            break;
            
        case UIInterfaceOrientationPortrait:
            break;
        default:
            NSAssert(false, @"unknow orientation");
    }

    cocos2d::EventAcceleration event(*_acceleration);
    auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchEvent(&event);
}
@end
#endif // !defined(CC_TARGET_OS_TVOS)


//

NS_CC_BEGIN

int Device::getDPI()
{
    static int dpi = -1;

    if (dpi == -1)
    {
        float scale = 1.0f;
        
        if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
            scale = [[UIScreen mainScreen] scale];
        }
        
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
            dpi = 132 * scale;
        } else if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
            dpi = 163 * scale;
        } else {
            dpi = 160 * scale;
        }
    }
    return dpi;
}


void Device::setAccelerometerEnabled(bool isEnabled)
{
#if !defined(CC_TARGET_OS_TVOS)
    [[CCAccelerometerDispatcher sharedAccelerometerDispatcher] setAccelerometerEnabled:isEnabled];
#endif
}

void Device::setAccelerometerInterval(float interval)
{
#if !defined(CC_TARGET_OS_TVOS)
    [[CCAccelerometerDispatcher sharedAccelerometerDispatcher] setAccelerometerInterval:interval];
#endif
}

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
    float        strokeColorA;
    float        strokeSize;
    float        tintColorR;
    float        tintColorG;
    float        tintColorB;
    float        tintColorA;
    
    unsigned char*  data;
    
} tImageInfo;

static bool s_isIOS7OrHigher = false;

static inline void lazyCheckIOS7()
{
    static bool isInited = false;
    if (!isInited)
    {
        s_isIOS7OrHigher = [[[UIDevice currentDevice] systemVersion] compare:@"7.0" options:NSNumericSearch] != NSOrderedAscending;
        isInited = true;
    }
}

static CGSize _calculateStringSize(NSString *str, id font, CGSize *constrainSize)
{
    CGSize textRect = CGSizeZero;
    textRect.width = constrainSize->width > 0 ? constrainSize->width
    : 0x7fffffff;
    textRect.height = constrainSize->height > 0 ? constrainSize->height
    : 0x7fffffff;
    
    CGSize dim;
    if(s_isIOS7OrHigher){
        NSDictionary *attibutes = @{NSFontAttributeName:font};
        dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin) attributes:attibutes context:nil].size;
    }
#if !defined(CC_TARGET_OS_TVOS)
    // not available on tvOS, and tvOS version is >= 7.0
    else {
        dim = [str sizeWithFont:font constrainedToSize:textRect];
    }
#endif

    dim.width = ceilf(dim.width);
    dim.height = ceilf(dim.height);
    
    return dim;
}

// refer Image::ETextAlign
#define ALIGN_TOP    1
#define ALIGN_CENTER 3
#define ALIGN_BOTTOM 2


static bool _initWithString(const char * text, cocos2d::Device::TextAlign align, const char * fontName, int size, tImageInfo* info)
{
    // lazy check whether it is iOS7 device
    lazyCheckIOS7();
    
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
        
        // add the padding (this could be 0 if no shadow and no stroke)
        dim.width  += shadowStrokePaddingX*2;
        dim.height += shadowStrokePaddingY*2;
        
        
        unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * (int)(dim.width * dim.height * 4));
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
            CC_SAFE_FREE(data);
            break;
        }
        
        // text color
        CGContextSetRGBFillColor(context, info->tintColorR, info->tintColorG, info->tintColorB, info->tintColorA);
        // move Y rendering to the top of the image
        CGContextTranslateCTM(context, 0.0f, (dim.height - shadowStrokePaddingY) );
        CGContextScaleCTM(context, 1.0f, -1.0f); //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
        
        // store the current context
        UIGraphicsPushContext(context);
        
        // measure text size with specified font and determine the rectangle to draw text in
        unsigned uHoriFlag = (int)align & 0x0f;
        NSTextAlignment nsAlign = (2 == uHoriFlag) ? NSTextAlignmentRight
                                                  : (3 == uHoriFlag) ? NSTextAlignmentCenter
                                                  : NSTextAlignmentLeft;
         
        
        CGColorSpaceRelease(colorSpace);
        
        // compute the rect used for rendering the text
        // based on wether shadows or stroke are enabled
        
        float textOriginX  = 0;
        float textOrigingY = startH;
        
        float textWidth    = dim.width;
        float textHeight   = dim.height;
        
        CGRect rect = CGRectMake(textOriginX, textOrigingY, textWidth, textHeight);
        
        CGContextSetShouldSubpixelQuantizeFonts(context, false);
        
        CGContextBeginTransparencyLayerWithRect(context, rect, NULL);
        
        if ( info->hasStroke )
        {
            CGContextSetTextDrawingMode(context, kCGTextStroke);
            
            if(s_isIOS7OrHigher)
            {
                NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
                paragraphStyle.alignment = nsAlign;
                paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
                [str drawInRect:rect withAttributes:@{
                                                      NSFontAttributeName: font,
                                                      NSStrokeWidthAttributeName: [NSNumber numberWithFloat: info->strokeSize / size * 100 ],
                                                      NSForegroundColorAttributeName:[UIColor colorWithRed:info->tintColorR
                                                                                                     green:info->tintColorG
                                                                                                      blue:info->tintColorB
                                                                                                     alpha:info->tintColorA],
                                                      NSParagraphStyleAttributeName:paragraphStyle,
                                                      NSStrokeColorAttributeName: [UIColor colorWithRed:info->strokeColorR
                                                                                                  green:info->strokeColorG
                                                                                                   blue:info->strokeColorB
                                                                                                  alpha:info->strokeColorA]
                                                      }
                 ];
                
                [paragraphStyle release];
            }

#if !defined(CC_TARGET_OS_TVOS)
            // not available on tvOS, and tvOS version is >= 7.0
            else
            {
                CGContextSetRGBStrokeColor(context, info->strokeColorR, info->strokeColorG, info->strokeColorB, info->strokeColorA);
                CGContextSetLineWidth(context, info->strokeSize);
                
                //original code that was not working in iOS 7
                [str drawInRect: rect withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:nsAlign];
            }
#endif
        }
        
        CGContextSetTextDrawingMode(context, kCGTextFill);

        // actually draw the text in the context
        if (s_isIOS7OrHigher)
        {
            NSMutableParagraphStyle* paragraphStyle = [[NSMutableParagraphStyle alloc] init];
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            paragraphStyle.alignment = nsAlign;

            NSDictionary *attributes = @{ NSFontAttributeName: font,
                                          NSParagraphStyleAttributeName: paragraphStyle,
                                          NSForegroundColorAttributeName: [UIColor colorWithRed:info->tintColorR
                                                                                         green:info->tintColorG
                                                                                          blue:info->tintColorB
                                                                                         alpha:info->tintColorA]
                                          };
            [str drawInRect:rect withAttributes: attributes];
            [paragraphStyle release];
        }
#if !defined(CC_TARGET_OS_TVOS)
        else
        {
            [str drawInRect: rect withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:nsAlign];
        }
#endif

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


Data Device::getTextureDataForText(const char * text, const FontDefinition& textDefinition, TextAlign align, int &width, int &height, bool& hasPremultipliedAlpha)
{
    Data ret;
    
    do {
        tImageInfo info = {0};
        info.width                  = textDefinition._dimensions.width;
        info.height                 = textDefinition._dimensions.height;
        info.hasShadow              = textDefinition._shadow._shadowEnabled;
        info.shadowOffset.width     = textDefinition._shadow._shadowOffset.width;
        info.shadowOffset.height    = textDefinition._shadow._shadowOffset.height;
        info.shadowBlur             = textDefinition._shadow._shadowBlur;
        info.shadowOpacity          = textDefinition._shadow._shadowOpacity;
        info.hasStroke              = textDefinition._stroke._strokeEnabled;
        info.strokeColorR           = textDefinition._stroke._strokeColor.r / 255.0f;
        info.strokeColorG           = textDefinition._stroke._strokeColor.g / 255.0f;
        info.strokeColorB           = textDefinition._stroke._strokeColor.b / 255.0f;
        info.strokeColorA           = textDefinition._stroke._strokeAlpha / 255.0f;
        info.strokeSize             = textDefinition._stroke._strokeSize;
        info.tintColorR             = textDefinition._fontFillColor.r / 255.0f;
        info.tintColorG             = textDefinition._fontFillColor.g / 255.0f;
        info.tintColorB             = textDefinition._fontFillColor.b / 255.0f;
        info.tintColorA             = textDefinition._fontAlpha / 255.0f;
        
        if (! _initWithString(text, align, textDefinition._fontName.c_str(), textDefinition._fontSize, &info))
        {
            break;
        }
        height = info.height;
        width = info.width;
        ret.fastSet(info.data,width * height * 4);
        hasPremultipliedAlpha = true;
    } while (0);
    
    return ret;
}

void Device::setKeepScreenOn(bool value)
{
    [[UIApplication sharedApplication] setIdleTimerDisabled:(BOOL)value];
}

/*!
 @brief Only works on iOS devices that support vibration (such as iPhone). Should only be used for important alerts. Use risks rejection in iTunes Store.
 @param duration ignored for iOS
 */
void Device::vibrate(float duration)
{
    // See https://developer.apple.com/library/ios/documentation/AudioToolbox/Reference/SystemSoundServicesReference/index.html#//apple_ref/c/econst/kSystemSoundID_Vibrate
    CC_UNUSED_PARAM(duration);
    
    // automatically vibrates for approximately 0.4 seconds
    AudioServicesPlayAlertSound(kSystemSoundID_Vibrate);
}

NS_CC_END

#endif // CC_PLATFORM_IOS

