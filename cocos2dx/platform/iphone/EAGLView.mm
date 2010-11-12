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

#import <QuartzCore/QuartzCore.h>

#import "EAGLView.h"
#import "ES1Renderer.h"
#import "CCDirector.h"
#import "NSSet.h"
#import "CCTouch.h"

#ifdef self
#undef self
#endif

//CLASS IMPLEMENTATIONS:

static EAGLView *view;

@interface EAGLView (Private)
-(BOOL) setupSurface;
@end

@implementation EAGLView

@synthesize surfaceSize=size_;
@synthesize pixelFormat=pixelformat_, depthFormat=depthFormat_;
@synthesize context=context_;

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
	return [[[self alloc] initWithFrame:frame pixelFormat:format] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained
{
	return [[[self alloc] initWithFrame:frame pixelFormat:format depthFormat:depth preserveBackbuffer:retained] autorelease];
}

+ (id) getGlobalView
{
	return view;
}

- (id) initWithFrame:(CGRect)frame
{
	return [self initWithFrame:frame pixelFormat:kEAGLColorFormatRGB565 depthFormat:0 preserveBackbuffer:NO];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format 
{
	return [self initWithFrame:frame pixelFormat:format depthFormat:0 preserveBackbuffer:NO];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained
{
	if((self = [super initWithFrame:frame]))
	{
		pixelformat_ = format;
		depthFormat_ = depth;
		size_ = frame.size;
		
		if( ! [self setupSurface] ) {
			[self release];
			return nil;
		}
	}

	view = self;
	return self;
}

-(id) initWithCoder:(NSCoder *)aDecoder
{
	if( (self = [super initWithCoder:aDecoder]) ) {
		
		CAEAGLLayer *eaglLayer = (CAEAGLLayer*)[self layer];
		
		pixelformat_ = kEAGLColorFormatRGB565;
		depthFormat_ = 0; // GL_DEPTH_COMPONENT24_OES;
		size_ = [eaglLayer bounds].size;

		if( ! [self setupSurface] ) {
			[self release];
			return nil;
		}
    }
	
    return self;
}

-(int) getWidth
{
	CGSize bound = [self bounds].size;
	return bound.width;
}

-(int) getHeight
{
	CGSize bound = [self bounds].size;
	return bound.height;
}

-(BOOL) setupSurface
{
	CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
	
	eaglLayer.opaque = YES;
	eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
									[NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
									pixelformat_, kEAGLDrawablePropertyColorFormat, nil];
	
		
	renderer_ = [[ES1Renderer alloc] initWithDepthFormat:depthFormat_];
	if (!renderer_)
		return NO;

	context_ = [renderer_ context];
	[context_ renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:eaglLayer];

	//discardFramebufferSupported_ = [[CCConfiguration sharedConfiguration] supportsDiscardFramebuffer];
	
	return YES;
}

- (void) dealloc
{
	[renderer_ release];
	[super dealloc];
}

- (void) layoutSubviews
{
    [renderer_ resizeFromLayer:(CAEAGLLayer*)self.layer];
    size_ = [renderer_ backingSize];
}

- (void) swapBuffers
{
	// IMPORTANT:
	// - preconditions
	//	-> context_ MUST be the OpenGL context
	//	-> renderBuffer_ must be the the RENDER BUFFER

#ifdef __IPHONE_4_0
	if( discardFramebufferSupported_ && depthFormat_ ) {
		GLenum attachments[] = { GL_DEPTH_ATTACHMENT_OES };
		glDiscardFramebufferEXT(GL_FRAMEBUFFER_OES, 1, attachments);
	}
#endif // __IPHONE_4_0
	
	//if(![context_ presentRenderbuffer:GL_RENDERBUFFER_OES])
		//CCLOG(@"cocos2d: Failed to swap renderbuffer in %s\n", __FUNCTION__);
	[context_ presentRenderbuffer:GL_RENDERBUFFER_OES];
#if COCOS2D_DEBUG
	CHECK_GL_ERROR();
#endif	
}

#pragma mark EAGLView - Point conversion

// Pass the touches to the superview
#pragma mark EAGLView - Touch Delegate

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	cocos2d::NSSet set;
	for (UITouch *touch in touches) {
		cocos2d::CCTouch *pCocosTouch = new cocos2d::CCTouch();
		float x = [touch locationInView: [touch view]].x;
		float y = [touch locationInView: [touch view]].y;
		pCocosTouch->SetTouchInfo(0, x, y);
		
		set.addObject(pCocosTouch);
		pCocosTouch->release();
	}
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesBegan(&set);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	cocos2d::NSSet set;
	for (UITouch *touch in touches) {
		cocos2d::CCTouch *pCocosTouch = new cocos2d::CCTouch();
		float x = [touch locationInView: [touch view]].x;
		float y = [touch locationInView: [touch view]].y;
		pCocosTouch->SetTouchInfo(0, x, y);
		
		set.addObject(pCocosTouch);
		pCocosTouch->release();
	}
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesMoved(&set);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	cocos2d::NSSet set;
	for (UITouch *touch in touches) {
		cocos2d::CCTouch *pCocosTouch = new cocos2d::CCTouch();
		float x = [touch locationInView: [touch view]].x;
		float y = [touch locationInView: [touch view]].y;
		pCocosTouch->SetTouchInfo(0, x, y);
		
		set.addObject(pCocosTouch);
		pCocosTouch->release();
	}
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesEnded(&set);
}
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	cocos2d::NSSet set;
	for (UITouch *touch in touches) {
		cocos2d::CCTouch *pCocosTouch = new cocos2d::CCTouch();
		float x = [touch locationInView: [touch view]].x;
		float y = [touch locationInView: [touch view]].y;
		pCocosTouch->SetTouchInfo(0, x, y);
		
		set.addObject(pCocosTouch);
		pCocosTouch->release();
	}
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesCancelled(&set);
}

@end
