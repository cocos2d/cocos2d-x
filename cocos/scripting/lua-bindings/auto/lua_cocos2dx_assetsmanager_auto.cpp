#include "lua_cocos2dx_assetsmanager_auto.hpp"
#include "cocos-ext.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_assetsmanager_AssetsManager_setStoragePath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_setStoragePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:setStoragePath"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_setStoragePath'", nullptr);
            return 0;
        }
        cobj->setStoragePath(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setStoragePath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_setStoragePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_setPackageUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_setPackageUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:setPackageUrl"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_setPackageUrl'", nullptr);
            return 0;
        }
        cobj->setPackageUrl(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setPackageUrl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_setPackageUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_checkUpdate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_checkUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_checkUpdate'", nullptr);
            return 0;
        }
        bool ret = cobj->checkUpdate();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:checkUpdate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_checkUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_getStoragePath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_getStoragePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_getStoragePath'", nullptr);
            return 0;
        }
        const char* ret = cobj->getStoragePath();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getStoragePath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_getStoragePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_update(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_update'", nullptr);
            return 0;
        }
        cobj->update();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:update",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_setConnectionTimeout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_setConnectionTimeout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.AssetsManager:setConnectionTimeout");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_setConnectionTimeout'", nullptr);
            return 0;
        }
        cobj->setConnectionTimeout(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setConnectionTimeout",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_setConnectionTimeout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_setVersionFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_setVersionFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:setVersionFileUrl"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_setVersionFileUrl'", nullptr);
            return 0;
        }
        cobj->setVersionFileUrl(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setVersionFileUrl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_setVersionFileUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_getPackageUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_getPackageUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_getPackageUrl'", nullptr);
            return 0;
        }
        const char* ret = cobj->getPackageUrl();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getPackageUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_getPackageUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_getConnectionTimeout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_getConnectionTimeout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_getConnectionTimeout'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getConnectionTimeout();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getConnectionTimeout",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_getConnectionTimeout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_getVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_getVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_getVersion'", nullptr);
            return 0;
        }
        std::string ret = cobj->getVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_getVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_getVersionFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_getVersionFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_getVersionFileUrl'", nullptr);
            return 0;
        }
        const char* ret = cobj->getVersionFileUrl();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getVersionFileUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_getVersionFileUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_deleteVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManager_deleteVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_deleteVersion'", nullptr);
            return 0;
        }
        cobj->deleteVersion();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:deleteVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_deleteVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        std::function<void (int)> arg3;
        std::function<void (int)> arg4;
        std::function<void ()> arg5;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:create"); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.AssetsManager:create"); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.AssetsManager:create"); arg2 = arg2_tmp.c_str();
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_create'", nullptr);
            return 0;
        }
        cocos2d::extension::AssetsManager* ret = cocos2d::extension::AssetsManager::create(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::extension::AssetsManager>(tolua_S, "cc.AssetsManager",(cocos2d::extension::AssetsManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AssetsManager:create",argc, 6);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:AssetsManager"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:AssetsManager"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.AssetsManager:AssetsManager"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager(arg0, arg1);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    if (argc == 3) 
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:AssetsManager"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.AssetsManager:AssetsManager"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.AssetsManager:AssetsManager"); arg2 = arg2_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager(arg0, arg1, arg2);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:AssetsManager",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManager_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_assetsmanager_AssetsManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AssetsManager)");
    return 0;
}

int lua_register_cocos2dx_assetsmanager_AssetsManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.AssetsManager");
    tolua_cclass(tolua_S,"AssetsManager","cc.AssetsManager","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"AssetsManager");
        tolua_function(tolua_S,"new",lua_cocos2dx_assetsmanager_AssetsManager_constructor);
        tolua_function(tolua_S,"setStoragePath",lua_cocos2dx_assetsmanager_AssetsManager_setStoragePath);
        tolua_function(tolua_S,"setPackageUrl",lua_cocos2dx_assetsmanager_AssetsManager_setPackageUrl);
        tolua_function(tolua_S,"checkUpdate",lua_cocos2dx_assetsmanager_AssetsManager_checkUpdate);
        tolua_function(tolua_S,"getStoragePath",lua_cocos2dx_assetsmanager_AssetsManager_getStoragePath);
        tolua_function(tolua_S,"update",lua_cocos2dx_assetsmanager_AssetsManager_update);
        tolua_function(tolua_S,"setConnectionTimeout",lua_cocos2dx_assetsmanager_AssetsManager_setConnectionTimeout);
        tolua_function(tolua_S,"setVersionFileUrl",lua_cocos2dx_assetsmanager_AssetsManager_setVersionFileUrl);
        tolua_function(tolua_S,"getPackageUrl",lua_cocos2dx_assetsmanager_AssetsManager_getPackageUrl);
        tolua_function(tolua_S,"getConnectionTimeout",lua_cocos2dx_assetsmanager_AssetsManager_getConnectionTimeout);
        tolua_function(tolua_S,"getVersion",lua_cocos2dx_assetsmanager_AssetsManager_getVersion);
        tolua_function(tolua_S,"getVersionFileUrl",lua_cocos2dx_assetsmanager_AssetsManager_getVersionFileUrl);
        tolua_function(tolua_S,"deleteVersion",lua_cocos2dx_assetsmanager_AssetsManager_deleteVersion);
        tolua_function(tolua_S,"create", lua_cocos2dx_assetsmanager_AssetsManager_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::AssetsManager).name();
    g_luaType[typeName] = "cc.AssetsManager";
    g_typeCast["AssetsManager"] = "cc.AssetsManager";
    return 1;
}

int lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetsManagerEx(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::EventAssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetsManagerEx'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetsManagerEx'", nullptr);
            return 0;
        }
        cocos2d::extension::AssetsManagerEx* ret = cobj->getAssetsManagerEx();
        object_to_luaval<cocos2d::extension::AssetsManagerEx>(tolua_S, "cc.AssetsManagerEx",(cocos2d::extension::AssetsManagerEx*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getAssetsManagerEx",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetsManagerEx'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetId(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::EventAssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetId'", nullptr);
            return 0;
        }
        std::string ret = cobj->getAssetId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getAssetId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLECode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::EventAssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLECode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLECode'", nullptr);
            return 0;
        }
        int ret = cobj->getCURLECode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getCURLECode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLECode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getMessage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::EventAssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getMessage'", nullptr);
            return 0;
        }
        std::string ret = cobj->getMessage();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getMessage",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLMCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::EventAssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLMCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLMCode'", nullptr);
            return 0;
        }
        int ret = cobj->getCURLMCode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getCURLMCode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLMCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercentByFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::EventAssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercentByFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercentByFile'", nullptr);
            return 0;
        }
        double ret = cobj->getPercentByFile();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getPercentByFile",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercentByFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getEventCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::EventAssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getEventCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getEventCode'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getEventCode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getEventCode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getEventCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::EventAssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercent'", nullptr);
            return 0;
        }
        double ret = cobj->getPercent();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getPercent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercent'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_assetsmanager_EventAssetsManagerEx_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventAssetsManagerEx)");
    return 0;
}

