/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2013-2015 zilongshanren
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

#import "ui/UIEditBox/iOS/CCUIEditBoxIOS.h"
#import "ui/UIEditBox/iOS/CCUISingleLineTextField.h"
#import "ui/UIEditBox/iOS/CCUIMultilineTextField.h"

#import "platform/ios/CCEAGLView-ios.h"
#include "base/CCDirector.h"

#define getEditBoxImplIOS() ((cocos2d::ui::EditBoxImplIOS *)_editBox)


@implementation UIEditBoxImplIOS_objc

#pragma mark - Static methods

+ (void)initialize
{
    [super initialize];
    
    LoadUITextViewCCUITextInputCategory();
    LoadUITextFieldCCUITextInputCategory();
}

#pragma mark - Init & Dealloc

- (instancetype)initWithFrame:(CGRect)frameRect editBox:(void *)editBox
{
    self = [super init];
    if (self) {
        
        _editState = NO;
        self.frameRect = frameRect;
        self.editBox = editBox;
        self.dataInputMode = cocos2d::ui::EditBox::InputFlag::LOWERCASE_ALL_CHARACTERS;
        self.keyboardReturnType = cocos2d::ui::EditBox::KeyboardReturnType::DEFAULT;
        
        [self createMultiLineTextField];
    }
    
    return self;
}

- (void)dealloc
{
    // custom setter cleanup
    self.textInput = nil;
    
    [super dealloc];
}

#pragma mark - Properties

- (void)setTextInput:(UIView<UITextInput,CCUITextInput> *)textInput
{
    if (_textInput == textInput) {
        return;
    }
    
    // common init
    textInput.backgroundColor = [UIColor clearColor];
    textInput.hidden = true;
    textInput.returnKeyType = UIReturnKeyDefault;
    [textInput ccui_setDelegate:self];
    
    // Migrate properties
    textInput.ccui_textColor = _textInput.ccui_textColor ?: [UIColor whiteColor];
    textInput.ccui_text = _textInput.ccui_text ?: @"";
    textInput.ccui_placeholder = _textInput.ccui_placeholder ?: @"";
    textInput.ccui_font = _textInput.ccui_font ?: [UIFont systemFontOfSize:self.frameRect.size.height*2/3];
    textInput.ccui_placeholderFont = _textInput.ccui_placeholderFont ?: textInput.ccui_font;
    textInput.ccui_placeholderTextColor = _textInput.ccui_placeholderTextColor ?: [UIColor lightGrayColor];
    
    [_textInput resignFirstResponder];
    [_textInput removeFromSuperview];
    [_textInput release];
    
    _textInput = [textInput retain];
    
    [self setInputFlag:self.dataInputMode];
    [self setReturnType:self.keyboardReturnType];
}

#pragma mark - Public methods

- (void)createSingleLineTextField
{
    CCUISingleLineTextField *textField = [[[CCUISingleLineTextField alloc] initWithFrame:self.frameRect] autorelease];
    textField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    textField.borderStyle = UITextBorderStyleNone;
    
    [textField addTarget:self action:@selector(textChanged:) forControlEvents:UIControlEventEditingChanged];
    
    self.textInput = textField;
}

- (void)createMultiLineTextField
{
    CCUIMultilineTextField *textView = [[[CCUIMultilineTextField alloc] initWithFrame:self.frameRect] autorelease];
    self.textInput = textView;
}

#pragma mark - Public methods

- (void)setFont:(UIFont *)font
{
    self.textInput.ccui_font = font;
}

- (void)setTextColor:(UIColor*)color
{
    self.textInput.ccui_textColor = color;
}

- (void)setPlaceholderFont:(UIFont *)font
{
    self.textInput.ccui_placeholderFont = font;
}

- (void)setPlaceholderTextColor:(UIColor *)color
{
    self.textInput.ccui_placeholderTextColor = color;
}

- (void)setInputMode:(cocos2d::ui::EditBox::InputMode)inputMode
{
    //multiline input
    if (inputMode == cocos2d::ui::EditBox::InputMode::ANY) {
        if (![self.textInput isKindOfClass:[UITextView class]]) {
            [self createMultiLineTextField];
        }
    }
    else {
        if (![self.textInput isKindOfClass:[UITextField class]]) {
            [self createSingleLineTextField];
        }
    }
    
    switch (inputMode)
    {
        case cocos2d::ui::EditBox::InputMode::EMAIL_ADDRESS:
            self.keyboardType = UIKeyboardTypeEmailAddress;
            break;
        case cocos2d::ui::EditBox::InputMode::NUMERIC:
            self.keyboardType = UIKeyboardTypeDecimalPad;
            break;
        case cocos2d::ui::EditBox::InputMode::PHONE_NUMBER:
            self.keyboardType = UIKeyboardTypePhonePad;
            break;
        case cocos2d::ui::EditBox::InputMode::URL:
            self.keyboardType = UIKeyboardTypeURL;
            break;
        case cocos2d::ui::EditBox::InputMode::DECIMAL:
            self.keyboardType = UIKeyboardTypeDecimalPad;
            break;
        case cocos2d::ui::EditBox::InputMode::SINGLE_LINE:
            self.keyboardType = UIKeyboardTypeDefault;
            break;
        default:
            self.keyboardType = UIKeyboardTypeDefault;
            break;
    }
}

