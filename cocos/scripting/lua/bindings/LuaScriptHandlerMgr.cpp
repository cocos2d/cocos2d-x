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
#ifdef __cplusplus
extern "C" {
#endif
#include "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include <map>
#include <string>
#include "LuaScriptHandlerMgr.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "Lua_web_socket.h"
#include "LuaOpengl.h"

using namespace cocos2d;
using namespace cocos2d::extension;

NS_CC_BEGIN

ScheduleHandlerDelegate* ScheduleHandlerDelegate::create()
{
    ScheduleHandlerDelegate *ret = new ScheduleHandlerDelegate();
    if (NULL != ret )
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

void ScheduleHandlerDelegate::scheduleFunc(float elapse)
{

}

void ScheduleHandlerDelegate::update(float elapse)
{

}


LuaCallFunc * LuaCallFunc::create(const std::function<void(void* ,Node*)>& func)
{
    auto ret = new LuaCallFunc();
    
    if (ret && ret->initWithFunction(func) ) {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return NULL;
}

void LuaCallFunc::execute()
{
    if (_functionLua)
    {
        _functionLua((void*)this,_target);
    }
    else
    {
        CallFuncN::execute();
    }
}

bool LuaCallFunc::initWithFunction(const std::function<void (void*, Node*)> &func)
{
    _functionLua = func;
    return true;
}

LuaCallFunc* LuaCallFunc::clone() const
{
    int handler =  ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::CALLFUNC);
    
    if (0 == handler)
        return NULL;
    
    auto ret = new LuaCallFunc();
    
    if( _functionLua )
    {
        ret->initWithFunction(_functionLua);
    }
    
    ret->autorelease();

    int newscriptHandler = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);
    
    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)ret, newscriptHandler, ScriptHandlerMgr::HandlerType::CALLFUNC);
        
    return ret;
}

ScriptHandlerMgr* ScriptHandlerMgr::_scriptHandlerMgr = NULL;

ScriptHandlerMgr::ScriptHandlerMgr()
{
    
}
ScriptHandlerMgr::~ScriptHandlerMgr()
{
    CC_SAFE_DELETE(_scriptHandlerMgr);
}
ScriptHandlerMgr* ScriptHandlerMgr::getInstance()
{
    if (NULL == _scriptHandlerMgr)
    {
        _scriptHandlerMgr = new ScriptHandlerMgr();
        _scriptHandlerMgr->init();
    }
    return _scriptHandlerMgr;
}

void ScriptHandlerMgr::init()
{
    _mapObjectHandlers.clear();
}

void ScriptHandlerMgr::addObjectHandler(void* object,int handler,ScriptHandlerMgr::HandlerType handlerType)
{
    if (NULL == object)
        return;
    
    //may be not need
    removeObjectHandler(object,handlerType);
    
    auto iter = _mapObjectHandlers.find(object);
    VecHandlerPairs vecHandlers;
    vecHandlers.clear();
    if (_mapObjectHandlers.end() != iter)
    {
        vecHandlers = iter->second;
    }
    
    HandlerPair eventHanler = std::make_pair(handlerType, handler);
    vecHandlers.push_back(eventHanler);
    _mapObjectHandlers[object] = vecHandlers;
}
void ScriptHandlerMgr::removeObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType)
{
    if (NULL == object || _mapObjectHandlers.empty())
        return;
    
    auto iterMap = _mapObjectHandlers.find(object);
    if (_mapObjectHandlers.end() == iterMap)
        return;
    
    if (iterMap->second.empty())
        return;
    
    auto iterVec = iterMap->second.begin();
    bool exist  = false;
    for (; iterVec != iterMap->second.end(); ++iterVec)
    {
        if (iterVec->first == handlerType)
        {
            exist = true;
            break;
        }
    }
    
    if (exist)
    {
        LuaEngine::getInstance()->removeScriptHandler(iterVec->second);
        iterMap->second.erase(iterVec);
    }

}
int  ScriptHandlerMgr::getObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType)
{
    if (NULL == object ||   _mapObjectHandlers.empty() )
        return 0;
    
    auto iter = _mapObjectHandlers.find(object);
    
    if (_mapObjectHandlers.end() != iter)
    {
        auto iterVec = (iter->second).begin();
        for (; iterVec != (iter->second).end(); iterVec++)
        {
            if (iterVec->first == handlerType)
            {
                return iterVec->second;
            }
        }
    }
    
    return 0;
}
void ScriptHandlerMgr::removeObjectAllHandlers(void* object)
{
    if (NULL == object || _mapObjectHandlers.empty())
        return;
    
    auto iter = _mapObjectHandlers.find(object);
    
    if (_mapObjectHandlers.end() != iter)
    {
        if (!iter->second.empty())
        {
            auto iterVec = iter->second.begin();
            for (; iterVec != iter->second.end(); ++iterVec)
            {
                LuaEngine::getInstance()->removeScriptHandler(iterVec->second);
            }
            (iter->second).clear();
        }
        _mapObjectHandlers.erase(iter);
    }
}

