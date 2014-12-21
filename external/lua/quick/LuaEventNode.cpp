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

#include "LuaEventNode.h"
#include "LuaTouchEventManager.h"
#include "LuaNodeManager.h"
#include "CCLuaEngine.h"
#include "tolua_fix.h"


NS_CC_BEGIN

LuaEventNode *LuaEventNode::create(Node *node)
{
    LuaEventNode *lnode = new LuaEventNode(node);
    lnode->autorelease();
//    log("---> Create LuaEventNode %p with node: %p", lnode, node);
    return lnode;
}

LuaEventNode::LuaEventNode(Node *node)
: _bTouchCaptureEnabled(true)
, _bTouchSwallowEnabled(true)
, _bTouchEnabled(false)
, _eTouchMode(modeTouchesOneByOne)
, _nodePreuse(nullptr)
{
    _node = node;
}

LuaEventNode::~LuaEventNode()
{
//    log("---> Release LuaEventNode %p", this);
}

Node *LuaEventNode::getDetachedNode() const
{
    if (_node)
    {
        return  _node;
    }
    return  _nodePreuse;
}

Node *LuaEventNode::getActiveNode() const
{
    return  _node;
}

LuaEventNode* LuaEventNode::getParent()
{
    if (!_node) return nullptr;
    Node *node = _node;
    LuaEventNode *eventNode = nullptr;

    do {
        node = node->getParent();
        if (nullptr == node) {
            //have no parent, return
            return nullptr;
        }

        eventNode = LuaNodeManager::getInstance()->getLuaNodeByNode(node, false);
        if (eventNode) {
            //find the eventNode
            return eventNode;
        }
    } while (true);

    return nullptr;
}

bool LuaEventNode::isVisible() const
{
    if (!_node) { return false; }
    Node *node = _node;
    do {
        if (!node) {
            // here reach the top node
            return true;
        }
        if (!node->isVisible()) {
            return false;
        }
        node = node->getParent();
    } while (true);

    return false;
}

bool LuaEventNode::isRunning() const
{
    if (_node)
    {
        return _node->isRunning();
    }
    return false;
}

void LuaEventNode::detachNode()
{
//    log("---> Detach LuaEventNode %p", this);
    _nodePreuse = _node;
    _node = nullptr;
}

// ----------------------------------------

void LuaEventNode::registerWithTouchDispatcher()
{
    //    CCLOG("CCNODE: REGISTER WITH TOUCH DISPATHCER <%p>", this);
    LuaTouchEventManager *mng = LuaTouchEventManager::getInstance();
    if (mng)
    {
        mng->addTouchableNode(this);
    }
}

void LuaEventNode::unregisterWithTouchDispatcher()
{
    //    CCLOG("CCNODE: UNREGISTER WITH TOUCH DISPATHCER <%p>", this);
    LuaTouchEventManager *mng = LuaTouchEventManager::getInstance();
    if (mng)
    {
        mng->removeTouchableNode(this);
    }
}

bool LuaEventNode::isTouchCaptureEnabled()
{
    return _bTouchCaptureEnabled;
}

void LuaEventNode::setTouchCaptureEnabled(bool value)
{
    _bTouchCaptureEnabled = value;
}

bool LuaEventNode::isTouchSwallowEnabled()
{
    return _bTouchSwallowEnabled;
}

void LuaEventNode::setTouchSwallowEnabled(bool value)
{
    _bTouchSwallowEnabled = value;
}

bool LuaEventNode::ccTouchCaptureBegan(Touch *pTouch, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pTarget);
    {
        return executeScriptTouchHandler(CCTOUCHBEGAN, pTouch, NODE_TOUCH_CAPTURING_PHASE);
    }
}

bool LuaEventNode::ccTouchCaptureMoved(Touch *pTouch, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pTarget);
    {
        return executeScriptTouchHandler(CCTOUCHMOVED, pTouch, NODE_TOUCH_CAPTURING_PHASE);
    }
}

void LuaEventNode::ccTouchCaptureEnded(Touch *pTouch, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pTarget);
    {
        executeScriptTouchHandler(CCTOUCHENDED, pTouch, NODE_TOUCH_CAPTURING_PHASE);
    }
}

void LuaEventNode::ccTouchCaptureCancelled(Touch *pTouch, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pTarget);
    {
        executeScriptTouchHandler(CCTOUCHCANCELLED, pTouch, NODE_TOUCH_CAPTURING_PHASE);
    }
}

void LuaEventNode::ccTouchesCaptureBegan(const std::vector<Touch*>& touches, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pTarget);
    {
        executeScriptTouchHandler(CCTOUCHBEGAN, touches, NODE_TOUCH_CAPTURING_PHASE);
    }
}

void LuaEventNode::ccTouchesCaptureMoved(const std::vector<Touch*>& touches, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pTarget);
    {
        executeScriptTouchHandler(CCTOUCHMOVED, touches, NODE_TOUCH_CAPTURING_PHASE);
    }
}

