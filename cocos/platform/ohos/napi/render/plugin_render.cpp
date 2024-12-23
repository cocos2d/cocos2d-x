#include <stdint.h>
#include <unistd.h>

#include "plugin_render.h"
#include "platform/ohos/napi/plugin_manager.h"
#include "../modules/TouchesNapi.h"
#include "../helper/NapiHelper.h"
#include "platform/ohos/CCLogOhos.h"
#include "cocos2d.h"
#include "native_window/external_window.h"
#include "native_buffer/native_buffer.h"

using namespace cocos2d;

#ifdef __cplusplus
extern "C" {
#endif

PluginRender* PluginRender::instance_ = nullptr;
OH_NativeXComponent_Callback PluginRender::callback_;
OH_NativeXComponent_MouseEvent_Callback PluginRender::mouseCallback_;
std::queue<OH_NativeXComponent_KeyEvent*> PluginRender::keyEventQueue_;
std::queue<OH_NativeXComponent_MouseEvent> PluginRender::mouseEventQueue_;
std::queue<PluginRender::EventMouseWheelData> PluginRender::mouseWheelEventQueue_;
uint64_t PluginRender::animationInterval_ = 16;
uint64_t PluginRender::lastTime = 0;
const int keyCodeUnknownInOH = -1;
const int keyActionUnknownInOH = -1;
float mousePositionX = -1;
float mousePositionY = -1;
bool isMouseLeftActive = false;
double scrollDistance = 0;

std::unordered_map<int, cocos2d::EventKeyboard::KeyCode> ohKeyMap = {
    {KEY_ESCAPE, cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE},
    {KEY_GRAVE, cocos2d::EventKeyboard::KeyCode::KEY_GRAVE},
    {KEY_MINUS, cocos2d::EventKeyboard::KeyCode::KEY_MINUS},
    {KEY_EQUALS, cocos2d::EventKeyboard::KeyCode::KEY_EQUAL},
    {KEY_DEL, cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE},
    {KEY_TAB, cocos2d::EventKeyboard::KeyCode::KEY_TAB},
    {KEY_LEFT_BRACKET, cocos2d::EventKeyboard::KeyCode::KEY_LEFT_BRACKET},
    {KEY_RIGHT_BRACKET, cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_BRACKET},
    {KEY_BACKSLASH, cocos2d::EventKeyboard::KeyCode::KEY_BACK_SLASH},
    {KEY_CAPS_LOCK, cocos2d::EventKeyboard::KeyCode::KEY_CAPS_LOCK},
    {KEY_SEMICOLON, cocos2d::EventKeyboard::KeyCode::KEY_SEMICOLON},
    {KEY_APOSTROPHE, cocos2d::EventKeyboard::KeyCode::KEY_QUOTE},
    {KEY_ENTER, cocos2d::EventKeyboard::KeyCode::KEY_ENTER},
    {KEY_SHIFT_LEFT, cocos2d::EventKeyboard::KeyCode::KEY_LEFT_SHIFT},
    {KEY_COMMA, cocos2d::EventKeyboard::KeyCode::KEY_COMMA},
    {KEY_PERIOD, cocos2d::EventKeyboard::KeyCode::KEY_PERIOD},
    {KEY_SLASH, cocos2d::EventKeyboard::KeyCode::KEY_SLASH},
    {KEY_SHIFT_RIGHT, cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_SHIFT},
    {KEY_CTRL_LEFT, cocos2d::EventKeyboard::KeyCode::KEY_LEFT_CTRL},
    {KEY_ALT_LEFT, cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ALT},
    {KEY_SPACE, cocos2d::EventKeyboard::KeyCode::KEY_SPACE},
    {KEY_ALT_RIGHT, cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ALT},
    {KEY_CTRL_RIGHT, cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_CTRL},
    {KEY_DPAD_LEFT, cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT},
    {KEY_DPAD_RIGHT, cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT},
    {KEY_DPAD_DOWN, cocos2d::EventKeyboard::KeyCode::KEY_DPAD_DOWN},
    {KEY_DPAD_UP, cocos2d::EventKeyboard::KeyCode::KEY_DPAD_UP},
    {KEY_SYSRQ, cocos2d::EventKeyboard::KeyCode::KEY_PRINT},
    {KEY_INSERT, cocos2d::EventKeyboard::KeyCode::KEY_INSERT},
    {KEY_FORWARD_DEL, cocos2d::EventKeyboard::KeyCode::KEY_DELETE}
};

cocos2d::EventKeyboard::KeyCode ohKeyCodeToCocosKeyCode(OH_NativeXComponent_KeyCode ohKeyCode)
{
    auto it = ohKeyMap.find(ohKeyCode);
    if (it != ohKeyMap.end()) {
        return static_cast<cocos2d::EventKeyboard::KeyCode>(it->second);
    }
    if (ohKeyCode >= KEY_0 && ohKeyCode <= KEY_9) {
        // 0 - 9
        return cocos2d::EventKeyboard::KeyCode(int(cocos2d::EventKeyboard::KeyCode::KEY_0) + (ohKeyCode - KEY_0));
    }
    if (ohKeyCode >= KEY_F1 && ohKeyCode <= KEY_F12) {
        // F1 - F12
        return cocos2d::EventKeyboard::KeyCode(int(cocos2d::EventKeyboard::KeyCode::KEY_F1) + (ohKeyCode - KEY_F1));
    }
    if (ohKeyCode >= KEY_A && ohKeyCode <= KEY_Z) {
        // A - Z
        return cocos2d::EventKeyboard::KeyCode(int(cocos2d::EventKeyboard::KeyCode::KEY_A) + (ohKeyCode - KEY_A));
    }
    return cocos2d::EventKeyboard::KeyCode(ohKeyCode);
}

void OnSurfaceCreatedCB(OH_NativeXComponent* component, void* window)
{
    OHOS_LOGD("OnSurfaceCreatedCB");
    PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_SURFACE_CREATED, component, window);
}

