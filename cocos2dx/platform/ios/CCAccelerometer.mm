/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
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

#include "CCAccelerometer.h"

#import <Foundation/Foundation.h>
#import "CCAccelerometerDelegate.h"
#import <UIKit/UIKit.h>
#import <functional>

@interface CCAccelerometerDispatcher : NSObject<UIAccelerometerDelegate>
{
    std::function<void(cocos2d::Acceleration*)> _function;
    cocos2d::Acceleration *_acceleration;
}

+ (id) sharedAccelerometerDispather;
- (id) init;
- (void) addDelegate: (std::function<void(cocos2d::Acceleration*)>) function;
- (void) setAccelerometerInterval:(float)interval;

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
    _function = nullptr;
    delete _acceleration;
    [super dealloc];
}

- (void) addDelegate: (std::function<void(cocos2d::Acceleration*)>) function
{
    _function = function;
    
    if (_function)
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
    if (! _function)
    {
        return;
    }
    
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
    
    _function(_acceleration);
}

@end

/** Implementation of Accelerometer
 */

NS_CC_BEGIN


Accelerometer::Accelerometer() {}

Accelerometer::~Accelerometer() {}

void Accelerometer::setDelegate(std::function<void (Acceleration *)> function)
{
    [[CCAccelerometerDispatcher sharedAccelerometerDispather] addDelegate:function];
}

void Accelerometer::setAccelerometerInterval(float interval)
{
    [[CCAccelerometerDispatcher sharedAccelerometerDispather] setAccelerometerInterval:interval];
}

NS_CC_END
