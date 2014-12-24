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

#include "LuaTouchEventManager.h"
#include "base/CCDirector.h"
#include "2d/CCLayer.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteBatchNode.h"
#include "physics/CCPhysicsWorld.h"

#include "LuaTouchTargetNode.h"
#include "base/ccUtils.h"
#include "base/CCEventDispatcher.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN

static LuaTouchEventManager* s_sharedLuaTouchEventManager = nullptr;

LuaTouchEventManager* LuaTouchEventManager::getInstance()
{
    if (s_sharedLuaTouchEventManager == nullptr)
    {
        s_sharedLuaTouchEventManager = new (std::nothrow) LuaTouchEventManager();
        if (!s_sharedLuaTouchEventManager->init())
        {
            delete s_sharedLuaTouchEventManager;
            s_sharedLuaTouchEventManager = nullptr;
            CCLOG("ERROR: Could not init LuaTouchEventManager");
        }
    }
    return s_sharedLuaTouchEventManager;
}

void LuaTouchEventManager::destroyInstance()
{
    //    log("---> LuaTouchEventManager::destroyInstance");
    CC_SAFE_DELETE(s_sharedLuaTouchEventManager);
}

LuaTouchEventManager::LuaTouchEventManager()
    : m_touchDispatchingEnabled(false)
    , _touchListener(nullptr)
	, _bDispatching(false)
{
    _touchableNodes.reserve(100);
    _touchingTargets.reserve(10);

    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Vec2(0.5f, 0.5f));
}

LuaTouchEventManager::~LuaTouchEventManager()
{
    //    log("---> Release LuaTouchEventManager");
    if (_running) {
        cleanup();
    }
}

bool LuaTouchEventManager::init()
{
    _running = true;

    auto size = Director::getInstance()->getWinSize();
    return initWithSize(size);
}

bool LuaTouchEventManager::initWithSize(const Size& size)
{
    setContentSize(size);
    return true;
}

std::string LuaTouchEventManager::getDescription() const
{
    return StringUtils::format("<LuaTouchEventManager | tag = %d>", _tag);
}

void LuaTouchEventManager::addTouchableNode(LuaEventNode *node)
{
    Node *activeNode = node->getActiveNode();
    if (!activeNode) return;
    if (!_touchableNodes.contains(node))
    {
        _touchableNodes.pushBack(node);
        _nodeLuaEventNodeMap.insert(std::make_pair(activeNode, node));
        //CCLOG("ADD TOUCHABLE NODE <%p>", node->getNode());
        if (!m_touchDispatchingEnabled)
        {
            enableTouchDispatching();
        }
    }
}

void LuaTouchEventManager::removeTouchableNode(LuaEventNode *node)
{
	if (_bDispatching) {
		return;
	}

    _touchableNodes.eraseObject(node);
    auto found = _nodeLuaEventNodeMap.find(node->getDetachedNode());
    if (found != _nodeLuaEventNodeMap.end())
    {
        _nodeLuaEventNodeMap.erase(found);
    }
    //CCLOG("REMOVE TOUCHABLE NODE <%p>", node->getNode());
    if (_touchableNodes.size() == 0 && m_touchDispatchingEnabled)
    {
        disableTouchDispatching();
        destroyInstance();
    }
}