void LuaEventNode::ccTouchesCaptureEnded(const std::vector<Touch*>& touches, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pTarget);
    {
        executeScriptTouchHandler(CCTOUCHENDED, touches, NODE_TOUCH_CAPTURING_PHASE);
    }
}

void LuaEventNode::ccTouchesCaptureCancelled(const std::vector<Touch*>& touches, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pTarget);
    {
        executeScriptTouchHandler(CCTOUCHCANCELLED, touches, NODE_TOUCH_CAPTURING_PHASE);
    }
}

void LuaEventNode::ccTouchesCaptureAdded(const std::vector<Touch*>& touches, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pTarget);
    {
        executeScriptTouchHandler(CCTOUCHADDED, touches, NODE_TOUCH_CAPTURING_PHASE);
    }
}

void LuaEventNode::ccTouchesCaptureRemoved(const std::vector<Touch*>& touches, LuaEventNode *pTarget)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pTarget);
    {
        executeScriptTouchHandler(CCTOUCHREMOVED, touches, NODE_TOUCH_CAPTURING_PHASE);
    }
}

bool LuaEventNode::isTouchEnabled()
{
    return (_node!=nullptr) && _bTouchEnabled;
}

void LuaEventNode::setLuaTouchEnabled(bool enabled)
{
    if (_bTouchEnabled != enabled)
    {
        _bTouchEnabled = enabled;

        if (enabled)
        {
            registerWithTouchDispatcher();
        }
        else
        {
            unregisterWithTouchDispatcher();
        }
    }
}

void LuaEventNode::setTouchMode(int mode)
{
    if(_eTouchMode != mode)
    {
        _eTouchMode = mode;
        
		if( _bTouchEnabled)
        {
			setLuaTouchEnabled(false);
			setLuaTouchEnabled(true);
		}
    }
}

int LuaEventNode::getTouchMode()
{
    return _eTouchMode;
}

bool LuaEventNode::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHBEGAN, pTouch);
    }
    return true;
}

void LuaEventNode::ccTouchMoved(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHMOVED, pTouch);
    }
}

void LuaEventNode::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHENDED, pTouch);
    }
}

void LuaEventNode::ccTouchCancelled(Touch *pTouch, Event *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHCANCELLED, pTouch);
    }
}

void LuaEventNode::ccTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHBEGAN, touches);
    }
}

void LuaEventNode::ccTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHMOVED, touches);
    }
}

void LuaEventNode::ccTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHENDED, touches);
    }
}

void LuaEventNode::ccTouchesCancelled(const std::vector<Touch*>& touches, Event *pEvent)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHCANCELLED, touches);
    }
}

void LuaEventNode::ccTouchesAdded(const std::vector<Touch*>& touches, Event *pEvent)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHADDED, touches);
    }
}

void LuaEventNode::ccTouchesRemoved(const std::vector<Touch*>& touches, Event *pEvent)
{
    CC_UNUSED_PARAM(touches);
    CC_UNUSED_PARAM(pEvent);
    {
        executeScriptTouchHandler(CCTOUCHREMOVED, touches);
    }
}

static LuaStack * initExecParam(Node *node, int phase)
{
    if (!node) return nullptr;
    int  id = node->_luaID;
    if (id<1)
    {
        return nullptr;
    }
    
    LuaEngine* engine = LuaEngine::getInstance();
    auto stack = engine->getLuaStack();
    stack->clean();
    
    auto L = stack->getLuaState();
    luaL_getmetatable(L, "cc.Node");                             /* stack: mt */
    lua_pushliteral(L, "EventDispatcher");
    lua_rawget(L, -2);                                           /* stack: mt func */
    lua_pushstring(L, "tolua_ubox");                             /* stack: mt func key */
    lua_rawget(L, -3);                                           /* stack: mt func ubox */
    if (lua_isnil(L, -1))
    {
        // use global ubox
        lua_pop(L, 1);                                              /* stack: mt func */
        lua_pushstring(L, "tolua_ubox");                            /* stack: mt func key */
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: mt func ubox */
    };
    lua_pushlightuserdata(L, node);                                 /* stack: mt func ubox ptr */
    lua_rawget(L,-2);                                               /* stack: mt func ubox ud */
    if (lua_isnil(L, -1))
    {
        stack->clean();
        return nullptr;
    }
    
    int etype = (phase == NODE_TOUCH_CAPTURING_PHASE) ? NODE_TOUCH_CAPTURE_EVENT : NODE_TOUCH_EVENT;
    lua_pushnumber(L, etype);                                       /* stack: mt func ubox ud etype */
    lua_remove(L, -3);                                              /* stack: mt func ud etype */

    return stack;
}

