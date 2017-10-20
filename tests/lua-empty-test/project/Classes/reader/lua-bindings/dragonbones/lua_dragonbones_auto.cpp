#include "lua-bindings/dragonbones/lua_dragonbones_auto.hpp"
#include "CCArmatureDisplay.h"
#include "Slot.h"
#include "Animation.h"
#include "AnimationState.h"
#include "WorldClock.h"
#include "EventObject.h"
#include "Slot.h"
#include "CCFactory.h"
#include "Transform.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_creator_dragonbones_Transform_getRotation(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Transform* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Transform",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Transform*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Transform_getRotation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Transform_getRotation'", nullptr);
            return 0;
        }
        double ret = cobj->getRotation();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Transform:getRotation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Transform_getRotation'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Transform_setRotation(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Transform* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Transform",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Transform*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Transform_setRotation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccdb.Transform:setRotation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Transform_setRotation'", nullptr);
            return 0;
        }
        cobj->setRotation(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Transform:setRotation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Transform_setRotation'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Transform_normalizeRadian(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccdb.Transform",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccdb.Transform:normalizeRadian");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Transform_normalizeRadian'", nullptr);
            return 0;
        }
        double ret = dragonBones::Transform::normalizeRadian(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccdb.Transform:normalizeRadian",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Transform_normalizeRadian'.",&tolua_err);
#endif
    return 0;
}
int lua_creator_dragonbones_Transform_constructor(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Transform* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Transform_constructor'", nullptr);
            return 0;
        }
        cobj = new dragonBones::Transform();
        tolua_pushusertype(tolua_S,(void*)cobj,"ccdb.Transform");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Transform:Transform",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Transform_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_creator_dragonbones_Transform_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Transform)");
    return 0;
}

int lua_register_creator_dragonbones_Transform(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.Transform");
    tolua_cclass(tolua_S,"Transform","ccdb.Transform","",nullptr);

    tolua_beginmodule(tolua_S,"Transform");
        tolua_function(tolua_S,"new",lua_creator_dragonbones_Transform_constructor);
        tolua_function(tolua_S,"getRotation",lua_creator_dragonbones_Transform_getRotation);
        tolua_function(tolua_S,"setRotation",lua_creator_dragonbones_Transform_setRotation);
        tolua_function(tolua_S,"normalizeRadian", lua_creator_dragonbones_Transform_normalizeRadian);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::Transform).name();
    g_luaType[typeName] = "ccdb.Transform";
    g_typeCast["Transform"] = "ccdb.Transform";
    return 1;
}

int lua_creator_dragonbones_EventObject_getTypeIndex(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccdb.EventObject",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_EventObject_getTypeIndex'", nullptr);
            return 0;
        }
        unsigned long ret = dragonBones::EventObject::getTypeIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccdb.EventObject:getTypeIndex",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_EventObject_getTypeIndex'.",&tolua_err);
#endif
    return 0;
}
int lua_creator_dragonbones_EventObject_constructor(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::EventObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_EventObject_constructor'", nullptr);
            return 0;
        }
        cobj = new dragonBones::EventObject();
        tolua_pushusertype(tolua_S,(void*)cobj,"ccdb.EventObject");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.EventObject:EventObject",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_EventObject_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_creator_dragonbones_EventObject_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventObject)");
    return 0;
}

int lua_register_creator_dragonbones_EventObject(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.EventObject");
    tolua_cclass(tolua_S,"EventObject","ccdb.EventObject","ccdb.BaseObject",nullptr);

    tolua_beginmodule(tolua_S,"EventObject");
        tolua_function(tolua_S,"new",lua_creator_dragonbones_EventObject_constructor);
        tolua_function(tolua_S,"getTypeIndex", lua_creator_dragonbones_EventObject_getTypeIndex);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::EventObject).name();
    g_luaType[typeName] = "ccdb.EventObject";
    g_typeCast["EventObject"] = "ccdb.EventObject";
    return 1;
}

int lua_creator_dragonbones_Armature_getSlot(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_getSlot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Armature:getSlot");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_getSlot'", nullptr);
            return 0;
        }
        dragonBones::Slot* ret = cobj->getSlot(arg0);
        object_to_luaval<dragonBones::Slot>(tolua_S, "ccdb.Slot",(dragonBones::Slot*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:getSlot",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_getSlot'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_getCacheFrameRate(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_getCacheFrameRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_getCacheFrameRate'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getCacheFrameRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:getCacheFrameRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_getCacheFrameRate'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_getName(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_getName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_getName'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getName();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:getName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_getName'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_dispose(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_dispose'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_dispose'", nullptr);
            return 0;
        }
        cobj->dispose();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:dispose",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_dispose'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_addSlot(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_addSlot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        dragonBones::Slot* arg0;
        std::string arg1;

        ok &= luaval_to_object<dragonBones::Slot>(tolua_S, 2, "ccdb.Slot",&arg0, "ccdb.Armature:addSlot");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.Armature:addSlot");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_addSlot'", nullptr);
            return 0;
        }
        cobj->addSlot(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:addSlot",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_addSlot'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_invalidUpdate(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_invalidUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_invalidUpdate'", nullptr);
            return 0;
        }
        cobj->invalidUpdate();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Armature:invalidUpdate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_invalidUpdate'", nullptr);
            return 0;
        }
        cobj->invalidUpdate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Armature:invalidUpdate");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccdb.Armature:invalidUpdate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_invalidUpdate'", nullptr);
            return 0;
        }
        cobj->invalidUpdate(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:invalidUpdate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_invalidUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_getBoneByDisplay(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_getBoneByDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        void* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_getBoneByDisplay'", nullptr);
            return 0;
        }
        dragonBones::Bone* ret = cobj->getBoneByDisplay(arg0);
        object_to_luaval<dragonBones::Bone>(tolua_S, "ccdb.Bone",(dragonBones::Bone*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:getBoneByDisplay",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_getBoneByDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_setCacheFrameRate(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_setCacheFrameRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccdb.Armature:setCacheFrameRate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_setCacheFrameRate'", nullptr);
            return 0;
        }
        cobj->setCacheFrameRate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:setCacheFrameRate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_setCacheFrameRate'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_removeSlot(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_removeSlot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        dragonBones::Slot* arg0;

        ok &= luaval_to_object<dragonBones::Slot>(tolua_S, 2, "ccdb.Slot",&arg0, "ccdb.Armature:removeSlot");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_removeSlot'", nullptr);
            return 0;
        }
        cobj->removeSlot(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:removeSlot",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_removeSlot'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature__bufferEvent(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature__bufferEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        dragonBones::EventObject* arg0;
        std::string arg1;

        ok &= luaval_to_object<dragonBones::EventObject>(tolua_S, 2, "ccdb.EventObject",&arg0, "ccdb.Armature:_bufferEvent");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.Armature:_bufferEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature__bufferEvent'", nullptr);
            return 0;
        }
        cobj->_bufferEvent(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:_bufferEvent",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature__bufferEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_addBone(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_addBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        dragonBones::Bone* arg0;

        ok &= luaval_to_object<dragonBones::Bone>(tolua_S, 2, "ccdb.Bone",&arg0, "ccdb.Armature:addBone");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_addBone'", nullptr);
            return 0;
        }
        cobj->addBone(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        dragonBones::Bone* arg0;
        std::string arg1;

        ok &= luaval_to_object<dragonBones::Bone>(tolua_S, 2, "ccdb.Bone",&arg0, "ccdb.Armature:addBone");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.Armature:addBone");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_addBone'", nullptr);
            return 0;
        }
        cobj->addBone(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:addBone",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_addBone'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_advanceTime(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_advanceTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccdb.Armature:advanceTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_advanceTime'", nullptr);
            return 0;
        }
        cobj->advanceTime(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:advanceTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_advanceTime'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_getBone(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_getBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Armature:getBone");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_getBone'", nullptr);
            return 0;
        }
        dragonBones::Bone* ret = cobj->getBone(arg0);
        object_to_luaval<dragonBones::Bone>(tolua_S, "ccdb.Bone",(dragonBones::Bone*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:getBone",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_getBone'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_getParent(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_getParent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_getParent'", nullptr);
            return 0;
        }
        dragonBones::Slot* ret = cobj->getParent();
        object_to_luaval<dragonBones::Slot>(tolua_S, "ccdb.Slot",(dragonBones::Slot*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:getParent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_getParent'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_getSlotByDisplay(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_getSlotByDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        void* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_getSlotByDisplay'", nullptr);
            return 0;
        }
        dragonBones::Slot* ret = cobj->getSlotByDisplay(arg0);
        object_to_luaval<dragonBones::Slot>(tolua_S, "ccdb.Slot",(dragonBones::Slot*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:getSlotByDisplay",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_getSlotByDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_removeBone(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_removeBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        dragonBones::Bone* arg0;

        ok &= luaval_to_object<dragonBones::Bone>(tolua_S, 2, "ccdb.Bone",&arg0, "ccdb.Armature:removeBone");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_removeBone'", nullptr);
            return 0;
        }
        cobj->removeBone(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:removeBone",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_removeBone'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_replaceTexture(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Armature_replaceTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        void* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_replaceTexture'", nullptr);
            return 0;
        }
        cobj->replaceTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Armature:replaceTexture",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_replaceTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Armature_getTypeIndex(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccdb.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Armature_getTypeIndex'", nullptr);
            return 0;
        }
        unsigned long ret = dragonBones::Armature::getTypeIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccdb.Armature:getTypeIndex",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Armature_getTypeIndex'.",&tolua_err);
