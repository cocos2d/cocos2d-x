/****************************************************************************
 Copyright (c) 2019 Xiamen Yaji Software Co., Ltd.
 http://www.cocos.com

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
 ****************************************************************************/


#include "network/CCWebSocket-android.h"
#include "network/WebSocket.h"
#include "platform/CCFileUtils.h"
#include "platform/android/jni/JniHelper.h"


#define JCLS_WEBSOCKET "org/cocos2dx/lib/Cocos2dxWebSocket"
#define J_BINARY_CLS_WEBSOCKET "org.cocos2dx.lib.Cocos2dxWebSocket"
#define JARG_STR        "Ljava/lang/String;"
#define JARG_DOWNLOADER "L" JCLS_WEBSOCKET ";"

#include <string>
#include <mutex>
#include <unordered_map>
#include <condition_variable>
#include <chrono>

using namespace std;


namespace {

    struct ConditionVariable {
        std::mutex mutex;
        std::condition_variable cond;
    };

    class ConnectionCV {
    public:
        ConnectionCV() = default;

        virtual ~ConnectionCV() {
            std::lock_guard<std::mutex> guard(_mtx);
            _conditions.clear();
        }

        void watchConnection(int64_t id)
        {
            std::lock_guard<std::mutex> guard(_mtx);
            CCASSERT(_conditions.find(id) == _conditions.end(), "id should not be registered before");
            auto p = std::make_shared<ConditionVariable>();
            _conditions.emplace(id, p);
        }

        void unwatchConnection(int64_t id)
        {
            std::lock_guard<std::mutex> guard(_mtx);
            _conditions.erase(id);
        }

        void notifyClosed(int64_t id)
        {
            std::shared_ptr<ConditionVariable> p = nullptr;
            {
                std::lock_guard<std::mutex> guard(_mtx);
                auto itr = _conditions.find(id);
                if(itr == _conditions.end())
                {
                    return;
                }
                p = itr->second;
            }
            std::unique_lock<std::mutex> guard(p->mutex);
            p->cond.notify_all();
        }

        void waitForClosing(int64_t id, std::chrono::duration<float> timeout)
        {
            std::shared_ptr<ConditionVariable> p = nullptr;
            {
                std::lock_guard<std::mutex> guard(_mtx);
                auto itr = _conditions.find(id);
                if (itr == _conditions.end()) {
                    return;
                }
                p = itr->second;
            }
            std::unique_lock<std::mutex> ul(p->mutex);
            p->cond.wait_for(ul, timeout);
        }
    private:
        std::mutex _mtx;
        std::unordered_map<int64_t, std::shared_ptr<ConditionVariable>> _conditions;
    };
}


namespace cocos2d{



