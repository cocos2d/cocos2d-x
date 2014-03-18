/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
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

#include "CCLuaStack.h"
#include "tolua_fix.h"
extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "lualib.h"
#include "lauxlib.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "lua_extensions.h"
#endif
}

#include "Cocos2dxLuaLoader.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/ios/CCLuaObjcBridge.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/CCLuaJavaBridge.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Lua_web_socket.h"
#endif
#include "LuaOpengl.h"
#include "LuaScriptHandlerMgr.h"
#include "lua_cocos2dx_auto.hpp"
#include "lua_cocos2dx_extension_auto.hpp"
#include "lua_cocos2dx_manual.hpp"
#include "LuaBasicConversions.h"
#include "lua_cocos2dx_extension_manual.h"
#include "lua_cocos2dx_deprecated.h"
#include "lua_xml_http_request.h"
#include "lua_cocos2dx_studio_auto.hpp"
#include "lua_cocos2dx_coco_studio_manual.hpp"
#include "lua_cocos2dx_spine_auto.hpp"
#include "lua_cocos2dx_spine_manual.hpp"
#include "lua_cocos2dx_physics_auto.hpp"
#include "lua_cocos2dx_physics_manual.hpp"
#include "lua_cocos2dx_ui_auto.hpp"
#include "lua_cocos2dx_ui_manual.hpp"

namespace {
int lua_print(lua_State * luastate)
{
    int nargs = lua_gettop(luastate);

    std::string t;
    for (int i=1; i <= nargs; i++)
    {
        if (lua_istable(luastate, i))
            t += "table";
        else if (lua_isnone(luastate, i))
            t += "none";
        else if (lua_isnil(luastate, i))
            t += "nil";
        else if (lua_isboolean(luastate, i))
        {
            if (lua_toboolean(luastate, i) != 0)
                t += "true";
            else
                t += "false";
        }
        else if (lua_isfunction(luastate, i))
            t += "function";
        else if (lua_islightuserdata(luastate, i))
            t += "lightuserdata";
        else if (lua_isthread(luastate, i))
            t += "thread";
        else
        {
            const char * str = lua_tostring(luastate, i);
            if (str)
                t += lua_tostring(luastate, i);
            else
                t += lua_typename(luastate, lua_type(luastate, i));
        }
        if (i!=nargs)
            t += "\t";
    }
    CCLOG("[LUA-print] %s", t.c_str());

    return 0;
}
}  // namespace {

NS_CC_BEGIN

LuaStack::~LuaStack()
{
    if (nullptr != _state)
    {
        lua_close(_state);
    }
}

LuaStack *LuaStack::create(void)
{
    LuaStack *stack = new LuaStack();
    stack->init();
    stack->autorelease();
    return stack;
}

LuaStack *LuaStack::attach(lua_State *L)
{
    LuaStack *stack = new LuaStack();
    stack->initWithLuaState(L);
    stack->autorelease();
    return stack;
}

bool LuaStack::init(void)
{
    _state = lua_open();
    luaL_openlibs(_state);
    toluafix_open(_state);

    // Register our version of the global "print" function
    const luaL_reg global_functions [] = {
        {"print", lua_print},
        {NULL, NULL}
    };
    luaL_register(_state, "_G", global_functions);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    luaopen_lua_extensions(_state);
#endif
    g_luaType.clear();
    register_all_cocos2dx(_state);
    register_all_cocos2dx_extension(_state);
    register_all_cocos2dx_deprecated(_state);
    register_cocos2dx_extension_CCBProxy(_state);
    tolua_opengl_open(_state);
    register_all_cocos2dx_ui(_state);
    register_all_cocos2dx_studio(_state);
    register_all_cocos2dx_manual(_state);
    register_all_cocos2dx_extension_manual(_state);
    register_all_cocos2dx_manual_deprecated(_state);
    register_all_cocos2dx_coco_studio_manual(_state);
    register_all_cocos2dx_ui_manual(_state);
    register_all_cocos2dx_spine(_state);
    register_all_cocos2dx_spine_manual(_state);
    register_glnode_manual(_state);
#if CC_USE_PHYSICS
    register_all_cocos2dx_physics(_state);
    register_all_cocos2dx_physics_manual(_state);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    LuaObjcBridge::luaopen_luaoc(_state);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    LuaJavaBridge::luaopen_luaj(_state);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    tolua_web_socket_open(_state);
    register_web_socket_manual(_state);
#endif
    
    register_xml_http_request(_state);
    
    tolua_script_handler_mgr_open(_state);

    // add cocos2dx loader
    addLuaLoader(cocos2dx_lua_loader);

    return true;
}

