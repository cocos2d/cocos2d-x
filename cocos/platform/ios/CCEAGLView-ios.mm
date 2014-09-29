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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import "CCEAGLView-ios.h"

#import <QuartzCore/QuartzCore.h>

#import "base/CCDirector.h"
#import "deprecated/CCSet.h"
#import "base/CCTouch.h"
#import "base/CCIMEDispatcher.h"
#import "CCGLViewImpl-ios.h"
#import "CCES2Renderer-ios.h"
#import "OpenGL_Internal-ios.h"

//CLASS IMPLEMENTATIONS:

#define IOS_MAX_TOUCHES_COUNT     10

@interface CCEAGLView (Private)
- (BOOL) setupSurfaceWithSharegroup:(EAGLSharegroup*)sharegroup;
- (unsigned int) convertPixelFormat:(NSString*) pixelFormat;
@end

@implementation CCEAGLView

@synthesize surfaceSize=size_;
@synthesize pixelFormat=pixelformat_, depthFormat=depthFormat_;
@synthesize context=context_;
@synthesize multiSampling=multiSampling_;
@synthesize isKeyboardShown=isKeyboardShown_;
@synthesize keyboardShowNotification = keyboardShowNotification_;
+ (Class) layerClass
{
    return [CAEAGLLayer class];
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

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)sampling numberOfSamples:(unsigned int)nSamples;
{
    if((self = [super initWithFrame:frame]))
    {
        isUseUITextField = YES;
        pixelformat_ = format;
        depthFormat_ = depth;
        multiSampling_ = sampling;
        requestedSamples_ = nSamples;
        preserveBackbuffer_ = retained;
        markedText_ = nil;
        if( ! [self setupSurfaceWithSharegroup:sharegroup] ) {
            [self release];
            return nil;
        }


        originalRect_ = self.frame;
        self.keyboardShowNotification = nil;
		
		if ([self respondsToSelector:@selector(setContentScaleFactor:)])
		{
			self.contentScaleFactor = [[UIScreen mainScreen] scale];
		}
    }
        
    return self;
}

-(id) initWithCoder:(NSCoder *)aDecoder
{
    if( (self = [super initWithCoder:aDecoder]) ) {
        
        CAEAGLLayer*            eaglLayer = (CAEAGLLayer*)[self layer];
        
        pixelformat_ = kEAGLColorFormatRGB565;
        depthFormat_ = 0; // GL_DEPTH_COMPONENT24_OES;
        multiSampling_= NO;
        requestedSamples_ = 0;
        size_ = [eaglLayer bounds].size;
        markedText_ = nil;
        
        if( ! [self setupSurfaceWithSharegroup:nil] ) {
            [self release];
            return nil;
        }
    }
    
    return self;
}

- (void)didMoveToWindow;
{
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


-(BOOL) setupSurfaceWithSharegroup:(EAGLSharegroup*)sharegroup
{
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
    
    eaglLayer.opaque = YES;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    [NSNumber numberWithBool:preserveBackbuffer_], kEAGLDrawablePropertyRetainedBacking,
                                    pixelformat_, kEAGLDrawablePropertyColorFormat, nil];
    
    
    renderer_ = [[CCES2Renderer alloc] initWithDepthFormat:depthFormat_
                                         withPixelFormat:[self convertPixelFormat:pixelformat_]
                                          withSharegroup:sharegroup
                                       withMultiSampling:multiSampling_
                                     withNumberOfSamples:requestedSamples_];
    
    NSAssert(renderer_, @"OpenGL ES 2.O is required.");
    if (!renderer_)
        return NO;
    
    context_ = [renderer_ context];
    
    #if GL_EXT_discard_framebuffer == 1
        discardFramebufferSupported_ = YES;
    #else
        discardFramebufferSupported_ = NO;
    #endif
    
    CHECK_GL_ERROR();
    
    return YES;
}

- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self]; // remove keyboard notification
    [renderer_ release];
    self.keyboardShowNotification = nullptr; // implicit release
    [super dealloc];
}

- (void) layoutSubviews
{
    [renderer_ resizeFromLayer:(CAEAGLLayer*)self.layer];
    size_ = [renderer_ backingSize];

    // Issue #914 #924
//     Director *director = [Director sharedDirector];
//     [director reshapeProjection:size_];
    cocos2d::Size size;
    size.width = size_.width;
    size.height = size_.height;
    //cocos2d::Director::getInstance()->reshapeProjection(size);

    // Avoid flicker. Issue #350
    //[director performSelectorOnMainThread:@selector(drawScene) withObject:nil waitUntilDone:YES];
    cocos2d::Director::getInstance()->drawScene();
}

