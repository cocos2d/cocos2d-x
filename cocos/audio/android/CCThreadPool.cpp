/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.
 
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
 
 Inspired by https://github.com/vit-vit/CTPL
 
 ****************************************************************************/

#include "audio/android/CCThreadPool.h"
#include <sys/time.h>


#ifdef __ANDROID__
#include <android/log.h>
#define LOG_TAG "ThreadPool"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...) printf(__VA_ARGS__)
#endif

namespace cocos2d { namespace experimental {

#define DEFAULT_THREAD_POOL_MIN_NUM (4)
#define DEFAULT_THREAD_POOL_MAX_NUM (20)

#define DEFAULT_SHRINK_INTERVAL (5.0f)
#define DEFAULT_SHRINK_STEP (2)
#define DEFAULT_STRETCH_STEP (2)

static ThreadPool *__defaultThreadPool = nullptr;

ThreadPool *ThreadPool::getDefaultThreadPool()
{
    if (__defaultThreadPool == nullptr)
    {
        __defaultThreadPool = newCachedThreadPool(DEFAULT_THREAD_POOL_MIN_NUM,
                                                  DEFAULT_THREAD_POOL_MAX_NUM,
                                                  DEFAULT_SHRINK_INTERVAL, DEFAULT_SHRINK_STEP,
                                                  DEFAULT_STRETCH_STEP);
    }

    return __defaultThreadPool;
}

void ThreadPool::destroyDefaultThreadPool()
{
    delete __defaultThreadPool;
    __defaultThreadPool = nullptr;
}

ThreadPool *ThreadPool::newCachedThreadPool(int minThreadNum, int maxThreadNum, int shrinkInterval,
                                            int shrinkStep, int stretchStep)
{
    ThreadPool *pool = new(std::nothrow) ThreadPool(minThreadNum, maxThreadNum);
    if (pool != nullptr)
    {
        pool->setFixedSize(false);
        pool->setShrinkInterval(shrinkInterval);
        pool->setShrinkStep(shrinkStep);
        pool->setStretchStep(stretchStep);
    }
    return pool;
}

ThreadPool *ThreadPool::newFixedThreadPool(int threadNum)
{
    ThreadPool *pool = new(std::nothrow) ThreadPool(threadNum, threadNum);
    if (pool != nullptr)
    {
        pool->setFixedSize(true);
    }
    return pool;
}

ThreadPool *ThreadPool::newSingleThreadPool()
{
    ThreadPool *pool = new(std::nothrow) ThreadPool(1, 1);
    if (pool != nullptr)
    {
        pool->setFixedSize(true);
    }
    return pool;
}

ThreadPool::ThreadPool(int minNum, int maxNum)
        : _isStop(false), _isDone(false), _idleThreadNum(0), _minThreadNum(minNum),
          _maxThreadNum(maxNum), _initedThreadNum(0), _shrinkInterval(DEFAULT_SHRINK_INTERVAL),
          _shrinkStep(DEFAULT_SHRINK_STEP), _stretchStep(DEFAULT_STRETCH_STEP),
          _isFixedSize(false)
{
    init();
}

// the destructor waits for all the functions in the queue to be finished
ThreadPool::~ThreadPool()
{
    stop();
}

// number of idle threads
int ThreadPool::getIdleThreadNum() const
{
    ThreadPool* thiz = const_cast<ThreadPool*>(this);
    std::lock_guard<std::mutex> lk(thiz->_idleThreadNumMutex);
    return _idleThreadNum;
}

void ThreadPool::init()
{
    gettimeofday(&_lastShrinkTime, nullptr);

    _maxThreadNum = std::max(_minThreadNum, _maxThreadNum);

    _threads.resize(_maxThreadNum);
    _abortFlags.resize(_maxThreadNum);
    _idleFlags.resize(_maxThreadNum);
    _initedFlags.resize(_maxThreadNum);

    for (int i = 0; i < _maxThreadNum; ++i)
    {
        _idleFlags[i] = std::make_shared<std::atomic<bool>>(false);
        if (i < _minThreadNum)
        {
            _abortFlags[i] = std::make_shared<std::atomic<bool>>(false);
            setThread(i);
            _initedFlags[i] = std::make_shared<std::atomic<bool>>(true);
            ++_initedThreadNum;
        }
        else
        {
            _abortFlags[i] = std::make_shared<std::atomic<bool>>(true);
            _initedFlags[i] = std::make_shared<std::atomic<bool>>(false);
        }
    }
}

bool ThreadPool::tryShrinkPool()
{
    LOGD("shrink pool, _idleThreadNum = %d \n", getIdleThreadNum());

    struct timeval before;
    gettimeofday(&before, nullptr);

    std::vector<int> threadIDsToJoin;
    int maxThreadNumToJoin = std::min(_initedThreadNum - _minThreadNum, _shrinkStep);

    for (int i = 0; i < _maxThreadNum; ++i)
    {
        if (threadIDsToJoin.size() >= maxThreadNumToJoin)
        {
            break;
        }

        if (*_idleFlags[i])
        {
            *_abortFlags[i] = true;
            threadIDsToJoin.push_back(i);
        }
    }

    {
        // stop the detached threads that were waiting
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.notify_all();
    }

    for (const auto& threadID : threadIDsToJoin)
    {  // wait for the computing threads to finish
        if (_threads[threadID]->joinable())
        {
            _threads[threadID]->join();
        }

        _threads[threadID].reset();
        *_initedFlags[threadID] = false;
        --_initedThreadNum;
    }

    struct timeval after;
    gettimeofday(&after, nullptr);

    float seconds = (after.tv_sec - before.tv_sec) + (after.tv_usec - before.tv_usec) / 1000000.0f;

    LOGD("shrink %d threads, waste: %f seconds\n", (int) threadIDsToJoin.size(), seconds);

    if (_initedThreadNum <= _minThreadNum)
        return true;

    return false;
}

void ThreadPool::stretchPool(int count)
{
    struct timeval before;
    gettimeofday(&before, nullptr);

    int oldThreadCount = _initedThreadNum;
    int newThreadCount = 0;

    for (int i = 0; i < _maxThreadNum; ++i)
    {
        if (!*_initedFlags[i])
        {
            *_abortFlags[i] = false;
            setThread(i);
            *_initedFlags[i] = true;
            ++_initedThreadNum;

            if (++newThreadCount >= count)
            {
                break;
            }
        }
    }

    if (newThreadCount > 0)
    {
        struct timeval after;
        gettimeofday(&after, nullptr);

        float seconds =
                (after.tv_sec - before.tv_sec) + (after.tv_usec - before.tv_usec) / 1000000.0f;

        LOGD("stretch pool from %d to %d, waste %f seconds\n", oldThreadCount, _initedThreadNum,
             seconds);
    }
}

void ThreadPool::pushTask(const std::function<void(int)>& runnable,
                          TaskType type/* = DEFAULT*/)
{
    if (!_isFixedSize)
    {
        _idleThreadNumMutex.lock();
        int idleNum = _idleThreadNum;
        _idleThreadNumMutex.unlock();

        if (idleNum > _minThreadNum)
        {
            if (_taskQueue.empty())
            {
                struct timeval now;
                gettimeofday(&now, nullptr);

                float seconds = (now.tv_sec - _lastShrinkTime.tv_sec) +
                                (now.tv_usec - _lastShrinkTime.tv_usec) / 1000000.0f;
                if (seconds > _shrinkInterval)
                {
                    tryShrinkPool();
                    _lastShrinkTime = now;
                }
            }
        }
        else if (idleNum == 0)
        {
            stretchPool(_stretchStep);
        }
    }

    auto callback = new(std::nothrow) std::function<void(int)>([runnable](int tid) {
        runnable(tid);
    });

    Task task;
    task.type = type;
    task.callback = callback;
    _taskQueue.push(std::move(task));

    {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.notify_one();
    }
}

void ThreadPool::stopAllTasks()
{
    Task task;
    while (_taskQueue.pop(task))
    {
        delete task.callback; // empty the queue
    }
}

void ThreadPool::stopTasksByType(TaskType type)
{
    Task task;

    std::vector<Task> notStopTasks;
    notStopTasks.reserve(_taskQueue.size());

    while (_taskQueue.pop(task))
    {
        if (task.type == type)
        {// Delete the task from queue
            delete task.callback;
        }
        else
        {// If task type isn't match, push it into a vector, then insert to task queue again
            notStopTasks.push_back(task);
        }
    }

    if (!notStopTasks.empty())
    {
        for (const auto& t : notStopTasks)
        {
            _taskQueue.push(t);
        }
    }
}

void ThreadPool::joinThread(int tid)
{
    if (tid < 0 || tid >= _threads.size())
    {
        LOGD("Invalid thread id %d\n", tid);
        return;
    }

    // wait for the computing threads to finish
    if (*_initedFlags[tid] && _threads[tid]->joinable())
    {
        _threads[tid]->join();
        *_initedFlags[tid] = false;
        --_initedThreadNum;
    }
}

int ThreadPool::getTaskNum() const
{
    return (int) _taskQueue.size();
}

void ThreadPool::setFixedSize(bool isFixedSize)
{
    _isFixedSize = isFixedSize;
}

void ThreadPool::setShrinkInterval(int seconds)
{
    if (seconds >= 0)
        _shrinkInterval = seconds;
}

void ThreadPool::setShrinkStep(int step)
{
    if (step > 0)
        _shrinkStep = step;
}

void ThreadPool::setStretchStep(int step)
{
    if (step > 0)
        _stretchStep = step;
}

void ThreadPool::stop()
{
    if (_isDone || _isStop)
        return;
    _isDone = true;  // give the waiting threads a command to finish

    {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.notify_all();  // stop all waiting threads
    }

    for (int i = 0, n = static_cast<int>(_threads.size()); i < n; ++i)
    {
        joinThread(i);
    }
    // if there were no threads in the pool but some functors in the queue, the functors are not deleted by the threads
    // therefore delete them here
    stopAllTasks();
    _threads.clear();
    _abortFlags.clear();
}

void ThreadPool::setThread(int tid)
{
    std::shared_ptr<std::atomic<bool>> abort_ptr(
            _abortFlags[tid]); // a copy of the shared ptr to the flag
    auto f = [this, tid, abort_ptr/* a copy of the shared ptr to the abort */]() {
        std::atomic<bool>& abort = *abort_ptr;
        Task task;
        bool isPop = _taskQueue.pop(task);
        while (true)
        {
            while (isPop)
            {  // if there is anything in the queue
                std::unique_ptr<std::function<void(int)>> func(
                        task.callback); // at return, delete the function even if an exception occurred
                (*task.callback)(tid);
                if (abort)
                    return;  // the thread is wanted to stop, return even if the queue is not empty yet
                else
                    isPop = _taskQueue.pop(task);
            }
            // the queue is empty here, wait for the next command
            std::unique_lock<std::mutex> lock(_mutex);
            _idleThreadNumMutex.lock();
            ++_idleThreadNum;
            _idleThreadNumMutex.unlock();

            *_idleFlags[tid] = true;
            _cv.wait(lock, [this, &task, &isPop, &abort]() {
                isPop = _taskQueue.pop(task);
                return isPop || _isDone || abort;
            });
            *_idleFlags[tid] = false;
            _idleThreadNumMutex.lock();
            --_idleThreadNum;
            _idleThreadNumMutex.unlock();
            
            if (!isPop)
                return;  // if the queue is empty and isDone == true or *flag then return
        }
    };
    _threads[tid].reset(
            new(std::nothrow) std::thread(f)); // compiler may not support std::make_unique()
}

}} // namespace cocos2d { namespace experimental {
