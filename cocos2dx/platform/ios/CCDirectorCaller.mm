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
#import <Foundation/Foundation.h>
#import "CCDirectorCaller.h"
#import "CCDirector.h"

static id s_sharedDirectorCaller;

@interface NSObject(CADisplayLink)
+(id) displayLinkWithTarget: (id)arg1 selector:(SEL)arg2;
-(void) addToRunLoop: (id)arg1 forMode: (id)arg2;
-(void) setFrameInterval: (int)interval;
-(void) invalidate;
@end

@implementation CCDirectorCaller

@synthesize interval;

+(id) sharedDirectorCaller
{
    if (s_sharedDirectorCaller == nil)
    {
        s_sharedDirectorCaller = [CCDirectorCaller new];
    }
    
    return s_sharedDirectorCaller;
}

+(void) destroy
{
    [s_sharedDirectorCaller release];
}

-(void) alloc
{
        interval = 1;
}

-(void) dealloc
{
    [displayLink release];
    [super dealloc];
}

-(void) startMainLoop
{
        // CCDirector::setAnimationInterval() is called, we should invalidate it first
        [displayLink invalidate];
        displayLink = nil;
        
        displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
        [displayLink setFrameInterval: self.interval];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

-(void) setAnimationInterval:(double)intervalNew
{
        // CCDirector::setAnimationInterval() is called, we should invalidate it first
        [displayLink invalidate];
        displayLink = nil;
        
        self.interval = 60.0 * intervalNew;
        
        displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
        [displayLink setFrameInterval: self.interval];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}
                      
-(void) doCaller: (id) sender
{
    cocos2d::CCDirector::sharedDirector()->mainLoop();
}

@end
