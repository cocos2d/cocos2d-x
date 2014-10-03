//
//  CCCustomBehaviorProvider.h
//  cocos2dx
//
//  Created by Jinwoo Baek on 9/25/14.
//  Copyright (c) 2014 cocos2d-x. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CCCustomDynamicLineBreaking.h"

@protocol CCCustomBehaviorProviding <NSObject>

+ (instancetype)sharedCustomBehaviorProvider;

@property (strong, nonatomic) id<CCCustomDynamicLineBreaking> customDynamicLineBreak;

@end

@interface CCCustomBehaviorProvider : NSObject <CCCustomBehaviorProviding>

@property (strong, nonatomic) id<CCCustomDynamicLineBreaking> customDynamicLineBreak;

@end