- (void)setKeyboardType:(UIKeyboardType)type
{
    self.textInput.keyboardType = type;
}

- (void)setInputFlag:(cocos2d::ui::EditBox::InputFlag)flag
{
    self.dataInputMode = flag;
    switch (flag)
    {
        case cocos2d::ui::EditBox::InputFlag::PASSWORD:
            //textView can't be used for input password
            self.textInput.ccui_secureTextEntry = YES;
            break;
            
        case cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD:
            self.textInput.autocapitalizationType = UITextAutocapitalizationTypeWords;
            break;
            
        case cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_SENTENCE:
            self.textInput.autocapitalizationType = UITextAutocapitalizationTypeSentences;
            break;
            
        case cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS:
            self.textInput.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
            break;
            
        case cocos2d::ui::EditBox::InputFlag::SENSITIVE:
            self.textInput.autocorrectionType = UITextAutocorrectionTypeNo;
            break;
            
        case cocos2d::ui::EditBox::InputFlag::LOWERCASE_ALL_CHARACTERS:
            self.textInput.autocapitalizationType = UITextAutocapitalizationTypeNone;
            break;
            
        default:
            break;
    }
}

- (void)setReturnType:(cocos2d::ui::EditBox::KeyboardReturnType)returnType
{
    self.keyboardReturnType = returnType;
    switch (returnType) {
        case cocos2d::ui::EditBox::KeyboardReturnType::DEFAULT:
            self.textInput.returnKeyType = UIReturnKeyDefault;
            break;
            
        case cocos2d::ui::EditBox::KeyboardReturnType::DONE:
            self.textInput.returnKeyType = UIReturnKeyDone;
            break;
            
        case cocos2d::ui::EditBox::KeyboardReturnType::SEND:
            self.textInput.returnKeyType = UIReturnKeySend;
            break;
            
        case cocos2d::ui::EditBox::KeyboardReturnType::SEARCH:
            self.textInput.returnKeyType = UIReturnKeySearch;
            break;
            
        case cocos2d::ui::EditBox::KeyboardReturnType::GO:
            self.textInput.returnKeyType = UIReturnKeyGo;
            break;
            
        case cocos2d::ui::EditBox::KeyboardReturnType::NEXT:
            self.textInput.returnKeyType = UIReturnKeyNext;
            break;

        default:
            self.textInput.returnKeyType = UIReturnKeyDefault;
            break;
    }
}

- (void)setTextHorizontalAlignment:(cocos2d::TextHAlignment)alignment
{
    self.textInput.ccui_alignment = static_cast<NSTextAlignment>(alignment);
}

- (void)setText:(NSString *)text
{
    self.textInput.ccui_text = text;
}

- (NSString *)text
{
    return self.textInput.ccui_text ?: @"";
}

- (void)setVisible:(BOOL)visible
{
    self.textInput.hidden = !visible;
}

- (NSString *)getDefaultFontName
{
    return self.textInput.ccui_font.fontName ?: @"";
}

- (cocos2d::ui::EditBoxDelegate::EditBoxEndAction)getEndAction
{
    cocos2d::ui::EditBoxDelegate::EditBoxEndAction action = cocos2d::ui::EditBoxDelegate::EditBoxEndAction::UNKNOWN;
    if (self.returnPressed) {
        if (self.keyboardReturnType == cocos2d::ui::EditBox::KeyboardReturnType::NEXT) {
            action = cocos2d::ui::EditBoxDelegate::EditBoxEndAction::TAB_TO_NEXT;
        } else if (self.keyboardReturnType == cocos2d::ui::EditBox::KeyboardReturnType::GO ||
                   self.keyboardReturnType == cocos2d::ui::EditBox::KeyboardReturnType::SEND ||
                   self.keyboardReturnType == cocos2d::ui::EditBox::KeyboardReturnType::SEARCH) {
            action = cocos2d::ui::EditBoxDelegate::EditBoxEndAction::RETURN;
        }
    }
    return action;
}

- (void)setPlaceHolder:(NSString *)text
{
    self.textInput.ccui_placeholder = text;
}

- (void)doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance
{
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *)view->getEAGLView();
    
    [eaglview doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
}