int lua_register_cocos2dx_assetsmanager_EventAssetsManagerEx(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventAssetsManagerEx");
    tolua_cclass(tolua_S,"EventAssetsManagerEx","cc.EventAssetsManagerEx","cc.EventCustom",nullptr);

    tolua_beginmodule(tolua_S,"EventAssetsManagerEx");
        tolua_function(tolua_S,"getAssetsManagerEx",lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetsManagerEx);
        tolua_function(tolua_S,"getAssetId",lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getAssetId);
        tolua_function(tolua_S,"getCURLECode",lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLECode);
        tolua_function(tolua_S,"getMessage",lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getMessage);
        tolua_function(tolua_S,"getCURLMCode",lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getCURLMCode);
        tolua_function(tolua_S,"getPercentByFile",lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercentByFile);
        tolua_function(tolua_S,"getEventCode",lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getEventCode);
        tolua_function(tolua_S,"getPercent",lua_cocos2dx_assetsmanager_EventAssetsManagerEx_getPercent);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::EventAssetsManagerEx).name();
    g_luaType[typeName] = "cc.EventAssetsManagerEx";
    g_typeCast["EventAssetsManagerEx"] = "cc.EventAssetsManagerEx";
    return 1;
}

int lua_cocos2dx_assetsmanager_Manifest_getManifestFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Manifest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Manifest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Manifest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_Manifest_getManifestFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_Manifest_getManifestFileUrl'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getManifestFileUrl();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:getManifestFileUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_Manifest_getManifestFileUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_Manifest_isVersionLoaded(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Manifest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Manifest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Manifest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_Manifest_isVersionLoaded'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_Manifest_isVersionLoaded'", nullptr);
            return 0;
        }
        bool ret = cobj->isVersionLoaded();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:isVersionLoaded",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_Manifest_isVersionLoaded'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_Manifest_isLoaded(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Manifest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Manifest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Manifest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_Manifest_isLoaded'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_Manifest_isLoaded'", nullptr);
            return 0;
        }
        bool ret = cobj->isLoaded();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:isLoaded",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_Manifest_isLoaded'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_Manifest_getPackageUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Manifest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Manifest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Manifest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_Manifest_getPackageUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_Manifest_getPackageUrl'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getPackageUrl();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:getPackageUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_Manifest_getPackageUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_Manifest_getVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Manifest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Manifest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Manifest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_Manifest_getVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_Manifest_getVersion'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:getVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_Manifest_getVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_Manifest_getVersionFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Manifest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Manifest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Manifest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_Manifest_getVersionFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_Manifest_getVersionFileUrl'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getVersionFileUrl();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:getVersionFileUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_Manifest_getVersionFileUrl'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_assetsmanager_Manifest_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Manifest)");
    return 0;
}

