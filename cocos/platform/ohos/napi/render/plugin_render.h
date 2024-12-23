#ifndef _PLUGIN_RENDER_H_
#define _PLUGIN_RENDER_H_

#include <string>
#include <unordered_map>
#include <uv.h>

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <napi/native_api.h>

#include "egl_core.h"
#include "../WorkerMessageQueue.h"

class PluginRender {
public:
    PluginRender();
    static PluginRender* GetInstance();
    static OH_NativeXComponent_Callback* GetNXComponentCallback();

    static void onMessageCallback(const uv_async_t* req);
    static void timerCb(uv_timer_t* handle);

    void SetNativeXComponent(OH_NativeXComponent* component);

    void workerInit(napi_env env, uv_loop_t* loop);

    void sendMsgToWorker(const MessageType& type, OH_NativeXComponent* component, void* window); 
    void sendMsgToWorker(const MessageType& type, OH_NativeXComponent* component, void* window, OH_NativeXComponent_TouchEvent* touchEvent);
    void enqueue(const WorkerMessageData& data);
    bool dequeue(WorkerMessageData* data);
    void triggerMessageSignal();
    void run();
    void changeFPS(uint64_t animationInterval);

public:
    // NAPI interface
    napi_value Export(napi_env env, napi_value exports);

    // Exposed to JS developers by NAPI
    static napi_value NapiChangeShape(napi_env env, napi_callback_info info);
    static napi_value NapiDrawTriangle(napi_env env, napi_callback_info info);
    static napi_value NapiChangeColor(napi_env env, napi_callback_info info);
    static napi_value NapiChangeColorWorker(napi_env env, napi_callback_info info);

    static void MouseWheelCB(std::string eventType, double scrollY);
    // Callback, called by ACE XComponent
    void OnSurfaceCreated(OH_NativeXComponent* component, void* window);

    void OnSurfaceChanged(OH_NativeXComponent* component, void* window);

    void OnSurfaceDestroyed(OH_NativeXComponent* component, void* window);

    void onSurfaceHide();
    
    void onSurfaceShow(void* window);

    void DispatchKeyEvent(OH_NativeXComponent* component, void* window);

    void DispatchMouseEvent(OH_NativeXComponent* component, void* window);

    void DispatchTouchEvent(OH_NativeXComponent* component, void* window, OH_NativeXComponent_TouchEvent* touchEvent);

    void DispatchMouseWheelEvent();

    void OnCreateNative(napi_env env, uv_loop_t* loop);
    void OnShowNative();
    void OnHideNative();
    void OnDestroyNative();

public:
    struct EventMouseWheelData {
        float positonX;
        float positonY;
        double scrollY;
    };
    static PluginRender* instance_;
    static OH_NativeXComponent_Callback callback_;
    static OH_NativeXComponent_MouseEvent_Callback mouseCallback_;
    static std::queue<OH_NativeXComponent_KeyEvent*> keyEventQueue_;
    static std::queue<OH_NativeXComponent_MouseEvent> mouseEventQueue_;
    static std::queue<EventMouseWheelData> mouseWheelEventQueue_;

    OH_NativeXComponent* component_{nullptr};
    uv_timer_t timerHandle_;
    bool timerInited_{false};
    uv_loop_t* workerLoop_{nullptr};
    uv_async_t messageSignal_{};
    WorkerMessageQueue messageQueue_;
    EGLCore* eglCore_{nullptr};

    uint64_t width_;
    uint64_t height_;

    double x_;
    double y_;

    static uint64_t animationInterval_;
    static uint64_t lastTime;
};

#endif // _PLUGIN_RENDER_H_
