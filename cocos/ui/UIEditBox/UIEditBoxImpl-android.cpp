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

#include "UIEditBoxImpl-android.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "UIEditBox.h"
#include <jni.h>
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "2d/CCLabel.h"
#include "base/ccUTF8.h"
#include "math/Vec2.h"
#include "ui/UIHelper.h"
#include "base/CCDirector.h"

NS_CC_BEGIN


namespace ui {

#define  LOGD(...)  __android_log_print(ANDROID_LOG_ERROR,"",__VA_ARGS__)
static void editBoxEditingDidBegin(int index);
static void editBoxEditingDidChanged(int index, const std::string& text);
static void editBoxEditingDidEnd(int index, const std::string& text);
extern "C"{
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxEditBoxHelper_editBoxEditingDidBegin(JNIEnv *env, jclass, jint index) {
        editBoxEditingDidBegin(index);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxEditBoxHelper_editBoxEditingChanged(JNIEnv *env, jclass, jint index, jstring text) {
        std::string textString = StringUtils::getStringUTFCharsJNI(env,text);
        editBoxEditingDidChanged(index, textString);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxEditBoxHelper_editBoxEditingDidEnd(JNIEnv *env, jclass, jint index, jstring text) {
        std::string textString = StringUtils::getStringUTFCharsJNI(env,text);
        editBoxEditingDidEnd(index, textString);
    }
}

static std::unordered_map<int, EditBoxImplAndroid*> s_allEditBoxes;


EditBoxImpl* __createSystemEditBox(EditBox* editBox)
{
    return new EditBoxImplAndroid(editBox);
}


EditBoxImplAndroid::EditBoxImplAndroid(EditBox* pEditText)
: EditBoxImplCommon(pEditText)
, _editBoxIndex(-1)
{
}

EditBoxImplAndroid::~EditBoxImplAndroid()
{
    s_allEditBoxes.erase(_editBoxIndex);
    removeEditBoxJNI(_editBoxIndex);
}

void EditBoxImplAndroid::createNativeControl(const Rect& frame)
{
    auto director = cocos2d::Director::getInstance();
    auto glView = director->getOpenGLView();
    auto frameSize = glView->getFrameSize();
    
    auto winSize = director->getWinSize();
    auto leftBottom = _editBox->convertToWorldSpace(Point::ZERO);
    
    auto contentSize = frame.size;
    auto rightTop = _editBox->convertToWorldSpace(Point(contentSize.width, contentSize.height));
    
    auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX();
    auto uiTop = frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();
    auto uiWidth = (rightTop.x - leftBottom.x) * glView->getScaleX();
    auto uiHeight = (rightTop.y - leftBottom.y) * glView->getScaleY();
    LOGD("scaleX = %f", glView->getScaleX());
    _editBoxIndex = addEditBoxJNI(uiLeft, uiTop, uiWidth, uiHeight, glView->getScaleX());
    s_allEditBoxes[_editBoxIndex] = this;
}

void EditBoxImplAndroid::setNativeFont(const char* pFontName, int fontSize)
{
    auto director = cocos2d::Director::getInstance();
    auto glView = director->getOpenGLView();
    setFontEditBoxJNI(_editBoxIndex, pFontName, fontSize * glView->getScaleX());
}

void EditBoxImplAndroid::setNativeFontColor(const Color4B& color)
{
    setFontColorEditBoxJNI(_editBoxIndex, color.r, color.g, color.b, color.a);
}

void EditBoxImplAndroid::setNativePlaceholderFont(const char* pFontName, int fontSize)
{
    CCLOG("Wraning! You can't change Andriod Hint fontName and fontSize");
}

void EditBoxImplAndroid::setNativePlaceholderFontColor(const Color4B& color)
{
    setPlaceHolderTextColorEditBoxJNI(_editBoxIndex, color.r, color.g, color.b, color.a);
}

void EditBoxImplAndroid::setNativeInputMode(EditBox::InputMode inputMode)
{
    setInputModeEditBoxJNI(_editBoxIndex, static_cast<int>(inputMode));
}

void EditBoxImplAndroid::setNativeMaxLength(int maxLength)
{
    setMaxLengthJNI(_editBoxIndex, maxLength);
}


void EditBoxImplAndroid::setNativeInputFlag(EditBox::InputFlag inputFlag)
{
    setInputFlagEditBoxJNI(_editBoxIndex, static_cast<int>(inputFlag));
}

void EditBoxImplAndroid::setNativeReturnType(EditBox::KeyboardReturnType returnType)
{
    setReturnTypeEditBoxJNI(_editBoxIndex, static_cast<int>(returnType));
}

bool EditBoxImplAndroid::isEditing()
{
    return false;
}

void EditBoxImplAndroid::setNativeText(const char* pText)
{
    setTextEditBoxJNI(_editBoxIndex, pText);
}

void EditBoxImplAndroid::setNativePlaceHolder(const char* pText)
{
    setPlaceHolderTextEditBoxJNI(_editBoxIndex, pText);
}


void EditBoxImplAndroid::setNativeVisible(bool visible)
{ // don't need to be implemented on android platform.
    setVisibleEditBoxJNI(_editBoxIndex, visible);
}

void EditBoxImplAndroid::updateNativeFrame(const Rect& rect)
{

    setEditBoxViewRectJNI(_editBoxIndex, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void EditBoxImplAndroid::nativeOpenKeyboard()
{
    //it will also open up the soft keyboard
    setVisibleEditBoxJNI(_editBoxIndex,true);
}


void EditBoxImplAndroid::nativeCloseKeyboard()
{
    closeEditBoxKeyboardJNI(_editBoxIndex);
}

void editBoxEditingDidBegin(int index)
{
    auto it = s_allEditBoxes.find(index);
    if (it != s_allEditBoxes.end())
    {
        s_allEditBoxes[index]->editBoxEditingDidBegin();
    }
}
void editBoxEditingDidChanged(int index, const std::string& text)
{
    auto it = s_allEditBoxes.find(index);
    if (it != s_allEditBoxes.end())
    {
        s_allEditBoxes[index]->editBoxEditingChanged(text);
    }
}

void editBoxEditingDidEnd(int index, const std::string& text)
{
    auto it = s_allEditBoxes.find(index);
    if (it != s_allEditBoxes.end())
    {
        s_allEditBoxes[index]->editBoxEditingDidEnd(text);
    }
}

const char* EditBoxImplAndroid::getNativeDefaultFontName()
{
    return "";
}

} //end of ui namespace

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) */

