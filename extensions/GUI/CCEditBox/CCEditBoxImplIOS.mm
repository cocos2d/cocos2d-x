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
#include "CCEditBoxImplIOS.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "CCEditBox.h"
#import "EAGLView.h"

#define getEditBoxImplIOS() ((cocos2d::extension::CCEditBoxImplIOS*)editBox_)

@implementation CustomUITextField
- (CGRect)textRectForBounds:(CGRect)bounds {
    float padding = 5.0f;
    return CGRectMake(bounds.origin.x + padding, bounds.origin.y + padding,
                      bounds.size.width - padding*2, bounds.size.height - padding*2);
}
- (CGRect)editingRectForBounds:(CGRect)bounds {
    return [self textRectForBounds:bounds];
}
@end


@implementation EditBoxImplIOS

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

-(id) initWithFrame: (CGRect) frameRect editBox: (void*) editBox
{
    self = [super init];
    
    do
    {
        if (self == nil) break;
        editState_ = NO;
        self.textField = [[[CustomUITextField alloc] initWithFrame: frameRect] autorelease];
        if (!textField_) break;
        [textField_ setTextColor:[UIColor whiteColor]];
        textField_.font = [UIFont systemFontOfSize:frameRect.size.height*2/3]; //TODO need to delete hard code here.
        textField_.backgroundColor = [UIColor clearColor];
        textField_.borderStyle = UITextBorderStyleNone;
        textField_.delegate = self;
        textField_.returnKeyType = UIReturnKeyDefault;
        [textField_ addTarget:self action:@selector(textChanged) forControlEvents:UIControlEventEditingChanged];
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

-(void) setPosition:(CGPoint) pos
{
    CGRect frame = [textField_ frame];
    frame.origin = pos;
    [textField_ setFrame:frame];
}

-(void) setContentSize:(CGSize) size
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

- (BOOL)textFieldShouldReturn:(UITextField *)sender
{
    if (sender == textField_) {
        [sender resignFirstResponder];
    }
    return NO;
}

-(void)animationSelector
{
    id eglView = [EAGLView sharedEGLView];
    [eglView doAnimationWhenAnotherEditBeClicked];
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)sender        // return NO to disallow editing.
{
    CCLOG("textFieldShouldBeginEditing...");
    editState_ = YES;
    id eglView = [EAGLView sharedEGLView];
    if ([eglView isKeyboardShown])
    {
        [self performSelector:@selector(animationSelector) withObject:nil afterDelay:0.0f];
    }
    cocos2d::extension::CCEditBoxDelegate* pDelegate = getEditBoxImplIOS()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidBegin(getEditBoxImplIOS()->getCCEditBox());
    }
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)sender
{
    CCLOG("textFieldShouldEndEditing...");
    editState_ = NO;
    
    cocos2d::extension::CCEditBoxDelegate* pDelegate = getEditBoxImplIOS()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidEnd(getEditBoxImplIOS()->getCCEditBox());
        pDelegate->editBoxReturn(getEditBoxImplIOS()->getCCEditBox());
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
- (BOOL)textField:(UITextField *) textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if (getEditBoxImplIOS()->getMaxLength() < 0)
    {
        return YES;
    }
    
    NSUInteger oldLength = [textField.text length];
    NSUInteger replacementLength = [string length];
    NSUInteger rangeLength = range.length;
    
    NSUInteger newLength = oldLength - rangeLength + replacementLength;
    
    return newLength <= getEditBoxImplIOS()->getMaxLength();
}

/**
 * Called each time when the text field's text has changed.
 */
- (void) textChanged
{
    // NSLog(@"text is %@", self.textField.text);
    cocos2d::extension::CCEditBoxDelegate* pDelegate = getEditBoxImplIOS()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxTextChanged(getEditBoxImplIOS()->getCCEditBox(), getEditBoxImplIOS()->getText());
    }
}

@end


NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplIOS(pEditBox);
}

