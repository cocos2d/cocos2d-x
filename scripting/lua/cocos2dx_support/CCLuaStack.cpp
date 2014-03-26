/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

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

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua_fix.h"
}

#include "ccMacros.h"
#include "platform/CCFileUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/ios/CCLuaObjcBridge.h"
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "platform/android/CCLuaJavaBridge.h"
#endif

#include "Cocos2dxLuaLoader.h"

// cocos2d-x luabinding
#include "LuaCocos2d.h"

// cocos-extensions
#include "LuaCocoStudio.h"
#include "lua_cocos2dx_manual.h"
#include "lua_cocos2dx_extensions_manual.h"
#include "lua_cocos2dx_cocostudio_manual.h"

#include <string>

using namespace std;

NS_CC_BEGIN

struct cc_timeval CCLuaStack::m_lasttime = {0};
CCLuaStackMap CCLuaStack::s_map;

CCLuaStack *CCLuaStack::create(void)
{
    CCLuaStack *stack = new CCLuaStack();
    stack->init();
    stack->autorelease();
    return stack;
}

CCLuaStack *CCLuaStack::stack(lua_State *L)
{
    CCLuaStackMapIterator it = s_map.find(L);
    if (it != s_map.end())
    {
        return it->second;
    }
    return NULL;
}

CCLuaStack::~CCLuaStack(void)
{
    s_map.erase(s_map.find(m_state));
    lua_close(m_state);
}

bool CCLuaStack::init(void)
{
    CCTime::gettimeofdayCocos2d(&m_lasttime, NULL);
    m_state = lua_open();
    CCAssert(m_state, "create Lua VM failed");

    s_map[m_state] = this;

    luaL_openlibs(m_state);
    toluafix_open(m_state);
    tolua_Cocos2d_open(m_state);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    CCLuaObjcBridge::luaopen_luaoc(m_state);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    CCLuaJavaBridge::luaopen_luaj(m_state);
#endif

    // register lua print
    lua_pushcfunction(m_state, lua_print);
    lua_setglobal(m_state, "print");

    // CocoStudio
    tolua_CocoStudio_open(m_state);
    register_all_cocos2dx_manual(m_state);
    register_all_cocos2dx_extension_manual(m_state);
    register_all_cocos2dx_studio_manual(m_state);
    // add cocos2dx loader
    addLuaLoader(cocos2dx_lua_loader);

    return true;
}

lua_State *CCLuaStack::getLuaState(void)
{
    return m_state;
}

void CCLuaStack::addSearchPath(const char *path)
{
    lua_getglobal(m_state, "package");                                  /* L: package */
    lua_getfield(m_state, -1, "path");                /* get package.path, L: package path */
    const char *cur_path =  lua_tostring(m_state, -1);
    lua_pushfstring(m_state, "%s;%s/?.lua", cur_path, path);            /* L: package path newpath */
    lua_setfield(m_state, -3, "path");          /* package.path = newpath, L: package path */
    lua_pop(m_state, 2);                                                /* L: - */
}

void CCLuaStack::addLuaLoader(lua_CFunction func)
{
    if (!func) return;

    lua_getglobal(m_state, "package");                                  /* L: package */
    lua_getfield(m_state, -1, "loaders");                               /* L: package, loaders */
    lua_pushcfunction(m_state, func);                                   /* L: package, loaders, func */
    for (int i = (int)lua_objlen(m_state, -2) + 1; i > 2; --i)
    {
        lua_rawgeti(m_state, -2, i - 1);                                /* L: package, loaders, func, function */
        lua_rawseti(m_state, -3, i);                                    /* L: package, loaders, func */
    }
    lua_rawseti(m_state, -2, 2);                                        /* L: package, loaders */
    lua_setfield(m_state, -2, "loaders");                               /* L: package */

    lua_pop(m_state, 1);
}

void CCLuaStack::removeScriptObjectByCCObject(CCObject *pObj)
{
    toluafix_remove_ccobject_by_refid(m_state, pObj->m_nLuaID);
}

void CCLuaStack::removeScriptHandler(int nHandler)
{
    toluafix_remove_function_by_refid(m_state, nHandler);
}

int CCLuaStack::executeString(const char *codes)
{
    lua_loadbuffer(m_state, codes, (int)strlen(codes), "");
    return executeFunction(0);
}

int CCLuaStack::executeScriptFile(const char *filename)
{
    CCAssert(filename, "CCLuaStack::executeScriptFile() - invalid filename");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string code("require \"");
    code.append(filename);
    code.append("\"");
    return executeString(code.c_str());
#else
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename);
    unsigned long chunkSize = 0;
    unsigned char *chunk = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "rb", &chunkSize);
    if (lua_loadbuffer(m_state, (const char*)chunk, (int)chunkSize, fullPath.c_str()) == 0)
    {
        return executeFunction(0);
    }
    return 0;
