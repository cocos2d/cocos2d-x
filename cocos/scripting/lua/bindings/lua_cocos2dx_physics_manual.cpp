#include "lua_cocos2dx_manual.hpp"

#if CC_USE_PHYSICS

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"

int lua_cocos2dx_physics_PhysicsBody_getJoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getJoints'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        do {
            
            if(!ok)
                return 0;
            auto& ret = cobj->getJoints();
            
            lua_newtable(tolua_S);
            
            if (ret.empty())
                return 1;
            
            auto iter = ret.begin();
            int  indexTable = 1;
            for (; iter != ret.end(); ++iter)
            {
                if (nullptr == *iter)
                    continue;
                
				std::string hashName = typeid(*iter).name();
				auto name = g_luaType.find(hashName);
				std::string className = "";
				if(name != g_luaType.end()){
					className = name->second.c_str();
				} else {
					className = "PhysicsJoint";
				}
                
                lua_pushnumber(tolua_S, (lua_Number)indexTable);
                tolua_pushusertype(tolua_S,(void*)(*iter), className.c_str());
                lua_rawset(tolua_S, -3);
                ++indexTable;
            }
		} while (0);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getJoints",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getJoints'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_physics_PhysicsWorld_getScene(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getScene'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::Scene& ret = cobj->getScene();
        do {
            
            std::string hashName = typeid(ret).name();
            auto iter = g_luaType.find(hashName);
            std::string className = "";
            if(iter != g_luaType.end()){
                className = iter->second.c_str();
            } else {
                className = "Scene";
            }
            
            int ID =  (int)(ret._ID);
            int* luaID = &(ret._luaID);
            toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)(&ret),className.c_str());
            
        }while (0);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getScene",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getScene'.",&tolua_err);
#endif
    
    return 0;
}


int lua_cocos2dx_physics_PhysicsWorld_rayCast(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_rayCast'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 4)
    {
        std::function<bool (cocos2d::PhysicsWorld &, const cocos2d::PhysicsRayCastInfo &, void *)> arg0;
        cocos2d::Point arg1;
        cocos2d::Point arg2;
        do {
            arg0 = [tolua_S](cocos2d::PhysicsWorld &world, const cocos2d::PhysicsRayCastInfo &info, void * data) -> bool
            {
                LuaStack* stack = LuaStack::create();
                std::string hashName = typeid(&world).name();
                auto iter = g_luaType.find(hashName);
                std::string className = "";
                if(iter != g_luaType.end()){
                    className = iter->second.c_str();
                } else {
                    className = "PhysicsWorld";
                }
                
                tolua_pushusertype(tolua_S, (void*)(&world), className.c_str());
                tolua_pushusertype(tolua_S, (void*)(&info), "PhysicsRayCastInfo");
                bool ret = stack->executeFunction(2);
                stack->clean();
                return ret;
            };
		} while(0)
            ;
        ok &= luaval_to_point(tolua_S, 3, &arg1);
        ok &= luaval_to_point(tolua_S, 4, &arg2);
#pragma warning NO CONVERSION TO NATIVE FOR void*;
        if(!ok)
            return 0;
        cobj->rayCast(arg0, arg1, arg2, nullptr);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "rayCast",argc, 4);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_rayCast'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_queryRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_queryRect'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        std::function<bool (cocos2d::PhysicsWorld &, cocos2d::PhysicsShape &, void *)> arg0;
        cocos2d::Rect arg1;
        do {
            arg0 = [tolua_S](cocos2d::PhysicsWorld &world, cocos2d::PhysicsShape &shape, void * data) -> bool
            {
                LuaStack* stack = LuaStack::create();
                std::string hashName = typeid(&world).name();
                auto iter = g_luaType.find(hashName);
                std::string className = "";
                if(iter != g_luaType.end()){
                    className = iter->second.c_str();
                } else {
                    className = "PhysicsWorld";
                }
                
                tolua_pushusertype(tolua_S, (void*)(&world), className.c_str());
                stack->pushObject(&shape, "PhysicsShape");
                bool ret = stack->executeFunction(2);
                stack->clean();
                return ret;
            };
		} while(0);
        
        ok &= luaval_to_rect(tolua_S, 3, &arg1);
#pragma warning NO CONVERSION TO NATIVE FOR void*;
        if(!ok)
            return 0;
        cobj->queryRect(arg0, arg1, nullptr);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "queryRect",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_queryRect'.",&tolua_err);
#endif
    
    return 0;
}


int lua_cocos2dx_physics_PhysicsWorld_queryPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_queryPoint'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        std::function<bool (cocos2d::PhysicsWorld &, cocos2d::PhysicsShape &, void *)> arg0;
        cocos2d::Point arg1;
        do {
            arg0 = [tolua_S](cocos2d::PhysicsWorld &world, cocos2d::PhysicsShape &shape, void * data) -> bool
            {
                LuaStack* stack = LuaStack::create();
                std::string hashName = typeid(&world).name();
                auto iter = g_luaType.find(hashName);
                std::string className = "";
                if(iter != g_luaType.end()){
                    className = iter->second.c_str();
                } else {
                    className = "PhysicsWorld";
                }
                
                tolua_pushusertype(tolua_S, (void*)(&world), className.c_str());
                stack->pushObject(&shape, "PhysicsShape");
                bool ret = stack->executeFunction(2);
                stack->clean();
                return ret;
            };
			assert(false);
		} while(0)
            ;
        ok &= luaval_to_point(tolua_S, 3, &arg1);
#pragma warning NO CONVERSION TO NATIVE FOR void*;
        if(!ok)
            return 0;
        cobj->queryPoint(arg0, arg1, nullptr);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "queryPoint",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_queryPoint'.",&tolua_err);
#endif
    
    return 0;
}

int register_all_cocos2dx_physics_manual(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "PhysicsBody");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getJoints");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsBody_getJoints );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    
    lua_pushstring(tolua_S, "PhysicsWorld");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getScene");
        lua_pushcfunction(tolua_S, lua_cocos2dx_physics_PhysicsWorld_getScene );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"queryPoint");
        lua_pushcfunction(tolua_S, lua_cocos2dx_physics_PhysicsWorld_queryPoint );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"queryRect");
        lua_pushcfunction(tolua_S, lua_cocos2dx_physics_PhysicsWorld_queryRect );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"rayCast");
        lua_pushcfunction(tolua_S, lua_cocos2dx_physics_PhysicsWorld_rayCast );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    return 0;
}

#endif