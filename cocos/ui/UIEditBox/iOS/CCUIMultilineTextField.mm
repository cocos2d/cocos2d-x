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

#import "CCUIMultilineTextField.h"

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
        [self addObserver:self forKeyPath:@"contentSize" options:(NSKeyValueObservingOptionNew) context:NULL];
    }
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [self removeObserver:self forKeyPath:@"contentSize"];
    
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
        
        _placeHolderLabel = [[UILabel alloc] initWithFrame:CGRectMake(0,0,self.bounds.size.width,0)];
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
    return bounds;
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

- (void)setInnerPadding:(float)left :(float)top :(float)right :(float)bottom
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float factor = glview->getScaleX() / glview->getContentScaleFactor();
    self.textContainerInset = UIEdgeInsetsMake(top * factor, left * factor, bottom * factor, right * factor);
    
    CGRect frame = _placeHolderLabel.frame;
    frame.origin.x = left * factor;
    frame.origin.y = top * factor;
    frame.size.width = self.bounds.size.width - (left * factor) - (right * factor);
    _placeHolderLabel.frame = frame;
    
}

- (void)setTextAlignment:(cocos2d::TextHAlignment)hAlign :(cocos2d::TextVAlignment)vAlign
{
    switch (hAlign) {
        case cocos2d::TextHAlignment::LEFT :
            [self setTextAlignment:NSTextAlignmentLeft];
            [_placeHolderLabel setTextAlignment:NSTextAlignmentLeft];
            break;
        case cocos2d::TextHAlignment::CENTER :
            [self setTextAlignment:NSTextAlignmentCenter];
            [_placeHolderLabel setTextAlignment:NSTextAlignmentCenter];
            break;
        case cocos2d::TextHAlignment::RIGHT :
            [self setTextAlignment:NSTextAlignmentRight];
            [_placeHolderLabel setTextAlignment:NSTextAlignmentRight];
            break;
        default:
            break;
    }
    
    _verticalAlign = vAlign;
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

-(void)observeValueForKeyPath:(NSString *)keyPath   ofObject:(id)object   change:(NSDictionary *)change   context:(void *)context {
    
    UITextView *tv = object;
    CGFloat topCorrect;
    
    switch (_verticalAlign) {
        case cocos2d::TextVAlignment::TOP :
            topCorrect = 0;
            break;
        case cocos2d::TextVAlignment::CENTER :
            topCorrect = ([tv bounds].size.height - [tv contentSize].height * [tv zoomScale])  / 2.0;
            break;
        case cocos2d::TextVAlignment::BOTTOM :
            topCorrect = [tv bounds].size.height - [tv contentSize].height;
            break;
        default:
            break;
    }
    
    topCorrect = ( topCorrect < 0.0 ? 0.0 : topCorrect );
    [tv setContentInset:UIEdgeInsetsMake(topCorrect,0,0,0)];
}
@end
