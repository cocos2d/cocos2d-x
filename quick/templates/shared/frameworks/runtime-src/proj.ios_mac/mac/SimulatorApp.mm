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

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string>
#include <vector>

#import "SimulatorApp.h"
#include "AppDelegate.h"
#include "glfw3.h"
#include "glfw3native.h"
#include "Runtime.h"
#include "ConfigParser.h"

#include "cocos2d.h"

using namespace cocos2d;

bool g_landscape = false;
bool g_windTop = false;
cocos2d::Size g_screenSize;
GLViewImpl* g_eglView = nullptr;

static AppController* g_nsAppDelegate=nullptr;

using namespace std;
using namespace cocos2d;

@implementation AppController

@synthesize menu;

std::string getCurAppPath(void)
{
    return [[[NSBundle mainBundle] bundlePath] UTF8String];
}

std::string getCurAppName(void)
{
    string appName = [[[NSProcessInfo processInfo] processName] UTF8String];
    int found = appName.find(" ");
    if (found!=std::string::npos)
        appName = appName.substr(0,found);
    
    return appName;
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
    [self updateProjectFromCommandLineArgs:&_project];
    [self startup];
}


#pragma mark -
#pragma mark functions

- (void) createSimulator:(NSString*)viewName viewWidth:(float)width viewHeight:(float)height factor:(float)frameZoomFactor
{
    if (g_eglView)
    {
        return;
    }
    
    if(!g_landscape)
    {
        float tmpvalue =width;
        width = height;
        height = tmpvalue;
    }
    g_windTop = ConfigParser::getInstance()->isWindowTop();
    g_eglView = GLViewImpl::createWithRect([viewName cStringUsingEncoding:NSUTF8StringEncoding],cocos2d::Rect(0.0f,0.0f,width,height),frameZoomFactor);
    auto director = Director::getInstance();
    director->setOpenGLView(g_eglView);

    _window = glfwGetCocoaWindow(g_eglView->getWindow());
    [[NSApplication sharedApplication] setDelegate: self];
    
    [self createViewMenu];
    [self updateMenu];
    [_window center];
    
    [_window becomeFirstResponder];
    [_window makeKeyAndOrderFront:self];
}

void createSimulator(const char* viewName, float width, float height,bool isLandscape,float frameZoomFactor)
{
    if(g_nsAppDelegate)
    {
        g_landscape = isLandscape;
        if(height > width)
        {
            float tmpvalue =width;
            width = height;
            height = tmpvalue;
        }
        g_screenSize.width = width;
        g_screenSize.height = height;
        
        [g_nsAppDelegate createSimulator:[NSString stringWithUTF8String:viewName] viewWidth:width viewHeight:height factor:frameZoomFactor];
    }
    
}

