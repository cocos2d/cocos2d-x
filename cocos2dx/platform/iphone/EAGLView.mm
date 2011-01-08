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

//CLASS IMPLEMENTATIONS:

#define MAX_TOUCHES     11

static EAGLView *view;
static cocos2d::CCTouch *s_pTouches[MAX_TOUCHES];

@interface EAGLView (Private)
- (BOOL) setupSurfaceWithSharegroup:(EAGLSharegroup*)sharegroup;
- (unsigned int) convertPixelFormat:(NSString*) pixelFormat;
@end

@implementation EAGLView

@synthesize surfaceSize=size_;
@synthesize pixelFormat=pixelformat_, depthFormat=depthFormat_;
@synthesize context=context_;
@synthesize touchesIntergerDict;
@synthesize indexBitsUsed;
@synthesize multiSampling=multiSampling_;

+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

+ (id) viewWithFrame:(CGRect)frame
{
	return [[[[self alloc] init] initWithFrame:frame] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format
{
	return [[[[self alloc] init] initWithFrame:frame pixelFormat:format] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth
{
	return [[[[self alloc] init] initWithFrame:frame pixelFormat:format depthFormat:depth preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)multisampling numberOfSamples:(unsigned int)samples
{
	return [[[[self alloc] init] initWithFrame:frame pixelFormat:format depthFormat:depth preserveBackbuffer:retained sharegroup:sharegroup multiSampling:multisampling numberOfSamples:samples] autorelease];
}

+ (id) sharedEGLView
{
	return view;
}

- (id) init
{
    touchesIntergerDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 4, NULL, NULL);
    indexBitsUsed = 0x00000000;
    return self;
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
		pixelformat_ = format;
		depthFormat_ = depth;
		multiSampling_ = sampling;
		requestedSamples_ = nSamples;
		preserveBackbuffer_ = retained;
		
		if( ! [self setupSurfaceWithSharegroup:sharegroup] ) {
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
		
		CAEAGLLayer*			eaglLayer = (CAEAGLLayer*)[self layer];
		
		pixelformat_ = kEAGLColorFormatRGB565;
		depthFormat_ = 0; // GL_DEPTH_COMPONENT24_OES;
		multiSampling_= NO;
		requestedSamples_ = 0;
		size_ = [eaglLayer bounds].size;

		if( ! [self setupSurfaceWithSharegroup:nil] ) {
			[self release];
			return nil;
		}
    }
	
	view = self;
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

-(int) getUnUsedIndex
{
    int i;
    int temp = indexBitsUsed;
    
    for (i = 0; i < MAX_TOUCHES; i++) {
        if (! (temp & 0x00000001)) {
            indexBitsUsed |= (1 <<  i);
            return i;
        }
        
        temp >>= 1;
    }
    
    // all bits are used
    return -1;
}

-(void) removeUsedIndexBit:(int) index
{
   if (index < 0 || index >= MAX_TOUCHES) {
       return;
   }
    
    unsigned int temp = 1 << index;
    temp = ~temp;
    indexBitsUsed &= temp;
}

-(BOOL) setupSurfaceWithSharegroup:(EAGLSharegroup*)sharegroup
{
	CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
	
	eaglLayer.opaque = YES;
	eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
									[NSNumber numberWithBool:preserveBackbuffer_], kEAGLDrawablePropertyRetainedBacking,
									pixelformat_, kEAGLDrawablePropertyColorFormat, nil];
	
	
	renderer_ = [[ES1Renderer alloc] initWithDepthFormat:depthFormat_
										 withPixelFormat:[self convertPixelFormat:pixelformat_]
										  withSharegroup:sharegroup
									   withMultiSampling:multiSampling_
									 withNumberOfSamples:requestedSamples_];
	if (!renderer_)
		return NO;
	
	context_ = [renderer_ context];
	[context_ renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:eaglLayer];

	//discardFramebufferSupported_ = [[CCConfiguration sharedConfiguration] supportsDiscardFramebuffer];
	
	return YES;
}

- (void) dealloc
{
    CFRelease(touchesIntergerDict);
	[renderer_ release];
	[super dealloc];
}

- (void) layoutSubviews
{
    [renderer_ resizeFromLayer:(CAEAGLLayer*)self.layer];
	size_ = [renderer_ backingSize];

	// Issue #914 #924
// 	CCDirector *director = [CCDirector sharedDirector];
// 	[director reshapeProjection:size_];
    cocos2d::CGSize size;
    size.width = size_.width;
    size.height = size_.height;
    cocos2d::CCDirector::sharedDirector()->reshapeProjection(size);

	// Avoid flicker. Issue #350
	//[director performSelectorOnMainThread:@selector(drawScene) withObject:nil waitUntilDone:YES];
	cocos2d::CCDirector::sharedDirector()->drawScene();
}

- (void) swapBuffers
{
	// IMPORTANT:
	// - preconditions
	//	-> context_ MUST be the OpenGL context
	//	-> renderbuffer_ must be the the RENDER BUFFER

#ifdef __IPHONE_4_0
	
	if (multiSampling_)
	{
		/* Resolve from msaaFramebuffer to resolveFramebuffer */
		//glDisable(GL_SCISSOR_TEST);     
		glBindFramebufferOES(GL_READ_FRAMEBUFFER_APPLE, [renderer_ msaaFrameBuffer]);
		glBindFramebufferOES(GL_DRAW_FRAMEBUFFER_APPLE, [renderer_ defaultFrameBuffer]);
		glResolveMultisampleFramebufferAPPLE();
	}
	
	if( discardFramebufferSupported_)
	{	
		if (multiSampling_)
		{
			if (depthFormat_)
			{
				GLenum attachments[] = {GL_COLOR_ATTACHMENT0_OES, GL_DEPTH_ATTACHMENT_OES};
				glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, attachments);
			}
			else
			{
				GLenum attachments[] = {GL_COLOR_ATTACHMENT0_OES};
				glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 1, attachments);
			}
			
			glBindRenderbufferOES(GL_RENDERBUFFER_OES, [renderer_ colorRenderBuffer]);
	
		}	
		
		// not MSAA
		else if (depthFormat_ ) {
			GLenum attachments[] = { GL_DEPTH_ATTACHMENT_OES};
			glDiscardFramebufferEXT(GL_FRAMEBUFFER_OES, 1, attachments);
		}
	}
	
#endif // __IPHONE_4_0
	
 	if(![context_ presentRenderbuffer:GL_RENDERBUFFER_OES])
        {
// 		CCLOG(@"cocos2d: Failed to swap renderbuffer in %s\n", __FUNCTION__);
        }

#if COCOS2D_DEBUG
	CHECK_GL_ERROR();
#endif
	
	// We can safely re-bind the framebuffer here, since this will be the
	// 1st instruction of the new main loop
	if( multiSampling_ )
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, [renderer_ msaaFrameBuffer]);	
}

- (unsigned int) convertPixelFormat:(NSString*) pixelFormat
{
	// define the pixel format
	GLenum pFormat;
	
	
	if([pixelFormat isEqualToString:@"EAGLColorFormat565"]) 
		pFormat = GL_RGB565_OES;
	else 
		pFormat = GL_RGBA8_OES;
	
	return pFormat;
}

#pragma mark EAGLView - Point conversion

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
#pragma mark EAGLView - Touch Delegate

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	cocos2d::NSSet set;
        cocos2d::CCTouch *pTouch;
    
	for (UITouch *touch in touches) {
                NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, touch);
                int unUsedIndex = 0;
        
                // it is a new touch
                if (! index) {
                    unUsedIndex = [self getUnUsedIndex];
                    
                    // The touches is more than MAX_TOUCHES ?
                    if (unUsedIndex == -1) {
                        return;
                    }
                    
                    pTouch = s_pTouches[unUsedIndex] = new cocos2d::CCTouch();
                }

		float x = [touch locationInView: [touch view]].x;
		float y = [touch locationInView: [touch view]].y;
		pTouch->SetTouchInfo(0, x, y);
        
                CFDictionaryAddValue(touchesIntergerDict, touch, [NSNumber numberWithInt:unUsedIndex]);
		
		set.addObject(pTouch);
	}
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesBegan(&set);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	cocos2d::NSSet set;
	for (UITouch *touch in touches) {
		NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, touch);
                if (! index) {
                    // if the index doesn't exist, it is an error
                    return;
                }
                
                cocos2d::CCTouch *pTouch = s_pTouches[[index intValue]];
                if (! pTouch) {
                    // if the pTouch is null, it is an error
                    return;
                }
        
		float x = [touch locationInView: [touch view]].x;
		float y = [touch locationInView: [touch view]].y;
		pTouch->SetTouchInfo(0, x, y);
		
		set.addObject(pTouch);
	}
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesMoved(&set);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	cocos2d::NSSet set;
	for (UITouch *touch in touches) {
            NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, touch);
            if (! index) {
                // if the index doesn't exist, it is an error
                return;
            }
        
                cocos2d::CCTouch *pTouch = s_pTouches[[index intValue]];
                if (! pTouch) {
                    // if the pTouch is null, it is an error
                    return;
                }
        
		float x = [touch locationInView: [touch view]].x;
		float y = [touch locationInView: [touch view]].y;
		pTouch->SetTouchInfo(0, x, y);
		
		set.addObject(pTouch);
                CFDictionaryRemoveValue(touchesIntergerDict, touch);
                pTouch->release();
                s_pTouches[[index intValue]] = NULL;
                [self removeUsedIndexBit:[index intValue]];
	}
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesEnded(&set);
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	cocos2d::NSSet set;
	for (UITouch *touch in touches) {
            NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, touch);
            if (! index) {
                // if the index doesn't exist, it is an error
                return;
            }
        
                cocos2d::CCTouch *pTouch = s_pTouches[[index intValue]];
                if (! pTouch) {
                    // if the pTouch is null, it is an error
                    return;
                }
        
		float x = [touch locationInView: [touch view]].x;
		float y = [touch locationInView: [touch view]].y;
		pTouch->SetTouchInfo(0, x, y);
		
		set.addObject(pTouch);
                CFDictionaryRemoveValue(touchesIntergerDict, touch);
                pTouch->release();
                s_pTouches[[index intValue]] = NULL;
                [self removeUsedIndexBit:[index intValue]];
	}
	
	cocos2d::CCDirector::sharedDirector()->getOpenGLView()->touchesCancelled(&set);
}

@end
