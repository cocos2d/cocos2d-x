/****************************************************************************
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

#ifndef cocos2d_libs_CCUITextInput_h
#define cocos2d_libs_CCUITextInput_h

static const int CC_EDIT_BOX_PADDING = 5;

/**
    This protocol provides a common interface for consolidating text input method calls
 */
@protocol CCUITextInput <NSObject>

@property (nonatomic, retain, setter=ccui_setText:) NSString *ccui_text;
@property (nonatomic, retain, setter=ccui_setPlaceholder:) NSString *ccui_placeholder;
@property (nonatomic, retain, setter=ccui_setPlaceholderLabel:) UILabel *ccui_placeholderLabel;
@property (nonatomic, retain, setter=ccui_setTextColor:) UIColor *ccui_textColor;
@property (nonatomic, retain, setter=ccui_setFont:) UIFont *ccui_font;
@property (nonatomic, assign, setter=ccui_setSecureTextEntry:) BOOL ccui_secureTextEntry;
@property (nonatomic, assign, setter=ccui_setTextHorizontalAlignment:) NSTextAlignment ccui_alignment;

/* can only set. and not get, since the getter will only return one delegate implementation */
- (void)ccui_setDelegate:(id<UITextFieldDelegate, UITextViewDelegate>)delegate;

@end

#endif
