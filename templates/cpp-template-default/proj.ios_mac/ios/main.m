#import <UIKit/UIKit.h>

int main(int argc, char *argv[]) {
    NSString *appControllerClassName = @"AppController";
#if __has_feature(objc_arc)
    @autoreleasepool {
        int retVal = UIApplicationMain(argc, argv, nil, appControllerClassName);
        return retVal;
    }
#else
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, appControllerClassName);
    [pool release];
    return retVal;
#endif
}
