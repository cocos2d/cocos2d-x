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
#include "2d/CCCamera.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerCustom.h"
#include "renderer/CCRenderer.h"
#include "deprecated/CCString.h"

#if CC_USE_PHYSICS
#include "physics/CCPhysicsWorld.h"
#endif

#if CC_USE_3D_PHYSICS
#include "physics3d/CCPhysics3DWorld.h"
#include "physics3d/CCPhysics3DComponent.h"
#endif

NS_CC_BEGIN

Scene::Scene()
#if CC_USE_PHYSICS
: _physicsWorld(nullptr)
#endif
{
#if CC_USE_3D_PHYSICS
    _physics3DWorld = nullptr;
    _physics3dDebugCamera = nullptr;
#endif
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Vec2(0.5f, 0.5f));
    
    _cameraOrderDirty = true;
    
    //create default camera
    _defaultCamera = Camera::create();
    addChild(_defaultCamera);
    
    _event = Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_PROJECTION_CHANGED, std::bind(&Scene::onProjectionChanged, this, std::placeholders::_1));
    _event->retain();
}

Scene::~Scene()
{
#if CC_USE_PHYSICS
    CC_SAFE_DELETE(_physicsWorld);
#endif
#if CC_USE_3D_PHYSICS
    CC_SAFE_RELEASE(_physics3DWorld);
    CC_SAFE_RELEASE(_physics3dDebugCamera);
#endif
    Director::getInstance()->getEventDispatcher()->removeEventListener(_event);
    CC_SAFE_RELEASE(_event);
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
    Scene *ret = new (std::nothrow) Scene();
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
    Scene *ret = new (std::nothrow) Scene();
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

void Scene::onProjectionChanged(EventCustom* event)
{
    if (_defaultCamera)
    {
        _defaultCamera->initDefault();
    }
}

static bool camera_cmp(const Camera* a, const Camera* b)
{
    return a->getDepth() < b->getDepth();
}

void Scene::render(Renderer* renderer)
{
    auto director = Director::getInstance();
    Camera* defaultCamera = nullptr;
    const auto& transform = getNodeToParentTransform();
    if (_cameraOrderDirty)
    {
        stable_sort(_cameras.begin(), _cameras.end(), camera_cmp);
        _cameraOrderDirty = false;
    }
    
    for (const auto& camera : _cameras)
    {
        if (!camera->isVisible())
            continue;
        
        Camera::_visitingCamera = camera;
        if (Camera::_visitingCamera->getCameraFlag() == CameraFlag::DEFAULT)
        {
            defaultCamera = Camera::_visitingCamera;
        }
        
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
        director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, Camera::_visitingCamera->getViewProjectionMatrix());
        
        //visit the scene
        visit(renderer, transform, 0);
        
        renderer->render();
        
        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    }
    
#if CC_USE_3D_PHYSICS
    if (_physics3DWorld && _physics3DWorld->isDebugDrawEnabled())
    {
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
        director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, _physics3dDebugCamera != nullptr ? _physics3dDebugCamera->getViewProjectionMatrix() : defaultCamera->getViewProjectionMatrix());
        _physics3DWorld->debugDraw(renderer);
        renderer->render();
        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    }
#endif

    Camera::_visitingCamera = nullptr;
}

void Scene::removeAllChildren()
{
    if (_defaultCamera)
        _defaultCamera->retain();
    
    Node::removeAllChildren();
    
    if (_defaultCamera)
    {
        addChild(_defaultCamera);
        _defaultCamera->release();
    }
}

#if CC_USE_3D_PHYSICS
void Scene::setPhysics3DDebugCamera(Camera* camera)
{
    CC_SAFE_RETAIN(camera);
    CC_SAFE_RELEASE(_physics3dDebugCamera);
    _physics3dDebugCamera = camera;
}
#endif

#if (CC_USE_PHYSICS || CC_USE_3D_PHYSICS)
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

Scene* Scene::createWithPhysics()
{
    Scene *ret = new (std::nothrow) Scene();
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
#if CC_USE_PHYSICS
        CC_BREAK_IF(! (_physicsWorld = PhysicsWorld::construct(*this)));
#endif
        
#if CC_USE_3D_PHYSICS
        Physics3DWorldDes info;
        //TODO: FIX ME
        //info.isDebugDrawEnabled = true;
        CC_BREAK_IF(! (_physics3DWorld = Physics3DWorld::create(&info)));
        _physics3DWorld->retain();
#endif
        
        // success
        ret = true;
    } while (0);
    return ret;
}

void Scene::addChildToPhysicsWorld(Node* child)
{
#if CC_USE_PHYSICS
    if (_physicsWorld)
    {
        std::function<void(Node*)> addToPhysicsWorldFunc = nullptr;
        addToPhysicsWorldFunc = [this, &addToPhysicsWorldFunc](Node* node) -> void
        {
            node->_physicsWorld = _physicsWorld;

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
#endif
    
#if CC_USE_3D_PHYSICS
    if (_physics3DWorld)
    {
        std::function<void(Node*)> addToPhysicsWorldFunc = nullptr;
        addToPhysicsWorldFunc = [this, &addToPhysicsWorldFunc](Node* node) -> void
        {
            static std::string comName = Physics3DComponent::getPhysics3DComponentName();
            auto com = static_cast<Physics3DComponent*>(node->getComponent(comName));
            if (com)
            {
                com->addToPhysicsWorld(_physics3DWorld);
            }
            
            auto& children = node->getChildren();
            for( const auto &n : children) {
                addToPhysicsWorldFunc(n);
            }
        };
        
        addToPhysicsWorldFunc(child);
    }
#endif
}

#endif

NS_CC_END
