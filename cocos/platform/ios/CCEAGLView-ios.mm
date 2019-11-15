/*

===== IMPORTANT =====

This is sample code demonstrating API, technology or techniques in development.
Although this sample code has been reviewed for technical accuracy, it is not
final. Apple is supplying this information to help you plan for the adoption of
the technologies and programming interfaces described herein. This information
is subject to change, and software implemented based on this sample code should
be tested with final operating system software and final documentation. Newer
versions of this sample code may be provided with future seeds of the API or
technology. For information about updates to this and other developer
documentation, view the New & Updated sidebars in subsequent documentation
seeds.

=====================

File: EAGLView.m
Abstract: Convenience class that wraps the CAEAGLLayer from CoreAnimation into a
UIView subclass.

Version: 1.3

Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple Inc.
("Apple") in consideration of your agreement to the following terms, and your
use, installation, modification or redistribution of this Apple software
constitutes acceptance of these terms.  If you do not agree with these terms,
please do not use, install, modify or redistribute this Apple software.

In consideration of your agreement to abide by the following terms, and subject
to these terms, Apple grants you a personal, non-exclusive license, under
Apple's copyrights in this original Apple software (the "Apple Software"), to
use, reproduce, modify and redistribute the Apple Software, with or without
modifications, in source and/or binary forms; provided that if you redistribute
the Apple Software in its entirety and without modifications, you must retain
this notice and the following text and disclaimers in all such redistributions
of the Apple Software.
Neither the name, trademarks, service marks or logos of Apple Inc. may be used
to endorse or promote products derived from the Apple Software without specific
prior written permission from Apple.  Except as expressly stated in this notice,
no other rights or licenses, express or implied, are granted by Apple herein,
including but not limited to any patent rights that may be infringed by your
derivative works or by other works in which the Apple Software may be
incorporated.

The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
COMBINATION WITH YOUR PRODUCTS.

IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR
DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF
CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF
APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Copyright (C) 2008 Apple Inc. All Rights Reserved.

*/
#import "platform/ios/CCEAGLView-ios.h"

#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>

#import "base/CCDirector.h"
#import "base/CCTouch.h"
#import "base/CCIMEDispatcher.h"
#import "renderer/backend/metal/DeviceMTL.h"
#import "platform/ios/CCInputView-ios.h"

//CLASS IMPLEMENTATIONS:

#define IOS_MAX_TOUCHES_COUNT     10

@interface CCEAGLView ()
@property (nonatomic) CCInputView* textInputView;
@property(nonatomic, readwrite, assign) BOOL isKeyboardShown;
@property(nonatomic, copy) NSNotification* keyboardShowNotification;
@property(nonatomic, assign) CGRect originalRect;
@end

@implementation CCEAGLView

@synthesize surfaceSize=size_;
@synthesize pixelFormat=pixelformat_, depthFormat=depthFormat_;
@synthesize multiSampling=multiSampling_;
@synthesize keyboardShowNotification = keyboardShowNotification_;
@synthesize isKeyboardShown;
@synthesize originalRect = originalRect_;

+ (Class) layerClass
{
    return [CAMetalLayer class];
}

