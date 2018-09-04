/****************************************************************************
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


#include "ThreadLoop.h"
#include <mutex>

#define CC_LOOP_USE_THREAD_LOCAL 0

namespace cocos2d
{
    namespace loop
    {
#if CC_LOOP_USE_THREAD_LOCAL
        //thread_local is not supported on iOS
        namespace 
        {
            thread_local uv_loop_t *__uvLoop = nullptr;
            thread_local bool __uvLoopInited = false;
        }
        
        void ThreadLoop::initThreadLoop()
        {
            if(!__uvLoopInited)
            {
                __uvLoop = (uv_loop_t*)malloc(sizeof(uv_loop_t));
                if(__uvLoop)
                {
                    uv_loop_init(__uvLoop);
                    __uvLoopInited = true;
                }
            }
        }

        uv_loop_t * ThreadLoop::getThreadLoop()
        {   
            return __uvLoopInited ? __uvLoop : nullptr;
        }
#else
        namespace
        {
            uv_key_t __uvLoopKey;
            uv_key_t __uvLoopInitedKey;
            uv_once_t __uvLoopInitOnce;
        }

        static void doInit()
        {
            uv_key_create(&__uvLoopKey);
            uv_key_create(&__uvLoopInitedKey);
            uv_key_set(&__uvLoopKey, nullptr);
            uv_key_set(&__uvLoopInitedKey, nullptr);
        }

        void ThreadLoop::initThreadLoop()
        {
            uv_once(&__uvLoopInitOnce, doInit);
            bool *inited = (bool*)uv_key_get(&__uvLoopInitedKey);
            if (inited == nullptr || false == *inited )
            {
                uv_loop_t *loopPtr = (uv_loop_t*)calloc(sizeof(uv_loop_t), 1);
                bool *initedPtr = new bool(true);
                if (loopPtr && initedPtr)
                {
                    uv_loop_init(loopPtr);
                    uv_key_set(&__uvLoopKey, loopPtr);
                    uv_key_set(&__uvLoopInitedKey, initedPtr);
                }
                else 
                {
                    if (loopPtr) free(loopPtr);
                    if (initedPtr) delete initedPtr;
                }
            }
        }

        uv_loop_t * ThreadLoop::getThreadLoop()
        {
            uv_once(&__uvLoopInitOnce, doInit);
            bool *inited = (bool*)uv_key_get(&__uvLoopInitedKey);
            return (inited && *inited) ? (uv_loop_t*)uv_key_get(&__uvLoopKey) : nullptr;
        }

        void ThreadLoop::closeLoop()
        {
            uv_loop_t *loop = getThreadLoop();
            if (loop)
            {
                uv_stop(loop);
                free(loop);
                bool *inited = (bool*)uv_key_get(&__uvLoopInitedKey);
                delete inited;
                uv_key_set(&__uvLoopInitedKey, nullptr);
                uv_key_set(&__uvLoopKey, nullptr);
            }
        }
#endif
    }
}
