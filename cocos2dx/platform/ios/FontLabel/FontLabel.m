//
//  FontLabel.m
//  FontLabel
//
//  Created by Kevin Ballard on 5/8/09.
//  Copyright © 2009 Zynga Game Networks
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

#import "FontLabel.h"
#import "FontManager.h"
#import "FontLabelStringDrawing.h"
#import "ZFont.h"

@interface ZFont (ZFontPrivate)
@property (nonatomic, readonly) CGFloat ratio;
@end

@implementation FontLabel
@synthesize zFont;
@synthesize zAttributedText;

- (id)initWithFrame:(CGRect)frame fontName:(NSString *)fontName pointSize:(CGFloat)pointSize {
	return [self initWithFrame:frame zFont:[[FontManager sharedManager] zFontWithName:fontName pointSize:pointSize]];
}

- (id)initWithFrame:(CGRect)frame zFont:(ZFont *)font {
	if ((self = [super initWithFrame:frame])) {
		zFont = [font retain];
	}
	return self;
}

- (id)initWithFrame:(CGRect)frame font:(CGFontRef)font pointSize:(CGFloat)pointSize {
	return [self initWithFrame:frame zFont:[ZFont fontWithCGFont:font size:pointSize]];
}

- (CGFontRef)cgFont {
	return self.zFont.cgFont;
}

- (void)setCGFont:(CGFontRef)font {
	if (self.zFont.cgFont != font) {
		self.zFont = [ZFont fontWithCGFont:font size:self.zFont.pointSize];
	}
}

- (CGFloat)pointSize {
	return self.zFont.pointSize;
}

- (void)setPointSize:(CGFloat)pointSize {
	if (self.zFont.pointSize != pointSize) {
		self.zFont = [ZFont fontWithCGFont:self.zFont.cgFont size:pointSize];
	}
}

- (void)setZAttributedText:(ZAttributedString *)attStr {
	if (zAttributedText != attStr) {
		[zAttributedText release];
		zAttributedText = [attStr copy];
		[self setNeedsDisplay];
	}
}

- (void)drawTextInRect:(CGRect)rect {
	if (self.zFont == NULL && self.zAttributedText == nil) {
		[super drawTextInRect:rect];
		return;
	}
	
	if (self.zAttributedText == nil) {
		// this method is documented as setting the text color for us, but that doesn't appear to be the case
		if (self.highlighted) {
			[(self.highlightedTextColor ?: [UIColor whiteColor]) setFill];
		} else {
			[(self.textColor ?: [UIColor blackColor]) setFill];
		}
		
		ZFont *actualFont = self.zFont;
		CGSize origSize = rect.size;
		if (self.numberOfLines == 1) {
			origSize.height = actualFont.leading;
			CGPoint point = CGPointMake(rect.origin.x,
										rect.origin.y + roundf(((rect.size.height - actualFont.leading) / 2.0f)));
			CGSize size = [self.text sizeWithZFont:actualFont];
			if (self.adjustsFontSizeToFitWidth && self.minimumFontSize < actualFont.pointSize) {
				if (size.width > origSize.width) {
					CGFloat desiredRatio = (origSize.width * actualFont.ratio) / size.width;
					CGFloat desiredPointSize = desiredRatio * actualFont.pointSize / actualFont.ratio;
					actualFont = [actualFont fontWithSize:MAX(MAX(desiredPointSize, self.minimumFontSize), 1.0f)];
					size = [self.text sizeWithZFont:actualFont];
				}
				if (!CGSizeEqualToSize(origSize, size)) {
					switch (self.baselineAdjustment) {
						case UIBaselineAdjustmentAlignCenters:
							point.y += roundf((origSize.height - size.height) / 2.0f);
							break;
						case UIBaselineAdjustmentAlignBaselines:
							point.y += (self.zFont.ascender - actualFont.ascender);
							break;
						case UIBaselineAdjustmentNone:
							break;
					}
				}
			}
			size.width = MIN(size.width, origSize.width);
			// adjust the point for alignment
			switch (self.textAlignment) {
				case UITextAlignmentLeft:
					break;
				case UITextAlignmentCenter:
					point.x += (origSize.width - size.width) / 2.0f;
					break;
				case UITextAlignmentRight:
					point.x += origSize.width - size.width;
					break;
			}
			[self.text drawAtPoint:point forWidth:size.width withZFont:actualFont lineBreakMode:self.lineBreakMode];
		} else {
			CGSize size = [self.text sizeWithZFont:actualFont constrainedToSize:origSize lineBreakMode:self.lineBreakMode numberOfLines:self.numberOfLines];
			CGPoint point = rect.origin;
			point.y += roundf((rect.size.height - size.height) / 2.0f);
			rect = (CGRect){point, CGSizeMake(rect.size.width, size.height)};
			[self.text drawInRect:rect withZFont:actualFont lineBreakMode:self.lineBreakMode alignment:self.textAlignment numberOfLines:self.numberOfLines];
		}
	} else {
		ZAttributedString *attStr = self.zAttributedText;
		if (self.highlighted) {
			// modify the string to change the base color
			ZMutableAttributedString *mutStr = [[attStr mutableCopy] autorelease];
			NSRange activeRange = NSMakeRange(0, attStr.length);
			while (activeRange.length > 0) {
				NSRange effective;
				UIColor *color = [attStr attribute:ZForegroundColorAttributeName atIndex:activeRange.location
							 longestEffectiveRange:&effective inRange:activeRange];
				if (color == nil) {
					[mutStr addAttribute:ZForegroundColorAttributeName value:[UIColor whiteColor] range:effective];
				}
				activeRange.location += effective.length, activeRange.length -= effective.length;
			}
			attStr = mutStr;
		}
		CGSize size = [attStr sizeConstrainedToSize:rect.size lineBreakMode:self.lineBreakMode numberOfLines:self.numberOfLines];
		CGPoint point = rect.origin;
		point.y += roundf((rect.size.height - size.height) / 2.0f);
		rect = (CGRect){point, CGSizeMake(rect.size.width, size.height)};
		[attStr drawInRect:rect withLineBreakMode:self.lineBreakMode alignment:self.textAlignment numberOfLines:self.numberOfLines];
	}
}

- (CGRect)textRectForBounds:(CGRect)bounds limitedToNumberOfLines:(NSInteger)numberOfLines {
	if (self.zFont == NULL && self.zAttributedText == nil) {
		return [super textRectForBounds:bounds limitedToNumberOfLines:numberOfLines];
	}
	
	if (numberOfLines == 1) {
		// if numberOfLines == 1 we need to use the version that converts spaces
		CGSize size;
		if (self.zAttributedText == nil) {
			size = [self.text sizeWithZFont:self.zFont];
		} else {
			size = [self.zAttributedText size];
		}
		bounds.size.width = MIN(bounds.size.width, size.width);
		bounds.size.height = MIN(bounds.size.height, size.height);
	} else {
		if (numberOfLines > 0) bounds.size.height = MIN(bounds.size.height, self.zFont.leading * numberOfLines);
		if (self.zAttributedText == nil) {
			bounds.size = [self.text sizeWithZFont:self.zFont constrainedToSize:bounds.size lineBreakMode:self.lineBreakMode];
		} else {
			bounds.size = [self.zAttributedText sizeConstrainedToSize:bounds.size lineBreakMode:self.lineBreakMode];
		}
	}
	return bounds;
}

- (void)dealloc {
	[zFont release];
	[zAttributedText release];
	[super dealloc];
}
@end
