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
#include "CCArray.h"
#include "CCScheduler.h"
#include "LuaScriptHandlerMgr.h"
#include "extensions/GUI/CCControlExtension/CCControl.h"
#include "LuaOpengl.h"
#include "lua_cocos2dx_extension_manual.h"
#include "lua_cocos2dx_coco_studio_manual.hpp"

NS_CC_BEGIN

LuaEngine* LuaEngine::_defaultEngine = NULL;

LuaEngine* LuaEngine::getInstance(void)
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
    extendLuaObject();
    executeScriptFile("DeprecatedEnum.lua");
    executeScriptFile("DeprecatedClass.lua");
    executeScriptFile("Deprecated.lua");
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
    return 0;
}

int LuaEngine::executeMenuItemEvent(MenuItem* pMenuItem)
{
    return 0;
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
    return 0;
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
    return 0;
}

int LuaEngine::executeLayerTouchesEvent(Layer* pLayer, int eventType, Set *pTouches)
{
    return 0;
}

int LuaEngine::executeLayerKeypadEvent(Layer* pLayer, int eventType)
{
    return 0;
}

int LuaEngine::executeAccelerometerEvent(Layer* pLayer, Acceleration* pAccelerationValue)
{
    return 0;
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

int LuaEngine::sendEvent(ScriptEvent* evt)
{
    if (NULL == evt)
        return 0;
    
    switch (evt->type)
    {
        case kNodeEvent:
            {
               return handleNodeEvent(evt->data);
            }
            break;
        case kMenuClickedEvent:
            {
                return handleMenuClickedEvent(evt->data);
            }
            break;
        case kNotificationEvent:
            {
                return handleNotificationEvent(evt->data);
            }
            break;
        case kCallFuncEvent:
            {
                return handleCallFuncActionEvent(evt->data);
            }
            break;
        case kScheduleEvent:
            {
                return handleScheduler(evt->data);
            }
            break;
        case kTouchEvent:
            {
                return handleTouchEvent(evt->data);
            }
            break;
        case kTouchesEvent:
            {
                return handleTouchesEvent(evt->data);
            }
            break;
        case kKeypadEvent:
            {
                return handleKeypadEvent(evt->data);
            }
            break;
        case kAccelerometerEvent:
            {
                return handleAccelerometerEvent(evt->data);
            }
            break;
        case kCommonEvent:
            {
                return handleCommonEvent(evt->data);
            }
            break;
        case kControlEvent:
            {
                return handlerControlEvent(evt->data);
            }
            break;
        case kTableViewEvent:
            {
                return handleTableViewEvent(evt->data);
            }
            break;
        case kAssetsManagerEvent:
            {
                return handleAssetsManagerEvent(evt->data);
            }
            break;
        case kCocoStudioEventListener:
            {
                return handleCocoStudioEventListener(evt->data);
            }
            break;
        case kArmatureWrapper:
            {
                return handleArmatureWrapper(evt->data);
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
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, ScriptHandlerMgr::HandlerType::NODE);
    
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
        
    MenuItem* menuItem = static_cast<MenuItem*>(basicScriptData->nativeObject);
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(menuItem, ScriptHandlerMgr::HandlerType::MENU_CLICKED);
    if (0 == handler)
        return 0;
    
    _stack->pushInt(menuItem->getTag());
    _stack->pushObject(menuItem, "MenuItem");
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
    
    NotificationCenter* center = static_cast<NotificationCenter*>(basicScriptData->nativeObject);
    
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
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (NULL == basicScriptData->nativeObject)
        return 0;
        
    int handler =ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, ScriptHandlerMgr::HandlerType::CALLFUNC);
    
    if (0 == handler)
        return 0;
    
    Object* target = static_cast<Object*>(basicScriptData->value);
    if (NULL != target)
    {
        _stack->pushObject(target, "Node");
    }
    int ret = _stack->executeFunctionByHandler(handler, target ? 1 : 0);
    _stack->clean();
    return ret;
}

int LuaEngine::handleScheduler(void* data)
{
    if (NULL == data)
        return 0;
    
    SchedulerScriptData* schedulerInfo = static_cast<SchedulerScriptData*>(data);
    
    _stack->pushFloat(schedulerInfo->elapse);
    int ret = _stack->executeFunctionByHandler(schedulerInfo->handler, 1);
    _stack->clean();
    
    return ret;
}

int LuaEngine::handleKeypadEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    KeypadScriptData* keypadScriptData = static_cast<KeypadScriptData*>(data);
    if (NULL == keypadScriptData->nativeObject)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(keypadScriptData->nativeObject, ScriptHandlerMgr::HandlerType::KEYPAD);
    
    if (0 == handler)
        return 0;
    
    EventKeyboard::KeyCode action = keypadScriptData->actionType;

    switch(action)
    {
        case EventKeyboard::KeyCode::KEY_BACKSPACE:
			_stack->pushString("backClicked");
			break;
		case EventKeyboard::KeyCode::KEY_MENU:
            _stack->pushString("menuClicked");
			break;
		default:
			break;
    }

    int ret = _stack->executeFunctionByHandler(handler, 1);
    _stack->clean();
    return ret;
}

