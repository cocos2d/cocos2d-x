/****************************************************************************
 Copyright (c) 2016-2017 Chukong Technologies Inc.
 Copyright (c) 2017-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include "utils/Utils.h"


namespace cocos2d { namespace experimental {

class  LegacyThreadPool {
public:
    enum class TaskType {
        DEFAULT = 0,
        NETWORK,
        IO,
        AUDIO,
        USER = 1000
    };

    /*
     * Gets the default thread pool which is a cached thread pool with default parameters.
     */
    static LegacyThreadPool *getDefaultThreadPool();

    /*
     * Destroys the default thread pool
     */
    static void destroyDefaultThreadPool();

    /*
     * Creates a cached thread pool
     * @note The return value has to be delete while it doesn't needed
     */
    static LegacyThreadPool *newCachedThreadPool(int minThreadNum, int maxThreadNum, int shrinkInterval,
                                                 int shrinkStep, int stretchStep);

    /*
     * Creates a thread pool with fixed thread count
     * @note The return value has to be delete while it doesn't needed
     */
    static LegacyThreadPool *newFixedThreadPool(int threadNum);

    /*
     * Creates a thread pool with only one thread in the pool, it could be used to execute multiply tasks serially in just one thread.
     * @note The return value has to be delete while it doesn't needed
     */
    static LegacyThreadPool *newSingleThreadPool();

    // the destructor waits for all the functions in the queue to be finished
    ~LegacyThreadPool();

    /* Pushs a task to thread pool
     *  @param runnable The callback of the task executed in sub thread
     *  @param type The task type, it's TASK_TYPE_DEFAULT if this argument isn't assigned
     *  @note This function has to be invoked in cocos thread
     */
    void pushTask(const std::function<void(int /*threadId*/)> &runnable, TaskType type = TaskType::DEFAULT);

    // Stops all tasks, it will remove all tasks in queue
    void stopAllTasks();

    // Stops some tasks by type
    void stopTasksByType(TaskType type);

    // Gets the minimum thread numbers
    inline int getMinThreadNum() const { return _minThreadNum; };

    // Gets the maximum thread numbers
    inline int getMaxThreadNum() const { return _maxThreadNum; };

    // Gets the number of idle threads
    int getIdleThreadNum() const;

    // Gets the number of initialized threads
    inline int getInitedThreadNum() const { return _initedThreadNum; };

    // Gets the task number
    int getTaskNum() const;

    /* 
     * Trys to shrink pool
     * @note This method is only available for cached thread pool
     */
    bool tryShrinkPool();

private:
    LegacyThreadPool(int minNum, int maxNum);

    LegacyThreadPool(const LegacyThreadPool &);

    LegacyThreadPool(LegacyThreadPool &&) noexcept;

    LegacyThreadPool &operator=(const LegacyThreadPool &);

    LegacyThreadPool &operator=(LegacyThreadPool &&) noexcept;

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
        bool push(T const &value) {
            std::unique_lock<std::mutex> lock(this->mutex);
            this->q.push(value);
            return true;
        }

        // deletes the retrieved element, do not use for non integral types
        bool pop(T &v) {
            std::unique_lock<std::mutex> lock(this->mutex);
            if (this->q.empty())
                return false;
            v = this->q.front();
            this->q.pop();
            return true;
        }

        bool empty() const {
            auto thiz = const_cast<ThreadSafeQueue *>(this);
            std::unique_lock<std::mutex> lock(thiz->mutex);
            return this->q.empty();
        }

        size_t size() const {
            auto thiz = const_cast<ThreadSafeQueue *>(this);
            std::unique_lock<std::mutex> lock(thiz->mutex);
            return this->q.size();
        }

    private:
        std::queue<T> q;
        std::mutex mutex;
    };

    struct Task {
        TaskType type;
        std::function<void(int)> *callback;
    };

    static LegacyThreadPool *_instance;

    ThreadSafeQueue<Task> _taskQueue;
    std::atomic<bool> _isDone{false};
    std::atomic<bool> _isStop{false};

    //IDEA: std::atomic<int> isn't supported by ndk-r10e while compiling with `armeabi` arch.
    // So using a mutex here instead.
    int _idleThreadNum{0}; // how many threads are waiting
    std::mutex _idleThreadNumMutex;

    std::mutex _mutex;
    std::condition_variable _cv;

    int _minThreadNum{0};
    int _maxThreadNum{0};
    int _initedThreadNum{0};

    std::chrono::time_point<std::chrono::high_resolution_clock> _lastShrinkTime;
    float _shrinkInterval{5};
    int _shrinkStep{2};
    int _stretchStep{2};
    bool _isFixedSize{false};
};

}} // namespace cocos2d { namespace experimental