#endif
    return 0;
}
static int lua_creator_dragonbones_Armature_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Armature)");
    return 0;
}

int lua_register_creator_dragonbones_Armature(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.Armature");
    tolua_cclass(tolua_S,"Armature","ccdb.Armature","ccdb.BaseObject",nullptr);

    tolua_beginmodule(tolua_S,"Armature");
        tolua_function(tolua_S,"getSlot",lua_creator_dragonbones_Armature_getSlot);
        tolua_function(tolua_S,"getCacheFrameRate",lua_creator_dragonbones_Armature_getCacheFrameRate);
        tolua_function(tolua_S,"getName",lua_creator_dragonbones_Armature_getName);
        tolua_function(tolua_S,"dispose",lua_creator_dragonbones_Armature_dispose);
        tolua_function(tolua_S,"addSlot",lua_creator_dragonbones_Armature_addSlot);
        tolua_function(tolua_S,"invalidUpdate",lua_creator_dragonbones_Armature_invalidUpdate);
        tolua_function(tolua_S,"getBoneByDisplay",lua_creator_dragonbones_Armature_getBoneByDisplay);
        tolua_function(tolua_S,"setCacheFrameRate",lua_creator_dragonbones_Armature_setCacheFrameRate);
        tolua_function(tolua_S,"removeSlot",lua_creator_dragonbones_Armature_removeSlot);
        tolua_function(tolua_S,"_bufferEvent",lua_creator_dragonbones_Armature__bufferEvent);
        tolua_function(tolua_S,"addBone",lua_creator_dragonbones_Armature_addBone);
        tolua_function(tolua_S,"advanceTime",lua_creator_dragonbones_Armature_advanceTime);
        tolua_function(tolua_S,"getBone",lua_creator_dragonbones_Armature_getBone);
        tolua_function(tolua_S,"getParent",lua_creator_dragonbones_Armature_getParent);
        tolua_function(tolua_S,"getSlotByDisplay",lua_creator_dragonbones_Armature_getSlotByDisplay);
        tolua_function(tolua_S,"removeBone",lua_creator_dragonbones_Armature_removeBone);
        tolua_function(tolua_S,"replaceTexture",lua_creator_dragonbones_Armature_replaceTexture);
        tolua_function(tolua_S,"getTypeIndex", lua_creator_dragonbones_Armature_getTypeIndex);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::Armature).name();
    g_luaType[typeName] = "ccdb.Armature";
    g_typeCast["Armature"] = "ccdb.Armature";
    return 1;
}

int lua_creator_dragonbones_Animation_isPlaying(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_isPlaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_isPlaying'", nullptr);
            return 0;
        }
        bool ret = cobj->isPlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:isPlaying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_isPlaying'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_fadeIn(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        double arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0, arg1);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        double arg1;
        int arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0, arg1, arg2);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 4) 
    {
        std::string arg0;
        double arg1;
        int arg2;
        int arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0, arg1, arg2, arg3);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 5) 
    {
        std::string arg0;
        double arg1;
        int arg2;
        int arg3;
        std::string arg4;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccdb.Animation:fadeIn");

        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0, arg1, arg2, arg3, arg4);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 6) 
    {
        std::string arg0;
        double arg1;
        int arg2;
        int arg3;
        std::string arg4;
        dragonBones::AnimationFadeOutMode arg5;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccdb.Animation:fadeIn");

        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 7) 
    {
        std::string arg0;
        double arg1;
        int arg2;
        int arg3;
        std::string arg4;
        dragonBones::AnimationFadeOutMode arg5;
        bool arg6;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccdb.Animation:fadeIn");

        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 8,&arg6, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 8) 
    {
        std::string arg0;
        double arg1;
        int arg2;
        int arg3;
        std::string arg4;
        dragonBones::AnimationFadeOutMode arg5;
        bool arg6;
        bool arg7;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccdb.Animation:fadeIn");

        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 8,&arg6, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 9,&arg7, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 9) 
    {
        std::string arg0;
        double arg1;
        int arg2;
        int arg3;
        std::string arg4;
        dragonBones::AnimationFadeOutMode arg5;
        bool arg6;
        bool arg7;
        bool arg8;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccdb.Animation:fadeIn");

        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 8,&arg6, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 9,&arg7, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 10,&arg8, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 10) 
    {
        std::string arg0;
        double arg1;
        int arg2;
        int arg3;
        std::string arg4;
        dragonBones::AnimationFadeOutMode arg5;
        bool arg6;
        bool arg7;
        bool arg8;
        bool arg9;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:fadeIn");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccdb.Animation:fadeIn");

        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "ccdb.Animation:fadeIn");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 8,&arg6, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 9,&arg7, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 10,&arg8, "ccdb.Animation:fadeIn");

        ok &= luaval_to_boolean(tolua_S, 11,&arg9, "ccdb.Animation:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_fadeIn'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->fadeIn(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:fadeIn",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_fadeIn'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_isCompleted(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_isCompleted'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_isCompleted'", nullptr);
            return 0;
        }
        bool ret = cobj->isCompleted();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:isCompleted",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_isCompleted'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_reset(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_reset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_reset'", nullptr);
            return 0;
        }
        cobj->reset();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:reset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_reset'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_play(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_play'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->play();
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:play");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_play'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->play(arg0);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:play");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccdb.Animation:play");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_play'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->play(arg0, arg1);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:play",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_play'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_getState(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_getState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:getState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_getState'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->getState(arg0);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:getState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_getState'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_stop(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:stop");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_stop'", nullptr);
            return 0;
        }
        cobj->stop(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:stop",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_getLastAnimationName(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_getLastAnimationName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_getLastAnimationName'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getLastAnimationName();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:getLastAnimationName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_getLastAnimationName'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_getLastAnimationState(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_getLastAnimationState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_getLastAnimationState'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->getLastAnimationState();
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:getLastAnimationState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_getLastAnimationState'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_gotoAndPlayByTime(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_gotoAndPlayByTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndPlayByTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndPlayByTime'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndPlayByTime(arg0);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        double arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndPlayByTime");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:gotoAndPlayByTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndPlayByTime'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndPlayByTime(arg0, arg1);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        double arg1;
        int arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndPlayByTime");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:gotoAndPlayByTime");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:gotoAndPlayByTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndPlayByTime'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndPlayByTime(arg0, arg1, arg2);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:gotoAndPlayByTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_gotoAndPlayByTime'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_gotoAndPlayByProgress(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_gotoAndPlayByProgress'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndPlayByProgress");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndPlayByProgress'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndPlayByProgress(arg0);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        double arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndPlayByProgress");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:gotoAndPlayByProgress");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndPlayByProgress'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndPlayByProgress(arg0, arg1);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        double arg1;
        int arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndPlayByProgress");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:gotoAndPlayByProgress");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:gotoAndPlayByProgress");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndPlayByProgress'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndPlayByProgress(arg0, arg1, arg2);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:gotoAndPlayByProgress",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_gotoAndPlayByProgress'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_hasAnimation(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_hasAnimation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:hasAnimation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_hasAnimation'", nullptr);
            return 0;
        }
        bool ret = cobj->hasAnimation(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:hasAnimation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_hasAnimation'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_gotoAndStopByTime(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_gotoAndStopByTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndStopByTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndStopByTime'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndStopByTime(arg0);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        double arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndStopByTime");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:gotoAndStopByTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndStopByTime'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndStopByTime(arg0, arg1);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:gotoAndStopByTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_gotoAndStopByTime'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_gotoAndStopByProgress(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_gotoAndStopByProgress'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndStopByProgress");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndStopByProgress'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndStopByProgress(arg0);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        double arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndStopByProgress");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccdb.Animation:gotoAndStopByProgress");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndStopByProgress'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndStopByProgress(arg0, arg1);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:gotoAndStopByProgress",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_gotoAndStopByProgress'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_gotoAndPlayByFrame(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_gotoAndPlayByFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndPlayByFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndPlayByFrame'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndPlayByFrame(arg0);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        unsigned int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndPlayByFrame");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccdb.Animation:gotoAndPlayByFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndPlayByFrame'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndPlayByFrame(arg0, arg1);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        unsigned int arg1;
        int arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndPlayByFrame");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccdb.Animation:gotoAndPlayByFrame");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccdb.Animation:gotoAndPlayByFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndPlayByFrame'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndPlayByFrame(arg0, arg1, arg2);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:gotoAndPlayByFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_gotoAndPlayByFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_gotoAndStopByFrame(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Animation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Animation_gotoAndStopByFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndStopByFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndStopByFrame'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndStopByFrame(arg0);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        unsigned int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.Animation:gotoAndStopByFrame");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccdb.Animation:gotoAndStopByFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_gotoAndStopByFrame'", nullptr);
            return 0;
        }
        dragonBones::AnimationState* ret = cobj->gotoAndStopByFrame(arg0, arg1);
        object_to_luaval<dragonBones::AnimationState>(tolua_S, "ccdb.AnimationState",(dragonBones::AnimationState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:gotoAndStopByFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_gotoAndStopByFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Animation_getTypeIndex(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccdb.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_getTypeIndex'", nullptr);
            return 0;
        }
        unsigned long ret = dragonBones::Animation::getTypeIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccdb.Animation:getTypeIndex",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_getTypeIndex'.",&tolua_err);
#endif
    return 0;
}
int lua_creator_dragonbones_Animation_constructor(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Animation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Animation_constructor'", nullptr);
            return 0;
        }
        cobj = new dragonBones::Animation();
        tolua_pushusertype(tolua_S,(void*)cobj,"ccdb.Animation");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Animation:Animation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Animation_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_creator_dragonbones_Animation_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Animation)");
    return 0;
}

int lua_register_creator_dragonbones_Animation(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.Animation");
    tolua_cclass(tolua_S,"Animation","ccdb.Animation","ccdb.BaseObject",nullptr);

    tolua_beginmodule(tolua_S,"Animation");
        tolua_function(tolua_S,"new",lua_creator_dragonbones_Animation_constructor);
        tolua_function(tolua_S,"isPlaying",lua_creator_dragonbones_Animation_isPlaying);
        tolua_function(tolua_S,"fadeIn",lua_creator_dragonbones_Animation_fadeIn);
        tolua_function(tolua_S,"isCompleted",lua_creator_dragonbones_Animation_isCompleted);
        tolua_function(tolua_S,"reset",lua_creator_dragonbones_Animation_reset);
        tolua_function(tolua_S,"play",lua_creator_dragonbones_Animation_play);
        tolua_function(tolua_S,"getState",lua_creator_dragonbones_Animation_getState);
        tolua_function(tolua_S,"stop",lua_creator_dragonbones_Animation_stop);
        tolua_function(tolua_S,"getLastAnimationName",lua_creator_dragonbones_Animation_getLastAnimationName);
        tolua_function(tolua_S,"getLastAnimationState",lua_creator_dragonbones_Animation_getLastAnimationState);
        tolua_function(tolua_S,"gotoAndPlayByTime",lua_creator_dragonbones_Animation_gotoAndPlayByTime);
        tolua_function(tolua_S,"gotoAndPlayByProgress",lua_creator_dragonbones_Animation_gotoAndPlayByProgress);
        tolua_function(tolua_S,"hasAnimation",lua_creator_dragonbones_Animation_hasAnimation);
        tolua_function(tolua_S,"gotoAndStopByTime",lua_creator_dragonbones_Animation_gotoAndStopByTime);
        tolua_function(tolua_S,"gotoAndStopByProgress",lua_creator_dragonbones_Animation_gotoAndStopByProgress);
        tolua_function(tolua_S,"gotoAndPlayByFrame",lua_creator_dragonbones_Animation_gotoAndPlayByFrame);
        tolua_function(tolua_S,"gotoAndStopByFrame",lua_creator_dragonbones_Animation_gotoAndStopByFrame);
        tolua_function(tolua_S,"getTypeIndex", lua_creator_dragonbones_Animation_getTypeIndex);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::Animation).name();
    g_luaType[typeName] = "ccdb.Animation";
    g_typeCast["Animation"] = "ccdb.Animation";
    return 1;
}

