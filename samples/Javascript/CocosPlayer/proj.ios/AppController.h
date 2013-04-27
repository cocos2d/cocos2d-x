#import "ServerController.h"


void startServer(bool isRetina, bool isIPhone);
void cleanCache() {
    std::string path = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
    NSString *writeablePath = [NSString stringWithCString:path.c_str() encoding:NSASCIIStringEncoding];
    NSString* dirPath = [writeablePath stringByAppendingPathComponent:@"ccb"];
    
    [[NSFileManager defaultManager] removeItemAtPath:dirPath error:NULL];
    [[NSFileManager defaultManager] removeItemAtPath:writeablePath error:NULL];
}


@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}
+ (AppController*) appController;

@end

