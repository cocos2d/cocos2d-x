/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#include "event/ScriptEventCenter.h"
#include "base/CCDirector.h"
#include "2d/CCLayer.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteBatchNode.h"
#include "physics/CCPhysicsWorld.h"
#include "deprecated/CCString.h"
#include "event/CCTouchDispatcher.h"
#include "event/CCTouchTargetNode.h"
#include "deprecated/CCArray.h"

NS_CC_BEGIN

ScriptEventCenter::ScriptEventCenter()
: m_touchableNodes(NULL)
, m_touchingTargets(NULL)
, m_touchDispatchingEnabled(false)
, _touchListener(NULL)
{
    m_touchableNodes = __Array::createWithCapacity(100);
    m_touchableNodes->retain();
    m_touchingTargets = __Array::createWithCapacity(10);
    m_touchingTargets->retain();

    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Vec2(0.5f, 0.5f));
}

ScriptEventCenter::~ScriptEventCenter()
{
    if (_running) {
        cleanup();
    }
    CC_SAFE_RELEASE(m_touchableNodes);
    CC_SAFE_RELEASE(m_touchingTargets);
}

bool ScriptEventCenter::init()
{
    _running = true;

    auto size = Director::getInstance()->getWinSize();
    return initWithSize(size);
}

bool ScriptEventCenter::initWithSize(const Size& size)
{
    setContentSize(size);
    return true;
}

ScriptEventCenter* ScriptEventCenter::create()
{
    ScriptEventCenter *ret = new ScriptEventCenter();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

std::string ScriptEventCenter::getDescription() const
{
    return StringUtils::format("<ScriptEventCenter | tag = %d>", _tag);
}

void ScriptEventCenter::addTouchableNode(Node *node)
{
    if (!m_touchableNodes->containsObject(node))
    {
        m_touchableNodes->addObject(node);
//        CCLOG("ADD TOUCHABLE NODE <%p>", node);
        if (!m_touchDispatchingEnabled)
        {
            enableTouchDispatching();
        }
    }
}

void ScriptEventCenter::removeTouchableNode(Node *node)
{
    m_touchableNodes->removeObject(node);
//    CCLOG("REMOVE TOUCHABLE NODE <%p>", node);
    if (m_touchableNodes->count() == 0 && m_touchDispatchingEnabled)
    {
        disableTouchDispatching();
    }
}

void ScriptEventCenter::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    if (!m_touchDispatchingEnabled) return;

    // save touches id
    for (auto it = touches.begin(); it != touches.end(); ++it)
    {
        m_touchingIds.insert(((Touch*)*it)->getID());
    }

    // check current in touching
    if (m_touchingTargets->count())
    {
        dispatchingTouchEvent(touches, event, CCTOUCHADDED);
        return;
    }

    // start new touching event
    // sort touchable nodes
    sortAllTouchableNodes(m_touchableNodes);

    // find touching target
    bool isTouchable = true;
    Ref *obj = NULL;
    Node *node = NULL;
    Node *checkTouchableNode = NULL;
    CCTouchTargetNode *touchTarget = NULL;

    CCARRAY_FOREACH(m_touchableNodes, obj)
    {
        checkTouchableNode = node = dynamic_cast<Node*>(obj);

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
        touchTarget = NULL;
        const Rect boundingBox = node->getCascadeBoundingBox();

        // set touch target
        Touch *touch = NULL;
        for (auto it = touches.begin(); it != touches.end(); ++it)
        {
            touch = (Touch*)*it;
            const Point touchPoint = touch->getLocation();

            if (boundingBox.containsPoint(touchPoint))
            {
                if (!touchTarget)
                {
                    touchTarget = CCTouchTargetNode::create(node);
                }

                if (touchTarget->getTouchMode() == Node::modeTouchesOneByOne)
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
        __Array *path = __Array::createWithCapacity(10);
        node = touchTarget->getNode();
        do
        {
            path->addObject(node);
            node = node->getParent();
        } while (node != NULL && node != this);

        // phase: capturing
        // from parent to child
        bool dispatchingContinue = true;
        int touchMode = touchTarget->getTouchMode();
        for (long i = path->count() - 1; dispatchingContinue && i >= 0; --i)
        {
            node = dynamic_cast<Node*>(path->getObjectAtIndex(i));
            if (touchMode == Node::modeTouchesAllAtOnce)
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
        if (touchMode == Node::modeTouchesAllAtOnce)
        {
            node->ccTouchesBegan(touches, event);
        }
        else
        {
            ret = node->ccTouchBegan(touchTarget->findTouch(touches), event);
        }

        if (ret)
        {
            m_touchingTargets->addObject(touchTarget);
            //            CCLOG("ADD TOUCH TARGET [%p]", touchTarget);
        }

        if (node->isTouchSwallowEnabled())
        {
            // target swallow touch event, stop dispatching
            break;
        }
        
        // continue dispatching, try to next
    }
}

void ScriptEventCenter::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
    dispatchingTouchEvent(touches, event, CCTOUCHMOVED);
}

void ScriptEventCenter::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
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
//    CCLOG("TOUCH ENDED, REMOVE ALL TOUCH TARGETS");
        m_touchingTargets->removeAllObjects();
    }
}