int lua_creator_dragonbones_Bone_getIK(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Bone_getIK'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Bone_getIK'", nullptr);
            return 0;
        }
        dragonBones::Bone* ret = cobj->getIK();
        object_to_luaval<dragonBones::Bone>(tolua_S, "ccdb.Bone",(dragonBones::Bone*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Bone:getIK",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Bone_getIK'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Bone_getIKChainIndex(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Bone_getIKChainIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Bone_getIKChainIndex'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getIKChainIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Bone:getIKChainIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Bone_getIKChainIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Bone_contains(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Bone_contains'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const dragonBones::TransformObject* arg0;

        ok &= luaval_to_object<const dragonBones::TransformObject>(tolua_S, 2, "ccdb.TransformObject",&arg0, "ccdb.Bone:contains");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Bone_contains'", nullptr);
            return 0;
        }
        bool ret = cobj->contains(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Bone:contains",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Bone_contains'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Bone_getIKChain(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Bone_getIKChain'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Bone_getIKChain'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getIKChain();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Bone:getIKChain",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Bone_getIKChain'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Bone_getVisible(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Bone_getVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Bone_getVisible'", nullptr);
            return 0;
        }
        bool ret = cobj->getVisible();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Bone:getVisible",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Bone_getVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Bone_setVisible(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Bone_setVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccdb.Bone:setVisible");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Bone_setVisible'", nullptr);
            return 0;
        }
        cobj->setVisible(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Bone:setVisible",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Bone_setVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Bone_invalidUpdate(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Bone_invalidUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Bone_invalidUpdate'", nullptr);
            return 0;
        }
        cobj->invalidUpdate();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Bone:invalidUpdate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Bone_invalidUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Bone_getTypeIndex(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccdb.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Bone_getTypeIndex'", nullptr);
            return 0;
        }
        unsigned long ret = dragonBones::Bone::getTypeIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccdb.Bone:getTypeIndex",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Bone_getTypeIndex'.",&tolua_err);
#endif
    return 0;
}
int lua_creator_dragonbones_Bone_constructor(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Bone_constructor'", nullptr);
            return 0;
        }
        cobj = new dragonBones::Bone();
        tolua_pushusertype(tolua_S,(void*)cobj,"ccdb.Bone");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Bone:Bone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Bone_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_creator_dragonbones_Bone_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Bone)");
    return 0;
}

int lua_register_creator_dragonbones_Bone(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.Bone");
    tolua_cclass(tolua_S,"Bone","ccdb.Bone","ccdb.TransformObject",nullptr);

    tolua_beginmodule(tolua_S,"Bone");
        tolua_function(tolua_S,"new",lua_creator_dragonbones_Bone_constructor);
        tolua_function(tolua_S,"getIK",lua_creator_dragonbones_Bone_getIK);
        tolua_function(tolua_S,"getIKChainIndex",lua_creator_dragonbones_Bone_getIKChainIndex);
        tolua_function(tolua_S,"contains",lua_creator_dragonbones_Bone_contains);
        tolua_function(tolua_S,"getIKChain",lua_creator_dragonbones_Bone_getIKChain);
        tolua_function(tolua_S,"getVisible",lua_creator_dragonbones_Bone_getVisible);
        tolua_function(tolua_S,"setVisible",lua_creator_dragonbones_Bone_setVisible);
        tolua_function(tolua_S,"invalidUpdate",lua_creator_dragonbones_Bone_invalidUpdate);
        tolua_function(tolua_S,"getTypeIndex", lua_creator_dragonbones_Bone_getTypeIndex);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::Bone).name();
    g_luaType[typeName] = "ccdb.Bone";
    g_typeCast["Bone"] = "ccdb.Bone";
    return 1;
}

int lua_creator_dragonbones_Slot_getRawDisplay(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Slot* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Slot",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Slot*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Slot_getRawDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Slot_getRawDisplay'", nullptr);
            return 0;
        }
        void* ret = cobj->getRawDisplay();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Slot:getRawDisplay",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Slot_getRawDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Slot_getChildArmature(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Slot* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Slot",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Slot*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Slot_getChildArmature'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Slot_getChildArmature'", nullptr);
            return 0;
        }
        dragonBones::Armature* ret = cobj->getChildArmature();
        object_to_luaval<dragonBones::Armature>(tolua_S, "ccdb.Armature",(dragonBones::Armature*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Slot:getChildArmature",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Slot_getChildArmature'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Slot_getDisplay(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Slot* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Slot",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Slot*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Slot_getDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Slot_getDisplay'", nullptr);
            return 0;
        }
        void* ret = cobj->getDisplay();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Slot:getDisplay",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Slot_getDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Slot_getMeshDisplay(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Slot* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Slot",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Slot*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Slot_getMeshDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Slot_getMeshDisplay'", nullptr);
            return 0;
        }
        void* ret = cobj->getMeshDisplay();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Slot:getMeshDisplay",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Slot_getMeshDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Slot_setDisplay(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Slot* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Slot",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Slot*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Slot_setDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        void* arg0;
        dragonBones::DisplayType arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccdb.Slot:setDisplay");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Slot_setDisplay'", nullptr);
            return 0;
        }
        cobj->setDisplay(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Slot:setDisplay",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Slot_setDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Slot_invalidUpdate(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Slot* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Slot",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Slot*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Slot_invalidUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Slot_invalidUpdate'", nullptr);
            return 0;
        }
        cobj->invalidUpdate();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Slot:invalidUpdate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Slot_invalidUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Slot_setDisplayIndex(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Slot* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Slot",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Slot*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Slot_setDisplayIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccdb.Slot:setDisplayIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Slot_setDisplayIndex'", nullptr);
            return 0;
        }
        cobj->setDisplayIndex(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Slot:setDisplayIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Slot_setDisplayIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Slot_setChildArmature(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Slot* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Slot",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Slot*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Slot_setChildArmature'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        dragonBones::Armature* arg0;

        ok &= luaval_to_object<dragonBones::Armature>(tolua_S, 2, "ccdb.Armature",&arg0, "ccdb.Slot:setChildArmature");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Slot_setChildArmature'", nullptr);
            return 0;
        }
        cobj->setChildArmature(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Slot:setChildArmature",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Slot_setChildArmature'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_Slot_getDisplayIndex(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::Slot* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.Slot",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::Slot*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_Slot_getDisplayIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_Slot_getDisplayIndex'", nullptr);
            return 0;
        }
        int ret = cobj->getDisplayIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.Slot:getDisplayIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_Slot_getDisplayIndex'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_dragonbones_Slot_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Slot)");
    return 0;
}

int lua_register_creator_dragonbones_Slot(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.Slot");
    tolua_cclass(tolua_S,"Slot","ccdb.Slot","ccdb.TransformObject",nullptr);

    tolua_beginmodule(tolua_S,"Slot");
        tolua_function(tolua_S,"getRawDisplay",lua_creator_dragonbones_Slot_getRawDisplay);
        tolua_function(tolua_S,"getChildArmature",lua_creator_dragonbones_Slot_getChildArmature);
        tolua_function(tolua_S,"getDisplay",lua_creator_dragonbones_Slot_getDisplay);
        tolua_function(tolua_S,"getMeshDisplay",lua_creator_dragonbones_Slot_getMeshDisplay);
        tolua_function(tolua_S,"setDisplay",lua_creator_dragonbones_Slot_setDisplay);
        tolua_function(tolua_S,"invalidUpdate",lua_creator_dragonbones_Slot_invalidUpdate);
        tolua_function(tolua_S,"setDisplayIndex",lua_creator_dragonbones_Slot_setDisplayIndex);
        tolua_function(tolua_S,"setChildArmature",lua_creator_dragonbones_Slot_setChildArmature);
        tolua_function(tolua_S,"getDisplayIndex",lua_creator_dragonbones_Slot_getDisplayIndex);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::Slot).name();
    g_luaType[typeName] = "ccdb.Slot";
    g_typeCast["Slot"] = "ccdb.Slot";
    return 1;
}

