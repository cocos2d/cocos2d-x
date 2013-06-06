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
#ifndef OLD_NACL_MOUNTS
#include "nacl_io/nacl_io.h"
#endif

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

USING_NS_CC;

CocosPepperInstance::CocosPepperInstance(PP_Instance instance) : pp::Instance(instance),
#ifdef OLD_NACL_MOUNTS
    m_runner(NULL),
#endif
    m_running(false)
{
    RequestInputEvents(PP_INPUTEVENT_CLASS_MOUSE);
    RequestFilteringInputEvents(PP_INPUTEVENT_CLASS_KEYBOARD);
}

void CocosPepperInstance::DidChangeView(const pp::View& view)
{
    pp::Rect position = view.GetRect();
    if (m_size == position.size())
    {
        // Size did not change.
        return;
    }

    if (m_running)
    {
        CCLOG("DidChangeView (%dx%d) while cocos thread already running",
               position.size().width(), position.size().height());
        return;
    }

    m_size = position.size();
    assert(!CCEGLView::g_instance);
    CCEGLView::g_instance = this;
    CCLOG("DidChangeView %dx%d", m_size.width(), m_size.height());
    pthread_create(&m_cocos_thread, NULL, cocos_main, this);
    m_running = true;
}


bool CocosPepperInstance::Init(uint32_t argc, const char* argn[], const char* argv[])
{
    CCLog("CocosPepperInstance::Init");
#ifdef OLD_NACL_MOUNTS
    m_runner = new MainThreadRunner(this);
#else
    CCLOG("%p %p", (void*)pp_instance(), (void*)pp::Module::Get()->get_browser_interface());
    nacl_io_init_ppapi(pp_instance(), pp::Module::Get()->get_browser_interface());
    CCLOG("done nacl_mounts_init_ppapi");


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

#endif
    return true;
}

bool CocosPepperInstance::HandleInputEvent(const pp::InputEvent& event)
{
    if (!CCApplication::isRunning())
      return false;
    CCEGLView::sharedOpenGLView()->AddEvent(event);
    return true;
}
