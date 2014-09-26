//
//  CCCustomDynamicLineBreaking.h
//  cocos2dx
//
//  Created by Jinwoo Baek on 9/25/14.
//  Copyright (c) 2014 cocos2d-x. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol CCCustomDynamicLineBreaking <NSObject>

@property (copy, nonatomic) NSString *textWithDynamicLineBreakIndicators;
@property (copy, nonatomic) UIFont *font;

- (NSString *)dynamicLineBreakWithLabelWidth:(CGFloat)labelWidth;

@end
