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
#import "CCDirectorDisplayLinkMacWrapper.h"
#import "ccConfig.h"

@implementation CCDirectorDisplayLinkMacWrapper

static CCDirectorDisplayLinkMacWrapper* sharedDisplayLinkMacWrapper;

@synthesize runningThread = runningThread_;

+(CCDirectorDisplayLinkMacWrapper*)sharedDisplayLinkMacWrapper
{
    if (! sharedDisplayLinkMacWrapper)
	{
		sharedDiplayLinkMacWrapper = [CCDirectorDisplayLinkMacWrapper new];
	}

	return sharedDiplayLinkMacWrapper;
}

- (void) init
{
	runningThread_ = nil;
	displayLink = nil;
}

- (CVReturn) getFrameForTime:(const CVTimeStamp*)outputTime
{
#if CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
	if( ! runningThread_ )
		runningThread_ = [NSThread currentThread];

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	[self drawScene];
	[[CCEventDispatcher sharedDispatcher] dispatchQueuedEvents];

	[[NSRunLoop currentRunLoop] run];

	[pool release];

#else
	[self performSelector:@selector(drawScene) onThread:runningThread_ withObject:nil waitUntilDone:YES];
#endif

	return kCVReturnSuccess;
}

// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
	CVReturn result = [(CCDirectorDisplayLinkMacWrapper*)displayLinkContext getFrameForTime:outputTime];
	return result;
}

- (void) startAnimation
{
#if ! CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
	runningThread_ = [[NSThread alloc] initWithTarget:self selector:@selector(mainLoop) object:nil];
	[runningThread_ start];	
#endif

	// Create a display link capable of being used with all active displays
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);

	// Set the renderer output callback function
	CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, self);

	// Set the display link for the current renderer
	CGLContextObj cglContext = [[openGLView_ openGLContext] CGLContextObj];
	CGLPixelFormatObj cglPixelFormat = [[openGLView_ pixelFormat] CGLPixelFormatObj];
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);

	// Activate the display link
	CVDisplayLinkStart(displayLink);
}

- (void) mainLoop
{
	cocos2d::CCDirector::sharedDirector()->mainLoop();
}

- (void) stopAnimation
{
	if( displayLink ) {
		CVDisplayLinkStop(displayLink);
		CVDisplayLinkRelease(displayLink);
		displayLink = NULL;

#if ! CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
		[runningThread_ cancel];
		[runningThread_ release];
		runningThread_ = nil;
#endif
	}
}

-(void) dealloc
{
	if( displayLink ) 
	{
		CVDisplayLinkStop(displayLink);
		CVDisplayLinkRelease(displayLink);
	}

	sharedDisplayLinkMacWrapper = nil;

	[super dealloc];
}

//
// Draw the Scene
//
- (void) drawScene
{    
	cocos2d::CCDirector::sharedDirector()->drawScene();
}

@end