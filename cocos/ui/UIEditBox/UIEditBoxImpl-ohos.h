#ifndef __UIEDITBOXIMPLOHOS_H__
#define __UIEDITBOXIMPLOHOS_H__

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include "ui/UIEditBox/UIEditBoxImpl-common.h"

NS_CC_BEGIN

class Label;

namespace ui {

    class EditBox;

    class EditBoxImplOhos : public EditBoxImplCommon
    {
    public:
        /**
         * @js NA
         */
        EditBoxImplOhos(EditBox* pEditText);
        /**
         * @js NA
         * @lua NA
         */
        virtual ~EditBoxImplOhos();

        virtual bool isEditing() override;
        virtual void createNativeControl(const Rect& frame) override;
        virtual void setNativeFont(const char* pFontName, int fontSize) override ;
        virtual void setNativeFontColor(const Color4B& color) override ;
        virtual void setNativePlaceholderFont(const char* pFontName, int fontSize) override ;
        virtual void setNativePlaceholderFontColor(const Color4B& color) override ;
        virtual void setNativeInputMode(EditBox::InputMode inputMode) override ;
        virtual void setNativeInputFlag(EditBox::InputFlag inputFlag) override ;
        virtual void setNativeReturnType(EditBox::KeyboardReturnType returnType)override ;
        virtual void setNativeText(const char* pText) override ;
        virtual void setNativePlaceHolder(const char* pText) override ;
        virtual void setNativeVisible(bool visible) override ;
        virtual void updateNativeFrame(const Rect& rect) override ;
        virtual void setNativeContentSize(const Size& size) override {};
        virtual const char* getNativeDefaultFontName() override ;
        virtual void nativeOpenKeyboard() override ;
        virtual void nativeCloseKeyboard() override ;
        virtual void setNativeMaxLength(int maxLength) override;

        static void hideAllEditBox();
        static void onBeginCallBack(int index);
        static void onChangeCallBack(int index, const std::string& text);
        static void onEnterCallBack(int index, const std::string& text);

    private:
        virtual void doAnimationWhenKeyboardMove(float duration, float distance)override {};
        int _editBoxIndex;
    };


}


NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS) */

#endif /* __UIEDITBOXIMPLOHOS_H__ */