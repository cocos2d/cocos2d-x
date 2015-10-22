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
#include "base/CCAutoreleasePool.h"

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

std::vector<Ref*> AsyncTaskPool::popThreadManagedObjects(std::thread::id threadId)
{
    auto threadAutoreleasePoolIter = _managedAsyncObjectArrays.find(threadId);

    if (threadAutoreleasePoolIter != _managedAsyncObjectArrays.end())
    {
        auto objects = threadAutoreleasePoolIter->second;
        threadAutoreleasePoolIter->second.clear();
        return objects;
    }
    else
    {
        return {};
    }
}

void AsyncTaskPool::mergeThreadManagedObjects(const std::vector<Ref*>& objects)
{
    auto pool = PoolManager::getInstance()->getCurrentPool();
    for (auto object : objects)
    {
        pool->addObject(object);
    }
}

AsyncTaskPool::ThreadTasks::ThreadTasks():
    _stop(false)
{
    _thread = std::thread(
        [this]
        {
            for (;;)
            {
                std::function<void()> task;
                AsyncTaskCallBack callback;
                {
                    std::unique_lock<std::mutex> lock(this->_queueMutex);
                    this->_condition.wait(lock,
                        [this] { return this->_stop || !this->_tasks.empty(); });
                    if (this->_stop && this->_tasks.empty())
                        return;
                    task = std::move(this->_tasks.front());
                    callback = std::move(this->_taskCallBacks.front());
                    this->_tasks.pop();
                    this->_taskCallBacks.pop();
                }

                task();
                Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, callback] { callback.callback(callback.callbackParam); });
                auto threadId = std::this_thread::get_id();
                auto objects = AsyncTaskPool::getInstance()->popThreadManagedObjects(threadId);
                Director::getInstance()->getScheduler()->performFunctionInCocosThread([objects] { AsyncTaskPool::getInstance()->mergeThreadManagedObjects(objects); });
            }
        }
    );
}

AsyncTaskPool::ThreadTasks::~ThreadTasks()
{
    {
        std::unique_lock<std::mutex> lock(_queueMutex);
        _stop = true;

        while (_tasks.size())
            _tasks.pop();
        while (_taskCallBacks.size())
            _taskCallBacks.pop();
    }
    _condition.notify_all();
    _thread.join();
}

NS_CC_END
