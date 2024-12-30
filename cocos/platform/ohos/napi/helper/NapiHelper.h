#ifndef CC_OH_NapiHelper_H
#define CC_OH_NapiHelper_H

#include <new>
#include <string>
#include <unordered_map>
#include <napi/native_api.h>
#include "../common/native_common.h"
#include <hilog/log.h>
#include "NapiValueConverter.h"
#include <uv.h>
#include <thread>
#include "Js_Cocos2dxHelper.h"

#define APP_LOG_DOMAIN 0x0001
#define APP_LOG_TAG "NapiHelper"
#define LOGI(...) ((void)OH_LOG_Print(LOG_APP, LOG_INFO, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))

const static int BUFFER_SIZE = 1024 * 10;

// Defines locks and semaphores.
typedef struct ThreadLockInfo {
    std::mutex mutex;
    std::condition_variable condition;
    bool ready = false;
} ThreadLockInfo;

typedef struct WorkParam {
    napi_env env;
    napi_ref funcRef;
    std::string inParam;
    std::string replyParam = std::string();
    int replyInt = -1;
    char replyString[64] = {0};
    // lock structure
    std::shared_ptr < ThreadLockInfo > lockInfo;
} WorkParam;

static auto successCallback = [](napi_env env, napi_callback_info info) -> napi_value {
    size_t sLen = 0;
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    void *param_in = nullptr;
    napi_get_cb_info(env, info, &argc, args, nullptr, &param_in);
    WorkParam *callbackParam = reinterpret_cast<WorkParam *>(param_in);
 
    // Use the napi_get_value method to read the return value based on the return value type (number or string).
    napi_valuetype type;
    napi_typeof(env, args[0], &type);
    switch(type) {
        case napi_number:
            if (napi_get_value_int32(env, args[0], &callbackParam->replyInt) != napi_ok) {
                LOGI("[%s] get number value error", __FUNCTION__);
            }
            break;
        case napi_string:
            if (napi_get_value_string_utf8(env, args[0], callbackParam->replyString, sizeof(callbackParam->replyString), &sLen) != napi_ok) {
                LOGI("[%s] get string value error", __FUNCTION__);
            }
            callbackParam->replyParam =callbackParam->replyString;
            LOGI("XXXXXX:retChar %{public}s", callbackParam->replyString);
            callbackParam->replyInt = sLen;
            break;
        default:
            LOGI("[%s] type is unknown", __FUNCTION__);
            break;
    }
 
    /* Child thread unlocking */
    std::unique_lock<std::mutex> lock(callbackParam->lockInfo->mutex);
    callbackParam->lockInfo->ready = true;
    callbackParam->lockInfo->condition.notify_all();
    return nullptr;
};

class JSFunction {
public:
    napi_ref funcRef;
    napi_env env;
    char* name = nullptr;

public: 
    static std::unordered_map<std::string, JSFunction> FUNCTION_MAP;  

    explicit JSFunction(char* name, napi_env env, napi_ref funcRef)
        : name(name), env(env), funcRef(funcRef){}
    
    explicit JSFunction(char* name, napi_env env)
        : name(name), env(env){} 

    explicit JSFunction(char* name)
        : name(name){} 

    static JSFunction getFunction(std::string functionName)
    {
        return FUNCTION_MAP.at(functionName);
    }

    static void addFunction(std::string name, JSFunction* jsFunction) {
        FUNCTION_MAP.emplace(name, *jsFunction);
    }

    template<typename ReturnType, typename... Args>
    typename std::enable_if<!std::is_same<ReturnType, void>::value, ReturnType>::type
    invoke(Args... args) {
        LOGI("=========cocos-[NApiHelper]=========JSFunction::invoke =========");
        napi_value global;
        napi_status status = napi_get_global(env, &global);
        //if (status != napi_ok) return;
        
        napi_value func;
        status = napi_get_reference_value(env, funcRef, &func);
        
        napi_value jsArgs[sizeof...(Args)] = {NapiValueConverter::ToNapiValue(env, args)...};
        napi_value return_val;
        status = napi_call_function(env, global, func, sizeof...(Args), jsArgs, &return_val);
        
        ReturnType value;
        if (!NapiValueConverter::ToCppValue(env, return_val, value)) {
            // Handle error here
        }
        return value;
    }
    
    template<typename ReturnType, typename... Args>
    typename std::enable_if<std::is_same<ReturnType, void>::value, void>::type
    invoke(Args... args) {
        LOGI("=========cocos-[NApiHelper]=========JSFunction::invoke =========");
        napi_value global;
        napi_status status = napi_get_global(env, &global);
        if (status != napi_ok) return;
        
        napi_value func;
        status = napi_get_reference_value(env, funcRef, &func);
        
        napi_value jsArgs[sizeof...(Args)] = {NapiValueConverter::ToNapiValue(env, args)...};
        napi_value return_val;
        status = napi_call_function(env, global, func, sizeof...(Args), jsArgs, &return_val);
    }

