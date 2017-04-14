/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2013-2015 zilongshanren
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

#import <UIKit/UIKit.h>
#import "ui/UIEditBox/iOS/CCUITextInput.h"
#include "ui/UIEditBox/UIEditBoxImpl-ios.h"


@interface UIEditBoxImplIOS_objc : NSObject <UITextFieldDelegate, UITextViewDelegate>

@property (nonatomic, retain) UIView<UITextInput, CCUITextInput> *textInput;
@property (nonatomic, assign) void *editBox;
@property (nonatomic, assign) NSString *text;
@property (nonatomic, assign) CGRect frameRect;
@property (nonatomic, assign) cocos2d::ui::EditBox::InputFlag dataInputMode;
@property (nonatomic, assign) cocos2d::ui::EditBox::KeyboardReturnType keyboardReturnType;
@property (nonatomic, readonly, getter = isEditState) BOOL editState;
@property (nonatomic, readwrite) BOOL returnPressed;

- (instancetype)initWithFrame:(CGRect)frameRect editBox:(void *)editBox;
- (void)doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance;

- (NSString *)getDefaultFontName;
- (cocos2d::ui::EditBoxDelegate::EditBoxEndAction)getEndAction;

- (void)setInputMode:(cocos2d::ui::EditBox::InputMode)inputMode;
- (void)setInputFlag:(cocos2d::ui::EditBox::InputFlag)flag;
- (void)setReturnType:(cocos2d::ui::EditBox::KeyboardReturnType)returnType;
- (void)setTextHorizontalAlignment:(cocos2d::TextHAlignment)alignment;

- (void)setPlaceHolder:(NSString *)text;
- (void)setVisible:(BOOL)visible;
- (void)setTextColor:(UIColor*)color;
- (void)setFont:(UIFont *)font;
- (void)updateFrame:(CGRect)rect;

- (void)openKeyboard;
- (void)closeKeyboard;

@end
