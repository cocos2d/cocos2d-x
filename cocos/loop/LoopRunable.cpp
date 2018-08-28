/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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


#include "LoopRunable.h"

#include <cassert>
namespace cocos2d
{
    namespace loop
    {
        LoopRunable::LoopRunable(uv_loop_t *loop, Loop *tsk, milliseconds interval) :
            _uvLoop(loop), _task(tsk), _intervalMS(duration_cast<milliseconds>(interval).count())
        {
            uv_timer_init(loop, &_uvTimer);
            _uvTimer.data = this;
        }

        void LoopRunable::beforeRun()
        {
            if (_task)
                _task->before();
            _startTime = high_resolution_clock::now();
            _updateTimes = 1;
            scheduleTaskUpdate();
        }

        void LoopRunable::run()
        {
            //schedule update for task
            uv_run(_uvLoop, UV_RUN_DEFAULT);
        }

        void LoopRunable::afterRun()
        {
            if (_task)
                _task->after();
            uv_loop_close(_uvLoop);
        }

        static void timer_handle(uv_timer_t *timer)
        {
            LoopRunable *self = (LoopRunable*)timer->data;
            self->onTimer();
            self->scheduleTaskUpdate();
        }

        void LoopRunable::onTimer()
        {
            _updateTimes += 1;
            if (_task)
                _task->update((int)_intervalMS);
        }

        void LoopRunable::scheduleTaskUpdate()
        {
            auto now = high_resolution_clock::now();
            while (expectTime() <= now) {
                onTimer();
            }
            //auto diff = expectTime() - high_resolution_clock::now();
            auto diff = expectTime() - now;
            auto delay = duration_cast<milliseconds>(diff).count();
            assert(delay >= 0);
            uv_timer_start(&_uvTimer, timer_handle, delay, 0);
        }
    }
}
