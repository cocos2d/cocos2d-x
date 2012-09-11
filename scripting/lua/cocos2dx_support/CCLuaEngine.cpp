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

#include "CCLuaEngine.h"
#include "tolua++.h"

extern "C" {
#include "lualib.h"
#include "lauxlib.h"
#include "tolua_fix.h"
}

#include "cocos2d.h"
#include "LuaCocos2d.h"
#include "cocoa/CCArray.h"
#include "CCScheduler.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Cocos2dxLuaLoader.h"
#endif

NS_CC_BEGIN

// #pragma mark -
// #pragma mark CCScriptValue

const CCScriptValue CCScriptValue::intValue(const int intValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeInt;
    value.m_field.intValue = intValue;
    return value;
}

const CCScriptValue CCScriptValue::floatValue(const float floatValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeFloat;
    value.m_field.floatValue = floatValue;
    return value;
}

const CCScriptValue CCScriptValue::booleanValue(const bool booleanValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeBoolean;
    value.m_field.booleanValue = booleanValue;
    return value;
}

const CCScriptValue CCScriptValue::stringValue(const char* stringValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeString;
    value.m_field.stringValue = new std::string(stringValue);
    return value;
}

const CCScriptValue CCScriptValue::stringValue(const std::string& stringValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeString;
    value.m_field.stringValue = new std::string(stringValue);
    return value;
}

const CCScriptValue CCScriptValue::dictValue(const CCScriptValueDict& dictValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeDict;
    value.m_field.dictValue = new CCScriptValueDict(dictValue);
    return value;
}

const CCScriptValue CCScriptValue::arrayValue(const CCScriptValueArray& arrayValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeArray;
    value.m_field.arrayValue = new CCScriptValueArray(arrayValue);
    return value;
}

const CCScriptValue CCScriptValue::ccobjectValue(CCObject* ccobjectValue, const char* objectTypename)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeCCObject;
    value.m_field.ccobjectValue = ccobjectValue;
    ccobjectValue->retain();
    value.m_ccobjectType = new std::string(objectTypename);
    return value;
}

const CCScriptValue CCScriptValue::ccobjectValue(CCObject* ccobjectValue, const std::string& objectTypename)
{
    return CCScriptValue::ccobjectValue(ccobjectValue, objectTypename.c_str());
}

CCScriptValue::CCScriptValue(const CCScriptValue& rhs)
{
    copy(rhs);
}

CCScriptValue& CCScriptValue::operator=(const CCScriptValue& rhs)
{
    if (this != &rhs) copy(rhs);
    return *this;
}

CCScriptValue::~CCScriptValue(void)
{
    if (m_type == CCScriptValueTypeString)
    {
        delete m_field.stringValue;
    }
    else if (m_type == CCScriptValueTypeDict)
    {
        delete m_field.dictValue;
    }
    else if (m_type == CCScriptValueTypeArray)
    {
        delete m_field.arrayValue;
    }
    else if (m_type == CCScriptValueTypeCCObject)
    {
        m_field.ccobjectValue->release();
        delete m_ccobjectType;
    }
}

void CCScriptValue::copy(const CCScriptValue& rhs)
{
    memcpy(&m_field, &rhs.m_field, sizeof(m_field));
    m_type = rhs.m_type;
    if (m_type == CCScriptValueTypeString)
    {
        m_field.stringValue = new std::string(*rhs.m_field.stringValue);
    }
    else if (m_type == CCScriptValueTypeDict)
    {
        m_field.dictValue = new CCScriptValueDict(*rhs.m_field.dictValue);
    }
    else if (m_type == CCScriptValueTypeArray)
    {
        m_field.arrayValue = new CCScriptValueArray(*rhs.m_field.arrayValue);
    }
    else if (m_type == CCScriptValueTypeCCObject)
    {
        m_field.ccobjectValue = rhs.m_field.ccobjectValue;
        m_field.ccobjectValue->retain();
        m_ccobjectType = new std::string(*rhs.m_ccobjectType);
    }
}

CCLuaEngine* CCLuaEngine::create(void)
{
    CCLuaEngine* pEngine = new CCLuaEngine();
    pEngine->init();
    return pEngine;
}

CCLuaEngine::~CCLuaEngine(void)
{
    lua_close(m_state);
}

