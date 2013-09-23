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

#ifndef __CCEditBoxIMPLMAC_H__
#define __CCEditBoxIMPLMAC_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#include "ExtensionMacros.h"
#include "CCEditBoxImpl.h"

@interface CustomNSTextField : NSTextField
{
}

@end

@interface EditBoxImplMac : NSObject <NSTextFieldDelegate>
{
    CustomNSTextField* textField_;
    void* editBox_;
    BOOL editState_;
}

@property(nonatomic, retain) NSTextField* textField;
@property(nonatomic, readonly, getter = isEditState) BOOL editState;
@property(nonatomic, assign) void* editBox;

-(id) initWithFrame: (NSRect) frameRect editBox: (void*) editBox;
-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance;
-(void) setPosition:(NSPoint) pos;
-(void) setContentSize:(NSSize) size;
-(void) visit;
-(void) openKeyboard;
-(void) closeKeyboard;

@end

NS_CC_EXT_BEGIN

class CCEditBox;
/**
 *  @js NA
 *  @lua NA
 */
class CCEditBoxImplMac : public CCEditBoxImpl
{
public:
    CCEditBoxImplMac(CCEditBox* pEditText);
    virtual ~CCEditBoxImplMac();
    
    virtual bool initWithSize(const CCSize& size);
    virtual void setFont(const char* pFontName, int fontSize);
    virtual void setFontColor(const ccColor3B& color);
    virtual void setPlaceholderFont(const char* pFontName, int fontSize);
    virtual void setPlaceholderFontColor(const ccColor3B& color);
    virtual void setInputMode(EditBoxInputMode inputMode);
    virtual void setInputFlag(EditBoxInputFlag inputFlag);
    virtual void setMaxLength(int maxLength);
    virtual int  getMaxLength();
    virtual void setReturnType(KeyboardReturnType returnType);
    virtual bool isEditing();
    
    virtual void setText(const char* pText);
    virtual const char* getText(void);
    virtual void setPlaceHolder(const char* pText);
    virtual void setPosition(const CCPoint& pos);
    virtual void setVisible(bool visible);
    virtual void setContentSize(const CCSize& size);
    virtual void setAnchorPoint(const CCPoint& anchorPoint);
    virtual void visit(void);
    virtual void doAnimationWhenKeyboardMove(float duration, float distance);
    virtual void openKeyboard();
    virtual void closeKeyboard();
    virtual void onEnter(void);
private:
    NSPoint    convertDesignCoordToScreenCoord(const CCPoint& designCoord, bool bInRetinaMode);
    void       adjustTextFieldPosition();
    CCSize     m_tContentSize;
    CCPoint    m_obPosition;
    CCPoint    m_obAnchorPoint;
    int        m_nMaxTextLength;
    bool       m_bInRetinaMode;
    EditBoxImplMac*  m_pSysEdit;
};


NS_CC_EXT_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#endif /* __CCEditBoxIMPLMAC_H__ */

