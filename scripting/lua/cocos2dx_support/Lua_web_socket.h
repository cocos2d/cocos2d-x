#ifndef __LUA_WEB_SOCKET_H__
#define __LUA_WEB_SOCKET_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "network/WebSocket.h"
class LuaWebSocket: public cocos2d::extension::WebSocket,public cocos2d::extension::WebSocket::Delegate
{
public:
    virtual ~LuaWebSocket();
    virtual void onOpen(WebSocket* ws);
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);
    virtual void onClose(WebSocket* ws);
    virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);
    
    enum WebSocketScriptHandlerType
    {
        kWebSocketScriptHandlerOpen,
        kWebSocketScriptHandlerMessage,
        kWebSocketScriptHandlerClose,
        kWebSocketScriptHandlerError,
    };
};

TOLUA_API int tolua_web_socket_open(lua_State* tolua_S);

#endif //(CC_TARGET_PLATFORM == CC_PLATFORM_IOS ...

#endif //__LUA_WEB_SOCKET_H__