bool LuaStack::initWithLuaState(lua_State *L)
{
    _state = L;
    return true;
}

void LuaStack::addSearchPath(const char* path)
{
    lua_getglobal(_state, "package");                                  /* L: package */
    lua_getfield(_state, -1, "path");                /* get package.path, L: package path */
    const char* cur_path =  lua_tostring(_state, -1);
    lua_pushfstring(_state, "%s;%s/?.lua", cur_path, path);            /* L: package path newpath */
    lua_setfield(_state, -3, "path");          /* package.path = newpath, L: package path */
    lua_pop(_state, 2);                                                /* L: - */
}

void LuaStack::addLuaLoader(lua_CFunction func)
{
    if (!func) return;
    
    // stack content after the invoking of the function
    // get loader table
    lua_getglobal(_state, "package");                                  /* L: package */
    lua_getfield(_state, -1, "loaders");                               /* L: package, loaders */
    
    // insert loader into index 2
    lua_pushcfunction(_state, func);                                   /* L: package, loaders, func */
    for (int i = lua_objlen(_state, -2) + 1; i > 2; --i)
    {
        lua_rawgeti(_state, -2, i - 1);                                /* L: package, loaders, func, function */
        // we call lua_rawgeti, so the loader table now is at -3
        lua_rawseti(_state, -3, i);                                    /* L: package, loaders, func */
    }
    lua_rawseti(_state, -2, 2);                                        /* L: package, loaders */
    
    // set loaders into package
    lua_setfield(_state, -2, "loaders");                               /* L: package */
    
    lua_pop(_state, 1);
}


void LuaStack::removeScriptObjectByObject(Ref* pObj)
{
    toluafix_remove_ccobject_by_refid(_state, pObj->_luaID);
}

void LuaStack::removeScriptHandler(int nHandler)
{
    toluafix_remove_function_by_refid(_state, nHandler);
}

int LuaStack::executeString(const char *codes)
{
    luaL_loadstring(_state, codes);
    return executeFunction(0);
}

int LuaStack::executeScriptFile(const char* filename)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string code("require \"");
    code.append(filename);
    code.append("\"");
    return executeString(code.c_str());
#else
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
    ++_callFromLua;
    int nRet = luaL_dofile(_state, fullPath.c_str());
    --_callFromLua;
    CC_ASSERT(_callFromLua >= 0);
    // lua_gc(_state, LUA_GCCOLLECT, 0);
    
    if (nRet != 0)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(_state, -1));
        lua_pop(_state, 1);
        return nRet;
    }
    return 0;
#endif
}