int lua_creator_dragonbones_BaseFactory_removeDragonBonesData(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::BaseFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.BaseFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::BaseFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_BaseFactory_removeDragonBonesData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.BaseFactory:removeDragonBonesData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_removeDragonBonesData'", nullptr);
            return 0;
        }
        cobj->removeDragonBonesData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.BaseFactory:removeDragonBonesData");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccdb.BaseFactory:removeDragonBonesData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_removeDragonBonesData'", nullptr);
            return 0;
        }
        cobj->removeDragonBonesData(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.BaseFactory:removeDragonBonesData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_BaseFactory_removeDragonBonesData'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_BaseFactory_removeTextureAtlasData(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::BaseFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.BaseFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::BaseFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_BaseFactory_removeTextureAtlasData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.BaseFactory:removeTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_removeTextureAtlasData'", nullptr);
            return 0;
        }
        cobj->removeTextureAtlasData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.BaseFactory:removeTextureAtlasData");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccdb.BaseFactory:removeTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_removeTextureAtlasData'", nullptr);
            return 0;
        }
        cobj->removeTextureAtlasData(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.BaseFactory:removeTextureAtlasData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_BaseFactory_removeTextureAtlasData'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_BaseFactory_parseDragonBonesData(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::BaseFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.BaseFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::BaseFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_BaseFactory_parseDragonBonesData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccdb.BaseFactory:parseDragonBonesData"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_parseDragonBonesData'", nullptr);
            return 0;
        }
        dragonBones::DragonBonesData* ret = cobj->parseDragonBonesData(arg0);
        object_to_luaval<dragonBones::DragonBonesData>(tolua_S, "ccdb.DragonBonesData",(dragonBones::DragonBonesData*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        const char* arg0;
        std::string arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccdb.BaseFactory:parseDragonBonesData"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.BaseFactory:parseDragonBonesData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_parseDragonBonesData'", nullptr);
            return 0;
        }
        dragonBones::DragonBonesData* ret = cobj->parseDragonBonesData(arg0, arg1);
        object_to_luaval<dragonBones::DragonBonesData>(tolua_S, "ccdb.DragonBonesData",(dragonBones::DragonBonesData*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        const char* arg0;
        std::string arg1;
        double arg2;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccdb.BaseFactory:parseDragonBonesData"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.BaseFactory:parseDragonBonesData");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "ccdb.BaseFactory:parseDragonBonesData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_parseDragonBonesData'", nullptr);
            return 0;
        }
        dragonBones::DragonBonesData* ret = cobj->parseDragonBonesData(arg0, arg1, arg2);
        object_to_luaval<dragonBones::DragonBonesData>(tolua_S, "ccdb.DragonBonesData",(dragonBones::DragonBonesData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.BaseFactory:parseDragonBonesData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_BaseFactory_parseDragonBonesData'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_BaseFactory_clear(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::BaseFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.BaseFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::BaseFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_BaseFactory_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccdb.BaseFactory:clear");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_clear'", nullptr);
            return 0;
        }
        cobj->clear(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.BaseFactory:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_BaseFactory_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_BaseFactory_addDragonBonesData(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::BaseFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.BaseFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::BaseFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_BaseFactory_addDragonBonesData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        dragonBones::DragonBonesData* arg0;

        ok &= luaval_to_object<dragonBones::DragonBonesData>(tolua_S, 2, "ccdb.DragonBonesData",&arg0, "ccdb.BaseFactory:addDragonBonesData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_addDragonBonesData'", nullptr);
            return 0;
        }
        cobj->addDragonBonesData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        dragonBones::DragonBonesData* arg0;
        std::string arg1;

        ok &= luaval_to_object<dragonBones::DragonBonesData>(tolua_S, 2, "ccdb.DragonBonesData",&arg0, "ccdb.BaseFactory:addDragonBonesData");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.BaseFactory:addDragonBonesData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_addDragonBonesData'", nullptr);
            return 0;
        }
        cobj->addDragonBonesData(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.BaseFactory:addDragonBonesData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_BaseFactory_addDragonBonesData'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_BaseFactory_buildArmature(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::BaseFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.BaseFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::BaseFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_BaseFactory_buildArmature'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.BaseFactory:buildArmature");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_buildArmature'", nullptr);
            return 0;
        }
        dragonBones::Armature* ret = cobj->buildArmature(arg0);
        object_to_luaval<dragonBones::Armature>(tolua_S, "ccdb.Armature",(dragonBones::Armature*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.BaseFactory:buildArmature");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.BaseFactory:buildArmature");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_buildArmature'", nullptr);
            return 0;
        }
        dragonBones::Armature* ret = cobj->buildArmature(arg0, arg1);
        object_to_luaval<dragonBones::Armature>(tolua_S, "ccdb.Armature",(dragonBones::Armature*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.BaseFactory:buildArmature");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.BaseFactory:buildArmature");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccdb.BaseFactory:buildArmature");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_buildArmature'", nullptr);
            return 0;
        }
        dragonBones::Armature* ret = cobj->buildArmature(arg0, arg1, arg2);
        object_to_luaval<dragonBones::Armature>(tolua_S, "ccdb.Armature",(dragonBones::Armature*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.BaseFactory:buildArmature",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_BaseFactory_buildArmature'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_BaseFactory_addTextureAtlasData(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::BaseFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.BaseFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::BaseFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_BaseFactory_addTextureAtlasData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        dragonBones::TextureAtlasData* arg0;

        ok &= luaval_to_object<dragonBones::TextureAtlasData>(tolua_S, 2, "ccdb.TextureAtlasData",&arg0, "ccdb.BaseFactory:addTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_addTextureAtlasData'", nullptr);
            return 0;
        }
        cobj->addTextureAtlasData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        dragonBones::TextureAtlasData* arg0;
        std::string arg1;

        ok &= luaval_to_object<dragonBones::TextureAtlasData>(tolua_S, 2, "ccdb.TextureAtlasData",&arg0, "ccdb.BaseFactory:addTextureAtlasData");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.BaseFactory:addTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_addTextureAtlasData'", nullptr);
            return 0;
        }
        cobj->addTextureAtlasData(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.BaseFactory:addTextureAtlasData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_BaseFactory_addTextureAtlasData'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_BaseFactory_getDragonBonesData(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::BaseFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.BaseFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::BaseFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_BaseFactory_getDragonBonesData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.BaseFactory:getDragonBonesData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_BaseFactory_getDragonBonesData'", nullptr);
            return 0;
        }
        dragonBones::DragonBonesData* ret = cobj->getDragonBonesData(arg0);
        object_to_luaval<dragonBones::DragonBonesData>(tolua_S, "ccdb.DragonBonesData",(dragonBones::DragonBonesData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.BaseFactory:getDragonBonesData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_BaseFactory_getDragonBonesData'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_dragonbones_BaseFactory_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BaseFactory)");
    return 0;
}

int lua_register_creator_dragonbones_BaseFactory(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.BaseFactory");
    tolua_cclass(tolua_S,"BaseFactory","ccdb.BaseFactory","",nullptr);

    tolua_beginmodule(tolua_S,"BaseFactory");
        tolua_function(tolua_S,"removeDragonBonesData",lua_creator_dragonbones_BaseFactory_removeDragonBonesData);
        tolua_function(tolua_S,"removeTextureAtlasData",lua_creator_dragonbones_BaseFactory_removeTextureAtlasData);
        tolua_function(tolua_S,"parseDragonBonesData",lua_creator_dragonbones_BaseFactory_parseDragonBonesData);
        tolua_function(tolua_S,"clear",lua_creator_dragonbones_BaseFactory_clear);
        tolua_function(tolua_S,"addDragonBonesData",lua_creator_dragonbones_BaseFactory_addDragonBonesData);
        tolua_function(tolua_S,"buildArmature",lua_creator_dragonbones_BaseFactory_buildArmature);
        tolua_function(tolua_S,"addTextureAtlasData",lua_creator_dragonbones_BaseFactory_addTextureAtlasData);
        tolua_function(tolua_S,"getDragonBonesData",lua_creator_dragonbones_BaseFactory_getDragonBonesData);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::BaseFactory).name();
    g_luaType[typeName] = "ccdb.BaseFactory";
    g_typeCast["BaseFactory"] = "ccdb.BaseFactory";
    return 1;
}

