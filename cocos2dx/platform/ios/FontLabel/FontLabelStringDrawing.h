//
//  FontLabelStringDrawing.h
//  FontLabel
//
//  Created by Kevin Ballard on 5/5/09.
//  Copyright © 2009 Zynga Game Networks
//  Copyright (c) 2011 cocos2d-x.org
//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#import <UIKit/UIKit.h>
#import "ZAttributedString.h"

@class ZFont;

@interface NSString (FontLabelStringDrawing)
// CGFontRef-based methods
- (CGSize)sizeWithCGFont:(CGFontRef)font pointSize:(CGFloat)pointSize __AVAILABILITY_INTERNAL_DEPRECATED;
- (CGSize)sizeWithCGFont:(CGFontRef)font pointSize:(CGFloat)pointSize constrainedToSize:(CGSize)size __AVAILABILITY_INTERNAL_DEPRECATED;
- (CGSize)sizeWithCGFont:(CGFontRef)font pointSize:(CGFloat)pointSize constrainedToSize:(CGSize)size
		   lineBreakMode:(UILineBreakMode)lineBreakMode __AVAILABILITY_INTERNAL_DEPRECATED;
- (CGSize)drawAtPoint:(CGPoint)point withCGFont:(CGFontRef)font pointSize:(CGFloat)pointSize __AVAILABILITY_INTERNAL_DEPRECATED;
- (CGSize)drawInRect:(CGRect)rect withCGFont:(CGFontRef)font pointSize:(CGFloat)pointSize __AVAILABILITY_INTERNAL_DEPRECATED;
- (CGSize)drawInRect:(CGRect)rect withCGFont:(CGFontRef)font pointSize:(CGFloat)pointSize
	   lineBreakMode:(UILineBreakMode)lineBreakMode __AVAILABILITY_INTERNAL_DEPRECATED;
- (CGSize)drawInRect:(CGRect)rect withCGFont:(CGFontRef)font pointSize:(CGFloat)pointSize
	   lineBreakMode:(UILineBreakMode)lineBreakMode alignment:(UITextAlignment)alignment __AVAILABILITY_INTERNAL_DEPRECATED;

// ZFont-based methods
- (CGSize)sizeWithZFont:(ZFont *)font;
- (CGSize)sizeWithZFont:(ZFont *)font constrainedToSize:(CGSize)size;
- (CGSize)sizeWithZFont:(ZFont *)font constrainedToSize:(CGSize)size lineBreakMode:(UILineBreakMode)lineBreakMode;
- (CGSize)sizeWithZFont:(ZFont *)font constrainedToSize:(CGSize)size lineBreakMode:(UILineBreakMode)lineBreakMode
		  numberOfLines:(NSUInteger)numberOfLines;
- (CGSize)drawAtPoint:(CGPoint)point withZFont:(ZFont *)font;
- (CGSize)drawAtPoint:(CGPoint)point forWidth:(CGFloat)width withZFont:(ZFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode;
- (CGSize)drawInRect:(CGRect)rect withZFont:(ZFont *)font;
- (CGSize)drawInRect:(CGRect)rect withZFont:(ZFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode;
- (CGSize)drawInRect:(CGRect)rect withZFont:(ZFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode
		   alignment:(UITextAlignment)alignment;
- (CGSize)drawInRect:(CGRect)rect withZFont:(ZFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode
		   alignment:(UITextAlignment)alignment numberOfLines:(NSUInteger)numberOfLines;
@end

@interface ZAttributedString (ZAttributedStringDrawing)
- (CGSize)size;
- (CGSize)sizeConstrainedToSize:(CGSize)size;
- (CGSize)sizeConstrainedToSize:(CGSize)size lineBreakMode:(UILineBreakMode)lineBreakMode;
- (CGSize)sizeConstrainedToSize:(CGSize)size lineBreakMode:(UILineBreakMode)lineBreakMode
				  numberOfLines:(NSUInteger)numberOfLines;
- (CGSize)drawAtPoint:(CGPoint)point;
- (CGSize)drawAtPoint:(CGPoint)point forWidth:(CGFloat)width lineBreakMode:(UILineBreakMode)lineBreakMode;
- (CGSize)drawInRect:(CGRect)rect;
- (CGSize)drawInRect:(CGRect)rect withLineBreakMode:(UILineBreakMode)lineBreakMode;
- (CGSize)drawInRect:(CGRect)rect withLineBreakMode:(UILineBreakMode)lineBreakMode alignment:(UITextAlignment)alignment;
- (CGSize)drawInRect:(CGRect)rect withLineBreakMode:(UILineBreakMode)lineBreakMode alignment:(UITextAlignment)alignment
	   numberOfLines:(NSUInteger)numberOfLines;
@end

// This class is used to invoke in .mm file.
// Can not invoke FontLabelStringDrawing directly in .mm.
// It seems that, in .mm it can not support category.
@interface FontLabelStringDrawingHelper : NSObject {
}
+ (CGSize)sizeWithZFont:(NSString*)string zfont:(ZFont *)font;
+ (CGSize)sizeWithZFont:(NSString *)string zfont:(ZFont *)font constrainedToSize:(CGSize)size;
+ (CGSize)drawInRect:(NSString*)string rect:(CGRect)rect withZFont:(ZFont *)font 
       lineBreakMode:(UILineBreakMode)lineBreakMode 
           alignment:(UITextAlignment)alignment;
@end
