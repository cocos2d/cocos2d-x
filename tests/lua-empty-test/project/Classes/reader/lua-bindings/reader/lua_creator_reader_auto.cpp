#include "lua-bindings/reader/lua_creator_reader_auto.hpp"
#include "CreatorReader.h"
#include "Collider.h"
#include "Contract.h"
#include "ColliderManager.h"
#include "AnimationManager.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_creator_reader_AnimationManager_pauseAnimationClip(lua_State* tolua_S)
{
    int argc = 0;
    creator::AnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.AnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::AnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_AnimationManager_pauseAnimationClip'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "creator.AnimationManager:pauseAnimationClip");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "creator.AnimationManager:pauseAnimationClip");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_AnimationManager_pauseAnimationClip'", nullptr);
            return 0;
        }
        cobj->pauseAnimationClip(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.AnimationManager:pauseAnimationClip",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_AnimationManager_pauseAnimationClip'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_AnimationManager_stopAnimationClip(lua_State* tolua_S)
{
    int argc = 0;
    creator::AnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.AnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::AnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_AnimationManager_stopAnimationClip'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "creator.AnimationManager:stopAnimationClip");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "creator.AnimationManager:stopAnimationClip");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_AnimationManager_stopAnimationClip'", nullptr);
            return 0;
        }
        cobj->stopAnimationClip(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.AnimationManager:stopAnimationClip",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_AnimationManager_stopAnimationClip'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_AnimationManager_playAnimationClip(lua_State* tolua_S)
{
    int argc = 0;
    creator::AnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.AnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::AnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_AnimationManager_playAnimationClip'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "creator.AnimationManager:playAnimationClip");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "creator.AnimationManager:playAnimationClip");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_AnimationManager_playAnimationClip'", nullptr);
            return 0;
        }
        cobj->playAnimationClip(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.AnimationManager:playAnimationClip",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_AnimationManager_playAnimationClip'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_AnimationManager_resumeAnimationClip(lua_State* tolua_S)
{
    int argc = 0;
    creator::AnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.AnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::AnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_AnimationManager_resumeAnimationClip'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "creator.AnimationManager:resumeAnimationClip");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "creator.AnimationManager:resumeAnimationClip");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_AnimationManager_resumeAnimationClip'", nullptr);
            return 0;
        }
        cobj->resumeAnimationClip(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.AnimationManager:resumeAnimationClip",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_AnimationManager_resumeAnimationClip'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_reader_AnimationManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AnimationManager)");
    return 0;
}

int lua_register_creator_reader_AnimationManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"creator.AnimationManager");
    tolua_cclass(tolua_S,"AnimationManager","creator.AnimationManager","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"AnimationManager");
        tolua_function(tolua_S,"pauseAnimationClip",lua_creator_reader_AnimationManager_pauseAnimationClip);
        tolua_function(tolua_S,"stopAnimationClip",lua_creator_reader_AnimationManager_stopAnimationClip);
        tolua_function(tolua_S,"playAnimationClip",lua_creator_reader_AnimationManager_playAnimationClip);
        tolua_function(tolua_S,"resumeAnimationClip",lua_creator_reader_AnimationManager_resumeAnimationClip);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(creator::AnimationManager).name();
    g_luaType[typeName] = "creator.AnimationManager";
    g_typeCast["AnimationManager"] = "creator.AnimationManager";
    return 1;
}

int lua_creator_reader_Collider_getTarget(lua_State* tolua_S)
{
    int argc = 0;
    creator::Collider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.Collider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::Collider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_Collider_getTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_Collider_getTarget'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getTarget();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.Collider:getTarget",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_Collider_getTarget'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_Collider_getAABB(lua_State* tolua_S)
{
    int argc = 0;
    creator::Collider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.Collider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::Collider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_Collider_getAABB'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_Collider_getAABB'", nullptr);
            return 0;
        }
        const cocos2d::Rect& ret = cobj->getAABB();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.Collider:getAABB",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_Collider_getAABB'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_reader_Collider_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Collider)");
    return 0;
}

