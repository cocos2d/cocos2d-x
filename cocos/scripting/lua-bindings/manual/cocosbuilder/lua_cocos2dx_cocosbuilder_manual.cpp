/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "scripting/lua-bindings/manual/cocosbuilder/lua_cocos2dx_cocosbuilder_manual.h"
#include "scripting/lua-bindings/auto/lua_cocos2dx_cocosbuilder_auto.hpp"
#include "cocos2d.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/cocosbuilder/CCBProxy.h"

USING_NS_CC;
USING_NS_CC_EXT;

static int tolua_cocos2d_CCBProxy_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        CCBProxy* tolua_ret = (CCBProxy*)CCBProxy::create();        
        int  nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int *pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.CCBProxy");
        return 1;
    }
    
    luaL_error(tolua_S, "%s function of CCBProxy has wrong number of arguments: %d, was expecting %d\n", "cc.CCBProxy:create", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CCBProxy_create'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_CCBProxy_createCCBReader(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    CCBProxy* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBProxy*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBProxy_createCCBReader'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        CCBReader* tolua_ret = (CCBReader*) self->createCCBReader();
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.CCBReader");
        return 1;
    }
    
    luaL_error(tolua_S, "%s function of CCBProxy  has wrong number of arguments: %d, was expecting %d\n", "cc.CCBProxy:createCCBReader", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CCBProxy_createCCBReader'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_CCBProxy_readCCBFromFile(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    CCBProxy* self = nullptr;
    const char* ccbFilePath = nullptr;
    CCBReader*  ccbReader   = nullptr;
    bool        setOwner    = false;
    Node*       tolua_ret    = nullptr;
    int         ID          = 0;
    int*        luaID       = nullptr;
    
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBProxy*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBProxy_readCCBFromFile'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (2 == argc || 3 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S, 2, 0, &tolua_err)||
            !tolua_isusertype(tolua_S,3,"cc.CCBReader",0,&tolua_err)||
            !tolua_isboolean(tolua_S,4,1,&tolua_err )
            )
            goto tolua_lerror;
#endif
        ccbFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
        ccbReader   = ((CCBReader*)  tolua_tousertype(tolua_S,3,0));
        setOwner = (bool)  tolua_toboolean(tolua_S,4,-1);
        tolua_ret = (Node*) self->readCCBFromFile(ccbFilePath, ccbReader, setOwner);
        ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.Node");
        return 1;
    }
    
    luaL_error(tolua_S, "%s function of CCBProxy  has wrong number of arguments: %d, was expecting %d\n", "cc.CCBReader:readCCBFromFile", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CCBProxy_readCCBFromFile'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_CCBProxy_getNodeTypeName(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    CCBProxy* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBProxy*>(tolua_tousertype(tolua_S,1,0));
  
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBProxy_getNodeTypeName'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
        
        Node* node = static_cast<Node*>(tolua_tousertype(tolua_S,2,0));
        const char* tolua_ret = (const char*)self->getNodeTypeName(node);
        tolua_pushstring(tolua_S,(const char*)tolua_ret);
        return 1;
    }
    
    luaL_error(tolua_S, " %s has wrong number of arguments: %d, was expecting %d\n", "cc.CCBProxy:getNodeTypeName", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CCBProxy_getNodeTypeName'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_CCBProxy_setCallback(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    CCBProxy* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBProxy*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBProxy_setCallback'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if ( argc >= 2 && argc <= 3 )
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err) ||
            !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 4, 1, &tolua_err)
            )
            goto tolua_lerror;
#endif
        
        Node* node = ((Node*)tolua_tousertype(tolua_S,2,0));
        LUA_FUNCTION funID = (  toluafix_ref_function(tolua_S,3,0));
        int   controlEvents = (int)tolua_tonumber(tolua_S, 4, 1);
        self->setCallback(node, funID, controlEvents);
        return 0;
    }
    
    luaL_error(tolua_S, " %s has wrong number of arguments: %d, was expecting %d\n", "cc.CCBProxy:setCallback", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CCBProxy_setCallback'.",&tolua_err);
    return 0;
#endif
}

