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
    for (; iterVec != iterMap->second.end(); iterVec++)
    {
        if (iterVec->first == handlerType)
        {
            exist = true;
            break;
        }
    }
    
    if (exist)
    {
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
        (iter->second).clear();
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


TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_script_handler_mgr_type(tolua_S);
    tolua_module(tolua_S, NULL,0);
    tolua_beginmodule(tolua_S, NULL);
      tolua_cclass(tolua_S,"ScriptHandlerMgr","ScriptHandlerMgr","",NULL);
      tolua_beginmodule(tolua_S, "ScriptHandlerMgr");
        tolua_function(tolua_S, "getInstance", tolua_Cocos2d_ScriptHandlerMgr_getInstance00);
      tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
   return 1; 
}
