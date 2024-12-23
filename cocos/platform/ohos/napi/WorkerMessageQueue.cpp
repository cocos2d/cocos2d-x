#include "WorkerMessageQueue.h"

void WorkerMessageQueue::enqueue(const WorkerMessageData& data) {
    std::lock_guard<std::mutex> lck(_mutex);
    _queue.push(data);
}

bool WorkerMessageQueue::dequeue(WorkerMessageData *data) {
    std::lock_guard<std::mutex> lck(_mutex);
    if (empty()) {
        return false;
    }
    *data = _queue.front();
    _queue.pop();
    return true;
}

bool WorkerMessageQueue::empty() const {
    return _queue.empty();
}
