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
#ifndef __CCTHREAD_POOL_H__
#define __CCTHREAD_POOL_H__

#include "platform/CCPlatformMacros.h"

#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <memory>

NS_CC_BEGIN

/**
 * @addtogroup base
 * @{
 */

class CC_DLL ThreadPool
{
public:
    
    enum TaskType
    {
        TASK_TYPE_DEFAULT = 0,
        TASK_TYPE_NETWORK,
        TASK_TYPE_IO,
        TASK_TYPE_AUDIO,
        TASK_TYPE_USER = 1000
    };
    
    /*
     * Gets the default thread pool which is a cached thread pool with default parameters.
     */
    static ThreadPool* getDefaultThreadPool();
    
    /*
     * Destroys the default thread pool
     */
    static void destroyDefaultThreadPool();
    
    /*
     * Creates a cached thread pool
     * @note The return value has to be delete while it doesn't needed
     */
    static ThreadPool* newCachedThreadPool(int minThreadNum, int maxThreadNum, int shrinkInterval, int shrinkStep, int stretchStep);
    
    /*
     * Creates a thread pool with fixed thread count
     * @note The return value has to be delete while it doesn't needed
     */
    static ThreadPool* newFixedThreadPool(int threadNum);
    
    /*
     * Creates a thread pool with only one thread in the pool, it could be used to exeute multipy tasks serially in just one thread.
     * @note The return value has to be delete while it doesn't needed
     */
    static ThreadPool* newSingleThreadPool();
    
    // the destructor waits for all the functions in the queue to be finished
    ~ThreadPool();
    
    /* Pushs a task to thread pool
     *  @param runnable The callback of the task executed in sub thread
     *  @param type The task type, it's TASK_TYPE_DEFAULT if this argument isn't assigned
     *  @note This function has to be invoked in cocos thread
     */
    void pushTask(const std::function<void(int)>& runnable, int type = TASK_TYPE_DEFAULT);
    
    // Stops all tasks, it will remove all tasks in queue
    void stopAllTasks();
    
    // Stops some tasks by type
    void stopTasksByType(int type);
    
    // Gets the minimum thread numbers
    inline int getMinThreadNum() { return _minThreadNum; };
    
    // Gets the maximum thread numbers
    inline int getMaxThreadNum() { return _maxThreadNum; };
    
    // Gets the number of idle threads
    int getIdleThreadNum();
    
    // Gets the number of initialized threads
    inline int getInitedThreadNum() { return _initedThreadNum; };
    
    // Gets the task number
    size_t getTaskNum();

    /* 
     * Trys to shrink pool
     * @note This method is only avaiable for cached thread pool
     */
    bool tryShrinkPool();
    
private:
    ThreadPool(int minNum, int maxNum);
    ThreadPool(const ThreadPool&);
    ThreadPool(ThreadPool&&);
    ThreadPool& operator=(const ThreadPool&);
    ThreadPool& operator=(ThreadPool&&);
    
    void init();
    void stop();
    void setThread(int tid);
    void joinThread(int tid);

    void setFixedSize(bool isFixedSize);
    void setShrinkInterval(int seconds);
    void setShrinkStep(int step);
    void setStretchStep(int step);
    void stretchPool(int count);
    
    std::vector<std::unique_ptr<std::thread>> _threads;
    std::vector<std::shared_ptr<std::atomic<bool>>> _abortFlags;
    std::vector<std::shared_ptr<std::atomic<bool>>> _idleFlags;
    std::vector<std::shared_ptr<std::atomic<bool>>> _initedFlags;
    
    template <typename T>
    class ThreadSafeQueue {
    public:
        bool push(T const & value)
        {
            std::unique_lock<std::mutex> lock(this->mutex);
            this->q.push(value);
            return true;
        }
        
        // deletes the retrieved element, do not use for non integral types
        bool pop(T & v)
        {
            std::unique_lock<std::mutex> lock(this->mutex);
            if (this->q.empty())
                return false;
            v = this->q.front();
            this->q.pop();
            return true;
        }
        
        bool empty()
        {
            std::unique_lock<std::mutex> lock(this->mutex);
            return this->q.empty();
        }
        
        size_t size()
        {
            std::unique_lock<std::mutex> lock(this->mutex);
            return this->q.size();
        }
    private:
        std::queue<T> q;
        std::mutex mutex;
    };
    
    struct Task
    {
        int type;
        std::function<void(int)>* callback;
    };
    
    ThreadSafeQueue<Task> _taskQueue;
    std::atomic<bool> _isDone;
    std::atomic<bool> _isStop;
    std::atomic<int> _idleThreadNum;  // how many threads are waiting
    
    std::mutex _mutex;
    std::condition_variable _cv;
    
    int _minThreadNum;
    int _maxThreadNum;
    int _initedThreadNum;
    
    struct timeval _lastShrinkTime;
    float _shrinkInterval;
    int _shrinkStep;
    int _stretchStep;
    bool _isFixedSize;
};
    
// end of base group
/// @}

NS_CC_END


#endif /* __CCTHREAD_POOL_H__ */
