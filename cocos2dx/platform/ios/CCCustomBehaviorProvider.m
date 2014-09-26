//
//  CCCustomBehaviorProvider.m
//  cocos2dx
//
//  Created by Jinwoo Baek on 9/25/14.
//  Copyright (c) 2014 cocos2d-x. All rights reserved.
//

#import "CCCustomBehaviorProvider.h"

@implementation CCCustomBehaviorProvider

+ (instancetype)sharedCustomBehaviorProvider;
{
    static CCCustomBehaviorProvider *sharedCustomBehaviorProvider = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedCustomBehaviorProvider = [[self alloc] init];
    });
    return sharedCustomBehaviorProvider;
}

@end
