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

#include "CCEditBoxImplMac.h"
#include "2d/CCDirector.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#include "CCEditBox.h"
#define GLFW_EXPOSE_NATIVE_NSGL
#define GLFW_EXPOSE_NATIVE_COCOA
#include "glfw3native.h"


#define getEditBoxImplMac() ((cocos2d::extension::EditBoxImplMac*)editBox_)



@implementation CCCustomNSTextField

- (CGRect)textRectForBounds:(CGRect)bounds {
    float padding = 5.0f;
    return CGRectMake(bounds.origin.x + padding, bounds.origin.y + padding,
                      bounds.size.width - padding*2, bounds.size.height - padding*2);
}
- (CGRect)editingRectForBounds:(CGRect)bounds {
    return [self textRectForBounds:bounds];
}

- (void)setup {
    [self setBordered:NO];
    [self setHidden:NO];
    [self setWantsLayer:YES];
}

@end


@implementation CCEditBoxImplMac

@synthesize textField = textField_;
@synthesize placeholderAttributes = placeholderAttributes_;
@synthesize editState = editState_;
@synthesize editBox = editBox_;

- (id) getNSWindow
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    return glfwGetCocoaWindow(glview->getWindow());
}

- (void)dealloc
{
    [textField_ resignFirstResponder];
    [textField_ removeFromSuperview];
    self.textField = NULL;
    [placeholderAttributes_ release];
    [super dealloc];
}

-(id) initWithFrame: (NSRect) frameRect editBox: (void*) editBox
{
    self = [super init];
    
    do
    {
        if (self == nil) break;
        editState_ = NO;
        self.textField = [[[CCCustomNSTextField alloc] initWithFrame: frameRect] autorelease];
        if (!textField_) break;
        NSFont *font = [NSFont systemFontOfSize:frameRect.size.height*2/3]; //TODO need to delete hard code here.
        textField_.textColor = [NSColor whiteColor];
        textField_.font = font;
        textField_.backgroundColor = [NSColor clearColor];
        [textField_ setup];
        textField_.delegate = self;
        self.editBox = editBox;
        self.placeholderAttributes = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                      font, NSFontAttributeName,
                                      [NSColor grayColor], NSForegroundColorAttributeName,
                                      nil];
        
        [[[self getNSWindow] contentView] addSubview:textField_];
        
        return self;
    }while(0);
    
    return nil;
}