int lua_register_cocos2dx_assetsmanager_Manifest(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Manifest");
    tolua_cclass(tolua_S,"Manifest","cc.Manifest","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Manifest");
        tolua_function(tolua_S,"getManifestFileUrl",lua_cocos2dx_assetsmanager_Manifest_getManifestFileUrl);
        tolua_function(tolua_S,"isVersionLoaded",lua_cocos2dx_assetsmanager_Manifest_isVersionLoaded);
        tolua_function(tolua_S,"isLoaded",lua_cocos2dx_assetsmanager_Manifest_isLoaded);
        tolua_function(tolua_S,"getPackageUrl",lua_cocos2dx_assetsmanager_Manifest_getPackageUrl);
        tolua_function(tolua_S,"getVersion",lua_cocos2dx_assetsmanager_Manifest_getVersion);
        tolua_function(tolua_S,"getVersionFileUrl",lua_cocos2dx_assetsmanager_Manifest_getVersionFileUrl);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::Manifest).name();
    g_luaType[typeName] = "cc.Manifest";
    g_typeCast["Manifest"] = "cc.Manifest";
    return 1;
}

int lua_cocos2dx_assetsmanager_AssetsManagerEx_getState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getState'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getState();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManagerEx_checkUpdate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_checkUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_checkUpdate'", nullptr);
            return 0;
        }
        cobj->checkUpdate();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:checkUpdate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_checkUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManagerEx_getStoragePath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getStoragePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getStoragePath'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getStoragePath();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getStoragePath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getStoragePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManagerEx_update(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_update'", nullptr);
            return 0;
        }
        cobj->update();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:update",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManagerEx_getLocalManifest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getLocalManifest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getLocalManifest'", nullptr);
            return 0;
        }
        const cocos2d::extension::Manifest* ret = cobj->getLocalManifest();
        object_to_luaval<cocos2d::extension::Manifest>(tolua_S, "cc.Manifest",(cocos2d::extension::Manifest*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getLocalManifest",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getLocalManifest'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManagerEx_getRemoteManifest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getRemoteManifest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getRemoteManifest'", nullptr);
            return 0;
        }
        const cocos2d::extension::Manifest* ret = cobj->getRemoteManifest();
        object_to_luaval<cocos2d::extension::Manifest>(tolua_S, "cc.Manifest",(cocos2d::extension::Manifest*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getRemoteManifest",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_getRemoteManifest'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManagerEx_downloadFailedAssets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_downloadFailedAssets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_downloadFailedAssets'", nullptr);
            return 0;
        }
        cobj->downloadFailedAssets();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:downloadFailedAssets",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_downloadFailedAssets'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_assetsmanager_AssetsManagerEx_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.AssetsManagerEx:create");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.AssetsManagerEx:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_create'", nullptr);
            return 0;
        }
        cocos2d::extension::AssetsManagerEx* ret = cocos2d::extension::AssetsManagerEx::create(arg0, arg1);
        object_to_luaval<cocos2d::extension::AssetsManagerEx>(tolua_S, "cc.AssetsManagerEx",(cocos2d::extension::AssetsManagerEx*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AssetsManagerEx:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_assetsmanager_AssetsManagerEx_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_assetsmanager_AssetsManagerEx_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AssetsManagerEx)");
    return 0;
}

