/****************************************************************************
 Copyright (c) 2012      cocos2d-x.org
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

#include "CCLuaEngine.h"
#include "tolua_fix.h"
#include "cocos2d.h"
#include "extensions/GUI/CCControlExtension/CCControl.h"
#include "LuaOpengl.h"
#include "lua_cocos2dx_manual.hpp"
#include "lua_cocos2dx_extension_manual.h"
#include "lua_cocos2dx_coco_studio_manual.hpp"
#include "lua_cocos2dx_ui_manual.hpp"

NS_CC_BEGIN

LuaEngine* LuaEngine::_defaultEngine = nullptr;

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
    _defaultEngine = nullptr;
}

bool LuaEngine::init(void)
{
    _stack = LuaStack::create();
    _stack->retain();
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

void LuaEngine::removeScriptObjectByObject(Ref* pObj)
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

int LuaEngine::executeNotificationEvent(__NotificationCenter* pNotificationCenter, const char* pszName)
{
    int nHandler = pNotificationCenter->getObserverHandlerByName(pszName);
    if (!nHandler) return 0;
    
    _stack->pushString(pszName);
    int ret = _stack->executeFunctionByHandler(nHandler, 1);
    _stack->clean();
    return ret;
}

int LuaEngine::executeCallFuncActionEvent(CallFunc* pAction, Ref* pTarget/* = NULL*/)
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

int LuaEngine::executeLayerTouchesEvent(Layer* pLayer, int eventType, __Set *pTouches)
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

int LuaEngine::executeEvent(int nHandler, const char* pEventName, Ref* pEventSource /* = NULL*/, const char* pEventSourceClassName /* = NULL*/)
{
    _stack->pushString(pEventName);
    if (pEventSource)
    {
        _stack->pushObject(pEventSource, pEventSourceClassName ? pEventSourceClassName : "cc.Ref");
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

bool LuaEngine::parseConfig(ConfigType type, const std::string& str)
{
    lua_getglobal(_stack->getLuaState(), "__onParseConfig");
    if (!lua_isfunction(_stack->getLuaState(), -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", "__onParseConfig");
        lua_pop(_stack->getLuaState(), 1);
        return false;
    }
    
    _stack->pushInt((int)type);
    _stack->pushString(str.c_str());
    
    return _stack->executeFunction(2);
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
    _stack->pushObject(menuItem, "cc.MenuItem");
    int ret = _stack->executeFunctionByHandler(handler, 2);
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
    
    Ref* target = static_cast<Ref*>(basicScriptData->value);
    if (NULL != target)
    {
        _stack->pushObject(target, "cc.Node");
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
            _stack->pushObject(commonInfo->eventSource, "cc.Ref");
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
        const cocos2d::Vec2 pt = Director::getInstance()->convertToGL(touch->getLocationInView());
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
        cocos2d::Vec2 pt = pDirector->convertToGL(touch->getLocationInView());
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
                _stack->pushObject((Ref*)basicScriptData->nativeObject, "cc.Ref");
                _stack->pushInt(controlEvents);
                ret = _stack->executeFunctionByHandler(handler, 2);
                _stack->clean();
            }
        }
    }

    return ret;    
}

int LuaEngine::handleEventAcc(void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (nullptr == basicScriptData->nativeObject || nullptr == basicScriptData->value)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, ScriptHandlerMgr::HandlerType::EVENT_ACC);
    if (0 == handler)
        return 0;
    
    lua_State* L = _stack->getLuaState();
    
    LuaEventAccelerationData* eventListennerAcc = static_cast<LuaEventAccelerationData*>(basicScriptData->value);    
    toluafix_pushusertype_ccobject(L, eventListennerAcc->event->_ID, &(eventListennerAcc->event->_luaID), (void*)(eventListennerAcc->event),"cc.Event");
    Acceleration*  accleration = static_cast<Acceleration*>(eventListennerAcc->acc);
    lua_pushnumber(L,accleration->x);
    lua_pushnumber(L,accleration->y);
    lua_pushnumber(L,accleration->z);
    lua_pushnumber(L,accleration->timestamp);
    int ret = _stack->executeFunctionByHandler(handler, 5);
    _stack->clean();
    return ret;
}

