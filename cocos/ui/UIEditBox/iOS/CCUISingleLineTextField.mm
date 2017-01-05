/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2015 Mazyad Alabduljaleel
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "ui/UIEditBox/iOS/CCUISingleLineTextField.h"
#import "ui/UIEditBox/iOS/CCUITextInput.h"

#include "base/CCDirector.h"

/**
 * http://stackoverflow.com/questions/18244790/changing-uitextfield-placeholder-font
 */


@implementation CCUISingleLineTextField

#pragma mark - Init & Dealloc

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _placeholderDefinition = [[NSMutableDictionary alloc]
                                  initWithObjectsAndKeys:
                                  self.font, NSFontAttributeName,
                                  [UIColor lightGrayColor], NSForegroundColorAttributeName, nil];
    }
    return self;
}

#pragma mark - Properties

- (UIColor *)placeholderTextColor
{
    return [_placeholderDefinition objectForKey:NSForegroundColorAttributeName];
}

- (UIFont *)placeholderFont
{
    return [_placeholderDefinition objectForKey:NSFontAttributeName];
}

-(void)setPlaceholderFont:(UIFont *)placeholderFont
{
    [_placeholderDefinition setObject:placeholderFont forKey:NSFontAttributeName];
}

-(void)setPlaceholderTextColor:(UIColor *)placeholderTextColor
{
    [_placeholderDefinition setObject:placeholderTextColor forKey:NSForegroundColorAttributeName];
}

#pragma mark - Public methods

- (void)drawPlaceholderInRect:(CGRect)rect {
        // center vertically
        CGSize textSize = [self.placeholder sizeWithAttributes:_placeholderDefinition];
        CGFloat hdif = rect.size.height - textSize.height;
        hdif = MAX(0, hdif);
        rect.origin.y += ceil(hdif/2.0);
        
        [[self placeholder] drawInRect:rect withAttributes:_placeholderDefinition];
}

- (CGRect)textRectForBounds:(CGRect)bounds
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    
    float padding = CC_EDIT_BOX_PADDING * glview->getScaleX() / glview->getContentScaleFactor();
    return CGRectInset(bounds, padding, padding);
}

- (CGRect)editingRectForBounds:(CGRect)bounds
{
    return [self textRectForBounds:bounds];
}

@end
