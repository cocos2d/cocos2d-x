
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

#import "RootViewController.h"

ServerController *server;


extern "C" {

    
    void setDeviceResolutionJNI(const char *text) {
        
    }
    
    void cleanCacheDirJNI(){
        cleanCache();
        [server sendFileList];
    }
    
    void openEditBox() {
        [server pressedPair];
    }
    
    void sendLogMsg(const char *msg) {
        if(server != NULL) {
            NSString *str = [NSString stringWithCString:msg encoding:NSASCIIStringEncoding];
            [server sendLog:[str stringByAppendingString:@"\n"]];
        }
    }
    
    void runJSApp() {
        [server runJSApp];
    }
    
    void updatePairing(const char *pairing) {
        NSString *code;
        if(pairing) {
            code = [NSString stringWithCString:pairing encoding:NSASCIIStringEncoding];
        } else {
            code = [[NSString alloc] initWithString:@"Auto"];
        }
        if([code isEqual:@"Auto"]) {
            [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"pairing"];
        } else {
            [[NSUserDefaults standardUserDefaults] setObject:code forKey:@"pairing"];
        }
        [[NSUserDefaults standardUserDefaults] synchronize];
        [server updatePairing];
    }
    
    const char * getCCBDirectoryPath() {
        std::string path = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
        NSString *writeablePath = [NSString stringWithCString:path.c_str() encoding:NSASCIIStringEncoding];
        NSString* dirPath = [writeablePath stringByAppendingPathComponent:@"ccb"];
        return [dirPath cStringUsingEncoding:NSASCIIStringEncoding];
    }
    
    void resetCocosApp() {
        [[AppController appController] resetCocos2d];
    }

    
}

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;
static AppController* appController = NULL;


+ (AppController*) appController
{
    return appController;
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    appController = self;
    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16 //_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0 ];

    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden: YES];

    cocos2d::CCApplication::sharedApplication()->run();
    
    startServer(s_sharedApplication.isRetina, s_sharedApplication.isIPhone);
    return YES;
}

- (BOOL)shouldAutorotate;
{
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}

void startServer(bool isRetina, bool isIPhone) {
    server = [[ServerController alloc] init];
    server.isIPhone = isIPhone;
    server.isRetina = isRetina;
    [server start];
    
    [server setNetworkStatus:kCCBNetworkStatusWaiting];
}

- (void)dealloc {
    [super dealloc];
}


@end