int LuaEngine::handleEventKeyboard(ScriptHandlerMgr::HandlerType type, void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (nullptr == basicScriptData->nativeObject || nullptr == basicScriptData->value)
        return 0;
    
    LuaEventKeyboarData* keyboardData = static_cast<LuaEventKeyboarData*>(basicScriptData->value);
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, type);
    if (0 == handler)
        return 0;
    
    lua_State* L = _stack->getLuaState();
    lua_pushinteger(L, keyboardData->keyCode);
    toluafix_pushusertype_ccobject(L, keyboardData->event->_ID, &(keyboardData->event->_luaID), (void*)(keyboardData->event),"cc.Event");
    int ret = _stack->executeFunctionByHandler(handler, 2);
    _stack->clean();
    return ret;
}

int LuaEngine::handleEventTouch(ScriptHandlerMgr::HandlerType type, void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (nullptr == basicScriptData->nativeObject || nullptr == basicScriptData->value)
        return 0;
    
    LuaEventTouchData* touchData = static_cast<LuaEventTouchData*>(basicScriptData->value);
    if (nullptr == touchData->touch || nullptr == touchData->event)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(basicScriptData->nativeObject, type);
    if (0 == handler)
        return 0;
    
    int ret = 0;
    
    Touch* touch = touchData->touch;
    if (NULL != touch) {
        _stack->pushObject(touchData->touch, "cc.Touch");
        _stack->pushObject(touchData->event, "cc.Event");
        ret = _stack->executeFunctionByHandler(handler, 2);
    }
    _stack->clean();
    
    return ret;
}

int LuaEngine::handleEventTouches(ScriptHandlerMgr::HandlerType type,void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (nullptr == basicScriptData->nativeObject || nullptr == basicScriptData->value)
        return 0;
    
    LuaEventTouchesData * touchesData = static_cast<LuaEventTouchesData*>(basicScriptData->value);
    if (nullptr == touchesData->event || touchesData->touches.size() == 0)
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)basicScriptData->nativeObject, type);
    
    if (0 == handler)
        return 0;
    
    lua_State *L = _stack->getLuaState();
    int ret = 0;
    
    lua_newtable(L);
    int i = 1;
    for (auto& touch : touchesData->touches)
    {
        _stack->pushInt(i);
        _stack->pushObject(touch, "cc.Touch");
        lua_rawset(L, -3);
        ++i;
    }
    _stack->pushObject(touchesData->event, "cc.Event");
    
    ret = _stack->executeFunctionByHandler(handler, 2);
    _stack->clean();
    return ret;
}

int LuaEngine::handleEventMouse(ScriptHandlerMgr::HandlerType type, void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (nullptr == basicScriptData->nativeObject || nullptr == basicScriptData->value)
        return 0;
    
    LuaEventMouseData * mouseData = static_cast<LuaEventMouseData*>(basicScriptData->value);
    if (nullptr == mouseData->event )
        return 0;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)basicScriptData->nativeObject, type);
    
    if (0 == handler)
        return 0;
    
    _stack->pushObject(mouseData->event, "cc.Event");
    int ret = _stack->executeFunctionByHandler(handler, 1);
    _stack->clean();
    
    return ret;
}

int LuaEngine::handleEvenCustom(void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData * basicData = static_cast<BasicScriptData*>(data);
    if (NULL == basicData->nativeObject || nullptr == basicData->value )
        return 0;
    
    EventCustom* eventCustom = static_cast<EventCustom*>(basicData->value);
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)basicData->nativeObject, ScriptHandlerMgr::HandlerType::EVENT_CUSTIOM);
    
    if (0 == handler)
        return 0;
    
    lua_State* L = _stack->getLuaState();
    toluafix_pushusertype_ccobject(L, eventCustom->_ID, &(eventCustom->_luaID), (void*)(eventCustom),"cc.EventCustom");
    int ret = _stack->executeFunctionByHandler(handler, 1);
    _stack->clean();
    
    return ret;
}

