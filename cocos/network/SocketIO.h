/****************************************************************************
 Copyright (c) 2015 Chris Hannon http://www.channon.us
 Copyright (c) 2013-2015 Chukong Technologies Inc.

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

*based on the SocketIO library created by LearnBoost at http://socket.io
*using spec version 1 found at https://github.com/LearnBoost/socket.io-spec

Usage is described below, a full working example can be found in TestCpp under ExtionsTest/NetworkTest/SocketIOTest

creating a new connection to a socket.io server running at localhost:3000

    SIOClient *client = SocketIO::connect(*delegate, "ws://localhost:3000");

the connection process will begin and if successful delegate::onOpen will be called
if the connection process results in an error, delegate::onError will be called with the err msg

sending a message to the server

    client->send("Hello!");

emitting an event to be handled by the server, argument json formatting is up to you

    client->emit("eventname", "[{\"arg\":\"value\"}]");

registering an event callback, target should be a member function in a subclass of SIODelegate
CC_CALLBACK_2 is used to wrap the callback with std::bind and store as an SIOEvent

    client->on("eventname", CC_CALLBACK_2(TargetClass::targetfunc, *targetclass_instance));

event target function should match this pattern, *this pointer will be made available

    void TargetClass::targetfunc(SIOClient *, const std::string&)

disconnect from the endpoint by calling disconnect(), onClose will be called on the delegate once complete
in the onClose method the pointer should be set to NULL or used to connect to a new endpoint

    client->disconnect();

 ****************************************************************************/

#ifndef __CC_SOCKETIO_H__
#define __CC_SOCKETIO_H__

#include <string>
#include "platform/CCPlatformMacros.h"
#include "base/CCMap.h"


/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

class SIOClientImpl;
class SIOClient;

/**@~english
 * Singleton and wrapper class to provide static creation method as well as registry of all sockets.
 *
 * @~chinese 
 * 一个简单封装套接字注册的静态创建方法的单例类。
 * 
 * @lua NA
 */
class CC_DLL SocketIO
{
public:
    /**
     * @~english Get instance of SocketIO.
     * @~chinese 获取SocketIO的实例（单例）。
     * 
     * @return @~english the instance of SocketIO.
     * @~chinese SocketIO的实例。
     */
    static SocketIO* getInstance();

    /**
     * @~english Destroy the instance of SocketIO.
     * @~chinese 销毁SocketIO的实例（单例）。
     */
    static void destroyInstance();

    /**
     * @~english The delegate class to process socket.io events.
     * @~chinese 处理套接字事件的代理类。
     * 
     * @lua NA
     */
    class SIODelegate
    {
    public:
        /** @~english Destructor of SIODelegate.  @~chinese 析构函数。*/
        virtual ~SIODelegate() {}

        /**@~english
         * This is kept for backwards compatibility, connect is now fired as a socket.io event "connect"
         * 
         * This function would be called when the related SIOClient object receive messages that mean it have connected to endpoint successfully.
         *
         * @~chinese 
         * 这个函数是为了向前兼容性而保留的，connect在socket.io新版本中会以"connect"事件触发
         * 
         * 这个函数将在相关的SIOClient对象连接成功时被调用。
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese 连接的SIOClient对象。
         */
        virtual void onConnect(SIOClient* client) { CC_UNUSED_PARAM(client); CCLOG("SIODelegate onConnect fired"); };

        /**@~english
         * 
         * This is kept for backwards compatibility, message is now fired as a socket.io event "message"
         *
         * This function would be called when the related SIOClient object receive message or json message.
         *
         * @~chinese 
         * 这个函数是为了向前兼容性而保留的，message在socket.io新版本中会以"message"事件触发
         * 
         * 这个函数将在相关的SIOClient对象接收到消息时被调用。
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese 连接的SIOClient对象。
         * @param data @~english the message,it could be json message
         * @~chinese 接收到的消息,它可以是json格式的。
         */
        virtual void onMessage(SIOClient* client, const std::string& data) { CC_UNUSED_PARAM(client); CCLOG("SIODelegate onMessage fired with data: %s", data.c_str()); };

