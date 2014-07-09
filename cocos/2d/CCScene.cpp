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
, _touchListener(NULL)
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

void Scene::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
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
        if (touchMode == _CCTouchesAllAtOnce)
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

void Scene::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
    dispatchingTouchEvent(touches, event, CCTOUCHMOVED);
}

void Scene::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
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

void Scene::onTouchesCancelled(const std::vector<Touch*>& touches, Event *event)
{
    dispatchingTouchEvent(touches, event, CCTOUCHCANCELLED);
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
    if (_touchListener) {
        _eventDispatcher->removeEventListener(_touchListener);
        _touchListener = NULL;
    }

//    Layer::cleanup();
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
    if (!_touchListener)
    {
        // Director::getInstance()->getTouchDispatcher()->addStandardDelegate(this, 0);
        _touchListener = EventListenerTouchAllAtOnce::create();
        if (!_touchListener) {
            return;
        }
        _touchListener->onTouchesBegan = CC_CALLBACK_2(Scene::onTouchesBegan, this);
        _touchListener->onTouchesMoved = CC_CALLBACK_2(Scene::onTouchesMoved, this);
        _touchListener->onTouchesEnded = CC_CALLBACK_2(Scene::onTouchesEnded, this);
        _touchListener->onTouchesCancelled = CC_CALLBACK_2(Scene::onTouchesCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    }
    m_touchDispatchingEnabled = true;
}

void Scene::disableTouchDispatching()
{
    m_touchDispatchingEnabled = false;
}

void Scene::dispatchingTouchEvent(const std::vector<Touch*>& touches, Event *pEvent, int event)
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
        for (int i = path->count() - 1; i >= 0; --i)
        {
            node = dynamic_cast<Node*>(path->objectAtIndex(i));
            if (touchMode == _CCTouchesAllAtOnce)
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
        if (touchMode == _CCTouchesAllAtOnce)
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