    static void callFunctionWithParams(WorkParam *param) {
        napi_ref funcRef = param->funcRef;
        std::string inParam = param->inParam;
        napi_env env = param->env;
        napi_value global;
        napi_status status = napi_get_global(env, &global);
        if (status != napi_ok) {
            LOGI("XXXXXX:[getClassObject] napi_get_global != napi_ok");
        }

        napi_value func;
        // Obtains the native interface and invokes the JS function transactFromNative.
        status = napi_get_reference_value(env, funcRef, &func);
        if (status != napi_ok) {
            LOGI("XXXXXX: napi_get_named_property getClassObject != napi_ok %{public}d", status);
        }

        napi_value promise;
        // Obtains the promise returned by the transactFromNative function.
        if (inParam.empty()){
            status = napi_call_function(env, global, func, 0, nullptr, &promise);
        }else {          
            napi_value argsOne[1] = { nullptr };
            napi_create_string_utf8(env, inParam.c_str(), NAPI_AUTO_LENGTH, &argsOne[0]);        
            //napi_create_int32(env, 22, &argsOne[0]);
            status = napi_call_function(env, global, func, 1, argsOne, &promise);
        }
        if (status != napi_ok) {
            LOGI("XXXXXX:napi_call_function getClassObject != napi_ok %{public}d", status);
        }

        napi_value thenFunc = nullptr;
        // Obtains the then function of the promise.
        status = napi_get_named_property(env, promise, "then", &thenFunc);
        if (status != napi_ok) {
            LOGI("XXXXXX:napi_get_named_property then failed, ret: %{public}d", status);
        }               

        napi_value successFunc = nullptr;
        // Note that the fifth parameter is passed to the callback function to obtain the return value in the callback.
        status = napi_create_function(env, "successFunc", NAPI_AUTO_LENGTH, successCallback, param, &successFunc);
        if (status != napi_ok) {
            LOGI("XXXXXX:napi_create_function successFunc failed, ret: %{public}d", status);
        }
        napi_value ret;
        // Call the then function
        status = napi_call_function(env, promise, thenFunc, 1, &successFunc, &ret);
        if (status != napi_ok) {
            LOGI("XXXXXX:napi_call_function thenFunc failed, ret: %{public}d", status);
        }
    }
    // Callback Function Type
    typedef std::function<void(std::string)> Callback;

    // Subthread function RunPromiseType: used to access the asynchronous function that returns promise in JS and implement synchronization.
    static void RunPromiseType(napi_env env,napi_ref funcRef, Callback callback,const char *argstr) {   
        WorkParam *workParam = new (std::nothrow) WorkParam;
        workParam->env = env;
        workParam->funcRef = funcRef;
        workParam->inParam = argstr;
        workParam->lockInfo = std::make_shared<ThreadLockInfo>();
        
        uv_loop_s * loop = nullptr;
        // Obtains the loop thread corresponding to the env in the JS.
        napi_get_uv_event_loop(workParam->env, &loop);
        // create uv_work
        uv_work_t * work = new (std::nothrow) uv_work_t;
        if (work == nullptr) {
            LOGI("XXXXXX:failed to new uv_work_t");
            delete workParam;
        }
        // Thread input parameters are stored work->data
        work->data = reinterpret_cast < void * > (workParam);

        // Execute work in the JS thread.
        uv_queue_work(
            loop, work, [](uv_work_t * work) {}, [](uv_work_t * work, int _status) {
                    WorkParam * param = reinterpret_cast < WorkParam * > (work->data);
                    callFunctionWithParams(param);
                });
        LOGI("XXXXXX:childThread lock and wait");
        // The sub-thread is locked and waits for the callback result of the JS thread.
        std::unique_lock<std::mutex> lock(workParam->lockInfo->mutex);
        // You can change the value to wait_for to prevent timeout.
        workParam->lockInfo->condition.wait(lock,[&workParam] { return workParam->lockInfo->ready; });
        // workParam->lockInfo->condition.wait_for(lock,std::chrono::milliseconds(2000), [&workParam] { return workParam->lockInfo->ready; });
        LOGI("XXXXXX:wait work end, result %{public}s", workParam->replyParam.c_str());
        callback(workParam->replyParam);
        delete workParam;
        delete work;
    }

    void invokeAsync(AsyncInfo key, const char *argstr) {
        Callback callback = [key](std::string value) {
            Js_Cocos2dxHelper::setAsyncInfo(key, value);//callback
        };
        // Create a child thread
        std::thread threadTestPromise(RunPromiseType,env,funcRef,callback,argstr);
        // Thread separation
        threadTestPromise.detach();    
    }

    void invokeAsync(AsyncInfo key) {
        Callback callback = [key](std::string value) {
            Js_Cocos2dxHelper::setAsyncInfo(key, value);//callback
        };
        // Create a child thread
        std::thread threadTestPromise(RunPromiseType,env,funcRef,callback,"");
        // Thread separation
        threadTestPromise.detach();    
    }

};
#endif //CC_OH_NapiHelper_H
