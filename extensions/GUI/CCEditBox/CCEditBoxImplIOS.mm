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
#include "CCEditBox.h"
#import "EAGLView.h"
#import "EditBoxImplIOS.h"

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplIOS(pEditBox);
}

#define GET_IMPL ((EditBoxImplIOS*)m_pSysEdit)

CCEditBoxImplIOS::CCEditBoxImplIOS(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, m_pSysEdit(NULL)
, m_nMaxTextLength(-1)
{
    m_bInRetinaMode = [[EAGLView sharedEGLView] contentScaleFactor] == 2.0f ? true : false;
}

CCEditBoxImplIOS::~CCEditBoxImplIOS()
{
    [GET_IMPL release];
}

void CCEditBoxImplIOS::doAnimationWhenKeyboardMove(float duration, float distance)
{
    if ([GET_IMPL isEditState] || distance < 0.0f)
    {
        [GET_IMPL doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
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
        
        m_pSysEdit = [[EditBoxImplIOS alloc] initWithFrame:rect editBox:this];
        if (!m_pSysEdit) break;
        
        return true;
    }while (0);
    
    return false;
}

void CCEditBoxImplIOS::setFontColor(const ccColor3B& color)
{
    GET_IMPL.textField.textColor = [UIColor colorWithRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
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
            GET_IMPL.textField.keyboardType = UIKeyboardTypeEmailAddress;
            break;
        case kEditBoxInputModeNumeric:
            GET_IMPL.textField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
            break;
        case kEditBoxInputModePhoneNumber:
            GET_IMPL.textField.keyboardType = UIKeyboardTypePhonePad;
            break;
        case kEditBoxInputModeUrl:
            GET_IMPL.textField.keyboardType = UIKeyboardTypeURL;
            break;
        case kEditBoxInputModeDecimal:
            GET_IMPL.textField.keyboardType = UIKeyboardTypeDecimalPad;
            break;
        case kEditBoxInputModeSingleLine:
            GET_IMPL.textField.keyboardType = UIKeyboardTypeDefault;
            break;
        default:
            GET_IMPL.textField.keyboardType = UIKeyboardTypeDefault;
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
            GET_IMPL.textField.secureTextEntry = YES;
            break;
        case kEditBoxInputFlagInitialCapsWord:
            GET_IMPL.textField.autocapitalizationType = UITextAutocapitalizationTypeWords;
            break;
        case kEditBoxInputFlagInitialCapsSentence:
            GET_IMPL.textField.autocapitalizationType = UITextAutocapitalizationTypeSentences;
            break;
        case kEditBoxInputFlagInitialCapsAllCharacters:
            GET_IMPL.textField.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
            break;
        default:
            break;
    }
}

void CCEditBoxImplIOS::setReturnType(KeyboardReturnType returnType)
{
    switch (returnType) {
        case kKeyboardReturnTypeDefault:
            GET_IMPL.textField.returnKeyType = UIReturnKeyDefault;
            break;
        case kKeyboardReturnTypeDone:
            GET_IMPL.textField.returnKeyType = UIReturnKeyDone;
            break;
        case kKeyboardReturnTypeSend:
            GET_IMPL.textField.returnKeyType = UIReturnKeySend;
            break;
        case kKeyboardReturnTypeSearch:
            GET_IMPL.textField.returnKeyType = UIReturnKeySearch;
            break;
        case kKeyboardReturnTypeGo:
            GET_IMPL.textField.returnKeyType = UIReturnKeyGo;
            break;
        default:
            GET_IMPL.textField.returnKeyType = UIReturnKeyDefault;
            break;
    }
}

bool CCEditBoxImplIOS::isEditing()
{
    return [GET_IMPL isEditState] ? true : false;
}

void CCEditBoxImplIOS::setText(const char* pText)
{
    GET_IMPL.textField.text = [NSString stringWithUTF8String:pText];
}

const char*  CCEditBoxImplIOS::getText(void)
{
    return [GET_IMPL.textField.text UTF8String];
}

void CCEditBoxImplIOS::setPlaceHolder(const char* pText)
{
    GET_IMPL.textField.placeholder = [NSString stringWithUTF8String:pText];
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
    [GET_IMPL setPosition:convertDesignCoordToScreenCoord(ccp(pos.x-m_tContentSize.width/2, pos.y+m_tContentSize.height/2), m_bInRetinaMode)];
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
    [GET_IMPL openKeyboard];
}

void CCEditBoxImplIOS::closeKeyboard()
{
    [GET_IMPL closeKeyboard];
}

NS_CC_EXT_END

