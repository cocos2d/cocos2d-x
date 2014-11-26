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
    enum class TaskType
    {
        TASK_IO,
        TASK_NETWORK,
        TASK_MAX_TYPE,
    };
    static AsyncTaskPool* getInstance();
    
    static void destoryInstance();
    
    template<class F, class... Args>
    auto enqueue(TaskType type, F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;
    
CC_CONSTRUCTOR_ACCESS:
    AsyncTaskPool();
    ~AsyncTaskPool();
    
protected:
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
                                          
                                          {
                                              std::unique_lock<std::mutex> lock(this->_queue_mutex);
                                              this->_condition.wait(lock,
                                                                    [this]{ return this->_stop || !this->_tasks.empty(); });
                                              if(this->_stop && this->_tasks.empty())
                                                  return;
                                              task = std::move(this->_tasks.front());
                                              this->_tasks.pop();
                                          }
                                          
                                          task();
                                      }
                                  }
                                  );
        }
        ~ThreadTasks()
        {
            std::unique_lock<std::mutex> lock(_queue_mutex);
            _stop = true;
            _condition.notify_all();
            _thread.join();
        }
    private:
        // need to keep track of thread so we can join them
        std::thread _thread;
        // the task queue
        std::queue< std::function<void()> > _tasks;
        
        // synchronization
        std::mutex _queue_mutex;
        std::condition_variable _condition;
        bool _stop;
    };
    
    //tasks
    ThreadTasks _threadTasks[int(TaskType::TASK_MAX_TYPE)];
    static AsyncTaskPool* s_asyncTaskPool;
};



NS_CC_END
#endif //__CCSYNC_TASK_POOL_H_
