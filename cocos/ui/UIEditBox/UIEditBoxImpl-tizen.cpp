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

#include "ui/UIEditBox/UIEditBoxImpl-tizen.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)

#include <Evas.h>
#include <Elementary.h>
#include <efl_extension.h>

#include "ui/UIEditBox/UIEditBox.h"
#include "2d/CCLabel.h"
#include "base/ccUTF8.h"


#include "platform/tizen/CCApplication-tizen.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplTizen(pEditBox);
}

EditBoxImplTizen::EditBoxImplTizen(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _label(nullptr)
, _labelPlaceHolder(nullptr)
, _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
, _editBoxInputFlag(EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS)
, _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
, _colText(Color3B::WHITE)
, _colPlaceHolder(Color3B::GRAY)
, _maxLength(-1)
{

}

EditBoxImplTizen::~EditBoxImplTizen()
{

}

void EditBoxImplTizen::doAnimationWhenKeyboardMove(float duration, float distance)
{ // don't need to be implemented on tizen platform.

}

static const int CC_EDIT_BOX_PADDING = 5;

bool EditBoxImplTizen::initWithSize(const Size& size)
{
    int fontSize = size.height-12;
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

void EditBoxImplTizen::setFont(const char* pFontName, int fontSize)
{
    if(_label != NULL) {
        _label->setSystemFontName(pFontName);
        _label->setSystemFontSize(fontSize);
    }

    if(_labelPlaceHolder != NULL) {
        _labelPlaceHolder->setSystemFontName(pFontName);
        _labelPlaceHolder->setSystemFontSize(fontSize);
    }
}

void EditBoxImplTizen::setFontColor(const Color4B& color)
{
    _colText = color;
    _label->setTextColor(color);
}

void EditBoxImplTizen::setPlaceholderFont(const char* pFontName, int fontSize)
{
    if(_labelPlaceHolder != NULL) {
        _labelPlaceHolder->setSystemFontName(pFontName);
        _labelPlaceHolder->setSystemFontSize(fontSize);
    }
}

void EditBoxImplTizen::setPlaceholderFontColor(const Color4B& color)
{
    _colPlaceHolder = color;
    _labelPlaceHolder->setTextColor(color);
}

void EditBoxImplTizen::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
}

void EditBoxImplTizen::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
}

int EditBoxImplTizen::getMaxLength()
{
    return _maxLength;
}

void EditBoxImplTizen::setInputFlag(EditBox::InputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
}

void EditBoxImplTizen::setReturnType(EditBox::KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
}

bool EditBoxImplTizen::isEditing()
{
    return false;
}

void EditBoxImplTizen::setText(const char* pText)
{
    if (pText != NULL)
    {
        _text = pText;

        if (_text.length() > 0)
        {
            _labelPlaceHolder->setVisible(false);

            std::string strToShow;

            if (EditBox::InputFlag::PASSWORD == _editBoxInputFlag)
            {
                long length = cc_utf8_strlen(_text.c_str(), -1);
                for (long i = 0; i < length; i++)
                {
                    strToShow.append("*");
                }
            }
            else
            {
                strToShow = _text;
            }

            _label->setString(strToShow.c_str());

            // Clip the text width to fit to the text box

            float fMaxWidth = _editSize.width - CC_EDIT_BOX_PADDING * 2;
            auto labelSize = _label->getContentSize();
            if(labelSize.width > fMaxWidth) {
                _label->setDimensions(fMaxWidth,labelSize.height);
            }
        }
        else
        {
            _labelPlaceHolder->setVisible(true);
            _label->setString("");
        }

    }
}

const char*  EditBoxImplTizen::getText(void)
{
    return _text.c_str();
}

void EditBoxImplTizen::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        _placeHolder = pText;
        if (_placeHolder.length() > 0 && _text.length() == 0)
        {
            _labelPlaceHolder->setVisible(true);
        }

        _labelPlaceHolder->setString(_placeHolder.c_str());
    }
}

void EditBoxImplTizen::setPosition(const Vec2& pos)
{ // don't need to be implemented on tizen platform.

}

void EditBoxImplTizen::setVisible(bool visible)
{ // don't need to be implemented on tizen platform.

}

void EditBoxImplTizen::setContentSize(const Size& size)
{ // don't need to be implemented on tizen platform.

}

void EditBoxImplTizen::setAnchorPoint(const Vec2& anchorPoint)
{ // don't need to be implemented on tizen platform.

}

void EditBoxImplTizen::visit(void)
{ // don't need to be implemented on tizen platform.

}

void EditBoxImplTizen::onEnter(void)
{ // don't need to be implemented on tizen platform.

}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    EditBoxImplTizen* thiz = (EditBoxImplTizen*)ctx;
    thiz->setText(pText);

    if (thiz->getDelegate() != NULL)
    {
        thiz->getDelegate()->editBoxTextChanged(thiz->getEditBox(), thiz->getText());
        thiz->getDelegate()->editBoxEditingDidEnd(thiz->getEditBox());
        thiz->getDelegate()->editBoxReturn(thiz->getEditBox());
    }

#if CC_ENABLE_SCRIPT_BINDING
    EditBox* pEditBox = thiz->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "ended", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "return", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

static Evas_Object * s_keypadWin = nullptr;

static void entry_back_cb(void *data, Evas_Object *obj, void *event_info)
{
    evas_object_del(s_keypadWin);
    s_keypadWin = nullptr;
}

static void entry_activated_cb(void *data, Evas_Object *obj, void *event_info)
{
    char *commit_str = (char *)event_info;
    const char* text = elm_entry_entry_get(obj);
    editBoxCallbackFunc(text, data);
    elm_entry_input_panel_hide(obj);
    evas_object_del(s_keypadWin);
    s_keypadWin = nullptr;
}

