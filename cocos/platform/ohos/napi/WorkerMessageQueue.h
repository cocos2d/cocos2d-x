#pragma once

#include <queue>

#include <thread>
#include <mutex>
#include <ace/xcomponent/native_interface_xcomponent.h>

enum class MessageType {
    WM_XCOMPONENT_SURFACE_CREATED = 0,
    WM_XCOMPONENT_TOUCH_EVENT,
    WM_XCOMPONENT_KEY_EVENT,
    WM_XCOMPONENT_MOUSE_EVENT,
    WM_XCOMPONENT_MOUSE_WHEEL_EVENT,
    WM_XCOMPONENT_SURFACE_CHANGED,
    WM_XCOMPONENT_SURFACE_HIDE,
    WM_XCOMPONENT_SURFACE_SHOW,
    WM_XCOMPONENT_SURFACE_DESTROY,
    WM_APP_SHOW,
    WM_APP_HIDE,
    WM_APP_DESTROY,
    WM_VSYNC,
};

struct WorkerMessageData {
    MessageType type;
    void* data;
    void* window;
    OH_NativeXComponent_TouchEvent* touchEvent;
};

class WorkerMessageQueue final {
public:
    void   enqueue(const WorkerMessageData& data);
    bool   dequeue(WorkerMessageData *data);
    bool   empty() const;
    size_t size() const {
        return _queue.size();
    }

private:
    std::mutex                    _mutex;
    std::queue<WorkerMessageData> _queue;
};
