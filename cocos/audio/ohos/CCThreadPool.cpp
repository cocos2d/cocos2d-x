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

#include "CCThreadPool.h"
#include <chrono>
#include <memory>



#define LOGD(...) printf(__VA_ARGS__)


#define TIME_MINUS(now, prev) (std::chrono::duration_cast<std::chrono::milliseconds>((now) - (prev)).count() / 1000.0f)

namespace cocos2d { namespace experimental {

#define DEFAULT_THREAD_POOL_MIN_NUM (4)
#define DEFAULT_THREAD_POOL_MAX_NUM (20)

#define DEFAULT_SHRINK_INTERVAL (5)
#define DEFAULT_SHRINK_STEP     (2)
#define DEFAULT_STRETCH_STEP    (2)

LegacyThreadPool *LegacyThreadPool::_instance = nullptr;

LegacyThreadPool *LegacyThreadPool::getDefaultThreadPool() {
    if (LegacyThreadPool::_instance == nullptr) {
        LegacyThreadPool::_instance = newCachedThreadPool(DEFAULT_THREAD_POOL_MIN_NUM,
                                                          DEFAULT_THREAD_POOL_MAX_NUM,
                                                          DEFAULT_SHRINK_INTERVAL, DEFAULT_SHRINK_STEP,
                                                          DEFAULT_STRETCH_STEP);
    }

    return LegacyThreadPool::_instance;
}

void LegacyThreadPool::destroyDefaultThreadPool() {
    delete LegacyThreadPool::_instance;
    LegacyThreadPool::_instance = nullptr;
}

LegacyThreadPool *LegacyThreadPool::newCachedThreadPool(int minThreadNum, int maxThreadNum, int shrinkInterval,
                                                        int shrinkStep, int stretchStep) {
    auto *pool = new LegacyThreadPool(minThreadNum, maxThreadNum);
    if (pool != nullptr) {
        pool->setFixedSize(false);
        pool->setShrinkInterval(shrinkInterval);
        pool->setShrinkStep(shrinkStep);
        pool->setStretchStep(stretchStep);
    }
    return pool;
}

LegacyThreadPool *LegacyThreadPool::newFixedThreadPool(int threadNum) {
    auto *pool = new LegacyThreadPool(threadNum, threadNum);
    if (pool != nullptr) {
        pool->setFixedSize(true);
    }
    return pool;
}

LegacyThreadPool *LegacyThreadPool::newSingleThreadPool() {
    auto *pool = new LegacyThreadPool(1, 1);
    if (pool != nullptr) {
        pool->setFixedSize(true);
    }
    return pool;
}

LegacyThreadPool::LegacyThreadPool(int minNum, int maxNum)
: _minThreadNum(minNum),
  _maxThreadNum(maxNum) {
    init();
}

// the destructor waits for all the functions in the queue to be finished
LegacyThreadPool::~LegacyThreadPool() {
    stop();
}

// number of idle threads
int LegacyThreadPool::getIdleThreadNum() const {
    auto *thiz = const_cast<LegacyThreadPool *>(this);
    std::lock_guard<std::mutex> lk(thiz->_idleThreadNumMutex);
    return _idleThreadNum;
}

void LegacyThreadPool::init() {
    _lastShrinkTime = std::chrono::high_resolution_clock::now();

    _maxThreadNum = std::max(_minThreadNum, _maxThreadNum);

    _threads.resize(_maxThreadNum);
    _abortFlags.resize(_maxThreadNum);
    _idleFlags.resize(_maxThreadNum);
    _initedFlags.resize(_maxThreadNum);

    for (int i = 0; i < _maxThreadNum; ++i) {
        _idleFlags[i] = std::make_shared<std::atomic<bool>>(false);
        if (i < _minThreadNum) {
            _abortFlags[i] = std::make_shared<std::atomic<bool>>(false);
            setThread(i);
            _initedFlags[i] = std::make_shared<std::atomic<bool>>(true);
            ++_initedThreadNum;
        } else {
            _abortFlags[i] = std::make_shared<std::atomic<bool>>(true);
            _initedFlags[i] = std::make_shared<std::atomic<bool>>(false);
        }
    }
}

bool LegacyThreadPool::tryShrinkPool() {
    LOGD("shrink pool, _idleThreadNum = %d \n", getIdleThreadNum());

    auto before = std::chrono::high_resolution_clock::now();

    std::vector<int> threadIDsToJoin;
    int maxThreadNumToJoin = std::min(_initedThreadNum - _minThreadNum, _shrinkStep);

    for (int i = 0; i < _maxThreadNum; ++i) {
        if ((int)threadIDsToJoin.size() >= maxThreadNumToJoin) {
            break;
        }

        if (*_idleFlags[i]) {
            *_abortFlags[i] = true;
            threadIDsToJoin.push_back(i);
        }
    }

    {
        // stop the detached threads that were waiting
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.notify_all();
    }

    for (const auto &threadID : threadIDsToJoin) { // wait for the computing threads to finish
        if (_threads[threadID]->joinable()) {
            _threads[threadID]->join();
        }

        _threads[threadID].reset();
        *_initedFlags[threadID] = false;
        --_initedThreadNum;
    }

    auto after = std::chrono::high_resolution_clock::now();

    float seconds = TIME_MINUS(after, before);

    LOGD("shrink %d threads, waste: %f seconds\n", (int)threadIDsToJoin.size(), seconds);

    return (_initedThreadNum <= _minThreadNum);
}

void LegacyThreadPool::stretchPool(int count) {
    auto before = std::chrono::high_resolution_clock::now();

    int oldThreadCount = _initedThreadNum;
    int newThreadCount = 0;

    for (int i = 0; i < _maxThreadNum; ++i) {
        if (!*_initedFlags[i]) {
            *_abortFlags[i] = false;
            setThread(i);
            *_initedFlags[i] = true;
            ++_initedThreadNum;

            if (++newThreadCount >= count) {
                break;
            }
        }
    }

    if (newThreadCount > 0) {
        auto after = std::chrono::high_resolution_clock::now();
        float seconds = TIME_MINUS(after, before);

        LOGD("stretch pool from %d to %d, waste %f seconds\n", oldThreadCount, _initedThreadNum,
             seconds);
    }
}

void LegacyThreadPool::pushTask(const std::function<void(int)> &runnable,
                                TaskType type /* = DEFAULT*/) {
    if (!_isFixedSize) {
        _idleThreadNumMutex.lock();
        int idleNum = _idleThreadNum;
        _idleThreadNumMutex.unlock();

        if (idleNum > _minThreadNum) {
            if (_taskQueue.empty()) {
                auto now = std::chrono::high_resolution_clock::now();
                float seconds = TIME_MINUS(now, _lastShrinkTime);
                if (seconds > _shrinkInterval) {
                    tryShrinkPool();
                    _lastShrinkTime = now;
                }
            }
        } else if (idleNum == 0) {
            stretchPool(_stretchStep);
        }
    }

    auto callback = new std::function<void(int)>([runnable](int tid) {
        runnable(tid);
    });

    Task task;
    task.type = type;
    task.callback = callback;
    _taskQueue.push(task);

    {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.notify_one();
    }
}

void LegacyThreadPool::stopAllTasks() {
    Task task;
    while (_taskQueue.pop(task)) {
        delete task.callback; // empty the queue
    }
}

void LegacyThreadPool::stopTasksByType(TaskType type) {
    Task task;

    std::vector<Task> notStopTasks;
    notStopTasks.reserve(_taskQueue.size());

    while (_taskQueue.pop(task)) {
        if (task.type == type) { // Delete the task from queue
            delete task.callback;
        } else { // If task type isn't match, push it into a vector, then insert to task queue again
            notStopTasks.push_back(task);
        }
    }

    if (!notStopTasks.empty()) {
        for (const auto &t : notStopTasks) {
            _taskQueue.push(t);
        }
    }
}

void LegacyThreadPool::joinThread(int tid) {
    if (tid < 0 || tid >= (int)_threads.size()) {
        LOGD("Invalid thread id %d\n", tid);
        return;
    }

    // wait for the computing threads to finish
    if (*_initedFlags[tid] && _threads[tid]->joinable()) {
        _threads[tid]->join();
        *_initedFlags[tid] = false;
        --_initedThreadNum;
    }
}

int LegacyThreadPool::getTaskNum() const {
    return (int)_taskQueue.size();
}

void LegacyThreadPool::setFixedSize(bool isFixedSize) {
    _isFixedSize = isFixedSize;
}

void LegacyThreadPool::setShrinkInterval(int seconds) {
    if (seconds >= 0) {
        _shrinkInterval = static_cast<float>(seconds);
    }
}

void LegacyThreadPool::setShrinkStep(int step) {
    if (step > 0) {
        _shrinkStep = step;
    }
}

void LegacyThreadPool::setStretchStep(int step) {
    if (step > 0) {
        _stretchStep = step;
    }
}

void LegacyThreadPool::stop() {
    if (_isDone || _isStop) {
        return;
    }

    _isDone = true; // give the waiting threads a command to finish

    {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.notify_all(); // stop all waiting threads
    }

    for (int i = 0, n = static_cast<int>(_threads.size()); i < n; ++i) {
        joinThread(i);
    }
    // if there were no threads in the pool but some functors in the queue, the functors are not deleted by the threads
    // therefore delete them here
    stopAllTasks();
    _threads.clear();
    _abortFlags.clear();
}

void LegacyThreadPool::setThread(int tid) {
    std::shared_ptr<std::atomic<bool>> abortPtr(
        _abortFlags[tid]); // a copy of the shared ptr to the flag
    auto f = [this, tid, abortPtr /* a copy of the shared ptr to the abort */]() {
        std::atomic<bool> &abort = *abortPtr;
        Task task;
        bool isPop = _taskQueue.pop(task);
        while (true) {
            while (isPop) { // if there is anything in the queue
                std::unique_ptr<std::function<void(int)>> func(
                    task.callback); // at return, delete the function even if an exception occurred
                (*task.callback)(tid);
                if (abort) {
                    return; // the thread is wanted to stop, return even if the queue is not empty yet
                }

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

            if (!isPop) {
                return; // if the queue is empty and isDone == true or *flag then return
            }
        }
    };
    _threads[tid].reset(
        new std::thread(f)); // compiler may not support std::make_unique()
}

}} // namespace cocos2d { namespace experimental