-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance
{
    [[[self getNSWindow] contentView] doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
}

-(void) setPosition:(NSPoint) pos
{
    NSRect frame = [textField_ frame];
    frame.origin = pos;
    [textField_ setFrame:frame];
}

-(void) setContentSize:(NSSize) size
{
    
}

-(void) visit
{
    
}

-(void) openKeyboard
{
    [textField_ becomeFirstResponder];
}

-(void) closeKeyboard
{
    [textField_ resignFirstResponder];
    [textField_ removeFromSuperview];
}

- (BOOL)textFieldShouldReturn:(NSTextField *)sender
{
    if (sender == textField_) {
        [sender resignFirstResponder];
    }
    return NO;
}

-(void)animationSelector
{
}

- (BOOL)textFieldShouldBeginEditing:(NSTextField *)sender        // return NO to disallow editing.
{
    editState_ = YES;
    cocos2d::extension::EditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidBegin(getEditBoxImplMac()->getEditBox());
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(NSTextField *)sender
{
    editState_ = NO;
    cocos2d::extension::EditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidEnd(getEditBoxImplMac()->getEditBox());
        pDelegate->editBoxReturn(getEditBoxImplMac()->getEditBox());
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
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
    return YES;
}

/**
 * Delegate method called before the text has been changed.
 * @param textField The text field containing the text.
 * @param range The range of characters to be replaced.
 * @param string The replacement string.
 * @return YES if the specified text range should be replaced; otherwise, NO to keep the old text.
 */
- (BOOL)textField:(NSTextField *) textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if (getEditBoxImplMac()->getMaxLength() < 0)
    {
        return YES;
    }
    
    NSUInteger oldLength = [[textField stringValue] length];
    NSUInteger replacementLength = [string length];
    NSUInteger rangeLength = range.length;
    
    NSUInteger newLength = oldLength - rangeLength + replacementLength;
    
    return newLength <= getEditBoxImplMac()->getMaxLength();
}

/**
 * Called each time when the text field's text has changed.
 */
- (void)controlTextDidChange:(NSNotification *)notification
{
    cocos2d::extension::EditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxTextChanged(getEditBoxImplMac()->getEditBox(), getEditBoxImplMac()->getText());
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

@end

NS_CC_EXT_BEGIN

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplMac(pEditBox);
}

EditBoxImplMac::EditBoxImplMac(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _anchorPoint(Vector2(0.5f, 0.5f))
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
    GLViewProtocol* eglView = Director::getInstance()->getOpenGLView();

    NSRect rect = NSMakeRect(0, 0, size.width * eglView->getScaleX(),size.height * eglView->getScaleY());

    if (_inRetinaMode) {
         rect.size.width /= 2.0f;
         rect.size.height /= 2.0f;
    }
    
    _sysEdit = [[CCEditBoxImplMac alloc] initWithFrame:rect editBox:this];
    
    if (!_sysEdit)
        return false;
    
    return true;
}

void EditBoxImplMac::setFont(const char* pFontName, int fontSize)
{
	NSString * fntName = [NSString stringWithUTF8String:pFontName];
	NSFont *textFont = [NSFont fontWithName:fntName size:fontSize];
	if(textFont != nil)
		[_sysEdit.textField setFont:textFont];
}

void EditBoxImplMac::setPlaceholderFont(const char* pFontName, int fontSize)
{
    NSString *fontName = [NSString stringWithUTF8String:pFontName];
    NSFont *font = [NSFont fontWithName:fontName size:fontSize];
    
    if (!font) {
        CCLOGWARN("Font not found: %s", pFontName);
        return;
    }
    
    _sysEdit.placeholderAttributes[NSFontAttributeName] = font;
    
    /* reload placeholder */
    const char *placeholder = [_sysEdit.textField.cell placeholderAttributedString].string.UTF8String;
    if (placeholder) {
        setPlaceHolder(placeholder);
    }
}

void EditBoxImplMac::setFontColor(const Color3B& color)
{
    _sysEdit.textField.textColor = [NSColor colorWithCalibratedRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
}

void EditBoxImplMac::setPlaceholderFontColor(const Color3B& color)
{
    NSColor *nsColor = [NSColor colorWithCalibratedRed:color.r/255.f green:color.g / 255.f blue:color.b / 255.f alpha:1.0f];
    _sysEdit.placeholderAttributes[NSForegroundColorAttributeName] = nsColor;
    
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
}

int EditBoxImplMac::getMaxLength()
{
    return _maxTextLength;
}

void EditBoxImplMac::setInputFlag(EditBox::InputFlag inputFlag)
{
    // TODO: NSSecureTextField
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
    _sysEdit.textField.stringValue = [NSString stringWithUTF8String:pText];
}

const char*  EditBoxImplMac::getText(void)
{
    return [_sysEdit.textField.stringValue UTF8String];
}

void EditBoxImplMac::setPlaceHolder(const char* pText)
{
    NSAttributedString *as = [[NSAttributedString alloc] initWithString:[NSString stringWithUTF8String:pText]
                                                             attributes:_sysEdit.placeholderAttributes];
    
    [[_sysEdit.textField cell] setPlaceholderAttributedString:as];
    [as release];
}

NSPoint EditBoxImplMac::convertDesignCoordToScreenCoord(const Vector2& designCoord, bool bInRetinaMode)
{
    NSRect frame = [_sysEdit.textField frame];
    CGFloat height = frame.size.height;
    
    GLViewProtocol* eglView = Director::getInstance()->getOpenGLView();

    Vector2 visiblePos = Vector2(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    Vector2 screenGLPos = visiblePos + eglView->getViewPortRect().origin;
    
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
	
	Vector2 designCoord = Vector2(rect.origin.x, rect.origin.y + rect.size.height);
    [_sysEdit setPosition:convertDesignCoordToScreenCoord(designCoord, _inRetinaMode)];
}

void EditBoxImplMac::setPosition(const Vector2& pos)
{
    _position = pos;
    adjustTextFieldPosition();
}

void EditBoxImplMac::setVisible(bool visible)
{
    [_sysEdit.textField setHidden:!visible];
}

void EditBoxImplMac::setContentSize(const Size& size)
{
    _contentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
}

void EditBoxImplMac::setAnchorPoint(const Vector2& anchorPoint)
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

NS_CC_EXT_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)