static int callNodeEventDispatcher(LuaStack *stack, LuaValueDict &event)
{
    auto L = stack->getLuaState();
    stack->pushLuaValueDict(event);                            /* stack: mt func ud phase evt */
    int rn = stack->executeFunction(3);
    if (rn==1)
    {
        bool b = lua_toboolean(L, -1);
        if (!b)
        {
            rn = 0;
        }
    }
    else
    {
        rn = 0;
    }
    
    stack->clean();
    return rn;
}

int LuaEventNode::executeScriptTouchHandler(int nEventType, Touch *pTouch, int phase /* = NODE_TOUCH_TARGETING_PHASE */)
{
    auto stack = initExecParam(this->getActiveNode(), phase);
    if (!stack)
    {
        return 0;
    }
    
    LuaValueDict event;
    switch (nEventType)
    {
        case CCTOUCHBEGAN:
            event["name"] = LuaValue::stringValue("began");
            break;
            
        case CCTOUCHMOVED:
            event["name"] = LuaValue::stringValue("moved");
            break;
            
        case CCTOUCHENDED:
            event["name"] = LuaValue::stringValue("ended");
            break;
            
        case CCTOUCHCANCELLED:
            event["name"] = LuaValue::stringValue("cancelled");
            break;
            
        default:
            CCAssert(false, "INVALID touch event");
            return 0;
    }
    
    event["mode"] = LuaValue::intValue((int)Touch::DispatchMode::ONE_BY_ONE);
    switch (phase)
    {
        case NODE_TOUCH_CAPTURING_PHASE:
            event["phase"] = LuaValue::stringValue("capturing");
            break;
            
        case NODE_TOUCH_TARGETING_PHASE:
            event["phase"] = LuaValue::stringValue("targeting");
            break;
            
        default:
            event["phase"] = LuaValue::stringValue("unknown");
    }
    
    const Point pt = Director::getInstance()->convertToGL(pTouch->getLocationInView());
    event["x"] = LuaValue::floatValue(pt.x);
    event["y"] = LuaValue::floatValue(pt.y);
    const Point prev = Director::getInstance()->convertToGL(pTouch->getPreviousLocationInView());
    event["prevX"] = LuaValue::floatValue(prev.x);
    event["prevY"] = LuaValue::floatValue(prev.y);
    
    
    return callNodeEventDispatcher(stack, event);
}

int LuaEventNode::executeScriptTouchHandler(int nEventType, const std::vector<Touch*>& touches, int phase /* = NODE_TOUCH_TARGETING_PHASE */)
{
    auto stack = initExecParam(this->getActiveNode(), phase);
    if (!stack)
    {
        return 0;
    }
    
    LuaValueDict event;
    switch (nEventType)
    {
        case CCTOUCHBEGAN:
            event["name"] = LuaValue::stringValue("began");
            break;
            
        case CCTOUCHMOVED:
            event["name"] = LuaValue::stringValue("moved");
            break;
            
        case CCTOUCHENDED:
            event["name"] = LuaValue::stringValue("ended");
            break;
            
        case CCTOUCHCANCELLED:
            event["name"] = LuaValue::stringValue("cancelled");
            break;
            
        case CCTOUCHADDED:
            event["name"] = LuaValue::stringValue("added");
            break;
            
        case CCTOUCHREMOVED:
            event["name"] = LuaValue::stringValue("removed");
            break;
            
        default:
            return 0;
    }
    
    event["mode"] = LuaValue::intValue((int)Touch::DispatchMode::ALL_AT_ONCE);
    switch (phase)
    {
        case NODE_TOUCH_CAPTURING_PHASE:
            event["phase"] = LuaValue::stringValue("capturing");
            break;
            
        case NODE_TOUCH_TARGETING_PHASE:
            event["phase"] = LuaValue::stringValue("targeting");
            break;
            
        default:
            event["phase"] = LuaValue::stringValue("unknown");
    }
    
    LuaValueDict points;
    Director* pDirector = Director::getInstance();
    char touchId[16];
    for (auto touchIt = touches.begin(); touchIt != touches.end(); ++touchIt)
    {
        LuaValueDict point;
        Touch* pTouch = (Touch*)*touchIt;
        sprintf(touchId, "%d", pTouch->getID());
        point["id"] = LuaValue::stringValue(touchId);
        
        const Point pt = pDirector->convertToGL(pTouch->getLocationInView());
        point["x"] = LuaValue::floatValue(pt.x);
        point["y"] = LuaValue::floatValue(pt.y);
        const Point prev = pDirector->convertToGL(pTouch->getPreviousLocationInView());
        point["prevX"] = LuaValue::floatValue(prev.x);
        point["prevY"] = LuaValue::floatValue(prev.y);
        
        points[touchId] = LuaValue::dictValue(point);
    }
    event["points"] = LuaValue::dictValue(points);

    return callNodeEventDispatcher(stack, event);
}

NS_CC_END
