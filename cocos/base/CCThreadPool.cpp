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

#include "CCThreadPool.h"
#include <sys/time.h>


#ifdef __ANDROID__
#include <android/log.h>
#define LOG_TAG "ThreadPool"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...) printf(__VA_ARGS__)
#endif

NS_CC_BEGIN

#define DEFAULT_THREAD_POOL_MIN_NUM (4)
#define DEFAULT_THREAD_POOL_MAX_NUM (20)

#define DEFAULT_SHRINK_INTERVAL (5.0f)
#define DEFAULT_SHRINK_STEP (2)
#define DEFAULT_STRETCH_STEP (2)

static ThreadPool* __defaultThreadPool = nullptr;

ThreadPool* ThreadPool::getDefaultThreadPool()
{
    if (__defaultThreadPool == nullptr)
    {
        __defaultThreadPool = new (std::nothrow) ThreadPool(DEFAULT_THREAD_POOL_MIN_NUM, DEFAULT_THREAD_POOL_MAX_NUM);
    }
    
    return __defaultThreadPool;
}

void ThreadPool::destroyDefaultThreadPool()
{
    delete __defaultThreadPool;
    __defaultThreadPool = nullptr;
}

ThreadPool::ThreadPool(int minNum, int maxNum)
: _idleThreadNum(0)
, _isStop(false)
, _isDone(false)
, _minThreadNum(minNum)
, _maxThreadNum(maxNum)
, _shrinkInterval(DEFAULT_SHRINK_INTERVAL)
, _shrinkStep(DEFAULT_SHRINK_STEP)
, _stretchStep(DEFAULT_STRETCH_STEP)
, _initedThreadNum(0)
{
    init();
}
    
// the destructor waits for all the functions in the queue to be finished
ThreadPool::~ThreadPool()
{
    stop();
}
    
// number of idle threads
int ThreadPool::getIdleThreadNum()
{
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

bool ThreadPool::shrinkPool()
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
    
    LOGD("shrink %d threads, waste: %f seconds\n", (int)threadIDsToJoin.size(), seconds);
    
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
        
        float seconds = (after.tv_sec - before.tv_sec) + (after.tv_usec - before.tv_usec) / 1000000.0f;
        
        LOGD("stretch pool from %d to %d, waste %f seconds\n", oldThreadCount, _initedThreadNum, seconds);
    }
}

// empty the queue
void ThreadPool::clearQueue()
{
    std::function<void(int tid)>* f;
    while (_taskQueue.pop(f))
    {
        delete f; // empty the queue
    }
}

void ThreadPool::pushTask(const std::function<void(int)>& runnable)
{
    if (_idleThreadNum > _minThreadNum)
    {
        if (_taskQueue.empty())
        {
            struct timeval now;
            gettimeofday(&now, nullptr);
            
            float seconds = (now.tv_sec - _lastShrinkTime.tv_sec) + (now.tv_usec - _lastShrinkTime.tv_usec) / 1000000.0f;
            if (seconds > _shrinkInterval)
            {
                shrinkPool();
                _lastShrinkTime = now;
            }
        }
    }
    else if (_idleThreadNum == 0)
    {
        stretchPool(_stretchStep);
    }
    
    auto task = new (std::nothrow) std::function<void(int tid)>([runnable](int tid) {
        runnable(tid);
    });
    _taskQueue.push(task);
    
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.notify_one();
    }
}

size_t ThreadPool::getTaskNum()
{
    return _taskQueue.size();
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
    
    for (int i = 0; i < static_cast<int>(_threads.size()); ++i)
    {  // wait for the computing threads to finish
        if (*_initedFlags[i] && _threads[i]->joinable())
        {
            _threads[i]->join();
            *_initedFlags[i] = false;
            --_initedThreadNum;
        }
    }
    // if there were no threads in the pool but some functors in the queue, the functors are not deleted by the threads
    // therefore delete them here
    clearQueue();
    _threads.clear();
    _abortFlags.clear();
}

void ThreadPool::setThread(int i)
{
    std::shared_ptr<std::atomic<bool>> abort_ptr(_abortFlags[i]); // a copy of the shared ptr to the flag
    auto f = [this, i, abort_ptr/* a copy of the shared ptr to the abort */]() {
        std::atomic<bool> & abort = *abort_ptr;
        std::function<void(int tid)> * cb = nullptr;
        bool isPop = _taskQueue.pop(cb);
        while (true)
        {
            while (isPop)
            {  // if there is anything in the queue
                std::unique_ptr<std::function<void(int tid)>> func(cb); // at return, delete the function even if an exception occurred
                (*cb)(i);
                if (abort)
                    return;  // the thread is wanted to stop, return even if the queue is not empty yet
                else
                    isPop = _taskQueue.pop(cb);
            }
            // the queue is empty here, wait for the next command
            std::unique_lock<std::mutex> lock(_mutex);
            ++_idleThreadNum;
            *_idleFlags[i] = true;
            _cv.wait(lock, [this, &cb, &isPop, &abort](){ isPop = _taskQueue.pop(cb); return isPop || _isDone || abort; });
            *_idleFlags[i] = false;
            --_idleThreadNum;
            if (!isPop)
                return;  // if the queue is empty and isDone == true or *flag then return
        }
    };
    _threads[i].reset(new (std::nothrow) std::thread(f)); // compiler may not support std::make_unique()
}

NS_CC_END
