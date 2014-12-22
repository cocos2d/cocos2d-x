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
                                          AsyncTaskPool::getInstance()->_taskcallbackDispatcher.enqueue(callback);
                                          //task();
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
    private:
        
        // need to keep track of thread so we can join them
        std::thread _thread;
        // the task queue
        std::queue< std::function<void()> > _tasks;
        std::queue<AsyncTaskCallBack>            _taskCallBacks;
//        std::queue< AsyncTask > _tasks;
        
        // synchronization
        std::mutex _queueMutex;
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
            
            std::unique_lock<std::mutex> lock(_queueMutex);
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
        
        void clear()
        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            _callBacks.clear();
        }
        
        void enqueue(const AsyncTaskCallBack& callback)
        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            _callBacks.push_back(callback);
        }
        
    protected:
        
        std::vector<AsyncTaskCallBack> _callBacks;
        std::mutex _queueMutex;
    };
    
    //tasks
    //ThreadTasks _threadTasks[int(TaskType::TASK_MAX_TYPE)];
    ThreadTasks *_threadTasks;
    //deal task call back
    AfterAsyncTaskDispatcher _taskcallbackDispatcher;
    static AsyncTaskPool* s_asyncTaskPool;
    static int s_maxCallBackPerProcess;
};

inline void AsyncTaskPool::stopTasks(TaskType type)
{
    auto& threadTask = _threadTasks[(int)type];
    auto& queue_mutex = threadTask._queueMutex;
    auto& tasks = threadTask._tasks;
    std::unique_lock<std::mutex> lock(queue_mutex);
    auto& taskcallbacks = threadTask._taskCallBacks;
    while(tasks.size())
        tasks.pop();
    while(taskcallbacks.size())
        taskcallbacks.pop();
    _taskcallbackDispatcher.clear();
}

template<class F>
inline void AsyncTaskPool::enqueue(AsyncTaskPool::TaskType type, const TaskCallBack& callback, void* callbackParam, F&& f)
{
    auto& threadTask = _threadTasks[(int)type];
    //return _threadTasks[taskType].enqueue(f, args);
    
    auto task = f;//std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    
    auto& queue_mutex = threadTask._queueMutex;
    auto& stop = threadTask._stop;
    auto& tasks = threadTask._tasks;
    auto& condition = threadTask._condition;
    auto& taskcallbacks = threadTask._taskCallBacks;
    
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        
        // don't allow enqueueing after stopping the pool
        if(stop)
        {
            CC_ASSERT(0 && "already stop");
            return;
        }
        
        AsyncTaskCallBack taskCallBack;
        taskCallBack.callback = callback;
        taskCallBack.callbackParam = callbackParam;
        tasks.emplace([task](){ task(); });
        taskcallbacks.emplace(taskCallBack);
    }
    condition.notify_one();
}

NS_CC_END
#endif //__CCSYNC_TASK_POOL_H_
