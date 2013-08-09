#include "lua_cocos2dx_auto.hpp"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"

static int tolua_cocos2d_MenuItemImage_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"MenuItemImage",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    do {
        if (argc == 0)
        {
            MenuItemImage* tolua_ret = (MenuItemImage*)MenuItemImage::create();
            //Uncheck
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
            return 1;
        }
    } while (0);
    do {
#if COCOS2D_DEBUG >= 1
		if (!tolua_isstring(tolua_S,2,0,&tolua_err) ||
            !tolua_isstring(tolua_S,3,0,&tolua_err))
        {
            ok = false;
		}
#endif        
        if (!ok)
        {
            ok = true;
            break;
        }
        const char* normalImage = ((const char*)  tolua_tostring(tolua_S,2,0));
        const char* selectedImage = ((const char*)  tolua_tostring(tolua_S,3,0));
        MenuItemImage* tolua_ret = (MenuItemImage*)  MenuItemImage::create(normalImage,selectedImage);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
        return 1;
        
    } while (0);
    do {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S,2,0,&tolua_err) ||
            !tolua_isstring(tolua_S,3,0,&tolua_err) ||
            !tolua_isstring(tolua_S,4,0,&tolua_err) )
        {
            goto tolua_lerror;
            break;
        }
#endif
        const char* normalImage = ((const char*)  tolua_tostring(tolua_S,2,0));
        const char* selectedImage = ((const char*)  tolua_tostring(tolua_S,3,0));
        const char* disabledImage = ((const char*)  tolua_tostring(tolua_S,4,0));
        
        MenuItemImage* tolua_ret = (MenuItemImage*)  MenuItemImage::create(normalImage,selectedImage,disabledImage);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
        return 1;
        
    } while (0);

	CCLOG("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Follow_initWithTarget'.\n",&tolua_err);
#endif
	return 0;
    
}

static int tolua_cocos2d_Menu_create(lua_State* tolua_S)
{
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"Menu",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0 )
    {
        cocos2d::Array* array = cocos2d::Array::create();
        if (NULL == array)
        {
            printf("Menu create method create array fail\n");
            return 0;
        }
        uint32_t i = 1;
        while (i <= argc)
        {
            if (!tolua_isuserdata(tolua_S, 1 + i, 0, &tolua_err) )
            {
                goto tolua_lerror;
                return 0;
            }
            
            cocos2d::Object* item = static_cast<cocos2d::Object*>(tolua_tousertype(tolua_S, 1 + i, NULL));
            if (NULL != item)
            {
                array->addObject(item);
                ++i;
            }
            
        }
        cocos2d::Menu* tolua_ret = cocos2d::Menu::createWithArray(array);
        //UnCheck
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Menu");
        return 1;
    }
    else if(argc == 0)
    {
        cocos2d::Menu* tolua_ret = cocos2d::Menu::create();
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
        return 1;
    }
    
    CCLOG("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Follow_initWithTarget'.\n",&tolua_err);
#endif
	return 0;
}
//tolua_cocos2d_Menu_create
static int tolua_cocos2d_MenuItem_registerScriptTapHandler(lua_State* tolua_S)
{
    int argc = 0;
    MenuItem* cobj = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"MenuItem",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = static_cast<cocos2d::MenuItemImage*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2d_MenuItem_registerScriptTapHandler00'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)cobj, handler, ScriptHandlerMgr::kMenuClickHandler);
        return 0;
    }
    
    CCLOG("wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItem_unregisterScriptTapHandler(lua_State* tolua_S)
{
    int argc = 0;
    MenuItem* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"MenuItem",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = static_cast<cocos2d::MenuItemImage*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2d_MenuItem_unregisterScriptTapHandler00'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)cobj, ScriptHandlerMgr::kMenuClickHandler);
        return 0;
    }
    
    CCLOG("wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptTapHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_registerScriptTouchHandler(lua_State* tolua_S)
{
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptTouchHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >=1 && argc <= 4) {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        bool isMultiTouches  = false;
        int  priority        = 0;
        bool swallowTouches  = true;
        
        if (argc >= 2) {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isboolean(tolua_S,3,0,&tolua_err)) {
                goto tolua_lerror;
            }
#endif
            isMultiTouches = (bool)tolua_toboolean(tolua_S,3,false);
        }
        
        if (argc >= 3) {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S,4,0,&tolua_err)) {
                goto tolua_lerror;
            }
#endif
            priority = (int)tolua_tonumber(tolua_S,4,0);
        }
        
        if (argc == 4) {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isboolean(tolua_S,5,0,&tolua_err)) {
                goto tolua_lerror;
            }
