#include "CCDevice.h"
#include "ccTypes.h"
#include "CCEventDispatcher.h"
#include "CCEventAcceleration.h"
#include "CCDirector.h"
#import <UIKit/UIKit.h>

// Accelerometer
#import<CoreMotion/CoreMotion.h>
#import<CoreFoundation/CoreFoundation.h>

@interface CCAccelerometerDispatcher : NSObject<UIAccelerometerDelegate>
{
    cocos2d::Acceleration *_acceleration;
    CMMotionManager *_motionManager;
}

+ (id) sharedAccelerometerDispather;
- (id) init;
- (void) setAccelerometerEnabled: (bool) isEnabled;
- (void) setAccelerometerInterval:(float) interval;

@end

@implementation CCAccelerometerDispatcher

static CCAccelerometerDispatcher* s_pAccelerometerDispatcher;

+ (id) sharedAccelerometerDispather
{
    if (s_pAccelerometerDispatcher == nil) {
        s_pAccelerometerDispatcher = [[self alloc] init];
    }
    
    return s_pAccelerometerDispatcher;
}

- (id) init
{
    if( (self = [super init]) ) {
        _acceleration = new cocos2d::Acceleration();
        _motionManager = [[CMMotionManager alloc] init];
    }
    return self;
}

- (void) dealloc
{
    s_pAccelerometerDispatcher = nullptr;
    delete _acceleration;
    [_motionManager release];
    [super dealloc];
}

- (void) setAccelerometerEnabled: (bool) isEnabled
{
    if (isEnabled)
    {
        [_motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue] withHandler:^(CMAccelerometerData *accelerometerData, NSError *error) {
            [self accelerometer:accelerometerData];
        }];
    }
    else
    {
        [_motionManager stopAccelerometerUpdates];
    }
}

-(void) setAccelerometerInterval:(float)interval
{
    _motionManager.accelerometerUpdateInterval = interval;
}

- (void)accelerometer:(CMAccelerometerData *)accelerometerData
{
    _acceleration->x = accelerometerData.acceleration.x;
    _acceleration->y = accelerometerData.acceleration.y;
    _acceleration->z = accelerometerData.acceleration.z;
    _acceleration->timestamp = accelerometerData.timestamp;
    
    double tmp = _acceleration->x;
    
    switch ([[UIApplication sharedApplication] statusBarOrientation])
    {
        case UIInterfaceOrientationLandscapeRight:
            _acceleration->x = -_acceleration->y;
            _acceleration->y = tmp;
            break;
            
        case UIInterfaceOrientationLandscapeLeft:
            _acceleration->x = _acceleration->y;
            _acceleration->y = -tmp;
            break;
            
        case UIInterfaceOrientationPortraitUpsideDown:
            _acceleration->x = -_acceleration->y;
            _acceleration->y = -tmp;
            break;
            
        case UIInterfaceOrientationPortrait:
            break;
    }

    cocos2d::EventAcceleration event(*_acceleration);
    auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchEvent(&event);
}

@end

//

NS_CC_BEGIN

int Device::getDPI()
{
    static int dpi = -1;

    if (dpi == -1)
    {
        float scale = 1.0f;
        
        if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
            scale = [[UIScreen mainScreen] scale];
        }
        
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
            dpi = 132 * scale;
        } else if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
            dpi = 163 * scale;
        } else {
            dpi = 160 * scale;
        }
    }
    return dpi;
}




void Device::setAccelerometerEnabled(bool isEnabled)
{
    [[CCAccelerometerDispatcher sharedAccelerometerDispather] setAccelerometerEnabled:isEnabled];
}

void Device::setAccelerometerInterval(float interval)
{
    [[CCAccelerometerDispatcher sharedAccelerometerDispather] setAccelerometerInterval:interval];
}


NS_CC_END
