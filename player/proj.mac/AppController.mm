//
//  AppDelegate.m
//  quick-x-player
//

#import "AppController.h"

#include "AppDelegate.h"
#include "glfw3.h"
#include "glfw3native.h"

#include "cocos2d.h"
USING_NS_CC;


#include "PlayerProtocol.h"

@implementation AppController

- (void) dealloc
{

}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [self updateProjectConfigFromCommandLineArgs:&projectConfig];
    

    // Insert code here to initialize your application

    GLView *view = GLView::createWithRect("quick-xf-player", cocos2d::Rect(0,0,960, 640), 1.0);
    Director::getInstance()->setOpenGLView(view);
    
    self.window = glfwGetCocoaWindow(view->getWindow());
    self.window.delegate = self;
    [NSApp setDelegate: self];
    
//    AppDelegate app;
//    Application::getInstance()->run();

    [self startup];
    
    // After run, application needs to be terminated immediately.
    [NSApp terminate: self];
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


- (void) updateProjectConfigFromCommandLineArgs:(ProjectConfig *)config
{
    NSArray *nsargs = [[NSProcessInfo processInfo] arguments];
    vector<string> args;
    for (int i = 0; i < [nsargs count]; ++i)
    {
        args.push_back([[nsargs objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]);
    }
    config->parseCommandLine(args);
    
    if (config->getProjectDir().length() == 0)
    {
        config->resetToWelcome();
    }
}

- (void) startup
{
    //    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"QUICK_COCOS2DX_ROOT"];
    NSString *path = [[NSUserDefaults standardUserDefaults] objectForKey:@"QUICK_COCOS2DX_ROOT"];
    if (!path || [path length] == 0)
    {
//        [self showPreferences:YES];
//        [self showAlertWithoutSheet:@"Please set quick-cocos2d-x root path." withTitle:@"quick-x-player error"];
    }
    
    const string projectDir = projectConfig.getProjectDir();
    if (projectDir.length())
    {
        vector<string> paths = FileUtils::getInstance()->getSearchPaths();
        paths.push_back(projectDir);
        
        // add res path
        {
            string resPath = projectDir + "/res/";
            paths.push_back(resPath);
        }

        {
            string resPath = projectDir + "/scripts/";
            paths.push_back(resPath);
        }
        
        {
            string resPath = projectDir + "/scripts/framework/";
            paths.push_back(resPath);
        }
        
        FileUtils::getInstance()->setSearchPaths(paths);
        if (projectConfig.isWriteDebugLogToFile())
        {
//            [self writeDebugLogToFile:projectConfig.getDebugLogFilePath()];
        }
    }
    
    const string writablePath = projectConfig.getWritableRealPath();
    if (writablePath.length())
    {
//        FileUtils::getInstance()->setWritablePath(writablePath.c_str());
    }
    
    if (projectConfig.isShowConsole())
    {
//        [self openConsoleWindow];
    }
    
    app = new AppDelegate();
//    bridge = new AppControllerBridge(self);
//    
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(bridge, callfuncO_selector(AppControllerBridge::onWelcomeNewProject), "WELCOME_NEW_PROJECT", NULL);
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(bridge, callfuncO_selector(AppControllerBridge::onWelcomeOpen), "WELCOME_OPEN_PROJECT", NULL);
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(bridge, callfuncO_selector(AppControllerBridge::onWelcomeSamples), "WELCOME_SAMPLES", NULL);
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(bridge, callfuncO_selector(AppControllerBridge::onWelcomeGetStarted), "WELCOME_OPEN_DOCUMENTS", NULL);
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(bridge, callfuncO_selector(AppControllerBridge::onWelcomeGetCommunity), "WELCOME_OPEN_COMMUNITY", NULL);
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(bridge, callfuncO_selector(AppControllerBridge::onWelcomeOpenRecent), "WELCOME_OPEN_PROJECT_ARGS", NULL);
    
    // send recent to Lua
    LuaValueArray titleArray;
    NSArray *recents = [[NSUserDefaults standardUserDefaults] arrayForKey:@"recents"];
    for (NSInteger i = 0; i < [recents count]; i++)
    {
        NSDictionary *recentItem = [recents objectAtIndex:i];
        titleArray.push_back(LuaValue::stringValue([[recentItem objectForKey:@"title"] UTF8String]));
    }
    app->setOpenRecents(titleArray);
    
    app->setProjectConfig(projectConfig);
//    app->run();
    Application::getInstance()->run();
}

@end
