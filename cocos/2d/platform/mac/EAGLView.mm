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

/*
 * Idea of subclassing NSOpenGLView was taken from  "TextureUpload" Apple's sample
 */

#import <Availability.h>

#import "EAGLView.h"
#import "CCEGLView.h"
#import <OpenGL/gl.h>
#import "CCDirector.h"
#import "ccConfig.h"
#import "CCSet.h"
#import "CCTouch.h"
#import "CCIMEDispatcher.h"
#import "CCEventDispatcherMac.h"
#import "CCEGLView.h"


//USING_NS_CC;
static CCEAGLView *view;

@implementation CCEAGLView

@synthesize eventDelegate = eventDelegate_, isFullScreen = isFullScreen_, frameZoomFactor=frameZoomFactor_;

+(id) sharedEGLView
{
	return view;
}


- (void) update
{
	// XXX: Should I do something here ?
	[super update];
}

- (void) prepareOpenGL
{
	// XXX: Initialize OpenGL context

	[super prepareOpenGL];
	
	// Make this openGL context current to the thread
	// (i.e. all openGL on this thread calls will go to this context)
	[[self openGLContext] makeCurrentContext];
	
	// Synchronize buffer swaps with vertical refresh rate
	GLint swapInt = 1;
	[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];	

//	GLint order = -1;
//	[[self openGLContext] setValues:&order forParameter:NSOpenGLCPSurfaceOrder];
}

- (NSUInteger) depthFormat
{
	return 24;
}

- (void) setFrameZoomFactor:(float)frameZoomFactor
{
    frameZoomFactor_ = frameZoomFactor;
    
    NSRect winRect = [[self window] frame];
    NSRect viewRect = [self frame];
    
    // compute the margin width and margin height
    float diffX = winRect.size.width - viewRect.size.width;
    float diffY = winRect.size.height - viewRect.size.height;
    
    // new window width and height
    float newWindowWidth = (int)(viewRect.size.width * frameZoomFactor + diffX);
    float newWindowHeight = (int)(viewRect.size.height * frameZoomFactor + diffY);
    
    // display window in the center of the screen
    NSRect screenRect = [[NSScreen mainScreen] frame];
    float originX = (screenRect.size.width - newWindowWidth) / 2;
    float originY = (screenRect.size.height - newWindowHeight) / 2;
    
    [[self window] setFrame:NSMakeRect(originX, originY, newWindowWidth, newWindowHeight) display:true];
}

- (void) reshape
{
	// We draw on a secondary thread through the display link
	// When resizing the view, -reshape is called automatically on the main thread
	// Add a mutex around to avoid the threads accessing the context simultaneously when resizing

	[self lockOpenGLContext];
	
//	NSRect rect = [self bounds];
	
	cocos2d::Director *director = cocos2d::Director::getInstance();
//	CGSize size = NSSizeToCGSize(rect.size);
//	cocos2d::Size ccsize = cocos2d::Size(size.width, size.height);
	//director->reshapeProjection(ccsize);
	
	// avoid flicker
	director->drawScene();
//	[self setNeedsDisplay:YES];
	
	[self unlockOpenGLContext];
}

-(void) lockOpenGLContext
{
	NSOpenGLContext *glContext = [self openGLContext];
	NSAssert( glContext, @"FATAL: could not get openGL context");

	[glContext makeCurrentContext];
	CGLLockContext((CGLContextObj)[glContext CGLContextObj]);
}

-(void) unlockOpenGLContext
{
	NSOpenGLContext *glContext = [self openGLContext];
	NSAssert( glContext, @"FATAL: could not get openGL context");

	CGLUnlockContext((CGLContextObj)[glContext CGLContextObj]);
}

- (void) dealloc
{
	CCLOGINFO("deallocing CCEAGLView: %p", self);
	[super dealloc];
}
	
-(int) getWidth
{
	NSSize bound = [self bounds].size;
	return bound.width;
}

-(int) getHeight
{
	NSSize bound = [self bounds].size;
	return bound.height;
}

@end
