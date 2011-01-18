        //
        //  apptestAppDelegate.m
        //  apptest
        //
        //  Created by Walzer on 11-1-17.
        //  Copyright __MyCompanyName__ 2011. All rights reserved.
        //

#import "EAGLView.h"
#import "___PROJECTNAMEASIDENTIFIER___AppDelegate.h"
#import "HelloWorldScene.h"
#import "platform/iphone/CCDirectorCaller.h"

@implementation ___PROJECTNAMEASIDENTIFIER___AppDelegate

@synthesize window;

- (void) applicationDidFinishLaunching:(UIApplication*)application
{        
        window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
        EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                         pixelFormat: kEAGLColorFormatRGBA8
                                         depthFormat: 0
                                  preserveBackbuffer: NO
                                          sharegroup:nil
                                       multiSampling:NO
                                     numberOfSamples:0];
        [__glView setMultipleTouchEnabled:YES];
        [window addSubview: __glView];
        [window makeKeyAndVisible];
        
        [[UIApplication sharedApplication] setStatusBarHidden: YES];
	
                //      // Enables High Res mode (Retina Display) on iPhone 4 and maintains low res on all other devices
                //      if (! CCDirector::sharedDirector()->enableRetinaDisplay(true)) {
                //                CCLOG("Retina Display Not supported");
                //      }
        
                // init director
        view = new cocos2d::CCXEGLView();
        cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
        pDirector->setOpenGLView(view);
        
        cocos2d::CCDirector::sharedDirector()->setDeviceOrientation(cocos2d::kCCDeviceOrientationLandscapeLeft);
        
                // turn on display FPS
        pDirector->setDisplayFPS(true);
        
                // create a scene. it's an autorelease object
        cocos2d::CCScene *pScene = HelloWorld::scene();
        
                // run
        pDirector->runWithScene(pScene);
        
                // start mainloop
        [[CCDirectorCaller sharedDirectorCaller] startMainLoop];
}


- (void)applicationWillResignActive:(UIApplication *)application {
        cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
        cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
        cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}

-(void) applicationDidEnterBackground:(UIApplication*)application {
        cocos2d::CCDirector::sharedDirector()->stopAnimation();
}

-(void) applicationWillEnterForeground:(UIApplication*)application {
        cocos2d::CCDirector::sharedDirector()->startAnimation();
}

- (void)applicationWillTerminate:(UIApplication *)application {
        cocos2d::CCDirector::sharedDirector()->end();
        
        [viewController release];
	
        [window release];
}

- (void)applicationSignificantTimeChange:(UIApplication *)application {
        cocos2d::CCDirector::sharedDirector()->setNextDeltaTimeZero(true);
}

- (void)dealloc {
        delete view;
        [window release];
        [super dealloc];
}

@end