int LuaEngine::handleAccelerometerEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (NULL == basicScriptData->nativeObject || NULL == basicScriptData->value)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, ScriptHandlerMgr::HandlerType::ACCELEROMETER);
    if (0 == handler)
        return 0;
    
    Acceleration* accelerationValue = static_cast<Acceleration*>(basicScriptData->value);
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
   
    CommonScriptData* commonInfo = static_cast<CommonScriptData*>(data);
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
            _stack->pushObject(commonInfo->eventSource, "Object");
        }
    }
    int ret = _stack->executeFunctionByHandler(commonInfo->handler, commonInfo->eventSource ? 2 : 1);
    _stack->clean();
    return ret;
}

int LuaEngine::handleTouchEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    TouchScriptData* touchScriptData = static_cast<TouchScriptData*>(data);
    if (NULL == touchScriptData->nativeObject || NULL == touchScriptData->touch)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)touchScriptData->nativeObject, ScriptHandlerMgr::HandlerType::TOUCHES);
    
    if (0 == handler)
        return 0;
    
    switch (touchScriptData->actionType)
    {
        case EventTouch::EventCode::BEGAN:
            _stack->pushString("began");
            break;
            
        case EventTouch::EventCode::MOVED:
            _stack->pushString("moved");
            break;
            
        case EventTouch::EventCode::ENDED:
            _stack->pushString("ended");
            break;
            
        case EventTouch::EventCode::CANCELLED:
            _stack->pushString("cancelled");
            break;
            
        default:
            return 0;
    }

    int ret = 0;

    Touch* touch = touchScriptData->touch;
    if (NULL != touch) {
        const Point pt = Director::getInstance()->convertToGL(touch->getLocationInView());
        _stack->pushFloat(pt.x);
        _stack->pushFloat(pt.y);
        ret = _stack->executeFunctionByHandler(handler, 3);
    }
    _stack->clean();
    return ret;
}

int LuaEngine::handleTouchesEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    TouchesScriptData* touchesScriptData = static_cast<TouchesScriptData*>(data);
    if (NULL == touchesScriptData->nativeObject || touchesScriptData->touches.size() == 0)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)touchesScriptData->nativeObject, ScriptHandlerMgr::HandlerType::TOUCHES);
    
    if (0 == handler)
        return 0;
    
    switch (touchesScriptData->actionType)
    {
        case EventTouch::EventCode::BEGAN:
            _stack->pushString("began");
            break;
            
        case EventTouch::EventCode::MOVED:
            _stack->pushString("moved");
            break;
            
        case EventTouch::EventCode::ENDED:
            _stack->pushString("ended");
            break;
            
        case EventTouch::EventCode::CANCELLED:
            _stack->pushString("cancelled");
            break;
            
        default:
            return 0;
    }
    
    Director* pDirector = Director::getInstance();
    lua_State *L = _stack->getLuaState();
    int ret = 0;

    lua_newtable(L);
    int i = 1;
    for (auto& touch : touchesScriptData->touches)
    {
        Point pt = pDirector->convertToGL(touch->getLocationInView());
        lua_pushnumber(L, pt.x);
        lua_rawseti(L, -2, i++);
        lua_pushnumber(L, pt.y);
        lua_rawseti(L, -2, i++);
        lua_pushinteger(L, touch->getID());
        lua_rawseti(L, -2, i++);
    }
    ret = _stack->executeFunctionByHandler(handler, 2);

    _stack->clean();
    return ret;
}

int LuaEngine::handleTableViewEvent(void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* eventData = static_cast<BasicScriptData*>(data);    
    if (nullptr == eventData->nativeObject || nullptr == eventData->value)
        return 0;
    
    LuaTableViewEventData* tableViewEventData = static_cast<LuaTableViewEventData*>(eventData->value);
    if (tableViewEventData->handlerType < ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL || tableViewEventData->handlerType > ScriptHandlerMgr::HandlerType::TABLEVIEW_NUMS_OF_CELLS )
        return 0;

    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, tableViewEventData->handlerType);
    
    if (0 == handler)
        return 0;
    
    int ret = 0;
    switch (tableViewEventData->handlerType)
    {
        case ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL:
        case ScriptHandlerMgr::HandlerType::SCROLLVIEW_ZOOM:
            {
                _stack->pushObject(static_cast<Object*>(eventData->nativeObject), "TableView");
                ret = _stack->executeFunctionByHandler(handler, 1);
            }
            break;
        case ScriptHandlerMgr::HandlerType::TABLECELL_TOUCHED:
        case ScriptHandlerMgr::HandlerType::TABLECELL_HIGHLIGHT:
        case ScriptHandlerMgr::HandlerType::TABLECELL_UNHIGHLIGHT:
        case ScriptHandlerMgr::HandlerType::TABLECELL_WILL_RECYCLE:
            {
                _stack->pushObject(static_cast<Object*>(eventData->nativeObject), "TableView");
                _stack->pushObject(static_cast<Object*>(tableViewEventData->value), "TableViewCell");
                ret = _stack->executeFunctionByHandler(handler, 2);
            }
            break;
        default:
            break;
    }
    
    return ret;
}

