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

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string>
#include <vector>

#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "platform/CCFileUtils.h"

#include "glfw3.h"
#include "glfw3native.h"

using namespace std;
using namespace cocos2d;
//using namespace cocos2d::extra;

@implementation AppController

@synthesize menu;

-(void) dealloc
{
    Director::getInstance()->end();
    [super dealloc];
}

#pragma mark -
#pragma delegates

- (void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    isAlwaysOnTop = NO;

    [self updateProjectConfigFromCommandLineArgs:&projectConfig];
    [self createWindowAndGLView];
    [self initUI];
    [self updateUI];
    [self startup];
    
    [[NSApplication sharedApplication] terminate:self];
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
    Director::getInstance()->end();
    [[NSApplication sharedApplication] terminate:self];
}

#pragma mark -
#pragma mark functions

- (void) createWindowAndGLView
{
    GLView *view = GLView::createWithRect("quick-x-player", cocos2d::Rect(0,0,projectConfig.getFrameSize().width, projectConfig.getFrameSize().height), projectConfig.getFrameScale());
    Director::getInstance()->setOpenGLView(view);
    
    window = glfwGetCocoaWindow(view->getWindow());
//    window.delegate = self;
    [NSApp setDelegate: self];
    
    // set window parameters
    [window center];
    
    if (projectConfig.getProjectDir().length())
    {
        [self setZoom:projectConfig.getFrameScale()];
        Vec2 pos = projectConfig.getWindowOffset();
        if (pos.x != 0 && pos.y != 0)
        {
            [window setFrameOrigin:NSMakePoint(pos.x, pos.y)];
        }
    }
    
    //    [window becomeFirstResponder];
    //    [window makeKeyAndOrderFront:self];
    //    [window setAcceptsMouseMovedEvents:NO];
}

- (void) startup
{
    const string projectDir = projectConfig.getProjectDir();
    if (projectDir.length())
    {
        FileUtils::getInstance()->setSearchRootPath(projectDir.c_str());
    }

    const string writablePath = projectConfig.getWritableRealPath();
    if (writablePath.length())
    {
        FileUtils::getInstance()->setWritablePath(writablePath.c_str());
    }

    app = new AppDelegate();
    app->setProjectConfig(projectConfig);
    app->run();
}

- (void) initUI
{
    NSMenu *submenu = [[[window menu] itemWithTitle:@"Screen"] submenu];

    SimulatorConfig *config = SimulatorConfig::sharedDefaults();
    int current = config->checkScreenSize(projectConfig.getFrameSize());
    for (int i = config->getScreenSizeCount() - 1; i >= 0; --i)
    {
        SimulatorScreenSize size = config->getScreenSize(i);
        NSMenuItem *item = [[[NSMenuItem alloc] initWithTitle:[NSString stringWithCString:size.title.c_str() encoding:NSUTF8StringEncoding]
                                                       action:@selector(onScreenChangeFrameSize:)
                                                keyEquivalent:@""] autorelease];
        [item setTag:i];

        if (i == current)
        {
            [item setState:NSOnState];
        }
        [submenu insertItem:item atIndex:0];
    }
}

- (void) updateUI
{
    NSMenu *menuScreen = [[[window menu] itemWithTitle:@"Screen"] submenu];
    NSMenuItem *itemPortait = [menuScreen itemWithTitle:@"Portait"];
    NSMenuItem *itemLandscape = [menuScreen itemWithTitle:@"Landscape"];
    if (projectConfig.isLandscapeFrame())
    {
        [itemPortait setState:NSOffState];
        [itemLandscape setState:NSOnState];
    }
    else
    {
        [itemPortait setState:NSOnState];
        [itemLandscape setState:NSOffState];
    }

    int scale = projectConfig.getFrameScale() * 100;

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

    [window setTitle:[NSString stringWithFormat:@"__PROJECT_PACKAGE_LAST_NAME_L__ (%0.0f%%)", projectConfig.getFrameScale() * 100]];
}

- (NSMutableArray*) makeCommandLineArgsFromProjectConfig
{
    return [self makeCommandLineArgsFromProjectConfig:kProjectConfigAll];
}

- (NSMutableArray*) makeCommandLineArgsFromProjectConfig:(unsigned int)mask
{
    projectConfig.setWindowOffset(Vec2(window.frame.origin.x, window.frame.origin.y));
    NSString *commandLine = [NSString stringWithCString:projectConfig.makeCommandLine(mask).c_str()
                                               encoding:NSUTF8StringEncoding];
    return [NSMutableArray arrayWithArray:[commandLine componentsSeparatedByString:@" "]];
}

