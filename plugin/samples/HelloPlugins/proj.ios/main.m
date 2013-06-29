#import <UIKit/UIKit.h>

// Under iOS and the Simulator, we can use an alternate Accelerometer interface
#import "AccelerometerSimulation.h"

int main(int argc, char *argv[]) {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];
    return retVal;
}
