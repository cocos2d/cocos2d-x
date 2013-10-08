#include "CCDevice.h"
#include "ccTypes.h"
#include "event_dispatcher/CCEventDispatcher.h"
#include "event_dispatcher/CCEventAcceleration.h"

#import <UIKit/UIKit.h>

// Accelerometer
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <functional>

@interface CCAccelerometerDispatcher : NSObject<UIAccelerometerDelegate>
{
    cocos2d::Acceleration *_acceleration;
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
    _acceleration = new cocos2d::Acceleration();
    return self;
}

- (void) dealloc
{
    s_pAccelerometerDispatcher = nullptr;
    delete _acceleration;
    [super dealloc];
}

- (void) setAccelerometerEnabled: (bool) isEnabled
{
    if (isEnabled)
    {
        [[UIAccelerometer sharedAccelerometer] setDelegate:self];
    }
    else
    {
        [[UIAccelerometer sharedAccelerometer] setDelegate:nil];
    }
}

-(void) setAccelerometerInterval:(float)interval
{
    [[UIAccelerometer sharedAccelerometer] setUpdateInterval:interval];
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    _acceleration->x = acceleration.x;
    _acceleration->y = acceleration.y;
    _acceleration->z = acceleration.z;
    _acceleration->timestamp = acceleration.timestamp;
    
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
    cocos2d::EventDispatcher::getInstance()->dispatchEvent(&event);
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