- (void) updateProjectFromCommandLineArgs:(ProjectConfig*)config
{
    config->setShowConsole(true);
    config->setDebuggerType(kCCLuaDebuggerCodeIDE);
    NSArray *nsargs = [[NSProcessInfo processInfo] arguments];
    long n = [nsargs count];
    if (n >= 2)
    {
        vector<string> args;
        for (int i = 0; i < [nsargs count]; ++i)
        {
            string arg = [[nsargs objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding];
            if (arg.length()) args.push_back(arg);
        }
        config->parseCommandLine(args);
    }
    
//    if (config->getProjectDir().length() == 0)
//    {
//        config->resetToWelcome();
//    }
}

- (void) startup
{
    if (_project.isShowConsole())
    {
        [self openConsoleWindow];
    }
    
//    NSArray *args = [[NSProcessInfo processInfo] arguments];
//    
//    if (args!=nullptr && [args count]>=2) {
//        extern std::string g_resourcePath;
//        g_resourcePath = [[args objectAtIndex:1]UTF8String];
//        if (g_resourcePath.at(0) != '/') {
//            g_resourcePath="";
//        }
//    }
    g_nsAppDelegate =self;
    AppDelegate app;
    if (_project.getDebuggerType()==kCCLuaDebuggerNone)
    {
        app.setLaunchMode(0);
    }
    Application::getInstance()->run();
    // After run, application needs to be terminated immediately.
    [[NSApplication sharedApplication] terminate: self];
}

- (void) openConsoleWindow
{
    if (!_consoleController)
    {
        _consoleController = [[ConsoleWindowController alloc] initWithWindowNibName:@"ConsoleWindow"];
    }
    [_consoleController.window orderFrontRegardless];
    
    //set console pipe
    _pipe = [NSPipe pipe] ;
    _pipeReadHandle = [_pipe fileHandleForReading] ;

    int outfd = [[_pipe fileHandleForWriting] fileDescriptor];
    if (dup2(outfd, fileno(stderr)) != fileno(stderr) || dup2(outfd, fileno(stdout)) != fileno(stdout))
    {
        perror("Unable to redirect output");
//                [self showAlert:@"Unable to redirect output to console!" withTitle:@"player error"];
    }
    else
    {
        [[NSNotificationCenter defaultCenter] addObserver: self
                                                 selector: @selector(handleNotification:)
                                                     name: NSFileHandleReadCompletionNotification
                                                   object: _pipeReadHandle] ;
        [_pipeReadHandle readInBackgroundAndNotify] ;
    }
}

- (void)handleNotification:(NSNotification *)note
{
    //NSLog(@"Received notification: %@", note);
    [_pipeReadHandle readInBackgroundAndNotify] ;
    NSData *data = [[note userInfo] objectForKey:NSFileHandleNotificationDataItem];
    NSString *str = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
    
    //show log to console
    [_consoleController trace:str];
    if(_fileHandle != nil)
    {
        [_fileHandle writeData:[str dataUsingEncoding:NSUTF8StringEncoding]];
    }
    
}

- (void) createViewMenu
{
    
    NSMenu *submenu = [[[_window menu] itemWithTitle:@"View"] submenu];

    for (int i = ConfigParser::getInstance()->getScreenSizeCount() - 1; i >= 0; --i)
    {
        SimulatorScreenSize size = ConfigParser::getInstance()->getScreenSize(i);
        NSMenuItem *item = [[[NSMenuItem alloc] initWithTitle:[NSString stringWithCString:size.title.c_str() encoding:NSUTF8StringEncoding]
                                                       action:@selector(onViewChangeFrameSize:)
                                                keyEquivalent:@""] autorelease];
        [item setTag:i];
        [submenu insertItem:item atIndex:0];
    }
}


- (void) updateMenu
{

    NSMenu *menuScreen = [[[_window menu] itemWithTitle:@"View"] submenu];
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
    
    NSMenu *menuControl = [[[_window menu] itemWithTitle:@"Control"] submenu];
    NSMenuItem *itemTop = [menuControl itemWithTitle:@"Keep Window Top"];
    if (g_windTop) {
        [_window setLevel:NSFloatingWindowLevel];
        [itemTop setState:NSOnState];
    }
    else
    {
        [_window setLevel:NSNormalWindowLevel];
        [itemTop setState:NSOffState];
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
    
    int count = ConfigParser::getInstance()->getScreenSizeCount();
    for (int i = 0; i < count; ++i)
    {
        bool bSel = false;
        SimulatorScreenSize size = ConfigParser::getInstance()->getScreenSize(i);
        if (size.width == width && size.height == height)
        {
            bSel = true;
        }
        NSMenuItem *itemView = [menuScreen itemWithTitle:[NSString stringWithUTF8String:size.title.c_str()]];
        [itemView setState:(bSel? NSOnState : NSOffState)];
    }
    

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

- (IBAction) onSetTop:(id)sender
{
    g_windTop = !g_windTop;
    [self updateMenu];
}


- (IBAction) onFileClose:(id)sender
{
    [[NSApplication sharedApplication] terminate:self];
}


- (IBAction) onScreenPortait:(id)sender
{
    if ([sender state] == NSOnState) return;
    g_landscape = false;
    [self updateView];
}

- (IBAction) onScreenLandscape:(id)sender
{
    if ([sender state] == NSOnState) return;
    g_landscape = true;
    [self updateView];
}

- (void) launch:(NSArray*)args
{
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *configuration = [NSMutableDictionary dictionaryWithObject:args forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error = [[[NSError alloc] init] autorelease];
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:configuration error:&error];
}

- (void) relaunch:(NSArray*)args
{
    [self launch:args];
    [[NSApplication sharedApplication] terminate:self];
}

- (IBAction) onRelaunch:(id)sender
{
    NSArray* args=[[NSArray alloc] initWithObjects:@" ", nil];
    [self relaunch:args];
}


- (IBAction) onViewChangeFrameSize:(id)sender
{
    NSInteger index = [sender tag];
    if (index >= 0 && index < ConfigParser::getInstance()->getScreenSizeCount())
    {
        SimulatorScreenSize size = ConfigParser::getInstance()->getScreenSize(index);
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