    int64_t _callJavaConnect(const std::string &url,const std::vector<std::string> *protocals, const std::string & caFile)
    {
        jlong connectionID = -1;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           J_BINARY_CLS_WEBSOCKET,
                                           "connect",
                                           "(" JARG_STR "[" JARG_STR JARG_STR")J")) {
            jstring jurl = methodInfo.env->NewStringUTF(url.c_str());

            //read text content of `caFile`
            std::string caContent;
            if(!caFile.empty()) {
                caContent = FileUtils::getInstance()->getStringFromFile(caFile);
            }

            jstring jcaFile = methodInfo.env->NewStringUTF(caContent.c_str());

            jclass stringClass = methodInfo.env->FindClass("java/lang/String");

            size_t protocalLength = protocals == nullptr ? 0 : protocals->size();

            jobjectArray jprotocals = methodInfo.env->NewObjectArray((jsize)protocalLength, stringClass, methodInfo.env->NewStringUTF(""));
            for(unsigned int i = 0 ; i < protocalLength ; i++ )
            {
                jstring item = methodInfo.env->NewStringUTF(protocals->at(i).c_str());
                methodInfo.env->SetObjectArrayElement(jprotocals, i, item);
            }

            connectionID = methodInfo.env->CallStaticLongMethod(methodInfo.classID, methodInfo.methodID, jurl, jprotocals, jcaFile);
            methodInfo.env->DeleteLocalRef(jurl);
            methodInfo.env->DeleteLocalRef(jcaFile);
            methodInfo.env->DeleteLocalRef(stringClass);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }

        return connectionID;
    }

    void _callJavaDisconnect(int64_t cid, bool syncClose)
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           J_BINARY_CLS_WEBSOCKET,
                                           "disconnect",
                                           "(JZ)V")) {
            jlong connectionID = cid;
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, connectionID, (jboolean) syncClose);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }

    }


    void _callJavaSendBinary(int64_t cid, const unsigned char *data, size_t len)
    {

        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           J_BINARY_CLS_WEBSOCKET,
                                           "sendBinary",
                                           "(J[B)V")) {
            jlong connectionID = cid;
            jbyteArray jdata = methodInfo.env->NewByteArray((jsize)len);
            methodInfo.env->SetByteArrayRegion(jdata, 0, (jsize)len, (const jbyte *)data);
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, connectionID, jdata);
            methodInfo.env->DeleteLocalRef(jdata);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }

    }

    void _callJavaSendString(int64_t cid, const std::string &data) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           J_BINARY_CLS_WEBSOCKET,
                                           "sendString",
                                           "(J"  JARG_STR ")V")) {
            jlong connectionID = cid;
            jstring jdata = methodInfo.env->NewStringUTF(data.c_str());
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, connectionID, jdata);
            methodInfo.env->DeleteLocalRef(jdata);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }

    static JNINativeMethod sMethodTable[] = {
            { "triggerEvent", "(J" JARG_STR JARG_STR "Z)V", (void*)cocos2d::network::_WebSocketAndroidNativeTriggerEvent}
    };

    static bool _registerNativeMethods(JNIEnv* env)
    {
        jclass clazz = env->FindClass(JCLS_WEBSOCKET);
        if (clazz == nullptr)
        {
            CCLOGERROR("_registerNativeMethods: can't find java class:%s", JARG_DOWNLOADER);
            return false;
        }
        if (JNI_OK != env->RegisterNatives(clazz, sMethodTable, sizeof(sMethodTable) / sizeof(sMethodTable[0])))
        {
            CCLOGERROR("_registerNativeMethods: failed");
            if (env->ExceptionCheck())
            {
                env->ExceptionClear();
            }
            return false;
        }
        return true;
    }

    static bool __registered = false;
    static ConnectionCV __syncPipe;
    static std::recursive_mutex __socketMapMtx;
    static std::unordered_map<int64_t, cocos2d::network::WebSocket *> __socketMap;

    namespace network {

        void _WebSocketAndroidNativeTriggerEvent(JNIEnv *env, jclass *klass, jlong cid,
                                                 jstring eventName, jstring data,
                                                 jboolean isBinary) {
            std::lock_guard<std::recursive_mutex> guard(__socketMapMtx);
            auto itr = __socketMap.find(cid);
            if (itr != __socketMap.end()) {
                const char *ceventName = env->GetStringUTFChars(eventName, nullptr);
                const char *cdata = env->GetStringUTFChars(data, nullptr);
                itr->second->triggerEvent(ceventName, cdata, (bool) isBinary);
                env->ReleaseStringUTFChars(eventName, ceventName);
                env->ReleaseStringUTFChars(data, cdata);
            }
        }

        void _preloadJavaWebSocketClass()
        {
            if(!__registered)
            {
                __registered = _registerNativeMethods(JniHelper::getEnv());
            }
        }

        WebSocket::WebSocket()
        {
        }

        WebSocket::~WebSocket()
        {
            if(_connectionID > 0)
            {
                std::lock_guard<std::recursive_mutex> guard(__socketMapMtx);
                __socketMap.erase(_connectionID);
            }
            __syncPipe.unwatchConnection(_connectionID);
        }

        void WebSocket::closeAllConnections()
        {
            std::lock_guard<std::recursive_mutex> guard(__socketMapMtx);
            for(auto it : __socketMap) {
                it.second->closeAsync();
            }
            __socketMap.clear();
        }

        bool WebSocket::init(const cocos2d::network::WebSocket::Delegate &delegate,
                             const std::string &url, const std::vector<std::string> *protocols,
                             const std::string &caFilePath) {

            _delegate = const_cast<Delegate*>(&delegate);
            _url = url;
            _caFilePath = caFilePath;
            _readyState = State::CONNECTING;

            if(_url.empty()) return false;

            _connectionID = _callJavaConnect(url, protocols, caFilePath);

            if(_connectionID > 0)
            {
                std::lock_guard<std::recursive_mutex> guard(__socketMapMtx);
                __socketMap.emplace(_connectionID, this);
            }

            __syncPipe.watchConnection(_connectionID);

            return true;
        }

        void WebSocket::send(const std::string &message)
        {
            _callJavaSendString(_connectionID, message);
        }

        void WebSocket::send(const unsigned char *binaryMsg, unsigned int len)
        {
            _callJavaSendBinary(_connectionID, binaryMsg, len);
        }

        void WebSocket::close()
        {
            _callJavaDisconnect(_connectionID, /* syncClose */ true);
            __syncPipe.waitForClosing(_connectionID, std::chrono::seconds(5));
            //invoke callback in current thread
            _readyState = State::CLOSED;
            _delegate->onClose(this);
        }

        void WebSocket::closeAsync()
        {
            _callJavaDisconnect(_connectionID, /* syncClose */ false);
        }

        void WebSocket::triggerEvent(const std::string &eventName, const std::string &data,
                                     bool binary)
                                     {
            //all events except "sync-closed" are running in GL-thread

            if(eventName == "open")
            {
                _readyState = State::OPEN;
                _delegate->onOpen(this);
            }
            else if(eventName == "message")
            {
                Data msg;
                msg.bytes = const_cast<char*>(data.c_str());
                msg.len = data.size();
                msg.isBinary = binary;
                _delegate->onMessage(this, msg);
            }
            else if(eventName == "closing")
            {
                _readyState = State::CLOSING;
            }
            else if(eventName == "closed")
            {
                _readyState = State::CLOSED;
                __syncPipe.notifyClosed(_connectionID);
                _delegate->onClose(this);
            }
            else if(eventName == "sync-closed")
            {
                __syncPipe.notifyClosed(_connectionID);
            }
            else if(eventName == "error")
            {
                _readyState = State::CLOSED;
                ErrorCode code = ErrorCode::UNKNOWN;
                if(data == "TIME_OUT") {
                    code = ErrorCode::TIME_OUT;
                } else if (data == "CONNECTION_FAILURE") {
                    code = ErrorCode::CONNECTION_FAILURE;
                } else {
                    CCLOGERROR("WebSocket unkown error %s", data.c_str());
                }
                _delegate->onError(this, code);
                __syncPipe.notifyClosed(_connectionID);
            }
            else
            {
                CCLOGERROR("WebSocket invalidate event name %s", eventName.c_str());
            }

        }

        WebSocket::State WebSocket::getReadyState() {
            return _readyState;
        }
    }
}

