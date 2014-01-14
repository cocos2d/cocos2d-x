/****************************************************************************
Copyright (c) 2008 Otto Chrons at Seastringo Oy.
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#import <TargetConditionals.h>

// when compiling to ARM (iPhone device), hide everything and use system defaults
// if you wish to use simulation mode even on the device, remove the #if/#endif
#if !TARGET_CPU_ARM
#import <UIKit/UIKit.h>

// this is exactly the same as UIAcceleration, but we can modify the member variables
@interface UIAccelerationSimulation: NSObject
{
    NSTimeInterval timestamp;
    UIAccelerationValue x, y, z;
}
@property(nonatomic, readonly) NSTimeInterval timestamp;
@property(nonatomic, readonly) UIAccelerationValue x, y, z;

@end

// override UIAccelerometer behavior
@interface UIAccelerometer (Simulation)
+ (UIAccelerometer *)sharedAccelerometer;
@end

// our own version of the Accelerometer
@interface CCAccelerometerSimulation : UIAccelerometer <NSMachPortDelegate>
{
    
    //CFSocketRef udpSocket;
    int udpSocket;
    NSThread *thread;
    BOOL isExiting;
    id<UIAccelerometerDelegate> accelDelegate;
    UIAccelerationSimulation *accObject;
    // Threaded notification support 
    NSMutableArray *notifications;
    NSThread *notificationThread;
    NSLock *notificationLock;
    NSMachPort *notificationPort;
}

@property(nonatomic, assign) id<UIAccelerometerDelegate> delegate;

- (void) setUpThreadingSupport;
- (void) handleMachMessage:(void *) msg;
- (void) processNotification:(NSNotification *) notification;
+ (CCAccelerometerSimulation *)getAccelerometer;
- (CCAccelerometerSimulation *)initialize;

@end

#endif