CCEditBoxImplIOS::CCEditBoxImplIOS(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, m_systemControl(NULL)
, m_nMaxTextLength(-1)
{
    m_bInRetinaMode = [[EAGLView sharedEGLView] contentScaleFactor] == 2.0f ? true : false;
}

CCEditBoxImplIOS::~CCEditBoxImplIOS()
{
    [m_systemControl release];
}

void CCEditBoxImplIOS::doAnimationWhenKeyboardMove(float duration, float distance)
{
    if ([m_systemControl isEditState] || distance < 0.0f)
    {
        [m_systemControl doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
    }
}

bool CCEditBoxImplIOS::initWithSize(const CCSize& size)
{
    do 
    {
        CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();

        CGRect rect = CGRectMake(0, 0, size.width * eglView->getScaleX(),size.height * eglView->getScaleY());

        if (m_bInRetinaMode)
        {
            rect.size.width /= 2.0f;
            rect.size.height /= 2.0f;
        }
        
        m_systemControl = [[EditBoxImplIOS alloc] initWithFrame:rect editBox:this];
        if (!m_systemControl) break;
        
        return true;
    }while (0);
    
    return false;
}

void CCEditBoxImplIOS::setFontColor(const ccColor3B& color)
{
    m_systemControl.textField.textColor = [UIColor colorWithRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
}

void CCEditBoxImplIOS::setPlaceholderFontColor(const ccColor3B& color)
{
    // TODO need to be implemented.
}

void CCEditBoxImplIOS::setInputMode(EditBoxInputMode inputMode)
{
    switch (inputMode)
    {
        case kEditBoxInputModeEmailAddr:
            m_systemControl.textField.keyboardType = UIKeyboardTypeEmailAddress;
            break;
        case kEditBoxInputModeNumeric:
            m_systemControl.textField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
            break;
        case kEditBoxInputModePhoneNumber:
            m_systemControl.textField.keyboardType = UIKeyboardTypePhonePad;
            break;
        case kEditBoxInputModeUrl:
            m_systemControl.textField.keyboardType = UIKeyboardTypeURL;
            break;
        case kEditBoxInputModeDecimal:
            m_systemControl.textField.keyboardType = UIKeyboardTypeDecimalPad;
            break;
        case kEditBoxInputModeSingleLine:
            m_systemControl.textField.keyboardType = UIKeyboardTypeDefault;
            break;
        default:
            m_systemControl.textField.keyboardType = UIKeyboardTypeDefault;
            break;
    }
}

void CCEditBoxImplIOS::setMaxLength(int maxLength)
{
    m_nMaxTextLength = maxLength;
}

int CCEditBoxImplIOS::getMaxLength()
{
    return m_nMaxTextLength;
}

void CCEditBoxImplIOS::setInputFlag(EditBoxInputFlag inputFlag)
{
    switch (inputFlag)
    {
        case kEditBoxInputFlagPassword:
            m_systemControl.textField.secureTextEntry = YES;
            break;
        case kEditBoxInputFlagInitialCapsWord:
            m_systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeWords;
            break;
        case kEditBoxInputFlagInitialCapsSentence:
            m_systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeSentences;
            break;
        case kEditBoxInputFlagInitialCapsAllCharacters:
            m_systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
            break;
        default:
            break;
    }
}

void CCEditBoxImplIOS::setReturnType(KeyboardReturnType returnType)
{
    switch (returnType) {
        case kKeyboardReturnTypeDefault:
            m_systemControl.textField.returnKeyType = UIReturnKeyDefault;
            break;
        case kKeyboardReturnTypeDone:
            m_systemControl.textField.returnKeyType = UIReturnKeyDone;
            break;
        case kKeyboardReturnTypeSend:
            m_systemControl.textField.returnKeyType = UIReturnKeySend;
            break;
        case kKeyboardReturnTypeSearch:
            m_systemControl.textField.returnKeyType = UIReturnKeySearch;
            break;
        case kKeyboardReturnTypeGo:
            m_systemControl.textField.returnKeyType = UIReturnKeyGo;
            break;
        default:
            m_systemControl.textField.returnKeyType = UIReturnKeyDefault;
            break;
    }
}

bool CCEditBoxImplIOS::isEditing()
{
    return [m_systemControl isEditState] ? true : false;
}

void CCEditBoxImplIOS::setText(const char* pText)
{
    m_systemControl.textField.text = [NSString stringWithUTF8String:pText];
}

const char*  CCEditBoxImplIOS::getText(void)
{
    return [m_systemControl.textField.text UTF8String];
}

void CCEditBoxImplIOS::setPlaceHolder(const char* pText)
{
    m_systemControl.textField.placeholder = [NSString stringWithUTF8String:pText];
}

static CGPoint convertDesignCoordToScreenCoord(const CCPoint& designCoord, bool bInRetinaMode)
{
    CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();
    float viewH = (float)[[EAGLView sharedEGLView] getHeight];
    
    CCPoint visiblePos = ccp(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    CCPoint screenGLPos = ccpAdd(visiblePos, eglView->getViewPortRect().origin);
    
    CGPoint screenPos = CGPointMake(screenGLPos.x, viewH - screenGLPos.y);
    
    if (bInRetinaMode)
    {
        screenPos.x = screenPos.x / 2.0f;
        screenPos.y = screenPos.y / 2.0f;
    }
    CCLOG("[EditBox] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}

void CCEditBoxImplIOS::setPosition(const CCPoint& pos)
{
    //TODO should consider anchor point, the default value is (0.5, 0,5)
    [m_systemControl setPosition:convertDesignCoordToScreenCoord(ccp(pos.x-m_tContentSize.width/2, pos.y+m_tContentSize.height/2), m_bInRetinaMode)];
}

void CCEditBoxImplIOS::setContentSize(const CCSize& size)
{
    m_tContentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
}

void CCEditBoxImplIOS::visit(void)
{
    
}

void CCEditBoxImplIOS::openKeyboard()
{
    [m_systemControl openKeyboard];
}

void CCEditBoxImplIOS::closeKeyboard()
{
    [m_systemControl closeKeyboard];
}

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */


