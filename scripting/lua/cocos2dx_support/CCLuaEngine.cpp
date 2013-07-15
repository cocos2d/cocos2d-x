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
#include "cocos2d.h"
#include "cocoa/CCArray.h"
#include "CCScheduler.h"
#include "LuaScriptHandlerMgr.h"

NS_CC_BEGIN

LuaEngine* LuaEngine::_defaultEngine = NULL;

LuaEngine* LuaEngine::defaultEngine(void)
{
    if (!_defaultEngine)
    {
        _defaultEngine = new LuaEngine();
        _defaultEngine->init();
    }
    return _defaultEngine;
}

LuaEngine::~LuaEngine(void)
{
    CC_SAFE_RELEASE(_stack);
    _defaultEngine = NULL;
}

bool LuaEngine::init(void)
{
    _stack = LuaStack::create();
    _stack->retain();
    return true;
}

void LuaEngine::addSearchPath(const char* path)
{
    _stack->addSearchPath(path);
}

void LuaEngine::addLuaLoader(lua_CFunction func)
{
    _stack->addLuaLoader(func);
}

void LuaEngine::removeScriptObjectByObject(Object* pObj)
{
    _stack->removeScriptObjectByObject(pObj);
    ScriptHandlerMgr::getInstance()->removeObjectAllHandlers(pObj);
}

void LuaEngine::removeScriptHandler(int nHandler)
{
    _stack->removeScriptHandler(nHandler);
}

int LuaEngine::executeString(const char *codes)
{
    int ret = _stack->executeString(codes);
    _stack->clean();
    return ret;
}

int LuaEngine::executeScriptFile(const char* filename)
{
    int ret = _stack->executeScriptFile(filename);
    _stack->clean();
    return ret;
}

int LuaEngine::executeGlobalFunction(const char* functionName)
{
    int ret = _stack->executeGlobalFunction(functionName);
    _stack->clean();
    return ret;
}

int LuaEngine::executeNodeEvent(Node* pNode, int nAction)
{
    int nHandler = pNode->getScriptHandler();
    if (!nHandler) return 0;
    
    switch (nAction)
    {
        case kNodeOnEnter:
            _stack->pushString("enter");
            break;
            
        case kNodeOnExit:
            _stack->pushString("exit");
            break;
            
        case kNodeOnEnterTransitionDidFinish:
            _stack->pushString("enterTransitionFinish");
            break;
            
        case kNodeOnExitTransitionDidStart:
            _stack->pushString("exitTransitionStart");
            break;
            
        case kNodeOnCleanup:
            _stack->pushString("cleanup");
            break;
            
        default:
            return 0;
    }
    int ret = _stack->executeFunctionByHandler(nHandler, 1);
    _stack->clean();
    return ret;
}

int LuaEngine::executeMenuItemEvent(MenuItem* pMenuItem)
{
    int nHandler = pMenuItem->getScriptTapHandler();
    if (!nHandler) return 0;
    
    _stack->pushInt(pMenuItem->getTag());
    _stack->pushObject(pMenuItem, "CCMenuItem");
    int ret = _stack->executeFunctionByHandler(nHandler, 2);
    _stack->clean();
    return ret;
}

int LuaEngine::executeNotificationEvent(NotificationCenter* pNotificationCenter, const char* pszName)
{
    int nHandler = pNotificationCenter->getObserverHandlerByName(pszName);
    if (!nHandler) return 0;
    
    _stack->pushString(pszName);
    int ret = _stack->executeFunctionByHandler(nHandler, 1);
    _stack->clean();
    return ret;
}

int LuaEngine::executeCallFuncActionEvent(CallFunc* pAction, Object* pTarget/* = NULL*/)
{
    int nHandler = pAction->getScriptHandler();
    if (!nHandler) return 0;
    
    if (pTarget)
    {
        _stack->pushObject(pTarget, "CCNode");
    }
    int ret = _stack->executeFunctionByHandler(nHandler, pTarget ? 1 : 0);
    _stack->clean();
    return ret;
}

int LuaEngine::executeSchedule(int nHandler, float dt, Node* pNode/* = NULL*/)
{
    if (!nHandler) return 0;
    _stack->pushFloat(dt);
    int ret = _stack->executeFunctionByHandler(nHandler, 1);
    _stack->clean();
    return ret;
}

int LuaEngine::executeLayerTouchEvent(Layer* pLayer, int eventType, Touch *pTouch)
{
    TouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptTouchHandlerEntry();
    if (!pScriptHandlerEntry) return 0;
    int nHandler = pScriptHandlerEntry->getHandler();
    if (!nHandler) return 0;
    
    switch (eventType)
    {
        case CCTOUCHBEGAN:
            _stack->pushString("began");
            break;
            
        case CCTOUCHMOVED:
            _stack->pushString("moved");
            break;
            
        case CCTOUCHENDED:
            _stack->pushString("ended");
            break;
            
        case CCTOUCHCANCELLED:
            _stack->pushString("cancelled");
            break;
            
        default:
            return 0;
    }
    
    const Point pt = Director::sharedDirector()->convertToGL(pTouch->getLocationInView());
    _stack->pushFloat(pt.x);
    _stack->pushFloat(pt.y);
    int ret = _stack->executeFunctionByHandler(nHandler, 3);
    _stack->clean();
    return ret;
}

int LuaEngine::executeLayerTouchesEvent(Layer* pLayer, int eventType, Set *pTouches)
{
    TouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptTouchHandlerEntry();
    if (!pScriptHandlerEntry) return 0;
    int nHandler = pScriptHandlerEntry->getHandler();
    if (!nHandler) return 0;
    
    switch (eventType)
    {
        case CCTOUCHBEGAN:
            _stack->pushString("began");
            break;
            
        case CCTOUCHMOVED:
            _stack->pushString("moved");
            break;
            
        case CCTOUCHENDED:
            _stack->pushString("ended");
            break;
            
        case CCTOUCHCANCELLED:
            _stack->pushString("cancelled");
            break;
            
        default:
            return 0;
    }

    Director* pDirector = Director::sharedDirector();
    lua_State *L = _stack->getLuaState();
    lua_newtable(L);
    int i = 1;
    for (SetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
    {
        Touch* pTouch = (Touch*)*it;
        Point pt = pDirector->convertToGL(pTouch->getLocationInView());
        lua_pushnumber(L, pt.x);
        lua_rawseti(L, -2, i++);
        lua_pushnumber(L, pt.y);
        lua_rawseti(L, -2, i++);
        lua_pushinteger(L, pTouch->getID());
        lua_rawseti(L, -2, i++);
    }
    int ret = _stack->executeFunctionByHandler(nHandler, 2);
    _stack->clean();
    return ret;
}

int LuaEngine::executeLayerKeypadEvent(Layer* pLayer, int eventType)
{
    ScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptKeypadHandlerEntry();
    if (!pScriptHandlerEntry)
        return 0;
    int nHandler = pScriptHandlerEntry->getHandler();
    if (!nHandler) return 0;
    
    switch (eventType)
    {
        case kTypeBackClicked:
            _stack->pushString("backClicked");
            break;
            
        case kTypeMenuClicked:
            _stack->pushString("menuClicked");
            break;
            
        default:
            return 0;
    }
    int ret = _stack->executeFunctionByHandler(nHandler, 1);
    _stack->clean();
    return ret;
}

int LuaEngine::executeAccelerometerEvent(Layer* pLayer, Acceleration* pAccelerationValue)
{
    ScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptAccelerateHandlerEntry();
    if (!pScriptHandlerEntry)
        return 0;
    int nHandler = pScriptHandlerEntry->getHandler();
    if (!nHandler) return 0;
    
    _stack->pushFloat(pAccelerationValue->x);
    _stack->pushFloat(pAccelerationValue->y);
    _stack->pushFloat(pAccelerationValue->z);
    _stack->pushFloat(pAccelerationValue->timestamp);
    int ret = _stack->executeFunctionByHandler(nHandler, 4);
    _stack->clean();
    return ret;
}

int LuaEngine::executeEvent(int nHandler, const char* pEventName, Object* pEventSource /* = NULL*/, const char* pEventSourceClassName /* = NULL*/)
{
    _stack->pushString(pEventName);
    if (pEventSource)
    {
        _stack->pushObject(pEventSource, pEventSourceClassName ? pEventSourceClassName : "CCObject");
    }
    int ret = _stack->executeFunctionByHandler(nHandler, pEventSource ? 2 : 1);
    _stack->clean();
    return ret;
}

bool LuaEngine::handleAssert(const char *msg)
{
    bool ret = _stack->handleAssert(msg);
    _stack->clean();
    return ret;
}

int LuaEngine::reallocateScriptHandler(int nHandler)
{    
    int nRet = _stack->reallocateScriptHandler(nHandler);
    _stack->clean();
    return nRet;
}

int LuaEngine::sendEvent(ScriptEvent* message)
{
    if (NULL == message)
        return 0;
    switch (message->type)
    {
        case kNodeEvent:
        {
           return handleNodeEvent(message->data);
        }
        break;
        case kMenuClickedEvent:
        {
            return handleMenuClickedEvent(message->data);
        }
        break;
        case kNotificationEvent:
        {
            return handleNotificationEvent(message->data);
        }
        break;
        case kCallFuncEvent:
        {
            return handleCallFuncActionEvent(message->data);
        }
        break;
        case kScheduleEvent:
        {
            return handleScheduler(message->data);
        }
        break;
        case kTouchesEvent:
        {
            return handleTouchesEvent(message->data);
        }
        break;
        case kKeypadEvent:
        {
            return handleKeypadEvent(message->data);
        }
        break;
        case kAccelerometerEvent:
        {
            return handleAccelerometerEvent(message->data);
        }
        break;
        case kCommonEvent:
        {
            return handleCommonEvent(message->data);
        }
        break;
        default:
        break;
    }
    
    return 0;
}

int LuaEngine::handleNodeEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = (BasicScriptData*)data;
    if (NULL == basicScriptData->nativeObject || NULL == basicScriptData->value)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, ScriptHandlerMgr::kNodeHandler);
    
    if (0 == handler)
        return 0;
    
    int action = *((int*)(basicScriptData->value));
    switch (action)
    {
        case kNodeOnEnter:
            _stack->pushString("enter");
            break;
            
        case kNodeOnExit:
            _stack->pushString("exit");
            break;
            
        case kNodeOnEnterTransitionDidFinish:
            _stack->pushString("enterTransitionFinish");
            break;
            
        case kNodeOnExitTransitionDidStart:
            _stack->pushString("exitTransitionStart");
            break;
            
        case kNodeOnCleanup:
            _stack->pushString("cleanup");
            break;
            
        default:
            return 0;
    }
    int ret = _stack->executeFunctionByHandler(handler, 1);
    _stack->clean();
    return ret;
}

