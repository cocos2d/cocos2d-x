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
#include "base/CCRef.h"
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

class AsyncTaskPool
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
     * get max number of call back per process, -1 means unlimited (-1 is the default value)
     */
    static int getMaxTaskCallBackPerProcess();
    
    /**
     * set max number of call back per process, -1 means unlimited
     */
    static void setMaxTaskCallBackPerProcess(int numTaskCallBack);
    
    /**
     * process the call back after task, this should be called in the main thread
     */
    void processTaskCallBack()
    {
        _taskcallbackDispatcher.update();
    }
    
    /**
     * enqueue a asynchronous task
     * @param type task type is io task, network task or others, each type of task has a thread to deal with it.
     * @param callback callback when the task is finished. The callback is called in the main thread instead of task thread
     * @param callbackParam parameter used by the callback
     * @param f task can be lambda function
     * @param args task parameters
     * @return the return value is a type of std::future. You can future->get() to wait until it is finished. Or get the notice in the callback
     */
    template<class F, class... Args>
    auto enqueue(TaskType type, const TaskCallBack& callback, void* callbackParam, F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;
    
CC_CONSTRUCTOR_ACCESS:
    AsyncTaskPool();
    ~AsyncTaskPool();
    
protected:
    struct AsyncTaskCallBack
    {
        TaskCallBack          callback;
        void*                 callbackParam;
    };
    
    // thread tasks internally used
    class ThreadTasks {
        friend class AsyncTaskPool;
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
                                              std::unique_lock<std::mutex> lock(this->_queue_mutex);
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
                                          AsyncTaskPool::getInstance()->_taskcallbackDispatcher.enqueue(callback);
                                          //task();
                                      }
                                  }
                                  );
        }
        ~ThreadTasks()
        {
            {
                std::unique_lock<std::mutex> lock(_queue_mutex);
                _stop = true;
                while(_tasks.size())_tasks.pop();
                while (_taskCallBacks.size()) {
                    _taskCallBacks.pop();
                }
            }
            _condition.notify_all();
            _thread.join();
        }
    private:
        
        // need to keep track of thread so we can join them
        std::thread _thread;
        // the task queue
        std::queue< std::function<void()> > _tasks;
        std::queue<AsyncTaskCallBack>            _taskCallBacks;
//        std::queue< AsyncTask > _tasks;
        
        // synchronization
        std::mutex _queue_mutex;
        std::condition_variable _condition;
        bool _stop;
    };
    
    class AfterAsyncTaskDispatcher
    {
    public:
        void update()
        {
            if (_callBacks.empty())
                return;
            
            std::unique_lock<std::mutex> lock(_queue_mutex);
            int numCallBack = 0;
            
            for (auto& it : _callBacks) {
                numCallBack++;
                if (s_maxCallBackPerProcess != -1 && numCallBack > s_maxCallBackPerProcess)
                    break;
                
                if (it.callback)
                {
                    it.callback(it.callbackParam);
                }
            }
            
            _callBacks.erase(_callBacks.begin(), _callBacks.begin() + numCallBack);
        }
        
        AfterAsyncTaskDispatcher() {}
        ~AfterAsyncTaskDispatcher() {}
        
        void enqueue(const AsyncTaskCallBack& callback)
        {
            std::unique_lock<std::mutex> lock(_queue_mutex);
            _callBacks.push_back(callback);
        }
        
    protected:
        
        std::vector<AsyncTaskCallBack> _callBacks;
        std::mutex _queue_mutex;
    };
    
    //tasks
    //ThreadTasks _threadTasks[int(TaskType::TASK_MAX_TYPE)];
    ThreadTasks *_threadTasks;
    //deal task call back
    AfterAsyncTaskDispatcher _taskcallbackDispatcher;
    static AsyncTaskPool* s_asyncTaskPool;
    static int s_maxCallBackPerProcess;
};

template<class F, class... Args>
auto AsyncTaskPool::enqueue(AsyncTaskPool::TaskType type, const TaskCallBack& callback, void* callbackParam, F&& f, Args&&... args)
-> std::future<typename std::result_of<F(Args...)>::type>
{
    auto& threadTask = _threadTasks[(int)type];
    //return _threadTasks[taskType].enqueue(f, args);
    
    using return_type = typename std::result_of<F(Args...)>::type;
    
    auto task = std::make_shared< std::packaged_task<return_type()> >(
                                                                      std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                                                                      );
    auto& queue_mutex = threadTask._queue_mutex;
    auto& stop = threadTask._stop;
    auto& tasks = threadTask._tasks;
    auto& condition = threadTask._condition;
    auto& taskcallbacks = threadTask._taskCallBacks;
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        
        // don't allow enqueueing after stopping the pool
        if(stop)
        {
            CC_ASSERT(0 && "already stop");
            return res;
        }
        
        AsyncTaskCallBack taskCallBack;
        taskCallBack.callback = callback;
        taskCallBack.callbackParam = callbackParam;
        tasks.emplace([task](){ (*task)(); });
        taskcallbacks.emplace(taskCallBack);
    }
    condition.notify_one();
    
    return res;
}

NS_CC_END
#endif //__CCSYNC_TASK_POOL_H_
