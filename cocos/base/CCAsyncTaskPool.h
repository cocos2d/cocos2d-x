/****************************************************************************
Copyright (c) 2010      cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCSYNC_TASK_POOL_H_
#define __CCSYNC_TASK_POOL_H_

#include "platform/CCPlatformMacros.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

NS_CC_BEGIN
/////////////////////////////////////////////////////////////////////////////

class CC_DLL AsyncTaskPool
{
public:
    typedef std::function<void(void*)> TaskCallBack;
    
    enum class TaskType
    {
        TASK_IO,
        TASK_NETWORK,
        TASK_OTHER,
        TASK_MAX_TYPE,
    };
    /**
     * get instance
     */
    static AsyncTaskPool* getInstance();
    /**
     * destroy instance
     */
    static void destoryInstance();
    
    /**
     * stop tasks
     * @param type task type you want to stop
     */
    void stopTasks(TaskType type);
    
    /**
     * enqueue a asynchronous task
     * @param type task type is io task, network task or others, each type of task has a thread to deal with it.
     * @param callback callback when the task is finished. The callback is called in the main thread instead of task thread
     * @param callbackParam parameter used by the callback
     * @param f task can be lambda function
     * @param args task parameters
     */
    template<class F>
    inline void enqueue(TaskType type, const TaskCallBack& callback, void* callbackParam, F&& f);
    
CC_CONSTRUCTOR_ACCESS:
    AsyncTaskPool();
    ~AsyncTaskPool();
    
protected:
    
    // thread tasks internally used
    class ThreadTasks {
        struct AsyncTaskCallBack
        {
            TaskCallBack          callback;
            void*                 callbackParam;
        };
    public:
        ThreadTasks()
        : _stop(false)
        {
            _thread = std::thread(
                                  [this]
                                  {
                                      for(;;)
                                      {
                                          std::function<void()> task;
                                          AsyncTaskCallBack callback;
                                          {
                                              std::unique_lock<std::mutex> lock(this->_queueMutex);
                                              this->_condition.wait(lock,
                                                                    [this]{ return this->_stop || !this->_tasks.empty(); });
                                              if(this->_stop && this->_tasks.empty())
                                                  return;
                                              task = std::move(this->_tasks.front());
                                              callback = std::move(this->_taskCallBacks.front());
                                              this->_tasks.pop();
                                              this->_taskCallBacks.pop();
                                          }
                                          
                                          task();
                                          Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, callback]{ callback.callback(callback.callbackParam); });
                                      }
                                  }
                                  );
        }
        ~ThreadTasks()
        {
            {
                std::unique_lock<std::mutex> lock(_queueMutex);
                _stop = true;
                
                while(_tasks.size())
                    _tasks.pop();
                while (_taskCallBacks.size())
                    _taskCallBacks.pop();
            }
            _condition.notify_all();
            _thread.join();
        }
        void clear()
        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            while(_tasks.size())
                _tasks.pop();
            while (_taskCallBacks.size())
                _taskCallBacks.pop();
        }
        template<class F>
        void enqueue(const TaskCallBack& callback, void* callbackParam, F&& f)
        {
            auto task = f;//std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            
            {
                std::unique_lock<std::mutex> lock(_queueMutex);
                
                // don't allow enqueueing after stopping the pool
                if(_stop)
                {
                    CC_ASSERT(0 && "already stop");
                    return;
                }
                
                AsyncTaskCallBack taskCallBack;
                taskCallBack.callback = callback;
                taskCallBack.callbackParam = callbackParam;
                _tasks.emplace([task](){ task(); });
                _taskCallBacks.emplace(taskCallBack);
            }
            _condition.notify_one();
        }
    private:
        
        // need to keep track of thread so we can join them
        std::thread _thread;
        // the task queue
        std::queue< std::function<void()> > _tasks;
        std::queue<AsyncTaskCallBack>            _taskCallBacks;
        
        // synchronization
        std::mutex _queueMutex;
        std::condition_variable _condition;
        bool _stop;
    };
    
    //tasks
    ThreadTasks _threadTasks[int(TaskType::TASK_MAX_TYPE)];
    
    static AsyncTaskPool* s_asyncTaskPool;
};

inline void AsyncTaskPool::stopTasks(TaskType type)
{
    auto& threadTask = _threadTasks[(int)type];
    threadTask.clear();
}

template<class F>
inline void AsyncTaskPool::enqueue(AsyncTaskPool::TaskType type, const TaskCallBack& callback, void* callbackParam, F&& f)
{
    auto& threadTask = _threadTasks[(int)type];
    
    threadTask.enqueue(callback, callbackParam, f);
}

NS_CC_END
#endif //__CCSYNC_TASK_POOL_H_
