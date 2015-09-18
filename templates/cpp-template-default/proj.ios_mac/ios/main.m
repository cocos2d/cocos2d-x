#import <UIKit/UIKit.h>

int main(int argc, char *argv[]) {
    NSString *appControllerClassName = @"AppController";
#if __has_feature(objc_arc)
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, appControllerClassName);
    }
#else
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    const int retVal = UIApplicationMain(argc, argv, nil, appControllerClassName);
    [pool release];
    return retVal;
#endif
}
