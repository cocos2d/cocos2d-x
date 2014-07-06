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

#include "2d/CCScene.h"
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

static const int _CCTouchesOneByOne = 1;
static const int _CCTouchesAllAtOnce = 0;

Scene::Scene()
: m_touchableNodes(NULL)
, m_touchingTargets(NULL)
, m_touchDispatchingEnabled(false)
, m_touchRegistered(false)
#if CC_USE_PHYSICS
, _physicsWorld(nullptr)
#endif
{
    m_touchableNodes = __Array::createWithCapacity(100);
    m_touchableNodes->retain();
    m_touchingTargets = __Array::createWithCapacity(10);
    m_touchingTargets->retain();

    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Vec2(0.5f, 0.5f));
}

Scene::~Scene()
{
    CC_SAFE_RELEASE(m_touchableNodes);
    CC_SAFE_RELEASE(m_touchingTargets);
#if CC_USE_PHYSICS
    CC_SAFE_DELETE(_physicsWorld);
#endif
}

bool Scene::init()
{
    auto size = Director::getInstance()->getWinSize();
    return initWithSize(size);
}

bool Scene::initWithSize(const Size& size)
{
    setContentSize(size);
    return true;
}

Scene* Scene::create()
{
    Scene *ret = new Scene();
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

Scene* Scene::createWithSize(const Size& size)
{
    Scene *ret = new Scene();
    if (ret && ret->initWithSize(size))
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

std::string Scene::getDescription() const
{
    return StringUtils::format("<Scene | tag = %d>", _tag);
}

Scene* Scene::getScene() const
{
    // FIX ME: should use const_case<> to fix compiling error
    return const_cast<Scene*>(this);
}

void Scene::addTouchableNode(Node *node)
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

void Scene::removeTouchableNode(Node *node)
{
    m_touchableNodes->removeObject(node);
//    CCLOG("REMOVE TOUCHABLE NODE <%p>", node);
    if (m_touchableNodes->count() == 0 && m_touchDispatchingEnabled)
    {
        disableTouchDispatching();
    }
}

void Scene::ccTouchesBegan(__Set *pTouches, Event *pEvent)
{
    if (!m_touchDispatchingEnabled) return;

    // save touches id
    for (__SetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
    {
        m_touchingIds.insert(((Touch*)*it)->getID());
    }

    // check current in touching
    if (m_touchingTargets->count())
    {
        dispatchingTouchEvent(pTouches, pEvent, CCTOUCHADDED);
        return;
    }

    // start new touching event
    // sort touchable nodes
    sortAllTouchableNodes(m_touchableNodes);

    // find touching target
    bool isTouchable = true;
    CCObject *obj = NULL;
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
        const CCRect boundingBox = node->getCascadeBoundingBox();

        // set touch target
        Touch *touch = NULL;
        for (__SetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
        {
            touch = (Touch*)*it;
            const CCPoint touchPoint = touch->getLocation();

            if (boundingBox.containsPoint(touchPoint))
            {
                if (!touchTarget)
                {
                    touchTarget = CCTouchTargetNode::create(node);
                }

                if (touchTarget->getTouchMode() == _CCTouchesOneByOne)
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
        for (int i = path->count() - 1; dispatchingContinue && i >= 0; --i)
        {
            node = dynamic_cast<Node*>(path->objectAtIndex(i));
            if (touchMode == _CCTouchesAllAtOnce)
            {
                node->ccTouchesCaptureBegan(pTouches, touchTarget->getNode());
            }
            else
            {
                dispatchingContinue = node->ccTouchCaptureBegan(touchTarget->findTouch(pTouches), touchTarget->getNode());
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
        if (touchMode == _CCTouchesAllAtOnce)
        {
            node->ccTouchesBegan(pTouches, pEvent);
        }
        else
        {
            ret = node->ccTouchBegan(touchTarget->findTouch(pTouches), pEvent);
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

void Scene::ccTouchesMoved(__Set *pTouches, Event *pEvent)
{
    dispatchingTouchEvent(pTouches, pEvent, CCTOUCHMOVED);
}

void Scene::ccTouchesEnded(__Set *pTouches, Event *pEvent)
{
    for (__SetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
    {
        m_touchingIds.erase(((Touch*)*it)->getID());
    }

    if (m_touchingIds.size())
    {
        dispatchingTouchEvent(pTouches, pEvent, CCTOUCHREMOVED);
    }
    else
    {
        dispatchingTouchEvent(pTouches, pEvent, CCTOUCHENDED);
        // remove all touching nodes
//    CCLOG("TOUCH ENDED, REMOVE ALL TOUCH TARGETS");
        m_touchingTargets->removeAllObjects();
    }
}

void Scene::ccTouchesCancelled(__Set *pTouches, Event *pEvent)
{
    dispatchingTouchEvent(pTouches, pEvent, CCTOUCHCANCELLED);
    // remove all touching nodes
//    CCLOG("TOUCH CANCELLED, REMOVE ALL TOUCH TARGETS");
    m_touchingTargets->removeAllObjects();
}

// void Scene::visit()
// {
//     g_drawOrder = 0;
//     CCLayer::visit();
// }

void Scene::cleanup(void)
{
    m_touchableNodes->removeAllObjects();
    m_touchingTargets->removeAllObjects();
    // Director::getInstance()->getTouchDispatcher()->removeDelegate(this);

    Layer::cleanup();
}

void Scene::sortAllTouchableNodes(__Array *nodes)
{
    int i, j, length = nodes->data->num;
    Node **x = (Node**)nodes->data->arr;
    Node *tempItem;

    // insertion sort
    for(i = 1; i < length; i++)
    {
        tempItem = x[i];
        j = i - 1;

        while(j >= 0 && (tempItem->getLocalZOrder() > x[j]->getLocalZOrder()))
        {
            x[j + 1] = x[j];
            j = j - 1;
        }
        x[j + 1] = tempItem;
    }

    // debug
    //    CCLOG("----------------------------------------");
    //    for(i=0; i<length; i++)
    //    {
    //        tempItem = x[i];
    //        CCLOG("[%03d] getLocalZOrder() = %u, w = %0.2f, h = %0.2f", i, tempItem->getLocalZOrder(), tempItem->getCascadeBoundingBox().size.width, tempItem->getCascadeBoundingBox().size.height);
    //    }
}

void Scene::enableTouchDispatching()
{
    if (!m_touchRegistered)
    {
        // Director::getInstance()->getTouchDispatcher()->addStandardDelegate(this, 0);
        m_touchRegistered = true;
    }
    m_touchDispatchingEnabled = true;
}

void Scene::disableTouchDispatching()
{
    m_touchDispatchingEnabled = false;
}

void Scene::dispatchingTouchEvent(__Set *pTouches, Event *pEvent, int event)
{
    Node *node = NULL;
    CCTouchTargetNode *touchTarget = NULL;
    Touch *touch = NULL;

    unsigned int count = m_touchingTargets->count();
//    CCLOG("TOUCH TARGETS COUNT [%u]", count);
    for (unsigned int i = 0; i < count; ++i)
    {
        touchTarget = dynamic_cast<CCTouchTargetNode*>(m_touchingTargets->objectAtIndex(i));

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
        if (touchMode != _CCTouchesAllAtOnce)
        {
            touch = touchTarget->findTouch(pTouches);
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
        for (int i = path->count() - 1; i >= 0; --i)
        {
            node = dynamic_cast<Node*>(path->objectAtIndex(i));
            if (touchMode == _CCTouchesAllAtOnce)
            {
                switch (event)
                {
                    case CCTOUCHMOVED:
                        node->ccTouchesCaptureMoved(pTouches, touchTarget->getNode());
                        break;

                    case CCTOUCHENDED:
                        node->ccTouchesCaptureEnded(pTouches, touchTarget->getNode());
                        break;

                    case CCTOUCHCANCELLED:
                        node->ccTouchesCaptureCancelled(pTouches, touchTarget->getNode());
                        break;

                    case CCTOUCHADDED:
                        node->ccTouchesCaptureAdded(pTouches, touchTarget->getNode());
                        break;

                    case CCTOUCHREMOVED:
                        node->ccTouchesCaptureRemoved(pTouches, touchTarget->getNode());
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
        if (touchMode == _CCTouchesAllAtOnce)
        {
            switch (event)
            {
                case CCTOUCHMOVED:
                    node->ccTouchesMoved(pTouches, pEvent);
                    break;

                case CCTOUCHENDED:
                    node->ccTouchesEnded(pTouches, pEvent);
                    break;

                case CCTOUCHCANCELLED:
                    node->ccTouchesCancelled(pTouches, pEvent);
                    break;

                case CCTOUCHADDED:
                    node->ccTouchesAdded(pTouches, pEvent);
                    break;

                case CCTOUCHREMOVED:
                    node->ccTouchesRemoved(pTouches, pEvent);
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

#if CC_USE_PHYSICS
void Scene::addChild(Node* child, int zOrder, int tag)
{
    Node::addChild(child, zOrder, tag);
    addChildToPhysicsWorld(child);
}

void Scene::addChild(Node* child, int zOrder, const std::string &name)
{
    Node::addChild(child, zOrder, name);
    addChildToPhysicsWorld(child);
}

void Scene::update(float delta)
{
    Node::update(delta);
    if (nullptr != _physicsWorld)
    {
        _physicsWorld->update(delta);
    }
}

Scene* Scene::createWithPhysics()
{
    Scene *ret = new Scene();
    if (ret && ret->initWithPhysics())
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

bool Scene::initWithPhysics()
{
    bool ret = false;
    do
    {
        Director * director;
        CC_BREAK_IF( ! (director = Director::getInstance()) );
        this->setContentSize(director->getWinSize());
        CC_BREAK_IF(! (_physicsWorld = PhysicsWorld::construct(*this)));
        
        this->scheduleUpdate();
        // success
        ret = true;
    } while (0);
    return ret;
}

void Scene::addChildToPhysicsWorld(Node* child)
{
    if (_physicsWorld)
    {
        std::function<void(Node*)> addToPhysicsWorldFunc = nullptr;
        addToPhysicsWorldFunc = [this, &addToPhysicsWorldFunc](Node* node) -> void
        {
            if (node->getPhysicsBody())
            {
                _physicsWorld->addBody(node->getPhysicsBody());
            }
            
            auto& children = node->getChildren();
            for( const auto &n : children) {
                addToPhysicsWorldFunc(n);
            }
        };
        
        addToPhysicsWorldFunc(child);
    }
}
#endif

NS_CC_END
