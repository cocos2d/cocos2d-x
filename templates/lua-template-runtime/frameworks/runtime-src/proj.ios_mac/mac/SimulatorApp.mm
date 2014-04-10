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

#import "SimulatorApp.h"
#import "WorkSpaceDialogController.h"
#import "NSAppSheetAdditions.h"

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string>
#include <vector>

#include "AppDelegate.h"
#include "glfw3.h"
#include "glfw3native.h"
#include "Runtime.h"

#include "cocos2d.h"

using namespace cocos2d;

bool g_landscape = false;
cocos2d::Size g_screenSize;
GLView* g_eglView = nullptr;

using namespace std;
using namespace cocos2d;

@implementation AppController

@synthesize menu;

std::string getCurAppPath(void)
{
    return [[[NSBundle mainBundle] bundlePath] UTF8String];
}

-(void) dealloc
{
    Director::getInstance()->end();
    [super dealloc];
}

#pragma mark -
#pragma delegates

- (void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NSArray *args = [[NSProcessInfo processInfo] arguments];

    if (args!=nullptr && [args count]>=2) {
        extern std::string g_resourcePath;
        g_resourcePath = [[args objectAtIndex:1]UTF8String];
    }

    AppDelegate app;
    [self createSimulator:[NSString stringWithUTF8String:"HelloLua"] viewWidth:960 viewHeight:640 factor:1.0];
    Application::getInstance()->run();
    // After run, application needs to be terminated immediately.
    [NSApp terminate: self];
}


#pragma mark -
#pragma mark functions

- (void) createSimulator:(NSString*)viewName viewWidth:(float)width viewHeight:(float)height factor:(float)frameZoomFactor
{
    if (g_eglView)
    {
        return;
    }
    
    g_eglView = GLView::createWithRect([viewName cStringUsingEncoding:NSUTF8StringEncoding],cocos2d::Rect(0.0f,0.0f,width,height),frameZoomFactor);
    auto director = Director::getInstance();
    director->setOpenGLView(g_eglView);
    g_landscape = false;
    g_screenSize.width = width;
    g_screenSize.height = height;
    if (width  > height)
    {
        g_landscape = true;
    }

    window = glfwGetCocoaWindow(g_eglView->getWindow());
    [NSApp setDelegate: self];
    
    [self createViewMenu];
    [self updateMenu];
    [window center];

    [window becomeFirstResponder];
    [window makeKeyAndOrderFront:self];
}


- (void) createViewMenu
{
    
    NSMenu *submenu = [[[window menu] itemWithTitle:@"View"] submenu];

    for (int i = SimulatorConfig::getInstance()->getScreenSizeCount() - 1; i >= 0; --i)
    {
        SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize(i);
        NSMenuItem *item = [[[NSMenuItem alloc] initWithTitle:[NSString stringWithCString:size.title.c_str() encoding:NSUTF8StringEncoding]
                                                       action:@selector(onViewChangeFrameSize:)
                                                keyEquivalent:@""] autorelease];
        [item setTag:i];
        [submenu insertItem:item atIndex:0];
    }
}


- (void) updateMenu
{

    NSMenu *menuScreen = [[[window menu] itemWithTitle:@"View"] submenu];
    NSMenuItem *itemPortait = [menuScreen itemWithTitle:@"Portait"];
    NSMenuItem *itemLandscape = [menuScreen itemWithTitle:@"Landscape"];
    if (g_landscape)
    {
        [itemPortait setState:NSOffState];
        [itemLandscape setState:NSOnState];
    }
    else
    {
        [itemPortait setState:NSOnState];
        [itemLandscape setState:NSOffState];
    }

    int scale = g_eglView->getFrameZoomFactor()*100;

    NSMenuItem *itemZoom100 = [menuScreen itemWithTitle:@"Actual (100%)"];
    NSMenuItem *itemZoom75 = [menuScreen itemWithTitle:@"Zoom Out (75%)"];
    NSMenuItem *itemZoom50 = [menuScreen itemWithTitle:@"Zoom Out (50%)"];
    NSMenuItem *itemZoom25 = [menuScreen itemWithTitle:@"Zoom Out (25%)"];
    [itemZoom100 setState:NSOffState];
    [itemZoom75 setState:NSOffState];
    [itemZoom50 setState:NSOffState];
    [itemZoom25 setState:NSOffState];
    if (scale == 100)
    {
        [itemZoom100 setState:NSOnState];
    }
    else if (scale == 75)
    {
        [itemZoom75 setState:NSOnState];
    }
    else if (scale == 50)
    {
        [itemZoom50 setState:NSOnState];
    }
    else if (scale == 25)
    {
        [itemZoom25 setState:NSOnState];
    }

    int width = g_screenSize.width;
    int height = g_screenSize.height;
    if (height > width)
    {
        int w = width;
        width = height;
        height = w;
    }
    
    int count = SimulatorConfig::getInstance()->getScreenSizeCount();
    for (int i = 0; i < count; ++i)
    {
        bool bSel = false;
        SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize(i);
        if (size.width == width && size.height == height)
        {
            bSel = true;
        }
        NSMenuItem *itemView = [menuScreen itemWithTitle:[NSString stringWithUTF8String:size.title.c_str()]];
        [itemView setState:(bSel? NSOnState : NSOffState)];
    }
    

    //[window setTitle:[NSString stringWithFormat:@"quick-x-player (%0.0f%%)", projectConfig.getFrameScale() * 100]];
}


- (void) updateView
{
    auto policy = g_eglView->getResolutionPolicy();
    auto designSize = g_eglView->getDesignResolutionSize();
    
    if (g_landscape)
    {
        g_eglView->setFrameSize(g_screenSize.width, g_screenSize.height);
    }
    else
    {
        g_eglView->setFrameSize(g_screenSize.height, g_screenSize.width);
    }
    
    g_eglView->setDesignResolutionSize(designSize.width, designSize.height, policy);
    
    [self updateMenu];
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
{
    return YES;
}

- (BOOL) applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
{
    return NO;
}

- (void) windowWillClose:(NSNotification *)notification
{
    [[NSRunningApplication currentApplication] terminate];
}

- (IBAction) onChangeProject:(id)sender
{

    WorkSpaceDialogController *controller = [[WorkSpaceDialogController alloc] initWithWindowNibName:@"WorkSpaceDialog"];
    [NSApp beginSheet:controller.window modalForWindow:window didEndBlock:^(NSInteger returnCode) {
        if (returnCode == NSRunStoppedResponse)
        {
            CCLOG("1111");
        }
        [controller release];
    }];
}


- (IBAction) onFileClose:(id)sender
{
    [[NSApplication sharedApplication] terminate:self];
}


- (IBAction) onScreenPortait:(id)sender
{
    g_landscape = false;
    [self updateView];

}

- (IBAction) onScreenLandscape:(id)sender
{
    g_landscape = true;
    [self updateView];
}

- (IBAction) onReloadScript:(id)sender
{
    reloadScript("");
}


- (IBAction) onViewChangeFrameSize:(id)sender
{
    NSInteger index = [sender tag];
    if (index >= 0 && index < SimulatorConfig::getInstance()->getScreenSizeCount())
    {
        SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize(index);
        g_screenSize.width = size.width;
        g_screenSize.height = size.height;
        [self updateView];
    }
}


- (IBAction) onScreenZoomOut:(id)sender
{
    if ([sender state] == NSOnState) return;
    float scale = (float)[sender tag] / 100.0f;
    g_eglView->setFrameZoomFactor(scale);
    [self updateView];
}


@end