void OnSurfaceChangedCB(OH_NativeXComponent* component, void* window) {
    OHOS_LOGD("OnSurfaceChangedCB");
    PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_SURFACE_CHANGED, component, window);
}

void onSurfaceHideCB(OH_NativeXComponent* component, void* window) {
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if(ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_SURFACE_HIDE, component, window);
}

void onSurfaceShowCB(OH_NativeXComponent* component, void* window) {
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if(ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_SURFACE_SHOW, component, window);
}

void OnSurfaceDestroyedCB(OH_NativeXComponent* component, void* window) {
    OHOS_LOGD("OnSurfaceDestroyedCB");
    PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_SURFACE_DESTROY, component, window);
}

void DispatchKeyEventCB(OH_NativeXComponent* component, void* window)
{
    OH_NativeXComponent_KeyEvent* keyEvent;
    if (OH_NativeXComponent_GetKeyEvent(component, &keyEvent) >= 0) {
        PluginRender::keyEventQueue_.push(keyEvent);
        PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_KEY_EVENT, component, window);
    } else {
        OHOS_LOGE("OpenHarmonyPlatform::getKeyEventError");
    }
}

void DispatchMouseEventCB(OH_NativeXComponent* component, void* window)
{
    OH_NativeXComponent_MouseEvent mouseEvent;
    int32_t ret = OH_NativeXComponent_GetMouseEvent(component, window, &mouseEvent);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        PluginRender::mouseEventQueue_.push(mouseEvent);
        PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_MOUSE_EVENT, component, window);
    } else {
        OHOS_LOGE("OpenHarmonyPlatform::getMouseEventError");
    }
}

void DispatchHoverEventCB(OH_NativeXComponent* component, bool isHover)
{
    OHOS_LOGD("OpenHarmonyPlatform::DispatchHoverEventCB");
}

void DispatchTouchEventCB(OH_NativeXComponent* component, void* window) {
    OH_NativeXComponent_TouchEvent* touchEvent = new(std::nothrow) OH_NativeXComponent_TouchEvent();
    if (!touchEvent) {
        OHOS_LOGE("DispatchTouchEventCB::touchEvent alloc failed");
        return;
    }
    int32_t ret = OH_NativeXComponent_GetTouchEvent(component, window, touchEvent);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_TOUCH_EVENT, component, window, touchEvent);
    } else {
        delete touchEvent;
    }
}

