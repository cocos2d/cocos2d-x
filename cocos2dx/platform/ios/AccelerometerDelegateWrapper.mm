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

#import "AccelerometerDelegateWrapper.h"

@implementation AccelerometerDispatcher

static AccelerometerDispatcher* s_pAccelerometerDispatcher;

@synthesize delegateWrappers;

+ (id) sharedAccelerometerDispather
{
    if (s_pAccelerometerDispatcher == nil) {
        s_pAccelerometerDispatcher = [[self alloc] init];
    }
    
    return s_pAccelerometerDispatcher;
}

- (id) init
{
    self.delegateWrappers = [NSMutableArray arrayWithCapacity:4];
    [[UIAccelerometer sharedAccelerometer] setDelegate: self];
    
    return self;
}

- (void) dealloc
{
    [[UIAccelerometer sharedAccelerometer] setDelegate: nil];
    [delegateWrappers release];
    [super dealloc];
}

- (id) findDelegateWrapperByDelegate: (cocos2d::CCAccelerometerDelegate *) delegate
{
    for (AccelerometerDelegateWrapper *wrapper in delegateWrappers) {
        if (wrapper.delegate_ == delegate) {
            return wrapper;
        }
    }
    
    return nil;
}

- (void) addDelegate: (cocos2d::CCAccelerometerDelegate *) delegate
{
    [delegateWrappers addObject: [AccelerometerDelegateWrapper delegateWrapperWithDelegate:delegate]];
}

- (void) removeDelegate: (cocos2d::CCAccelerometerDelegate *) delegate
{
    [delegateWrappers removeObject:[self findDelegateWrapperByDelegate:delegate]];
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    cocos2d::CCAcceleration accelerationCpp;
    
    accelerationCpp.x = acceleration.x;
    accelerationCpp.y = acceleration.y;
    accelerationCpp.z = acceleration.z;
    accelerationCpp.timestamp = acceleration.timestamp;
    
    double tmp = accelerationCpp.x;
    
    switch ([[UIApplication sharedApplication] statusBarOrientation]) 
    {
    case UIInterfaceOrientationLandscapeRight:
        accelerationCpp.x = -acceleration.y;
        accelerationCpp.y = tmp;
        break;
        
    case UIInterfaceOrientationLandscapeLeft:
        accelerationCpp.x = acceleration.y;
        accelerationCpp.y = -tmp;
        break;
        
    case UIInterfaceOrientationPortraitUpsideDown:
        accelerationCpp.x = -accelerationCpp.y;
        accelerationCpp.y = -tmp;
        break;
            
    case UIInterfaceOrientationPortrait:
        break;
    }
    
    for (AccelerometerDelegateWrapper *wrapper in delegateWrappers) {
        [wrapper didAccelerate: &accelerationCpp];
    }
}

@end


@implementation AccelerometerDelegateWrapper

@synthesize delegate_;

+ (id)delegateWrapperWithDelegate:(cocos2d::CCAccelerometerDelegate *)delegate
{
    return [[self alloc] initWithDelegate: delegate];
}

-  (id) initWithDelegate: (cocos2d::CCAccelerometerDelegate *)delegate
{
    delegate->AccelerometerKeep();
    self.delegate_ = delegate;
    
    return self;
}

-  (void) didAccelerate: (cocos2d::CCAcceleration *)acceleration
{
    self.delegate_->didAccelerate(acceleration);
}

-  (void) dealloc
{
    self.delegate_->AccelerometerDestroy();
    
    [super dealloc];
}

@end