bool CCLuaEngine::init(void)
{
    m_state = lua_open();
    luaL_openlibs(m_state);
    tolua_Cocos2d_open(m_state);
    toluafix_open(m_state);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    addLuaLoader(loader_Android);
#endif
    return true;
}

void CCLuaEngine::removeScriptObjectByCCObject(CCObject* pObj)
{
    toluafix_remove_ccobject_by_refid(m_state, pObj->m_nLuaID);
}

void CCLuaEngine::removeScriptHandler(int nHandler)
{
    toluafix_remove_function_by_refid(m_state, nHandler);
}

void CCLuaEngine::addSearchPath(const char* path)
{
    lua_getglobal(m_state, "package");                                  /* stack: package */
    lua_getfield(m_state, -1, "path");                /* get package.path, stack: package path */
    const char* cur_path =  lua_tostring(m_state, -1);
    lua_pop(m_state, 1);                                                /* stack: package */
    lua_pushfstring(m_state, "%s;%s/?.lua", cur_path, path);            /* stack: package newpath */
    lua_setfield(m_state, -2, "path");          /* package.path = newpath, stack: package */
    lua_pop(m_state, 1);                                                /* stack: - */
}

int CCLuaEngine::executeString(const char *codes)
{
    int nRet =    luaL_dostring(m_state, codes);
    lua_gc(m_state, LUA_GCCOLLECT, 0);

    if (nRet != 0)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, -1));
        lua_pop(m_state, 1);
        return nRet;
    }
    return 0;
}

int CCLuaEngine::executeScriptFile(const char* filename)
{
    int nRet = luaL_dofile(m_state, filename);
    // lua_gc(m_state, LUA_GCCOLLECT, 0);

    if (nRet != 0)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, -1));
        lua_pop(m_state, 1);
        return nRet;
    }
    return 0;
}

int CCLuaEngine::executeGlobalFunction(const char* functionName)
{
    lua_getglobal(m_state, functionName);       /* query function by name, stack: function */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
        lua_pop(m_state, 1);
        return 0;
    }

    int error = lua_pcall(m_state, 0, 1, 0);             /* call function, stack: ret */
    // lua_gc(m_state, LUA_GCCOLLECT, 0);

    if (error)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));
        lua_pop(m_state, 1); // clean error message
        return 0;
    }

    // get return value
    if (!lua_isnumber(m_state, -1))
    {
        lua_pop(m_state, 1);
        return 0;
    }

    int ret = lua_tointeger(m_state, -1);
    lua_pop(m_state, 1);                                                /* stack: - */
    return ret;
}

int CCLuaEngine::executeNodeEvent(CCNode* pNode, int nAction)
{
    int ret = 0;
    do 
    {
        int nScriptHandler = pNode->getScriptHandler();
        CC_BREAK_IF(0 == nScriptHandler);
        CCScriptValueDict dict;
        if (nAction == kCCNodeOnEnter)
        {
            dict["name"] = CCScriptValue::stringValue("enter");
            this->pushCCScriptValueDict(dict);
            ret = this->executeFunctionByHandler(nScriptHandler, 1);
        }
        else if (nAction == kCCNodeOnExit)
        {
            dict["name"] = CCScriptValue::stringValue("exit");
            this->pushCCScriptValueDict(dict);
            ret = this->executeFunctionByHandler(nScriptHandler, 1);
        }
    } while (0);
    return ret;
}

int CCLuaEngine::executeMenuItemEvent(CCMenuItem* pMenuItem)
{
    int ret = 0;
    do 
    {
        int nScriptHandler = pMenuItem->getScriptTapHandler();
        CC_BREAK_IF(0 == nScriptHandler);
        ret = this->pushIntegerData(pMenuItem->getTag());
        ret = this->executeFunctionByHandler(nScriptHandler, 1);
    } while (0);
    return ret;
}

int CCLuaEngine::executeNotificationEvent(CCNotificationCenter* pNotificationCenter, const char* pszName)
{
    int ret = 0;
    do 
    {
        int nScriptHandler = pNotificationCenter->getScriptHandler();
        CC_BREAK_IF(0 == nScriptHandler);
        ret = this->pushStringData(pszName);
        ret = this->executeFunctionByHandler(nScriptHandler, 1);
    } while (0);
    return ret;
}

