#include "lua_cocos2dx_controller_auto.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CCGameController.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_controller_Controller_receiveExternalKeyEvent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Controller* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Controller",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Controller*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_Controller_receiveExternalKeyEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        bool arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Controller:receiveExternalKeyEvent");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.Controller:receiveExternalKeyEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_Controller_receiveExternalKeyEvent'", nullptr);
            return 0;
        }
        cobj->receiveExternalKeyEvent(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Controller:receiveExternalKeyEvent",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_Controller_receiveExternalKeyEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_Controller_getDeviceName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Controller* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Controller",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Controller*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_Controller_getDeviceName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_Controller_getDeviceName'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getDeviceName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Controller:getDeviceName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_Controller_getDeviceName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_Controller_isConnected(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Controller* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Controller",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Controller*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_Controller_isConnected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_Controller_isConnected'", nullptr);
            return 0;
        }
        bool ret = cobj->isConnected();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Controller:isConnected",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_Controller_isConnected'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_Controller_getDeviceId(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Controller* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Controller",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Controller*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_Controller_getDeviceId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_Controller_getDeviceId'", nullptr);
            return 0;
        }
        int ret = cobj->getDeviceId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Controller:getDeviceId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_Controller_getDeviceId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_Controller_setTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Controller* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Controller",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Controller*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_Controller_setTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Controller:setTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_Controller_setTag'", nullptr);
            return 0;
        }
        cobj->setTag(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Controller:setTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_Controller_setTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_Controller_getTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Controller* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Controller",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Controller*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_Controller_getTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_Controller_getTag'", nullptr);
            return 0;
        }
        int ret = cobj->getTag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Controller:getTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_Controller_getTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_Controller_startDiscoveryController(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Controller",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_Controller_startDiscoveryController'", nullptr);
            return 0;
        }
        cocos2d::Controller::startDiscoveryController();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Controller:startDiscoveryController",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_Controller_startDiscoveryController'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_controller_Controller_stopDiscoveryController(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Controller",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_Controller_stopDiscoveryController'", nullptr);
            return 0;
        }
        cocos2d::Controller::stopDiscoveryController();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Controller:stopDiscoveryController",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_Controller_stopDiscoveryController'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_controller_Controller_getControllerByTag(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Controller",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Controller:getControllerByTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_Controller_getControllerByTag'", nullptr);
            return 0;
        }
        cocos2d::Controller* ret = cocos2d::Controller::getControllerByTag(arg0);
        object_to_luaval<cocos2d::Controller>(tolua_S, "cc.Controller",(cocos2d::Controller*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Controller:getControllerByTag",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_Controller_getControllerByTag'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_controller_Controller_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Controller)");
    return 0;
}

int lua_register_cocos2dx_controller_Controller(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Controller");
    tolua_cclass(tolua_S,"Controller","cc.Controller","",nullptr);

    tolua_beginmodule(tolua_S,"Controller");
        tolua_function(tolua_S,"receiveExternalKeyEvent",lua_cocos2dx_controller_Controller_receiveExternalKeyEvent);
        tolua_function(tolua_S,"getDeviceName",lua_cocos2dx_controller_Controller_getDeviceName);
        tolua_function(tolua_S,"isConnected",lua_cocos2dx_controller_Controller_isConnected);
        tolua_function(tolua_S,"getDeviceId",lua_cocos2dx_controller_Controller_getDeviceId);
        tolua_function(tolua_S,"setTag",lua_cocos2dx_controller_Controller_setTag);
        tolua_function(tolua_S,"getTag",lua_cocos2dx_controller_Controller_getTag);
        tolua_function(tolua_S,"startDiscoveryController", lua_cocos2dx_controller_Controller_startDiscoveryController);
        tolua_function(tolua_S,"stopDiscoveryController", lua_cocos2dx_controller_Controller_stopDiscoveryController);
        tolua_function(tolua_S,"getControllerByTag", lua_cocos2dx_controller_Controller_getControllerByTag);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Controller).name();
    g_luaType[typeName] = "cc.Controller";
    g_typeCast["Controller"] = "cc.Controller";
    return 1;
}

