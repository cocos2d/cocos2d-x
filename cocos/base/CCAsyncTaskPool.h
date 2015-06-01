/****************************************************************************
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

/**
* @addtogroup base
* @{
*/
NS_CC_BEGIN

/**
 * @class AsyncTaskPool
 * @brief @~english This class allows to perform background operations without having to manipulate threads.
 * @~chinese 这个类允许执行后台操作,而无需操作线程。
 * @js NA
 */
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


    /** @brief
     * @~english
     * Returns the shared instance of the async task pool.
     * @~chinese 
     * 返回异步任务池实例。
     * @return @~english instance of the async task pool.
     * @~chinese 异步任务池实例。
     */
    static AsyncTaskPool* getInstance();


    /** @brief 
     * @~english
     * Destroys the async task pool.
     * @~chinese 
     * 销毁异步任务池。
     */
    static void destoryInstance();
    

    /** @brief
     * @~english
     * Stop tasks.
     *
     * @~chinese 
     * 停止任务
     * 
     * @param type @~english Task type you want to stop.
     * @~chinese 待停止的任务类型。
     */
    void stopTasks(TaskType type);
    

    /** @brief
     * @~english
     * Enqueue a asynchronous task.
     *
     * @~chinese 
     * 异步任务排队。
     * 
     * @param type @~english task type is io task, network task or others, each type of task has a thread to deal with it.
     * @~chinese 任务类型是io、网络任务或其他,每种类型的任务有一个线程来处理它。
     * @param callback @~english callback when the task is finished. The callback is called in the main thread instead of task thread.
     * @~chinese 当任务完成后的回调。在主线程调用回调,而不是任务线程。
     * @param callbackParam @~english parameter used by the callback.
     * @~chinese 回调使用的参数。
     * @param f @~english task can be lambda function.
     * @~chinese 任务可以是lambda函数。
     * @lua NA
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
// end group
/// @}
#endif //__CCSYNC_TASK_POOL_H_