#endif
}

int CCLuaStack::executeGlobalFunction(const char *functionName, int numArgs /* = 0 */)
{
    lua_getglobal(m_state, functionName);       /* query function by name, stack: function */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
        lua_pop(m_state, 1);
        return 0;
    }
    return executeFunction(numArgs);
}

void CCLuaStack::clean(void)
{
    lua_settop(m_state, 0);
}

void CCLuaStack::settop(int top)
{
    lua_settop(m_state, top);
}

void CCLuaStack::copyValue(int index)
{
    lua_pushvalue(m_state, index);
}

void CCLuaStack::pushInt(int intValue)
{
    lua_pushinteger(m_state, intValue);
}

void CCLuaStack::pushFloat(float floatValue)
{
    lua_pushnumber(m_state, floatValue);
}

void CCLuaStack::pushBoolean(bool boolValue)
{
    lua_pushboolean(m_state, boolValue);
}

void CCLuaStack::pushString(const char *stringValue)
{
    lua_pushstring(m_state, stringValue);
}

void CCLuaStack::pushString(const char *stringValue, int length)
{
    lua_pushlstring(m_state, stringValue, length);
}

void CCLuaStack::pushNil(void)
{
    lua_pushnil(m_state);
}

void CCLuaStack::pushCCObject(CCObject *objectValue, const char *typeName)
{
    toluafix_pushusertype_ccobject(m_state, objectValue->m_uID, &objectValue->m_nLuaID, objectValue, typeName);
}

void CCLuaStack::pushCCLuaValue(const CCLuaValue& value)
{
    const CCLuaValueType type = value.getType();
    if (type == CCLuaValueTypeInt)
    {
        return pushInt(value.intValue());
    }
    else if (type == CCLuaValueTypeFloat)
    {
        return pushFloat(value.floatValue());
    }
    else if (type == CCLuaValueTypeBoolean)
    {
        return pushBoolean(value.booleanValue());
    }
    else if (type == CCLuaValueTypeString)
    {
        return pushString(value.stringValue().c_str());
    }
    else if (type == CCLuaValueTypeDict)
    {
        pushCCLuaValueDict(value.dictValue());
    }
    else if (type == CCLuaValueTypeArray)
    {
        pushCCLuaValueArray(value.arrayValue());
    }
    else if (type == CCLuaValueTypeCCObject)
    {
        pushCCObject(value.ccobjectValue(), value.getCCObjectTypename().c_str());
    }
}

void CCLuaStack::pushCCLuaValueDict(const CCLuaValueDict& dict)
{
    lua_newtable(m_state);                                              /* L: table */
    for (CCLuaValueDictIterator it = dict.begin(); it != dict.end(); ++it)
    {
        lua_pushstring(m_state, it->first.c_str());                     /* L: table key */
        pushCCLuaValue(it->second);                                     /* L: table key value */
        lua_rawset(m_state, -3);                     /* table.key = value, L: table */
    }
}

void CCLuaStack::pushCCLuaValueArray(const CCLuaValueArray& array)
{
    lua_newtable(m_state);                                              /* L: table */
    int index = 1;
    for (CCLuaValueArrayIterator it = array.begin(); it != array.end(); ++it)
    {
        pushCCLuaValue(*it);                                            /* L: table value */
        lua_rawseti(m_state, -2, index);          /* table[index] = value, L: table */
        ++index;
    }
}

bool CCLuaStack::pushFunctionByHandler(int nHandler)
{
    toluafix_get_function_by_refid(m_state, nHandler);                  /* L: ... func */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", nHandler);
        lua_pop(m_state, 1);
        return false;
    }
    return true;
}

int CCLuaStack::executeFunction(int numArgs)
{
    ++m_callFromLua;
    int ret = lua_execute(m_state, numArgs, true);
    --m_callFromLua;
    return ret;
}

int CCLuaStack::executeFunctionByHandler(int nHandler, int numArgs)
{
    int ret = 0;
    if (pushFunctionByHandler(nHandler))                                /* L: ... arg1 arg2 ... func */
    {
        if (numArgs > 0)
        {
            lua_insert(m_state, -(numArgs + 1));                        /* L: ... func arg1 arg2 ... */
        }
        ret = executeFunction(numArgs);
    }
    return ret;
}

bool CCLuaStack::handleAssert(const char *msg)
{
    if (m_callFromLua == 0) return false;

    lua_pushfstring(m_state, "ASSERT FAILED ON LUA EXECUTE: %s", msg ? msg : "unknown");
    lua_error(m_state);
    return true;
}

int CCLuaStack::reallocateScriptHandler(int nHandler)
{
    LUA_FUNCTION  nNewHandle = -1;

    if (pushFunctionByHandler(nHandler))
    {
        nNewHandle = toluafix_ref_function(m_state,lua_gettop(m_state),0);
    }
    return nNewHandle;
}