int register_cocos2dx_extension_CCBProxy(lua_State* tolua_S)
{
    tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");
    tolua_usertype(tolua_S,"cc.CCBProxy");
    tolua_cclass(tolua_S,"CCBProxy","cc.CCBProxy","cc.Layer",NULL);
    tolua_beginmodule(tolua_S,"CCBProxy");
    tolua_function(tolua_S, "create", tolua_cocos2d_CCBProxy_create);
    tolua_function(tolua_S, "createCCBReader", tolua_cocos2d_CCBProxy_createCCBReader);
    tolua_function(tolua_S, "readCCBFromFile", tolua_cocos2d_CCBProxy_readCCBFromFile);
    tolua_function(tolua_S, "getNodeTypeName", tolua_cocos2d_CCBProxy_getNodeTypeName);
    tolua_function(tolua_S, "setCallback", tolua_cocos2d_CCBProxy_setCallback);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    
    std::string typeName = typeid(CCBProxy).name();
    g_luaType[typeName] = "cc.CCBProxy";
    return 1;
}

static int tolua_cocos2d_CCBReader_load(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    CCBReader* self = nullptr;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBReader*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBReader_load'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >= 1 && argc <= 3)
    {
        const char* fileName = nullptr;
        std::string fileName_tmp = "";
        ok &= luaval_to_std_string(tolua_S, 2, &fileName_tmp, "cc.CCBReader:load");
        fileName = fileName_tmp.c_str();
        if (!ok)
            return 0;
        
        if (1 == argc)
        {
            Node* tolua_ret = (Node*) self->readNodeGraphFromFile(fileName);
            int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.Node");
            return 1;
        }
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S, 3, "cc.Ref", 0, &tolua_err))
            goto tolua_lerror;
#endif
        Ref* owner = static_cast<Ref*>(tolua_tousertype(tolua_S, 3, 0));
        //In lua owner always define in lua script by table, so owner is always nullptr
        if (2 == argc)
        {
            Node* tolua_ret = (Node*) self->readNodeGraphFromFile(fileName,owner);
            int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.Node");
            return 1;
        }
        
        Size size;
        ok &= luaval_to_size(tolua_S, 4, &size, "cc.CCBReader:load");
        if (!ok)
            return 0;
        
        Node* tolua_ret = (Node*) self->readNodeGraphFromFile(fileName,owner,size);
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.Node");
        return 1;
        
    }
    
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.CCBReader:load",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CCBReader_load'.",&tolua_err);
    return 0;
#endif
}

static void extendCCBReader(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.CCBReader");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"load");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CCBReader_load );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}


static int tolua_cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    CCBAnimationManager* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBAnimationManager*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (2 == argc)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2, "cc.CallFunc", 0, &tolua_err) ||
            !tolua_isstring(tolua_S, 3, 0, &tolua_err) )
            goto tolua_lerror;
#endif
        
        CallFunc* pCallFunc = static_cast<CallFunc*>(tolua_tousertype(tolua_S,2,0));
        const char* keyframeCallback = ((const char*)  tolua_tostring(tolua_S,3,0));
        std::string strKey = "";
        if (NULL != keyframeCallback) {
            strKey = keyframeCallback;
        }
        self->setCallFunc(pCallFunc, strKey);
        
        return 0;
    }
    
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.CCBAnimationManager:setCallFuncForLuaCallbackNamed",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed'.",&tolua_err);
    return 0;
#endif
}

static void extendCCBAnimationManager(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.CCBAnimationManager");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setCallFuncForLuaCallbackNamed");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

int register_all_cocos2dx_cocosbuilder_manual(lua_State* tolua_S)
{
    register_cocos2dx_extension_CCBProxy(tolua_S);
    extendCCBReader(tolua_S);
    extendCCBAnimationManager(tolua_S);
    return 0;
}


int register_cocosbuilder_module(lua_State* tolua_S)
{
    lua_getglobal(tolua_S, "_G");
    if (lua_istable(tolua_S,-1))//stack:...,_G,
    {
        register_all_cocos2dx_cocosbuilder(tolua_S);
        register_all_cocos2dx_cocosbuilder_manual(tolua_S);
    }
    lua_pop(tolua_S, 1);
    return 1;
}