void LuaTouchEventManager::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    if (!m_touchDispatchingEnabled || _touchableNodes.size() < 1) return;

    // save touches id
    for (auto it = touches.begin(); it != touches.end(); ++it)
    {
        m_touchingIds.insert(((Touch*)*it)->getID());
    }

    // check current in touching
    if (_touchingTargets.size())
    {
        dispatchingTouchEvent(touches, event, CCTOUCHADDED);
        return;
    }

    // start new touching event
    // sort touchable nodes
    sortAllTouchableNodes(_touchableNodes);

    // find touching target
    bool isTouchable = true;
    LuaEventNode *node = nullptr;
    LuaEventNode *checkTouchableNode = nullptr;
    LuaTouchTargetNode *touchTarget = nullptr;

    for (auto iter = _touchableNodes.begin(); iter != _touchableNodes.end(); ++iter)
    {
        checkTouchableNode = node = *iter;

        // check node is visible and capturing enabled
        isTouchable = true;
        do
        {
            isTouchable = isTouchable
                && checkTouchableNode->isRunning()
                && checkTouchableNode->isVisible()
                && checkTouchableNode->isTouchCaptureEnabled();
            checkTouchableNode = checkTouchableNode->getParent();
        } while (checkTouchableNode && isTouchable);
        if (!isTouchable) continue;

        // prepare for touch testing
        touchTarget = nullptr;
        Node *activeNode = node->getActiveNode();
        if (!activeNode) continue;
        const Rect boundingBox = utils::getCascadeBoundingBox(activeNode);

        // set touch target
        Touch *touch = nullptr;
        for (auto it = touches.begin(); it != touches.end(); ++it)
        {
            touch = (Touch*)*it;
            const Point touchPoint = touch->getLocation();

            if (boundingBox.containsPoint(touchPoint))
            {
                if (!touchTarget)
                {
                    touchTarget = LuaTouchTargetNode::create(node);
                }

                if (touchTarget->getTouchMode() == LuaEventNode::modeTouchesOneByOne)
                {
                    touchTarget->setTouchId(touch->getID());
                    break;
                }
            }
        }

        if (!touchTarget)
        {
            // touch points not in current target, try to next
            continue;
        }

        // try to dispatching event
        Vector<LuaEventNode*> path(10);
        node = touchTarget->getNode();
        do
        {
            path.pushBack(node);
            node = node->getParent();
        } while (node != nullptr /*&& node != this*/);

        // phase: capturing
        // from parent to child
        bool dispatchingContinue = true;
        int touchMode = touchTarget->getTouchMode();
        for (long i = path.size() - 1; dispatchingContinue && i >= 0; --i)
        {
            node = path.at(i);
            if (touchMode == LuaEventNode::modeTouchesAllAtOnce)
            {
                node->ccTouchesCaptureBegan(touches, touchTarget->getNode());
            }
            else
            {
                dispatchingContinue = node->ccTouchCaptureBegan(touchTarget->findTouch(touches), touchTarget->getNode());
            }
        }

        if (!dispatchingContinue)
        {
            // the target stop dispatching, try to next
            continue;
        }

        // phase: targeting
        node = touchTarget->getNode();
        bool ret = true;
        if (touchMode == LuaEventNode::modeTouchesAllAtOnce)
        {
            node->ccTouchesBegan(touches, event);
        }
        else
        {
            ret = node->ccTouchBegan(touchTarget->findTouch(touches), event);
        }

        if (ret)
        {
            _touchingTargets.pushBack(touchTarget);
            //CCLOG("ADD TOUCH TARGET [%p]", touchTarget->getNode()->getNode());
        }

        if (node->isTouchSwallowEnabled())
        {
            // target swallow touch event, stop dispatching
            break;
        }

        // continue dispatching, try to next
    }
}

void LuaTouchEventManager::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
    dispatchingTouchEvent(touches, event, CCTOUCHMOVED);
}

void LuaTouchEventManager::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
    for (auto it = touches.begin(); it != touches.end(); ++it)
    {
        m_touchingIds.erase(((Touch*)*it)->getID());
    }

    if (m_touchingIds.size())
    {
        dispatchingTouchEvent(touches, event, CCTOUCHREMOVED);
    }
    else
    {
        dispatchingTouchEvent(touches, event, CCTOUCHENDED);
        // remove all touching nodes
        //CCLOG("TOUCH ENDED, REMOVE ALL TOUCH TARGETS");
        _touchingTargets.clear();
    }
}

void LuaTouchEventManager::cleanDisabledNode()
{
	Vector<LuaEventNode*> toErase;

	for (auto it : _touchableNodes)
	{
		if (!it->isTouchEnabled())
		{
			toErase.pushBack(it);
		}
	}

	for (auto it : toErase)
	{
		removeTouchableNode(it);
	}
}

void LuaTouchEventManager::onTouchesCancelled(const std::vector<Touch*>& touches, Event *event)
{
    dispatchingTouchEvent(touches, event, CCTOUCHCANCELLED);
    // remove all touching nodes
    //CCLOG("TOUCH CANCELLED, REMOVE ALL TOUCH TARGETS");
    _touchingTargets.clear();
    // clear all touching points
	m_touchingIds.clear();
}