int LuaEngine::handlerControlEvent(void* data)
{
    if ( NULL == data )
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (NULL == basicScriptData->nativeObject)
        return 0;
    
    int controlEvents = *((int*)(basicScriptData->value));
    
    int handler = 0;
    int ret = 0;
    
    for (int i = 0; i < kControlEventTotalNumber; i++)
    {
        if ((controlEvents & (1 << i)))
        {
            ScriptHandlerMgr::HandlerType controlHandler = ScriptHandlerMgr::HandlerType((int)ScriptHandlerMgr::HandlerType::CONTROL_TOUCH_DOWN + i);
            handler = ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, controlHandler);
            
            if (0 != handler)
            {
                _stack->pushObject((Object*)basicScriptData->nativeObject, "Object");
                _stack->pushInt(controlEvents);
                ret = _stack->executeFunctionByHandler(handler, 2);
                _stack->clean();
            }
        }
    }

    return ret;    
}

void LuaEngine::extendLuaObject()
{    
    if ( NULL == _stack || NULL == _stack->getLuaState())
        return;
    
    lua_State* lua_S = _stack->getLuaState();
    extendWebsocket(lua_S);
    extendGLNode(lua_S);
    
    _stack->clean();
}

void LuaEngine::extendWebsocket(lua_State* lua_S)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    if (NULL == lua_S)
        return;
    
    lua_pushstring(lua_S,"WebSocket");
    lua_rawget(lua_S,LUA_REGISTRYINDEX);
    if (lua_istable(lua_S,-1))
    {
        lua_pushstring(lua_S,"registerScriptHandler");
        lua_pushcfunction(lua_S,tolua_Cocos2d_WebSocket_registerScriptHandler00);
        lua_rawset(lua_S,-3);
        lua_pushstring(lua_S,"unregisterScriptHandler");
        lua_pushcfunction(lua_S,tolua_Cocos2d_WebSocket_unregisterScriptHandler00);
        lua_rawset(lua_S,-3);
    }
#endif
}

void LuaEngine::extendGLNode(lua_State* lua_S)
{
    if (NULL == lua_S)
        return;
    
    lua_pushstring(lua_S,"GLNode");
    lua_rawget(lua_S,LUA_REGISTRYINDEX);
    if (lua_istable(lua_S,-1))
    {
        lua_pushstring(lua_S,"registerScriptDrawHandler");
        lua_pushcfunction(lua_S,tolua_Cocos2d_GLNode_registerScriptDrawHandler00);
        lua_rawset(lua_S,-3);
        lua_pushstring(lua_S,"unregisterScriptDrawHandler");
        lua_pushcfunction(lua_S,tolua_Cocos2d_GLNode_unregisterScriptDrawHandler00);
        lua_rawset(lua_S,-3);
    }
}

int LuaEngine::sendEventReturnArray(ScriptEvent* message,int numResults,Array& resultArray)
{
    if (nullptr == message || numResults <= 0)
        return 0;
    
    switch (message->type)
    {
        case kTableViewEvent:
            return handleTableViewEventReturnArray(message->data,numResults,resultArray);
            break;
        default:
            break;
    }
    return 0;
}

