//
//  CCDirectorCaller.h
//  HelloWorld
//
//  Created by Walzer on 10-11-11.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>

@interface CCDirectorCaller : NSObject {
	id displayLink;
}
-(void) startMainLoop;
-(void) doCaller: (id) sender;
+(id) sharedDirectorCaller;
+(void) destroy;
@end