void LuaTouchEventManager::cleanup(void)
{
    //CCLOG("LuaEventManager cleanup, REMOVE ALL TOUCH TARGETS");
    _nodePriorityMap.clear();
    _touchableNodes.clear();
    _touchingTargets.clear();
    if (_touchListener) {
        _eventDispatcher->removeEventListener(_touchListener);
        _touchListener = nullptr;
    }
    _running = false;
}

void LuaTouchEventManager::sortAllTouchableNodes(Vector<LuaEventNode*>& nodes)
{
    ssize_t length = nodes.size();

    if (length < 1)
    {
        return;
    }

    // Reset priority index
    _nodePriorityIndex = 0;
    _nodePriorityMap.clear();

    auto rootNode = Director::getInstance()->getRunningScene();
    if (!rootNode)
    {
        return;
    }
    visitTarget(rootNode, true);

    // After sort: priority < 0, > 0
    std::sort(nodes.begin(), nodes.end(), [this](const LuaEventNode* l1, const LuaEventNode* l2) {
        return _nodePriorityMap[l1->getDetachedNode()] > _nodePriorityMap[l2->getDetachedNode()];
    });

#if DUMP_LISTENER_ITEM_PRIORITY_INFO
    log("-----------------------------------");
    for (auto& l : nodes)
    {
        log("listener priority: node ([%s]%p), priority (%d)", typeid(*l->getNode()).name(), l->getNode(), _nodePriorityMap[l->getNode()]);
    }
#endif
}

void LuaTouchEventManager::enableTouchDispatching()
{
    if (!_touchListener)
    {
        _touchListener = EventListenerTouchAllAtOnce::create();
        if (!_touchListener) {
            return;
        }
        _touchListener->onTouchesBegan = CC_CALLBACK_2(LuaTouchEventManager::onTouchesBegan, this);
        _touchListener->onTouchesMoved = CC_CALLBACK_2(LuaTouchEventManager::onTouchesMoved, this);
        _touchListener->onTouchesEnded = CC_CALLBACK_2(LuaTouchEventManager::onTouchesEnded, this);
        _touchListener->onTouchesCancelled = CC_CALLBACK_2(LuaTouchEventManager::onTouchesCancelled, this);
        _eventDispatcher->addEventListenerWithFixedPriority(_touchListener, -1);
    }
    m_touchDispatchingEnabled = true;
}

void LuaTouchEventManager::disableTouchDispatching()
{
    m_touchDispatchingEnabled = false;
}

void LuaTouchEventManager::dispatchingTouchEvent(const std::vector<Touch*>& touches, Event *pEvent, int event)
{
    _bDispatching = true;
    dispatchingTouchEventReal(touches, pEvent, event);
    _bDispatching = false;
    cleanDisabledNode();
}

