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
#include "WebSocket.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class LuaWebSocketDelegate : public WebSocket::Delegate
{
public:
    
    virtual void onOpen(WebSocket* ws)
    {
        if (NULL != ws) {
            int nHandler = ws->getScriptHandler(WebSocket::kwebSocketScriptHandlerOpen);
            if (-1 != nHandler) {
                CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(nHandler,"");
            }
        }
    }
    
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data)
    {
        if (data.isBinary) {
            int nHandler = ws->getScriptHandler(WebSocket::kwebSocketScriptHandlerMessage);
            if (-1 != nHandler) {
                CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventByTable(nHandler, (const unsigned char*)data.bytes, data.len, "");
            }
        }
        else{
            
            int nHandler = ws->getScriptHandler(WebSocket::kwebSocketScriptHandlerMessage);
            if (-1 != nHandler) {
                CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(nHandler,data.bytes);
            }
        }
    }
    
    virtual void onClose(WebSocket* ws)
    {
        if (NULL != ws) {
            int nHandler = ws->getScriptHandler(WebSocket::kwebSocketScriptHandlerClose);
            if (-1 != nHandler) {
                CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(nHandler,"");
            }
        }
    }
    
    virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error)
    {
        if (NULL != ws) {
            int nHandler = ws->getScriptHandler(WebSocket::kwebSocketScriptHandlerError);
            if (-1 != nHandler) {
                CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(nHandler,"");
            }
        }
    }
};

#ifdef __cplusplus
static int tolua_collect_WebSocket (lua_State* tolua_S)
{
    WebSocket* self = (WebSocket*) tolua_tousertype(tolua_S,1,0);
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
            WebSocket *wSocket = new WebSocket();
            LuaWebSocketDelegate* delegate = new LuaWebSocketDelegate();
            wSocket->init(*delegate, urlName);
            tolua_pushusertype(tolua_S,(void*)wSocket,"WebSocket");
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
        WebSocket *wSocket = new WebSocket();
        LuaWebSocketDelegate* delegate = new LuaWebSocketDelegate();
        wSocket->init(*delegate, urlName,&protocols);
        tolua_pushusertype(tolua_S,(void*)wSocket,"WebSocket");
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
        CCArray*    protocolArray = ((CCArray*)  tolua_tousertype(tolua_S,3,0));
        std::vector<std::string> protocols;
        if (NULL != protocolArray) {
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(protocolArray, pObj)
            {
                CCString* pStr = (CCString*)pObj;
                if (NULL != pStr) {
                    protocols.push_back(pStr->getCString());
                }
            }
        }
        WebSocket *wSocket = new WebSocket();
        LuaWebSocketDelegate* delegate = new LuaWebSocketDelegate();
        wSocket->init(*delegate, urlName,&protocols);
        tolua_pushusertype(tolua_S,(void*)wSocket,"WebSocket");
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
        WebSocket* self = (WebSocket*)  tolua_tousertype(tolua_S,1,0);
        int tolua_ret = -1;
        if (NULL != self) {
            tolua_ret = self->getReadyState();
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

/* method: sendStrMsg of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_sendStrMsg00
static int tolua_Cocos2d_WebSocket_sendStrMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err)               ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        WebSocket* self    = (WebSocket*)  tolua_tousertype(tolua_S,1,0);
        const char *pData  = ((const char*)  tolua_tostring(tolua_S,2,0));
        if (NULL != self && NULL != pData && strlen(pData) > 0) {
            std::string strData = pData;
            self->send(strData);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'sendStrMsg'.",&tolua_err);
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
        WebSocket* self    = (WebSocket*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addHandlerOfDelegateEvent of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_registerScriptHandler00
static int tolua_Cocos2d_WebSocket_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        WebSocket* self    = (WebSocket*)  tolua_tousertype(tolua_S,1,0);
        if (NULL != self ) {
            int nFunID = (  toluafix_ref_function(tolua_S,2,0));
            WebSocket::webSocketScriptHandlerType handlerType = ((WebSocket::webSocketScriptHandlerType) (int)  tolua_tonumber(tolua_S,3,0));
            self->registerScriptHandler(nFunID, handlerType);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeHandlerOfDelegateEvent of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_unregisterScriptHandler00
static int tolua_Cocos2d_WebSocket_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        WebSocket* self    = (WebSocket*)  tolua_tousertype(tolua_S,1,0);
        if (NULL != self ) {
            WebSocket::webSocketScriptHandlerType handlerType = ((WebSocket::webSocketScriptHandlerType) (int)  tolua_tonumber(tolua_S,2,0));
            self->unregisterScriptHandler(handlerType);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendBinaryMsg of class WebSocket */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_WebSocket_sendBinaryMsg00
static int tolua_Cocos2d_WebSocket_sendBinaryMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !tolua_istable(tolua_S, 2, 0, &tolua_err)             ||
        !tolua_isnumber(tolua_S,3, 0,&tolua_err)             ||
        !tolua_isnoobj(tolua_S, 4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        WebSocket* self    = (WebSocket*)  tolua_tousertype(tolua_S,1,0);
        int   nLength      = lua_tonumber(tolua_S, 3);
        
        if (NULL != self && nLength > 0) {
            unsigned char* binaryArray = new unsigned char[nLength];
            for (int i = 0; i < nLength; i++) {
                binaryArray[i] = (unsigned char)tolua_tofieldnumber(tolua_S, 2, i+1, 0);
            }
            self->send(binaryArray, nLength);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'sendBinaryMsg'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

TOLUA_API int tolua_web_socket_open(lua_State* tolua_S){
    tolua_open(tolua_S);
    tolua_reg_Web_Socket_type(tolua_S);
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
      tolua_constant(tolua_S,"kStateConnecting",WebSocket::kStateConnecting);
      tolua_constant(tolua_S,"kStateOpen",WebSocket::kStateOpen);
      tolua_constant(tolua_S,"kStateClosing",WebSocket::kStateClosing);
      tolua_constant(tolua_S,"kStateClosed",WebSocket::kStateClosed);
      tolua_constant(tolua_S,"kwebSocketScriptHandlerOpen",WebSocket::kwebSocketScriptHandlerOpen);
      tolua_constant(tolua_S,"kwebSocketScriptHandlerMessage",WebSocket::kwebSocketScriptHandlerMessage);
      tolua_constant(tolua_S,"kwebSocketScriptHandlerClose",WebSocket::kwebSocketScriptHandlerClose);
      tolua_constant(tolua_S,"kwebSocketScriptHandlerError",WebSocket::kwebSocketScriptHandlerError);
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
        tolua_function(tolua_S, "sendStrMsg", tolua_Cocos2d_WebSocket_sendStrMsg00);
        tolua_function(tolua_S, "close", tolua_Cocos2d_WebSocket_close00);
        tolua_function(tolua_S, "registerScriptHandler", tolua_Cocos2d_WebSocket_registerScriptHandler00);
        tolua_function(tolua_S, "unregisterScriptHandler", tolua_Cocos2d_WebSocket_unregisterScriptHandler00);
        tolua_function(tolua_S, "sendBinaryMsg", tolua_Cocos2d_WebSocket_sendBinaryMsg00);
      tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
	return 1;
}