int lua_register_cocos2dx_assetsmanager_AssetsManagerEx(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.AssetsManagerEx");
    tolua_cclass(tolua_S,"AssetsManagerEx","cc.AssetsManagerEx","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"AssetsManagerEx");
        tolua_function(tolua_S,"getState",lua_cocos2dx_assetsmanager_AssetsManagerEx_getState);
        tolua_function(tolua_S,"checkUpdate",lua_cocos2dx_assetsmanager_AssetsManagerEx_checkUpdate);
        tolua_function(tolua_S,"getStoragePath",lua_cocos2dx_assetsmanager_AssetsManagerEx_getStoragePath);
        tolua_function(tolua_S,"update",lua_cocos2dx_assetsmanager_AssetsManagerEx_update);
        tolua_function(tolua_S,"getLocalManifest",lua_cocos2dx_assetsmanager_AssetsManagerEx_getLocalManifest);
        tolua_function(tolua_S,"getRemoteManifest",lua_cocos2dx_assetsmanager_AssetsManagerEx_getRemoteManifest);
        tolua_function(tolua_S,"downloadFailedAssets",lua_cocos2dx_assetsmanager_AssetsManagerEx_downloadFailedAssets);
        tolua_function(tolua_S,"create", lua_cocos2dx_assetsmanager_AssetsManagerEx_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::AssetsManagerEx).name();
    g_luaType[typeName] = "cc.AssetsManagerEx";
    g_typeCast["AssetsManagerEx"] = "cc.AssetsManagerEx";
    return 1;
}

static int lua_cocos2dx_assetsmanager_EventListenerAssetsManagerEx_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventListenerAssetsManagerEx)");
    return 0;
}

int lua_register_cocos2dx_assetsmanager_EventListenerAssetsManagerEx(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventListenerAssetsManagerEx");
    tolua_cclass(tolua_S,"EventListenerAssetsManagerEx","cc.EventListenerAssetsManagerEx","cc.EventListenerCustom",nullptr);

    tolua_beginmodule(tolua_S,"EventListenerAssetsManagerEx");
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::EventListenerAssetsManagerEx).name();
    g_luaType[typeName] = "cc.EventListenerAssetsManagerEx";
    g_typeCast["EventListenerAssetsManagerEx"] = "cc.EventListenerAssetsManagerEx";
    return 1;
}
TOLUA_API int register_all_cocos2dx_assetsmanager(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_assetsmanager_AssetsManagerEx(tolua_S);
	lua_register_cocos2dx_assetsmanager_EventListenerAssetsManagerEx(tolua_S);
	lua_register_cocos2dx_assetsmanager_AssetsManager(tolua_S);
	lua_register_cocos2dx_assetsmanager_Manifest(tolua_S);
	lua_register_cocos2dx_assetsmanager_EventAssetsManagerEx(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