PluginRender::PluginRender() : component_(nullptr) {
    auto renderCallback = PluginRender::GetNXComponentCallback();
    renderCallback->OnSurfaceCreated = OnSurfaceCreatedCB;
    renderCallback->OnSurfaceChanged = OnSurfaceChangedCB;
    renderCallback->OnSurfaceDestroyed = OnSurfaceDestroyedCB;
    renderCallback->DispatchTouchEvent = DispatchTouchEventCB;
}

PluginRender* PluginRender::GetInstance() {
    if (instance_ == nullptr) {
        instance_ = new PluginRender();
    }
    return instance_;
}

OH_NativeXComponent_Callback* PluginRender::GetNXComponentCallback() {
    return &PluginRender::callback_;
}

// static
void PluginRender::onMessageCallback(const uv_async_t* /* req */) {
    void* window = nullptr;
    WorkerMessageData msgData;
    PluginRender* render = PluginRender::GetInstance();

    while (true) {
        //loop until all msg dispatch
        if (!render->dequeue(reinterpret_cast<WorkerMessageData*>(&msgData))) {
            // Queue has no data
            break;
        }

        if ((msgData.type >= MessageType::WM_XCOMPONENT_SURFACE_CREATED) && (msgData.type <= MessageType::WM_XCOMPONENT_SURFACE_DESTROY)) {
            OH_NativeXComponent* nativexcomponet = reinterpret_cast<OH_NativeXComponent*>(msgData.data);
            CC_ASSERT(nativexcomponet != nullptr);

            if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_CREATED) {
                render->OnSurfaceCreated(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_KEY_EVENT) {
                render->DispatchKeyEvent(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_MOUSE_EVENT) {
                render->DispatchMouseEvent(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_MOUSE_WHEEL_EVENT) {
                render->DispatchMouseWheelEvent();
            } else if (msgData.type == MessageType::WM_XCOMPONENT_TOUCH_EVENT) {
                render->DispatchTouchEvent(nativexcomponet, msgData.window, msgData.touchEvent);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_CHANGED) {
                render->OnSurfaceChanged(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_SHOW) {
                render->onSurfaceShow(msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_HIDE) {
                render->onSurfaceHide();
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_DESTROY) {
                render->OnSurfaceDestroyed(nativexcomponet, msgData.window);
            } else {
                CC_ASSERT(false);
            }
            continue;
        }

        if (msgData.type == MessageType::WM_APP_SHOW) {
            render->OnShowNative();
        } else if (msgData.type == MessageType::WM_APP_HIDE) {
            render->OnHideNative();
        } else if (msgData.type == MessageType::WM_APP_DESTROY) {
            render->OnDestroyNative();
        }
        if(msgData.type == MessageType::WM_VSYNC) {
            // render->runTask();
        }
    }
}

static uint64_t getCurrentMillSecond() {
    struct timeval stCurrentTime;

    gettimeofday(&stCurrentTime,NULL);
    return stCurrentTime.tv_sec * 1000 + stCurrentTime.tv_usec / 1000; //millseconds
}

// static
void PluginRender::timerCb(uv_timer_t* handle)
{
    // OHOS_LOGD("PluginRender::timerCb, animationInterval_ is %{public}lu", animationInterval_);
    if (PluginRender::GetInstance()->eglCore_ != nullptr) {
        cocos2d::CCDirector::sharedDirector()->mainLoop();
        PluginRender::GetInstance()->eglCore_->Update();
    }
    uint64_t curTime = getCurrentMillSecond();
    if (curTime - lastTime < animationInterval_)
    {
        usleep((animationInterval_ - curTime + lastTime) * 1000);
    }
    lastTime = getCurrentMillSecond();
}

void PluginRender::SetNativeXComponent(OH_NativeXComponent* component) {
    component_ = component;
    OH_NativeXComponent_RegisterCallback(component_, &PluginRender::callback_);
    // register keyEvent
    OH_NativeXComponent_RegisterKeyEventCallback(component_, DispatchKeyEventCB);
    // register mouseEvent
    PluginRender::mouseCallback_.DispatchMouseEvent = DispatchMouseEventCB;
    PluginRender::mouseCallback_.DispatchHoverEvent = DispatchHoverEventCB;
    OH_NativeXComponent_RegisterMouseEventCallback(component_, &mouseCallback_);
    OH_NativeXComponent_RegisterSurfaceHideCallback(component_, onSurfaceHideCB);
    OH_NativeXComponent_RegisterSurfaceShowCallback(component_, onSurfaceShowCB);
}

void PluginRender::workerInit(napi_env env, uv_loop_t* loop) {
    OHOS_LOGD("PluginRender::workerInit");
    workerLoop_ = loop;
    if (workerLoop_) {
        uv_async_init(workerLoop_, &messageSignal_, reinterpret_cast<uv_async_cb>(PluginRender::onMessageCallback));
        if (!messageQueue_.empty()) {
            triggerMessageSignal(); // trigger the signal to handle the pending message
        }
    }
}

void PluginRender::DispatchKeyEvent(OH_NativeXComponent* component, void* window)
{
    OH_NativeXComponent_KeyEvent* keyEvent;
    while (!keyEventQueue_.empty()) {
        keyEvent = keyEventQueue_.front();
        keyEventQueue_.pop();
        OH_NativeXComponent_KeyAction action;
        OH_NativeXComponent_GetKeyEventAction(keyEvent, &action);
        OH_NativeXComponent_KeyCode code;
        OH_NativeXComponent_GetKeyEventCode(keyEvent, &code);
        if (code == keyCodeUnknownInOH || action == keyActionUnknownInOH) {
            // unknown code and action don't callback
            return;
        }
        bool isPressed = action == 0;
        EventKeyboard event(ohKeyCodeToCocosKeyCode(code), isPressed);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
}

void PluginRender::DispatchMouseEvent(OH_NativeXComponent* component, void* window)
{
    OH_NativeXComponent_MouseEvent mouseEvent;
    while (!mouseEventQueue_.empty()) {
        mouseEvent = mouseEventQueue_.front();
        mouseEventQueue_.pop();
        EventMouse::MouseEventType mouseAction;
        mousePositionX = mouseEvent.x;
        mousePositionY = mouseEvent.y;
        switch (mouseEvent.action) {
            case 1:
                mouseAction = EventMouse::MouseEventType::MOUSE_DOWN;
                break;
            case 2:
                mouseAction = EventMouse::MouseEventType::MOUSE_UP;
                break;
            case 3:
                mouseAction = EventMouse::MouseEventType::MOUSE_MOVE;
                break;
            default:
                mouseAction = EventMouse::MouseEventType::MOUSE_NONE;
                break;
        }
        EventMouse::MouseButton mouseButton;
        switch (mouseEvent.button) {
            case 1:
                mouseButton = EventMouse::MouseButton::BUTTON_LEFT;
                break;
            case 2:
                mouseButton = EventMouse::MouseButton::BUTTON_RIGHT;
                break;
            case 4:
                mouseButton = EventMouse::MouseButton::BUTTON_MIDDLE;
                break;
            default:
                mouseButton = EventMouse::MouseButton::BUTTON_UNSET;
                break;    
        }
        if (mouseEvent.action == 1 && mouseEvent.button == 1) {
            isMouseLeftActive = true;
        }
        if (mouseEvent.action == 2 && mouseEvent.button == 1) {
            isMouseLeftActive = false;
        }
        EventMouse event(mouseAction);
        event.setCursorPosition(mouseEvent.x, mouseEvent.y);
        event.setMouseButton(mouseButton);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
    
}

void PluginRender::sendMsgToWorker(const MessageType& type, OH_NativeXComponent* component, void* window) {
    WorkerMessageData data{type, static_cast<void*>(component), window};
    enqueue(data);
}

void PluginRender::sendMsgToWorker(const MessageType& type, OH_NativeXComponent* component, void* window, OH_NativeXComponent_TouchEvent* touchEvent) {
    WorkerMessageData data{type, static_cast<void*>(component), window, touchEvent};
    enqueue(data);
}

void PluginRender::enqueue(const WorkerMessageData& msg) {
    messageQueue_.enqueue(msg);
    triggerMessageSignal();
}

bool PluginRender::dequeue(WorkerMessageData* msg) {
    return messageQueue_.dequeue(msg);
}

void PluginRender::triggerMessageSignal() {
    if(workerLoop_ != nullptr) {
        // It is possible that when the message is sent, the worker thread has not yet started.
        uv_async_send(&messageSignal_);
    }
}

void PluginRender::run() {
    OHOS_LOGD("PluginRender::run");
    if (workerLoop_) {
        uv_timer_init(workerLoop_, &timerHandle_);
        timerInited_ = true;
    }
}

void PluginRender::changeFPS(uint64_t animationInterval) {
    OHOS_LOGD("PluginRender::changeFPS, animationInterval from %{public}lu to %{public}lu", animationInterval_, animationInterval);
    animationInterval_ = animationInterval;
}

void Cocos2dxRenderer_nativeInit(int w, int h);
void PluginRender::OnSurfaceCreated(OH_NativeXComponent* component, void* window) {
    OHOS_LOGD("PluginRender::OnSurfaceCreated");
    eglCore_ = new EGLCore();
    int32_t ret = OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        int32_t code = SET_USAGE;
        OHNativeWindow *nativeWindow = static_cast<OHNativeWindow *>(window); 
        int32_t ret = OH_NativeWindow_NativeWindowHandleOpt(nativeWindow, code, NATIVEBUFFER_USAGE_MEM_DMA);
        eglCore_->GLContextInit(window, width_, height_);
        Cocos2dxRenderer_nativeInit(width_, height_);
    }
}

void PluginRender::OnSurfaceChanged(OH_NativeXComponent* component, void* window) {
    OHOS_LOGD("PluginRender::OnSurfaceChanged");
    int32_t ret = OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OHOS_LOGD("PluginRender::OnSurfaceChanged, width is %{public}d, height is %{public}d", width_, height_);
        cocos2d::Application::getInstance()->applicationScreenSizeChanged(width_, height_);
    }
}

void PluginRender::onSurfaceHide() {
    eglCore_->destroySurface();
}
 
void PluginRender::onSurfaceShow(void* window) {
    eglCore_->createSurface(window);
}

void PluginRender::OnSurfaceDestroyed(OH_NativeXComponent* component, void* window) {
}

void PluginRender::DispatchMouseWheelEvent()
{
    EventMouseWheelData mouseWheelData;
    while (!mouseWheelEventQueue_.empty()) {
        mouseWheelData = mouseWheelEventQueue_.front();
        mouseWheelEventQueue_.pop();
        EventMouse mouseWheelEvent(cocos2d::EventMouse::MouseEventType::MOUSE_SCROLL);
       mouseWheelEvent.setScrollData(0, -mouseWheelData.scrollY);
        // mouseWheelEvent.setScrollData(0, -mouseWheelData.scrollY > 0 ? 1 : -1);
        mouseWheelEvent.setCursorPosition(mouseWheelData.positonX, mouseWheelData.positonY);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&mouseWheelEvent);
    }
}

void PluginRender::DispatchTouchEvent(OH_NativeXComponent* component, void* window, OH_NativeXComponent_TouchEvent* touchEvent)
{
    intptr_t ids[touchEvent->numPoints];
    float xs[touchEvent->numPoints];
    float ys[touchEvent->numPoints];
    for (int i = 0; i < touchEvent->numPoints; i++) {
        ids[i] = touchEvent->touchPoints[i].id;
        xs[i] = touchEvent->touchPoints[i].x;
        ys[i] = touchEvent->touchPoints[i].y;
        OHOS_LOGD("Touch Info : x = %{public}f, y = %{public}f", xs[i], ys[i]);
    }
    switch (touchEvent -> type) {
        case OH_NATIVEXCOMPONENT_DOWN:
            JSFunction::getFunction("CocosEditBox.hideAllEditBox").invoke<void>(); // hide all editbox
            Cocos2dxRenderer_nativeTouchesBegin(touchEvent->numPoints, ids, xs, ys);
            OHOS_LOGD("Touch Info : OH_NATIVEXCOMPONENT_DOWN");
            break;
        case OH_NATIVEXCOMPONENT_UP:
            Cocos2dxRenderer_nativeTouchesEnd(touchEvent->id, touchEvent->x, touchEvent->y);
            OHOS_LOGD("Touch Info : OH_NATIVEXCOMPONENT_UP");
            break;
        case OH_NATIVEXCOMPONENT_MOVE:
            Cocos2dxRenderer_nativeTouchesMove(touchEvent->numPoints, ids, xs, ys);
            OHOS_LOGD("Touch Info : OH_NATIVEXCOMPONENT_MOVE");
            break;
        case OH_NATIVEXCOMPONENT_CANCEL:
            Cocos2dxRenderer_nativeTouchesCancel(touchEvent->numPoints, ids, xs, ys);
            OHOS_LOGD("Touch Info : OH_NATIVEXCOMPONENT_CANCEL");
            break;
        case OH_NATIVEXCOMPONENT_UNKNOWN:
            OHOS_LOGD("Touch Info : OH_NATIVEXCOMPONENT_UNKNOWN");
            break;
        default:
            OHOS_LOGD("Touch Info : default");
            break;
    }
    delete touchEvent;
}

void PluginRender::MouseWheelCB(std::string eventType, double scrollY)
{
    if (isMouseLeftActive) {
        return;
    }
    if (eventType == "actionEnd") {
        scrollDistance = 0;
    }
    if (eventType == "actionUpdate") {
        double moveScrollY = scrollY - scrollDistance;
        scrollDistance = scrollY;
        PluginRender::EventMouseWheelData mouseWheelData{mousePositionX, mousePositionY, moveScrollY};
        PluginRender::mouseWheelEventQueue_.push(mouseWheelData);
        PluginRender::GetInstance()->sendMsgToWorker(MessageType::WM_XCOMPONENT_MOUSE_WHEEL_EVENT, nullptr, nullptr);
    }
}

void PluginRender::OnCreateNative(napi_env env, uv_loop_t* loop) {
    OHOS_LOGD("PluginRender::OnCreateNative");
}

void PluginRender::OnShowNative() {
    OHOS_LOGD("PluginRender::OnShowNative");
    cocos2d::Application* app = cocos2d::Application::getInstance();
    if(app) {
        app->applicationWillEnterForeground();
    }
    cocos2d::EventCustom foregroundEvent(EVENT_COME_TO_FOREGROUND);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&foregroundEvent);
    if (timerInited_) {
        uv_timer_start(&timerHandle_, &PluginRender::timerCb, 0, 1);
    }
}

void PluginRender::OnHideNative() {
    OHOS_LOGD("PluginRender::OnHideNative");
    cocos2d::Application* app = cocos2d::Application::getInstance();
    if(app) {
        app->applicationDidEnterBackground();
    }
    cocos2d::EventCustom backgroundEvent(EVENT_COME_TO_BACKGROUND);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&backgroundEvent);
    if (timerInited_) {
        uv_timer_stop(&timerHandle_);
    }
}

void PluginRender::OnDestroyNative() {
    OHOS_LOGD("PluginRender::OnDestoryNative");
    if (timerInited_) {
        uv_timer_stop(&timerHandle_);
    }
}

napi_value PluginRender::Export(napi_env env, napi_value exports) {
    OHOS_LOGD("PluginRender::Export");
    // Register JS API
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("changeShape", PluginRender::NapiChangeShape),
        DECLARE_NAPI_FUNCTION("drawTriangle", PluginRender::NapiDrawTriangle),
        DECLARE_NAPI_FUNCTION("changeColor", PluginRender::NapiChangeColor),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

napi_value PluginRender::NapiChangeShape(napi_env env, napi_callback_info info)
{
    OHOS_LOGD("PluginRender::NapiChangeShape");
    PluginRender* instance = PluginRender::GetInstance();
    if (instance) {
        CCDirector::sharedDirector()->mainLoop();
        instance->eglCore_->Update();
    }
    return nullptr;
}

napi_value PluginRender::NapiDrawTriangle(napi_env env, napi_callback_info info) {
    OHOS_LOGD("NapiDrawTriangle");
    return nullptr;
}

napi_value PluginRender::NapiChangeColor(napi_env env, napi_callback_info info) {
    OHOS_LOGD("NapiChangeColor");
    return nullptr;
}

#ifdef __cplusplus
}
#endif
