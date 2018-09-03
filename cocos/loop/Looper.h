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


#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <iostream>
#include <atomic>
#include <cstdint>
#include <memory>

#include "uv.h"

#include "Collections.h"
#include "LoopRunable.h"
#include "ThreadLoop.h"
#include "Loop.h"
#include "Finalizer.h"
#include "SeqItem.h"

//#include "platform/CCPlatformMacros.h"

#define CC_LOOPER_THREAD_START_WAIT 3000

namespace cocos2d
{

    namespace loop
    {

        class LoopRunable;

        enum class ThreadCategory {
            ANY_THREAD = 0,
            MAIN_THREAD = 1 << 0,
            PHYSICS_THREAD = 1 << 1,
            RENDER_THREAD = 1 << 2,
            NET_THREAD = 1 << 3,
        };

        template<typename LoopEvent>
        static void async_handle(uv_async_t *data);

        template<typename LoopEvent>
        class Looper : public std::enable_shared_from_this<Looper<LoopEvent> > {
        private:
            static ThreadSafeMap<std::string, uv_key_t> _tlsKeyMap;

        public:
            typedef std::function<void(LoopEvent&)> EventCF;
            typedef std::function<void()> DispatchF;
            typedef std::shared_ptr<Looper<LoopEvent> > Ptr;

            static Looper *getCurrentThread();
            static void setLocalData(const std::string &name, void *data);
            static void *getLocalData(const std::string &name);
            static void clearLocalData(const std::string &name);

            Looper(ThreadCategory cate, Loop* task, int64_t updateMs);
            Looper(Loop* task, int64_t updateMs);
            Looper();
            virtual ~Looper();

            void init();

            void runSync(int waitMS = CC_LOOPER_THREAD_START_WAIT);
            void runAsync();

            void asyncStop();
            bool syncStop();
            void join();
            void detach();

            void emit(const std::string &name, LoopEvent &arg);
            void on(const std::string &name, std::function<void(LoopEvent&)> callback);
            void off(const std::string &name);

            void dispatch(const std::function<void()> &fn);
            void wait(const std::function<void()> &fn);
            void wait(const std::function<void()> &fn, int timeoutMS);

            bool isCurrentThread() const;

            uv_loop_t *getUVLoop() { assert(_initialized); return _uvLoop; };

        private:
            void notify();
            void onNotify();
            void onStop();
            void onRun();

            uint64_t genSeq() { return _eventFnSeq.fetch_add(1); }
            void handleEvent(const std::string &name, LoopEvent &ev);
            void handleFn(const std::function<void()> &fn);

            bool _isCurrentThread() const;

            ThreadCategory _category;
            Loop *_loop;
            uv_loop_t *_uvLoop;
            std::shared_ptr<LoopRunable> _task;
            ThreadSafeMapArray<std::string, EventCF> _callbackMap;
            ThreadSafeQueue<SeqItem<LoopEvent>> _pendingEvents;
            ThreadSafeQueue<SeqItem<DispatchF>> _pendingFns;

            std::atomic_uint64_t _eventFnSeq{ 0 };
            bool _forceStoped = false;
            bool _isStopped = false;
            bool _initialized = false;

            std::thread *_threadId = nullptr;
            int64_t _intervalMs;
         
        public:
            uv_async_t _uvAsync;
            std::condition_variable _waitThreadCV;
            std::mutex _waitThreadMtx;
            friend class LoopMgr;
            friend void async_handle<LoopEvent>(uv_async_t * data);
        };



        using namespace std::chrono;

        template<typename LoopEvent>
        static void async_handle(uv_async_t *handle)
        {
            //Looper<LoopEvent> *t = (Looper<LoopEvent> *)((char*)data - offsetof(Looper<LoopEvent>, _uvAsync));
            Looper<LoopEvent> *t = (Looper<LoopEvent> *)handle->data;
            t->onNotify();
        }


        //declare static field
        template<typename LoopEvent>
        ThreadSafeMap<std::string, uv_key_t> Looper<LoopEvent>::_tlsKeyMap;

        template<typename LoopEvent>
        Looper<LoopEvent>::Looper(ThreadCategory cate, Loop *tsk, int64_t updateMs) :
            _category(cate), _loop(tsk), _intervalMs(updateMs)
        {}

        template<typename LoopEvent>
        Looper<LoopEvent>::Looper() :
            _category(ThreadCategory::ANY_THREAD), _loop(nullptr), _intervalMs(1000)
        {}

        template<typename LoopEvent>
        Looper<LoopEvent>::Looper(Loop *tsk, int64_t updateMs) :
            _category(ThreadCategory::ANY_THREAD), _loop(tsk), _intervalMs(updateMs)
        {}

        template<typename LoopEvent>
        Looper<LoopEvent>::~Looper()
        {


            if (!_isStopped)
            {
                std::cerr << "Destroy Looper and force close inner thread" << std::endl;
            }
            //quit thread before destroy Looper
            if (_threadId) {
                asyncStop();
                if (_threadId->joinable()) _threadId->join();
                delete _threadId;
                _threadId = nullptr;
            }
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::init()
        {
            assert(!_initialized);
          
            //create uv_loop_t
            _uvLoop = ThreadLoop::getThreadLoop();

            //init async event handler
            uv_async_init(_uvLoop, &_uvAsync, &async_handle<LoopEvent>);
            _uvAsync.data = this;

            //create loop object
            _task = std::make_shared<LoopRunable>(_uvLoop, _loop, milliseconds(_intervalMs));
            _initialized = true;

            setLocalData("__thread", this);
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::on(const std::string &name, std::function<void(LoopEvent&)> callback)
        {
            _callbackMap.add(name, callback);
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::off(const std::string &name)
        {
            _callbackMap.clear(name);
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::emit(const std::string &name, LoopEvent &event)
        {
            _pendingEvents.pushBack(SeqItem<LoopEvent>(genSeq(), name, event));
            notify();
        }

        template<typename LoopEvent>
        bool Looper<LoopEvent>::isCurrentThread() const
        {
            assert(_initialized);
            return _uvLoop && _uvLoop == ThreadLoop::getThreadLoop();
        }

        template<typename LoopEvent>
        bool Looper<LoopEvent>::_isCurrentThread() const
        {
            return _uvLoop && _uvLoop == ThreadLoop::getThreadLoop();
        }

        template<typename LoopEvent>
        Looper<LoopEvent> * Looper<LoopEvent>::getCurrentThread()
        {
            return getLocalData("__thread");
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::runAsync()
        {
            assert(!_threadId);
            assert(!_initialized); //call Looper<T>#init() before this
            auto self = this->shared_from_this();
            _threadId = new std::thread([self]() {
                ThreadLoop::initThreadLoop();
                self->init();
                self->onRun();
            });
            _threadId->detach();
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::runSync(int timeoutMS)
        {
            assert(!_threadId);
            assert(!_initialized); //call Looper<T>#init() before this
            auto self = this->shared_from_this();
            
            _threadId = new std::thread([self]() {
                ThreadLoop::initThreadLoop();
                self->init();
                self->_waitThreadCV.notify_all();
                self->onRun();
            });
            _threadId->detach();

            std::unique_lock<std::mutex> lock(_waitThreadMtx);
            auto waitStatus = _waitThreadCV.wait_for(lock, std::chrono::milliseconds(timeoutMS));
            if(waitStatus == std::cv_status::timeout)
            {
                std::cerr << "[Looper] start loop timeout!" << std::endl;
            }
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::onRun()
        {
            if (_isStopped) return;
            assert(_initialized);
            auto *tsk = _task.get();
            assert(tsk);
            Finalizer defer([tsk]() {
                tsk->afterRun();
            });

            tsk->beforeRun();

            //handle events before thread start
            if (_isStopped) return;
            onNotify();

            if (_isStopped) return;
            tsk->run();
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::asyncStop()
        {
            _forceStoped = true;
            notify();
        }

        template<typename LoopEvent>
        bool Looper<LoopEvent>::syncStop()
        {

            if (!_initialized) return false;
            if (_isStopped) return true;

            _forceStoped = true;
            wait([this]() {
                this->onNotify();
            });
            //flush pending task list
            return true;
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::onStop()
        {
            _isStopped = true;
            onNotify();
            uv_stop(_uvLoop);
            _pendingEvents.clear();
            _pendingFns.clear();
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::join()
        {
            assert(_initialized);
            assert(_threadId->joinable());
            _threadId->join();
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::detach()
        {
            assert(_initialized);
            _threadId->detach();
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::dispatch(const std::function<void()> &fn)
        {
            _pendingFns.pushBack(SeqItem<DispatchF>(genSeq(), (DispatchF)fn));
            if (!isCurrentThread())
            {
                notify();
            }
            else
            {
                onNotify();
            }
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::wait(const std::function<void()> &fn)
        {
            wait(fn, 0); //wait forever
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::wait(const std::function<void()> &fn, int timeoutMS)
        {
            if (isCurrentThread())
            {
                _pendingFns.pushBack(SeqItem<DispatchF>(genSeq(), fn));
                onNotify();
            }
            else
            {
                std::condition_variable cv;
                std::mutex mtx;
                std::unique_lock<std::mutex> lock(mtx);
                _pendingFns.pushBack(SeqItem<DispatchF>(genSeq(), [&cv, &mtx, &fn]() {
                    std::unique_lock<std::mutex> lock2(mtx);
                    fn();
                    cv.notify_one();
                }));
                notify();
                if (timeoutMS > 0)
                {
                    cv.wait_for(lock, milliseconds(timeoutMS));
                }
                else
                {
                    cv.wait(lock);
                }
            }
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::notify()
        {
            if (_isStopped || !_initialized) return;
            uv_async_send(&_uvAsync);
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::onNotify() {
            assert(isCurrentThread());

            if (_isStopped) return;

            while (_pendingEvents.size() > 0 && _pendingFns.size() > 0)
            {
                std::lock_guard<std::recursive_mutex> guardEvents(_pendingEvents.getMutex());
                std::lock_guard<std::recursive_mutex> guardFns(_pendingFns.getMutex());
                auto ev = _pendingEvents.front();
                auto fn = _pendingFns.front();
                if (ev.id < fn.id) {
                    SeqItem<LoopEvent> item = _pendingEvents.popFront();
                    handleEvent(item.name, item.data);
                }
                else {
                    auto &&fn = _pendingFns.popFront();
                    handleFn(fn.data);
                }
            }

            while (_pendingEvents.size() > 0)
            {
                SeqItem<LoopEvent> item = _pendingEvents.popFront();
                handleEvent(item.name, item.data);
            }
            while (_pendingFns.size() > 0)
            {
                auto fn = _pendingFns.popFront();
                handleFn(fn.data);
            }
            if (_forceStoped && !_isStopped) {
                onStop();
            }
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::setLocalData(const std::string &name, void *data)
        {
            uv_key_t &key = _tlsKeyMap.getOrInit(name, [](uv_key_t &k) {
                uv_key_create(&k);
            });
            uv_key_set(&key, data);
        }
        template<typename LoopEvent>
        void *Looper<LoopEvent>::getLocalData(const std::string &name)
        {
            if (!_tlsKeyMap.exists(name))
            {
                return nullptr;
            }
            return uv_key_get(&_tlsKeyMap[name]);
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::clearLocalData(const std::string &name)
        {
            _tlsKeyMap.erase(name);
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::handleEvent(const std::string &name, LoopEvent &ev)
        {
            _callbackMap.forEach(name, [&ev](EventCF &eventCb) {
                eventCb(ev);
            });
        }

        template<typename LoopEvent>
        void Looper<LoopEvent>::handleFn(const std::function<void()> &fn)
        {
            fn();
        }

    }
}
