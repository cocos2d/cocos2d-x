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
#import "EAGLView.h"

#define getEditBoxImplMac() ((cocos2d::extension::CCEditBoxImplMac*)editBox_)

@implementation CustomNSTextField

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


@implementation EditBoxImplMac

@synthesize textField = textField_;
@synthesize editState = editState_;
@synthesize editBox = editBox_;

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
        self.textField = [[[CustomNSTextField alloc] initWithFrame: frameRect] autorelease];
        if (!textField_) break;
        [textField_ setTextColor:[NSColor whiteColor]];
        textField_.font = [NSFont systemFontOfSize:frameRect.size.height*2/3]; //TODO need to delete hard code here.
        textField_.backgroundColor = [NSColor clearColor];
        [textField_ setup];
        textField_.delegate = self;
        [textField_ setDelegate:self];
        self.editBox = editBox;
        
        [[EAGLView sharedEGLView] addSubview:textField_];
        
        return self;
    }while(0);
    
    return nil;
}

-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance
{
    id eglView = [EAGLView sharedEGLView];
    [eglView doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
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
    cocos2d::extension::CCEditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidBegin(getEditBoxImplMac()->getCCEditBox());
    }
    
    cocos2d::extension::CCEditBox*  pEditBox= getEditBoxImplMac()->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
    }
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(NSTextField *)sender
{
    editState_ = NO;
    cocos2d::extension::CCEditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidEnd(getEditBoxImplMac()->getCCEditBox());
        pDelegate->editBoxReturn(getEditBoxImplMac()->getCCEditBox());
    }
    
    cocos2d::extension::CCEditBox*  pEditBox= getEditBoxImplMac()->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "ended",pEditBox);
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "return",pEditBox);
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
    cocos2d::extension::CCEditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxTextChanged(getEditBoxImplMac()->getCCEditBox(), getEditBoxImplMac()->getText());
    }
    
    cocos2d::extension::CCEditBox*  pEditBox= getEditBoxImplMac()->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
    }
}

@end

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplMac(pEditBox);
}

CCEditBoxImplMac::CCEditBoxImplMac(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText), m_pSysEdit(NULL), m_nMaxTextLength(-1)
, m_obAnchorPoint(ccp(0.5f, 0.5f))
{
    //! TODO: Retina on Mac
    //! m_bInRetinaMode = [[EAGLView sharedEGLView] contentScaleFactor] == 2.0f ? true : false;
    m_bInRetinaMode = false;
}

CCEditBoxImplMac::~CCEditBoxImplMac()
{
    [m_pSysEdit release];
}

void CCEditBoxImplMac::doAnimationWhenKeyboardMove(float duration, float distance)
{
    if ([m_pSysEdit isEditState] || distance < 0.0f)
        [m_pSysEdit doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
}

bool CCEditBoxImplMac::initWithSize(const CCSize& size)
{
    CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();

    NSRect rect = NSMakeRect(0, 0, size.width * eglView->getScaleX(),size.height * eglView->getScaleY());

    if (m_bInRetinaMode) {
         rect.size.width /= 2.0f;
         rect.size.height /= 2.0f;
    }
    
    m_pSysEdit = [[EditBoxImplMac alloc] initWithFrame:rect editBox:this];
    
    if (!m_pSysEdit)
        return false;
    
    return true;
}

void CCEditBoxImplMac::setFont(const char* pFontName, int fontSize)
{
    //TODO:
//	if(pFontName == NULL)
//		return;
//	NSString * fntName = [NSString stringWithUTF8String:pFontName];
//	UIFont *textFont = [UIFont fontWithName:fntName size:fontSize];
//	if(textFont != nil)
//		[m_pSysEdit.textField setFont:textFont];
}

void CCEditBoxImplMac::setPlaceholderFont(const char* pFontName, int fontSize)
{
	// TODO need to be implemented.
}

void CCEditBoxImplMac::setFontColor(const ccColor3B& color)
{
    m_pSysEdit.textField.textColor = [NSColor colorWithCalibratedRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
}

void CCEditBoxImplMac::setPlaceholderFontColor(const ccColor3B& color)
{
    // TODO need to be implemented.
}

void CCEditBoxImplMac::setInputMode(EditBoxInputMode inputMode)
{
}

void CCEditBoxImplMac::setMaxLength(int maxLength)
{
    m_nMaxTextLength = maxLength;
}

int CCEditBoxImplMac::getMaxLength()
{
    return m_nMaxTextLength;
}

void CCEditBoxImplMac::setInputFlag(EditBoxInputFlag inputFlag)
{
    // TODO: NSSecureTextField
}

void CCEditBoxImplMac::setReturnType(KeyboardReturnType returnType)
{
}

bool CCEditBoxImplMac::isEditing()
{
    return [m_pSysEdit isEditState] ? true : false;
}

void CCEditBoxImplMac::setText(const char* pText)
{
    m_pSysEdit.textField.stringValue = [NSString stringWithUTF8String:pText];
}

const char*  CCEditBoxImplMac::getText(void)
{
    return [m_pSysEdit.textField.stringValue UTF8String];
}

void CCEditBoxImplMac::setPlaceHolder(const char* pText)
{
    [[m_pSysEdit.textField cell] setPlaceholderString:[NSString stringWithUTF8String:pText]];
}

NSPoint CCEditBoxImplMac::convertDesignCoordToScreenCoord(const CCPoint& designCoord, bool bInRetinaMode)
{
    NSRect frame = [m_pSysEdit.textField frame];
    CGFloat height = frame.size.height;
    
    CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();

    CCPoint visiblePos = ccp(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    CCPoint screenGLPos = ccpAdd(visiblePos, eglView->getViewPortRect().origin);
    
    //TODO: I don't know why here needs to substract `height`.
    NSPoint screenPos = NSMakePoint(screenGLPos.x, screenGLPos.y-height);
    
    if (bInRetinaMode) {
        screenPos.x = screenPos.x / 2.0f;
        screenPos.y = screenPos.y / 2.0f;
    }
    
    CCLOG("[EditBox] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}

void CCEditBoxImplMac::adjustTextFieldPosition()
{
	CCSize contentSize = m_pEditBox->getContentSize();
	CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);

    rect = CCRectApplyAffineTransform(rect, m_pEditBox->nodeToWorldTransform());
	
	CCPoint designCoord = ccp(rect.origin.x, rect.origin.y + rect.size.height);
    [m_pSysEdit setPosition:convertDesignCoordToScreenCoord(designCoord, m_bInRetinaMode)];
}

void CCEditBoxImplMac::setPosition(const CCPoint& pos)
{
    m_obPosition = pos;
    adjustTextFieldPosition();
}

void CCEditBoxImplMac::setVisible(bool visible)
{
    [m_pSysEdit.textField setHidden:!visible];
}

void CCEditBoxImplMac::setContentSize(const CCSize& size)
{
    m_tContentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
}

void CCEditBoxImplMac::setAnchorPoint(const CCPoint& anchorPoint)
{
    CCLOG("[Edit text] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
	m_obAnchorPoint = anchorPoint;
	setPosition(m_obPosition);
}

void CCEditBoxImplMac::visit(void)
{
    
}

void CCEditBoxImplMac::openKeyboard()
{
    [m_pSysEdit openKeyboard];
}

void CCEditBoxImplMac::closeKeyboard()
{
    [m_pSysEdit closeKeyboard];
}

void CCEditBoxImplMac::onEnter(void)
{
    adjustTextFieldPosition();
}

NS_CC_EXT_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)