NS_CC_END


static void tolua_reg_script_handler_mgr_type(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "ScheduleHandlerDelegate");
    tolua_usertype(tolua_S, "ScriptHandlerMgr");
}

/* method: getInstance of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_getInstance00
static int tolua_Cocos2d_ScriptHandlerMgr_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* tolua_ret = (ScriptHandlerMgr*)  ScriptHandlerMgr::getInstance();
        tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScriptHandlerMgr");
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptHandler of class  ScriptHandlerMgr */
static int tolua_Cocos2d_ScriptHandlerMgr_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S, 2, "cc.Object", 0, &tolua_err) ||
        !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err) ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        cocos2d::ScriptHandlerMgr* scriptHanlderMgr = static_cast<cocos2d::ScriptHandlerMgr*>(tolua_tousertype(tolua_S,1,0));
#ifndef TOLUA_RELEASE
        if (nullptr == scriptHanlderMgr)
        {
            tolua_error(tolua_S,"invalid 'scriptHanlderMgr' in function 'tolua_Cocos2d_ScriptHandlerMgr_registerScriptHandler00'\n", NULL);
            return 0;
        }
#endif
        LUA_FUNCTION handler =  toluafix_ref_function(tolua_S,3,0);
        ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType)(int)tolua_tonumber(tolua_S, 4, 0);
        scriptHanlderMgr->addObjectHandler(tolua_tousertype(tolua_S, 2, 0), handler,handlerType);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

/* method: unregisterScriptHandler of class  ScriptHandlerMgr */
static int tolua_Cocos2d_ScriptHandlerMgr_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S, 2, "cc.Object", 0, &tolua_err) ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        cocos2d::ScriptHandlerMgr* scriptHanlderMgr = static_cast<cocos2d::ScriptHandlerMgr*>(tolua_tousertype(tolua_S,1,0));
#ifndef TOLUA_RELEASE
        if (nullptr == scriptHanlderMgr)
        {
            tolua_error(tolua_S,"invalid 'scriptHanlderMgr' in function 'tolua_Cocos2d_ScriptHandlerMgr_unregisterScriptHandler00'\n", NULL);
            return 0;
        }
#endif
        ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType)(int)tolua_tonumber(tolua_S, 3, 0);
        scriptHanlderMgr->removeObjectHandler(tolua_tousertype(tolua_S, 2, 0), handlerType);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}

/* method: removeObjectAllHandlers of class  ScriptHandlerMgr */
static int tolua_Cocos2d_ScriptHandlerMgr_removeObjectAllHandlers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S, 2, "cc.Object", 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        cocos2d::ScriptHandlerMgr* scriptHanlderMgr = static_cast<cocos2d::ScriptHandlerMgr*>(tolua_tousertype(tolua_S,1,0));
#ifndef TOLUA_RELEASE
        if (nullptr == scriptHanlderMgr)
        {
            tolua_error(tolua_S,"invalid 'scriptHanlderMgr' in function 'tolua_Cocos2d_ScriptHandlerMgr_removeObjectAllHandlers00'\n", NULL);
            return 0;
        }
#endif
        scriptHanlderMgr->removeObjectAllHandlers(tolua_tousertype(tolua_S, 2, 0));
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeObjectAllHandlers'.",&tolua_err);
    return 0;
#endif
}

TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_script_handler_mgr_type(tolua_S);
    tolua_module(tolua_S, NULL,0);
    tolua_beginmodule(tolua_S, NULL);
      tolua_cclass(tolua_S,"ScriptHandlerMgr","ScriptHandlerMgr","",NULL);
      tolua_beginmodule(tolua_S, "ScriptHandlerMgr");
        tolua_function(tolua_S, "getInstance", tolua_Cocos2d_ScriptHandlerMgr_getInstance00);
        tolua_function(tolua_S, "registerScriptHandler", tolua_Cocos2d_ScriptHandlerMgr_registerScriptHandler00);
        tolua_function(tolua_S, "unregisterScriptHandler", tolua_Cocos2d_ScriptHandlerMgr_unregisterScriptHandler00);
        tolua_function(tolua_S, "removeObjectAllHandlers", tolua_Cocos2d_ScriptHandlerMgr_removeObjectAllHandlers00);
      tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
   return 1; 
}