void ScriptEventCenter::onTouchesCancelled(const std::vector<Touch*>& touches, Event *event)
{
    dispatchingTouchEvent(touches, event, CCTOUCHCANCELLED);
    // remove all touching nodes
//    CCLOG("TOUCH CANCELLED, REMOVE ALL TOUCH TARGETS");
    m_touchingTargets->removeAllObjects();
}

void ScriptEventCenter::cleanup(void)
{
    m_touchableNodes->removeAllObjects();
    m_touchingTargets->removeAllObjects();
    if (_touchListener) {
        _eventDispatcher->removeEventListener(_touchListener);
        _touchListener = NULL;
    }
    _running = false;
}

void ScriptEventCenter::sortAllTouchableNodes(__Array *nodes)
{
    ssize_t i, j, length = nodes->data->num;
    Node **x = (Node**)nodes->data->arr;
    Node *tempItem;

    // insertion sort
    for(i = 1; i < length; i++)
    {
        tempItem = x[i];
        j = i - 1;

        while(j >= 0 && (tempItem->m_drawOrder > x[j]->m_drawOrder))
        {
            x[j + 1] = x[j];
            j = j - 1;
        }
        x[j + 1] = tempItem;
    }

    // debug
//        CCLOG("----------------------------------------");
//        for(i=0; i<length; i++)
//        {
//            tempItem = x[i];
//            CCLOG("[%03d] m_drawOrder = %u, w = %0.2f, h = %0.2f", i, tempItem->m_drawOrder, tempItem->getCascadeBoundingBox().size.width, tempItem->getCascadeBoundingBox().size.height);
//        }
}

void ScriptEventCenter::enableTouchDispatching()
{
    if (!_touchListener)
    {
        _touchListener = EventListenerTouchAllAtOnce::create();
        if (!_touchListener) {
            return;
        }
        _touchListener->onTouchesBegan = CC_CALLBACK_2(ScriptEventCenter::onTouchesBegan, this);
        _touchListener->onTouchesMoved = CC_CALLBACK_2(ScriptEventCenter::onTouchesMoved, this);
        _touchListener->onTouchesEnded = CC_CALLBACK_2(ScriptEventCenter::onTouchesEnded, this);
        _touchListener->onTouchesCancelled = CC_CALLBACK_2(ScriptEventCenter::onTouchesCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    }
    m_touchDispatchingEnabled = true;
}

void ScriptEventCenter::disableTouchDispatching()
{
    m_touchDispatchingEnabled = false;
}

void ScriptEventCenter::dispatchingTouchEvent(const std::vector<Touch*>& touches, Event *pEvent, int event)
{
    Node *node = NULL;
    CCTouchTargetNode *touchTarget = NULL;
    Touch *touch = NULL;

    ssize_t count = m_touchingTargets->count();
//    CCLOG("TOUCH TARGETS COUNT [%u]", count);
    for (ssize_t i = 0; i < count; ++i)
    {
        touchTarget = dynamic_cast<CCTouchTargetNode*>(m_touchingTargets->getObjectAtIndex(i));

        if (!touchTarget->getNode()->isRunning())
        {
            // target removed from scene, remove it
//            CCLOG("REMOVE TARGET [%u]", i);
            m_touchingTargets->removeObjectAtIndex(i);
            --count;
            --i;
            continue;
        }

        int touchMode = touchTarget->getTouchMode();
        if (touchMode != Node::modeTouchesAllAtOnce)
        {
            touch = touchTarget->findTouch(touches);
            if (!touch)
            {
                // not found touch id for target, skip this target
                continue;
            }
        }

        // try to dispatching event
        __Array *path = __Array::createWithCapacity(10);
        node = touchTarget->getNode();
        do
        {
            path->addObject(node);
            node = node->getParent();
        } while (node != NULL && node != this);

        // phase: capturing
        // from parent to child
        for (long i = path->count() - 1; i >= 0; --i)
        {
            node = dynamic_cast<Node*>(path->getObjectAtIndex(i));
            if (touchMode == Node::modeTouchesAllAtOnce)
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
                }
            }
        }

        // phase: targeting
        node = touchTarget->getNode();
        if (touchMode == Node::modeTouchesAllAtOnce)
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
            }
        }
    }
}

NS_CC_END