        /**@~english
         * This is kept for backwards compatibility, close is now fired as a socket.io event "close"
         *
         * This function would be called when the related SIOClient object disconnect or receive disconnect signal.
         *
         * @~chinese 
         * 这个函数是为了向前兼容性而保留的，close在socket.io新版本中会以"close"事件触发
         * 
         * 这个函数将在相关的SIOClient对象断开连接时被调用。
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese 连接的SIOClient对象。
         */
        virtual void onClose(SIOClient* client) = 0;

        /**@~english
         * Pure virtual callback function, this function should be overrided by the subclass.
         *
         * This function would be called when the related SIOClient object receive error signal or didn't connect the endpoint but do some network operation, eg.,send and emit,etc.
         *
         * @~chinese 
         * 纯虚回调函数,这个函数应该被子类覆盖。
         * 
         * 这个函数将在相关的SIOClient对象接收到错误信号或者在断开连接状态下执行一些网络操作时（例如：send，emit等）被调用。
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese 连接的SIOClient对象。
         * @param data @~english the error message
         * @~chinese 错误消息。
         */
        virtual void onError(SIOClient* client, const std::string& data) = 0;

        /**@~english
         * Fire event to script when the related SIOClient object receive the fire event signal.
         *
         * @~chinese 
         *  当相关的SIOClient对象接收到发送事件信号时转发事件到脚本层。
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese 连接的SIOClient对象。
         * @param eventName @~english the event's name.
         * @~chinese 事件的名称。
         * @param data @~english the event's data information.
         * @~chinese 事件的数据信息。
         */
        virtual void fireEventToScript(SIOClient* client, const std::string& eventName, const std::string& data) { CC_UNUSED_PARAM(client); CCLOG("SIODelegate event '%s' fired with data: %s", eventName.c_str(), data.c_str()); };
    };

    /**
     * @~english Static client creation method, similar to socketio.connect(uri) in JS.
     * @~chinese 静态函数，创建套接字客户端。在JS中调用形式为socketio.connect(uri)
     * 
     * @param uri @~english the URI of the socket.io server.
     * @~chinese 套接字的服务端URI。
     * @param delegate @~english the delegate which want to receive events from the socket.io client.
     * @~chinese 接收处理客户端事件的代理。
     *
     * @return SIOClient* @~english an initialized SIOClient if connected successfully, otherwise nullptr.
     * @~chinese 如果连接成功返回一个初始化的SIOClient对象，否则返回nullptr。
     */
    static SIOClient* connect(const std::string& uri, SocketIO::SIODelegate& delegate);

    /**
     * @~english Static client creation method, similar to socketio.connect(uri) in JS.
     * @~chinese 静态函数，创建套接字客户端。在JS中调用形式为socketio.connect(uri)
     * 
     * @param delegate @~english the delegate which want to receive events from the socket.io client.
     * @~chinese 接收处理客户端事件的代理。
     * @param uri @~english the URI of the socket.io server.
     * @~chinese 套接字的服务端URI。
     *
     * @return SIOClient* @~english an initialized SIOClient if connected successfully, otherwise nullptr.
     * @~chinese 如果连接成功返回一个初始化的SIOClient对象，否则返回nullptr。
     */
    CC_DEPRECATED_ATTRIBUTE  static SIOClient* connect(SocketIO::SIODelegate& delegate, const std::string& uri);

private:

    SocketIO();
    virtual ~SocketIO(void);

    static SocketIO *_inst;

    cocos2d::Map<std::string, SIOClientImpl*> _sockets;

    SIOClientImpl* getSocket(const std::string& uri);
    void addSocket(const std::string& uri, SIOClientImpl* socket);
    void removeSocket(const std::string& uri);

    friend class SIOClientImpl;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(SocketIO)
};

//c++11 style callbacks entities will be created using CC_CALLBACK (which uses std::bind)
typedef std::function<void(SIOClient*, const std::string&)> SIOEvent;
//c++11 map to callbacks
typedef std::unordered_map<std::string, SIOEvent> EventRegistry;

/**
 * @~english A single connection to a socket.io endpoint.
 * @~chinese 一个套接字连接。
 * 
 * @lua NA
 */
class CC_DLL SIOClient
    : public cocos2d::Ref
{
private:
    int _port;
    std::string _host, _path, _tag;
    bool _connected;
    SIOClientImpl* _socket;

    SocketIO::SIODelegate* _delegate;

    EventRegistry _eventRegistry;

    void fireEvent(const std::string& eventName, const std::string& data);

    void onOpen();
    void onConnect();
    void socketClosed();

    friend class SIOClientImpl;

public:
    /**
     * @~english Construtor of SIOClient class.
     * @~chinese SIOClient构造函数。
     * 
     * @param host @~english the string that represent the host address.
     * @~chinese 主机地址的字符串表示。
     * @param port @~english the int value represent the port number.
     * @~chinese 端口号。
     * @param path @~english the string that represent endpoint.
     * @~chinese 终端路径。
     * @param impl @~english the SIOClientImpl object.
     * @~chinese SIOClientImpl对象。
     * @param delegate @~english the SIODelegate object.
     * @~chinese SIODelegate对象。
     */
    SIOClient(const std::string& host, int port, const std::string& path, SIOClientImpl* impl, SocketIO::SIODelegate& delegate);

    /**
     * @~english Destructior of SIOClient class.
     * @~chinese 析构函数。
     */
    virtual ~SIOClient();

    /**
     * @~english Get the delegate for the client
     * @~chinese 得到客户端的代理。
     * 
     * @return @~english the delegate object for the client.
     * @~chinese 客户端的委托对象。
     */
    SocketIO::SIODelegate* getDelegate() { return _delegate; };

    /**
     * @~english Disconnect from the endpoint, onClose will be called for the delegate when complete
     * @~chinese 断开和远程终端的连接，断开完成时代理的onClose将被调用。
     */
    void disconnect();

    /**
     * @~english Send a message to the socket.io server.
     * @~chinese 发送一条消息到套接字服务端。
     * 
     * @param s @~english message.
     * @~chinese 消息。
     */
    void send(const std::string& s);
    /**
     * @~english Emit the eventname and the args to the endpoint that _path point to.
     * @~chinese 给_path指向的终端发送给定的事件及参数。
     * 
     * @param eventname @~english the name of event. @~chinese 事件名称。
     * @param args @~english the argument of event. @~chinese 事件参数。
     */
    void emit(const std::string& eventname, const std::string& args);

    /**@~english
     * Used to register a socket.io event callback.
     * Event argument should be passed using CC_CALLBACK2(&Base::function, this).
     *
     * @~chinese 
     * 注册一个套接字事件回调。
     * 回调函数应该通过CC_CALLBACK2使用。
     *
     * @param eventName @~english the name of event. @~chinese 事件的名称。
     * @param e @~english the callback function. @~chinese 回调函数。
     */
    void on(const std::string& eventName, SIOEvent e);
    
    /**
     * @~english Set tag of SIOClient.
     * The tag is used to distinguish the various SIOClient objects.
     * @~chinese 给SIOClient设置标签，用于方便区分各个SIOClient对象。
     * 
     * @param tag @~english string object.
     * @~chinese 标签（字符串）。
     */
    void setTag(const char* tag);
    

    /**
     * @~english Get tag of SIOClient.
     * @~chinese 获取SIOClient的标签。
     * 
     * @return const char *  @~english the pointer point to the _tag.
     * @~chinese 标签的指针。
     */
    inline const char* getTag()
    {
        return _tag.c_str();
    };

};

}

NS_CC_END

// end group
/// @}

#endif /* defined(__CC_JSB_SOCKETIO_H__) */
