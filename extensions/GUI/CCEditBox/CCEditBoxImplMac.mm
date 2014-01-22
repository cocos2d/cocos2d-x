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
@synthesize editState = editState_;
@synthesize editBox = editBox_;

- (id) getNSWindow {
    return glfwGetCocoaWindow(cocos2d::EGLView::getInstance()->getWindow());
}

- (void)dealloc
{
    [textField_ resignFirstResponder];
    [textField_ removeFromSuperview];
    self.textField = NULL;
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
        [textField_ setTextColor:[NSColor whiteColor]];
        textField_.font = [NSFont systemFontOfSize:frameRect.size.height*2/3]; //TODO need to delete hard code here.
        textField_.backgroundColor = [NSColor clearColor];
        [textField_ setup];
        textField_.delegate = self;
        [textField_ setDelegate:self];
        self.editBox = editBox;
        
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
    
    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
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
    
    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "ended",pEditBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName,0,64*sizeof(char));
        strncpy(data.eventName,"return",64);
        event.data = (void*)&data;
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
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
    
    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
}

@end

NS_CC_EXT_BEGIN

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplMac(pEditBox);
}

EditBoxImplMac::EditBoxImplMac(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _anchorPoint(Point(0.5f, 0.5f))
, _maxTextLength(-1)
, _sysEdit(NULL)
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
    EGLViewProtocol* eglView = EGLView::getInstance();

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
    //TODO:
//	if(pFontName == NULL)
//		return;
//	NSString * fntName = [NSString stringWithUTF8String:pFontName];
//	UIFont *textFont = [UIFont fontWithName:fntName size:fontSize];
//	if(textFont != nil)
//		[_sysEdit.textField setFont:textFont];
}

void EditBoxImplMac::setPlaceholderFont(const char* pFontName, int fontSize)
{
	// TODO need to be implemented.
}

void EditBoxImplMac::setFontColor(const Color3B& color)
{
    _sysEdit.textField.textColor = [NSColor colorWithCalibratedRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
}

void EditBoxImplMac::setPlaceholderFontColor(const Color3B& color)
{
    // TODO need to be implemented.
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
    [[_sysEdit.textField cell] setPlaceholderString:[NSString stringWithUTF8String:pText]];
}

NSPoint EditBoxImplMac::convertDesignCoordToScreenCoord(const Point& designCoord, bool bInRetinaMode)
{
    NSRect frame = [_sysEdit.textField frame];
    CGFloat height = frame.size.height;
    
    EGLViewProtocol* eglView = EGLView::getInstance();

    Point visiblePos = Point(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    Point screenGLPos = visiblePos + eglView->getViewPortRect().origin;
    
    //TODO: I don't know why here needs to substract `height`.
    NSPoint screenPos = NSMakePoint(screenGLPos.x, screenGLPos.y-height);
    
    if (bInRetinaMode) {
        screenPos.x = screenPos.x / 2.0f;
        screenPos.y = screenPos.y / 2.0f;
    }
    
    CCLOG("[EditBox] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}

void EditBoxImplMac::adjustTextFieldPosition()
{
	Size contentSize = _editBox->getContentSize();
	Rect rect = Rect(0, 0, contentSize.width, contentSize.height);

    rect = RectApplyAffineTransform(rect, _editBox->nodeToWorldTransform());
	
	Point designCoord = Point(rect.origin.x, rect.origin.y + rect.size.height);
    [_sysEdit setPosition:convertDesignCoordToScreenCoord(designCoord, _inRetinaMode)];
}

void EditBoxImplMac::setPosition(const Point& pos)
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

void EditBoxImplMac::setAnchorPoint(const Point& anchorPoint)
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


