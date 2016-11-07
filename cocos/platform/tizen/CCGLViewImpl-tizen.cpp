/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN

#include "platform/tizen/CCGLViewImpl-tizen.h"
#include <app.h>
#include <Evas.h>
#include <Elementary.h>
#include <efl_extension.h>
#include "platform/CCApplication.h"
#include "base/CCIMEDispatcher.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

GLViewImpl* GLViewImpl::createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    auto ret = new GLViewImpl;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLViewImpl* GLViewImpl::create(const std::string& viewName)
{
    auto ret = new GLViewImpl;
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(const std::string& viewName)
{
    auto ret = new GLViewImpl();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}

GLViewImpl::GLViewImpl()
{

}

GLViewImpl::~GLViewImpl()
{

}

bool GLViewImpl::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    return true;
}

bool GLViewImpl::initWithFullScreen(const std::string& viewName)
{
    return true;
}


bool GLViewImpl::isOpenGLReady()
{
    return (_screenSize.width != 0 && _screenSize.height != 0);
}

void GLViewImpl::end()
{
	ui_app_exit();
}

void GLViewImpl::swapBuffers()
{
}

//============================================================================================
static Evas_Object * s_keypadWin = nullptr;
static Evas_Object * s_keypadEntry = nullptr;
Ecore_IMF_Context *s_imf = nullptr;

static void imfEventCommitCallback(void *data, Ecore_IMF_Context *ctx, void *event_info)
{
    auto commit_str = (char *)event_info;
    if (commit_str)
    {
        cocos2d::IMEDispatcher::sharedDispatcher()->dispatchInsertText(commit_str, strlen(commit_str));
    }
}

static void entryKeyCallback(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
    auto keyInfo = (Evas_Event_Key_Up*)event_info;
    if (keyInfo->key && !strcmp(keyInfo->key,"BackSpace"))
    {
        cocos2d::IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
    }
}

static void stateChangedCallback(void *data, Ecore_IMF_Context *ctx, int value)
{
    if (value == ECORE_IMF_INPUT_PANEL_STATE_HIDE)
    {
        evas_object_del(s_keypadWin);
        s_keypadWin = nullptr;
        s_imf = nullptr;
    }
}

static void closeKeypad()
{
    ecore_imf_context_input_panel_event_callback_add (s_imf, ECORE_IMF_INPUT_PANEL_STATE_EVENT, stateChangedCallback, NULL);
    elm_entry_input_panel_hide(s_keypadEntry);
}

static void entryActivatedCallback(void *data, Evas_Object *obj, void *event_info)
{
    closeKeypad();
}

static void keyPadBackCallback(void *data, Evas_Object *obj, void *event_info)
{
    closeKeypad();
}

static void blankAreaClickedCallback(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
    closeKeypad();
}

void GLViewImpl::setIMEKeyboardState(bool open)
{
    if (open)
    {
        if (!s_keypadWin)
        {
            auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
            auto app = Application::getInstance();

            s_keypadWin = elm_win_add(app->_win, "cocos2d-x textfield", ELM_WIN_BASIC);
            elm_win_autodel_set(s_keypadWin, EINA_TRUE);
            elm_win_conformant_set(s_keypadWin, EINA_TRUE);
            elm_win_alpha_set(s_keypadWin, EINA_TRUE);
            eext_object_event_callback_add(s_keypadWin, EEXT_CALLBACK_BACK, keyPadBackCallback, NULL);
            evas_object_show(s_keypadWin);

            int rots[2];
            rots[0] = (int)elm_win_rotation_get(app->_win);
            rots[1] = rots[0] + 180 % 360;
            elm_win_wm_rotation_available_rotations_set(s_keypadWin, rots, 2);

            auto rectangle = elm_bg_add(s_keypadWin);
            evas_object_resize(rectangle, frameSize.width, frameSize.height + 50);
            evas_object_color_set(rectangle, 0xff, 0xff, 0xff, 0);
            evas_object_move(rectangle, 0, -50);
            evas_object_show(rectangle);

            evas_object_repeat_events_set(rectangle, EINA_TRUE);
            evas_object_event_callback_add(rectangle, EVAS_CALLBACK_MOUSE_UP, blankAreaClickedCallback, NULL);
            evas_object_event_callback_add(rectangle, EVAS_CALLBACK_MULTI_UP, blankAreaClickedCallback, NULL);

            s_keypadEntry = elm_entry_add(rectangle);
            elm_entry_single_line_set(s_keypadEntry, EINA_TRUE);
            evas_object_resize(s_keypadEntry, frameSize.width, 50);
            evas_object_move(s_keypadEntry, 0, -50);
            elm_entry_input_panel_return_key_type_set(s_keypadEntry, ELM_INPUT_PANEL_RETURN_KEY_TYPE_DONE);
            elm_entry_prediction_allow_set(s_keypadEntry, EINA_FALSE);
            evas_object_event_callback_add(s_keypadEntry, EVAS_CALLBACK_KEY_UP, entryKeyCallback, NULL);
            evas_object_show(s_keypadEntry);

            elm_object_focus_set(s_keypadEntry, EINA_TRUE);
            evas_object_smart_callback_add(s_keypadEntry, "activated", entryActivatedCallback, NULL);
            elm_entry_input_panel_show(s_keypadEntry);

            s_imf = (Ecore_IMF_Context*)elm_entry_imf_context_get(s_keypadEntry);
            ecore_imf_context_event_callback_add(s_imf, ECORE_IMF_CALLBACK_COMMIT, imfEventCommitCallback, s_keypadEntry);
        }
    } 
    else if (s_keypadWin)
    {
        closeKeypad();
    }
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN
