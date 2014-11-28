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
int lua_cocos2dx_csloader_CSLoader_createNodeFromProtocolBuffers(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_createNodeFromProtocolBuffers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:createNodeFromProtocolBuffers");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_createNodeFromProtocolBuffers'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->createNodeFromProtocolBuffers(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:createNodeFromProtocolBuffers",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_createNodeFromProtocolBuffers'.",&tolua_err);
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
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_setRecordXMLPath(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_setRecordXMLPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.CSLoader:setRecordXMLPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_setRecordXMLPath'", nullptr);
            return 0;
        }
        cobj->setRecordXMLPath(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:setRecordXMLPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_setRecordXMLPath'.",&tolua_err);
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
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:setJsonPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_setJsonPath'.",&tolua_err);
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
int lua_cocos2dx_csloader_CSLoader_isRecordProtocolBuffersPath(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_isRecordProtocolBuffersPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_isRecordProtocolBuffersPath'", nullptr);
            return 0;
        }
        bool ret = cobj->isRecordProtocolBuffersPath();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:isRecordProtocolBuffersPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_isRecordProtocolBuffersPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_isRecordXMLPath(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_isRecordXMLPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_isRecordXMLPath'", nullptr);
            return 0;
        }
        bool ret = cobj->isRecordXMLPath();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:isRecordXMLPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_isRecordXMLPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_getProtocolBuffersPath(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_getProtocolBuffersPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_getProtocolBuffersPath'", nullptr);
            return 0;
        }
        std::string ret = cobj->getProtocolBuffersPath();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:getProtocolBuffersPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_getProtocolBuffersPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_getXMLPath(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_getXMLPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_getXMLPath'", nullptr);
            return 0;
        }
        std::string ret = cobj->getXMLPath();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:getXMLPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_getXMLPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_createNodeFromXML(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_createNodeFromXML'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:createNodeFromXML");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_createNodeFromXML'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->createNodeFromXML(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:createNodeFromXML",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_createNodeFromXML'.",&tolua_err);
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
int lua_cocos2dx_csloader_CSLoader_setRecordProtocolBuffersPath(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_setRecordProtocolBuffersPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.CSLoader:setRecordProtocolBuffersPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_setRecordProtocolBuffersPath'", nullptr);
            return 0;
        }
        cobj->setRecordProtocolBuffersPath(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:setRecordProtocolBuffersPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_setRecordProtocolBuffersPath'.",&tolua_err);
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
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:setRecordJsonPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_setRecordJsonPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_setProtocolBuffersPath(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_setProtocolBuffersPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:setProtocolBuffersPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_setProtocolBuffersPath'", nullptr);
            return 0;
        }
        cobj->setProtocolBuffersPath(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:setProtocolBuffersPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_setProtocolBuffersPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_purge(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_purge'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_purge'", nullptr);
            return 0;
        }
        cobj->purge();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:purge",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_purge'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_csloader_CSLoader_setXMLPath(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_csloader_CSLoader_setXMLPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:setXMLPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_setXMLPath'", nullptr);
            return 0;
        }
        cobj->setXMLPath(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CSLoader:setXMLPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_setXMLPath'.",&tolua_err);
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
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CSLoader:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_csloader_CSLoader_createNode(lua_State* tolua_S)
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

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:createNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_csloader_CSLoader_createNode'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cocos2d::CSLoader::createNode(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CSLoader:createNode",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_createNode'.",&tolua_err);
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
        tolua_function(tolua_S,"createNodeFromProtocolBuffers",lua_cocos2dx_csloader_CSLoader_createNodeFromProtocolBuffers);
        tolua_function(tolua_S,"init",lua_cocos2dx_csloader_CSLoader_init);
        tolua_function(tolua_S,"setRecordXMLPath",lua_cocos2dx_csloader_CSLoader_setRecordXMLPath);
        tolua_function(tolua_S,"setJsonPath",lua_cocos2dx_csloader_CSLoader_setJsonPath);
        tolua_function(tolua_S,"loadNodeWithFile",lua_cocos2dx_csloader_CSLoader_loadNodeWithFile);
        tolua_function(tolua_S,"loadNodeWithContent",lua_cocos2dx_csloader_CSLoader_loadNodeWithContent);
        tolua_function(tolua_S,"isRecordProtocolBuffersPath",lua_cocos2dx_csloader_CSLoader_isRecordProtocolBuffersPath);
        tolua_function(tolua_S,"isRecordXMLPath",lua_cocos2dx_csloader_CSLoader_isRecordXMLPath);
        tolua_function(tolua_S,"getProtocolBuffersPath",lua_cocos2dx_csloader_CSLoader_getProtocolBuffersPath);
        tolua_function(tolua_S,"getXMLPath",lua_cocos2dx_csloader_CSLoader_getXMLPath);
        tolua_function(tolua_S,"createNodeFromXML",lua_cocos2dx_csloader_CSLoader_createNodeFromXML);
        tolua_function(tolua_S,"isRecordJsonPath",lua_cocos2dx_csloader_CSLoader_isRecordJsonPath);
        tolua_function(tolua_S,"setRecordProtocolBuffersPath",lua_cocos2dx_csloader_CSLoader_setRecordProtocolBuffersPath);
        tolua_function(tolua_S,"getJsonPath",lua_cocos2dx_csloader_CSLoader_getJsonPath);
        tolua_function(tolua_S,"setRecordJsonPath",lua_cocos2dx_csloader_CSLoader_setRecordJsonPath);
        tolua_function(tolua_S,"setProtocolBuffersPath",lua_cocos2dx_csloader_CSLoader_setProtocolBuffersPath);
        tolua_function(tolua_S,"purge",lua_cocos2dx_csloader_CSLoader_purge);
        tolua_function(tolua_S,"setXMLPath",lua_cocos2dx_csloader_CSLoader_setXMLPath);
        tolua_function(tolua_S,"destroyInstance", lua_cocos2dx_csloader_CSLoader_destroyInstance);
        tolua_function(tolua_S,"createNode", lua_cocos2dx_csloader_CSLoader_createNode);
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

