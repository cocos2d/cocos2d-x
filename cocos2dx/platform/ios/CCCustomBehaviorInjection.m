//
//  CCCustomBehaviorInjection.m
//  cocos2dx
//
//  Created by Jinwoo Baek on 9/25/14.
//  Copyright (c) 2014 cocos2d-x. All rights reserved.
//

#import "CCCustomBehaviorInjection.h"

@implementation CCCustomBehaviorInjection

+ (instancetype)sharedCustomBehaviorInjection;
{
    static CCCustomBehaviorInjection *shareCustomBehaviorInjections = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        shareCustomBehaviorInjections = [[self alloc] init];
    });
    return shareCustomBehaviorInjections;
}

@end