int LuaEngine::handleEvent(ScriptHandlerMgr::HandlerType type,void* data)
{
    switch (type)
    {
        case ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL:
        case ScriptHandlerMgr::HandlerType::SCROLLVIEW_ZOOM:
        case ScriptHandlerMgr::HandlerType::TABLECELL_TOUCHED:
        case ScriptHandlerMgr::HandlerType::TABLECELL_HIGHLIGHT:
        case ScriptHandlerMgr::HandlerType::TABLECELL_UNHIGHLIGHT:
        case ScriptHandlerMgr::HandlerType::TABLECELL_WILL_RECYCLE:
            {
                return handleTableViewEvent(type, data);
            }
            break;
        case ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS:
        case ScriptHandlerMgr::HandlerType::ASSETSMANAGER_ERROR:
        case ScriptHandlerMgr::HandlerType::ASSETSMANAGER_SUCCESS:
            {
                return handleAssetsManagerEvent(type, data);
            }
            break;
        case ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER:
            {
                return handleStudioEventListener(type, data);
            }
            break;
        case ScriptHandlerMgr::HandlerType::ARMATURE_EVENT:
            {
                return handleArmatureWrapper(type, data);
            }
            break;
        case ScriptHandlerMgr::HandlerType::EVENT_ACC:
            {
                return handleEventAcc(data);
            }
            break;
        case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_PRESSED:
        case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_RELEASED:
            {
                return handleEventKeyboard(type,data);
            }
            break;
        case ScriptHandlerMgr::HandlerType::EVENT_CUSTIOM:
            {
                return handleEvenCustom(data);
            }
            break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_BEGAN:
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_MOVED:
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_ENDED:
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_CANCELLED:
            {
                return handleEventTouch(type, data);
            }
            break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_BEGAN:
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_MOVED:
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_ENDED:
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_CANCELLED:
            {
                return handleEventTouches(type, data);
            }
            break;
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_DOWN:
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_UP:
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_MOVE:
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_SCROLL:
            {
                return handleEventMouse(type, data);
            }
            break;
        default:
            break;
    }
    
    return 0;
}

int LuaEngine::handleEvent(ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func)
{
    switch (type)
    {
        case ScriptHandlerMgr::HandlerType::TABLECELL_SIZE_FOR_INDEX:
        case ScriptHandlerMgr::HandlerType::TABLECELL_AT_INDEX:
        case ScriptHandlerMgr::HandlerType::TABLEVIEW_NUMS_OF_CELLS:
            {
                return handleTableViewEvent(type, data, numResults,func);
            }
            break;
        default:
            break;
    }
    
    return 0;
}

int LuaEngine::handleTableViewEvent(ScriptHandlerMgr::HandlerType type,void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* eventData = static_cast<BasicScriptData*>(data);
    if (nullptr == eventData->nativeObject || nullptr == eventData->value)
        return 0;
    
    LuaTableViewEventData* tableViewData = static_cast<LuaTableViewEventData*>(eventData->value);
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, type);
    
    if (0 == handler)
        return 0;
    
    Ref* obj = static_cast<Ref*>(eventData->nativeObject);
    if (nullptr == obj)
        return 0;
    
    int ret = 0;
    switch (type)
    {
        case ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL:
        case ScriptHandlerMgr::HandlerType::SCROLLVIEW_ZOOM:
        {
            toluafix_pushusertype_ccobject(_stack->getLuaState(), obj->_ID, &(obj->_luaID), (void*)(obj),"cc.TableView");
            ret = _stack->executeFunctionByHandler(handler, 1);
        }
            break;
        case ScriptHandlerMgr::HandlerType::TABLECELL_TOUCHED:
        case ScriptHandlerMgr::HandlerType::TABLECELL_HIGHLIGHT:
        case ScriptHandlerMgr::HandlerType::TABLECELL_UNHIGHLIGHT:
        case ScriptHandlerMgr::HandlerType::TABLECELL_WILL_RECYCLE:
        {
            Ref* cellObject = static_cast<Ref*>(tableViewData->value);
            if (nullptr == cellObject) {
                break;
            }
            toluafix_pushusertype_ccobject(_stack->getLuaState(), obj->_ID, &(obj->_luaID), (void*)(obj),"cc.TableView");
            toluafix_pushusertype_ccobject(_stack->getLuaState(), cellObject->_ID, &(cellObject->_luaID), (void*)(cellObject),"cc.TableViewCell");
            ret = _stack->executeFunctionByHandler(handler, 2);
        }
            break;
        default:
            break;
    }
    
    return ret;

}

