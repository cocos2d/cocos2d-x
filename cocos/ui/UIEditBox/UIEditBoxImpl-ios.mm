/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
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

/** TODO: Missing doc - Why is this subclass necessary?
 */
@interface UICustomUITextField : UITextField
@end

@implementation UICustomUITextField

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


@interface UIEditBoxImplIOS_objc : NSObject <UITextFieldDelegate>

@property (nonatomic, retain) UITextField *textField;
@property (nonatomic, assign) void *editBox;
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
        UITextField *textField = [[[UICustomUITextField alloc] initWithFrame: frameRect] autorelease];

        textField.textColor = [UIColor whiteColor];
         // TODO: need to delete hard code here.
        textField.font = [UIFont systemFontOfSize:frameRect.size.height*2/3];
        textField.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
        textField.backgroundColor = [UIColor clearColor];
        textField.borderStyle = UITextBorderStyleNone;
        textField.delegate = self;
        textField.hidden = true;
        textField.returnKeyType = UIReturnKeyDefault;
        
        [textField addTarget:self action:@selector(textChanged:) forControlEvents:UIControlEventEditingChanged];

        
        self.textField = textField;
        self.editBox = editBox;
    }
    
    return self;
}

- (void)dealloc
{
    [_textField resignFirstResponder];
    [_textField removeFromSuperview];
    
    self.textField = nil;
    
    [super dealloc];
}

#pragma mark - Public methods

- (void)doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance
{
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *)view->getEAGLView();

    [eaglview doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
}

- (void)setPosition:(CGPoint)pos
{
    // TODO: Handle anchor point?
    CGRect frame = _textField.frame;
    frame.origin = pos;
    
    _textField.frame = frame;
}

- (void)setContentSize:(CGSize)size
{
    CGRect frame = _textField.frame;
    frame.size = size;
    
    _textField.frame = frame;
}

- (void)openKeyboard
{
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *)view->getEAGLView();

    [eaglview addSubview:_textField];
    [_textField becomeFirstResponder];
}

- (void)closeKeyboard
{
    [_textField resignFirstResponder];
    [_textField removeFromSuperview];
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

#pragma mark - UITextField delegate methods

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
        [_systemControl.textField setFont:textFont];
    }
}
    
void EditBoxImplIOS::setNativeFontColor(const Color4B& color)
{
    _systemControl.textField.textColor = [UIColor colorWithRed:color.r / 255.0f
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
    switch (inputMode)
    {
        case EditBox::InputMode::EMAIL_ADDRESS:
            _systemControl.textField.keyboardType = UIKeyboardTypeEmailAddress;
            break;
        case EditBox::InputMode::NUMERIC:
            _systemControl.textField.keyboardType = UIKeyboardTypeDecimalPad;
            break;
        case EditBox::InputMode::PHONE_NUMBER:
            _systemControl.textField.keyboardType = UIKeyboardTypePhonePad;
            break;
        case EditBox::InputMode::URL:
            _systemControl.textField.keyboardType = UIKeyboardTypeURL;
            break;
        case EditBox::InputMode::DECIMAL:
            _systemControl.textField.keyboardType = UIKeyboardTypeDecimalPad;
            break;
        case EditBox::InputMode::SINGLE_LINE:
            _systemControl.textField.keyboardType = UIKeyboardTypeDefault;
            break;
        default:
            _systemControl.textField.keyboardType = UIKeyboardTypeDefault;
            break;
    }
}

void EditBoxImplIOS::setNativeInputFlag(EditBox::InputFlag inputFlag)
{
    switch (inputFlag)
    {
        case EditBox::InputFlag::PASSWORD:
            _systemControl.textField.secureTextEntry = YES;
            break;
        case EditBox::InputFlag::INITIAL_CAPS_WORD:
            _systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeWords;
            break;
        case EditBox::InputFlag::INITIAL_CAPS_SENTENCE:
            _systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeSentences;
            break;
        case EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS:
            _systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
            break;
        case EditBox::InputFlag::SENSITIVE:
            _systemControl.textField.autocorrectionType = UITextAutocorrectionTypeNo;
            break;
        default:
            break;
    }
}
    
NSString* removeSiriString(NSString* str)
{
    NSString* siriString = @"\xef\xbf\xbc";
    return [str stringByReplacingOccurrencesOfString:siriString withString:@""];
}

const char*  EditBoxImplIOS::getText(void)
{
    return [removeSiriString(_systemControl.textField.text) UTF8String];
}


void EditBoxImplIOS::setNativeReturnType(EditBox::KeyboardReturnType returnType)
{
    switch (returnType) {
        case EditBox::KeyboardReturnType::DEFAULT:
            _systemControl.textField.returnKeyType = UIReturnKeyDefault;
            break;
        case EditBox::KeyboardReturnType::DONE:
            _systemControl.textField.returnKeyType = UIReturnKeyDone;
            break;
        case EditBox::KeyboardReturnType::SEND:
            _systemControl.textField.returnKeyType = UIReturnKeySend;
            break;
        case EditBox::KeyboardReturnType::SEARCH:
            _systemControl.textField.returnKeyType = UIReturnKeySearch;
            break;
        case EditBox::KeyboardReturnType::GO:
            _systemControl.textField.returnKeyType = UIReturnKeyGo;
            break;
        default:
            _systemControl.textField.returnKeyType = UIReturnKeyDefault;
            break;
    }
}

void EditBoxImplIOS::setNativeText(const char* pText)
{
    NSString* nsText =[NSString stringWithUTF8String:pText];
    if ([nsText compare:_systemControl.textField.text] != NSOrderedSame)
    {
        _systemControl.textField.text = nsText;
    }
}

void EditBoxImplIOS::setNativePlaceHolder(const char* pText)
{
    _systemControl.textField.placeholder = [NSString stringWithUTF8String:pText];
}

void EditBoxImplIOS::setNativeVisible(bool visible)
{
    _systemControl.textField.hidden = !visible;
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
    const char* pDefaultFontName = [[_systemControl.textField.font fontName] UTF8String];
    return pDefaultFontName;
}

void EditBoxImplIOS::nativeOpenKeyboard()
{
    _systemControl.textField.hidden = NO;
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
        fontSize = [_systemControl.textField frame].size.height*2/3;
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


