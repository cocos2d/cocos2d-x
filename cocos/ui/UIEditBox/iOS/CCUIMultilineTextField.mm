//
//  CCUIMultilineTextField.m
//  cocos2d_libs
//
//  Created by Mazyad Alabduljaleel on 9/15/15.
//
//

#import "CCUIMultilineTextField.h"

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
        
        _placeHolderLabel = [[UILabel alloc] initWithFrame:CGRectMake(8,8,self.bounds.size.width - 16,0)];
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
