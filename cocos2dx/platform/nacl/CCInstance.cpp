/****************************************************************************
Copyright (c) 2013 The Chromium Authors

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

#include "platform/CCCommon.h"
#include "CCInstance.h"
#include "CCApplication.h"
#include "CCEGLView.h"

#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/module.h>
#include <nacl_io/nacl_io.h>

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

USING_NS_CC;

CocosPepperInstance::CocosPepperInstance(PP_Instance instance) : pp::Instance(instance),
    _running(false)
{
    RequestInputEvents(PP_INPUTEVENT_CLASS_MOUSE);
    RequestFilteringInputEvents(PP_INPUTEVENT_CLASS_KEYBOARD);
}

void CocosPepperInstance::DidChangeView(const pp::View& view)
{
    pp::Rect position = view.GetRect();
    if (_size == position.size())
    {
        // Size did not change.
        return;
    }

    if (_running)
    {
        CCLOG("DidChangeView (%dx%d) while cocos thread already running",
               position.size().width(), position.size().height());
        return;
    }

    _size = position.size();
    assert(!EGLView::g_instance);
    EGLView::g_instance = this;
    CCLOG("DidChangeView %dx%d", _size.width(), _size.height());
    pthread_create(&_cocos_thread, NULL, cocos_main, this);
    _running = true;
}


bool CocosPepperInstance::Init(uint32_t argc, const char* argn[], const char* argv[])
{
    log("CocosPepperInstance::Init: %x %p", pp_instance(),
          pp::Module::Get()->get_browser_interface());
    nacl_io_init_ppapi(pp_instance(),
                       pp::Module::Get()->get_browser_interface());

    umount("/");
    int rtn = mount("Resources",  /* source. Use relative URL */
          "/",  /* target */
          "httpfs",  /* filesystemtype */
          0,  /* mountflags */
          "");  /* data */

    if (rtn != 0)
    {
        CCLOG("mount failed: %d %s", errno, strerror(errno));
        return false;
    }

    return true;
}

bool CocosPepperInstance::HandleInputEvent(const pp::InputEvent& event)
{
    if (!Application::isRunning())
      return false;
    EGLView::getInstance()->AddEvent(event);
    return true;
}
