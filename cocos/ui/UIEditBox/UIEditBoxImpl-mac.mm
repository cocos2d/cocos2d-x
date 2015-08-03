/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 Jozef Pridavok
 
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

#include "UIEditBoxImpl-mac.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#include "base/CCDirector.h"
#include "UIEditBox.h"
#include "deprecated/CCString.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#define getEditBoxImplMac() ((cocos2d::ui::EditBoxImplMac *)_editBox)

#pragma mark - internal classes

/** TODO: Missing doc - What does "CustomTextFieldFormatter" do?
 */
@interface CustomTextFieldFormatter : NSFormatter

@property (nonatomic, assign) int maximumLength;

@end

@implementation CustomTextFieldFormatter

- (instancetype)init
{
    self = [super init];
    if (self) {
        _maximumLength = INT_MAX;
    }
    
    return self;
}

- (NSString *)stringForObjectValue:(id)object
{
    return object;
}

- (BOOL)getObjectValue:(id *)object forString:(NSString *)string errorDescription:(NSString **)error
{
    *object = string;
    return YES;
}

- (BOOL)isPartialStringValid:(NSString **)partialStringPtr
       proposedSelectedRange:(NSRangePointer)proposedSelRangePtr
              originalString:(NSString *)origString
       originalSelectedRange:(NSRange)origSelRange
            errorDescription:(NSString **)error
{
    return (*partialStringPtr).length <= self.maximumLength;
}

- (NSAttributedString *)attributedStringForObjectValue:(id)anObject withDefaultAttributes:(NSDictionary *)attributes
{
    return nil;
}

@end

#pragma mark - UIEditBox mac implementation

@interface UIEditBoxImplMac : NSObject <NSTextFieldDelegate>

@property (nonatomic, retain) NSTextField* textField;
@property (nonatomic, retain) NSSecureTextField *secureTextField;
@property (nonatomic, retain) NSMutableDictionary *placeholderAttributes;
@property (nonatomic, readonly) NSWindow *window;

@property (nonatomic, readonly, getter = isEditState) BOOL editState;
@property (nonatomic, assign, getter = isSecure) BOOL secure;
@property (nonatomic, assign) void *editBox;

- (instancetype)initWithFrame:(NSRect)frameRect editBox:(void *)editBox;

- (void)doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance;
- (void)setPosition:(NSPoint)pos;

- (void)openKeyboard;
- (void)closeKeyboard;

@end


@implementation UIEditBoxImplMac

- (instancetype)initWithFrame:(NSRect)frameRect editBox:(void *)editBox
{
    self = [super init];
    
    if (self) {
        
        _editState = NO;
        _secure = NO;
        
        self.textField = [[[NSTextField alloc] initWithFrame:frameRect] autorelease];
        self.secureTextField = [[[NSSecureTextField alloc] initWithFrame:frameRect] autorelease];

        //TODO: need to delete hard code here.
        NSFont *font = [NSFont systemFontOfSize:frameRect.size.height*2/3];
        _textField.font = font;
        _secureTextField.font = font;
        
        [self setupTextField:_textField];
        [self setupTextField:_secureTextField];

        self.editBox = editBox;
        self.placeholderAttributes = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                      font, NSFontAttributeName,
                                      [NSColor grayColor], NSForegroundColorAttributeName,
                                      nil];
        
        [self.window.contentView addSubview:_textField];
    }
    
    return self;
}

- (void)dealloc
{
    [_textField resignFirstResponder];
    [_textField removeFromSuperview];
    [_textField release];
    
    [_secureTextField resignFirstResponder];
    [_secureTextField removeFromSuperview];
    [_secureTextField release];
    
    [_placeholderAttributes release];
    
    [super dealloc];
}

- (NSWindow *)window
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    return glview->getCocoaWindow();
}

- (void)setPosition:(NSPoint)pos
{
    NSRect frame = _textField.frame;
    frame.origin = pos;
    
    _textField.frame = frame;
    _secureTextField.frame = frame;
}

- (void)setupTextField:(NSTextField *)textField
{
    textField.textColor = [NSColor whiteColor];
    textField.backgroundColor = [NSColor clearColor];
    textField.bordered = NO;
    textField.hidden = NO;
    textField.wantsLayer = YES;
    textField.delegate = self;
}

- (void)doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance
{
    [self.window.contentView doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
}

- (void)setSecure:(BOOL)secure
{
    NSAssert(secure, @"Can only set this flag to true");
    
    _secure = secure;
        
    [_textField.superview addSubview:_secureTextField];
    [_textField removeFromSuperview];
}

- (void)openKeyboard
{
    NSView *contentView = self.window.contentView;
    
    if (!_secure) {
        [contentView addSubview:_textField];
        [_textField becomeFirstResponder];
    }
    else {
        [contentView addSubview:_secureTextField];
        [_secureTextField becomeFirstResponder];
    }
}

- (void)closeKeyboard
{
    if ([_textField superview]) {
        [_textField resignFirstResponder];
        [_textField removeFromSuperview];
    }
    else {
        [_secureTextField resignFirstResponder];
        [_secureTextField removeFromSuperview];
    }
}

- (BOOL)textFieldShouldReturn:(NSTextField *)sender
{
    if (sender == _textField || sender == _secureTextField) {
        [sender resignFirstResponder];
    }
    return NO;
}

- (void)controlTextDidBeginEditing:(NSNotification *)notification
{
    _editState = YES;
    cocos2d::ui::EditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidBegin(getEditBoxImplMac()->getEditBox());
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    cocos2d::ui::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

- (void)controlTextDidEndEditing:(NSNotification *)notification
{
    _editState = NO;
    cocos2d::ui::EditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidEnd(getEditBoxImplMac()->getEditBox());
        pDelegate->editBoxReturn(getEditBoxImplMac()->getEditBox());
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    cocos2d::ui::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "ended",pEditBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "return", sizeof(data.eventName));
        event.data = (void*)&data;
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}


/**
 * Called each time when the text field's text has changed.
 */
- (void)controlTextDidChange:(NSNotification *)notification
{
    cocos2d::ui::EditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxTextChanged(getEditBoxImplMac()->getEditBox(), getEditBoxImplMac()->getText());
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    cocos2d::ui::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

@end


NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplMac(pEditBox);
}

EditBoxImplMac::EditBoxImplMac(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _anchorPoint(Vec2(0.5f, 0.5f))
, _maxTextLength(-1)
, _sysEdit(nullptr)
{
    //! TODO: Retina on Mac
    //! _inRetinaMode = [[CCEAGLView sharedEGLView] contentScaleFactor] == 2.0f ? true : false;
    _inRetinaMode = false;
}

EditBoxImplMac::~EditBoxImplMac()
{
    [_sysEdit release];
}

void EditBoxImplMac::doAnimationWhenKeyboardMove(float duration, float distance)
{
    if ([_sysEdit isEditState] || distance < 0.0f)
        [_sysEdit doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
}

bool EditBoxImplMac::initWithSize(const Size& size)
{
    GLView* eglView = Director::getInstance()->getOpenGLView();

    NSRect rect = NSMakeRect(0, 0, size.width * eglView->getScaleX(),size.height * eglView->getScaleY());

    if (_inRetinaMode) {
         rect.size.width /= 2.0f;
         rect.size.height /= 2.0f;
    }
    
    _sysEdit = [[UIEditBoxImplMac alloc] initWithFrame:rect editBox:this];
    
    if (!_sysEdit)
        return false;
    
    return true;
}

void EditBoxImplMac::setFont(const char* pFontName, int fontSize)
{
    NSString * fntName = [NSString stringWithUTF8String:pFontName];
    float retinaFactor = _inRetinaMode ? 2.0f : 1.0f;
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float scaleFactor = glview->getScaleX();
    NSFont *textFont = [NSFont fontWithName:fntName size:fontSize  * scaleFactor / retinaFactor];
    if (textFont != nil) {
        [_sysEdit.textField setFont:textFont];
        [_sysEdit.secureTextField setFont:textFont];
    }
}

void EditBoxImplMac::setPlaceholderFont(const char* pFontName, int fontSize)
{
    NSString *fontName = [NSString stringWithUTF8String:pFontName];
    float retinaFactor = _inRetinaMode ? 2.0f : 1.0f;
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float scaleFactor = glview->getScaleX();
    NSFont *font = [NSFont fontWithName:fontName size:fontSize  * scaleFactor / retinaFactor];
    
    if (!font) {
        CCLOGWARN("Font not found: %s", pFontName);
        return;
    }
    
    [_sysEdit.placeholderAttributes setObject:font forKey:NSFontAttributeName];
    
    /* reload placeholder */
    const char *placeholder = [_sysEdit.textField.cell placeholderAttributedString].string.UTF8String;
    if (placeholder) {
        setPlaceHolder(placeholder);
    }
}

void EditBoxImplMac::setFontColor(const Color4B& color)
{
    NSColor *newColor = [NSColor colorWithCalibratedRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:color.a / 255.f];
    _sysEdit.textField.textColor = newColor;
    _sysEdit.secureTextField.textColor = newColor;
}
    
void EditBoxImplMac::setPlaceholderFontColor(const Color4B& color)
{
    NSColor *nsColor = [NSColor colorWithCalibratedRed:color.r/255.f green:color.g / 255.f blue:color.b / 255.f alpha:color.a / 255.f];
    [_sysEdit.placeholderAttributes setObject:nsColor forKey:NSForegroundColorAttributeName];
    
    /* reload placeholder */
    const char *placeholder = [_sysEdit.textField.cell placeholderAttributedString].string.UTF8String;
    if (placeholder) {
        setPlaceHolder(placeholder);
    }
}

void EditBoxImplMac::setInputMode(EditBox::InputMode inputMode)
{
}

void EditBoxImplMac::setMaxLength(int maxLength)
{
    _maxTextLength = maxLength;
    id formater =  [[[CustomTextFieldFormatter alloc]init] autorelease];
    [formater setMaximumLength:maxLength];
    [_sysEdit.secureTextField setFormatter:formater];
    [_sysEdit.textField setFormatter:formater];
}

int EditBoxImplMac::getMaxLength()
{
    return _maxTextLength;
}

void EditBoxImplMac::setInputFlag(EditBox::InputFlag inputFlag)
{
    switch (inputFlag)
    {
        case EditBox::InputFlag::PASSWORD:
            _sysEdit.secure = YES;
            break;
        case EditBox::InputFlag::INITIAL_CAPS_WORD:
            CCLOGWARN("INITIAL_CAPS_WORD not implemented");
            break;
        case EditBox::InputFlag::INITIAL_CAPS_SENTENCE:
            CCLOGWARN("INITIAL_CAPS_SENTENCE not implemented");
            break;
        case EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS:
            CCLOGWARN("INTIAL_CAPS_ALL_CHARACTERS not implemented");
            break;
        case EditBox::InputFlag::SENSITIVE:
            CCLOGWARN("SENSITIVE not implemented");
            break;
        default:
            break;
    }
}

void EditBoxImplMac::setReturnType(EditBox::KeyboardReturnType returnType)
{
}

bool EditBoxImplMac::isEditing()
{
    return [_sysEdit isEditState] ? true : false;
}

void EditBoxImplMac::setText(const char* pText)
{
    NSString *string = [NSString stringWithUTF8String:pText];
    _sysEdit.textField.stringValue = string;
    _sysEdit.secureTextField.stringValue = string;
}

const char*  EditBoxImplMac::getText(void)
{
    if (_sysEdit.secureTextField.superview) {
        return [_sysEdit.secureTextField.stringValue UTF8String];
    }
    
    return [_sysEdit.textField.stringValue UTF8String];
}

void EditBoxImplMac::setPlaceHolder(const char* pText)
{
    NSAttributedString *as = [[NSAttributedString alloc] initWithString:[NSString stringWithUTF8String:pText]
                                                             attributes:_sysEdit.placeholderAttributes];
    
    [[_sysEdit.textField cell] setPlaceholderAttributedString:as];
    [[_sysEdit.secureTextField cell] setPlaceholderAttributedString:as];
    [as release];
}

NSPoint EditBoxImplMac::convertDesignCoordToScreenCoord(const Vec2& designCoord, bool bInRetinaMode)
{
    NSRect frame = [_sysEdit.textField frame];
    CGFloat height = frame.size.height;
    
    GLView* eglView = Director::getInstance()->getOpenGLView();

    Vec2 visiblePos = Vec2(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    Vec2 screenGLPos = visiblePos + eglView->getViewPortRect().origin;
    
    //TODO: I don't know why here needs to substract `height`.
    NSPoint screenPos = NSMakePoint(screenGLPos.x, screenGLPos.y-height);
    
    if (bInRetinaMode) {
        screenPos.x = screenPos.x / 2.0f;
        screenPos.y = screenPos.y / 2.0f;
    }
    
    CCLOGINFO("[EditBox] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}

void EditBoxImplMac::updatePosition(float dt)
{
    if(nullptr != _sysEdit)
    {
        adjustTextFieldPosition();
    }
}

void EditBoxImplMac::adjustTextFieldPosition()
{
    Size contentSize = _editBox->getContentSize();
    Rect rect = Rect(0, 0, contentSize.width, contentSize.height);

    rect = RectApplyAffineTransform(rect, _editBox->nodeToWorldTransform());
    
    Vec2 designCoord = Vec2(rect.origin.x, rect.origin.y + rect.size.height);
    [_sysEdit setPosition:convertDesignCoordToScreenCoord(designCoord, _inRetinaMode)];
}

void EditBoxImplMac::setPosition(const Vec2& pos)
{
    _position = pos;
    adjustTextFieldPosition();
}

void EditBoxImplMac::setVisible(bool visible)
{
    [_sysEdit.textField setHidden:!visible];
    [_sysEdit.secureTextField setHidden:!visible];
}

void EditBoxImplMac::setContentSize(const Size& size)
{
    _contentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
}

void EditBoxImplMac::setAnchorPoint(const Vec2& anchorPoint)
{
    CCLOG("[Edit text] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
    _anchorPoint = anchorPoint;
    setPosition(_position);
}

void EditBoxImplMac::visit(void)
{
    
}

void EditBoxImplMac::openKeyboard()
{
    [_sysEdit openKeyboard];
}

void EditBoxImplMac::closeKeyboard()
{
    [_sysEdit closeKeyboard];
}

void EditBoxImplMac::onEnter(void)
{
    adjustTextFieldPosition();
}

}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)