- (void)updateFrame:(CGRect)rect
{
    CGRect frame = self.textInput.frame;
    frame.origin = rect.origin;
    frame.size = rect.size;
    
    self.textInput.frame = frame;
}

- (void)openKeyboard
{
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *)view->getEAGLView();
    
    [eaglview addSubview:self.textInput];
    [self.textInput becomeFirstResponder];
}

- (void)closeKeyboard
{
    [self.textInput resignFirstResponder];
    [self.textInput removeFromSuperview];
}

- (BOOL)textFieldShouldReturn:(UITextField *)sender
{
    if (sender == self.textInput) {
        self.returnPressed = YES;
        [sender resignFirstResponder];
    }
    return NO;
}

- (void)animationSelector
{
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *)view->getEAGLView();
    
    [eaglview doAnimationWhenAnotherEditBeClicked];
}

#pragma mark - UITextView delegate methods

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView
{
    CCLOG("textFieldShouldBeginEditing...");
    _editState = YES;
    _returnPressed = NO;
    
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *) view->getEAGLView();
    
    if ([eaglview isKeyboardShown]) {
        [self performSelector:@selector(animationSelector) withObject:nil afterDelay:0.0f];
    }
    
    getEditBoxImplIOS()->editBoxEditingDidBegin();
    return YES;
}

- (BOOL)textViewShouldEndEditing:(UITextView *)textView
{
    CCLOG("textFieldShouldEndEditing...");
    _editState = NO;
    getEditBoxImplIOS()->refreshInactiveText();

    const char* inputText = [textView.text UTF8String];
    getEditBoxImplIOS()->editBoxEditingDidEnd(inputText, [self getEndAction]);
    
    return YES;
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    int maxLength = getEditBoxImplIOS()->getMaxLength();
    if (maxLength < 0)
    {
        return YES;
    }
    
    // Prevent crashing undo bug http://stackoverflow.com/questions/433337/set-the-maximum-character-length-of-a-uitextfield
    if (range.length + range.location > textView.text.length) {
        return NO;
    }
    
    NSUInteger oldLength = textView.text.length;
    NSUInteger replacementLength = text.length;
    NSUInteger rangeLength = range.length;
    
    NSUInteger newLength = oldLength - rangeLength + replacementLength;
    
    return newLength <= maxLength;
}

- (void)textViewDidChange:(UITextView *)textView
{
    int maxLength = getEditBoxImplIOS()->getMaxLength();
    if (textView.markedTextRange == nil) {
        if (textView.text.length > maxLength) {
            textView.text = [textView.text substringToIndex:maxLength];
        }
        
        const char* inputText = [textView.text UTF8String];
        getEditBoxImplIOS()->editBoxEditingChanged(inputText);
    }
}


#pragma mark - UITextField delegate methods
/**
 * Called each time when the text field's text has changed.
 */
- (void)textChanged:(UITextField *)textField
{
    int maxLength = getEditBoxImplIOS()->getMaxLength();
    if (textField.markedTextRange == nil) {
        if (textField.text.length > maxLength) {
            textField.text = [textField.text substringToIndex:maxLength];
        }
        
        const char* inputText = [textField.text UTF8String];
        getEditBoxImplIOS()->editBoxEditingChanged(inputText);
    }
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)sender        // return NO to disallow editing.
{
    CCLOG("textFieldShouldBeginEditing...");
    _editState = YES;
    
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *)view->getEAGLView();
    
    if ([eaglview isKeyboardShown]) {
        [self performSelector:@selector(animationSelector) withObject:nil afterDelay:0.0f];
    }
    
    getEditBoxImplIOS()->editBoxEditingDidBegin();
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)sender
{
    CCLOG("textFieldShouldEndEditing...");
    _editState = NO;
    const char* inputText = [sender.text UTF8String];

    getEditBoxImplIOS()->editBoxEditingDidEnd(inputText, [self getEndAction]);
    
    return YES;
}

/**
 * Delegate method called before the text has been changed.
 * @param textField The text field containing the text.
 * @param range The range of characters to be replaced.
 * @param string The replacement string.
 * @return YES if the specified text range should be replaced; otherwise, NO to keep the old text.
 */
- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    int maxLength = getEditBoxImplIOS()->getMaxLength();
    if (maxLength < 0) {
        return YES;
    }
    
    // Prevent crashing undo bug http://stackoverflow.com/questions/433337/set-the-maximum-character-length-of-a-uitextfield
    if (range.length + range.location > textField.text.length) {
        return NO;
    }
    
    NSUInteger oldLength = textField.text.length;
    NSUInteger replacementLength = string.length;
    NSUInteger rangeLength = range.length;
    
    NSUInteger newLength = oldLength - rangeLength + replacementLength;
    
    return newLength <= maxLength;
}

@end
