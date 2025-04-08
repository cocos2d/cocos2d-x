#include "ui/UIEditBox/UIEditBoxImpl-ohos.h"
#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include "ui/UIEditBox/UIEditBox.h"
#include "2d/CCLabel.h"
#include "base/ccUTF8.h"
#include "math/Vec2.h"
#include "ui/UIHelper.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"
#include "platform/ohos/CCLogOhos.h"
#include "aki/jsbind.h"


NS_CC_BEGIN

namespace ui {

    static std::unordered_map<int, EditBoxImplOhos*> s_allEditBoxes;
    static int curIndex = 0;

    EditBoxImpl* __createSystemEditBox(EditBox* editBox)
    {
        return new EditBoxImplOhos(editBox);
    }

    void EditBoxImplOhos::createNativeControl(const Rect& frame)
    {
        OHOS_LOGD("create textinput");

        auto director = cocos2d::Director::getInstance();
        auto glView = director->getOpenGLView();
        auto frameSize = glView->getFrameSize();

        auto winSize = director->getWinSize();
        auto leftBottom = _editBox->convertToWorldSpace(Point::ZERO);

        auto contentSize = frame.size;
        auto rightTop = _editBox->convertToWorldSpace(Point(contentSize.width, contentSize.height));
        auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2) * glView->getScaleX();
        auto uiTop = frameSize.height / 2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();
        auto uiWidth = (rightTop.x - leftBottom.x) * glView->getScaleX();
        auto uiHeight = (rightTop.y - leftBottom.y) * glView->getScaleY();
        auto paddingW = (int)(5 * glView->getScaleX());
        auto paddingH = (int)(uiHeight * 0.33f / 2);