int CCLuaStack::lua_print(lua_State *L)
{
    struct cc_timeval now;

    float deltatime = 0;
    if (CCTime::gettimeofdayCocos2d(&now, NULL) != 0)
    {
        CCLOG("CCLuaStack:lua_print() - error in gettimeofday");
    }
    else
    {
        if (m_lasttime.tv_sec)
        {
            deltatime = now.tv_sec - m_lasttime.tv_sec + (now.tv_usec - m_lasttime.tv_usec) / 1000000.0f;
        }
        else
        {
            m_lasttime = now;
            deltatime = 0;
        }
    }

    int nargs = lua_gettop(L);
    std::string t("[");
    char timestr[32];
    memset(timestr, 0, sizeof(timestr));
    sprintf(timestr, "%.4f", deltatime);
    t += timestr;
    t += "] ";
    for (int i=1; i <= nargs; i++)
    {
        if (lua_istable(L, i))
            t += "table";
        else if (lua_isnone(L, i))
            t += "none";
        else if (lua_isnil(L, i))
            t += "nil";
        else if (lua_isboolean(L, i))
        {
            if (lua_toboolean(L, i) != 0)
                t += "true";
            else
                t += "false";
        }
        else if (lua_isfunction(L, i))
            t += "function";
        else if (lua_islightuserdata(L, i))
            t += "lightuserdata";
        else if (lua_isthread(L, i))
            t += "thread";
        else
        {
            const char * str = lua_tostring(L, i);
            if (str)
                t += lua_tostring(L, i);
            else
                t += lua_typename(L, lua_type(L, i));
        }
        if (i!=nargs)
            t += "  ";
    }
    CCLuaLog(t.c_str());

    return 0;
}

int CCLuaStack::lua_execute(lua_State *L, int numArgs, bool removeResult)
{
    int functionIndex = -(numArgs + 1);
    if (!lua_isfunction(L, functionIndex))
    {
        CCLOG("value at stack [%d] is not function", functionIndex);
        lua_pop(L, numArgs + 1); // remove function and arguments
        return 0;
    }

    int traceback = 0;
    lua_getglobal(L, "__G__TRACKBACK__");                         /* L: ... func arg1 arg2 ... G */
    if (!lua_isfunction(L, -1))
    {
        lua_pop(L, 1);                                            /* L: ... func arg1 arg2 ... */
    }
    else
    {
        lua_insert(L, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
        traceback = functionIndex - 1;
    }

    int error = 0;
    error = lua_pcall(L, numArgs, 1, traceback);                  /* L: ... [G] ret */
    if (error)
    {
        if (traceback == 0)
        {
            CCLOG("[LUA ERROR] %s", lua_tostring(L, - 1));        /* L: ... error */
            lua_pop(L, 1); // remove error message from stack
        }
        else                                                            /* L: ... G error */
        {
            lua_pop(L, 2); // remove __G__TRACKBACK__ and error message from stack
        }
        return 0;
    }

    int ret = 0;
    if (removeResult)
    {
        if (lua_isnumber(L, -1))
        {
            ret = (int)lua_tointeger(L, -1);
        }
        else if (lua_isboolean(L, -1))
        {
            ret = lua_toboolean(L, -1);
        }
        // remove return value from stack
        lua_pop(L, 1);                                            /* L: ... [G] */
    }
    else
    {
        ret = 1;
    }

    if (traceback)
    {
        lua_remove(L, removeResult ? -1 : -2);
    }

    return ret;
}

int CCLuaStack::lua_loadbuffer(lua_State *L, const char *chunk, int chunkSize, const char *chunkName)
{
    int r = luaL_loadbuffer(L, chunk, chunkSize, chunkName);

#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
    if (r)
    {
        switch (r)
        {
            case LUA_ERRSYNTAX:
                CCLOG("[LUA ERROR] load \"%s\", error: syntax error during pre-compilation.", chunkName);
                break;

            case LUA_ERRMEM:
                CCLOG("[LUA ERROR] load \"%s\", error: memory allocation error.", chunkName);
                break;

            case LUA_ERRFILE:
                CCLOG("[LUA ERROR] load \"%s\", error: cannot open/read file.", chunkName);
                break;

            default:
                CCLOG("[LUA ERROR] load \"%s\", error: unknown.", chunkName);
        }
    }
#endif
    return r;
}

int CCLuaStack::executeFunctionReturnArray(int nHandler,int nNumArgs,int nNummResults,CCArray* pResultArray)
{
    if (NULL == pResultArray)
        return 0;

    if (pushFunctionByHandler(nHandler))                 /* L: ... arg1 arg2 ... func */
    {
        if (nNumArgs > 0)
        {
            lua_insert(m_state, -(nNumArgs + 1));         /* L: ... func arg1 arg2 ... */
            int functionIndex = -(nNumArgs + 1);
            if (!lua_isfunction(m_state, functionIndex))
            {
                CCLOG("value at stack [%d] is not function", functionIndex);
                lua_pop(m_state, nNumArgs + 1); // remove function and arguments
                return 0;
            }

            int traceback = 0;
            lua_getglobal(m_state, "__G__TRACKBACK__");                         /* L: ... func arg1 arg2 ... G */
            if (!lua_isfunction(m_state, -1))
            {
                lua_pop(m_state, 1);                                            /* L: ... func arg1 arg2 ... */
            }
            else
            {
                lua_insert(m_state, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
                traceback = functionIndex - 1;
            }

            int error = 0;
            ++m_callFromLua;
            error = lua_pcall(m_state, nNumArgs, nNummResults, traceback);                  /* L: ... [G] ret1 ret2 ... retResults*/
            --m_callFromLua;
            if (error)
            {
                if (traceback == 0)
                {
                    CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));        /* L: ... error */
                    lua_pop(m_state, 1); // remove error message from stack
                }
                else                                                            /* L: ... G error */
                {
                    lua_pop(m_state, 2); // remove __G__TRACKBACK__ and error message from stack
                }
                return 0;
            }

            // get return value,don't pass LUA_MULTRET to numResults,
            if (nNummResults <= 0)
                return 0;

            for (int i = 0 ; i < nNummResults; i++)
            {
                if (lua_type(m_state, -1) == LUA_TBOOLEAN) {

                    bool value = lua_toboolean(m_state, -1);
                    pResultArray->addObject(CCBool::create(value)) ;

                }else if (lua_type(m_state, -1) == LUA_TNUMBER) {

                    double value = lua_tonumber(m_state, -1);
                    pResultArray->addObject(CCDouble::create(value));

                }else if (lua_type(m_state, -1) == LUA_TSTRING) {

                    const char *value = lua_tostring(m_state, -1);
                    pResultArray->addObject(CCString::create(value));

                }else{

                    pResultArray->addObject(static_cast<CCObject*>(tolua_tousertype(m_state, -1, NULL)));
                }
                // remove return value from stack
                lua_pop(m_state, 1);                                                /* L: ... [G] ret1 ret2 ... ret*/
            }
            /* L: ... [G]*/

            if (traceback)
            {
                lua_pop(m_state, 1); // remove __G__TRACKBACK__ from stack      /* L: ... */
            }
        }
    }

    lua_settop(m_state, 0);

    return 1;
}

