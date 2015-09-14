/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2013-2015 zilongshanren
 
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
#include "UIEditBoxImpl-ios.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#define kLabelZOrder  9999

#include "UIEditBox.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"
#import "platform/ios/CCEAGLView-ios.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define getEditBoxImplIOS() ((cocos2d::ui::EditBoxImplIOS *)_editBox)

static const int CC_EDIT_BOX_PADDING = 5;

#pragma mark - Internal Classes

/**
 * http://stackoverflow.com/questions/1328638/placeholder-in-uitextview
 */
CGFloat const UI_PLACEHOLDER_TEXT_CHANGED_ANIMATION_DURATION = 0.25;

@interface UIMultilineTextField : UITextView
@property (nonatomic, retain) NSString *placeholder;
@property (nonatomic, retain) UIColor *placeholderColor;
-(void)textChanged:(NSNotification*)notification;
@end

@interface UIMultilineTextField ()
@property (nonatomic, retain) UILabel *placeHolderLabel;
@end

@implementation UIMultilineTextField

- (CGRect)textRectForBounds:(CGRect)bounds
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    
    float padding = CC_EDIT_BOX_PADDING * glview->getScaleX() / glview->getContentScaleFactor();
    return CGRectInset(bounds, padding, padding);
}

- (id)initWithFrame:(CGRect)frame
{
    if( (self = [super initWithFrame:frame]) )
    {
        [self setPlaceholder:@""];
        [self setPlaceholderColor:[UIColor lightGrayColor]];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(textChanged:)
                                                     name:UITextViewTextDidChangeNotification object:nil];
    }
    return self;
}

- (void)textChanged:(NSNotification *)notification
{
    if([[self placeholder] length] == 0)
    {
        return;
    }
    
    [UIView animateWithDuration:UI_PLACEHOLDER_TEXT_CHANGED_ANIMATION_DURATION animations:^{
        if([[self text] length] == 0)
        {
            [[self viewWithTag:999] setAlpha:1];
        }
        else
        {
            [[self viewWithTag:999] setAlpha:0];
        }
    }];
}

- (void)setText:(NSString *)text {
    [super setText:text];
    [self textChanged:nil];
}

- (void)drawRect:(CGRect)rect
{
    if( [[self placeholder] length] > 0 )
    {
        if (_placeHolderLabel == nil )
        {
            _placeHolderLabel = [[UILabel alloc] initWithFrame:CGRectMake(8,8,self.bounds.size.width - 16,0)];
            _placeHolderLabel.lineBreakMode = NSLineBreakByWordWrapping;
            _placeHolderLabel.numberOfLines = 0;
            _placeHolderLabel.font = self.font;
            _placeHolderLabel.backgroundColor = [UIColor clearColor];
            _placeHolderLabel.textColor = self.placeholderColor;
            _placeHolderLabel.alpha = 0;
            _placeHolderLabel.tag = 999;
            [self addSubview:_placeHolderLabel];
        }
        
        _placeHolderLabel.text = self.placeholder;
        [_placeHolderLabel sizeToFit];
        [self sendSubviewToBack:_placeHolderLabel];
    }
    
    if( [[self text] length] == 0 && [[self placeholder] length] > 0 )
    {
        [[self viewWithTag:999] setAlpha:1];
    }
    
    [super drawRect:rect];
}

- (CGRect)editingRectForBounds:(CGRect)bounds
{
    return [self textRectForBounds:bounds];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];

    [_placeHolderLabel release];
    _placeHolderLabel = nil;
    [_placeholderColor release];
    _placeholderColor = nil;
    [_placeholder release];
    _placeholder = nil;
    [super dealloc];
}

@end

/** TODO: Missing doc - Why is this subclass necessary?
 */
@interface UISingleLineTextField : UITextField
@end

@implementation UISingleLineTextField

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

#pragma mark - UIEditBox ios implementation


@interface UIEditBoxImplIOS_objc : NSObject <UITextFieldDelegate, UITextViewDelegate>