void EditBoxImplTizen::openKeyboard()
{
    if (s_keypadWin)
    {
        return;
    }

    if (_delegate != NULL)
    {
        _delegate->editBoxEditingDidBegin(_editBox);
    }

#if CC_ENABLE_SCRIPT_BINDING
    EditBox* pEditBox = this->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif

    Evas_Object* parent = Application::getInstance()->_win;
    GLView* glView = Director::getInstance()->getOpenGLView();
    Size frameSize = glView->getFrameSize();

    s_keypadWin = elm_win_add(parent, "cocos2d-x", ELM_WIN_BASIC);
    elm_win_autodel_set(s_keypadWin, EINA_TRUE);
    elm_win_conformant_set(s_keypadWin, EINA_TRUE);
    elm_win_alpha_set(s_keypadWin, EINA_TRUE);
    evas_object_show(s_keypadWin);
    eext_object_event_callback_add(s_keypadWin, EEXT_CALLBACK_BACK, entry_back_cb, this);
    int rots[2];
    rots[0] = (int)(elm_win_rotation_get(parent));
    rots[1] = rots[0] + 180 % 360;
    elm_win_wm_rotation_available_rotations_set(s_keypadWin, rots, 2);
    
    Evas_Object* bgFull = elm_bg_add(s_keypadWin);
    evas_object_color_set(bgFull, 0, 0, 0, 0xa0);
    evas_object_resize(bgFull, frameSize.width, frameSize.height);
    evas_object_show(bgFull);

    int height = frameSize.height / 10;
    Evas_Object* rectangle = elm_bg_add(bgFull);
    evas_object_resize(rectangle, frameSize.width, height);
    evas_object_move(rectangle, 0, height);
    evas_object_color_set(rectangle, 0xff, 0xff, 0xff, 0xff);
    evas_object_show(rectangle);

    Evas_Object* title = elm_entry_add(rectangle);
    evas_object_resize(title, frameSize.width, height);
    auto text = _placeHolder.c_str();
    auto richText = (char*)malloc(strlen(text) + 50);
    sprintf(richText,"<color=#ffffff>%s</>", text);
    elm_entry_entry_set(title, richText);
    elm_entry_editable_set(title, EINA_FALSE);
    //elm_entry_drag_disabled_set(title, EINA_TRUE);
    //elm_entry_drop_disabled_set(title, EINA_TRUE);
    evas_object_show(title);
    free(richText);

    Evas_Object* entry = elm_entry_add(bgFull);
    elm_object_focus_set(entry, EINA_TRUE);
    evas_object_resize(entry, frameSize.width, height);
    evas_object_move(entry, 0, height);
    elm_entry_single_line_set(entry, EINA_TRUE);
    elm_entry_line_wrap_set(entry, ELM_WRAP_MIXED);
    elm_entry_entry_set(entry, _text.c_str());
    evas_object_show(entry);
    elm_object_focus_set(entry, EINA_TRUE);
    eext_entry_selection_back_event_allow_set(entry, EINA_TRUE);
    Elm_Entry_Filter_Limit_Size limit_size = { 0, };
    limit_size.max_char_count = _maxLength;
    elm_entry_markup_filter_append(entry, elm_entry_filter_limit_size, &limit_size);
    elm_entry_input_panel_return_key_type_set(entry, ELM_INPUT_PANEL_RETURN_KEY_TYPE_DONE);
    elm_entry_prediction_allow_set(entry, EINA_FALSE);

    evas_object_smart_callback_add(entry, "activated", entry_activated_cb, this);

    switch(_editBoxInputFlag)
    {
    case EditBox::InputFlag::PASSWORD:
        elm_entry_password_set(entry, EINA_TRUE);
        elm_entry_input_panel_layout_set(entry, ELM_INPUT_PANEL_LAYOUT_EMAIL);
        break;
    case EditBox::InputFlag::SENSITIVE:
        elm_entry_input_hint_set(entry, ELM_INPUT_HINT_SENSITIVE_DATA);
        break;
    case EditBox::InputFlag::INITIAL_CAPS_WORD:
        elm_entry_autocapital_type_set(entry, ELM_AUTOCAPITAL_TYPE_WORD);
        break;
    case EditBox::InputFlag::INITIAL_CAPS_SENTENCE:
        elm_entry_autocapital_type_set(entry, ELM_AUTOCAPITAL_TYPE_SENTENCE);
        break;
    case EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS:
        elm_entry_autocapital_type_set(entry, ELM_AUTOCAPITAL_TYPE_ALLCHARACTER);
        break;
    }

    switch(_editBoxInputMode)
    {
    case EditBox::InputMode::ANY:
        break;
    case EditBox::InputMode::EMAIL_ADDRESS:
        elm_entry_input_panel_layout_set(entry, ELM_INPUT_PANEL_LAYOUT_EMAIL);
        break;
    case EditBox::InputMode::NUMERIC:
        elm_entry_input_panel_layout_set(entry, ELM_INPUT_PANEL_LAYOUT_NUMBER);
        break;
    case EditBox::InputMode::PHONE_NUMBER:
        elm_entry_input_panel_layout_set(entry, ELM_INPUT_PANEL_LAYOUT_PHONENUMBER);
        break;
    case EditBox::InputMode::URL:
        elm_entry_input_panel_layout_set(entry, ELM_INPUT_PANEL_LAYOUT_URL);
        break;
    case EditBox::InputMode::DECIMAL:
        elm_entry_input_panel_layout_set(entry, ELM_INPUT_PANEL_LAYOUT_HEX); //fixme?
        break;
    case EditBox::InputMode::SINGLE_LINE:
        break;
    }
}

void EditBoxImplTizen::closeKeyboard()
{

}

}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) */