int lua_creator_dragonbones_WorldClock_clear(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::WorldClock* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.WorldClock",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::WorldClock*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_WorldClock_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_WorldClock_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.WorldClock:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_WorldClock_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_WorldClock_advanceTime(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::WorldClock* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.WorldClock",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::WorldClock*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_WorldClock_advanceTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccdb.WorldClock:advanceTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_WorldClock_advanceTime'", nullptr);
            return 0;
        }
        cobj->advanceTime(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.WorldClock:advanceTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_WorldClock_advanceTime'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_WorldClock_contains(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::WorldClock* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.WorldClock",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::WorldClock*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_WorldClock_contains'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const dragonBones::IAnimateble* arg0;

        ok &= luaval_to_object<const dragonBones::IAnimateble>(tolua_S, 2, "ccdb.IAnimateble",&arg0, "ccdb.WorldClock:contains");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_WorldClock_contains'", nullptr);
            return 0;
        }
        bool ret = cobj->contains(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.WorldClock:contains",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_WorldClock_contains'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_dragonbones_WorldClock_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (WorldClock)");
    return 0;
}

int lua_register_creator_dragonbones_WorldClock(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.WorldClock");
    tolua_cclass(tolua_S,"WorldClock","ccdb.WorldClock","",nullptr);

    tolua_beginmodule(tolua_S,"WorldClock");
        tolua_function(tolua_S,"clear",lua_creator_dragonbones_WorldClock_clear);
        tolua_function(tolua_S,"advanceTime",lua_creator_dragonbones_WorldClock_advanceTime);
        tolua_function(tolua_S,"contains",lua_creator_dragonbones_WorldClock_contains);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::WorldClock).name();
    g_luaType[typeName] = "ccdb.WorldClock";
    g_typeCast["WorldClock"] = "ccdb.WorldClock";
    return 1;
}

int lua_creator_dragonbones_AnimationState_setCurrentTime(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_setCurrentTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccdb.AnimationState:setCurrentTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_setCurrentTime'", nullptr);
            return 0;
        }
        cobj->setCurrentTime(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:setCurrentTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_setCurrentTime'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_removeBoneMask(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_removeBoneMask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.AnimationState:removeBoneMask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_removeBoneMask'", nullptr);
            return 0;
        }
        cobj->removeBoneMask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.AnimationState:removeBoneMask");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccdb.AnimationState:removeBoneMask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_removeBoneMask'", nullptr);
            return 0;
        }
        cobj->removeBoneMask(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:removeBoneMask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_removeBoneMask'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_getGroup(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_getGroup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_getGroup'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getGroup();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:getGroup",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_getGroup'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_getCurrentPlayTimes(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_getCurrentPlayTimes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_getCurrentPlayTimes'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getCurrentPlayTimes();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:getCurrentPlayTimes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_getCurrentPlayTimes'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_getName(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_getName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_getName'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getName();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:getName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_getName'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_getCurrentTime(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_getCurrentTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_getCurrentTime'", nullptr);
            return 0;
        }
        double ret = cobj->getCurrentTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:getCurrentTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_getCurrentTime'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_getTotalTime(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_getTotalTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_getTotalTime'", nullptr);
            return 0;
        }
        double ret = cobj->getTotalTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:getTotalTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_getTotalTime'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_removeAllBoneMask(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_removeAllBoneMask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_removeAllBoneMask'", nullptr);
            return 0;
        }
        cobj->removeAllBoneMask();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:removeAllBoneMask",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_removeAllBoneMask'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_getLayer(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_getLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_getLayer'", nullptr);
            return 0;
        }
        int ret = cobj->getLayer();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:getLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_getLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_isCompleted(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_isCompleted'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_isCompleted'", nullptr);
            return 0;
        }
        bool ret = cobj->isCompleted();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:isCompleted",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_isCompleted'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_play(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_play'", nullptr);
            return 0;
        }
        cobj->play();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:play",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_play'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_fadeOut(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_fadeOut'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccdb.AnimationState:fadeOut");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_fadeOut'", nullptr);
            return 0;
        }
        cobj->fadeOut(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        double arg0;
        bool arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccdb.AnimationState:fadeOut");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccdb.AnimationState:fadeOut");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_fadeOut'", nullptr);
            return 0;
        }
        cobj->fadeOut(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:fadeOut",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_fadeOut'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_stop(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_isPlaying(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_isPlaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_isPlaying'", nullptr);
            return 0;
        }
        bool ret = cobj->isPlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:isPlaying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_isPlaying'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_addBoneMask(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_addBoneMask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.AnimationState:addBoneMask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_addBoneMask'", nullptr);
            return 0;
        }
        cobj->addBoneMask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.AnimationState:addBoneMask");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccdb.AnimationState:addBoneMask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_addBoneMask'", nullptr);
            return 0;
        }
        cobj->addBoneMask(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:addBoneMask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_addBoneMask'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_containsBoneMask(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::AnimationState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_AnimationState_containsBoneMask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.AnimationState:containsBoneMask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_containsBoneMask'", nullptr);
            return 0;
        }
        bool ret = cobj->containsBoneMask(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:containsBoneMask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_containsBoneMask'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_AnimationState_getTypeIndex(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccdb.AnimationState",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_getTypeIndex'", nullptr);
            return 0;
        }
        unsigned long ret = dragonBones::AnimationState::getTypeIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccdb.AnimationState:getTypeIndex",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_getTypeIndex'.",&tolua_err);
#endif
    return 0;
}
int lua_creator_dragonbones_AnimationState_constructor(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::AnimationState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_AnimationState_constructor'", nullptr);
            return 0;
        }
        cobj = new dragonBones::AnimationState();
        tolua_pushusertype(tolua_S,(void*)cobj,"ccdb.AnimationState");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.AnimationState:AnimationState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_AnimationState_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_creator_dragonbones_AnimationState_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AnimationState)");
    return 0;
}

int lua_register_creator_dragonbones_AnimationState(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.AnimationState");
    tolua_cclass(tolua_S,"AnimationState","ccdb.AnimationState","ccdb.BaseObject",nullptr);

    tolua_beginmodule(tolua_S,"AnimationState");
        tolua_function(tolua_S,"new",lua_creator_dragonbones_AnimationState_constructor);
        tolua_function(tolua_S,"setCurrentTime",lua_creator_dragonbones_AnimationState_setCurrentTime);
        tolua_function(tolua_S,"removeBoneMask",lua_creator_dragonbones_AnimationState_removeBoneMask);
        tolua_function(tolua_S,"getGroup",lua_creator_dragonbones_AnimationState_getGroup);
        tolua_function(tolua_S,"getCurrentPlayTimes",lua_creator_dragonbones_AnimationState_getCurrentPlayTimes);
        tolua_function(tolua_S,"getName",lua_creator_dragonbones_AnimationState_getName);
        tolua_function(tolua_S,"getCurrentTime",lua_creator_dragonbones_AnimationState_getCurrentTime);
        tolua_function(tolua_S,"getTotalTime",lua_creator_dragonbones_AnimationState_getTotalTime);
        tolua_function(tolua_S,"removeAllBoneMask",lua_creator_dragonbones_AnimationState_removeAllBoneMask);
        tolua_function(tolua_S,"getLayer",lua_creator_dragonbones_AnimationState_getLayer);
        tolua_function(tolua_S,"isCompleted",lua_creator_dragonbones_AnimationState_isCompleted);
        tolua_function(tolua_S,"play",lua_creator_dragonbones_AnimationState_play);
        tolua_function(tolua_S,"fadeOut",lua_creator_dragonbones_AnimationState_fadeOut);
        tolua_function(tolua_S,"stop",lua_creator_dragonbones_AnimationState_stop);
        tolua_function(tolua_S,"isPlaying",lua_creator_dragonbones_AnimationState_isPlaying);
        tolua_function(tolua_S,"addBoneMask",lua_creator_dragonbones_AnimationState_addBoneMask);
        tolua_function(tolua_S,"containsBoneMask",lua_creator_dragonbones_AnimationState_containsBoneMask);
        tolua_function(tolua_S,"getTypeIndex", lua_creator_dragonbones_AnimationState_getTypeIndex);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::AnimationState).name();
    g_luaType[typeName] = "ccdb.AnimationState";
    g_typeCast["AnimationState"] = "ccdb.AnimationState";
    return 1;
}

