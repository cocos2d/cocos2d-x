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

#include "base/CCAsyncTaskPool.h"

NS_CC_BEGIN

AsyncTaskPool* AsyncTaskPool::s_asyncTaskPool = nullptr;

AsyncTaskPool* AsyncTaskPool::getInstance()
{
    if (s_asyncTaskPool == nullptr)
    {
        s_asyncTaskPool = new (std::nothrow) AsyncTaskPool();
    }
    return s_asyncTaskPool;
}

void AsyncTaskPool::destoryInstance()
{
    delete s_asyncTaskPool;
    s_asyncTaskPool = nullptr;
}

AsyncTaskPool::AsyncTaskPool()
{
    
}

AsyncTaskPool::~AsyncTaskPool()
{
    
}

template<class F, class... Args>
auto AsyncTaskPool::enqueue(AsyncTaskPool::TaskType type, F&& f, Args&&... args)
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
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        
        // don't allow enqueueing after stopping the pool
        if(stop)
        {
            CC_ASSERT(0 && "already stop");
            return res;
        }
        
        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    
    return res;
}

NS_CC_END