int LuaEngine::handleMenuClickedEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = (BasicScriptData*)data;
    if (NULL == basicScriptData->nativeObject)
        return 0;
        
    MenuItem* menuItem = (MenuItem*)(basicScriptData->nativeObject);
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)menuItem, ScriptHandlerMgr::kMenuClickHandler);
    if (0 == handler)
        return 0;
    
    _stack->pushInt(menuItem->getTag());
    _stack->pushObject(menuItem, "CCMenuItem");
    int ret = _stack->executeFunctionByHandler(handler, 2);
    _stack->clean();
    return ret;
}

int LuaEngine::handleNotificationEvent(void* data)
{
    if ( NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = (BasicScriptData*)(data);
    if (NULL == basicScriptData->nativeObject ||NULL == basicScriptData->value)
        return 0;
    
    NotificationCenter* center = (NotificationCenter*)(basicScriptData->nativeObject);
    
    int handler = center->getObserverHandlerByName((const char*)basicScriptData->value);
    
    if (0 == handler)
        return 0;
    
    _stack->pushString((const char*)basicScriptData->value);
    int ret = _stack->executeFunctionByHandler(handler, 1);
    _stack->clean();
    return ret;
}

int LuaEngine::handleCallFuncActionEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = (BasicScriptData*)(data);
    if (NULL == basicScriptData->nativeObject)
        return 0;
        
    int handler =ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, ScriptHandlerMgr::kCallFuncHandler);
    
    if (0 == handler)
        return 0;
    
    Object* target     =  (Object*)(basicScriptData->value);
    if (NULL != target)
    {
        _stack->pushObject(target, "CCNode");
    }
    int ret = _stack->executeFunctionByHandler(handler, target ? 1 : 0);
    _stack->clean();
    return ret;
}