int lua_register_creator_reader_Collider(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"creator.Collider");
    tolua_cclass(tolua_S,"Collider","creator.Collider","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Collider");
        tolua_function(tolua_S,"getTarget",lua_creator_reader_Collider_getTarget);
        tolua_function(tolua_S,"getAABB",lua_creator_reader_Collider_getAABB);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(creator::Collider).name();
    g_luaType[typeName] = "creator.Collider";
    g_typeCast["Collider"] = "creator.Collider";
    return 1;
}

int lua_creator_reader_CircleCollider_getRadius(lua_State* tolua_S)
{
    int argc = 0;
    creator::CircleCollider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.CircleCollider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::CircleCollider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_CircleCollider_getRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_CircleCollider_getRadius'", nullptr);
            return 0;
        }
        double ret = cobj->getRadius();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.CircleCollider:getRadius",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_CircleCollider_getRadius'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_reader_CircleCollider_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CircleCollider)");
    return 0;
}

int lua_register_creator_reader_CircleCollider(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"creator.CircleCollider");
    tolua_cclass(tolua_S,"CircleCollider","creator.CircleCollider","creator.Collider",nullptr);

    tolua_beginmodule(tolua_S,"CircleCollider");
        tolua_function(tolua_S,"getRadius",lua_creator_reader_CircleCollider_getRadius);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(creator::CircleCollider).name();
    g_luaType[typeName] = "creator.CircleCollider";
    g_typeCast["CircleCollider"] = "creator.CircleCollider";
    return 1;
}

int lua_creator_reader_BoxCollider_getSize(lua_State* tolua_S)
{
    int argc = 0;
    creator::BoxCollider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.BoxCollider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::BoxCollider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_BoxCollider_getSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_BoxCollider_getSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.BoxCollider:getSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_BoxCollider_getSize'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_reader_BoxCollider_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BoxCollider)");
    return 0;
}

int lua_register_creator_reader_BoxCollider(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"creator.BoxCollider");
    tolua_cclass(tolua_S,"BoxCollider","creator.BoxCollider","creator.Collider",nullptr);

    tolua_beginmodule(tolua_S,"BoxCollider");
        tolua_function(tolua_S,"getSize",lua_creator_reader_BoxCollider_getSize);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(creator::BoxCollider).name();
    g_luaType[typeName] = "creator.BoxCollider";
    g_typeCast["BoxCollider"] = "creator.BoxCollider";
    return 1;
}

static int lua_creator_reader_PolygonCollider_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PolygonCollider)");
    return 0;
}

int lua_register_creator_reader_PolygonCollider(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"creator.PolygonCollider");
    tolua_cclass(tolua_S,"PolygonCollider","creator.PolygonCollider","creator.Collider",nullptr);

    tolua_beginmodule(tolua_S,"PolygonCollider");
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(creator::PolygonCollider).name();
    g_luaType[typeName] = "creator.PolygonCollider";
    g_typeCast["PolygonCollider"] = "creator.PolygonCollider";
    return 1;
}

int lua_creator_reader_Contract_getCollider1(lua_State* tolua_S)
{
    int argc = 0;
    creator::Contract* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.Contract",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::Contract*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_Contract_getCollider1'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_Contract_getCollider1'", nullptr);
            return 0;
        }
        creator::Collider* ret = cobj->getCollider1();
        object_to_luaval<creator::Collider>(tolua_S, "creator.Collider",(creator::Collider*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.Contract:getCollider1",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_Contract_getCollider1'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_Contract_getCollider2(lua_State* tolua_S)
{
    int argc = 0;
    creator::Contract* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.Contract",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::Contract*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_Contract_getCollider2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_Contract_getCollider2'", nullptr);
            return 0;
        }
        creator::Collider* ret = cobj->getCollider2();
        object_to_luaval<creator::Collider>(tolua_S, "creator.Collider",(creator::Collider*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.Contract:getCollider2",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_Contract_getCollider2'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_reader_Contract_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Contract)");
    return 0;
}

int lua_register_creator_reader_Contract(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"creator.Contract");
    tolua_cclass(tolua_S,"Contract","creator.Contract","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Contract");
        tolua_function(tolua_S,"getCollider1",lua_creator_reader_Contract_getCollider1);
        tolua_function(tolua_S,"getCollider2",lua_creator_reader_Contract_getCollider2);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(creator::Contract).name();
    g_luaType[typeName] = "creator.Contract";
    g_typeCast["Contract"] = "creator.Contract";
    return 1;
}

int lua_creator_reader_ColliderManager_isDebugDrawEnabled(lua_State* tolua_S)
{
    int argc = 0;
    creator::ColliderManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.ColliderManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::ColliderManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_ColliderManager_isDebugDrawEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_ColliderManager_isDebugDrawEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isDebugDrawEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.ColliderManager:isDebugDrawEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_ColliderManager_isDebugDrawEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_ColliderManager_enableDebugDraw(lua_State* tolua_S)
{
    int argc = 0;
    creator::ColliderManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.ColliderManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::ColliderManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_ColliderManager_enableDebugDraw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "creator.ColliderManager:enableDebugDraw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_ColliderManager_enableDebugDraw'", nullptr);
            return 0;
        }
        cobj->enableDebugDraw(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.ColliderManager:enableDebugDraw",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_ColliderManager_enableDebugDraw'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_ColliderManager_enableAABBDebugDraw(lua_State* tolua_S)
{
    int argc = 0;
    creator::ColliderManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.ColliderManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::ColliderManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_ColliderManager_enableAABBDebugDraw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "creator.ColliderManager:enableAABBDebugDraw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_ColliderManager_enableAABBDebugDraw'", nullptr);
            return 0;
        }
        cobj->enableAABBDebugDraw(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.ColliderManager:enableAABBDebugDraw",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_ColliderManager_enableAABBDebugDraw'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_ColliderManager_removeCollider(lua_State* tolua_S)
{
    int argc = 0;
    creator::ColliderManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.ColliderManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::ColliderManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_ColliderManager_removeCollider'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        creator::Collider* arg0;

        ok &= luaval_to_object<creator::Collider>(tolua_S, 2, "creator.Collider",&arg0, "creator.ColliderManager:removeCollider");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_ColliderManager_removeCollider'", nullptr);
            return 0;
        }
        cobj->removeCollider(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.ColliderManager:removeCollider",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_ColliderManager_removeCollider'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_ColliderManager_isAABBDebugDrawEnabled(lua_State* tolua_S)
{
    int argc = 0;
    creator::ColliderManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.ColliderManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::ColliderManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_ColliderManager_isAABBDebugDrawEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_ColliderManager_isAABBDebugDrawEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isAABBDebugDrawEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.ColliderManager:isAABBDebugDrawEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_ColliderManager_isAABBDebugDrawEnabled'.",&tolua_err);
#endif

    return 0;
}
static int lua_creator_reader_ColliderManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ColliderManager)");
    return 0;
}

int lua_register_creator_reader_ColliderManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"creator.ColliderManager");
    tolua_cclass(tolua_S,"ColliderManager","creator.ColliderManager","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"ColliderManager");
        tolua_function(tolua_S,"isDebugDrawEnabled",lua_creator_reader_ColliderManager_isDebugDrawEnabled);
        tolua_function(tolua_S,"enableDebugDraw",lua_creator_reader_ColliderManager_enableDebugDraw);
        tolua_function(tolua_S,"enableAABBDebugDraw",lua_creator_reader_ColliderManager_enableAABBDebugDraw);
        tolua_function(tolua_S,"removeCollider",lua_creator_reader_ColliderManager_removeCollider);
        tolua_function(tolua_S,"isAABBDebugDrawEnabled",lua_creator_reader_ColliderManager_isAABBDebugDrawEnabled);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(creator::ColliderManager).name();
    g_luaType[typeName] = "creator.ColliderManager";
    g_typeCast["ColliderManager"] = "creator.ColliderManager";
    return 1;
}