int LuaStack::executeGlobalFunction(const char* functionName)
{
    lua_getglobal(_state, functionName);       /* query function by name, stack: function */
    if (!lua_isfunction(_state, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
        lua_pop(_state, 1);
        return 0;
    }
    return executeFunction(0);
}

void LuaStack::clean(void)
{
    lua_settop(_state, 0);
}

void LuaStack::pushInt(int intValue)
{
    lua_pushinteger(_state, intValue);
}

void LuaStack::pushFloat(float floatValue)
{
    lua_pushnumber(_state, floatValue);
}

void LuaStack::pushLong(long longValue)
{
    lua_pushnumber(_state, longValue);
}

void LuaStack::pushBoolean(bool boolValue)
{
    lua_pushboolean(_state, boolValue);
}

void LuaStack::pushString(const char* stringValue)
{
    lua_pushstring(_state, stringValue);
}

void LuaStack::pushString(const char* stringValue, int length)
{
    lua_pushlstring(_state, stringValue, length);
}

void LuaStack::pushNil(void)
{
    lua_pushnil(_state);
}

void LuaStack::pushObject(Ref* objectValue, const char* typeName)
{
    toluafix_pushusertype_ccobject(_state, objectValue->_ID, &objectValue->_luaID, objectValue, typeName);
}

void LuaStack::pushLuaValue(const LuaValue& value)
{
    const LuaValueType type = value.getType();
    if (type == LuaValueTypeInt)
    {
        return pushInt(value.intValue());
    }
    else if (type == LuaValueTypeFloat)
    {
        return pushFloat(value.floatValue());
    }
    else if (type == LuaValueTypeBoolean)
    {
        return pushBoolean(value.booleanValue());
    }
    else if (type == LuaValueTypeString)
    {
        return pushString(value.stringValue().c_str());
    }
    else if (type == LuaValueTypeDict)
    {
        pushLuaValueDict(value.dictValue());
    }
    else if (type == LuaValueTypeArray)
    {
        pushLuaValueArray(value.arrayValue());
    }
    else if (type == LuaValueTypeObject)
    {
        pushObject(value.ccobjectValue(), value.getObjectTypename().c_str());
    }
}

void LuaStack::pushLuaValueDict(const LuaValueDict& dict)
{
    lua_newtable(_state);                                              /* L: table */
    for (LuaValueDictIterator it = dict.begin(); it != dict.end(); ++it)
    {
        lua_pushstring(_state, it->first.c_str());                     /* L: table key */
        pushLuaValue(it->second);                                     /* L: table key value */
        lua_rawset(_state, -3);                     /* table.key = value, L: table */
    }
}

void LuaStack::pushLuaValueArray(const LuaValueArray& array)
{
    lua_newtable(_state);                                              /* L: table */
    int index = 1;
    for (LuaValueArrayIterator it = array.begin(); it != array.end(); ++it)
    {
        pushLuaValue(*it);                                            /* L: table value */
        lua_rawseti(_state, -2, index);          /* table[index] = value, L: table */
        ++index;
    }
}

bool LuaStack::pushFunctionByHandler(int nHandler)
{
    toluafix_get_function_by_refid(_state, nHandler);                  /* L: ... func */
    if (!lua_isfunction(_state, -1))
    {
        CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", nHandler);
        lua_pop(_state, 1);
        return false;
    }
    return true;
}

int LuaStack::executeFunction(int numArgs)
{
    int functionIndex = -(numArgs + 1);
    if (!lua_isfunction(_state, functionIndex))
    {
        CCLOG("value at stack [%d] is not function", functionIndex);
        lua_pop(_state, numArgs + 1); // remove function and arguments
        return 0;
    }

    int traceback = 0;
    lua_getglobal(_state, "__G__TRACKBACK__");                         /* L: ... func arg1 arg2 ... G */
    if (!lua_isfunction(_state, -1))
    {
        lua_pop(_state, 1);                                            /* L: ... func arg1 arg2 ... */
    }
    else
    {
        lua_insert(_state, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
        traceback = functionIndex - 1;
    }
    
    int error = 0;
    ++_callFromLua;
    error = lua_pcall(_state, numArgs, 1, traceback);                  /* L: ... [G] ret */
    --_callFromLua;
    if (error)
    {
        if (traceback == 0)
        {
            CCLOG("[LUA ERROR] %s", lua_tostring(_state, - 1));        /* L: ... error */
            lua_pop(_state, 1); // remove error message from stack
        }
        else                                                            /* L: ... G error */
        {
            lua_pop(_state, 2); // remove __G__TRACKBACK__ and error message from stack
        }
        return 0;
    }
    
    // get return value
    int ret = 0;
    if (lua_isnumber(_state, -1))
    {
        ret = lua_tointeger(_state, -1);
    }
    else if (lua_isboolean(_state, -1))
    {
        ret = lua_toboolean(_state, -1);
    }
    // remove return value from stack
    lua_pop(_state, 1);                                                /* L: ... [G] */
    
    if (traceback)
    {
        lua_pop(_state, 1); // remove __G__TRACKBACK__ from stack      /* L: ... */
    }
    
    return ret;
}

int LuaStack::executeFunctionByHandler(int nHandler, int numArgs)
{
    int ret = 0;
    if (pushFunctionByHandler(nHandler))                                /* L: ... arg1 arg2 ... func */
    {
        if (numArgs > 0)
        {
            lua_insert(_state, -(numArgs + 1));                        /* L: ... func arg1 arg2 ... */
        }
        ret = executeFunction(numArgs);
    }
    lua_settop(_state, 0);
    return ret;
}

bool LuaStack::handleAssert(const char *msg)
{
    if (_callFromLua == 0) return false;
    
    lua_pushfstring(_state, "ASSERT FAILED ON LUA EXECUTE: %s", msg ? msg : "unknown");
    lua_error(_state);
    return true;
}

int LuaStack::reallocateScriptHandler(int nHandler)
{
    LUA_FUNCTION  nNewHandle = -1;
    
    if (pushFunctionByHandler(nHandler))
    {
       nNewHandle = toluafix_ref_function(_state,lua_gettop(_state),0);
    }
/*
    toluafix_get_function_by_refid(_state,nNewHandle);
    if (!lua_isfunction(_state, -1))
    {
        CCLOG("Error!");
    }
    lua_settop(_state, 0);
*/
    return nNewHandle;

}

int LuaStack::executeFunctionReturnArray(int handler,int numArgs,int numResults,__Array& resultArray)
{
    if (pushFunctionByHandler(handler))                 /* L: ... arg1 arg2 ... func */
    {
        if (numArgs > 0)
        {
            lua_insert(_state, -(numArgs + 1));         /* L: ... func arg1 arg2 ... */
            int functionIndex = -(numArgs + 1);
            if (!lua_isfunction(_state, functionIndex))
            {
                CCLOG("value at stack [%d] is not function", functionIndex);
                lua_pop(_state, numArgs + 1); // remove function and arguments
                return 0;
            }
            
            int traceback = 0;
            lua_getglobal(_state, "__G__TRACKBACK__");                         /* L: ... func arg1 arg2 ... G */
            if (!lua_isfunction(_state, -1))
            {
                lua_pop(_state, 1);                                            /* L: ... func arg1 arg2 ... */
            }
            else
            {
                lua_insert(_state, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
                traceback = functionIndex - 1;
            }
            
            int error = 0;
            ++_callFromLua;
            error = lua_pcall(_state, numArgs, numResults, traceback);                  /* L: ... [G] ret1 ret2 ... retResults*/
            --_callFromLua;
            if (error)
            {
                if (traceback == 0)
                {
                    CCLOG("[LUA ERROR] %s", lua_tostring(_state, - 1));        /* L: ... error */
                    lua_pop(_state, 1); // remove error message from stack
                }
                else                                                            /* L: ... G error */
                {
                    lua_pop(_state, 2); // remove __G__TRACKBACK__ and error message from stack
                }
                return 0;
            }
            
            // get return value,don't pass LUA_MULTRET to numResults,
            if (numResults <= 0)
                return 0;
            
            for (int i = 0 ; i < numResults; i++)
            {
                if (lua_type(_state, -1) == LUA_TBOOLEAN) {
                    
                    bool value = lua_toboolean(_state, -1);
                    resultArray.addObject(Bool::create(value)) ;
                    
                }else if (lua_type(_state, -1) == LUA_TNUMBER) {
                    
                    double value = lua_tonumber(_state, -1);
                    resultArray.addObject(Double::create(value));
                    
                }else if (lua_type(_state, -1) == LUA_TSTRING) {
                    
                    const char* value = lua_tostring(_state, -1);
                    resultArray.addObject(String::create(value));
                    
                }else{
                    
                    resultArray.addObject(static_cast<Ref*>(tolua_tousertype(_state, -1, NULL)));
                }
                // remove return value from stack
                lua_pop(_state, 1);                                                /* L: ... [G] ret1 ret2 ... ret*/
            }
            /* L: ... [G]*/
            
            if (traceback)
            {
                lua_pop(_state, 1); // remove __G__TRACKBACK__ from stack      /* L: ... */
            }
        }
    }
    lua_settop(_state, 0);
    return 1;
}

int LuaStack::executeFunction(int handler, int numArgs, int numResults, const std::function<void(lua_State*,int)>& func)
{
    if (pushFunctionByHandler(handler))                 /* L: ... arg1 arg2 ... func */
    {
        if (numArgs > 0)
        {
            lua_insert(_state, -(numArgs + 1));                        /* L: ... func arg1 arg2 ... */
        }
        
        int functionIndex = -(numArgs + 1);
        
        if (!lua_isfunction(_state, functionIndex))
        {
            CCLOG("value at stack [%d] is not function", functionIndex);
            lua_pop(_state, numArgs + 1); // remove function and arguments
            return 0;
        }
        
        int traceCallback = 0;
        lua_getglobal(_state, "__G__TRACKBACK__");                        /* L: ... func arg1 arg2 ... G */
        if (!lua_isfunction(_state, -1))
        {
            lua_pop(_state, 1);                                           /* L: ... func arg1 arg2 ... */
        }
        else
        {
            lua_insert(_state, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
            traceCallback = functionIndex - 1;
        }
        
        int error = 0;
        ++_callFromLua;
        error = lua_pcall(_state, numArgs, numResults, traceCallback);     /* L: ... [G] ret1 ret2 ... retResults*/
        --_callFromLua;
        
        if (error)
        {
            if (traceCallback == 0)
            {
                CCLOG("[LUA ERROR] %s", lua_tostring(_state, - 1));        /* L: ... error */
                lua_pop(_state, 1);                                        // remove error message from stack
            }
            else                                                           /* L: ... G error */
            {
                lua_pop(_state, 2);                                        // remove __G__TRACKBACK__ and error message from stack
            }
            return 0;
        }
        
        // get return value,don't pass LUA_MULTRET to numResults,
        do {
            
            if (numResults <= 0 || nullptr == func)
                break;
            
            func(_state, numResults);
            
        } while (0);
        
        if (traceCallback)
        {
            lua_pop(_state, 1);                                          // remove __G__TRACKBACK__ from stack      /* L: ... */
        }
    }
    
    return 1;
}

int LuaStack::reload(const char* moduleFileName)
{
    if (nullptr == moduleFileName || strlen(moduleFileName) == 0)
    {
        CCLOG("moudulFileName is null");
        return 1;
    }

    lua_getglobal(_state, "package");                         /* L: package */
    lua_getfield(_state, -1, "loaded");                       /* L: package loaded */
    lua_pushstring(_state, moduleFileName);
    lua_gettable(_state, -2);                                 /* L:package loaded module */
    if (!lua_isnil(_state, -1))
    {
        lua_pushstring(_state, moduleFileName);               /* L:package loaded module name */
        lua_pushnil(_state);                                  /* L:package loaded module name nil*/
        lua_settable(_state, -4);                             /* L:package loaded module */
    }
    lua_pop(_state, 3);
    
    std::string name = moduleFileName;
    std::string require = "require \'" + name + "\'";
    return executeString(require.c_str());
}

NS_CC_END