void LuaTouchEventManager::dispatchingTouchEventReal(const std::vector<Touch*>& touches, Event *pEvent, int event)
{
    LuaEventNode *node = nullptr;
    LuaTouchTargetNode *touchTarget = nullptr;
    Touch *touch = nullptr;

    ssize_t count = _touchingTargets.size();
    //CCLOG("dispatchingTouchEvent COUNT [%zd]", count);
    for (ssize_t i = 0; i < count; ++i)
    {
        touchTarget = _touchingTargets.at(i);

        if (!touchTarget->getNode()->isRunning())
        {
            // target removed from scene, remove it
            //            CCLOG("REMOVE TARGET [%u]", i);
            _touchingTargets.erase(i);
            --count;
            --i;
            continue;
        }

        int touchMode = touchTarget->getTouchMode();
        if (touchMode != LuaEventNode::modeTouchesAllAtOnce)
        {
            touch = touchTarget->findTouch(touches);
            if (!touch)
            {
                // not found touch id for target, skip this target
                continue;
            }
        }

        // try to dispatching event
        Vector<LuaEventNode*> path(10);
        node = touchTarget->getNode();
        do
        {
            path.pushBack(node);
            node = node->getParent();
        } while (node != nullptr /*&& node != this*/);

        // phase: capturing
        // from parent to child
        for (long j = path.size() - 1; j >= 0; --j)
        {
            node = path.at(j);
            if (touchMode == LuaEventNode::modeTouchesAllAtOnce)
            {
                switch (event)
                {
                case CCTOUCHMOVED:
                    node->ccTouchesCaptureMoved(touches, touchTarget->getNode());
                    break;

                case CCTOUCHENDED:
                    node->ccTouchesCaptureEnded(touches, touchTarget->getNode());
                    break;

                case CCTOUCHCANCELLED:
                    node->ccTouchesCaptureCancelled(touches, touchTarget->getNode());
                    break;

                case CCTOUCHADDED:
                    node->ccTouchesCaptureAdded(touches, touchTarget->getNode());
                    break;

                case CCTOUCHREMOVED:
                    node->ccTouchesCaptureRemoved(touches, touchTarget->getNode());
                    break;
                }
            }
            else
            {
                switch (event)
                {
                case CCTOUCHMOVED:
                    node->ccTouchCaptureMoved(touch, touchTarget->getNode());
                    break;

                case CCTOUCHENDED:
                    node->ccTouchCaptureEnded(touch, touchTarget->getNode());
                    break;

                case CCTOUCHCANCELLED:
                    node->ccTouchCaptureCancelled(touch, touchTarget->getNode());
                    break;

                case CCTOUCHREMOVED:
                    if (touch->getID() == touchTarget->getTouchId())
                    {
                        node->ccTouchCaptureEnded(touch, touchTarget->getNode());
                    }
                    break;
                }
            }
        } // for (long j = path.size() - 1; j >= 0; --j)

        // phase: targeting
        node = touchTarget->getNode();
        if (touchMode == LuaEventNode::modeTouchesAllAtOnce)
        {
            switch (event)
            {
            case CCTOUCHMOVED:
                node->ccTouchesMoved(touches, pEvent);
                break;

            case CCTOUCHENDED:
                node->ccTouchesEnded(touches, pEvent);
                break;

            case CCTOUCHCANCELLED:
                node->ccTouchesCancelled(touches, pEvent);
                break;

            case CCTOUCHADDED:
                node->ccTouchesAdded(touches, pEvent);
                break;

            case CCTOUCHREMOVED:
                node->ccTouchesRemoved(touches, pEvent);
                break;
            }
        }
        else
        {
            switch (event)
            {
            case CCTOUCHMOVED:
                node->ccTouchMoved(touch, pEvent);
                break;

            case CCTOUCHENDED:
                node->ccTouchEnded(touch, pEvent);
                break;

            case CCTOUCHCANCELLED:
                node->ccTouchCancelled(touch, pEvent);
                break;

            case CCTOUCHREMOVED:
                if (touch->getID() == touchTarget->getTouchId())
                {
                    node->ccTouchEnded(touch, pEvent);
                    // target touching ended, remove it
                    //CCLOG("REMOVE TARGET [%zd]", i);
                    _touchingTargets.erase(i);
                    --count;
                    --i;
                }
                break;
            }
        }
    }
    //CCLOG("dispatchingTouchEvent end");
}

void LuaTouchEventManager::visitTarget(Node* node, bool isRootNode)
{
    int i = 0;
    auto& children = node->getChildren();

    auto childrenCount = children.size();

    if (childrenCount > 0)
    {
        Node* child = nullptr;
        // visit children zOrder < 0
        for (; i < childrenCount; i++)
        {
            child = children.at(i);

            if (child && child->getLocalZOrder() < 0)
                visitTarget(child, false);
            else
                break;
        }

        if (_nodeLuaEventNodeMap.find(node) != _nodeLuaEventNodeMap.end())
        {
            _globalZOrderNodeMap[node->getGlobalZOrder()].push_back(node);
        }

        for (; i < childrenCount; i++)
        {
            child = children.at(i);
            if (child)
                visitTarget(child, false);
        }
    }
    else
    {
        if (_nodeLuaEventNodeMap.find(node) != _nodeLuaEventNodeMap.end())
        {
            _globalZOrderNodeMap[node->getGlobalZOrder()].push_back(node);
        }
    }

    if (isRootNode)
    {
        std::vector<float> globalZOrders;
        globalZOrders.reserve(_globalZOrderNodeMap.size());

        for (const auto& e : _globalZOrderNodeMap)
        {
            globalZOrders.push_back(e.first);
        }

        std::sort(globalZOrders.begin(), globalZOrders.end(), [](const float a, const float b){
            return a < b;
        });

        for (const auto& globalZ : globalZOrders)
        {
            for (const auto& n : _globalZOrderNodeMap[globalZ])
            {
                _nodePriorityMap[n] = ++_nodePriorityIndex;
            }
        }

        _globalZOrderNodeMap.clear();
    }
}

NS_CC_END