@property (nonatomic, retain) UITextField *textField;
@property (nonatomic, retain) UITextView *textView;
@property (nonatomic, assign) void *editBox;
@property (nonatomic, assign) CGRect frameRect;
@property (nonatomic, assign) cocos2d::ui::EditBox::InputFlag dataInputMode;
@property (nonatomic, assign) cocos2d::ui::EditBox::KeyboardReturnType keyboardReturnType;
@property (nonatomic, readonly, getter = isEditState) BOOL editState;

- (instancetype)initWithFrame:(CGRect)frameRect editBox:(void *)editBox;
- (void)doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance;

- (void)setPosition:(CGPoint)pos;
- (void)setContentSize:(CGSize)size;

- (void)openKeyboard;
- (void)closeKeyboard;

@end

#pragma mark - UIEditBox iOS implementation

@implementation UIEditBoxImplIOS_objc

#pragma mark - Init & Dealloc

- (instancetype)initWithFrame:(CGRect)frameRect editBox:(void *)editBox
{
    self = [super init];
    
    if (self)
    {
        _editState = NO;
        self.textField = nil;
        self.textView = nil;
        self.frameRect = frameRect;
        self.editBox = editBox;
        self.dataInputMode = cocos2d::ui::EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS;
        self.keyboardReturnType = cocos2d::ui::EditBox::KeyboardReturnType::DEFAULT;
        [self createMultiLineTextField];
    }
    
    return self;
}

- (void)createSingleLineTextField{
    UISingleLineTextField *textField = [[[UISingleLineTextField alloc] initWithFrame: self.frameRect] autorelease];
    
    UIColor *textColor;
    NSString *text;
    NSString *placeholder;
    CGFloat fontSize;
    if (self.textView != nil) {
        textColor = self.textView.textColor;
        text = self.textView.text;
        placeholder = [(UIMultilineTextField*)self.textView placeholder];
        fontSize = [self.textView.font pointSize];
    }
    else{
        textColor = [UIColor whiteColor];
        text = @"";
        placeholder = @"";
        fontSize = self.frameRect.size.height*2/3;
    }
    
    textField.textColor = textColor;
    // TODO: need to delete hard code here.
    textField.font = [UIFont systemFontOfSize: fontSize];
    textField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    textField.backgroundColor = [UIColor clearColor];
    textField.borderStyle = UITextBorderStyleNone;
    textField.delegate = self;
    textField.hidden = true;
    textField.returnKeyType = UIReturnKeyDefault;
    textField.text = text;
    
    [textField addTarget:self action:@selector(textChanged:) forControlEvents:UIControlEventEditingChanged];
    
    self.textField = textField;
    
    [self removeMultiLineTextField];
}

- (void)createMultiLineTextField{
    UIMultilineTextField *textView = [[[UIMultilineTextField alloc] initWithFrame: self.frameRect] autorelease];
    
    UIColor *textColor;
    NSString *text;
    NSString *placeholder;
    CGFloat fontSize;
    if (self.textField != nil) {
        textColor = self.textField.textColor;
        text = self.textField.text;
        placeholder = [self.textField placeholder];
        fontSize = [self.textField.font pointSize];
    }
    else{
        textColor = [UIColor whiteColor];
        text = @"";
        placeholder = @"";
        fontSize = self.frameRect.size.height*2/3;
    }
    textView.textColor = textColor;
    textView.font = [UIFont systemFontOfSize:fontSize];
    textView.backgroundColor = [UIColor clearColor];
    textView.delegate = self;
    textView.hidden = true;
    textView.returnKeyType = UIReturnKeyDefault;
    textView.text = text;
    textView.placeholder = placeholder;
    
    self.textView = textView;
    
    [self removeSingleLineTextField];
}

-(void)removeSingleLineTextField{
    if (_textField != nil)
    {
        [_textField resignFirstResponder];
        [_textField removeFromSuperview];
        self.textField = nil;
    }
}

-(void)removeMultiLineTextField{
    if (_textView != nil)
    {
        [_textView resignFirstResponder];
        [_textView removeFromSuperview];
        self.textView = nil;
    }
}

- (void)dealloc
{
    [self removeSingleLineTextField];
    [self removeMultiLineTextField];
    
    [super dealloc];
}