int LuaEngine::handleTableViewEventReturnArray(void* data,int numResults,Array& resultArray)
{
    if (nullptr == data || numResults <= 0)
        return 0;
    
    if (nullptr == data)
        return 0;
    
    BasicScriptData* eventData = static_cast<BasicScriptData*>(data);
    if (nullptr == eventData->nativeObject || nullptr == eventData->value)
        return 0;
    
    LuaTableViewEventData* tableViewEventData = static_cast<LuaTableViewEventData*>(eventData->value);
    if (tableViewEventData->handlerType < ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL || tableViewEventData->handlerType > ScriptHandlerMgr::HandlerType::TABLEVIEW_NUMS_OF_CELLS )
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, tableViewEventData->handlerType);
    
    if (0 == handler)
        return 0;
    
    int ret = 0;
    switch (tableViewEventData->handlerType)
    {
        case ScriptHandlerMgr::HandlerType::TABLECELL_SIZE_FOR_INDEX:
            {
                _stack->pushObject(static_cast<Object*>(eventData->nativeObject), "TableView");
                _stack->pushLong(*((long*)tableViewEventData->value));
                ret = _stack->executeFunctionReturnArray(handler, 2, 2, resultArray);
            }
            break;
        case ScriptHandlerMgr::HandlerType::TABLECELL_AT_INDEX:
            {
                _stack->pushObject(static_cast<Object*>(eventData->nativeObject), "TableView");
                _stack->pushLong(*((long*)tableViewEventData->value));
                ret = _stack->executeFunctionReturnArray(handler, 2, 1, resultArray);
            }
            break;
        case ScriptHandlerMgr::HandlerType::TABLEVIEW_NUMS_OF_CELLS:
            {
                _stack->pushObject(static_cast<Object*>(eventData->nativeObject), "TableView");
                ret = _stack->executeFunctionReturnArray(handler, 1, 1, resultArray);               
            }
            break;
        default:
            break;
    }
    
    return ret;
}

int LuaEngine::handleAssetsManagerEvent(void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* eventData = static_cast<BasicScriptData*>(data);
    if (nullptr == eventData->nativeObject || nullptr == eventData->value)
        return 0;
    
    LuaAssetsManagerEventData* assetsManagerEventData = static_cast<LuaAssetsManagerEventData*>(eventData->value);
    if (assetsManagerEventData->handlerType < ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS || assetsManagerEventData->handlerType > ScriptHandlerMgr::HandlerType::ASSETSMANAGER_ERROR )
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, assetsManagerEventData->handlerType);
    
    if (0 == handler)
        return 0;
    
    int ret = 0;
    switch (assetsManagerEventData->handlerType)
    {
        case ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS:
        case ScriptHandlerMgr::HandlerType::ASSETSMANAGER_ERROR:
        {
            _stack->pushInt(assetsManagerEventData->value);
            ret = _stack->executeFunctionByHandler(handler, 1);
        }
            break;
            
        case ScriptHandlerMgr::HandlerType::ASSETSMANAGER_SUCCESS:
        {
            ret = _stack->executeFunctionByHandler(handler, 0);
        }
            break;
            
        default:
            break;
    }
    
    return ret;
}

int LuaEngine::handleCocoStudioEventListener(void* data)
{
    
    if (nullptr == data)
        return 0;
    
    BasicScriptData* eventData = static_cast<BasicScriptData*>(data);
    if (nullptr == eventData->nativeObject || nullptr == eventData->value)
        return 0;
    
    LuaCocoStudioEventListenerData* listenerData = static_cast<LuaCocoStudioEventListenerData*>(eventData->value);
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
    
    if (0 == handler)
        return 0;
    
    _stack->pushObject(listenerData->objTarget, "Object");
    _stack->pushInt(listenerData->eventType);
    
    _stack->executeFunctionByHandler(handler, 2);
    _stack->clean();
    
    return 0;
}

int LuaEngine::handleArmatureWrapper(void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* eventData = static_cast<BasicScriptData*>(data);
    if (nullptr == eventData->nativeObject || nullptr == eventData->value)
        return 0;
    
    LuaArmatureWrapperEventData* wrapperData = static_cast<LuaArmatureWrapperEventData*>(eventData->value);
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
    
    if (0 == handler)
        return 0;
    
    switch (wrapperData->eventType)
    {
        case LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::MOVEMENT_EVENT:
            {
                LuaArmatureMovementEventData* movementData = static_cast<LuaArmatureMovementEventData*>(wrapperData->eventData);
                
                _stack->pushObject(movementData->objTarget, "Armature");
                _stack->pushInt(movementData->movementType);
                _stack->pushString(movementData->movementID.c_str());
                _stack->executeFunctionByHandler(handler, 3);
            }
            break;
        case LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FRAME_EVENT:
            {
                LuaArmatureFrameEventData* frameData = static_cast<LuaArmatureFrameEventData*>(wrapperData->eventData);
                
                _stack->pushObject(frameData->objTarget, "Bone");
                _stack->pushString(frameData->frameEventName.c_str());
                _stack->pushInt(frameData->originFrameIndex);
                _stack->pushInt(frameData->currentFrameIndex);
                _stack->executeFunctionByHandler(handler, 4);
            }
            break;
        case LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FILE_ASYNC:
            {
                _stack->pushFloat(*(float*)wrapperData->eventData);
                _stack->executeFunctionByHandler(handler, 1);
            }
            break;
        default:
            break;
    }
    
    _stack->clean();
    
    return 0;
}

NS_CC_END
