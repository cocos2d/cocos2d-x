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

#import <UIKit/UIKit.h>

#include "platform/CCDevice.h"
#include "base/ccTypes.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventAcceleration.h"
#include "base/CCDirector.h"
#include "platform/apple/CCDevice-apple.h"

// Accelerometer
#if !defined(CC_TARGET_OS_TVOS)
#import<CoreMotion/CoreMotion.h>
#endif
#import<CoreFoundation/CoreFoundation.h>
#import <CoreText/CoreText.h>
// Vibrate
#import <AudioToolbox/AudioToolbox.h>

const float MAX_MEASURE_HEIGHT = 10000;


static NSAttributedString* __attributedStringWithFontSize(NSMutableAttributedString* attributedString, CGFloat fontSize)
{
    {
        [attributedString beginEditing];

        [attributedString enumerateAttribute:NSFontAttributeName inRange:NSMakeRange(0, attributedString.length) options:0 usingBlock:^(id value, NSRange range, BOOL *stop) {

            UIFont* font = value;
            font = [font fontWithSize:fontSize];

            [attributedString removeAttribute:NSFontAttributeName range:range];
            [attributedString addAttribute:NSFontAttributeName value:font range:range];
        }];

        [attributedString endEditing];
    }

    return [[attributedString copy] autorelease];
}

static CGFloat _calculateTextDrawStartHeight(cocos2d::Device::TextAlign align, CGSize realDimensions, CGSize dimensions)
{
    float startH = 0;
    // vertical alignment
    unsigned int vAlignment = ((int)align >> 4) & 0x0F;
    switch (vAlignment) {
            //bottom
        case 2:startH = dimensions.height - realDimensions.height;break;
            //top
        case 1:startH = 0;break;
            //center
        case 3: startH = (dimensions.height - realDimensions.height) / 2;break;
        default:
            break;
    }
    return startH;
}

static CGSize _calculateShrinkedSizeForString(NSAttributedString **str,
                                              id font,
                                              CGSize constrainSize,
                                              bool enableWrap,
                                              int& newFontSize)
{
    CGRect actualSize = CGRectMake(0, 0, constrainSize.width + 1, constrainSize.height + 1);
    int fontSize = [font pointSize];
    fontSize = fontSize + 1;

    if (!enableWrap) {
        while (actualSize.size.width > constrainSize.width ||
               actualSize.size.height > constrainSize.height) {
            fontSize = fontSize - 1;

            if(fontSize < 0) {
                actualSize = CGRectMake(0, 0, 0, 0);
                break;
            }

            NSMutableAttributedString *mutableString = [[*str mutableCopy] autorelease];
            *str = __attributedStringWithFontSize(mutableString, fontSize);

            CTFramesetterRef framesetter = CTFramesetterCreateWithAttributedString((__bridge CFAttributedStringRef)*str);
            CGSize targetSize = CGSizeMake(MAX_MEASURE_HEIGHT, MAX_MEASURE_HEIGHT);
            CGSize fitSize = CTFramesetterSuggestFrameSizeWithConstraints(framesetter, CFRangeMake(0, [(*str) length]), NULL, targetSize, NULL);
            CFRelease(framesetter);
            if (fitSize.width == 0 || fitSize.height == 0) {
                continue;
            }
           
            actualSize.size = fitSize;
            
            if (constrainSize.width <= 0) {
                constrainSize.width = fitSize.width;
            }
            if (constrainSize.height <= 0) {
                constrainSize.height = fitSize.height;
            }
            if (fontSize <= 0) {
                break;
            }
        }

    }
    else {
        while (actualSize.size.height > constrainSize.height ||
               actualSize.size.width > constrainSize.width) {
            fontSize = fontSize - 1;
            if(fontSize < 0) {
                actualSize = CGRectMake(0, 0, 0, 0);
                break;
            }
            
            NSMutableAttributedString *mutableString = [[*str mutableCopy] autorelease];
            *str = __attributedStringWithFontSize(mutableString, fontSize);
            
            CGSize fitSize = [*str boundingRectWithSize:CGSizeMake(constrainSize.width, MAX_MEASURE_HEIGHT)
                                    options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingUsesFontLeading)
                                    context:nil].size;

            if (fitSize.width == 0 || fitSize.height == 0) {
                continue;
            }
            
            actualSize.size = fitSize;
            
            if (constrainSize.height <= 0) {
                constrainSize.height = fitSize.height;
            }
            if (constrainSize.width <= 0) {
                constrainSize.width = fitSize.width;
            }
            if (fontSize <= 0) {
                break;
            }
        }

    }

    newFontSize = fontSize;

    return CGSizeMake(ceilf(actualSize.size.width), ceilf(actualSize.size.height));
}

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
            NSAssert(false, @"unknown orientation");
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
    float        lineSpacing;

    unsigned char*  data;

} tImageInfo;