        s_allEditBoxes[curIndex] = this;
        _editBoxIndex = curIndex;
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.createCocosEditBox")) {
            function->Invoke<void>(_editBoxIndex, uiLeft, uiTop, uiWidth, uiHeight, paddingW, paddingH); 
        }
        curIndex++;
    }

    EditBoxImplOhos::EditBoxImplOhos(EditBox* pEditText)
        : EditBoxImplCommon(pEditText)
        , _editBoxIndex(-1)
    {

    }

    EditBoxImplOhos::~EditBoxImplOhos()
    {
        s_allEditBoxes.erase(_editBoxIndex);
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.removeCocosEditBox")) {
            function->Invoke<void>(_editBoxIndex); 
        }
    }

    bool EditBoxImplOhos::isEditing()
    {
        return false;
    }

    void EditBoxImplOhos::setNativeText(const char* pText)
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setCurrentText")) {
            function->Invoke<void>(_editBoxIndex, pText); 
        }
    }

    void EditBoxImplOhos::setNativeFont(const char* pFontName, int fontSize)
    {
        auto director = cocos2d::Director::getInstance();
        auto glView = director->getOpenGLView();
        auto isFontFileExists = cocos2d::FileUtils::getInstance()->isFileExist(pFontName);
        std::string realFontPath = pFontName;
        if (isFontFileExists) {
            realFontPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(pFontName);
            if (realFontPath.find("rawfile/") == 0)
            {
                realFontPath = realFontPath.substr(strlen("rawfile/"));   // Chop out the 'assets/' portion of the path.
            }
        }
        auto realFontsize = fontSize * glView->getScaleX();
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxFontSize")) {
            function->Invoke<void>(_editBoxIndex, realFontsize); 
        }
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxFontPath")) {
            function->Invoke<void>(_editBoxIndex, realFontPath); 
        }
    }

    void EditBoxImplOhos::setNativeFontColor(const Color4B& color)
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxFontColor")) {
            function->Invoke<void>(_editBoxIndex, (int)color.r, (int)color.g, (int)color.b, (int)color.a); 
        }
    }

    void EditBoxImplOhos::setNativePlaceHolder(const char* pText)
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxPlaceHolder")) {
            function->Invoke<void>(_editBoxIndex, pText); 
        }
    }

    void EditBoxImplOhos::setNativePlaceholderFont(const char* pFontName, int fontSize)
    {
        auto director = cocos2d::Director::getInstance();
        auto glView = director->getOpenGLView();
        auto isFontFileExists = cocos2d::FileUtils::getInstance()->isFileExist(pFontName);
        std::string realFontPath = pFontName;
        if (isFontFileExists) {
            realFontPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(pFontName);
            if (realFontPath.find("rawfile/") == 0)
            {
                realFontPath = realFontPath.substr(strlen("rawfile/"));   // Chop out the 'assets/' portion of the path.
            }
        }
        auto realFontsize = fontSize * glView->getScaleX();
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxPlaceHolderFontSize")) {
            function->Invoke<void>(_editBoxIndex, realFontsize); 
        }
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxPlaceHolderFontPath")) {
            function->Invoke<void>(_editBoxIndex, realFontPath); 
        }
    }

    void EditBoxImplOhos::setNativePlaceholderFontColor(const Color4B& color)
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxPlaceHolderFontColor")) {
            function->Invoke<void>(_editBoxIndex, (int)color.r, (int)color.g, (int)color.b, (int)color.a); 
        }
    }

    void EditBoxImplOhos::setNativeMaxLength(int maxLength)
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxMaxLength")) {
            function->Invoke<void>(_editBoxIndex, maxLength); 
        }
    }

    void EditBoxImplOhos::setNativeInputMode(EditBox::InputMode inputMode)
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setNativeInputMode")) {
            function->Invoke<void>(_editBoxIndex, static_cast<int>(inputMode)); 
        }
    }

    void EditBoxImplOhos::setNativeInputFlag(EditBox::InputFlag inputFlag)
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setNativeInputFlag")) {
            function->Invoke<void>(_editBoxIndex, static_cast<int>(inputFlag)); 
        }
    }

    void EditBoxImplOhos::setNativeReturnType(EditBox::KeyboardReturnType returnType)
    {
        OHOS_LOGW("OHOS not support returnType %{public}d", returnType);
    }

    void EditBoxImplOhos::setNativeVisible(bool visible)
    {   
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxVisible")) {
            function->Invoke<void>(_editBoxIndex, visible); 
        }
    }

    void EditBoxImplOhos::updateNativeFrame(const Rect& rect)
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxViewRect")) {
            function->Invoke<void>(_editBoxIndex, (int)rect.origin.x, (int)rect.origin.y, (int)rect.size.width, (int)rect.size.height); 
        }
    }

    void EditBoxImplOhos::nativeOpenKeyboard()
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxVisible")) {
            function->Invoke<void>(_editBoxIndex, true); 
        }
    }

    void EditBoxImplOhos::nativeCloseKeyboard()
    {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxVisible")) {
            function->Invoke<void>(_editBoxIndex, false); 
        }
    }

    void EditBoxImplOhos::hideAllEditBox() {
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.hideAllEditBox")) {
            function->Invoke<void>(); 
        }
    }

    void EditBoxImplOhos::onBeginCallBack(int index)
    {
        OHOS_LOGD("textinput editBoxEditingDidBegin");
        auto it = s_allEditBoxes.find(index);
        if (it != s_allEditBoxes.end())
        {
            s_allEditBoxes[index]->editBoxEditingDidBegin();
        }
    }

    void EditBoxImplOhos::onChangeCallBack(int index, const std::string& text)
    {
        OHOS_LOGD("textinput onChangeCallBack");
        auto it = s_allEditBoxes.find(index);
        if (it != s_allEditBoxes.end())
        {
            s_allEditBoxes[index]->editBoxEditingChanged(text);
        }
    }

    void EditBoxImplOhos::onEnterCallBack(int index, const std::string& text)
    {
        OHOS_LOGD("textinput onEnterCallBack");
        if (auto function = aki::JSBind::GetJSFunction("CocosEditBox.setEditBoxVisible")) {
            function->Invoke<void>(index, false); 
        }
        auto it = s_allEditBoxes.find(index);
        if (it != s_allEditBoxes.end())
        {
            s_allEditBoxes[index]->editBoxEditingDidEnd(text);
        }
    }

    const char* EditBoxImplOhos::getNativeDefaultFontName()
    {
        return "sans-serif";
    }
}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS) */
