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

#ifndef __CC_INSTANCE_H__
#define __CC_INSTANCE_H__

#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/input_event.h>
#include <pthread.h>

#ifdef OLD_NACL_MOUNTS
#include "nacl-mounts/base/MainThreadRunner.h"
#endif

extern "C" void* cocos_main(void* arg);

class CocosPepperInstance : public pp::Instance {
public:
    explicit CocosPepperInstance(PP_Instance instance);

    virtual ~CocosPepperInstance()
    {
#ifdef OLD_NACL_MOUNTS
        if (m_runner)
            delete m_runner;
#endif
    }

    virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);

    void DidChangeView(const pp::View& view);

    bool HandleInputEvent(const pp::InputEvent& event);

    pp::Size Size() { return m_size; }

#ifdef OLD_NACL_MOUNTS
    MainThreadRunner* m_runner;
#endif
private:
    pp::Size m_size;
    pthread_t m_cocos_thread;
    bool m_running;
};

#endif /* __CC_INSTANCE_H__ */
