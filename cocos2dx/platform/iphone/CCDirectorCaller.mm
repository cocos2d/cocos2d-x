//
//  CCDirectorCaller.mm
//  HelloWorld
//
//  Created by Walzer on 10-11-11.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
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

-(void) dealloc
{
	[displayLink invalidate];
	[displayLink release];
	[super dealloc];
}

-(void) startMainLoop
{
	displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
	[displayLink setFrameInterval: 1];
	[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}
					  
-(void) doCaller: (id) sender
{
	cocos2d::CCDirector::getSharedDirector()->preMainLoop();
}

@end
