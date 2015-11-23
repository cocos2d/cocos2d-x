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

#import "CCUISingleLineTextField.h"
#import "CCUITextInput.h"

@implementation CCUISingleLineTextField

- (CGRect)textRectForBounds:(CGRect)bounds
{
    if (!_leftPadding) {
        _leftPadding = _topPadding = _rightPadding = _bottomPadding = 0.0;
    }
    
    return CGRectMake(bounds.origin.x + _leftPadding, bounds.origin.y + _topPadding,
                      bounds.size.width - _leftPadding - _rightPadding, bounds.size.height - _topPadding - _bottomPadding);
}

- (CGRect)editingRectForBounds:(CGRect)bounds
{
    return [self textRectForBounds:bounds];
}

- (void)setInnerPadding:(float)left :(float)top :(float)right :(float)bottom
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float factor = glview->getScaleX() / glview->getContentScaleFactor();
    
    _leftPadding = left * factor;
    _topPadding = top * factor;
    _rightPadding = right * factor;
    _bottomPadding = bottom * factor;
    
}

- (void)setTextAlignMent:(cocos2d::TextHAlignment)hAlign :(cocos2d::TextVAlignment)vAlign
{
    switch (hAlign) {
        case cocos2d::TextHAlignment::LEFT :
            [self setTextAlignment:NSTextAlignmentLeft];
            break;
        case cocos2d::TextHAlignment::CENTER :
            [self setTextAlignment:NSTextAlignmentCenter];
            break;
        case cocos2d::TextHAlignment::RIGHT :
            [self setTextAlignment:NSTextAlignmentRight];
            break;
        default:
            break;
    }
    
    switch (vAlign) {
        case cocos2d::TextVAlignment::TOP :
            self.contentVerticalAlignment = UIControlContentVerticalAlignmentTop;
            break;
        case cocos2d::TextVAlignment::CENTER :
            self.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
            break;
        case cocos2d::TextVAlignment::BOTTOM :
            self.contentVerticalAlignment = UIControlContentVerticalAlignmentBottom;
            break;
        default:
            break;
    }
    
}
@end