int LuaEngine::handleScheduler(void* data)
{
    if (NULL == data)
        return 0;
    
    SchedulerScriptData* schedulerInfo = (SchedulerScriptData*)data;
    
    _stack->pushFloat(schedulerInfo->elapse);
    int ret = _stack->executeFunctionByHandler(schedulerInfo->handler, 1);
    _stack->clean();
    
    return ret;
}

int LuaEngine::handleKeypadEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    KeypadScriptData* keypadScriptData = (KeypadScriptData*)data;
    if (NULL == keypadScriptData->nativeObject)
        return 0;
    
    switch (keypadScriptData->objectType)
    {
        case kLayerKeypad:
        {
            Layer* layer = (Layer*)(keypadScriptData->nativeObject);
            return handleLayerKeypadEvent(layer, keypadScriptData->actionType);
        }
        break;
            
        default:
            break;
    }
    
    return 0;
}

int LuaEngine::handleAccelerometerEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = (BasicScriptData*)data;
    if (NULL == basicScriptData->nativeObject || NULL == basicScriptData->value)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, ScriptHandlerMgr::kAccelerometerHandler);
    if (0 == handler)
        return 0;
    
    Acceleration* accelerationValue = (Acceleration*)(basicScriptData->value);
    _stack->pushFloat(accelerationValue->x);
    _stack->pushFloat(accelerationValue->y);
    _stack->pushFloat(accelerationValue->z);
    _stack->pushFloat(accelerationValue->timestamp);
    int ret = _stack->executeFunctionByHandler(handler, 4);
    _stack->clean();
    return ret;
}

int LuaEngine::handleCommonEvent(void* data)
{
    if (NULL == data)
        return 0;
   
    CommonScriptData* commonInfo = (CommonScriptData*)data;
    if (NULL == commonInfo->eventName || 0 == commonInfo->handler)
        return 0;
    
    _stack->pushString(commonInfo->eventName);
    if (NULL != commonInfo->eventSource)
    {
        if (NULL  != commonInfo->eventSourceClassName && strlen(commonInfo->eventSourceClassName) > 0)
        {
            _stack->pushObject(commonInfo->eventSource, commonInfo->eventSourceClassName);
        }
        else
        {
            _stack->pushObject(commonInfo->eventSource, "CCObject");
        }
    }
    int ret = _stack->executeFunctionByHandler(commonInfo->handler, commonInfo->eventSource ? 2 : 1);
    _stack->clean();
    return ret;
}

int LuaEngine::handleTouchesEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    TouchesScriptData* touchesScriptData = (TouchesScriptData*)data;
    if (NULL == touchesScriptData->nativeObject || NULL == touchesScriptData->touches)
        return 0;
    
    switch (touchesScriptData->objectType)
    {
        case kLayerTouches:
        {
            Layer* layer = (Layer*)(touchesScriptData->nativeObject);
            return handleLayerTouchesEvent(layer, touchesScriptData->actionType, touchesScriptData->touches);
        }
        break;
            
        default:
            break;
    }

    return 0;
}