- (void) updateProjectConfigFromCommandLineArgs:(ProjectConfig *)config
{
    NSArray *nsargs = [[NSProcessInfo processInfo] arguments];
    vector<string> args;
    for (int i = 0; i < [nsargs count]; ++i)
    {
        args.push_back([[nsargs objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]);
    }
    config->parseCommandLine(args);
    config->dump();
}

- (void) launch:(NSArray*)args
{
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *configuration = [NSMutableDictionary dictionaryWithObject:args
                                                                            forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error = [[[NSError alloc] init] autorelease];
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:configuration error:&error];
}

- (void) relaunch:(NSArray*)args
{
    [self saveLastState];
    if (projectConfig.isExitWhenRelaunch())
    {
        exit(99);
    }
    else
    {
        [self launch:args];
        [[NSApplication sharedApplication] terminate:self];
    }
}

- (void) relaunch
{
    [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
}

- (void) showAlertWithoutSheet:(NSString*)message withTitle:(NSString*)title
{
    NSAlert *alert = [[[NSAlert alloc] init] autorelease];
    [alert addButtonWithTitle:@"OK"];
    [alert setMessageText:message];
    [alert setInformativeText:title];
    [alert setAlertStyle:NSWarningAlertStyle];
    [alert runModal];
}

- (void) setZoom:(float)scale
{
//    [glView setFrameZoomFactor:scale];
    Director::getInstance()->getOpenGLView()->setFrameZoomFactor(scale);
    projectConfig.setFrameScale(scale);
}

-(void) setAlwaysOnTop:(BOOL)alwaysOnTop
{
    NSMenuItem *windowMenu = [[window menu] itemWithTitle:@"Window"];
    NSMenuItem *menuItem = [[windowMenu submenu] itemWithTitle:@"Always On Top"];
    if (alwaysOnTop)
    {
        [window setLevel:NSFloatingWindowLevel];
        [menuItem setState:NSOnState];
    }
    else
    {
        [window setLevel:NSNormalWindowLevel];
        [menuItem setState:NSOffState];
    }
    isAlwaysOnTop = alwaysOnTop;
}

-(void) saveLastState
{
    NSMutableDictionary *state = [NSMutableDictionary dictionary];
    [state setObject:[NSNumber numberWithInt:window.frame.origin.x] forKey:@"x"];
    [state setObject:[NSNumber numberWithInt:window.frame.origin.y] forKey:@"y"];
    [state setObject:[NSNumber numberWithFloat:projectConfig.getFrameScale()] forKey:@"scale"];
    [[NSUserDefaults standardUserDefaults] setObject:state forKey:@"last-state"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

#pragma mark -
#pragma mark IB Actions

- (IBAction) onFileRelaunch:(id)sender
{
    [self relaunch];
}

- (IBAction) onScreenChangeFrameSize:(id)sender
{
    NSInteger i = [sender tag];
    if (i >= 0 && i < SimulatorConfig::sharedDefaults()->getScreenSizeCount())
    {
        SimulatorScreenSize size = SimulatorConfig::sharedDefaults()->getScreenSize((int)i);
        projectConfig.setFrameSize(projectConfig.isLandscapeFrame() ? CCSize(size.height, size.width) : CCSize(size.width, size.height));
        projectConfig.setFrameScale(1.0f);
        [self relaunch];
    }
}

- (IBAction) onScreenPortait:(id)sender
{
    if ([sender state] == NSOnState) return;
    [sender setState:NSOnState];
    [[[[[window menu] itemWithTitle:@"Screen"] submenu] itemWithTitle:@"Landscape"] setState:NSOffState];
    projectConfig.changeFrameOrientationToPortait();
    [self relaunch];
}

- (IBAction) onScreenLandscape:(id)sender
{
    if ([sender state] == NSOnState) return;
    [sender setState:NSOnState];
    [[[[[window menu] itemWithTitle:@"Screen"] submenu] itemWithTitle:@"Portait"] setState:NSOffState];
    projectConfig.changeFrameOrientationToLandscape();
    [self relaunch];
}

- (IBAction) onScreenZoomOut:(id)sender
{
    if ([sender state] == NSOnState) return;
    float scale = (float)[sender tag] / 100.0f;
    [self setZoom:scale];
    [self updateUI];
}

-(IBAction) onWindowAlwaysOnTop:(id)sender
{
    [self setAlwaysOnTop:!isAlwaysOnTop];
}

@end
