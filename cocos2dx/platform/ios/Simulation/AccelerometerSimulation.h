/*
 *  AccelerometerSimulation.h
 *  AccelerometerGraph
 *
 *  Created by Otto Chrons on 9/26/08.
 *  Copyright 2008 Seastringo Oy. All rights reserved.
 *
 */
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

// override UIAccelerometer behaviour
@interface UIAccelerometer (Simulation)
+ (UIAccelerometer *)sharedAccelerometer;
@end

// our own version of the Accelerometer
@interface AccelerometerSimulation : UIAccelerometer <NSMachPortDelegate>
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
+ (AccelerometerSimulation *)getAccelerometer;
- (AccelerometerSimulation *)initialize;

@end

#endif