static CGSize _calculateStringSize(NSAttributedString *str, id font, CGSize *constrainSize, bool enableWrap, int overflow)
{
    CGSize textRect = CGSizeZero;
    textRect.width = constrainSize->width > 0 ? constrainSize->width
    : MAX_MEASURE_HEIGHT;
    textRect.height = constrainSize->height > 0 ? constrainSize->height
    : MAX_MEASURE_HEIGHT;
    
    if (overflow == 1) {
        if(!enableWrap) {
            textRect.width = MAX_MEASURE_HEIGHT;
            textRect.height = MAX_MEASURE_HEIGHT;
        } else {
            textRect.height = MAX_MEASURE_HEIGHT;
        }
    }

    CGSize dim;
    dim = [str boundingRectWithSize:CGSizeMake(textRect.width, textRect.height)
                                 options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingUsesFontLeading)
                            context:nil].size;

    dim.width = ceilf(dim.width);
    dim.height = ceilf(dim.height);

    return dim;
}

static id _createSystemFont( const char * fontName, int size)
{
    NSString * fntName      = [NSString stringWithUTF8String:fontName];
    // On iOS custom fonts must be listed beforehand in the App info.plist (in order to be usable) and referenced only the by the font family name itself when
    // calling [UIFont fontWithName]. Therefore even if the developer adds 'SomeFont.ttf' or 'fonts/SomeFont.ttf' to the App .plist, the font must
    // be referenced as 'SomeFont' when calling [UIFont fontWithName]. Hence we strip out the folder path components and the extension here in order to get just
    // the font family name itself. This stripping step is required especially for references to user fonts stored in CCB files; CCB files appear to store
    // the '.ttf' extensions when referring to custom fonts.
    fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
    
    // create the font
    id font = [UIFont fontWithName:fntName size:size];
    
    if (!font)
    {
        font = [UIFont systemFontOfSize:size];
    }
    return font;
}

