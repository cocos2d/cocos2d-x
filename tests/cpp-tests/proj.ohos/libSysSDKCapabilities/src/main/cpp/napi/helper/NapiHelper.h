//
// Created on 2023/5/13.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

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

// 定义锁及信号量
typedef struct ThreadLockInfo
{
    std::mutex mutex;
    std::condition_variable condition;
    bool ready = false;
} ThreadLockInfo;

typedef struct WorkParam
{
    napi_env env;
    napi_ref funcRef;
    // 入参
    std::string inParam;
    /*size_t argc;
    napi_value* jsArgs;*/
    // 出参
    std::string replyParam = std::string();
    int replyInt = -1;
    char replyString[64] = {0};
    // 锁结构
    std::shared_ptr < ThreadLockInfo > lockInfo;
} WorkParam;

static auto successCallback = [](napi_env env, napi_callback_info info) -> napi_value {
    size_t sLen = 0;
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    void *param_in = nullptr;
    napi_get_cb_info(env, info, &argc, args, nullptr, &param_in);
    WorkParam *callbackParam = reinterpret_cast<WorkParam *>(param_in);
 
    // 根据返回值类型(number或string)采用对应napi_get_value方法来读取返回值
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
 
    /* 子线程解锁 */
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
        // 获取Native调用JS函数 transactFromNative
        status = napi_get_reference_value(env, funcRef, &func);
        if (status != napi_ok) {
            LOGI("XXXXXX:[jni_bridge] napi_get_named_property getClassObject != napi_ok %{public}d", status);
        }

        napi_value promise;
        // 获取transactFromNative函数返回的promise
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
        // 获取promise的then函数
        status = napi_get_named_property(env, promise, "then", &thenFunc);
        if (status != napi_ok) {
            LOGI("XXXXXX:napi_get_named_property then failed, ret: %{public}d", status);
        }               

        napi_value successFunc = nullptr;
        // 注意 将第5个参数 传入回调函数用于获取回调中的返回值
        status = napi_create_function(env, "successFunc", NAPI_AUTO_LENGTH, successCallback, param, &successFunc);
        if (status != napi_ok) {
            LOGI("XXXXXX:napi_create_function successFunc failed, ret: %{public}d", status);
        }
        napi_value ret;
        // 调用then函数
        status = napi_call_function(env, promise, thenFunc, 1, &successFunc, &ret);
        if (status != napi_ok) {
            LOGI("XXXXXX:napi_call_function thenFunc failed, ret: %{public}d", status);
        }
    }
    // 回调函数类型
    typedef std::function<void(std::string)> Callback;

    // 子线程函数 RunPromiseType: 用于访问js中返回promise的异步函数 并实现同步
    static void RunPromiseType(napi_env env,napi_ref funcRef, Callback callback,const char *argstr) {   
        WorkParam *workParam = new (std::nothrow) WorkParam;
        workParam->env = env;
        workParam->funcRef = funcRef;
        workParam->inParam = argstr;
        workParam->lockInfo = std::make_shared<ThreadLockInfo>();
        
        uv_loop_s * loop = nullptr;
        // 获取js中env对应线程loop
        napi_get_uv_event_loop(workParam->env, &loop);
        // 创建uv_work
        uv_work_t * work = new (std::nothrow) uv_work_t;
        if (work == nullptr) {
            LOGI("XXXXXX:failed to new uv_work_t");
            delete workParam;
        }
        // 线程传入参数存入work->data
        work->data = reinterpret_cast < void * > (workParam);

        // 在js线程中执行work
        uv_queue_work(
            loop, work, [](uv_work_t * work) {}, [](uv_work_t * work, int _status) {
                    WorkParam * param = reinterpret_cast < WorkParam * > (work->data);
                    callFunctionWithParams(param);
                });
        LOGI("XXXXXX:childThread lock and wait");
        // 子线程中先锁住等待js线程的回调结果
        std::unique_lock<std::mutex> lock(workParam->lockInfo->mutex);
        // 此处可以修改为wait_for防止超时
        workParam->lockInfo->condition.wait(lock,[&workParam] { return workParam->lockInfo->ready; });
        // workParam->lockInfo->condition.wait_for(lock,std::chrono::milliseconds(2000), [&workParam] { return workParam->lockInfo->ready; });
        LOGI("XXXXXX:wait work end, result %{public}s", workParam->replyParam.c_str());
        callback(workParam->replyParam);
        delete workParam;
        delete work;
    }

    void invokeAsync(AsyncInfo key, const char *argstr) {
        Callback callback = [key](std::string value) {
            Js_Cocos2dxHelper::setAsyncInfo(key, value);//回调函数
        };
        // 创建子线程
        std::thread threadTestPromise(RunPromiseType,env,funcRef,callback,argstr);
        // 线程分离
        threadTestPromise.detach();    
    }

    void invokeAsync(AsyncInfo key) {
        Callback callback = [key](std::string value) {
            Js_Cocos2dxHelper::setAsyncInfo(key, value);//回调函数
        };
        // 创建子线程
        std::thread threadTestPromise(RunPromiseType,env,funcRef,callback,"");
        // 线程分离
        threadTestPromise.detach();    
    }

};
#endif //CC_OH_NapiHelper_H