int CCLuaEngine::executeCallFuncActionEvent(CCCallFunc* pAction, CCObject* pTarget/* = NULL*/)
{
    int ret = 0;
    do 
    {
        int nScriptHandler = pAction->getScriptHandler();
        CC_BREAK_IF(0 == nScriptHandler);
        if (pTarget != NULL)
        {
            ret = this->pushCCObject(pTarget, "CCNode");
        }
        ret = this->executeFunctionByHandler(nScriptHandler, 1);
    } while (0);
    return ret;
}

int CCLuaEngine::executeSchedule(CCTimer* pTimer, float dt, CCNode* pNode/* = NULL*/)
{
    int ret = 0;
    do 
    {
        int nScriptHandler = pTimer->getScriptHandler();
        CC_BREAK_IF(0 == nScriptHandler);
        ret = this->pushFloatData(dt);
        ret = this->executeFunctionByHandler(nScriptHandler, 1);
    } while (0);
    return ret;
}

// functions for excute touch event
int CCLuaEngine::executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch)
{
    int ret = 0;
    do 
    {
        CCTouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptHandlerEntry();
        CC_BREAK_IF(NULL == pScriptHandlerEntry);
        int nScriptHandler = pScriptHandlerEntry->getHandler();
        CC_BREAK_IF(0 == nScriptHandler);
        CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        lua_pushinteger(m_state, eventType);
        lua_pushnumber(m_state, pt.x);
        lua_pushnumber(m_state, pt.y);
        ret = executeFunctionByHandler(nScriptHandler, 3);
    } while (0);
    return ret;
}

int CCLuaEngine::executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches)
{
    int ret = 0;
    do 
    {
        CCTouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptHandlerEntry();
        CC_BREAK_IF(NULL == pScriptHandlerEntry);
        int nScriptHandler = pScriptHandlerEntry->getHandler();
        CC_BREAK_IF(0 == nScriptHandler);
        lua_pushinteger(m_state, eventType);
        lua_newtable(m_state);

        CCDirector* pDirector = CCDirector::sharedDirector();
        CCSetIterator it = pTouches->begin();
        CCTouch* pTouch;
        int n = 1;
        while (it != pTouches->end())
        {
            pTouch = (CCTouch*)*it;
            CCPoint pt = pDirector->convertToGL(pTouch->getLocationInView());
            lua_pushnumber(m_state, pt.x);
            lua_rawseti(m_state, -2, n++);
            lua_pushnumber(m_state, pt.y);
            lua_rawseti(m_state, -2, n++);
            ++it;
        }

        ret = executeFunctionByHandler(nScriptHandler, 2);
    } while (0);

    return ret;
}

int CCLuaEngine::executeFunctionByHandler(int nHandler, int numArgs)
{
    if (pushFunction(nHandler))                                         /* stack: ... arg1 arg2 ... func */
    {
        if (numArgs > 0)
        {
            lua_insert(m_state, -(numArgs + 1));                        /* stack: ... func arg1 arg2 ... */
        }
        
        int traceback = 0;
        lua_getglobal(m_state, "__G__TRACKBACK__");                     /* stack: ... func arg1 arg2 ... G */
        if (!lua_isfunction(m_state, -1))
        {
            lua_pop(m_state, 1);                                        /* stack: ... func arg1 arg2 ... */
        }
        else
        {
            traceback = -(numArgs + 2);
            lua_insert(m_state, traceback);                             /* stack: ... G func arg1 arg2 ... */
        }
        
        int error = 0;
        error = lua_pcall(m_state, numArgs, 1, traceback);              /* stack: ... ret */
        if (error)
        {
            if (traceback == 0)
            {
                CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));    /* stack: ... error */
                lua_pop(m_state, 1); // remove error message from stack
            }
            return 0;
        }
        
        // get return value
        int ret = 0;
        if (lua_isnumber(m_state, -1))
        {
            ret = lua_tointeger(m_state, -1);
        }
        else if (lua_isboolean(m_state, -1))
        {
            ret = lua_toboolean(m_state, -1);
        }
        
        lua_pop(m_state, 1); // remove return value from stack
        return ret;
    }
    else
    {
        lua_pop(m_state, numArgs); // remove args from stack
        return 0;
    }
}