- (void) swapBuffers
{
    // IMPORTANT:
    // - preconditions
    //    -> context_ MUST be the OpenGL context
    //    -> renderbuffer_ must be the the RENDER BUFFER

#ifdef __IPHONE_4_0
    
    if (multiSampling_)
    {
        /* Resolve from msaaFramebuffer to resolveFramebuffer */
        //glDisable(GL_SCISSOR_TEST);     
        glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, [renderer_ msaaFrameBuffer]);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, [renderer_ defaultFrameBuffer]);
        glResolveMultisampleFramebufferAPPLE();
    }
    
    if(discardFramebufferSupported_)
    {    
        if (multiSampling_)
        {
            if (depthFormat_)
            {
                GLenum attachments[] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
                glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, attachments);
            }
            else
            {
                GLenum attachments[] = {GL_COLOR_ATTACHMENT0};
                glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 1, attachments);
            }
            
            glBindRenderbuffer(GL_RENDERBUFFER, [renderer_ colorRenderBuffer]);
    
        }    
        
        // not MSAA
        else if (depthFormat_ ) {
            GLenum attachments[] = { GL_DEPTH_ATTACHMENT};
            glDiscardFramebufferEXT(GL_FRAMEBUFFER, 1, attachments);
        }
    }
    
#endif // __IPHONE_4_0
    
     if(![context_ presentRenderbuffer:GL_RENDERBUFFER])
        {
//         CCLOG(@"cocos2d: Failed to swap renderbuffer in %s\n", __FUNCTION__);
        }

#if COCOS2D_DEBUG
    CHECK_GL_ERROR();
#endif
    
    // We can safely re-bind the framebuffer here, since this will be the
    // 1st instruction of the new main loop
    if( multiSampling_ )
        glBindFramebuffer(GL_FRAMEBUFFER, [renderer_ msaaFrameBuffer]);    
}

