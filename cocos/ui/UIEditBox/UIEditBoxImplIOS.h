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

#ifndef __UIEditBoxIMPLIOS_H__
#define __UIEditBoxIMPLIOS_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "extensions/ExtensionMacros.h"
#include "UIEditBoxImpl.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface UICustomUITextField : UITextField
{
}

@end


@interface UIEditBoxImplIOS_objc : NSObject <UITextFieldDelegate>
{
    UICustomUITextField* textField_;
    void* editBox_;
    BOOL editState_;
}

@property(nonatomic, retain) UITextField* textField;
@property(nonatomic, readonly, getter = isEditState) BOOL editState;
@property(nonatomic, assign) void* editBox;

-(id) initWithFrame: (CGRect) frameRect editBox: (void*) editBox;
-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance;
-(void) setPosition:(CGPoint) pos;
-(void) setContentSize:(CGSize) size;
-(void) visit;
-(void) openKeyboard;
-(void) closeKeyboard;

@end

NS_CC_BEGIN

namespace ui {

class EditBox;

class EditBoxImplIOS : public EditBoxImpl
{
public:
    /**
     * @js NA
     */
    EditBoxImplIOS(EditBox* pEditText);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImplIOS();
    
    virtual bool initWithSize(const Size& size);
    virtual void setFont(const char* pFontName, int fontSize);
    virtual void setFontColor(const Color3B& color);
    virtual void setPlaceholderFont(const char* pFontName, int fontSize);
    virtual void setPlaceholderFontColor(const Color3B& color);
    virtual void setInputMode(EditBox::InputMode inputMode);
    virtual void setInputFlag(EditBox::InputFlag inputFlag);
    virtual void setMaxLength(int maxLength);
    virtual int  getMaxLength();
    virtual void setReturnType(EditBox::KeyboardReturnType returnType);
    virtual bool isEditing();
    
    virtual void setText(const char* pText);
    virtual const char* getText(void);
    virtual void refreshInactiveText();
    virtual void setPlaceHolder(const char* pText);
    virtual void setPosition(const Vec2& pos);
    virtual void setVisible(bool visible);
    virtual void setContentSize(const Size& size);
	virtual void setAnchorPoint(const Vec2& anchorPoint);
    virtual void updatePosition(float dt) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void visit(void);
    /**
     * @js NA
     * @lua NA
     */
	virtual void onEnter(void);
    virtual void doAnimationWhenKeyboardMove(float duration, float distance);
    virtual void openKeyboard();
    virtual void closeKeyboard();
	
	virtual void onEndEditing();
private:
	void			initInactiveLabels(const Size& size);
	void			setInactiveText(const char* pText);
	void			adjustTextFieldPosition();
    void            placeInactiveLabels();
	
    Label*     _label;
    Label*     _labelPlaceHolder;
    Size          _contentSize;
    Vec2         _position;
    Vec2         _anchorPoint;
    UIEditBoxImplIOS_objc* _systemControl;
    int             _maxTextLength;
    bool            _inRetinaMode;
};


}

NS_CC_END


#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */

#endif /* __UIEditBoxIMPLIOS_H__ */