int lua_creator_dragonbones_CCArmatureDisplay_advanceTimeBySelf(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCArmatureDisplay* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCArmatureDisplay",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCArmatureDisplay*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCArmatureDisplay_advanceTimeBySelf'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccdb.CCArmatureDisplay:advanceTimeBySelf");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCArmatureDisplay_advanceTimeBySelf'", nullptr);
            return 0;
        }
        cobj->advanceTimeBySelf(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCArmatureDisplay:advanceTimeBySelf",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCArmatureDisplay_advanceTimeBySelf'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCArmatureDisplay_removeEvent(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCArmatureDisplay* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCArmatureDisplay",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCArmatureDisplay*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCArmatureDisplay_removeEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCArmatureDisplay:removeEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCArmatureDisplay_removeEvent'", nullptr);
            return 0;
        }
        cobj->removeEvent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCArmatureDisplay:removeEvent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCArmatureDisplay_removeEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCArmatureDisplay_getArmature(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCArmatureDisplay* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCArmatureDisplay",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCArmatureDisplay*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCArmatureDisplay_getArmature'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCArmatureDisplay_getArmature'", nullptr);
            return 0;
        }
        dragonBones::Armature* ret = cobj->getArmature();
        object_to_luaval<dragonBones::Armature>(tolua_S, "ccdb.Armature",(dragonBones::Armature*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCArmatureDisplay:getArmature",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCArmatureDisplay_getArmature'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCArmatureDisplay_setEventCallback(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCArmatureDisplay* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCArmatureDisplay",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCArmatureDisplay*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCArmatureDisplay_setEventCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (dragonBones::EventObject *)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCArmatureDisplay_setEventCallback'", nullptr);
            return 0;
        }
        cobj->setEventCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCArmatureDisplay:setEventCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCArmatureDisplay_setEventCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCArmatureDisplay_clearEventCallback(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCArmatureDisplay* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCArmatureDisplay",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCArmatureDisplay*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCArmatureDisplay_clearEventCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCArmatureDisplay_clearEventCallback'", nullptr);
            return 0;
        }
        cobj->clearEventCallback();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCArmatureDisplay:clearEventCallback",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCArmatureDisplay_clearEventCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCArmatureDisplay_hasEvent(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCArmatureDisplay* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCArmatureDisplay",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCArmatureDisplay*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCArmatureDisplay_hasEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCArmatureDisplay:hasEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCArmatureDisplay_hasEvent'", nullptr);
            return 0;
        }
        bool ret = cobj->hasEvent(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCArmatureDisplay:hasEvent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCArmatureDisplay_hasEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCArmatureDisplay_hasEventCallback(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCArmatureDisplay* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCArmatureDisplay",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCArmatureDisplay*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCArmatureDisplay_hasEventCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCArmatureDisplay_hasEventCallback'", nullptr);
            return 0;
        }
        bool ret = cobj->hasEventCallback();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCArmatureDisplay:hasEventCallback",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCArmatureDisplay_hasEventCallback'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_dragonbones_CCArmatureDisplay_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCArmatureDisplay)");
    return 0;
}

int lua_register_creator_dragonbones_CCArmatureDisplay(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.CCArmatureDisplay");
    tolua_cclass(tolua_S,"CCArmatureDisplay","ccdb.CCArmatureDisplay","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"CCArmatureDisplay");
        tolua_function(tolua_S,"advanceTimeBySelf",lua_creator_dragonbones_CCArmatureDisplay_advanceTimeBySelf);
        tolua_function(tolua_S,"removeEvent",lua_creator_dragonbones_CCArmatureDisplay_removeEvent);
        tolua_function(tolua_S,"getArmature",lua_creator_dragonbones_CCArmatureDisplay_getArmature);
        tolua_function(tolua_S,"setEventCallback",lua_creator_dragonbones_CCArmatureDisplay_setEventCallback);
        tolua_function(tolua_S,"clearEventCallback",lua_creator_dragonbones_CCArmatureDisplay_clearEventCallback);
        tolua_function(tolua_S,"hasEvent",lua_creator_dragonbones_CCArmatureDisplay_hasEvent);
        tolua_function(tolua_S,"hasEventCallback",lua_creator_dragonbones_CCArmatureDisplay_hasEventCallback);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::CCArmatureDisplay).name();
    g_luaType[typeName] = "ccdb.CCArmatureDisplay";
    g_typeCast["CCArmatureDisplay"] = "ccdb.CCArmatureDisplay";
    return 1;
}

