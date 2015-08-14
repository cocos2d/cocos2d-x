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
#include "jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "2d/CCLabel.h"
#include "base/ccUTF8.h"
#include "math/Vec2.h"
#include "ui/UIHelper.h"
#include "base/ccUTF8.h"

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

void EditBoxImplAndroid::editBoxEditingDidBegin()
{
    // LOGD("textFieldShouldBeginEditing...");
    cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();

    if (pDelegate != nullptr)
    {
        pDelegate->editBoxEditingDidBegin(_editBox);
    }

#if CC_ENABLE_SCRIPT_BINDING
    if (NULL != _editBox && 0 != _editBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(_editBox->getScriptEditBoxHandler(), "began", _editBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

void EditBoxImplAndroid::editBoxEditingDidEnd(const std::string& text)
{
    // LOGD("textFieldShouldEndEditing...");
    _text = text;
    this->refreshInactiveText();
    
    cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxEditingDidEnd(_editBox);
        pDelegate->editBoxReturn(_editBox);
    }

#if CC_ENABLE_SCRIPT_BINDING
    if (_editBox != nullptr && 0 != _editBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(_editBox->getScriptEditBoxHandler(), "ended", _editBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "return", sizeof(data.eventName));
        event.data = (void *)&data;
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif

    if (_editBox != nullptr)
    {
        this->onEndEditing(text);
    }
}

void EditBoxImplAndroid::editBoxEditingChanged(const std::string& text)
{
    // LOGD("editBoxTextChanged...");
    cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();
    _text = text;
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxTextChanged(_editBox, text);
    }

#if CC_ENABLE_SCRIPT_BINDING
    if (NULL != _editBox && 0 != _editBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(_editBox->getScriptEditBoxHandler(), "changed", _editBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

EditBoxImplAndroid::EditBoxImplAndroid(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _label(nullptr)
, _labelPlaceHolder(nullptr)
, _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
, _editBoxInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS)
, _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
, _colText(Color3B::WHITE)
, _colPlaceHolder(Color3B::GRAY)
, _maxLength(-1)
, _editBoxIndex(-1)
{
}

EditBoxImplAndroid::~EditBoxImplAndroid()
{
    s_allEditBoxes.erase(_editBoxIndex);
    removeEditBoxJNI(_editBoxIndex);
}

void EditBoxImplAndroid::doAnimationWhenKeyboardMove(float duration, float distance)
{ // don't need to be implemented on android platform.
	
}

static const int CC_EDIT_BOX_PADDING = 5;

bool EditBoxImplAndroid::initWithSize(const Size& size)
{
    auto rect = Rect(0,0, size.width, size.height);
    _editBoxIndex = addEditBoxJNI(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    s_allEditBoxes[_editBoxIndex] = this;

    _label = Label::create();
    _label->setSystemFontSize(size.height-12);
	// align the text vertically center
    _label->setAnchorPoint(Vec2(0, 0.5f));
    _label->setPosition(Vec2(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _label->setTextColor(_colText);
    _editBox->addChild(_label);
	
    _labelPlaceHolder = Label::create();
    _labelPlaceHolder->setSystemFontSize(size.height-12);
	// align the text vertically center
    _labelPlaceHolder->setAnchorPoint(Vec2(0, 0.5f));
    _labelPlaceHolder->setPosition(CC_EDIT_BOX_PADDING, size.height / 2.0f);
    _labelPlaceHolder->setVisible(false);
    _labelPlaceHolder->setTextColor(_colPlaceHolder);
    _editBox->addChild(_labelPlaceHolder);
    
    _editSize = size;
    return true;
}

void EditBoxImplAndroid::setFont(const char* pFontName, int fontSize)
{
  if(_label != NULL)
  {
      if(strlen(pFontName) > 0)
      {
          _label->setSystemFontName(pFontName);
      }
      if(fontSize > 0)
      {
          _label->setSystemFontSize(fontSize);
      }
  }
	
  if(_labelPlaceHolder != NULL)
  {
      if(strlen(pFontName) > 0)
      {
          _labelPlaceHolder->setSystemFontName(pFontName);
      }
      if(fontSize > 0)
      {
          _labelPlaceHolder->setSystemFontSize(fontSize);
      }
  }
  setFontEditBoxJNI(_editBoxIndex, pFontName, fontSize);
}

void EditBoxImplAndroid::setFontColor(const Color4B& color)
{
    _colText = color;
    _label->setTextColor(color);
    setFontColorEditBoxJNI(_editBoxIndex, color.r, color.g, color.b, color.a);
}

void EditBoxImplAndroid::setPlaceholderFont(const char* pFontName, int fontSize)
{
  if(_labelPlaceHolder != NULL)
  {
      if(strlen(pFontName) > 0)
      {
          _labelPlaceHolder->setSystemFontName(pFontName);
      }
      if(fontSize > 0)
      {
          _labelPlaceHolder->setSystemFontSize(fontSize);
      }
  }
  CCLOG("Wraning! You can't change Andriod Hint fontName and fontSize");
}

void EditBoxImplAndroid::setPlaceholderFontColor(const Color4B& color)
{
    _colPlaceHolder = color;
    _labelPlaceHolder->setTextColor(color);
    setPlaceHolderTextColorEditBoxJNI(_editBoxIndex, color.r, color.g, color.b, color.a);
}

void EditBoxImplAndroid::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
    setInputModeEditBoxJNI(_editBoxIndex, static_cast<int>(inputMode));
}

void EditBoxImplAndroid::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
    setMaxLengthJNI(_editBoxIndex, _maxLength);
}

int EditBoxImplAndroid::getMaxLength()
{
    return _maxLength;
}

void EditBoxImplAndroid::setInputFlag(EditBox::InputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
    setInputFlagEditBoxJNI(_editBoxIndex, static_cast<int>(inputFlag));
}

void EditBoxImplAndroid::setReturnType(EditBox::KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
    setReturnTypeEditBoxJNI(_editBoxIndex, static_cast<int>(returnType));
}

bool EditBoxImplAndroid::isEditing()
{
    return false;
}

void EditBoxImplAndroid::setInactiveText(const char* pText)
{
    if(EditBox::InputFlag::PASSWORD == _editBoxInputFlag)
    {
        std::string passwordString;
        for(int i = 0; i < strlen(pText); ++i)
            passwordString.append("\u25CF");
        _label->setString(passwordString.c_str());
    }
    else
    {
        _label->setString(pText);
    }
    // Clip the text width to fit to the text box
    float fMaxWidth = _editBox->getContentSize().width - CC_EDIT_BOX_PADDING * 2;
    Size labelSize = _label->getContentSize();
    if(labelSize.width > fMaxWidth) {
        _label->setDimensions(fMaxWidth,labelSize.height);
    }
}

void  EditBoxImplAndroid::refreshInactiveText()
{
    setInactiveText(_text.c_str());
    if(_text.size() == 0)
    {
        _label->setVisible(false);
        _labelPlaceHolder->setVisible(true);
    }
    else
    {
        _label->setVisible(true);
        _labelPlaceHolder->setVisible(false);
    }
}
void EditBoxImplAndroid::setText(const char* pText)
{
    setTextEditBoxJNI(_editBoxIndex, pText);
    _text = pText;
    refreshInactiveText();
}

const char*  EditBoxImplAndroid::getText(void)
{
    return _text.c_str();
}

void EditBoxImplAndroid::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        _placeHolder = pText;
        if (_placeHolder.length() > 0 && _text.length() == 0)
        {
            _labelPlaceHolder->setVisible(true);
        }
		
        _labelPlaceHolder->setString(_placeHolder.c_str());
        setPlaceHolderTextEditBoxJNI(_editBoxIndex, pText);
    }
}

void EditBoxImplAndroid::setPosition(const Vec2& pos)
{ // don't need to be implemented on android platform.
}

void EditBoxImplAndroid::setVisible(bool visible)
{ // don't need to be implemented on android platform.
    setVisibleEditBoxJNI(_editBoxIndex, visible);
}

void EditBoxImplAndroid::setContentSize(const Size& size)
{ // don't need to be implemented on android platform.
}

void EditBoxImplAndroid::setAnchorPoint(const Vec2& anchorPoint)
{ // don't need to be implemented on android platform.
}

void EditBoxImplAndroid::draw(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{ // don't need to be implemented on android platform.
    if(parentFlags)
    {
        auto rect = ui::Helper::convertBoundingBoxToScreen(_editBox);
        setEditBoxViewRectJNI(_editBoxIndex, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    }
}

void EditBoxImplAndroid::onEnter(void)
{ // don't need to be implemented on android platform.
}

void EditBoxImplAndroid::openKeyboard()
{
    _label->setVisible(false);
    _labelPlaceHolder->setVisible(false);

    //it will also open up the soft keyboard
    setVisibleEditBoxJNI(_editBoxIndex,true);
}


void EditBoxImplAndroid::closeKeyboard()
{
    closeEditBoxKeyboardJNI(_editBoxIndex);
}

void EditBoxImplAndroid::onEndEditing(const std::string& text)
{
    setVisibleEditBoxJNI(_editBoxIndex, false);
    if(text.size() == 0)
    {
        _label->setVisible(false);
        _labelPlaceHolder->setVisible(true);
    }
    else
    {
        _label->setVisible(true);
        _labelPlaceHolder->setVisible(false);
        setInactiveText(text.c_str());
    }
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
} //end of ui namespace

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) */

