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

#import "CCWindow.h"
#import "EAGLView.h"

@implementation CCWindow

- (id) initWithFrame:(NSRect)frame fullscreen:(BOOL)fullscreen
{
	int styleMask = fullscreen ? NSBackingStoreBuffered : ( NSTitledWindowMask | NSClosableWindowMask );
	self = [self initWithContentRect:frame
						   styleMask:styleMask
							 backing:NSBackingStoreBuffered
							   defer:YES];

	if (self != nil)
	{
		if(fullscreen)
		{
			[self setLevel:NSMainMenuWindowLevel+1];
			[self setHidesOnDeactivate:YES];
			[self setHasShadow:NO];
		}

		[self setAcceptsMouseMovedEvents:NO];
		[self setOpaque:YES];
	}
	return self;
}

- (BOOL) canBecomeKeyWindow
{
	return YES;
}

- (BOOL) canBecomeMainWindow
{
	return YES;
}

- (void) keyDown:(NSEvent *)event
{
	// exit fullscreen if user pressed esc
	if([event keyCode] == 53)
	{
		EAGLView* eaglView = [EAGLView sharedEGLView];
		
		// cancel full screen
		if( [eaglView isFullScreen] )
			[eaglView setFullScreen:NO];

		// let another responder take it
		else
			[super keyDown:event];
	}
}

@end

