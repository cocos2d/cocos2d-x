#include "lua_cocos2dx_csloader_auto.hpp"
#include "CSLoader.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_cocos2dx_csloader_CSLoader_createNodeFromJson(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_createNodeFromJson'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:createNodeFromJson");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_createNodeFromJson'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->createNodeFromJson(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:createNodeFromJson",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_createNodeFromJson'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:createNodeWithFlatBuffersFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersFile'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->createNodeWithFlatBuffersFile(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:createNodeWithFlatBuffersFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_loadNodeWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_loadNodeWithFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:loadNodeWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_loadNodeWithFile'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->loadNodeWithFile(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:loadNodeWithFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_loadNodeWithFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_bindCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_bindCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        std::string arg0;
        std::string arg1;
        cocos2d::ui::Widget* arg2;
        cocos2d::Node* arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:bindCallback");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.CSLoader:bindCallback");

        ok &= luaval_to_object<cocos2d::ui::Widget>(tolua_S, 4, "ccui.Widget",&arg2, "cc.CSLoader:bindCallback");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 5, "cc.Node",&arg3, "cc.CSLoader:bindCallback");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_bindCallback'", nullptr);
            return 0;
        }
        bool ret = cobj->bindCallback(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:bindCallback",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_bindCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_setJsonPath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_setJsonPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:setJsonPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_setJsonPath'", nullptr);
            return 0;
        }
        cobj->setJsonPath(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:setJsonPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_setJsonPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_init'", nullptr);
            return 0;
        }
        cobj->init();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_loadNodeWithContent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_loadNodeWithContent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:loadNodeWithContent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_loadNodeWithContent'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->loadNodeWithContent(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:loadNodeWithContent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_loadNodeWithContent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_isRecordJsonPath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_isRecordJsonPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_isRecordJsonPath'", nullptr);
            return 0;
        }
        bool ret = cobj->isRecordJsonPath();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:isRecordJsonPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_isRecordJsonPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_getJsonPath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_getJsonPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_getJsonPath'", nullptr);
            return 0;
        }
        std::string ret = cobj->getJsonPath();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:getJsonPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_getJsonPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_setRecordJsonPath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_setRecordJsonPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.CSLoader:setRecordJsonPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_setRecordJsonPath'", nullptr);
            return 0;
        }
        cobj->setRecordJsonPath(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:setRecordJsonPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_setRecordJsonPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersForSimulator(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CSLoader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersForSimulator'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:createNodeWithFlatBuffersForSimulator");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersForSimulator'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->createNodeWithFlatBuffersForSimulator(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:createNodeWithFlatBuffersForSimulator",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersForSimulator'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_destroyInstance'", nullptr);
            return 0;
        }
        cocos2d::CSLoader::destroyInstance();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CSLoader:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_csloader_CSLoader_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_getInstance'", nullptr);
            return 0;
        }
        cocos2d::CSLoader* ret = cocos2d::CSLoader::getInstance();
        object_to_luaval<cocos2d::CSLoader>(tolua_S, "cc.CSLoader",(cocos2d::CSLoader*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CSLoader:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_csloader_CSLoader_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CSLoader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::CSLoader();
        tolua_pushusertype(tolua_S,(void*)cobj,"cc.CSLoader");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:CSLoader",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_csloader_CSLoader_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CSLoader)");
    return 0;
}

int lua_register_cocos2dx_csloader_CSLoader(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.CSLoader");
    tolua_cclass(tolua_S,"CSLoader","cc.CSLoader","",nullptr);

    tolua_beginmodule(tolua_S,"CSLoader");
        tolua_function(tolua_S,"new",lua_cocos2dx_csloader_CSLoader_constructor);
        tolua_function(tolua_S,"createNodeFromJson",lua_cocos2dx_csloader_CSLoader_createNodeFromJson);
        tolua_function(tolua_S,"createNodeWithFlatBuffersFile",lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersFile);
        tolua_function(tolua_S,"loadNodeWithFile",lua_cocos2dx_csloader_CSLoader_loadNodeWithFile);
        tolua_function(tolua_S,"bindCallback",lua_cocos2dx_csloader_CSLoader_bindCallback);
        tolua_function(tolua_S,"setJsonPath",lua_cocos2dx_csloader_CSLoader_setJsonPath);
        tolua_function(tolua_S,"init",lua_cocos2dx_csloader_CSLoader_init);
        tolua_function(tolua_S,"loadNodeWithContent",lua_cocos2dx_csloader_CSLoader_loadNodeWithContent);
        tolua_function(tolua_S,"isRecordJsonPath",lua_cocos2dx_csloader_CSLoader_isRecordJsonPath);
        tolua_function(tolua_S,"getJsonPath",lua_cocos2dx_csloader_CSLoader_getJsonPath);
        tolua_function(tolua_S,"setRecordJsonPath",lua_cocos2dx_csloader_CSLoader_setRecordJsonPath);
        tolua_function(tolua_S,"createNodeWithFlatBuffersForSimulator",lua_cocos2dx_csloader_CSLoader_createNodeWithFlatBuffersForSimulator);
        tolua_function(tolua_S,"destroyInstance", lua_cocos2dx_csloader_CSLoader_destroyInstance);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_csloader_CSLoader_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::CSLoader).name();
    g_luaType[typeName] = "cc.CSLoader";
    g_typeCast["CSLoader"] = "cc.CSLoader";
    return 1;
}
TOLUA_API int register_all_cocos2dx_csloader(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_csloader_CSLoader(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

