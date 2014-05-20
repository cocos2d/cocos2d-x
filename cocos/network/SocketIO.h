/****************************************************************************
 Copyright (c) 2013 Chris Hannon http://www.channon.us
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "base/CCPlatformMacros.h"
#include "base/CCMap.h"

#include <string>

NS_CC_BEGIN

namespace network {

//forward declarations
class SIOClientImpl;
class SIOClient;

/**
 *  @brief 单例和包装的类，提供了静态创建方法以及所有sockets的注册
 */
class SocketIO
{
public:
    static SocketIO* getInstance();
    static void destroyInstance();

    /**
     *  @brief 处理socket.io事件的delegate类
     */
    class SIODelegate
    {
    public:
        virtual ~SIODelegate() {}
        virtual void onConnect(SIOClient* client) = 0;
        virtual void onMessage(SIOClient* client, const std::string& data) = 0;
        virtual void onClose(SIOClient* client) = 0;
        virtual void onError(SIOClient* client, const std::string& data) = 0;
        virtual void fireEventToScript(SIOClient* client, const std::string& eventName, const std::string& data) { CCLOG("SIODelegate event '%s' fired with data: %s", eventName.c_str(), data.c_str()); };
    };

    /**
     *  @brief  静态客户端创建方法，类似于JS中的socketio.connect(uri)
     *  @param  delegate 想要从socket.io客户端接收事件的delegate
     *  @param  uri      socket.io服务端的URI
     *  @return 如果连接成功，返回一个初始化的SIOClient，否则为NULL
     */
    static SIOClient* connect(const std::string& uri, SocketIO::SIODelegate& delegate);

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
     *  @brief 到socket.io端点的单个连接
     */
class SIOClient
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
    void receivedDisconnect();

    friend class SIOClientImpl;

public:
    SIOClient(const std::string& host, int port, const std::string& path, SIOClientImpl* impl, SocketIO::SIODelegate& delegate);
    virtual ~SIOClient(void);

    /**
     *  @brief 返回客户端的delegate
     */
    SocketIO::SIODelegate* getDelegate() { return _delegate; };

    /**
     *  @brief 从端点断开连接，当完成的时候onClose会从delegate中被调用
     */
    void disconnect();
    /**
     *  @brief 向socket.io服务端发送一个message
     */
    void send(std::string s);
    /**
     *  @brief 处理socket.io事件的delegate类
     */
    void emit(std::string eventname, std::string args);
    /**
     *  @brief 用于注册一个socket.io事件回调
     *         事件参数应该使用CC_CALLBACK2(&Base::function, this)来传递
     */
    void on(const std::string& eventName, SIOEvent e);

    inline void setTag(const char* tag)
    {
        _tag = tag;
    };

    inline const char* getTag()
    {
        return _tag.c_str();
    };

};

}

NS_CC_END

#endif /* defined(__CC_JSB_SOCKETIO_H__) */