NS_CC_END


USING_NS_CC;

static map<unsigned int, char*> hash_type_mapping;
TOLUA_API void toluafix_add_type_mapping(size_t type,const char *clsName)
{

    if(hash_type_mapping.find(type) == hash_type_mapping.end())
    {
        hash_type_mapping[type] = strdup(clsName);
    }
}

TOLUA_API int toluafix_pushusertype_ccobject(lua_State *L,
                                             int refid,
                                             int *p_refid,
                                             void *vptr,
                                             const char *vtype)
{
    if (vptr == NULL || p_refid == NULL)
    {
        lua_pushnil(L);
        return -1;
    }

    CCObject *ptr = static_cast<CCObject*>(vptr);
    unsigned int hash = hash_code(typeid(*ptr));
    char* type = hash_type_mapping[hash];
    if (type == NULL)
    {
        // CCLOG("[TOLUA] Unable to find type map for object %s:%p,", vtype, vptr);
    }

    if (*p_refid == 0)
    {
        *p_refid = refid;

        lua_pushstring(L, TOLUA_REFID_PTR_MAPPING);
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: refid_ptr */
        lua_pushinteger(L, refid);                                  /* stack: refid_ptr refid */
        lua_pushlightuserdata(L, ptr);                              /* stack: refid_ptr refid ptr */

        lua_rawset(L, -3);                  /* refid_ptr[refid] = ptr, stack: refid_ptr */
        lua_pop(L, 1);                                              /* stack: - */

        lua_pushstring(L, TOLUA_REFID_TYPE_MAPPING);
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: refid_type */
        lua_pushinteger(L, refid);                                  /* stack: refid_type refid */
        lua_pushstring(L, type ? type : vtype);                     /* stack: refid_type refid type */
        lua_rawset(L, -3);                /* refid_type[refid] = type, stack: refid_type */
        lua_pop(L, 1);                                              /* stack: - */

        //printf("[LUA] push CCObject OK - refid: %d, ptr: %x, type: %s\n", *p_refid, (int)ptr, type);
    }

    tolua_pushusertype_and_addtoroot(L, ptr, type ? type : vtype);
    return 0;
}
