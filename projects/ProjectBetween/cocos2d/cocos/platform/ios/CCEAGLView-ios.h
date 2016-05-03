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

File: EAGLView.h
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

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <CoreFoundation/CoreFoundation.h>

#import "platform/ios/CCESRenderer-ios.h"

//CLASS INTERFACE:

/** CCEAGLView Class.
 * This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
 * The view content is basically an EAGL surface you render your OpenGL scene into.
 * Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
 */
@interface CCEAGLView : UIView <UIKeyInput, UITextInput>
{
    id                        <CCESRenderer> renderer_;    
    EAGLContext                *context_; // weak ref

    NSString                *pixelformat_;
    GLuint                    depthFormat_;
    BOOL                    preserveBackbuffer_;

    CGSize                    size_;
    BOOL                    discardFramebufferSupported_;

    //fsaa addition
    BOOL                    multisampling_;
    unsigned int               requestedSamples_;
    BOOL                    isUseUITextField;
@private
    NSString *              markedText_;
    CGRect                  caretRect_;
    CGRect                  originalRect_;
    NSNotification*         keyboardShowNotification_;
    BOOL                    isKeyboardShown_;
}

@property(nonatomic, readonly) UITextPosition *beginningOfDocument;
@property(nonatomic, readonly) UITextPosition *endOfDocument;
@property(nonatomic, assign) id<UITextInputDelegate> inputDelegate;
@property(nonatomic, readonly) UITextRange *markedTextRange;
@property (nonatomic, copy) NSDictionary *markedTextStyle;
@property(readwrite, copy) UITextRange *selectedTextRange;
@property(nonatomic, readonly) id<UITextInputTokenizer> tokenizer;
@property(nonatomic, readonly, getter = isKeyboardShown) BOOL isKeyboardShown;
@property(nonatomic, copy) NSNotification* keyboardShowNotification;
/** creates an initializes an CCEAGLView with a frame and 0-bit depth buffer, and a RGB565 color buffer */
+ (id) viewWithFrame:(CGRect)frame;
/** creates an initializes an CCEAGLView with a frame, a color buffer format, and 0-bit depth buffer */
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format;
/** creates an initializes an CCEAGLView with a frame, a color buffer format, and a depth buffer format */
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth;
/** creates an initializes an CCEAGLView with a frame, a color buffer format, a depth buffer format, a sharegroup, and multisampling */
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)multisampling numberOfSamples:(unsigned int)samples;

/** Initializes an CCEAGLView with a frame and 0-bit depth buffer, and a RGB565 color buffer */
- (id) initWithFrame:(CGRect)frame; //These also set the current context
/** Initializes an CCEAGLView with a frame, a color buffer format, and 0-bit depth buffer */
- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format;
/** Initializes an CCEAGLView with a frame, a color buffer format, a depth buffer format, a sharegroup and multisampling support */
- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)sampling numberOfSamples:(unsigned int)nSamples;

/** pixel format: it could be RGBA8 (32-bit) or RGB565 (16-bit) */
@property(nonatomic,readonly) NSString* pixelFormat;
/** depth format of the render buffer: 0, 16 or 24 bits*/
@property(nonatomic,readonly) GLuint depthFormat;

/** returns surface size in pixels */
@property(nonatomic,readonly) CGSize surfaceSize;

/** OpenGL context */
@property(nonatomic,readonly) EAGLContext *context;

@property(nonatomic,readwrite) BOOL multiSampling;


/** CCEAGLView uses double-buffer. This method swaps the buffers */
-(void) swapBuffers;

- (CGRect) convertRectFromViewToSurface:(CGRect)rect;
- (CGPoint) convertPointFromViewToSurface:(CGPoint)point;

-(int) getWidth;
-(int) getHeight;

-(void) doAnimationWhenKeyboardMoveWithDuration:(float) duration distance:(float) dis;
-(void) doAnimationWhenAnotherEditBeClicked;
@end

#endif // CC_PLATFORM_IOS