int LuaEngine::handleLayerTouchesEvent(Layer* layer,int actionType,Set* touches)
{
    if (NULL == layer || NULL == touches)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)layer, ScriptHandlerMgr::kTouchesHandler);
    if (0 == handler)
        return 0;
    
    switch (actionType)
    {
        case CCTOUCHBEGAN:
            _stack->pushString("began");
            break;
            
        case CCTOUCHMOVED:
            _stack->pushString("moved");
            break;
            
        case CCTOUCHENDED:
            _stack->pushString("ended");
            break;
            
        case CCTOUCHCANCELLED:
            _stack->pushString("cancelled");
            break;
            
        default:
            return 0;
    }
    
    Director* pDirector = Director::sharedDirector();
    lua_State *L = _stack->getLuaState();
    int count = touches->count();
    int ret = 0;
    if (count == 1)
    {
        Touch* touch = (Touch*)*(touches->begin());
        if (NULL != touch) {
            const Point pt = Director::sharedDirector()->convertToGL(touch->getLocationInView());
            _stack->pushFloat(pt.x);
            _stack->pushFloat(pt.y);
            ret = _stack->executeFunctionByHandler(handler, 3);
        }
    }
    else if(count > 1)
    {
        lua_newtable(L);
        int i = 1;
        for (SetIterator it = touches->begin(); it != touches->end(); ++it)
        {
            Touch* pTouch = (Touch*)*it;
            Point pt = pDirector->convertToGL(pTouch->getLocationInView());
            lua_pushnumber(L, pt.x);
            lua_rawseti(L, -2, i++);
            lua_pushnumber(L, pt.y);
            lua_rawseti(L, -2, i++);
            lua_pushinteger(L, pTouch->getID());
            lua_rawseti(L, -2, i++);
        }
        ret = _stack->executeFunctionByHandler(handler, 2);
    }
    _stack->clean();
    return ret;
}

int LuaEngine::handleLayerKeypadEvent(Layer* layer,int actionType)
{
    if (NULL == layer)
        return 0;

    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)layer, ScriptHandlerMgr::kKeypadHandler);
    
    if (0 == handler)
        return 0;
    
    int action = actionType;
    
    switch (action)
    {
        case kTypeBackClicked:
            _stack->pushString("backClicked");
            break;
            
        case kTypeMenuClicked:
            _stack->pushString("menuClicked");
            break;
            
        default:
            return 0;
    }
    int ret = _stack->executeFunctionByHandler(handler, 1);
    _stack->clean();
    return ret;
}

void LuaEngine::expandLuaObjecFunc()
{    
    if ( NULL == _stack || NULL == _stack->getLuaState())
        return;
    
    lua_State* lua_S = _stack->getLuaState();
    expandNodeFunc(lua_S);
    expandMenuItemFunc(lua_S);
    expandLayerFunc(lua_S);
    
    _stack->clean();
}

void LuaEngine::expandNodeFunc(lua_State* lua_S)
{
   if(NULL == lua_S)
       return;
    
    lua_pushstring(lua_S,"CCNode");
    lua_gettable(lua_S,LUA_REGISTRYINDEX); /* get super */
    if (lua_istable(lua_S,-1))
    {
        lua_pushstring(lua_S,"registerScriptHandler");
        lua_pushcfunction(lua_S,tolua_Cocos2d_registerScriptHandler00);
        lua_rawset(lua_S,-3);
    }
}

void LuaEngine::expandMenuItemFunc(lua_State* lua_S)
{
    if (NULL == lua_S)
        return;
    
    lua_pushstring(lua_S,"CCMenuItem");
    lua_gettable(lua_S,LUA_REGISTRYINDEX); /* get super */
    if (lua_istable(lua_S,-1))
    {
        lua_pushstring(lua_S,"registerScriptTapHandler");
        lua_pushcfunction(lua_S,tolua_Cocos2d_registerScriptTapHandler00);
        lua_rawset(lua_S,-3);
    }
}

void LuaEngine::expandLayerFunc(lua_State* lua_S)
{
    if (NULL == lua_S)
        return;
    
    lua_pushstring(lua_S,"CCLayer");
    lua_gettable(lua_S,LUA_REGISTRYINDEX); /* get super */
    if (lua_istable(lua_S,-1))
    {
        lua_pushstring(lua_S,"registerScriptTouchHandler");
        lua_pushcfunction(lua_S,tolua_Cocos2d_registerScriptTouchHandler00);
        lua_rawset(lua_S,-3);
        lua_pushstring(lua_S, "registerScriptKeypadHandler");
        lua_pushcfunction(lua_S, tolua_Cocos2d_registerScriptKeypadHandler00);
        lua_rawset(lua_S, -3);
        lua_pushstring(lua_S, "registerScriptAccelerateHandler");
        lua_pushcfunction(lua_S, tolua_Cocos2d_registerScriptAccelerateHandler00);
        lua_rawset(lua_S, -3);
    }
}
NS_CC_END
