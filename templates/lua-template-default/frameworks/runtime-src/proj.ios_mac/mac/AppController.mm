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

#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCLuaEngine.h"

#import "AppController.h"

using namespace std;
using namespace cocos2d;

@implementation AppController

-(void) dealloc
{
    Director::getInstance()->end();
    [super dealloc];
}

- (BOOL) windowShouldClose:(id)sender
{
    return YES;
}

- (void) windowWillClose:(NSNotification *)notification
{
    [[NSRunningApplication currentApplication] terminate];
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
{
    return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
    
    GLViewImpl *eglView = GLViewImpl::createWithRect("Cocos2d-x", cocos2d::Rect(0, 0, 960, 640), 1.0f);
    
    auto director = Director::getInstance();
    director->setOpenGLView(eglView);
    
    _window = eglView->getCocoaWindow();
    [[NSApplication sharedApplication] setDelegate: self];
    [_window center];

    NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
    FileUtils::getInstance()->addSearchPath(resourcePath.UTF8String);
    
    // app
    _app = new AppDelegate();
    Application::getInstance()->run();
    
    // After run, application needs to be terminated immediately.
    [NSApp terminate: self];
}

@end