static bool _initWithString(const char * text, cocos2d::Device::TextAlign align, const char * fontName, int size, tImageInfo* info, bool enableWrap, int overflow)
{

    bool bRet = false;
    do
    {
        CC_BREAK_IF(! text || ! info);

        id font = _createSystemFont(fontName, size);
        
        CC_BREAK_IF(! font);
        
        NSString * str          = [NSString stringWithUTF8String:text];
        CC_BREAK_IF(!str);

        CGSize dimensions;
        dimensions.width     = info->width;
        dimensions.height    = info->height;

        NSTextAlignment nsAlign = FontUtils::_calculateTextAlignment(align);
        NSMutableParagraphStyle* paragraphStyle = FontUtils::_calculateParagraphStyle(enableWrap, overflow);
        paragraphStyle.alignment = nsAlign;
        paragraphStyle.lineSpacing = info->lineSpacing;

        // measure text size with specified font and determine the rectangle to draw text in

        UIColor *foregroundColor = [UIColor colorWithRed:info->tintColorR
                                                  green:info->tintColorG
                                                   blue:info->tintColorB
                                                  alpha:info->tintColorA];

        // adjust text rect according to overflow
        NSMutableDictionary* tokenAttributesDict = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                             foregroundColor,NSForegroundColorAttributeName,
                                             font, NSFontAttributeName,
                                             paragraphStyle, NSParagraphStyleAttributeName, nil];

        NSAttributedString *stringWithAttributes =[[[NSAttributedString alloc] initWithString:str
                                                                                   attributes:tokenAttributesDict] autorelease];

        int shrinkFontSize = size;
        CGSize realDimensions;
        if (overflow == 2) {
            realDimensions = _calculateShrinkedSizeForString(&stringWithAttributes, font, dimensions, enableWrap, shrinkFontSize);
        } else {
            realDimensions = _calculateStringSize(stringWithAttributes, font, &dimensions, enableWrap, overflow);
        }

        
        CC_BREAK_IF(realDimensions.width <= 0 || realDimensions.height <= 0);
        if (dimensions.width <= 0) {
            dimensions.width = realDimensions.width;
        }
        if (dimensions.height <= 0) {
            dimensions.height = realDimensions.height;
        }

        // compute start point
        CGFloat yPadding = _calculateTextDrawStartHeight(align, realDimensions, dimensions);
        CGFloat xPadding = FontUtils::_calculateTextDrawStartWidth(align, realDimensions, dimensions);
        
        NSInteger POTWide = dimensions.width;
        NSInteger POTHigh = dimensions.height;
        
        CGRect textRect = CGRectMake(xPadding, yPadding,
                                     realDimensions.width, realDimensions.height);


        NSUInteger textureSize = POTWide * POTHigh * 4;
        unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * textureSize);
        memset(data, 0, textureSize);

        // draw text
        CGColorSpaceRef colorSpace  = CGColorSpaceCreateDeviceRGB();
        CGContextRef context        = CGBitmapContextCreate(data,
                                                            POTWide,
                                                            POTHigh,
                                                            8,
                                                            POTWide * 4,
                                                            colorSpace,
                                                            kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        if (!context)
        {
            CGColorSpaceRelease(colorSpace);
            CC_SAFE_FREE(data);
            break;
        }

        // text color
        CGContextSetRGBFillColor(context,
                                 info->tintColorR,
                                 info->tintColorG,
                                 info->tintColorB,
                                 info->tintColorA);

        // move Y rendering to the top of the image
        CGContextTranslateCTM(context, 0.0f, POTHigh);
        
        //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
        CGContextScaleCTM(context, 1.0f, -1.0f);
        // store the current context
        UIGraphicsPushContext(context);

        CGColorSpaceRelease(colorSpace);

        CGContextSetShouldSubpixelQuantizeFonts(context, false);

        CGContextBeginTransparencyLayerWithRect(context, textRect, NULL);


        if ( info->hasStroke )
        {
            CGContextSetTextDrawingMode(context, kCGTextStroke);
            UIColor *strokeColor = [UIColor colorWithRed:info->strokeColorR
                                                  green:info->strokeColorG
                                                   blue:info->strokeColorB
                                                  alpha:info->strokeColorA];

                
            NSMutableDictionary* tokenAttributesDict2 = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                                        foregroundColor,NSForegroundColorAttributeName,
                                                        font, NSFontAttributeName,
                                                        paragraphStyle, NSParagraphStyleAttributeName, nil];
            [tokenAttributesDict2 setObject:[NSNumber numberWithFloat: info->strokeSize / shrinkFontSize * 100]
                                     forKey:NSStrokeWidthAttributeName];
             [tokenAttributesDict2 setObject:strokeColor forKey:NSStrokeColorAttributeName];
            
            NSAttributedString *strokeString =[[[NSAttributedString alloc] initWithString:str
                                                                                       attributes:tokenAttributesDict2] autorelease];
            
            if(overflow == 2){
                _calculateShrinkedSizeForString(&strokeString, font, dimensions, enableWrap, shrinkFontSize);
            }


            [strokeString drawInRect:textRect];

        }

        CGContextSetTextDrawingMode(context, kCGTextFill);

        // actually draw the text in the context
        [stringWithAttributes drawInRect:textRect];

        CGContextEndTransparencyLayer(context);

        // pop the context
        UIGraphicsPopContext();

        // release the context
        CGContextRelease(context);
       
        // output params
        info->data                 = data;
        info->isPremultipliedAlpha = true;
        info->width                = static_cast<int>(POTWide);
        info->height               = static_cast<int>(POTHigh);
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
        info.lineSpacing            = textDefinition._lineSpacing;

        if (! _initWithString(text, align, textDefinition._fontName.c_str(), textDefinition._fontSize, &info, textDefinition._enableWrap, textDefinition._overflow))
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
    // See http://stackoverflow.com/questions/4724980/making-the-iphone-vibrate
    // should vibrate no matter it is silient or not
    if([[UIDevice currentDevice].model isEqualToString:@"iPhone"])
    {
        AudioServicesPlaySystemSound (1352); //works ALWAYS as of this post
    }
    else
    {
        // Not an iPhone, so doesn't have vibrate
        // play the less annoying tick noise or one of your own
        AudioServicesPlayAlertSound (kSystemSoundID_Vibrate);
    }
}

NS_CC_END

#endif // CC_PLATFORM_IOS
