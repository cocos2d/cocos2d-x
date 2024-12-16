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
#include "platform/ohos/napi/helper/NapiHelper.h"
#include "platform/ohos/CCLogOhos.h"
// destroy dialog when lost focus

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
        JSFunction::getFunction("CocosEditBox.createCocosEditBox").invoke<void>(_editBoxIndex, uiLeft, uiTop, uiWidth, uiHeight, paddingW, paddingH);
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
        JSFunction::getFunction("CocosEditBox.removeCocosEditBox").invoke<void>(_editBoxIndex);
    }

    bool EditBoxImplOhos::isEditing()
    {
        return false;
    }

    void EditBoxImplOhos::setNativeText(const char* pText)
    {
        JSFunction::getFunction("CocosEditBox.setCurrentText").invoke<void>(_editBoxIndex, pText);
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
        JSFunction::getFunction("CocosEditBox.setEditBoxFontSize").invoke<void>(_editBoxIndex, realFontsize);
        JSFunction::getFunction("CocosEditBox.setEditBoxFontPath").invoke<void>(_editBoxIndex, realFontPath);
    }

    void EditBoxImplOhos::setNativeFontColor(const Color3B& color)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxFontColor").invoke<void>(_editBoxIndex, (int)color.r, (int)color.g, (int)color.b, 255);
    }

    void EditBoxImplOhos::setNativePlaceHolder(const char* pText)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxPlaceHolder").invoke<void>(_editBoxIndex, pText);
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
        JSFunction::getFunction("CocosEditBox.setEditBoxPlaceHolderFontSize").invoke<void>(_editBoxIndex, realFontsize);
        JSFunction::getFunction("CocosEditBox.setEditBoxPlaceHolderFontPath").invoke<void>(_editBoxIndex, realFontPath);
    }

    void EditBoxImplOhos::setNativePlaceholderFontColor(const Color3B& color)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxPlaceHolderFontColor").invoke<void>(_editBoxIndex, (int)color.r, (int)color.g, (int)color.b, 255);
    }

    void EditBoxImplOhos::setNativeMaxLength(int maxLength)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxMaxLength").invoke<void>(_editBoxIndex, maxLength);
    }

    void EditBoxImplOhos::setNativeInputMode(EditBox::InputMode inputMode)
    {
        JSFunction::getFunction("CocosEditBox.setNativeInputMode").invoke<void>(_editBoxIndex, static_cast<int>(inputMode));
    }

    void EditBoxImplOhos::setNativeInputFlag(EditBox::InputFlag inputFlag)
    {
        JSFunction::getFunction("CocosEditBox.setNativeInputFlag").invoke<void>(_editBoxIndex, static_cast<int>(inputFlag));
    }

    void EditBoxImplOhos::setNativeReturnType(EditBox::KeyboardReturnType returnType)
    {
        OHOS_LOGW("OHOS not support returnType %{public}d", returnType);
    }

    void EditBoxImplOhos::setNativeVisible(bool visible)
    {   
        JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(_editBoxIndex, visible);
    }

    void EditBoxImplOhos::updateNativeFrame(const Rect& rect)
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxViewRect").invoke<void>(_editBoxIndex, (int)rect.origin.x, (int)rect.origin.y, (int)rect.size.width, (int)rect.size.height);
    }

    void EditBoxImplOhos::nativeOpenKeyboard()
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(_editBoxIndex, true);
    }

    void EditBoxImplOhos::nativeCloseKeyboard()
    {
        JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(_editBoxIndex, false);
    }

    void EditBoxImplOhos::hideAllEditBox() {
        JSFunction::getFunction("CocosEditBox.hideAllEditBox").invoke<void>();
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
        JSFunction::getFunction("CocosEditBox.setEditBoxVisible").invoke<void>(index, false);
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

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) */