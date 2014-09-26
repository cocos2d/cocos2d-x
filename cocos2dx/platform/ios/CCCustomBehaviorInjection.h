//
//  CCCustomBehaviorInjection.h
//  cocos2dx
//
//  Created by Jinwoo Baek on 9/25/14.
//  Copyright (c) 2014 cocos2d-x. All rights reserved.
//

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#ifndef __CC_CUSTOM_BEHAVIOR_INJECTION_IOS_H__
#define __CC_CUSTOM_BEHAVIOR_INJECTION_IOS_H__

#import <Foundation/Foundation.h>
#import "CCCustomDynamicLineBreaking.h"

@interface CCCustomBehaviorInjection : NSObject

+ (instancetype)sharedCustomBehaviorInjection;

@property (strong, nonatomic) id<CCCustomDynamicLineBreaking> customDynamicLineBreak;

@end

//#endif
#endif