int lua_creator_dragonbones_CCFactory_getTextureDisplay(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCFactory_getTextureDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:getTextureDisplay");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_getTextureDisplay'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = cobj->getTextureDisplay(arg0);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:getTextureDisplay");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.CCFactory:getTextureDisplay");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_getTextureDisplay'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = cobj->getTextureDisplay(arg0, arg1);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCFactory:getTextureDisplay",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCFactory_getTextureDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCFactory_getSoundEventManater(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCFactory_getSoundEventManater'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_getSoundEventManater'", nullptr);
            return 0;
        }
        dragonBones::CCArmatureDisplay* ret = cobj->getSoundEventManater();
        object_to_luaval<dragonBones::CCArmatureDisplay>(tolua_S, "ccdb.CCArmatureDisplay",(dragonBones::CCArmatureDisplay*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCFactory:getSoundEventManater",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCFactory_getSoundEventManater'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCFactory_buildArmatureDisplay(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCFactory_buildArmatureDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:buildArmatureDisplay");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_buildArmatureDisplay'", nullptr);
            return 0;
        }
        dragonBones::CCArmatureDisplay* ret = cobj->buildArmatureDisplay(arg0);
        object_to_luaval<dragonBones::CCArmatureDisplay>(tolua_S, "ccdb.CCArmatureDisplay",(dragonBones::CCArmatureDisplay*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:buildArmatureDisplay");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.CCFactory:buildArmatureDisplay");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_buildArmatureDisplay'", nullptr);
            return 0;
        }
        dragonBones::CCArmatureDisplay* ret = cobj->buildArmatureDisplay(arg0, arg1);
        object_to_luaval<dragonBones::CCArmatureDisplay>(tolua_S, "ccdb.CCArmatureDisplay",(dragonBones::CCArmatureDisplay*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:buildArmatureDisplay");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.CCFactory:buildArmatureDisplay");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccdb.CCFactory:buildArmatureDisplay");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_buildArmatureDisplay'", nullptr);
            return 0;
        }
        dragonBones::CCArmatureDisplay* ret = cobj->buildArmatureDisplay(arg0, arg1, arg2);
        object_to_luaval<dragonBones::CCArmatureDisplay>(tolua_S, "ccdb.CCArmatureDisplay",(dragonBones::CCArmatureDisplay*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCFactory:buildArmatureDisplay",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCFactory_buildArmatureDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCFactory_loadTextureAtlasData(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCFactory_loadTextureAtlasData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:loadTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_loadTextureAtlasData'", nullptr);
            return 0;
        }
        dragonBones::TextureAtlasData* ret = cobj->loadTextureAtlasData(arg0);
        object_to_luaval<dragonBones::TextureAtlasData>(tolua_S, "ccdb.TextureAtlasData",(dragonBones::TextureAtlasData*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:loadTextureAtlasData");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.CCFactory:loadTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_loadTextureAtlasData'", nullptr);
            return 0;
        }
        dragonBones::TextureAtlasData* ret = cobj->loadTextureAtlasData(arg0, arg1);
        object_to_luaval<dragonBones::TextureAtlasData>(tolua_S, "ccdb.TextureAtlasData",(dragonBones::TextureAtlasData*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        double arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:loadTextureAtlasData");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.CCFactory:loadTextureAtlasData");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "ccdb.CCFactory:loadTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_loadTextureAtlasData'", nullptr);
            return 0;
        }
        dragonBones::TextureAtlasData* ret = cobj->loadTextureAtlasData(arg0, arg1, arg2);
        object_to_luaval<dragonBones::TextureAtlasData>(tolua_S, "ccdb.TextureAtlasData",(dragonBones::TextureAtlasData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCFactory:loadTextureAtlasData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCFactory_loadTextureAtlasData'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCFactory_parseTextureAtlasData(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCFactory_parseTextureAtlasData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:parseTextureAtlasData");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.CCFactory:parseTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_parseTextureAtlasData'", nullptr);
            return 0;
        }
        dragonBones::TextureAtlasData* ret = cobj->parseTextureAtlasData(arg0, arg1);
        object_to_luaval<dragonBones::TextureAtlasData>(tolua_S, "ccdb.TextureAtlasData",(dragonBones::TextureAtlasData*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:parseTextureAtlasData");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.CCFactory:parseTextureAtlasData");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccdb.CCFactory:parseTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_parseTextureAtlasData'", nullptr);
            return 0;
        }
        dragonBones::TextureAtlasData* ret = cobj->parseTextureAtlasData(arg0, arg1, arg2);
        object_to_luaval<dragonBones::TextureAtlasData>(tolua_S, "ccdb.TextureAtlasData",(dragonBones::TextureAtlasData*)ret);
        return 1;
    }
    if (argc == 4) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        double arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:parseTextureAtlasData");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.CCFactory:parseTextureAtlasData");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccdb.CCFactory:parseTextureAtlasData");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "ccdb.CCFactory:parseTextureAtlasData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_parseTextureAtlasData'", nullptr);
            return 0;
        }
        dragonBones::TextureAtlasData* ret = cobj->parseTextureAtlasData(arg0, arg1, arg2, arg3);
        object_to_luaval<dragonBones::TextureAtlasData>(tolua_S, "ccdb.TextureAtlasData",(dragonBones::TextureAtlasData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCFactory:parseTextureAtlasData",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCFactory_parseTextureAtlasData'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCFactory_loadDragonBonesData(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccdb.CCFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (dragonBones::CCFactory*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_dragonbones_CCFactory_loadDragonBonesData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:loadDragonBonesData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_loadDragonBonesData'", nullptr);
            return 0;
        }
        dragonBones::DragonBonesData* ret = cobj->loadDragonBonesData(arg0);
        object_to_luaval<dragonBones::DragonBonesData>(tolua_S, "ccdb.DragonBonesData",(dragonBones::DragonBonesData*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccdb.CCFactory:loadDragonBonesData");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccdb.CCFactory:loadDragonBonesData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_loadDragonBonesData'", nullptr);
            return 0;
        }
        dragonBones::DragonBonesData* ret = cobj->loadDragonBonesData(arg0, arg1);
        object_to_luaval<dragonBones::DragonBonesData>(tolua_S, "ccdb.DragonBonesData",(dragonBones::DragonBonesData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCFactory:loadDragonBonesData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCFactory_loadDragonBonesData'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_dragonbones_CCFactory_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccdb.CCFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_destroyInstance'", nullptr);
            return 0;
        }
        dragonBones::CCFactory::destroyInstance();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccdb.CCFactory:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCFactory_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_creator_dragonbones_CCFactory_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccdb.CCFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_getInstance'", nullptr);
            return 0;
        }
        dragonBones::CCFactory* ret = dragonBones::CCFactory::getInstance();
        object_to_luaval<dragonBones::CCFactory>(tolua_S, "ccdb.CCFactory",(dragonBones::CCFactory*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccdb.CCFactory:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCFactory_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_creator_dragonbones_CCFactory_constructor(lua_State* tolua_S)
{
    int argc = 0;
    dragonBones::CCFactory* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_dragonbones_CCFactory_constructor'", nullptr);
            return 0;
        }
        cobj = new dragonBones::CCFactory();
        tolua_pushusertype(tolua_S,(void*)cobj,"ccdb.CCFactory");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.CCFactory:CCFactory",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_creator_dragonbones_CCFactory_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_creator_dragonbones_CCFactory_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCFactory)");
    return 0;
}

int lua_register_creator_dragonbones_CCFactory(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccdb.CCFactory");
    tolua_cclass(tolua_S,"CCFactory","ccdb.CCFactory","ccdb.BaseFactory",nullptr);

    tolua_beginmodule(tolua_S,"CCFactory");
        tolua_function(tolua_S,"new",lua_creator_dragonbones_CCFactory_constructor);
        tolua_function(tolua_S,"getTextureDisplay",lua_creator_dragonbones_CCFactory_getTextureDisplay);
        tolua_function(tolua_S,"getSoundEventManater",lua_creator_dragonbones_CCFactory_getSoundEventManater);
        tolua_function(tolua_S,"buildArmatureDisplay",lua_creator_dragonbones_CCFactory_buildArmatureDisplay);
        tolua_function(tolua_S,"loadTextureAtlasData",lua_creator_dragonbones_CCFactory_loadTextureAtlasData);
        tolua_function(tolua_S,"parseTextureAtlasData",lua_creator_dragonbones_CCFactory_parseTextureAtlasData);
        tolua_function(tolua_S,"loadDragonBonesData",lua_creator_dragonbones_CCFactory_loadDragonBonesData);
        tolua_function(tolua_S,"destroyInstance", lua_creator_dragonbones_CCFactory_destroyInstance);
        tolua_function(tolua_S,"getInstance", lua_creator_dragonbones_CCFactory_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(dragonBones::CCFactory).name();
    g_luaType[typeName] = "ccdb.CCFactory";
    g_typeCast["CCFactory"] = "ccdb.CCFactory";
    return 1;
}
TOLUA_API int register_all_creator_dragonbones(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccdb",0);
	tolua_beginmodule(tolua_S,"ccdb");

	lua_register_creator_dragonbones_Slot(tolua_S);
	lua_register_creator_dragonbones_CCArmatureDisplay(tolua_S);
	lua_register_creator_dragonbones_Transform(tolua_S);
	lua_register_creator_dragonbones_EventObject(tolua_S);
	lua_register_creator_dragonbones_AnimationState(tolua_S);
	lua_register_creator_dragonbones_BaseFactory(tolua_S);
	lua_register_creator_dragonbones_Animation(tolua_S);
	lua_register_creator_dragonbones_CCFactory(tolua_S);
	lua_register_creator_dragonbones_Armature(tolua_S);
	lua_register_creator_dragonbones_WorldClock(tolua_S);
	lua_register_creator_dragonbones_Bone(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