int LuaEngine::handleTableViewEvent(ScriptHandlerMgr::HandlerType handlerType,void* data, int numResults, const std::function<void(lua_State*,int)>& func)
{
    if (nullptr == data || numResults <= 0)
        return 0;
    
    BasicScriptData* eventData = static_cast<BasicScriptData*>(data);
    if (nullptr == eventData->nativeObject || nullptr == eventData->value)
        return 0;
    
    LuaTableViewEventData* tableViewData = static_cast<LuaTableViewEventData*>(eventData->value);
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, handlerType);
    
    if (0 == handler)
        return 0;
    
    Ref* obj = static_cast<Ref*>(eventData->nativeObject);
    if (nullptr == obj)
        return 0;
    
    int ret = 0;
    switch (handlerType)
    {
        case ScriptHandlerMgr::HandlerType::TABLECELL_SIZE_FOR_INDEX:
        {
            toluafix_pushusertype_ccobject(_stack->getLuaState(), obj->_ID, &(obj->_luaID), (void*)(obj),"cc.TableView");
            _stack->pushLong(*((ssize_t*)tableViewData->value));
            ret = _stack->executeFunction(handler, 2, 2, func);
        }
            break;
        case ScriptHandlerMgr::HandlerType::TABLECELL_AT_INDEX:
        {
            toluafix_pushusertype_ccobject(_stack->getLuaState(), obj->_ID, &(obj->_luaID), (void*)(obj),"cc.TableView");
            _stack->pushLong(*((ssize_t*)tableViewData->value));
            ret = _stack->executeFunction(handler, 2, 1, func);
        }
            break;
        case ScriptHandlerMgr::HandlerType::TABLEVIEW_NUMS_OF_CELLS:
        {
            toluafix_pushusertype_ccobject(_stack->getLuaState(), obj->_ID, &(obj->_luaID), (void*)(obj),"cc.TableView");
            ret = _stack->executeFunction(handler, 1, 1, func);
        }
            break;
        default:
            break;
    }
    
    return ret;
}

int LuaEngine::handleAssetsManagerEvent(ScriptHandlerMgr::HandlerType type,void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* eventData = static_cast<BasicScriptData*>(data);
    if (nullptr == eventData->nativeObject || nullptr == eventData->value)
        return 0;
    
    LuaAssetsManagerEventData* assetsManagerData = static_cast<LuaAssetsManagerEventData*>(eventData->value);
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, type);
    
    if (0 == handler)
        return 0;
    
    int ret = 0;
    switch (type)
    {
        case ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS:
        case ScriptHandlerMgr::HandlerType::ASSETSMANAGER_ERROR:
            {
                _stack->pushInt(assetsManagerData->value);
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

int LuaEngine::handleStudioEventListener(ScriptHandlerMgr::HandlerType type,void* data)
{
    if (nullptr == data)
        return 0;
    
    BasicScriptData* eventData = static_cast<BasicScriptData*>(data);
    if (nullptr == eventData->nativeObject || nullptr == eventData->value)
        return 0;
    
    LuaStudioEventListenerData* listenerData = static_cast<LuaStudioEventListenerData*>(eventData->value);
    
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER);
    
    if (0 == handler)
        return 0;
    
    _stack->pushObject(listenerData->objTarget, "cc.Ref");
    _stack->pushInt(listenerData->eventType);
    
    _stack->executeFunctionByHandler(handler, 2);
    _stack->clean();
    
    return 0;
}

int LuaEngine::handleArmatureWrapper(ScriptHandlerMgr::HandlerType type,void* data)
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
            
                _stack->pushObject(movementData->objTarget, "ccs.Armature");
                _stack->pushInt(movementData->movementType);
                _stack->pushString(movementData->movementID.c_str());
                _stack->executeFunctionByHandler(handler, 3);
            }
            break;
        case LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FRAME_EVENT:
            {
                LuaArmatureFrameEventData* frameData = static_cast<LuaArmatureFrameEventData*>(wrapperData->eventData);
            
                _stack->pushObject(frameData->objTarget, "ccs.Bone");
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

int LuaEngine::reload(const char* moduleFileName)
{
    return _stack->reload(moduleFileName);
}

NS_CC_END
