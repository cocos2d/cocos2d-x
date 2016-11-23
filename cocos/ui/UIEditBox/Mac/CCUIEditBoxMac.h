/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 zilongshanren
 
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

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "ui/UIEditBox/UIEditBoxImpl-mac.h"
#include "ui/UIEditBox/Mac/CCUITextInput.h"

#pragma mark - UIEditBox mac implementation

@class NSFont;

@interface UIEditBoxImplMac : NSObject <NSTextFieldDelegate, NSTextViewDelegate>
{
    BOOL _editState;
    NSView<CCUITextInput> * _textInput;
    void * _editBox;
}

@property (nonatomic, retain) NSView<CCUITextInput> *textInput;
@property (nonatomic, readonly) NSWindow *window;

@property (nonatomic, readonly, getter = isEditState) BOOL editState;
@property (nonatomic, assign) void *editBox;
@property (nonatomic, assign) NSString *text;
@property (nonatomic, assign) NSRect frameRect;
@property (nonatomic, assign) cocos2d::ui::EditBox::InputFlag dataInputMode;
@property (nonatomic, assign) cocos2d::ui::EditBox::KeyboardReturnType keyboardReturnType;

- (instancetype)initWithFrame:(NSRect)frameRect editBox:(void *)editBox;
- (void)setMaxLength:(int)maxLength;
- (void)updateFrame:(CGRect)rect;

- (void)openKeyboard;
- (void)closeKeyboard;

- (NSString *)getDefaultFontName;
- (cocos2d::ui::EditBoxDelegate::EditBoxEndAction)getEndAction:(NSNotification *)notification;

- (void)setInputMode:(cocos2d::ui::EditBox::InputMode)inputMode;
- (void)setInputFlag:(cocos2d::ui::EditBox::InputFlag)inputFlag;
- (void)setReturnType:(cocos2d::ui::EditBox::KeyboardReturnType)returnType;

- (void)setPlaceHolder:(const char *)text;
- (void)setVisible:(BOOL)visible;
- (void)setTextColor:(NSColor*)color;
- (void)setFont:(NSFont *)font;
- (void)setPlaceholderFontColor:(NSColor*)color;
- (void)setPlaceholderFont:(NSFont*)font;
@end