#endif
            swallowTouches = (bool)tolua_toboolean(tolua_S,5,true);
        }
        
        Touch::DispatchMode touchesMode = Touch::DispatchMode::ALL_AT_ONCE;
        if (!isMultiTouches)
            touchesMode = Touch::DispatchMode::ONE_BY_ONE;
        self->setTouchMode(touchesMode);
        self->setTouchPriority(priority);
		self->setSwallowsTouches(swallowTouches);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::kTouchesHandler);
        return 0;
    }
    
    CCLOG("wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptTouchHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptTouchHandler(lua_State* tolua_S)
{
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptTouchHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, ScriptHandlerMgr::kTouchesHandler);
        return 0;
    }
    
    CCLOG("wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptTapHandler'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Scheduler_scheduleScriptFunc00(lua_State* tolua_S)
{
    int argc = 0;
    Scheduler* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Scheduler",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Scheduler*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Scheduler_scheduleScriptFunc00'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (3 == argc) {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
            !tolua_isboolean(tolua_S,4,0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        float interval = (float)  tolua_tonumber(tolua_S,3,0);
        bool  paused   = (bool)  tolua_toboolean(tolua_S,4,0);
        unsigned int tolua_ret = (unsigned int)  self->scheduleScriptFunc(handler,interval,paused);
        tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        return 1;
    }
    
    CCLOG("wrong number of arguments: %d, was expecting %d\n", argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'scheduleScriptFunc'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Scheduler_unscheduleScriptEntry(lua_State* tolua_S)
{
    int argc = 0;
    Scheduler* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Scheduler",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Scheduler*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Scheduler_unscheduleScriptEntry'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc) {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        unsigned int scheduleScriptEntryID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        self->unscheduleScriptEntry(scheduleScriptEntryID);
        return 0;
    }
    
    CCLOG("wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unscheduleScriptEntry'.",&tolua_err);
    return 0;
#endif
}

//void lua_extend_cocos2dx_MenuItem
//{
//    
//}

int register_all_cocos2dx_manual(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    lua_pushstring(tolua_S,"MenuItem");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerScriptTapHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItem_registerScriptTapHandler);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "unregisterScriptTapHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItem_unregisterScriptTapHandler);
        lua_rawset(tolua_S, -3);
    }
    
    lua_pushstring(tolua_S,"MenuItemImage");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemImage_create);
        lua_rawset(tolua_S,-3);
    }
    
    lua_pushstring(tolua_S, "Menu");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Menu_create);
        lua_rawset(tolua_S,-3);
    }
    
    lua_pushstring(tolua_S,"Layer");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerScriptTouchHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Layer_registerScriptTouchHandler);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "unregisterScriptTouchHandler");
        lua_pushcfunction(tolua_S,tolua_Cocos2d_unregisterScriptTouchHandler00);
        lua_rawset(tolua_S, -3);
//        lua_pushstring(lua_S, "registerScriptKeypadHandler");
//        lua_pushcfunction(lua_S, tolua_Cocos2d_registerScriptKeypadHandler00);
//        lua_rawset(lua_S, -3);
//        lua_pushstring(lua_S, "unregisterScriptKeypadHandler");
//        lua_pushcfunction(lua_S, tolua_Cocos2d_unregisterScriptKeypadHandler00);
//        lua_rawset(lua_S, -3);
//        lua_pushstring(lua_S, "registerScriptAccelerateHandler");
//        lua_pushcfunction(lua_S, tolua_Cocos2d_registerScriptAccelerateHandler00);
//        lua_rawset(lua_S, -3);
//        lua_pushstring(lua_S, "unregisterScriptAccelerateHandler");
//        lua_pushcfunction(lua_S, tolua_Cocos2d_unregisterScriptAccelerateHandler00);
//        lua_rawset(lua_S, -3);
    }
    
    lua_pushstring(tolua_S,"Scheduler");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"scheduleScriptFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Scheduler_scheduleScriptFunc00);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "unscheduleScriptEntry");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Scheduler_unscheduleScriptEntry);
        lua_rawset(tolua_S, -3);
    }
    return 0;
}