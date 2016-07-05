#ifndef __UIEditBoxIMPLEMCC_H__
#define __UIEditBoxIMPLEMCC_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN)

#include "UIEditBoxImpl-common.h"


NS_CC_BEGIN

namespace ui {

class EditBox;

class EditBoxImplEmcc : public EditBoxImpl
{
public:
    /**
     * @js NA
     */
    EditBoxImplEmcc(EditBox* pEditText);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImplEmcc();
    
    virtual bool initWithSize(const Size& size) override;
    virtual void setFont(const char* pFontName, int fontSize) override;
    virtual void setFontColor(const Color4B& color) override;
    virtual void setPlaceholderFont(const char* pFontName, int fontSize) override;
    virtual void setPlaceholderFontColor(const Color4B& color) override;
    virtual void setInputMode(EditBox::InputMode inputMode) override;
    virtual void setInputFlag(EditBox::InputFlag inputFlag) override;
    virtual void setMaxLength(int maxLength) override;
    virtual int  getMaxLength() override;
    virtual void setReturnType(EditBox::KeyboardReturnType returnType) override;
    virtual bool isEditing() override;
    
    virtual void setText(const char* pText) override;
    virtual const char* getText(void) override;
    virtual void setPlaceHolder(const char* pText) override;
    virtual void setPosition(const Vec2& pos) override;
    virtual void setVisible(bool visible) override;
    virtual void setContentSize(const Size& size) override;
    virtual void setAnchorPoint(const Vec2& anchorPoint) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void doAnimationWhenKeyboardMove(float duration, float distance) override;
    virtual void openKeyboard() override;
    virtual void closeKeyboard() override;
    virtual void updatePosition(float dt) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter(void) override;
    
protected:
    void adjustTextFieldPositionAndSize();
    void createFromJS();
    
    static void onEnterCallback(void *userData);
    
private:
    Vec2 _position;
    Vec2 _anchorPoint;
    Size _contentSize;
    int _maxTextLength = 0;
    EditBox::InputFlag _inputFlag;
    EditBox::InputMode _inputMode;
    
    std::string _fontName;
    std::string _text;
    std::string _placeholderText;
    
    Color4B _color;
    Color4B _placeholderColor;
    
    int _fontSize = 0;
    int _id = 0;
    bool _isDirty = true;
    bool _isCreate  = false;
};


}

NS_CC_END


#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN) */

#endif /* __UIEditBoxIMPLEMCC_H__ */

