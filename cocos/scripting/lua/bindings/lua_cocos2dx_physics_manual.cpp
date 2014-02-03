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

#ifndef CC_SAFE_FREE
#define CC_SAFE_FREE(p) { if(p) free(p); p = nullptr; }
#endif

int lua_cocos2dx_physics_PhysicsBody_getJoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
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
					className = "cc.PhysicsJoint";
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
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
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
                className = "cc.Scene";
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
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
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
    if (argc == 3)
    {
        std::function<bool (cocos2d::PhysicsWorld &, const cocos2d::PhysicsRayCastInfo &, void *)> arg0;
        cocos2d::Point arg1;
        cocos2d::Point arg2;
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        do {
            arg0 = [handler, tolua_S](cocos2d::PhysicsWorld &world, const cocos2d::PhysicsRayCastInfo &info, void * data) -> bool
            {
                std::string hashName = typeid(&world).name();
                auto iter = g_luaType.find(hashName);
                std::string className = "";
                if(iter != g_luaType.end()){
                    className = iter->second.c_str();
                } else {
                    className = "cc.PhysicsWorld";
                }
                
                tolua_pushusertype(tolua_S, (void*)(&world), className.c_str());
                physics_raycastinfo_to_luaval(tolua_S, info);
                return LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
            };
		} while(0);
        
        ok &= luaval_to_point(tolua_S, 3, &arg1);
        ok &= luaval_to_point(tolua_S, 4, &arg2);
        if(!ok)
            return 0;
        cobj->rayCast(arg0, arg1, arg2, nullptr);
        toluafix_remove_function_by_refid(tolua_S, handler);
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
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
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
    if (argc == 2)
    {
        std::function<bool (cocos2d::PhysicsWorld &, cocos2d::PhysicsShape &, void *)> arg0;
        cocos2d::Rect arg1;
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        do {
            arg0 = [handler, tolua_S](cocos2d::PhysicsWorld &world, cocos2d::PhysicsShape &shape, void * data) -> bool
            {
                std::string hashName = typeid(&world).name();
                auto iter = g_luaType.find(hashName);
                std::string className = "";
                if(iter != g_luaType.end()){
                    className = iter->second.c_str();
                } else {
                    className = "cc.PhysicsWorld";
                }
                
                tolua_pushusertype(tolua_S, (void*)(&world), className.c_str());
                
                hashName = typeid(&shape).name();
                iter = g_luaType.find(hashName);
                className = "";
                if(iter != g_luaType.end()){
                    className = iter->second.c_str();
                } else {
                    className = "cc.PhysicsShape";
                }
                toluafix_pushusertype_ccobject(tolua_S, shape._ID, &shape._luaID, (void*)(&shape), className.c_str());
                return LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
            };
		} while(0);
        
        ok &= luaval_to_rect(tolua_S, 3, &arg1);
        if(!ok)
            return 0;
        cobj->queryRect(arg0, arg1, nullptr);
        toluafix_remove_function_by_refid(tolua_S, handler);
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
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
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
    if (argc == 2)
    {
        std::function<bool (cocos2d::PhysicsWorld &, cocos2d::PhysicsShape &, void *)> arg0;
        cocos2d::Point arg1;
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        do {
            arg0 = [handler, tolua_S](cocos2d::PhysicsWorld &world, cocos2d::PhysicsShape &shape, void * data) -> bool
            {
                std::string hashName = typeid(&world).name();
                auto iter = g_luaType.find(hashName);
                std::string className = "";
                if(iter != g_luaType.end()){
                    className = iter->second.c_str();
                } else {
                    className = "cc.PhysicsWorld";
                }
                
                tolua_pushusertype(tolua_S, (void*)(&world), className.c_str());
                
                hashName = typeid(&shape).name();
                iter = g_luaType.find(hashName);
                className = "";
                if(iter != g_luaType.end()){
                    className = iter->second.c_str();
                } else {
                    className = "cc.PhysicsShape";
                }
                toluafix_pushusertype_ccobject(tolua_S, shape._ID, &shape._luaID, (void*)(&shape), className.c_str());
                return LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
            };
			assert(false);
		} while(0)
            ;
        ok &= luaval_to_point(tolua_S, 3, &arg1);
        if(!ok)
            return 0;
        cobj->queryPoint(arg0, arg1, nullptr);
        toluafix_remove_function_by_refid(tolua_S, handler);
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

int lua_cocos2dx_physics_PhysicsBody_createPolygon(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        cocos2d::Point* arg0 = nullptr;
        int arg1 = 0;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createPolygon(arg0, arg1);
        CC_SAFE_FREE(arg0);
        do {
			if (NULL != ret){
				std::string hashName = typeid(*ret).name();
				auto iter = g_luaType.find(hashName);
				std::string className = "";
				if(iter != g_luaType.end()){
					className = iter->second.c_str();
				} else {
					className = "cc.PhysicsBody";
				}
				cocos2d::Object *dynObject = dynamic_cast<cocos2d::Object *>((cocos2d::PhysicsBody*)ret);
				if (NULL != dynObject) {
					int ID = ret ? (int)(dynObject->_ID) : -1;
					int* luaID = ret ? &(dynObject->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,className.c_str());
				} else {
                    tolua_pushusertype(tolua_S,(void*)ret,className.c_str());
                }} else {
                    lua_pushnil(tolua_S);
                }
		} while (0);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Point* arg0;
        int arg1 = 0;
        cocos2d::PhysicsMaterial arg2;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        ok &= luaval_to_physics_material(tolua_S, 3, &arg2);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createPolygon(arg0, arg1, arg2);
        CC_SAFE_FREE(arg0);
        do {
			if (NULL != ret){
				std::string hashName = typeid(*ret).name();
				auto iter = g_luaType.find(hashName);
				std::string className = "";
				if(iter != g_luaType.end()){
					className = iter->second.c_str();
				} else {
					className = "cc.PhysicsBody";
				}
				cocos2d::Object *dynObject = dynamic_cast<cocos2d::Object *>((cocos2d::PhysicsBody*)ret);
				if (NULL != dynObject) {
					int ID = ret ? (int)(dynObject->_ID) : -1;
					int* luaID = ret ? &(dynObject->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,className.c_str());
				} else {
                    tolua_pushusertype(tolua_S,(void*)ret,className.c_str());
                }} else {
                    lua_pushnil(tolua_S);
                }
		} while (0);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Point* arg0;
        int arg1 = 0;
        cocos2d::PhysicsMaterial arg2;
        cocos2d::Point arg3;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        ok &= luaval_to_physics_material(tolua_S, 3, &arg2);
        ok &= luaval_to_point(tolua_S, 4, &arg3);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createPolygon(arg0, arg1, arg2, arg3);
        CC_SAFE_FREE(arg0);
        do {
			if (NULL != ret){
				std::string hashName = typeid(*ret).name();
				auto iter = g_luaType.find(hashName);
				std::string className = "";
				if(iter != g_luaType.end()){
					className = iter->second.c_str();
				} else {
					className = "cc.PhysicsBody";
				}
				cocos2d::Object *dynObject = dynamic_cast<cocos2d::Object *>((cocos2d::PhysicsBody*)ret);
				if (NULL != dynObject) {
					int ID = ret ? (int)(dynObject->_ID) : -1;
					int* luaID = ret ? &(dynObject->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,className.c_str());
				} else {
                    tolua_pushusertype(tolua_S,(void*)ret,className.c_str());
                }} else {
                    lua_pushnil(tolua_S);
                }
		} while (0);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createPolygon",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_createPolygon'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_physics_PhysicsBody_createEdgePolygon(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        cocos2d::Point* arg0;
        int arg1;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgePolygon(arg0, arg1);
        CC_SAFE_FREE(arg0);
        do {
			if (NULL != ret){
				std::string hashName = typeid(*ret).name();
				auto iter = g_luaType.find(hashName);
				std::string className = "";
				if(iter != g_luaType.end()){
					className = iter->second.c_str();
				} else {
					className = "cc.PhysicsBody";
				}
				cocos2d::Object *dynObject = dynamic_cast<cocos2d::Object *>((cocos2d::PhysicsBody*)ret);
				if (NULL != dynObject) {
					int ID = ret ? (int)(dynObject->_ID) : -1;
					int* luaID = ret ? &(dynObject->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,className.c_str());
				} else {
                    tolua_pushusertype(tolua_S,(void*)ret,className.c_str());
                }} else {
                    lua_pushnil(tolua_S);
                }
		} while (0);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Point* arg0;
        int arg1;
        cocos2d::PhysicsMaterial arg2;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        ok &= luaval_to_physics_material(tolua_S, 3, &arg2);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgePolygon(arg0, arg1, arg2);
        CC_SAFE_FREE(arg0);
        do {
			if (NULL != ret){
				std::string hashName = typeid(*ret).name();
				auto iter = g_luaType.find(hashName);
				std::string className = "";
				if(iter != g_luaType.end()){
					className = iter->second.c_str();
				} else {
					className = "cc.PhysicsBody";
				}
				cocos2d::Object *dynObject = dynamic_cast<cocos2d::Object *>((cocos2d::PhysicsBody*)ret);
				if (NULL != dynObject) {
					int ID = ret ? (int)(dynObject->_ID) : -1;
					int* luaID = ret ? &(dynObject->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,className.c_str());
				} else {
                    tolua_pushusertype(tolua_S,(void*)ret,className.c_str());
                }} else {
                    lua_pushnil(tolua_S);
                }
		} while (0);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Point* arg0;
        int arg1;
        cocos2d::PhysicsMaterial arg2;
        double arg3;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        ok &= luaval_to_physics_material(tolua_S, 3, &arg2);
        ok &= luaval_to_number(tolua_S, 4,&arg3);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgePolygon(arg0, arg1, arg2, arg3);
        CC_SAFE_FREE(arg0);
        do {
			if (NULL != ret){
				std::string hashName = typeid(*ret).name();
				auto iter = g_luaType.find(hashName);
				std::string className = "";
				if(iter != g_luaType.end()){
					className = iter->second.c_str();
				} else {
					className = "cc.PhysicsBody";
				}
				cocos2d::Object *dynObject = dynamic_cast<cocos2d::Object *>((cocos2d::PhysicsBody*)ret);
				if (NULL != dynObject) {
					int ID = ret ? (int)(dynObject->_ID) : -1;
					int* luaID = ret ? &(dynObject->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,className.c_str());
				} else {
                    tolua_pushusertype(tolua_S,(void*)ret,className.c_str());
                }} else {
                    lua_pushnil(tolua_S);
                }
		} while (0);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createEdgePolygon",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_createEdgePolygon'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_physics_PhysicsBody_createEdgeChain(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        cocos2d::Point* arg0;
        int arg1;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeChain(arg0, arg1);
        CC_SAFE_FREE(arg0);
        do {
			if (NULL != ret){
				std::string hashName = typeid(*ret).name();
				auto iter = g_luaType.find(hashName);
				std::string className = "";
				if(iter != g_luaType.end()){
					className = iter->second.c_str();
				} else {
					className = "cc.PhysicsBody";
				}
				cocos2d::Object *dynObject = dynamic_cast<cocos2d::Object *>((cocos2d::PhysicsBody*)ret);
				if (NULL != dynObject) {
					int ID = ret ? (int)(dynObject->_ID) : -1;
					int* luaID = ret ? &(dynObject->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,className.c_str());
				} else {
                    tolua_pushusertype(tolua_S,(void*)ret,className.c_str());
                }} else {
                    lua_pushnil(tolua_S);
                }
		} while (0);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Point* arg0;
        int arg1;
        cocos2d::PhysicsMaterial arg2;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        ok &= luaval_to_physics_material(tolua_S, 3, &arg2);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeChain(arg0, arg1, arg2);
        CC_SAFE_FREE(arg0);
        do {
			if (NULL != ret){
				std::string hashName = typeid(*ret).name();
				auto iter = g_luaType.find(hashName);
				std::string className = "";
				if(iter != g_luaType.end()){
					className = iter->second.c_str();
				} else {
					className = "cc.PhysicsBody";
				}
				cocos2d::Object *dynObject = dynamic_cast<cocos2d::Object *>((cocos2d::PhysicsBody*)ret);
				if (NULL != dynObject) {
					int ID = ret ? (int)(dynObject->_ID) : -1;
					int* luaID = ret ? &(dynObject->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,className.c_str());
				} else {
                    tolua_pushusertype(tolua_S,(void*)ret,className.c_str());
                }} else {
                    lua_pushnil(tolua_S);
                }
		} while (0);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Point* arg0;
        int arg1;
        cocos2d::PhysicsMaterial arg2;
        double arg3;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        ok &= luaval_to_physics_material(tolua_S, 3, &arg2);
        ok &= luaval_to_number(tolua_S, 4,&arg3);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeChain(arg0, arg1, arg2, arg3);
        CC_SAFE_FREE(arg0);
        do {
			if (NULL != ret){
				std::string hashName = typeid(*ret).name();
				auto iter = g_luaType.find(hashName);
				std::string className = "";
				if(iter != g_luaType.end()){
					className = iter->second.c_str();
				} else {
					className = "cc.PhysicsBody";
				}
				cocos2d::Object *dynObject = dynamic_cast<cocos2d::Object *>((cocos2d::PhysicsBody*)ret);
				if (NULL != dynObject) {
					int ID = ret ? (int)(dynObject->_ID) : -1;
					int* luaID = ret ? &(dynObject->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,className.c_str());
				} else {
                    tolua_pushusertype(tolua_S,(void*)ret,className.c_str());
                }} else {
                    lua_pushnil(tolua_S);
                }
		} while (0);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createEdgeChain",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeChain'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_physics_PhysicsShape_recenterPoints(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        cocos2d::Point* arg0;
        int arg1 = 0;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsShape::recenterPoints(arg0, arg1);
        points_to_luaval(tolua_S, arg0, arg1);
        CC_SAFE_FREE(arg0);
        
        return 0;
    }
    if (argc == 2)
    {
        cocos2d::Point* arg0;
        int arg1 = 0;
        cocos2d::Point arg2;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        ok &= luaval_to_point(tolua_S, 3, &arg2);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::PhysicsShape::recenterPoints(arg0, arg1, arg2);
        points_to_luaval(tolua_S, arg0, arg1);
        CC_SAFE_FREE(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "recenterPoints",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_recenterPoints'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_physics_PhysicsShape_getPolyonCenter(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        cocos2d::Point* arg0;
        int arg1 = 0;
        do {
            ok = luaval_to_array_of_Point(tolua_S, 2, &arg0, &arg1);
            if (nullptr == arg0){
                LUA_PRECONDITION( arg0, "Invalid Native Object");
            }} while (0);
        if(!ok)
        {
            CC_SAFE_FREE(arg0);
            return 0;
        }
        cocos2d::Point ret = cocos2d::PhysicsShape::getPolyonCenter(arg0, arg1);
        CC_SAFE_FREE(arg0);
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getPolyonCenter",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getPolyonCenter'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_physics_PhysicsShapeBox_getPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeBox* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeBox",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsShapeBox*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeBox_getPoints'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        cocos2d::Point arg0[4];
        cobj->getPoints(arg0);
        points_to_luaval(tolua_S, arg0, 4);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPoints",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeBox_getPoints'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_physics_PhysicsShapePolygon_getPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapePolygon* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapePolygon",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsShapePolygon*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapePolygon_getPoints'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        int count = cobj->getPointsCount();
        cocos2d::Point* arg0 = new cocos2d::Point[count];
        cobj->getPoints(arg0);
        points_to_luaval(tolua_S, arg0, count);
        CC_SAFE_FREE(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPoints",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapePolygon_getPoints'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_physics_PhysicsShapeEdgeBox_getPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeEdgeBox* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeEdgeBox",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsShapeEdgeBox*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeEdgeBox_getPoints'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        int count = cobj->getPointsCount();
        cocos2d::Point* arg0 = new cocos2d::Point[count];
        cobj->getPoints(arg0);
        points_to_luaval(tolua_S, arg0, count);
        CC_SAFE_FREE(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPoints",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeEdgeBox_getPoints'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_physics_PhysicsShapeEdgePolygon_getPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeEdgePolygon* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeEdgePolygon",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsShapeEdgePolygon*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeEdgePolygon_getPoints'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        int count = cobj->getPointsCount();
        cocos2d::Point* arg0 = new cocos2d::Point[count];
        cobj->getPoints(arg0);
        points_to_luaval(tolua_S, arg0, count);
        CC_SAFE_FREE(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPoints",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeEdgePolygon_getPoints'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_physics_PhysicsShapeEdgeChain_getPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeEdgeChain* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeEdgeChain",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::PhysicsShapeEdgeChain*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeEdgeChain_getPoints'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        int count = cobj->getPointsCount();
        cocos2d::Point* arg0 = new cocos2d::Point[count];
        cobj->getPoints(arg0);
        points_to_luaval(tolua_S, arg0, count);
        CC_SAFE_FREE(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPoints",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeEdgeChain_getPoints'.",&tolua_err);
#endif
    
    return 0;
}

static int tolua_cocos2dx_EventListenerPhysicsContact_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerPhysicsContact* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerPhysicsContact", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerPhysicsContact*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerPhysicsContact_registerScriptHandler'\n", nullptr);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        ScriptHandlerMgr::HandlerType type        = static_cast<ScriptHandlerMgr::HandlerType>((int)tolua_tonumber(tolua_S, 3, 0));
        switch (type)
        {
            case ScriptHandlerMgr::HandlerType::EVENT_PHYSICS_CONTACT_BEGIN:
            {
                ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                
                self->onContactBegin = [handler](EventCustom* event, const PhysicsContact& contact) -> bool{
                    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
                    stack->pushObject(event, "cc.EventCustom");
                    stack->pushObject(const_cast<PhysicsContact*>(&contact), "cc.PhysicsContact");
                    bool ret = stack->executeFunctionByHandler(handler, 2);
                    stack->clean();
                    
                    return ret;
                };
            }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_PHYSICS_CONTACT_PRESOLVE:
            {
                ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                
                self->onContactPreSolve = [handler](EventCustom* event, const PhysicsContact& contact, const PhysicsContactPreSolve& solve) -> bool{
                    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
                    stack->pushObject(event, "cc.EventCustom");
                    stack->pushObject(const_cast<PhysicsContact*>(&contact), "cc.PhysicsContact");
                    tolua_pushusertype(stack->getLuaState(), const_cast<PhysicsContactPreSolve*>(&solve), "cc.PhysicsContactPreSolve");
                    bool ret = stack->executeFunctionByHandler(handler, 3);
                    stack->clean();
                    
                    return ret;
                };
            }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_PHYSICS_CONTACT_POSTSOLVE:
            {
                ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                
                self->onContactPostSolve = [handler](EventCustom* event, const PhysicsContact& contact, const PhysicsContactPostSolve& solve){
                    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
                    stack->pushObject(event, "cc.EventCustom");
                    stack->pushObject(const_cast<PhysicsContact*>(&contact), "cc.PhysicsContact");
                    tolua_pushusertype(stack->getLuaState(), const_cast<PhysicsContactPostSolve*>(&solve), "cc.PhysicsContactPostSolve");
                    stack->executeFunctionByHandler(handler, 3);
                    stack->clean();
                };
            }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_PHYSICS_CONTACT_SEPERATE:
            {
                ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                
                self->onContactSeperate = [handler](EventCustom* event, const PhysicsContact& contact){
                    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
                    stack->pushObject(event, "cc.EventCustom");
                    stack->pushObject(const_cast<PhysicsContact*>(&contact), "cc.PhysicsContact");
                    stack->executeFunctionByHandler(handler, 2);
                    stack->clean();
                };
            }
                break;
            default:
                break;
        }
        return 0;
    }
    
    CCLOG("'registerScriptHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

int register_all_cocos2dx_physics_manual(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.PhysicsBody");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getJoints");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsBody_getJoints );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"createPolygon");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsBody_createPolygon );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"createEdgeChain");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsBody_createEdgeChain );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"createEdgePolygon");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsBody_createEdgePolygon );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    
    lua_pushstring(tolua_S, "cc.PhysicsShape");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"recenterPoints");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsShape_recenterPoints );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"getPolyonCenter");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsShape_getPolyonCenter );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    
    lua_pushstring(tolua_S, "cc.PhysicsShapeBox");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getPoints");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsShapeBox_getPoints );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    
    lua_pushstring(tolua_S, "cc.PhysicsShapeEdgeBox");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getPoints");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsShapeEdgeBox_getPoints );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    
    lua_pushstring(tolua_S, "cc.PhysicsShapePolygon");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getPoints");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsShapePolygon_getPoints );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    
    lua_pushstring(tolua_S, "cc.PhysicsShapeEdgePolygon");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getPoints");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsShapeEdgePolygon_getPoints );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    
    lua_pushstring(tolua_S, "cc.PhysicsShapeEdgeChain");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getPoints");
        lua_pushcfunction(tolua_S,lua_cocos2dx_physics_PhysicsShapeEdgeChain_getPoints);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    
    lua_pushstring(tolua_S, "cc.PhysicsWorld");
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
        lua_pushstring(tolua_S, "DEBUGDRAW_NONE");
        lua_pushnumber(tolua_S, PhysicsWorld::DEBUGDRAW_NONE);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "DEBUGDRAW_SHAPE");
        lua_pushnumber(tolua_S, PhysicsWorld::DEBUGDRAW_SHAPE);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "DEBUGDRAW_JOINT");
        lua_pushnumber(tolua_S, PhysicsWorld::DEBUGDRAW_JOINT);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "DEBUGDRAW_CONTACT");
        lua_pushnumber(tolua_S, PhysicsWorld::DEBUGDRAW_CONTACT);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "DEBUGDRAW_ALL");
        lua_pushnumber(tolua_S, PhysicsWorld::DEBUGDRAW_ALL);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
    
    lua_pushstring(tolua_S, "cc.EventListenerPhysicsContact");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerPhysicsContact_registerScriptHandler);
    }
    lua_pop(tolua_S, 1);

    tolua_constant(tolua_S, "PHYSICS_INFINITY", PHYSICS_INFINITY);
    
    return 0;
}

#endif