- (unsigned int) convertPixelFormat:(NSString*) pixelFormat
{
    // define the pixel format
    GLenum pFormat;
    
    
    if([pixelFormat isEqualToString:@"EAGLColorFormat565"]) 
        pFormat = GL_RGB565;
    else 
        pFormat = GL_RGBA8_OES;
    
    return pFormat;
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


-(void) handleTouchesAfterKeyboardShow
{
    NSArray *subviews = self.subviews;
    
    for(UIView* view in subviews)
    {
        if([view isKindOfClass:NSClassFromString(@"CCCustomUITextField")] ||
           [view isKindOfClass:NSClassFromString(@"UICustomUITextField")])
        {
            if ([view isFirstResponder])
            {
                [view resignFirstResponder];
                return;
            }
        }
    }
}

// Pass the touches to the superview
#pragma mark CCEAGLView - Touch Delegate
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (isKeyboardShown_)
    {
        [self handleTouchesAfterKeyboardShow];
    }
    
    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        ids[i] = touch;
        xs[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;;
        ys[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;;
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
    
    int i = 0;
    for (UITouch *touch in touches) {
        ids[i] = touch;
        xs[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;;
        ys[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;;
        ++i;
    }

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    glview->handleTouchesMove(i, (intptr_t*)ids, xs, ys);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch* ids[IOS_MAX_TOUCHES_COUNT] = {0};
    float xs[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    float ys[IOS_MAX_TOUCHES_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        ids[i] = touch;
        xs[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;;
        ys[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;;
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
        ids[i] = touch;
        xs[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;;
        ys[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;;
        ++i;
    }

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    glview->handleTouchesCancel(i, (intptr_t*)ids, xs, ys);
}

#pragma mark - UIView - Responder

- (BOOL)canBecomeFirstResponder
{
    if (nil != markedText_) {
        [markedText_ release];
    }
    markedText_ = nil;
    if (isUseUITextField)
    {
        return NO;
    }
    return YES;
}

- (BOOL)becomeFirstResponder
{
    isUseUITextField = NO;
    return [super becomeFirstResponder];
}

- (BOOL)resignFirstResponder
{
    isUseUITextField = YES;
    return [super resignFirstResponder];
}

#pragma mark - UIKeyInput protocol


- (BOOL)hasText
{
    return NO;
}

- (void)insertText:(NSString *)text
{
    if (nil != markedText_) {
        [markedText_ release];
        markedText_ = nil;
    }
    const char * pszText = [text cStringUsingEncoding:NSUTF8StringEncoding];
    cocos2d::IMEDispatcher::sharedDispatcher()->dispatchInsertText(pszText, strlen(pszText));
}

- (void)deleteBackward
{
    if (nil != markedText_) {
        [markedText_ release];
        markedText_ = nil;
    }
    cocos2d::IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
}

#pragma mark - UITextInputTrait protocol

-(UITextAutocapitalizationType) autocapitalizationType
{
    return UITextAutocapitalizationTypeNone;
}

#pragma mark - UITextInput protocol

#pragma mark UITextInput - properties

@synthesize beginningOfDocument;
@synthesize endOfDocument;
@synthesize inputDelegate;
@synthesize markedTextRange;
@synthesize markedTextStyle;
// @synthesize selectedTextRange;       // must implement
@synthesize tokenizer;

/* Text may have a selection, either zero-length (a caret) or ranged.  Editing operations are
 * always performed on the text from this selection.  nil corresponds to no selection. */
- (void)setSelectedTextRange:(UITextRange *)aSelectedTextRange;
{
    CCLOG("UITextRange:setSelectedTextRange");
}
- (UITextRange *)selectedTextRange;
{
    return [[[UITextRange alloc] init] autorelease];
}

#pragma mark UITextInput - Replacing and Returning Text

- (NSString *)textInRange:(UITextRange *)range;
{
    CCLOG("textInRange");
    return @"";
}
- (void)replaceRange:(UITextRange *)range withText:(NSString *)theText;
{
    CCLOG("replaceRange");
}

#pragma mark UITextInput - Working with Marked and Selected Text



/* If text can be selected, it can be marked. Marked text represents provisionally
 * inserted text that has yet to be confirmed by the user.  It requires unique visual
 * treatment in its display.  If there is any marked text, the selection, whether a
 * caret or an extended range, always resides within.
 *
 * Setting marked text either replaces the existing marked text or, if none is present,
 * inserts it from the current selection. */ 

- (void)setMarkedTextRange:(UITextRange *)markedTextRange;
{
    CCLOG("setMarkedTextRange");
}

- (UITextRange *)markedTextRange;
{
    CCLOG("markedTextRange");
    return nil; // Nil if no marked text.
}
- (void)setMarkedTextStyle:(NSDictionary *)markedTextStyle;
{
    CCLOG("setMarkedTextStyle");
    
}
- (NSDictionary *)markedTextStyle;
{
    CCLOG("markedTextStyle");
    return nil;
}
- (void)setMarkedText:(NSString *)markedText selectedRange:(NSRange)selectedRange;
{
    CCLOG("setMarkedText");
    if (markedText == markedText_) {
        return;
    }
    if (nil != markedText_) {
        [markedText_ release];
    }
    markedText_ = markedText;
    [markedText_ retain];
}
- (void)unmarkText;
{
    CCLOG("unmarkText");
    if (nil == markedText_)
    {
        return;
    }
    const char * pszText = [markedText_ cStringUsingEncoding:NSUTF8StringEncoding];
    cocos2d::IMEDispatcher::sharedDispatcher()->dispatchInsertText(pszText, strlen(pszText));
    [markedText_ release];
    markedText_ = nil;
}

#pragma mark Methods for creating ranges and positions.

- (UITextRange *)textRangeFromPosition:(UITextPosition *)fromPosition toPosition:(UITextPosition *)toPosition;
{
    CCLOG("textRangeFromPosition");
    return nil;
}
- (UITextPosition *)positionFromPosition:(UITextPosition *)position offset:(NSInteger)offset;
{
    CCLOG("positionFromPosition");
    return nil;
}
- (UITextPosition *)positionFromPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction offset:(NSInteger)offset;
{
    CCLOG("positionFromPosition");
    return nil;
}

/* Simple evaluation of positions */
- (NSComparisonResult)comparePosition:(UITextPosition *)position toPosition:(UITextPosition *)other;
{
    CCLOG("comparePosition");
    return (NSComparisonResult)0;
}
- (NSInteger)offsetFromPosition:(UITextPosition *)from toPosition:(UITextPosition *)toPosition;
{
    CCLOG("offsetFromPosition");
    return 0;
}

- (UITextPosition *)positionWithinRange:(UITextRange *)range farthestInDirection:(UITextLayoutDirection)direction;
{
    CCLOG("positionWithinRange");
    return nil;
}
- (UITextRange *)characterRangeByExtendingPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction;
{
    CCLOG("characterRangeByExtendingPosition");
    return nil;
}

#pragma mark Writing direction

- (UITextWritingDirection)baseWritingDirectionForPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction;
{
    CCLOG("baseWritingDirectionForPosition");
    return UITextWritingDirectionNatural;
}
- (void)setBaseWritingDirection:(UITextWritingDirection)writingDirection forRange:(UITextRange *)range;
{
    CCLOG("setBaseWritingDirection");
}

#pragma mark Geometry

/* Geometry used to provide, for example, a correction rect. */
- (CGRect)firstRectForRange:(UITextRange *)range;
{
    CCLOG("firstRectForRange");
    return CGRectNull;
}
- (CGRect)caretRectForPosition:(UITextPosition *)position;
{
    CCLOG("caretRectForPosition");
    return caretRect_;
}

#pragma mark Hit testing

/* JS - Find the closest position to a given point */
- (UITextPosition *)closestPositionToPoint:(CGPoint)point;
{
    CCLOG("closestPositionToPoint");
    return nil;
}
- (UITextPosition *)closestPositionToPoint:(CGPoint)point withinRange:(UITextRange *)range;
{
    CCLOG("closestPositionToPoint");
    return nil;
}
- (UITextRange *)characterRangeAtPoint:(CGPoint)point;
{
    CCLOG("characterRangeAtPoint");
    return nil;
}

- (NSArray *)selectionRectsForRange:(UITextRange *)range
{
    CCLOG("selectionRectsForRange");
    return nil;
}

#pragma mark - UIKeyboard notification

- (void)onUIKeyboardNotification:(NSNotification *)notif;
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
    
    
    if (self.contentScaleFactor == 2.0f)
    {
        // Convert to pixel coordinate
        
        begin = CGRectApplyAffineTransform(begin, CGAffineTransformScale(CGAffineTransformIdentity, 2.0f, 2.0f));
        end = CGRectApplyAffineTransform(end, CGAffineTransformScale(CGAffineTransformIdentity, 2.0f, 2.0f));
    }
    
    float offestY = glview->getViewPortRect().origin.y;
    CCLOG("offestY = %f", offestY);
    if (offestY < 0.0f)
    {
        begin.origin.y += offestY;
        begin.size.height -= offestY;
        end.size.height -= offestY;
    }
    
    // Convert to desigin coordinate
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
        self.keyboardShowNotification = notif; // implicit copy
        dispatcher->dispatchKeyboardWillShow(notiInfo);
    }
    else if (UIKeyboardDidShowNotification == type)
    {
        //CGSize screenSize = self.window.screen.bounds.size;
        dispatcher->dispatchKeyboardDidShow(notiInfo);
        caretRect_ = end;
        caretRect_.origin.y = viewSize.height - (caretRect_.origin.y + caretRect_.size.height + [UIFont smallSystemFontSize]);
        caretRect_.size.height = 0;
        isKeyboardShown_ = YES;
    }
    else if (UIKeyboardWillHideNotification == type)
    {
        dispatcher->dispatchKeyboardWillHide(notiInfo);
    }
    else if (UIKeyboardDidHideNotification == type)
    {
        caretRect_ = CGRectZero;
        dispatcher->dispatchKeyboardDidHide(notiInfo);
        isKeyboardShown_ = NO;
    }
}

UIInterfaceOrientation getFixedOrientation(UIInterfaceOrientation statusBarOrientation)
{
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
    {
        statusBarOrientation = UIInterfaceOrientationPortrait;
    }
    return statusBarOrientation;
}

-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)dis
{
    [UIView beginAnimations:nil context:nullptr];
	[UIView setAnimationDelegate:self];
	[UIView setAnimationDuration:duration];
	[UIView setAnimationBeginsFromCurrentState:YES];
    
    //NSLog(@"[animation] dis = %f, scale = %f \n", dis, cocos2d::GLView::getInstance()->getScaleY());
    
    if (dis < 0.0f) dis = 0.0f;

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
	dis *= glview->getScaleY();
    
    if (self.contentScaleFactor == 2.0f)
    {
        dis /= 2.0f;
    }
    
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
    
	[UIView commitAnimations];
}


-(void) doAnimationWhenAnotherEditBeClicked
{
    if (self.keyboardShowNotification != nil)
    {
        [[NSNotificationCenter defaultCenter]postNotification:self.keyboardShowNotification];
    }
}

@end

#endif // CC_PLATFORM_IOS
