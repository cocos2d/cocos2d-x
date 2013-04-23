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
 
#import "AppController.h"
#import "AppDelegate.h"

static AppDelegate s_sharedApplication;

@implementation AppController

	@synthesize window, glView;

	-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
	{
		// create the window
		// note that using NSResizableWindowMask causes the window to be a little
		// smaller and therefore ipad graphics are not loaded
		NSRect rect = NSMakeRect(0, 0, 2048, 1536);
		window = [[NSWindow alloc] initWithContentRect:rect
			styleMask:( NSClosableWindowMask | NSTitledWindowMask )
			backing:NSBackingStoreBuffered
			defer:YES];
		
		// allocate our GL view
		// (isn't there already a shared EAGLView?)
		glView = [[EAGLView alloc] initWithFrame:rect];

		// set window parameters
		[window becomeFirstResponder];
		[window setContentView:glView];
		[window setTitle:@"SampleGame"];
		[window makeKeyAndOrderFront:self];
		[window setAcceptsMouseMovedEvents:NO];
        
        [glView setFrameZoomFactor:0.4];

		cocos2d::CCApplication::sharedApplication()->run();
	}

	-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
	{
		return YES;
	}

	-(void) dealloc
	{
		cocos2d::CCDirector::sharedDirector()->end();
		[super dealloc];
	}

#pragma mark -
#pragma mark IB Actions

	-(IBAction) toggleFullScreen:(id)sender
	{
		EAGLView* pView = [EAGLView sharedEGLView];
		[pView setFullScreen:!pView.isFullScreen];
	}

	-(IBAction) exitFullScreen:(id)sender
	{
		[[EAGLView sharedEGLView] setFullScreen:NO];
	}

@end
