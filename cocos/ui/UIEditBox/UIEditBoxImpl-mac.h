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

#ifndef __UIEditBoxIMPLMAC_H__
#define __UIEditBoxIMPLMAC_H__

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#include "UIEditBoxImpl.h"


@interface UIEditBoxImplMac : NSObject <NSTextFieldDelegate>
{
    NSTextField* textField_;
    NSSecureTextField* secureTextField_;
    void* editBox_;
    BOOL editState_;
    NSMutableDictionary* placeholderAttributes_;
}

@property(nonatomic, retain) NSTextField* textField;
@property(nonatomic, retain) NSSecureTextField* secureTextField;
@property(nonatomic, retain) NSMutableDictionary* placeholderAttributes;
@property(nonatomic, readonly, getter = isEditState) BOOL editState;
@property(nonatomic, assign) void* editBox;
@property(nonatomic, assign, getter = isSecure) BOOL secure;

-(id) initWithFrame: (NSRect) frameRect editBox: (void*) editBox;
-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance;
-(void) setPosition:(NSPoint) pos;
-(void) setContentSize:(NSSize) size;
-(void) visit;
-(void) openKeyboard;
-(void) closeKeyboard;

@end


NS_CC_BEGIN

namespace ui {
    
class EditBox;

class EditBoxImplMac : public EditBoxImpl
{
public:
    /**
     * @js NA
     */
    EditBoxImplMac(EditBox* pEditText);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImplMac();
    
    virtual bool initWithSize(const Size& size);
    virtual void setFont(const char* pFontName, int fontSize);
    virtual void setFontColor(const Color4B& color);
    virtual void setPlaceholderFont(const char* pFontName, int fontSize);
    virtual void setPlaceholderFontColor(const Color4B& color);
    virtual void setInputMode(EditBox::InputMode inputMode);
    virtual void setInputFlag(EditBox::InputFlag inputFlag);
    virtual void setMaxLength(int maxLength);
    virtual int  getMaxLength();
    virtual void setReturnType(EditBox::KeyboardReturnType returnType);
    virtual bool isEditing();
    
    virtual void setText(const char* pText);
    virtual const char* getText(void);
    virtual void setPlaceHolder(const char* pText);
    virtual void setPosition(const Vec2& pos);
    virtual void setVisible(bool visible);
    virtual void setContentSize(const Size& size);
    virtual void setAnchorPoint(const Vec2& anchorPoint);
    /**
     * @js NA
     * @lua NA
     */
    virtual void visit(void);
    virtual void doAnimationWhenKeyboardMove(float duration, float distance);
    virtual void openKeyboard();
    virtual void closeKeyboard();
    virtual void updatePosition(float dt) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter(void);
private:
    NSPoint    convertDesignCoordToScreenCoord(const Vec2& designCoord, bool bInRetinaMode);
    void       adjustTextFieldPosition();
    Size     _contentSize;
    Vec2    _position;
    Vec2    _anchorPoint;
    int        _maxTextLength;
    bool       _inRetinaMode;
    UIEditBoxImplMac*  _sysEdit;
};


}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#endif /* __UIEditBoxIMPLMAC_H__ */

