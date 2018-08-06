/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2015 Mazyad Alabduljaleel
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#import "ui/UIEditBox/iOS/CCUIMultilineTextField.h"

#include "base/CCDirector.h"

/**
 * http://stackoverflow.com/questions/1328638/placeholder-in-uitextview
 */
CGFloat const UI_PLACEHOLDER_TEXT_CHANGED_ANIMATION_DURATION = 0.25;


@implementation CCUIMultilineTextField

#pragma mark - Init & Dealloc

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(textChanged:)
                                                     name:UITextViewTextDidChangeNotification
                                                   object:nil];
    }
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [_placeHolderLabel release];
    
    [super dealloc];
}

#pragma mark - Properties

- (NSString *)placeholder
{
    return self.placeHolderLabel.text;
}

- (void)setPlaceholder:(NSString *)placeholder
{
    self.placeHolderLabel.text = placeholder;
    [self.placeHolderLabel sizeToFit];
}

- (void)setText:(NSString *)text
{
    [super setText:text];
    [self textChanged:nil];
}

- (UILabel *)placeHolderLabel
{
    if (_placeHolderLabel == nil) {
        auto glview = cocos2d::Director::getInstance()->getOpenGLView();
        float padding = CC_EDIT_BOX_PADDING * glview->getScaleX() / glview->getContentScaleFactor();

        _placeHolderLabel = [[UILabel alloc] initWithFrame:CGRectMake(padding,
                                                                      padding,
                                                                      self.bounds.size.width - padding * 2,
                                                                      0)];
        _placeHolderLabel.lineBreakMode = NSLineBreakByWordWrapping;
        _placeHolderLabel.numberOfLines = 0;
        _placeHolderLabel.font = self.font;
        _placeHolderLabel.backgroundColor = [UIColor clearColor];
        _placeHolderLabel.textColor = [UIColor lightGrayColor];
        _placeHolderLabel.alpha = 0;
        
        [self addSubview:_placeHolderLabel];
    }
    
    return _placeHolderLabel;
}

#pragma mark - Public methods

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

- (void)layoutSubviews
{
    [super layoutSubviews];
    
    if (self.placeholder.length > 0) {
        [self sendSubviewToBack:self.placeHolderLabel];
    }
}

- (void)drawRect:(CGRect)rect
{
    if (self.text.length == 0 && self.placeholder.length > 0) {
        self.placeHolderLabel.alpha = 1;
    }
    
    [super drawRect:rect];
}

#pragma mark - NSNotification Observers

- (void)textChanged:(NSNotification *)notification
{
    if (self.placeholder.length == 0) {
        return;
    }
    
    [UIView animateWithDuration:UI_PLACEHOLDER_TEXT_CHANGED_ANIMATION_DURATION animations:^{
        
        CGFloat alpha = (self.text.length == 0 ? 1 : 0);
        self.placeHolderLabel.alpha = alpha;
    }];
}

@end
