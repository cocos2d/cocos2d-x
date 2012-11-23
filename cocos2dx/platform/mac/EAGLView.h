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

#ifndef __EAGLVIEW_MAC_H__
#define __EAGLVIEW_MAC_H__

#import <Cocoa/Cocoa.h>
#import "ccConfig.h"

//PROTOCOLS:

@protocol MacEventDelegate <NSObject>
// Mouse
- (void)mouseDown:(NSEvent *)theEvent;
- (void)mouseUp:(NSEvent *)theEvent;
- (void)mouseMoved:(NSEvent *)theEvent;
- (void)mouseDragged:(NSEvent *)theEvent;
- (void)rightMouseDown:(NSEvent*)event;
- (void)rightMouseDragged:(NSEvent*)event;
- (void)rightMouseUp:(NSEvent*)event;
- (void)otherMouseDown:(NSEvent*)event;
- (void)otherMouseDragged:(NSEvent*)event;
- (void)otherMouseUp:(NSEvent*)event;
- (void)scrollWheel:(NSEvent *)theEvent;
- (void)mouseEntered:(NSEvent *)theEvent;
- (void)mouseExited:(NSEvent *)theEvent;


// Keyboard
- (void)keyDown:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;
- (void)flagsChanged:(NSEvent *)theEvent;

// Touches
- (void)touchesBeganWithEvent:(NSEvent *)event;
- (void)touchesMovedWithEvent:(NSEvent *)event;
- (void)touchesEndedWithEvent:(NSEvent *)event;
- (void)touchesCancelledWithEvent:(NSEvent *)event;

#if CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
- (void)queueEvent:(NSEvent*)event selector:(SEL)selector;
#endif

@end

/** MacGLView
 
 Only available for Mac OS X
 */
@interface EAGLView : NSOpenGLView {
	id<MacEventDelegate> eventDelegate_;

	BOOL isFullScreen_;
	NSWindow		*fullScreenWindow_;
	
	// cache
	NSWindow		*windowGLView_;
    NSView          *superViewGLView_;
    NSRect          originalWinRect_; // Original size and position
    
    float           frameZoomFactor_;
}

@property (nonatomic, readwrite, assign) id<MacEventDelegate> eventDelegate;

// whether or not the view is in fullscreen mode
@property (nonatomic, readonly) BOOL isFullScreen;

@property (nonatomic, readwrite) float frameZoomFactor;

// initializes the MacGLView with a frame rect and an OpenGL context
- (id) initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context;

- (id) initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format;

/** uses and locks the OpenGL context */
-(void) lockOpenGLContext;

/** unlocks the openGL context */
-(void) unlockOpenGLContext;

/** returns the depth format of the view in BPP */
- (NSUInteger) depthFormat;

- (void) setFrameZoomFactor:(float)frameZoomFactor;

// get the view object
+(id) sharedEGLView;

-(int) getWidth;
-(int) getHeight;
-(void) swapBuffers;

-(void) setFullScreen:(BOOL)fullscreen;

@end
#endif // __EAGLVIEW_MAC_H__