int lua_cocos2dx_controller_EventController_getControllerEventType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_EventController_getControllerEventType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_EventController_getControllerEventType'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getControllerEventType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:getControllerEventType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_EventController_getControllerEventType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_EventController_setConnectStatus(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_EventController_setConnectStatus'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.EventController:setConnectStatus");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_EventController_setConnectStatus'", nullptr);
            return 0;
        }
        cobj->setConnectStatus(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:setConnectStatus",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_EventController_setConnectStatus'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_EventController_isConnected(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_EventController_isConnected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_EventController_isConnected'", nullptr);
            return 0;
        }
        bool ret = cobj->isConnected();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:isConnected",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_EventController_isConnected'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_EventController_setKeyCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_EventController_setKeyCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.EventController:setKeyCode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_EventController_setKeyCode'", nullptr);
            return 0;
        }
        cobj->setKeyCode(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:setKeyCode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_EventController_setKeyCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_EventController_getController(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_EventController_getController'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_EventController_getController'", nullptr);
            return 0;
        }
        cocos2d::Controller* ret = cobj->getController();
        object_to_luaval<cocos2d::Controller>(tolua_S, "cc.Controller",(cocos2d::Controller*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:getController",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_EventController_getController'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_EventController_getKeyCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_controller_EventController_getKeyCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_EventController_getKeyCode'", nullptr);
            return 0;
        }
        int ret = cobj->getKeyCode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:getKeyCode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_EventController_getKeyCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_controller_EventController_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            cocos2d::EventController::ControllerEventType arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.EventController:EventController");

            if (!ok) { break; }
            cocos2d::Controller* arg1;
            ok &= luaval_to_object<cocos2d::Controller>(tolua_S, 3, "cc.Controller",&arg1);

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.EventController:EventController");

            if (!ok) { break; }
            cobj = new cocos2d::EventController(arg0, arg1, arg2);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventController");
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::EventController::ControllerEventType arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.EventController:EventController");

            if (!ok) { break; }
            cocos2d::Controller* arg1;
            ok &= luaval_to_object<cocos2d::Controller>(tolua_S, 3, "cc.Controller",&arg1);

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.EventController:EventController");

            if (!ok) { break; }
            cobj = new cocos2d::EventController(arg0, arg1, arg2);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventController");
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.EventController:EventController",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_EventController_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_controller_EventController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventController)");
    return 0;
}

int lua_register_cocos2dx_controller_EventController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventController");
    tolua_cclass(tolua_S,"EventController","cc.EventController","cc.Event",nullptr);

    tolua_beginmodule(tolua_S,"EventController");
        tolua_function(tolua_S,"new",lua_cocos2dx_controller_EventController_constructor);
        tolua_function(tolua_S,"getControllerEventType",lua_cocos2dx_controller_EventController_getControllerEventType);
        tolua_function(tolua_S,"setConnectStatus",lua_cocos2dx_controller_EventController_setConnectStatus);
        tolua_function(tolua_S,"isConnected",lua_cocos2dx_controller_EventController_isConnected);
        tolua_function(tolua_S,"setKeyCode",lua_cocos2dx_controller_EventController_setKeyCode);
        tolua_function(tolua_S,"getController",lua_cocos2dx_controller_EventController_getController);
        tolua_function(tolua_S,"getKeyCode",lua_cocos2dx_controller_EventController_getKeyCode);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::EventController).name();
    g_luaType[typeName] = "cc.EventController";
    g_typeCast["EventController"] = "cc.EventController";
    return 1;
}

int lua_cocos2dx_controller_EventListenerController_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.EventListenerController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_controller_EventListenerController_create'", nullptr);
            return 0;
        }
        cocos2d::EventListenerController* ret = cocos2d::EventListenerController::create();
        object_to_luaval<cocos2d::EventListenerController>(tolua_S, "cc.EventListenerController",(cocos2d::EventListenerController*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EventListenerController:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_controller_EventListenerController_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_controller_EventListenerController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventListenerController)");
    return 0;
}

int lua_register_cocos2dx_controller_EventListenerController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventListenerController");
    tolua_cclass(tolua_S,"EventListenerController","cc.EventListenerController","cc.EventListener",nullptr);

    tolua_beginmodule(tolua_S,"EventListenerController");
        tolua_function(tolua_S,"create", lua_cocos2dx_controller_EventListenerController_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::EventListenerController).name();
    g_luaType[typeName] = "cc.EventListenerController";
    g_typeCast["EventListenerController"] = "cc.EventListenerController";
    return 1;
}
TOLUA_API int register_all_cocos2dx_controller(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_controller_EventListenerController(tolua_S);
	lua_register_cocos2dx_controller_Controller(tolua_S);
	lua_register_cocos2dx_controller_EventController(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

#endif
