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

- (NSString *)customDynamicLineBreakWithString:(NSString *)string font:(UIFont *)font textWidth:(CGFloat)textWidth;

@end
