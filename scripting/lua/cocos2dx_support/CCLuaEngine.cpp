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

NS_CC_BEGIN

CCLuaEngine* CCLuaEngine::_defaultEngine = NULL;

CCLuaEngine* CCLuaEngine::defaultEngine(void)
{
    if (!_defaultEngine)
    {
        _defaultEngine = new CCLuaEngine();
        _defaultEngine->init();
    }
    return _defaultEngine;
}

CCLuaEngine::~CCLuaEngine(void)
{
    CC_SAFE_RELEASE(_stack);
    _defaultEngine = NULL;
}

bool CCLuaEngine::init(void)
{
    _stack = CCLuaStack::create();
    _stack->retain();
    return true;
}

void CCLuaEngine::addSearchPath(const char* path)
{
    _stack->addSearchPath(path);
}

void CCLuaEngine::addLuaLoader(lua_CFunction func)
{
    _stack->addLuaLoader(func);
}

void CCLuaEngine::removeScriptObjectByCCObject(CCObject* pObj)
{
    _stack->removeScriptObjectByCCObject(pObj);
}

void CCLuaEngine::removeScriptHandler(int nHandler)
{
    _stack->removeScriptHandler(nHandler);
}

int CCLuaEngine::executeString(const char *codes)
{
    int ret = _stack->executeString(codes);
    _stack->clean();
    return ret;
}

int CCLuaEngine::executeScriptFile(const char* filename)
{
    int ret = _stack->executeScriptFile(filename);
    _stack->clean();
    return ret;
}

int CCLuaEngine::executeGlobalFunction(const char* functionName)
{
    int ret = _stack->executeGlobalFunction(functionName);
    _stack->clean();
    return ret;
}

int CCLuaEngine::executeNodeEvent(CCNode* pNode, int nAction)
{
    int nHandler = pNode->getScriptHandler();
    if (!nHandler) return 0;
    
    switch (nAction)
    {
        case kCCNodeOnEnter:
            _stack->pushString("enter");
            break;
            
        case kCCNodeOnExit:
            _stack->pushString("exit");
            break;
            
        case kCCNodeOnEnterTransitionDidFinish:
            _stack->pushString("enterTransitionFinish");
            break;
            
        case kCCNodeOnExitTransitionDidStart:
            _stack->pushString("exitTransitionStart");
            break;
            
        case kCCNodeOnCleanup:
            _stack->pushString("cleanup");
            break;
            
        default:
            return 0;
    }
    int ret = _stack->executeFunctionByHandler(nHandler, 1);
    _stack->clean();
    return ret;
}

int CCLuaEngine::executeMenuItemEvent(CCMenuItem* pMenuItem)
{
    int nHandler = pMenuItem->getScriptTapHandler();
    if (!nHandler) return 0;
    
    _stack->pushInt(pMenuItem->getTag());
    _stack->pushCCObject(pMenuItem, "CCMenuItem");
    int ret = _stack->executeFunctionByHandler(nHandler, 2);
    _stack->clean();
    return ret;
}

int CCLuaEngine::executeNotificationEvent(CCNotificationCenter* pNotificationCenter, const char* pszName)
{
    int nHandler = pNotificationCenter->getObserverHandlerByName(pszName);
    if (!nHandler) return 0;
    
    _stack->pushString(pszName);
    int ret = _stack->executeFunctionByHandler(nHandler, 1);
    _stack->clean();
    return ret;
}

int CCLuaEngine::executeCallFuncActionEvent(CCCallFunc* pAction, CCObject* pTarget/* = NULL*/)
{
    int nHandler = pAction->getScriptHandler();
    if (!nHandler) return 0;
    
    if (pTarget)
    {
        _stack->pushCCObject(pTarget, "CCNode");
    }
    int ret = _stack->executeFunctionByHandler(nHandler, pTarget ? 1 : 0);
    _stack->clean();
    return ret;
}

int CCLuaEngine::executeSchedule(int nHandler, float dt, CCNode* pNode/* = NULL*/)
{
    if (!nHandler) return 0;
    _stack->pushFloat(dt);
    int ret = _stack->executeFunctionByHandler(nHandler, 1);
    _stack->clean();
    return ret;
}

int CCLuaEngine::executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch)
{
    CCTouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptTouchHandlerEntry();
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
    
    const CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    _stack->pushFloat(pt.x);
    _stack->pushFloat(pt.y);
    int ret = _stack->executeFunctionByHandler(nHandler, 3);
    _stack->clean();
    return ret;
}

int CCLuaEngine::executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches)
{
    CCTouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptTouchHandlerEntry();
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

    CCDirector* pDirector = CCDirector::sharedDirector();
    lua_State *L = _stack->getLuaState();
    lua_newtable(L);
    int i = 1;
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
    {
        CCTouch* pTouch = (CCTouch*)*it;
        CCPoint pt = pDirector->convertToGL(pTouch->getLocationInView());
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

int CCLuaEngine::executeLayerKeypadEvent(CCLayer* pLayer, int eventType)
{
    CCScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptKeypadHandlerEntry();
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

int CCLuaEngine::executeAccelerometerEvent(CCLayer* pLayer, CCAcceleration* pAccelerationValue)
{
    CCScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptAccelerateHandlerEntry();
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

int CCLuaEngine::executeEvent(int nHandler, const char* pEventName, CCObject* pEventSource /* = NULL*/, const char* pEventSourceClassName /* = NULL*/)
{
    _stack->pushString(pEventName);
    if (pEventSource)
    {
        _stack->pushCCObject(pEventSource, pEventSourceClassName ? pEventSourceClassName : "CCObject");
    }
    int ret = _stack->executeFunctionByHandler(nHandler, pEventSource ? 2 : 1);
    _stack->clean();
    return ret;
}

bool CCLuaEngine::handleAssert(const char *msg)
{
    bool ret = _stack->handleAssert(msg);
    _stack->clean();
    return ret;
}

int CCLuaEngine::reallocateScriptHandler(int nHandler)
{    
    int nRet = _stack->reallocateScriptHandler(nHandler);
    _stack->clean();
    return nRet;
}

NS_CC_END
