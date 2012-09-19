//
//  AccelerometerSimulation.m
//  AccelerometerGraph
//
//  Created by Otto Chrons on 9/26/08.
//  Copyright 2008 Seastringo Oy. All rights reserved.
//

#import "AccelerometerSimulation.h"

// when compiling to ARM (iPhone device), hide everything and use system defaults
// if you wish to use simulation mode even on the device, remove the #if/#endif
#if !TARGET_CPU_ARM

#import <netdb.h>

#define kAccelerometerSimulationPort 10552

@implementation UIAccelerationSimulation

@synthesize timestamp;
@synthesize x;
@synthesize y;
@synthesize z;

-(UIAccelerationSimulation*)initWithTimestamp:(NSTimeInterval)aTimeStamp
                                            X:(UIAccelerationValue)ax
                                            Y:(UIAccelerationValue)ay
                                            Z:(UIAccelerationValue)az 
{
    timestamp = aTimeStamp;
    x = ax;
    y = ay;
    z = az;
    
    return self;
}    
@end

@implementation UIAccelerometer (Simulation)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-protocol-method-implementation"
// override the static method and return our simulated version instead
+ (UIAccelerometer *)sharedAccelerometer
{
    return [AccelerometerSimulation getAccelerometer];
}
#pragma clang diagnostic pop
@end
/*
 // callback that never got called with CFSocket UDP...
 
 void mySocketCallBack( CFSocketRef s,
 CFSocketCallBackType callbackType,
 CFDataRef address,
 const void *data,
 void *info)
 {
 AccelerometerSimulation *accSim = (AccelerometerSimulation*)info;
 
 NSLog(@"Data %s received", (char*)data);
 }
 */

// singleton
static AccelerometerSimulation *sharedAccelerometer = NULL;

@implementation AccelerometerSimulation

- (void) dealloc {
    if (sharedAccelerometer) {
        [sharedAccelerometer release];
        sharedAccelerometer = NULL;
    }
    [super dealloc];
}

// this is straight from developer guide example for multi-threaded notifications
- (void) setUpThreadingSupport {
    if ( notifications ) return;
    
    notifications      = [[NSMutableArray alloc] init];
    notificationLock   = [[NSLock alloc] init];
    notificationThread = [[NSThread currentThread] retain];
    
    notificationPort = [[NSMachPort alloc] init];
    [notificationPort setDelegate:self];
    [[NSRunLoop currentRunLoop] addPort:notificationPort
                                forMode:(NSString *) kCFRunLoopCommonModes];
}

// this is straight from developer guide example

- (void) processNotification:(NSNotification *) notification {
    if( [NSThread currentThread] != notificationThread ) {
        // Forward the notification to the correct thread, this is the socket thread
        NSDate* date = [[NSDate alloc] init];
        [notificationLock lock];
        [notifications addObject:notification];
        [notificationLock unlock];
        [notificationPort sendBeforeDate:date
                              components:nil
                                    from:nil
                                reserved:0];
        [date release];
    }
    else {
        // now we are in the main thread
        // Process the notification here;
        NSString *data = (NSString*)[notification object];
        
        // parse the data, no error handling!
        NSArray *components = [data componentsSeparatedByString:@","];
        
        // create our own acceleration object
        [accObject initWithTimestamp:[[components objectAtIndex:1] doubleValue] 
                                   X:[[components objectAtIndex:2] doubleValue] 
                                   Y:[[components objectAtIndex:3] doubleValue]
                                   Z:[[components objectAtIndex:4] doubleValue]];
        [accelDelegate accelerometer:self didAccelerate:(UIAcceleration*)accObject];
    }
}

// this is straight from developer guide example
- (void) handleMachMessage:(void *) msg {
    [notificationLock lock];
    while ( [notifications count] ) {
        NSNotification *notification = [[notifications objectAtIndex:0] retain];
        [notifications removeObjectAtIndex:0];
        [notificationLock unlock];
        [self processNotification:notification];
        [notification release];
        [notificationLock lock];
    };
    [notificationLock unlock];
}
#ifndef __clang_analyzer__
+ (AccelerometerSimulation *)getAccelerometer
{
    if( sharedAccelerometer == NULL )
        sharedAccelerometer = [[AccelerometerSimulation alloc] initialize];
    
    return sharedAccelerometer;
}
#endif
- (void)threadLoop:(id)object
{
    char buffer[1024];
    // we never exit...
    while(1) {
        int count = recv( udpSocket, buffer, sizeof(buffer), 0 );
        if( count > 0 )
        {
            // got data, let's pass it on
            buffer[count] = 0;
            NSString *str = [[NSString alloc] initWithUTF8String:buffer];
            [[NSNotificationCenter defaultCenter]  postNotificationName:@"ThreadAccelNotification" object:str];
            [str release];
        }
        
    }
}

// initialize our version of the accelerometer
- (AccelerometerSimulation *)initialize
{
    accObject = [UIAccelerationSimulation alloc];
    isExiting = false;
    
    // couldn't get the CFSocket version to work with UDP and runloop, so used Berkeley sockets and a thread instead
    
    udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    // listen on all interfaces
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_len = sizeof(struct sockaddr_in);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(kAccelerometerSimulationPort);
    
    bind(udpSocket, (const struct sockaddr*)&sin, sizeof(sin));
    
    // create a separate thread for receiving UDP packets
    thread = [[NSThread alloc] initWithTarget:self
                                     selector:@selector(threadLoop:)
                                       object:nil];
    [thread start];    
    
    // cross-thread communication setup
    [self setUpThreadingSupport];
    [[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(processNotification:)
     name:@"ThreadAccelNotification"
     object:nil];
    /*
     // create and initialize a socket
     CFSocketContext ctx;
     
     ctx.info = self;
     ctx.version = 0;
     ctx.retain = NULL;
     ctx.release = NULL;
     ctx.copyDescription = NULL;
     udpSocket = CFSocketCreate(NULL, PF_INET, SOCK_DGRAM, IPPROTO_UDP, kCFSocketDataCallBack | 0xF, mySocketCallBack, NULL);
     
     CFRunLoopSourceRef source;
     CFDataRef addr;
     CFSocketError theErr;
     struct sockaddr_in sin;
     memset(&sin, 0, sizeof(sin));
     sin.sin_addr.s_addr = INADDR_ANY;
     sin.sin_len = sizeof(struct sockaddr_in);
     sin.sin_family = AF_INET;
     sin.sin_port = htons(10552);
     addr = CFDataCreate(NULL, (unsigned char *)&sin, sizeof(sin));
     theErr = CFSocketConnectToAddress(udpSocket, addr, 0);
     switch (theErr) {
     case kCFSocketSuccess:
     NSLog(@"UDP Logged in");
     source = CFSocketCreateRunLoopSource(NULL, udpSocket, 0);
     CFRunLoopAddSource(CFRunLoopGetMain(), source, 
     kCFRunLoopDefaultMode);
     break;
     case kCFSocketError:
     NSLog(@"UDP Error");
     break;
     default:
     NSLog(@"UDP Networking Error");
     break;
     }
     */
    return self;
}

// we grab the delegate setting action
- (void)setDelegate:(id<UIAccelerometerDelegate>)delegate
{
    accelDelegate = delegate;
}

- (id<UIAccelerometerDelegate>)delegate
{
    return accelDelegate;
}
@end

#endif
