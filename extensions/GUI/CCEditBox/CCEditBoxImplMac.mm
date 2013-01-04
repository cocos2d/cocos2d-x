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
#include "CCEditBox.h"
#import "EAGLView.h"
#import "EditBoxImplMac.h"

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplMac(pEditBox);
}

#define GET_IMPL ((EditBoxImplMac*)m_pSysEdit)

CCEditBoxImplMac::CCEditBoxImplMac(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, m_pSysEdit(NULL)
, m_nMaxTextLength(-1)
{
    //! TODO: Retina on Mac
    //! m_bInRetinaMode = [[EAGLView sharedEGLView] contentScaleFactor] == 2.0f ? true : false;
    m_bInRetinaMode = false;
}

CCEditBoxImplMac::~CCEditBoxImplMac()
{
    [GET_IMPL release];
}

void CCEditBoxImplMac::doAnimationWhenKeyboardMove(float duration, float distance)
{
    if ([GET_IMPL isEditState] || distance < 0.0f)
    {
        [GET_IMPL doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
    }
}

bool CCEditBoxImplMac::initWithSize(const CCSize& size)
{
    do 
    {
        CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();

        NSRect rect = NSMakeRect(0, 0, size.width * eglView->getScaleX(),size.height * eglView->getScaleY());

        if (m_bInRetinaMode)
        {
             rect.size.width /= 2.0f;
             rect.size.height /= 2.0f;
        }
        
        m_pSysEdit = [[EditBoxImplMac alloc] initWithFrame:rect editBox:this];
        if (!m_pSysEdit) break;
        
        return true;
    }while (0);
    
    return false;
}

void CCEditBoxImplMac::setFontColor(const ccColor3B& color)
{
    GET_IMPL.textField.textColor = [NSColor colorWithCalibratedRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
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
    return [GET_IMPL isEditState] ? true : false;
}

void CCEditBoxImplMac::setText(const char* pText)
{
    GET_IMPL.textField.stringValue = [NSString stringWithUTF8String:pText];
}

const char*  CCEditBoxImplMac::getText(void)
{
    return [GET_IMPL.textField.stringValue UTF8String];
}

void CCEditBoxImplMac::setPlaceHolder(const char* pText)
{
    [[GET_IMPL.textField cell] setPlaceholderString:[NSString stringWithUTF8String:pText]];
}

static NSPoint convertDesignCoordToScreenCoord(const CCPoint& designCoord, bool bInRetinaMode)
{
    CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();
    float viewH = (float)[[EAGLView sharedEGLView] getHeight];
    
    CCPoint visiblePos = ccp(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    CCPoint screenGLPos = ccpAdd(visiblePos, eglView->getViewPortRect().origin);
    
    NSPoint screenPos = NSMakePoint(screenGLPos.x, viewH - screenGLPos.y);
    
    if (bInRetinaMode)
    {
        screenPos.x = screenPos.x / 2.0f;
        screenPos.y = screenPos.y / 2.0f;
    }
    CCLOG("[EditBox] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}

void CCEditBoxImplMac::setPosition(const CCPoint& pos)
{
    //TODO should consider anchor point, the default value is (0.5, 0,5)
    [GET_IMPL setPosition:convertDesignCoordToScreenCoord(ccp(pos.x-m_tContentSize.width/2, pos.y+m_tContentSize.height/2), m_bInRetinaMode)];
}

void CCEditBoxImplMac::setContentSize(const CCSize& size)
{
    m_tContentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
}

void CCEditBoxImplMac::visit(void)
{
    
}

void CCEditBoxImplMac::openKeyboard()
{
    [GET_IMPL openKeyboard];
}

void CCEditBoxImplMac::closeKeyboard()
{
    [GET_IMPL closeKeyboard];
}

NS_CC_EXT_END