+ (id) viewWithFrame:(CGRect)frame
{
    return [[[self alloc] initWithFrame:frame] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format
{
    return [[[self alloc]initWithFrame:frame pixelFormat:format] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth
{
    return [[[self alloc] initWithFrame:frame pixelFormat:format depthFormat:depth preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)multisampling numberOfSamples:(unsigned int)samples
{
    return [[[self alloc]initWithFrame:frame pixelFormat:format depthFormat:depth preserveBackbuffer:retained sharegroup:sharegroup multiSampling:multisampling numberOfSamples:samples] autorelease];
}

- (id) initWithFrame:(CGRect)frame
{
    return [self initWithFrame:frame pixelFormat:kEAGLColorFormatRGB565 depthFormat:0 preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format 
{
    return [self initWithFrame:frame pixelFormat:format depthFormat:0 preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)sampling numberOfSamples:(unsigned int)nSamples
{
    if((self = [super initWithFrame:frame]))
    {
        self.textInputView = [[CCInputView alloc] initWithFrame:frame];

        originalRect_ = self.frame;
        self.keyboardShowNotification = nil;
        if ([self respondsToSelector:@selector(setContentScaleFactor:)])
        {
            self.contentScaleFactor = [[UIScreen mainScreen] scale];
        }

        id<MTLDevice> device = MTLCreateSystemDefaultDevice();
        if (!device)
        {
             CCLOG("Doesn't support metal.");
             return nil;
        }
        CAMetalLayer* metalLayer = (CAMetalLayer*)[self layer];
        metalLayer.device = device;
        metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        metalLayer.framebufferOnly = YES;
        cocos2d::backend::DeviceMTL::setCAMetalLayer(metalLayer);
    }
    
    return self;
}

-(id) initWithCoder:(NSCoder *)aDecoder
{
    if ( (self = [super initWithCoder:aDecoder]) )
    {
        size_ = [self bounds].size;
        self.textInputView = [[CCInputView alloc] initWithCoder:aDecoder];
    }
    
    return self;
}


-(int) getWidth
{
    CGSize bound = [self bounds].size;
    return (int)bound.width * self.contentScaleFactor;
}

-(int) getHeight
{
    CGSize bound = [self bounds].size;
    return (int)bound.height * self.contentScaleFactor;
}

- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self]; // remove keyboard notification
    [self.textInputView release];
    [super dealloc];
}

- (void) layoutSubviews
{
    if (!cocos2d::Director::getInstance()->isValid())
        return;

    size_ = [self bounds].size;
    size_.width *= self.contentScaleFactor;
    size_.height *= self.contentScaleFactor;

    // Avoid flicker. Issue #350
    if ([NSThread isMainThread])
    {
        cocos2d::Director::getInstance()->drawScene();
    }
}

- (void) swapBuffers
{
}

#pragma mark CCEAGLView - Point conversion

- (CGPoint) convertPointFromViewToSurface:(CGPoint)point
{
    CGRect bounds = [self bounds];
    
    CGPoint ret;
    ret.x = (point.x - bounds.origin.x) / bounds.size.width * size_.width;
    ret.y =  (point.y - bounds.origin.y) / bounds.size.height * size_.height;
    
    return ret;
}

- (CGRect) convertRectFromViewToSurface:(CGRect)rect
{
    CGRect bounds = [self bounds];
    
    CGRect ret;
    ret.origin.x = (rect.origin.x - bounds.origin.x) / bounds.size.width * size_.width;
    ret.origin.y = (rect.origin.y - bounds.origin.y) / bounds.size.height * size_.height;
    ret.size.width = rect.size.width / bounds.size.width * size_.width;
    ret.size.height = rect.size.height / bounds.size.height * size_.height;
    
    return ret;
}

// Pass the touches to the superview
#pragma mark CCEAGLView - Touch Delegate
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.isKeyboardShown)
        [self closeKeyboardOpenedByEditBox];
    
    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= IOS_MAX_TOUCHES_COUNT) {
            CCLOG("warning: touches more than 10, should adjust IOS_MAX_TOUCHES_COUNT");
            break;
        }

        ids[i] = touch;
        xs[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;
        ys[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;
        ++i;
    }

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    glview->handleTouchesBegin(i, (intptr_t*)ids, xs, ys);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    float fs[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    float ms[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= IOS_MAX_TOUCHES_COUNT) {
            CCLOG("warning: touches more than 10, should adjust IOS_MAX_TOUCHES_COUNT");
            break;
        }

        ids[i] = touch;
        xs[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;
        ys[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;
#if defined(__IPHONE_9_0) && (__IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_9_0)
        // running on iOS 9.0 or higher version
        if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0f) {
            fs[i] = touch.force;
            ms[i] = touch.maximumPossibleForce;
        }
#endif
        ++i;
    }

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    glview->handleTouchesMove(i, (intptr_t*)ids, xs, ys, fs, ms);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= IOS_MAX_TOUCHES_COUNT) {
            CCLOG("warning: touches more than 10, should adjust IOS_MAX_TOUCHES_COUNT");
            break;
        }

        ids[i] = touch;
        xs[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;
        ys[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;
        ++i;
    }

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    glview->handleTouchesEnd(i, (intptr_t*)ids, xs, ys);
}
    
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= IOS_MAX_TOUCHES_COUNT) {
            CCLOG("warning: touches more than 10, should adjust IOS_MAX_TOUCHES_COUNT");
            break;
        }
        
        ids[i] = touch;
        xs[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;
        ys[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;
        ++i;
    }

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    glview->handleTouchesCancel(i, (intptr_t*)ids, xs, ys);
}

- (void) showKeyboard
{
    [self addSubview:self.textInputView];
    [self.textInputView becomeFirstResponder];
}

- (void) hideKeyboard
{
    [self.textInputView resignFirstResponder];
    [self.textInputView removeFromSuperview];
}

-(void) doAnimationWhenKeyboardMoveWithDuration:(float) duration distance:(float) dis
{
    [UIView beginAnimations:nil context:nullptr];
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDuration:duration];
        [UIView setAnimationBeginsFromCurrentState:YES];
        
        //NSLog(@"[animation] dis = %f, scale = %f \n", dis, cocos2d::GLView::getInstance()->getScaleY());
        
        if (dis < 0.0f) dis = 0.0f;

        auto glview = cocos2d::Director::getInstance()->getOpenGLView();
        dis *= glview->getScaleY();
        
        dis /= self.contentScaleFactor;

    #if defined(CC_TARGET_OS_TVOS)
        self.frame = CGRectMake(originalRect_.origin.x, originalRect_.origin.y - dis, originalRect_.size.width, originalRect_.size.height);
    #else
        switch (getFixedOrientation([[UIApplication sharedApplication] statusBarOrientation]))
        {
            case UIInterfaceOrientationPortrait:
                self.frame = CGRectMake(originalRect_.origin.x, originalRect_.origin.y - dis, originalRect_.size.width, originalRect_.size.height);
                break;
                
            case UIInterfaceOrientationPortraitUpsideDown:
                self.frame = CGRectMake(originalRect_.origin.x, originalRect_.origin.y + dis, originalRect_.size.width, originalRect_.size.height);
                break;
                
            case UIInterfaceOrientationLandscapeLeft:
                self.frame = CGRectMake(originalRect_.origin.x - dis, originalRect_.origin.y , originalRect_.size.width, originalRect_.size.height);
                break;
                
            case UIInterfaceOrientationLandscapeRight:
                self.frame = CGRectMake(originalRect_.origin.x + dis, originalRect_.origin.y , originalRect_.size.width, originalRect_.size.height);
                break;
                
            default:
                break;
        }
    #endif
        
        [UIView commitAnimations];
}

-(void) doAnimationWhenAnotherEditBeClicked
{
    if (self.keyboardShowNotification != nil)
    {
        [[NSNotificationCenter defaultCenter]postNotification:self.keyboardShowNotification];
    }
}

#pragma UIKeyboard notification

#if !defined(CC_TARGET_OS_TVOS)
namespace {
    UIInterfaceOrientation getFixedOrientation(UIInterfaceOrientation statusBarOrientation)
    {
        if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
        {
            statusBarOrientation = UIInterfaceOrientationPortrait;
        }
        return statusBarOrientation;
    }
}
#endif

- (void)didMoveToWindow
{
#if !defined(CC_TARGET_OS_TVOS)
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardWillShowNotification object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardWillHideNotification object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUIKeyboardNotification:)
                                                 name:UIKeyboardDidHideNotification object:nil];
#endif
}

- (void)onUIKeyboardNotification:(NSNotification *)notif
{
    NSString * type = notif.name;
    
    NSDictionary* info = [notif userInfo];
    CGRect begin = [self convertRect:
                    [[info objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue]
                            fromView:self];
    CGRect end = [self convertRect:
                  [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue]
                          fromView:self];
    double aniDuration = [[info objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    
    CGSize viewSize = self.frame.size;

    CGFloat tmp;
    switch (getFixedOrientation([[UIApplication sharedApplication] statusBarOrientation]))
    {
        case UIInterfaceOrientationPortrait:
            begin.origin.y = viewSize.height - begin.origin.y - begin.size.height;
            end.origin.y = viewSize.height - end.origin.y - end.size.height;
            break;
            
        case UIInterfaceOrientationPortraitUpsideDown:
            begin.origin.x = viewSize.width - (begin.origin.x + begin.size.width);
            end.origin.x = viewSize.width - (end.origin.x + end.size.width);
            break;
            
        case UIInterfaceOrientationLandscapeLeft:
            std::swap(begin.size.width, begin.size.height);
            std::swap(end.size.width, end.size.height);
            std::swap(viewSize.width, viewSize.height);
            
            tmp = begin.origin.x;
            begin.origin.x = begin.origin.y;
            begin.origin.y = viewSize.height - tmp - begin.size.height;
            tmp = end.origin.x;
            end.origin.x = end.origin.y;
            end.origin.y = viewSize.height - tmp - end.size.height;
            break;
            
        case UIInterfaceOrientationLandscapeRight:
            std::swap(begin.size.width, begin.size.height);
            std::swap(end.size.width, end.size.height);
            std::swap(viewSize.width, viewSize.height);
            
            tmp = begin.origin.x;
            begin.origin.x = begin.origin.y;
            begin.origin.y = tmp;
            tmp = end.origin.x;
            end.origin.x = end.origin.y;
            end.origin.y = tmp;
            break;
            
        default:
            break;
    }

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float scaleX = glview->getScaleX();
    float scaleY = glview->getScaleY();
    
    // Convert to pixel coordinate
    begin = CGRectApplyAffineTransform(begin, CGAffineTransformScale(CGAffineTransformIdentity, self.contentScaleFactor, self.contentScaleFactor));
    end = CGRectApplyAffineTransform(end, CGAffineTransformScale(CGAffineTransformIdentity, self.contentScaleFactor, self.contentScaleFactor));
    
    float offestY = glview->getViewPortRect().origin.y;
    if (offestY < 0.0f)
    {
        begin.origin.y += offestY;
        begin.size.height -= offestY;
        end.size.height -= offestY;
    }
    
    // Convert to design coordinate
    begin = CGRectApplyAffineTransform(begin, CGAffineTransformScale(CGAffineTransformIdentity, 1.0f/scaleX, 1.0f/scaleY));
    end = CGRectApplyAffineTransform(end, CGAffineTransformScale(CGAffineTransformIdentity, 1.0f/scaleX, 1.0f/scaleY));

    
    cocos2d::IMEKeyboardNotificationInfo notiInfo;
    notiInfo.begin = cocos2d::Rect(begin.origin.x,
                                     begin.origin.y,
                                     begin.size.width,
                                     begin.size.height);
    notiInfo.end = cocos2d::Rect(end.origin.x,
                                   end.origin.y,
                                   end.size.width,
                                   end.size.height);
    notiInfo.duration = (float)aniDuration;
    
    cocos2d::IMEDispatcher* dispatcher = cocos2d::IMEDispatcher::sharedDispatcher();
    if (UIKeyboardWillShowNotification == type)
    {
        dispatcher->dispatchKeyboardWillShow(notiInfo);
    }
    else if (UIKeyboardDidShowNotification == type)
    {
        self.isKeyboardShown = YES;
        dispatcher->dispatchKeyboardDidShow(notiInfo);
    }
    else if (UIKeyboardWillHideNotification == type)
    {
        dispatcher->dispatchKeyboardWillHide(notiInfo);
    }
    else if (UIKeyboardDidHideNotification == type)
    {
        self.isKeyboardShown = NO;
        dispatcher->dispatchKeyboardDidHide(notiInfo);
    }
}

// Close the keyboard opened by EditBox
-(void) closeKeyboardOpenedByEditBox
{
    NSArray *subviews = self.subviews;
    
    for(UIView* view in subviews)
    {
        if([view isKindOfClass:NSClassFromString(@"UITextView")] ||
           [view isKindOfClass:NSClassFromString(@"UITextField")])
        {
            if ([view isFirstResponder])
            {
                [view resignFirstResponder];
                return;
            }
        }
    }
}

@end
