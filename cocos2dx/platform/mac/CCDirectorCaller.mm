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
#import "CCDirectorCaller.h"
#import "CCDirector.h"
#import "EAGLView.h"
#import "CCEventDispatcher.h"
#include "CCAutoreleasePool.h"

static id s_sharedDirectorCaller;

@interface NSObject(CADisplayLink)
+(id) displayLinkWithTarget: (id)arg1 selector:(SEL)arg2;
-(void) addToRunLoop: (id)arg1 forMode: (id)arg2;
-(void) setFrameInterval: (int)interval;
-(void) invalidate;
@end

@implementation CCDirectorCaller

@synthesize interval;

+(id) sharedDirectorCaller
{
	if (s_sharedDirectorCaller == nil)
	{
		s_sharedDirectorCaller = [[CCDirectorCaller alloc] init];
	}
	
	return s_sharedDirectorCaller;
}

-(void) alloc
{
    interval = 1;
}

-(void) dealloc
{
    s_sharedDirectorCaller = nil;
    CCLOG("cocos2d: deallocing CCDirectorCaller %x", self);
	if (displayLink) {
		CVDisplayLinkRelease(displayLink);
	}
    
    CCLOG("--------------------------------------------------------------------------------");
    CCLOG("");
    CCLOG("");
    CCLOG("");
	[super dealloc];
}

- (CVReturn) getFrameForTime:(const CVTimeStamp*)outputTime
{
#if CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
	//if( ! runningThread_ )
	//runningThread_ = [NSThread currentThread];
    
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	cocos2d::CCDirector::sharedDirector()->drawScene();
	cocos2d::CCPoolManager::sharedPoolManager()->pop();
	[[CCEventDispatcher sharedDispatcher] dispatchQueuedEvents];
	
	[[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:nil];
	
	// release the objects
	[pool release];
	
#else
	[self performSelector:@selector(drawScene) onThread:[NSThread currentThread] withObject:nil waitUntilDone:YES];
#endif
	
    return kCVReturnSuccess;
}

// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    //    CVReturn result = [(CCDirectorCaller*)displayLinkContext getFrameForTime:outputTime];
    //    return result;
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	cocos2d::CCDirector::sharedDirector()->mainLoop();
	[pool release];
    
	return kCVReturnSuccess;
}

- (void)timerFired:(id)sender
{
    // It is good practice in a Cocoa application to allow the system to send the -drawRect:
    // message when it needs to draw, and not to invoke it directly from the timer.
    // All we do here is tell the display it needs a refresh
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
	// get the opengl view
	EAGLView *openGLView = [EAGLView sharedEGLView];
	[openGLView lockOpenGLContext];
    
	// run the main cocos2d loop
	cocos2d::CCDirector::sharedDirector()->mainLoop();
    
	// flush buffer (this line is very important!)
	[[openGLView openGLContext] flushBuffer];
	
	[openGLView unlockOpenGLContext];
    
	// send any queued events
	[[CCEventDispatcher sharedDispatcher] dispatchQueuedEvents];
    
	[pool release];
}

-(void) startMainLoop
{
    // CCDirector::setAnimationInterval() is called, we should invalide it first
    //        [displayLink invalidate];
    //        displayLink = nil;
    //
    //        displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
    //        [displayLink setFrameInterval: self.interval];
    //        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
#if ! CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
	NSThread* thread = [[NSThread alloc] initWithTarget:self selector:@selector(mainLoop) object:nil];
	[thread start];
#endif
	// NSTimer
	[renderTimer invalidate];
	renderTimer = nil;
    
	renderTimer = [NSTimer timerWithTimeInterval:self.interval/60.0f   //a 1ms time interval
                                          target:self
                                        selector:@selector(timerFired:)
                                        userInfo:nil
                                         repeats:YES];
    
    [[NSRunLoop currentRunLoop] addTimer:renderTimer
                                 forMode:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop] addTimer:renderTimer
                                 forMode:NSEventTrackingRunLoopMode]; //Ensure timer fires during resize
    
    /*
     // CVDisplayLink
     //cocos2d::CCDirector::sharedDirector()->gettimeofday();
     
     // Create a display link capable of being used with all active displays
     CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
     
     // Set the renderer output callback function
     CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, self);
     
     // Set the display link for the current renderer
     EAGLView *openGLView_ = (EAGLView*)[EAGLView sharedEGLView];
     CGLContextObj cglContext = (CGLContextObj)[[openGLView_ openGLContext] CGLContextObj];
     CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[openGLView_ pixelFormat] CGLPixelFormatObj];
     CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
     
     // Activate the display link
     CVDisplayLinkStart(displayLink);
     */
}

-(void) end
{
    [renderTimer invalidate];
	renderTimer = nil;
    [self release];
}

-(void) setAnimationInterval:(double)intervalNew
{
	self.interval = 60.0 * intervalNew;
	[renderTimer invalidate];
	renderTimer = nil;
	renderTimer = [NSTimer timerWithTimeInterval:self.interval/60.0f   //a 1ms time interval
										  target:self
										selector:@selector(timerFired:)
										userInfo:nil
										 repeats:YES];
	
	[[NSRunLoop currentRunLoop] addTimer:renderTimer 
								 forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:renderTimer 
								 forMode:NSEventTrackingRunLoopMode];
}

-(void) doCaller: (id) sender
{
	cocos2d::CCDirector::sharedDirector()->mainLoop();
}

@end