#pragma mark - Public methods
- (void)setFont:(UIFont*)font{
    if (_textField != nil)
    {
        [_textField setFont:font];
    }
    if (_textView != nil) {
        [_textView setFont:font];
    }
}

- (void)setTextColor:(UIColor*)color{
    if (_textField != nil)
    {
        [_textField setTextColor:color];
    }
    if (_textView != nil) {
        [_textView setTextColor:color];
    }
}

- (void)setInputMode:(cocos2d::ui::EditBox::InputMode)inputMode{
    //multiline input
    if (inputMode == cocos2d::ui::EditBox::InputMode::ANY)
    {
        if (self.textField != nil)
        {
            [self createMultiLineTextField];
            [self setInputFlag:self.dataInputMode];
            [self setReturnType:self.keyboardReturnType];
        }
    }
    else
    {
        if (self.textView != nil) {
            [self createSingleLineTextField];
            [self setInputFlag:self.dataInputMode];
            [self setReturnType:self.keyboardReturnType];
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

- (void)setKeyboardType:(UIKeyboardType)type{
    if (_textField != nil)
    {
        [_textField setKeyboardType:type];
    }
    if (_textView != nil) {
        [_textView setKeyboardType:type];
    }
}

- (void)setInputFlag:(cocos2d::ui::EditBox::InputFlag)flag{
    self.dataInputMode = flag;
    switch (flag)
    {
        case cocos2d::ui::EditBox::InputFlag::PASSWORD:
            if (self.textField != nil)
            {
                self.textField.secureTextEntry = YES;
            }
            //textView can't be used for input password
            break;
        case cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD:
            if (self.textField != nil)
            {
                self.textField.autocapitalizationType = UITextAutocapitalizationTypeWords;
            }
            if (self.textView != nil)
            {
                self.textView.autocapitalizationType = UITextAutocapitalizationTypeWords;
            }
            break;
        case cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_SENTENCE:
            if (self.textField != nil)
            {
                self.textField.autocapitalizationType = UITextAutocapitalizationTypeSentences;
            }
            if (self.textView != nil)
            {
                self.textView.autocapitalizationType = UITextAutocapitalizationTypeSentences;
            }
            break;
        case cocos2d::ui::EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS:
            if (self.textField != nil)
            {
                self.textField.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
            }
            if (self.textView != nil)
            {
                self.textView.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
            }
            break;
        case cocos2d::ui::EditBox::InputFlag::SENSITIVE:
            if (self.textField != nil)
            {
                self.textField.autocorrectionType = UITextAutocorrectionTypeNo;
            }
            if (self.textView != nil)
            {
                self.textView.autocorrectionType = UITextAutocorrectionTypeNo;
            }
            break;
        default:
            break;
    }
}

- (void)setReturnType:(cocos2d::ui::EditBox::KeyboardReturnType)returnType{
    self.keyboardReturnType = returnType;
    switch (returnType) {
        case cocos2d::ui::EditBox::KeyboardReturnType::DEFAULT:
            if (self.textField != nil) {
                self.textField.returnKeyType = UIReturnKeyDefault;
            }
            if (self.textView != nil) {
                self.textView.returnKeyType = UIReturnKeyDefault;
            }
            break;
        case cocos2d::ui::EditBox::KeyboardReturnType::DONE:
            if (self.textField != nil) {
                self.textField.returnKeyType = UIReturnKeyDone;
            }
            if (self.textView != nil) {
                self.textView.returnKeyType = UIReturnKeyDone;
            }
            break;
        case cocos2d::ui::EditBox::KeyboardReturnType::SEND:
            if (self.textField != nil) {
                self.textField.returnKeyType = UIReturnKeySend;
            }
            if (self.textView != nil) {
                self.textView.returnKeyType = UIReturnKeySend;
            }
            break;
        case cocos2d::ui::EditBox::KeyboardReturnType::SEARCH:
            if (self.textField !=  nil) {
                self.textField.returnKeyType = UIReturnKeySearch;
            }
            if (self.textView != nil) {
                self.textView.returnKeyType = UIReturnKeySearch;
            }
            break;
        case cocos2d::ui::EditBox::KeyboardReturnType::GO:
            if (self.textField != nil) {
                self.textField.returnKeyType = UIReturnKeyGo;
            }
            if (self.textView != nil) {
                self.textView.returnKeyType = UIReturnKeyGo;
            }
            break;
        default:
            if (self.textField != nil) {
                self.textField.returnKeyType = UIReturnKeyDefault;
            }
            if (self.textView != nil) {
                self.textView.returnKeyType = UIReturnKeyDefault;
            }
            break;
    }
}

- (void)setText:(NSString*)text{
    if (self.textField != nil) {
        self.textField.text = text;
    }
    if (self.textView != nil) {
        self.textView.text = text;
    }
}

- (NSString*)getText{
    if (self.textField != nil) {
        return self.textField.text;
    }
    if (self.textView != nil) {
        return self.textView.text;
    }
    return @"";
}

- (void)setVisible:(BOOL)visible{
    if (self.textField != nil) {
        self.textField.hidden = !visible;
    }
    if (self.textView != nil) {
        self.textView.hidden = !visible;
    }
}

- (NSString*)getDefaultFontName{
    if (self.textField != nil) {
        return [self.textField.font fontName];
    }
    if (self.textView != nil) {
        return [self.textView.font fontName];
    }
    
    return @"";
}

- (void)setPlaceHolder:(NSString*)text{
    if (self.textField != nil) {
        self.textField.placeholder = text;
    }
    if (self.textView != nil) {
        [(UIMultilineTextField*)self.textView setPlaceholder:text];
    }
}

- (void)doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance
{
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *)view->getEAGLView();

    [eaglview doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
}

- (void)setPosition:(CGPoint)pos
{
    // TODO: Handle anchor point?
    if (_textField != nil)
    {
        CGRect frame = _textField.frame;
        frame.origin = pos;
        _textField.frame = frame;
    }
    if (_textView != nil)
    {
        CGRect frame = _textView.frame;
        frame.origin = pos;
        _textView.frame = frame;
    }
}

- (void)setContentSize:(CGSize)size
{
    if (_textField != nil)
    {
        CGRect frame = _textField.frame;
        frame.size = size;
        _textField.frame = frame;
    }
    if (_textView != nil)
    {
        CGRect frame = _textView.frame;
        frame.size = size;
        _textView.frame = frame;
    }
}

- (void)openKeyboard
{
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *)view->getEAGLView();

    if (_textField != nil)
    {
        [eaglview addSubview:_textField];
        [_textField becomeFirstResponder];
    }
    if (_textView != nil)
    {
        [eaglview addSubview:_textView];
        [_textView becomeFirstResponder];
    }
}

- (void)closeKeyboard
{
    if (_textField != nil)
    {
        [_textField resignFirstResponder];
        [_textField removeFromSuperview];
    }
    if (_textView != nil)
    {
        [_textView resignFirstResponder];
        [_textView removeFromSuperview];
    }
}

- (BOOL)textFieldShouldReturn:(UITextField *)sender
{
    if (sender == _textField) {
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
    
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *) view->getEAGLView();
    
    if ([eaglview isKeyboardShown])
    {
        [self performSelector:@selector(animationSelector) withObject:nil afterDelay:0.0f];
    }
    
    getEditBoxImplIOS()->editBoxEditingDidBegin();
    return YES;
}

- (BOOL)textViewShouldEndEditing:(UITextView *)textView;
{
    CCLOG("textFieldShouldEndEditing...");
    _editState = NO;
    getEditBoxImplIOS()->refreshInactiveText();
    
    const char* inputText = [textView.text UTF8String];
    getEditBoxImplIOS()->editBoxEditingDidEnd(inputText);

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
    if(range.length + range.location > textView.text.length)
    {
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
    if (textView.text.length > maxLength) {
        textView.text = [textView.text substringToIndex:maxLength];
    }
    
    const char* inputText = [textView.text UTF8String];
    getEditBoxImplIOS()->editBoxEditingChanged(inputText);
}


#pragma mark - UITextField delegate methods
/**
 * Called each time when the text field's text has changed.
 */
- (void)textChanged:(UITextField*)textField
{
    int maxLength = getEditBoxImplIOS()->getMaxLength();
    if (textField.text.length > maxLength) {
        textField.text = [textField.text substringToIndex:maxLength];
    }
    
    const char* inputText = [textField.text UTF8String];
    getEditBoxImplIOS()->editBoxEditingChanged(inputText);
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)sender        // return NO to disallow editing.
{
    CCLOG("textFieldShouldBeginEditing...");
    _editState = YES;

    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *) view->getEAGLView();

    if ([eaglview isKeyboardShown])
    {
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

    getEditBoxImplIOS()->editBoxEditingDidEnd(inputText);
    
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
    if (maxLength < 0)
    {
        return YES;
    }
    
    // Prevent crashing undo bug http://stackoverflow.com/questions/433337/set-the-maximum-character-length-of-a-uitextfield
    if(range.length + range.location > textField.text.length)
    {
        return NO;
    }
    
    NSUInteger oldLength = textField.text.length;
    NSUInteger replacementLength = string.length;
    NSUInteger rangeLength = range.length;
    
    NSUInteger newLength = oldLength - rangeLength + replacementLength;
    
    return newLength <= maxLength;
}

@end


NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplIOS(pEditBox);
}

EditBoxImplIOS::EditBoxImplIOS(EditBox* pEditText)
: EditBoxImplCommon(pEditText)
,_systemControl(nullptr)
, _anchorPoint(Vec2(0.5f, 0.5f))
{
    
}

EditBoxImplIOS::~EditBoxImplIOS()
{
    [_systemControl release];
    _systemControl = nil;
}
    
void EditBoxImplIOS::createNativeControl(const Rect& frame)
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    Rect rect(0, 0, frame.size.width * glview->getScaleX(), frame.size.height * glview->getScaleY());

    float factor = cocos2d::Director::getInstance()->getContentScaleFactor();

    rect.size.width /= factor;
    rect.size.height /= factor;
    
    _systemControl = [[UIEditBoxImplIOS_objc alloc] initWithFrame:CGRectMake(rect.origin.x,
                                                                             rect.origin.y,
                                                                             rect.size.width,
                                                                         rect.size.height)
                                                          editBox:this];

}

bool EditBoxImplIOS::isEditing()
{
    return [_systemControl isEditState] ? true : false;
}

void EditBoxImplIOS::doAnimationWhenKeyboardMove(float duration, float distance)
{
    if ([_systemControl isEditState] || distance < 0.0f)
    {
        [_systemControl doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
    }
}
    
void EditBoxImplIOS::setNativeFont(const char* pFontName, int fontSize)
{
    UIFont* textFont = constructFont(pFontName, fontSize);
    if(textFont != nil) {
        [_systemControl setFont:textFont];
    }
}
    
void EditBoxImplIOS::setNativeFontColor(const Color4B& color)
{
    _systemControl.textColor = [UIColor colorWithRed:color.r / 255.0f
                                                         green:color.g / 255.0f
                                                          blue:color.b / 255.0f
                                                         alpha:color.a / 255.f];

}

void EditBoxImplIOS::setNativePlaceholderFont(const char* pFontName, int fontSize)
{
    //TODO::
}

void EditBoxImplIOS::setNativePlaceholderFontColor(const Color4B& color)
{
    //TODO::
}

void EditBoxImplIOS::setNativeInputMode(EditBox::InputMode inputMode)
{
    [_systemControl setInputMode:inputMode];
}

void EditBoxImplIOS::setNativeInputFlag(EditBox::InputFlag inputFlag)
{
    [_systemControl setInputFlag:inputFlag];
}
    
NSString* removeSiriString(NSString* str)
{
    NSString* siriString = @"\xef\xbf\xbc";
    return [str stringByReplacingOccurrencesOfString:siriString withString:@""];
}

const char*  EditBoxImplIOS::getText(void)
{
    return [removeSiriString([_systemControl getText]) UTF8String];
}


void EditBoxImplIOS::setNativeReturnType(EditBox::KeyboardReturnType returnType)
{
    [_systemControl setReturnType:returnType];
}

void EditBoxImplIOS::setNativeText(const char* pText)
{
    NSString* nsText =[NSString stringWithUTF8String:pText];
    if ([nsText compare: [_systemControl getText]] != NSOrderedSame)
    {
        _systemControl.text = nsText;
    }
}

void EditBoxImplIOS::setNativePlaceHolder(const char* pText)
{
    [_systemControl setPlaceHolder:[NSString stringWithUTF8String:pText]];
}

void EditBoxImplIOS::setNativeVisible(bool visible)
{
    [_systemControl setVisible:visible];
}

void EditBoxImplIOS::updateNativeFrame(const Rect& rect)
{
    //no-op
}

void EditBoxImplIOS::setNativeContentSize(const Size& size)
{
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    CCEAGLView *eaglview = static_cast<CCEAGLView *>(glview->getEAGLView());
    float factor = eaglview.contentScaleFactor;
    
    [_systemControl setContentSize:CGSizeMake(size.width / factor, size.height / factor)];
}

const char* EditBoxImplIOS::getNativeDefaultFontName()
{
    const char* pDefaultFontName = [[_systemControl getDefaultFontName] UTF8String];
    return pDefaultFontName;
}

void EditBoxImplIOS::nativeOpenKeyboard()
{
    [_systemControl setVisible:YES];
    [_systemControl openKeyboard];
}

void EditBoxImplIOS::nativeCloseKeyboard()
{
    [_systemControl closeKeyboard];
}
    
UIFont* EditBoxImplIOS::constructFont(const char *fontName, int fontSize)
{
    CCASSERT(fontName != nullptr, "fontName can't be nullptr");
    CCEAGLView *eaglview = static_cast<CCEAGLView *>(cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView());
    float retinaFactor = eaglview.contentScaleFactor;
    NSString * fntName = [NSString stringWithUTF8String:fontName];
    
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float scaleFactor = glview->getScaleX();
    
    if (fontSize == -1)
    {
        fontSize = _systemControl.frameRect.size.height*2/3;
    }
    else
    {
        fontSize = fontSize * scaleFactor / retinaFactor;
    }
    
    UIFont *textFont = nil;
    if (strlen(fontName) > 0)
    {
        textFont = [UIFont fontWithName:fntName size:fontSize];
    }
    else
    {
        textFont = [UIFont systemFontOfSize:fontSize];
    }
    return textFont;
}
    
void EditBoxImplIOS::setPosition(const Vec2& pos)
{
    _position = pos;
    adjustTextFieldPosition();
}

void EditBoxImplIOS::setAnchorPoint(const Vec2& anchorPoint)
{
    CCLOG("[Edit text] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
    _anchorPoint = anchorPoint;
    setPosition(_position);
}

void EditBoxImplIOS::updatePosition(float dt)
{
    if (nullptr != _systemControl) {
        this->adjustTextFieldPosition();
    }
}

static CGPoint convertDesignCoordToScreenCoord(const Vec2& designCoord)
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *) glview->getEAGLView();
    
    float viewH = (float)[eaglview getHeight];
    
    Vec2 visiblePos = Vec2(designCoord.x * glview->getScaleX(), designCoord.y * glview->getScaleY());
    Vec2 screenGLPos = visiblePos + glview->getViewPortRect().origin;
    
    CGPoint screenPos = CGPointMake(screenGLPos.x, viewH - screenGLPos.y);
    
    float factor = eaglview.contentScaleFactor;
    screenPos.x = screenPos.x / factor;
    screenPos.y = screenPos.y / factor;
    
    CCLOGINFO("[EditBox] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}


void EditBoxImplIOS::adjustTextFieldPosition()
{
    Size contentSize = _editBox->getContentSize();
    Rect rect = Rect(0, 0, contentSize.width, contentSize.height);
    rect = RectApplyAffineTransform(rect, _editBox->nodeToWorldTransform());
    
    Vec2 designCoord = Vec2(rect.origin.x, rect.origin.y + rect.size.height);
    [_systemControl setPosition:convertDesignCoordToScreenCoord(designCoord)];
}

}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */


