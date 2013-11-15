
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#ifdef __cplusplus
extern "C" {
#endif
    #include "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include <map>
#include <string>
#include "Lua_web_socket.h"
#include "cocos2d.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "LuaScriptHandlerMgr.h"

using namespace cocos2d;


static int SendBinaryMessageToLua(int nHandler,const unsigned char* pTable,int nLength)
{
    if (NULL == pTable || nHandler <= 0) {
        return 0;
    }
    
    if (NULL == ScriptEngineManager::getInstance()->getScriptEngine()) {
        return 0;
    }
    
    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
    if (NULL == pStack) {
        return 0;
    }

    lua_State *tolua_s = pStack->getLuaState();
    if (NULL == tolua_s) {
        return 0;
    }
    
    int nRet = 0;
    LuaValueArray array;
    for (int i = 0 ; i < nLength; i++) {
        LuaValue value = LuaValue::intValue(pTable[i]);
        array.push_back(value);
    }
    
    pStack->pushLuaValueArray(array);
    nRet = pStack->executeFunctionByHandler(nHandler, 1);
    pStack->clean();
    return nRet;
}



LuaWebSocket::~LuaWebSocket()
{
    ScriptHandlerMgr::getInstance()->removeObjectAllHandlers((void*)this);
}

void LuaWebSocket::onOpen(WebSocket* ws)
{
    LuaWebSocket* luaWs = dynamic_cast<LuaWebSocket*>(ws);
    if (NULL != luaWs) {
        int nHandler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this,ScriptHandlerMgr::HandlerType::WEBSOCKET_OPEN);
        if (0 != nHandler) {
            CommonScriptData data(nHandler,"");
            ScriptEvent event(kCommonEvent,(void*)&data);
            ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        }
    }
}
    
void LuaWebSocket::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
    LuaWebSocket* luaWs = dynamic_cast<LuaWebSocket*>(ws);
    if (NULL != luaWs) {
        if (data.isBinary) {
            int nHandler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this,ScriptHandlerMgr::HandlerType::WEBSOCKET_MESSAGE);
            if (0 != nHandler) {
                SendBinaryMessageToLua(nHandler, (const unsigned char*)data.bytes, data.len);
            }
        }
        else{
                
            int nHandler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this,ScriptHandlerMgr::HandlerType::WEBSOCKET_MESSAGE);
            if (0 != nHandler) {
                    CommonScriptData commonData(nHandler,data.bytes);
                    ScriptEvent event(kCommonEvent,(void*)&commonData);
                    ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
            }
        }
    }
}
    
void LuaWebSocket::onClose(WebSocket* ws)
{
    LuaWebSocket* luaWs = dynamic_cast<LuaWebSocket*>(ws);
    if (NULL != luaWs) {
        int nHandler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this,ScriptHandlerMgr::HandlerType::WEBSOCKET_CLOSE);
        if (0 != nHandler)
        {
            CommonScriptData data(nHandler,"");
            ScriptEvent event(kCommonEvent,(void*)&data);
            ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        }
    }
}
    
void LuaWebSocket::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{
    LuaWebSocket* luaWs = dynamic_cast<LuaWebSocket*>(ws);
    if (NULL != luaWs) {
        int nHandler = 0;//luaWs->getScriptHandler(LuaWebSocket::kWebSocketScriptHandlerError);
        if (0 != nHandler)
        {
            CommonScriptData data(nHandler,"");
            ScriptEvent event(kCommonEvent,(void*)&data);
            ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        }
    }
}



#ifdef __cplusplus
static int tolua_collect_WebSocket (lua_State* tolua_S)
{
    LuaWebSocket* self = (LuaWebSocket*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif
/* function to release collected object via destructor */
static void tolua_reg_Web_Socket_type(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "WebSocket");
}

/* method: create of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_create00
static int tolua_Cocos2d_WebSocket_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err)  ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
            const char* urlName = ((const char*)  tolua_tostring(tolua_S,2,0));
            LuaWebSocket *wSocket = new LuaWebSocket();
            wSocket->init(*wSocket, urlName);
            tolua_pushusertype(tolua_S,(void*)wSocket,"WebSocket");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByAProtocol of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_createByAProtocol00
static int tolua_Cocos2d_WebSocket_createByAProtocol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err)  ||
        !tolua_isstring(tolua_S,3,0,&tolua_err)  ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const char *urlName  = ((const char*)  tolua_tostring(tolua_S,2,0));
        const char *protocol = ((const char*)  tolua_tostring(tolua_S,3,0));
        std::vector<std::string> protocols;
        protocols.push_back(protocol);
        LuaWebSocket *wSocket = new LuaWebSocket();
        wSocket->init(*wSocket, urlName,&protocols);
        tolua_pushusertype(tolua_S,(void*)wSocket,"WebSocket");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createByAProtocol'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByAProtocol of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_createByProtocolArray00
static int tolua_Cocos2d_WebSocket_createByProtocolArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err)  ||
        !tolua_isusertable(tolua_S,3,"CCArray",0,&tolua_err)  ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const char *urlName  = ((const char*)  tolua_tostring(tolua_S,2,0));
        Array*    protocolArray = ((Array*)  tolua_tousertype(tolua_S,3,0));
        std::vector<std::string> protocols;
        if (NULL != protocolArray) {
            Object* pObj = NULL;
            CCARRAY_FOREACH(protocolArray, pObj)
            {
                String* pStr = static_cast<String*>(pObj);
                if (NULL != pStr) {
                    protocols.push_back(pStr->getCString());
                }
            }
        }
        LuaWebSocket *wSocket = new LuaWebSocket();
        wSocket->init(*wSocket, urlName,&protocols);
        tolua_pushusertype(tolua_S,(void*)wSocket,"WebSocket");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createByProtocolArray'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getReadyState of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_getReadyState00
static int tolua_Cocos2d_WebSocket_getReadyState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaWebSocket *self = (LuaWebSocket*)tolua_tousertype(tolua_S,1,0);
        int tolua_ret = -1;
        if (NULL != self) {
            tolua_ret = (int)self->getReadyState();
        }
        tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getReadyState'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


/* method: close of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_close00
static int tolua_Cocos2d_WebSocket_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaWebSocket* self    = (LuaWebSocket*)  tolua_tousertype(tolua_S,1,0);
        if (NULL != self ) {
            self->close();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getReadyState'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendString of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_sendString00
static int tolua_Cocos2d_WebSocket_sendString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S, 1, "WebSocket", 0, &tolua_err) ||
        !tolua_isstring(tolua_S, 2, 0, &tolua_err)                ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaWebSocket* self    = (LuaWebSocket*)  tolua_tousertype(tolua_S,1,0);
        size_t size = 0;
        const char* data = (const char*) lua_tolstring(tolua_S, 2, &size);
        if ( NULL == data)
            return 0;

        if (strlen(data) != size)
        {
            self->send((const unsigned char*)data, static_cast<unsigned int>(size));
        }
        else
        {
            self->send(data);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'sendString'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


TOLUA_API int tolua_web_socket_open(lua_State* tolua_S){
    tolua_open(tolua_S);
    tolua_reg_Web_Socket_type(tolua_S);
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
      #ifdef __cplusplus
      tolua_cclass(tolua_S,"WebSocket","WebSocket","",tolua_collect_WebSocket);
      #else
      tolua_cclass(tolua_S,"WebSocket","WebSocket","",NULL);
      #endif
      tolua_beginmodule(tolua_S,"WebSocket");
        tolua_function(tolua_S, "create", tolua_Cocos2d_WebSocket_create00);
        tolua_function(tolua_S, "createByAProtocol", tolua_Cocos2d_WebSocket_createByAProtocol00);
        tolua_function(tolua_S, "createByProtocolArray", tolua_Cocos2d_WebSocket_createByProtocolArray00);
        tolua_function(tolua_S, "getReadyState", tolua_Cocos2d_WebSocket_getReadyState00);
        tolua_function(tolua_S, "close", tolua_Cocos2d_WebSocket_close00);
        tolua_function(tolua_S, "sendString", tolua_Cocos2d_WebSocket_sendString00);
      tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
	return 1;
}

#endif//(CC_TARGET_PLATFORM == CC_PLATFORM_IOS ...