int lua_creator_reader_CreatorReader_getAnimationManager(lua_State* tolua_S)
{
    int argc = 0;
    creator::CreatorReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.CreatorReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::CreatorReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_CreatorReader_getAnimationManager'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_CreatorReader_getAnimationManager'", nullptr);
            return 0;
        }
        creator::AnimationManager* ret = cobj->getAnimationManager();
        object_to_luaval<creator::AnimationManager>(tolua_S, "creator.AnimationManager",(creator::AnimationManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.CreatorReader:getAnimationManager",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_CreatorReader_getAnimationManager'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_CreatorReader_setup(lua_State* tolua_S)
{
    int argc = 0;
    creator::CreatorReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.CreatorReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::CreatorReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_CreatorReader_setup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_CreatorReader_setup'", nullptr);
            return 0;
        }
        cobj->setup();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.CreatorReader:setup",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_CreatorReader_setup'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_CreatorReader_getVersion(lua_State* tolua_S)
{
    int argc = 0;
    creator::CreatorReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.CreatorReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::CreatorReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_CreatorReader_getVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_CreatorReader_getVersion'", nullptr);
            return 0;
        }
        std::string ret = cobj->getVersion();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.CreatorReader:getVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_CreatorReader_getVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_CreatorReader_getSceneGraph(lua_State* tolua_S)
{
    int argc = 0;
    creator::CreatorReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.CreatorReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::CreatorReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_CreatorReader_getSceneGraph'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_CreatorReader_getSceneGraph'", nullptr);
            return 0;
        }
        cocos2d::Scene* ret = cobj->getSceneGraph();
        object_to_luaval<cocos2d::Scene>(tolua_S, "cc.Scene",(cocos2d::Scene*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.CreatorReader:getSceneGraph",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_CreatorReader_getSceneGraph'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_CreatorReader_getColliderManager(lua_State* tolua_S)
{
    int argc = 0;
    creator::CreatorReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"creator.CreatorReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (creator::CreatorReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_creator_reader_CreatorReader_getColliderManager'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_CreatorReader_getColliderManager'", nullptr);
            return 0;
        }
        creator::ColliderManager* ret = cobj->getColliderManager();
        object_to_luaval<creator::ColliderManager>(tolua_S, "creator.ColliderManager",(creator::ColliderManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "creator.CreatorReader:getColliderManager",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_CreatorReader_getColliderManager'.",&tolua_err);
#endif

    return 0;
}
int lua_creator_reader_CreatorReader_createWithFilename(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"creator.CreatorReader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "creator.CreatorReader:createWithFilename");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_creator_reader_CreatorReader_createWithFilename'", nullptr);
            return 0;
        }
        creator::CreatorReader* ret = creator::CreatorReader::createWithFilename(arg0);
        object_to_luaval<creator::CreatorReader>(tolua_S, "creator.CreatorReader",(creator::CreatorReader*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "creator.CreatorReader:createWithFilename",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_creator_reader_CreatorReader_createWithFilename'.",&tolua_err);
#endif
    return 0;
}
static int lua_creator_reader_CreatorReader_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CreatorReader)");
    return 0;
}

int lua_register_creator_reader_CreatorReader(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"creator.CreatorReader");
    tolua_cclass(tolua_S,"CreatorReader","creator.CreatorReader","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"CreatorReader");
        tolua_function(tolua_S,"getAnimationManager",lua_creator_reader_CreatorReader_getAnimationManager);
        tolua_function(tolua_S,"setup",lua_creator_reader_CreatorReader_setup);
        tolua_function(tolua_S,"getVersion",lua_creator_reader_CreatorReader_getVersion);
        tolua_function(tolua_S,"getSceneGraph",lua_creator_reader_CreatorReader_getSceneGraph);
        tolua_function(tolua_S,"getColliderManager",lua_creator_reader_CreatorReader_getColliderManager);
        tolua_function(tolua_S,"createWithFilename", lua_creator_reader_CreatorReader_createWithFilename);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(creator::CreatorReader).name();
    g_luaType[typeName] = "creator.CreatorReader";
    g_typeCast["CreatorReader"] = "creator.CreatorReader";
    return 1;
}
TOLUA_API int register_all_creator_reader(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"creator",0);
	tolua_beginmodule(tolua_S,"creator");

	lua_register_creator_reader_Collider(tolua_S);
	lua_register_creator_reader_ColliderManager(tolua_S);
	lua_register_creator_reader_BoxCollider(tolua_S);
	lua_register_creator_reader_CreatorReader(tolua_S);
	lua_register_creator_reader_Contract(tolua_S);
	lua_register_creator_reader_AnimationManager(tolua_S);
	lua_register_creator_reader_PolygonCollider(tolua_S);
	lua_register_creator_reader_CircleCollider(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