int CCLuaEngine::pushIntegerData(int data)
{
    lua_pushinteger(m_state, data);
    return lua_gettop(m_state);
}

int CCLuaEngine::pushFloatData(float data)
{
    lua_pushnumber(m_state, data);
    return lua_gettop(m_state);
}

int CCLuaEngine::pushBooleanData(bool data)
{
    lua_pushboolean(m_state, data);
    return lua_gettop(m_state);
}

int CCLuaEngine::pushStringData(const char* data)
{
    lua_pushstring(m_state, data);
    return lua_gettop(m_state);
}

int CCLuaEngine::pushCCObject(CCObject* pObject, const char* typeName)
{
    toluafix_pushusertype_ccobject(m_state, pObject->m_uID, &pObject->m_nLuaID, pObject, typeName);
    return lua_gettop(m_state);
}

int CCLuaEngine::pushCCScriptValue(const CCScriptValue& value)
{
    const CCScriptValueType type = value.getType();
    if (type == CCScriptValueTypeInt)
    {
        return pushIntegerData(value.intValue());
    }
    else if (type == CCScriptValueTypeFloat)
    {
        return pushFloatData(value.floatValue());
    }
    else if (type == CCScriptValueTypeBoolean)
    {
        return pushBooleanData(value.booleanValue());
    }
    else if (type == CCScriptValueTypeString)
    {
        return pushStringData(value.stringValue().c_str());
    }
    else if (type == CCScriptValueTypeDict)
    {
        pushCCScriptValueDict(value.dictValue());
    }
    else if (type == CCScriptValueTypeArray)
    {
        pushCCScriptValueArray(value.arrayValue());
    }
    else if (type == CCScriptValueTypeCCObject)
    {
        pushCCObject(value.ccobjectValue(), value.getCCObjectTypename().c_str());
    }
    
    return lua_gettop(m_state);
}

int CCLuaEngine::pushCCScriptValueDict(const CCScriptValueDict& dict)
{
    lua_newtable(m_state);                                      /* stack: table */
    for (CCScriptValueDictIterator it = dict.begin(); it != dict.end(); ++it)
    {
        lua_pushstring(m_state, it->first.c_str());             /* stack: table key */
        pushCCScriptValue(it->second);                   /* stack: table key value */
        lua_rawset(m_state, -3);             /* table.key = value, stack: table */
    }
    
    return lua_gettop(m_state);
}

int CCLuaEngine::pushCCScriptValueArray(const CCScriptValueArray& array)
{
    lua_newtable(m_state);                                      /* stack: table */
    int index = 1;
    for (CCScriptValueArrayIterator it = array.begin(); it != array.end(); ++it)
    {
        pushCCScriptValue(*it);                          /* stack: table value */
        lua_rawseti(m_state, -2, index);  /* table[index] = value, stack: table */
        ++index;
    }
    
    return lua_gettop(m_state);
}

void CCLuaEngine::cleanStack(void)
{
    lua_settop(m_state, 0);
}

void CCLuaEngine::addLuaLoader(lua_CFunction func)
{
    if (!func) return;

    // stack content after the invoking of the function
    // get loader table
    lua_getglobal(m_state, "package");                     // package
    lua_getfield(m_state, -1, "loaders");                  // package, loaders

    // insert loader into index 2
    lua_pushcfunction(m_state, func);                      // package, loaders, func
    for (int i = lua_objlen(m_state, -2) + 1; i > 2; --i)
    {
        lua_rawgeti(m_state, -2, i - 1);                   // package, loaders, func, function
                                                           // we call lua_rawgeti, so the loader table now is at -3
        lua_rawseti(m_state, -3, i);                       // package, loaders, func
    }
    lua_rawseti(m_state, -2, 2);                           // package, loaders

    // set loaders into package
    lua_setfield(m_state, -2, "loaders");                  // package

    lua_pop(m_state, 1);
}

bool CCLuaEngine::pushFunction(int nHandler)
{
    lua_rawgeti(m_state, LUA_REGISTRYINDEX, nHandler);  /* stack: ... func */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", nHandler);
        lua_pop(m_state, 1);
        return false;
    }
    return true;
}

NS_CC_END
