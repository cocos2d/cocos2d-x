/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2017 Chukong Technologies Inc.

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
#include "base/CCScheduler.h"
#include "2d/CCCamera.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerCustom.h"
#include "base/ccUTF8.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCFrameBuffer.h"

#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramStateCache.h"
#include "renderer/CCTextureCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "renderer/CCFrameBuffer.h"

#include "3d/CCSprite3D.h"
#include "3d/CCSprite3DMaterial.h"

#include "Entity.h"

#if CC_USE_PHYSICS
#include "physics/CCPhysicsWorld.h"
#endif

#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "physics3d/CCPhysics3DWorld.h"
#include "physics3d/CCPhysics3DComponent.h"
#endif

#if CC_USE_NAVMESH
#include "navmesh/CCNavMesh.h"
#endif

#import "CCApplication.h"

using namespace cocos2d;
using namespace experimental;

NS_CC_BEGIN

Scene::Scene()
{
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
    _physics3DWorld = nullptr;
    _physics3dDebugCamera = nullptr;
#endif
#if CC_USE_NAVMESH
    _navMesh = nullptr;
    _navMeshDebugCamera = nullptr;
#endif
#if CC_USE_PHYSICS
    _physicsWorld = nullptr;
#endif
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Vec2(0.5f, 0.5f));
    
    _cameraOrderDirty = true;

    _event = Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_PROJECTION_CHANGED, std::bind(&Scene::onProjectionChanged, this, std::placeholders::_1));
    _event->retain();

    /**
     *
     * @Scene
     *  @Ambient;
     *
     */
    this->ambient.source1 = DirectionLight::create(Vec3(0, 0, 0), Color3B(0, 0, 0));
    this->ambient.source2 = AmbientLight::create(Color3B(0, 0, 0));

    this->ambient.source1->retain();
    this->ambient.source2->retain();
    
    this->camera = nullptr;
}

Scene::~Scene()
{
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
    CC_SAFE_RELEASE(_physics3DWorld);
    CC_SAFE_RELEASE(_physics3dDebugCamera);
#endif
#if CC_USE_NAVMESH
    CC_SAFE_RELEASE(_navMesh);
#endif
    Director::getInstance()->getEventDispatcher()->removeEventListener(_event);
    CC_SAFE_RELEASE(_event);
    
#if CC_USE_PHYSICS
    delete _physicsWorld;
#endif
    
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine)
    {
        sEngine->releaseAllChildrenRecursive(this);
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
}

#if CC_USE_NAVMESH
void Scene::setNavMesh(NavMesh* navMesh)
{
    if (_navMesh != navMesh)
    {
        CC_SAFE_RETAIN(navMesh);
        CC_SAFE_RELEASE(_navMesh);
        _navMesh = navMesh;
    }
}
#endif

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

void Scene::onProjectionChanged(EventCustom* /*event*/)
{
}

static bool camera_cmp(const Camera* a, const Camera* b)
{
    return a->getRenderOrder() < b->getRenderOrder();
}

const std::vector<Camera*>& Scene::getCameras()
{
    if (_cameraOrderDirty)
    {
        stable_sort(_cameras.begin(), _cameras.end(), camera_cmp);
        _cameraOrderDirty = false;
    }
    return _cameras;
}

void Scene::render(Renderer* renderer, const Mat4& eyeTransform, const Mat4* eyeProjection)
{
    render(renderer, &eyeTransform, eyeProjection, 1);
}

void Scene::render(Renderer* renderer, const Mat4* eyeTransforms, const Mat4* eyeProjections, unsigned int multiViewCount)
{
    auto director = Director::getInstance();
    const auto& transform = getNodeToParentTransform();

    director->onRenderStart();

    for (int i = 0; i < getCameras().size(); i++)
    {
        auto camera = getCameras().at(i);

        if (!camera->isVisible())
            continue;

        director->onRenderStart(camera->getIndex());

        this->camera = camera;

        // There are two ways to modify the "default camera" with the eye Transform:
        // a) modify the "nodeToParentTransform" matrix
        // b) modify the "additional transform" matrix
        // both alternatives are correct, if the user manually modifies the camera with a camera->setPosition()
        // then the "nodeToParent transform" will be lost.
        // And it is important that the change is "permanent", because the matrix might be used for calculate
        // culling and other stuff.
        for (unsigned int i = 0; i < multiViewCount; ++i) {
            if (eyeProjections)
                camera->setAdditionalProjection(eyeProjections[i] * camera->getProjectionMatrix().getInversed());
            if (eyeTransforms)
                camera->setAdditionalTransform(eyeTransforms[i].getInversed());
            director->pushProjectionMatrix(i);
            director->loadProjectionMatrix(this->camera->getViewProjectionMatrix(), i);
        }

        camera->apply();
        camera->clearBackground();

        visit(renderer, transform, 0);

#if CC_USE_NAVMESH
        if (_navMesh && _navMeshDebugCamera == camera)
        {
            _navMesh->debugDraw(renderer);
        }
#endif

        renderer->render();
        camera->restore();

        director->onRenderFinish(camera->getIndex());

        for (unsigned int i = 0; i < multiViewCount; ++i)
            director->popProjectionMatrix(i);

        // we shouldn't restore the transform matrix since it could be used
        // from "update" or other parts of the game to calculate culling or something else.
//        camera->setNodeToParentTransform(eyeCopy);
    }

#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
    if (_physics3DWorld && _physics3DWorld->isDebugDrawEnabled())
    {
        Camera *physics3dDebugCamera = _physics3dDebugCamera != nullptr ? _physics3dDebugCamera: defaultCamera;
        
        for (unsigned int i = 0; i < multiViewCount; ++i) {
            if (eyeProjections)
                physics3dDebugCamera->setAdditionalProjection(eyeProjections[i] * physics3dDebugCamera->getProjectionMatrix().getInversed());
            if (eyeTransforms)
                physics3dDebugCamera->setAdditionalTransform(eyeTransforms[i].getInversed());
            director->pushProjectionMatrix(i);
            director->loadProjectionMatrix(physics3dDebugCamera->getViewProjectionMatrix(), i);
        }
        
        physics3dDebugCamera->apply();
        physics3dDebugCamera->clearBackground();

        _physics3DWorld->debugDraw(renderer);
        renderer->render();
        
        physics3dDebugCamera->restore();

        for (unsigned int i = 0; i < multiViewCount; ++i)
            director->popProjectionMatrix(i);
    }
#endif

    this->camera = nullptr;
//    experimental::FrameBuffer::applyDefaultFBO();

director->onRenderFinish();
}

void Scene::removeAllChildren()
{
    Node::removeAllChildren();
}

#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
void Scene::setPhysics3DDebugCamera(Camera* camera)
{
    CC_SAFE_RETAIN(camera);
    CC_SAFE_RELEASE(_physics3dDebugCamera);
    _physics3dDebugCamera = camera;
}
#endif

#if CC_USE_NAVMESH
void Scene::setNavMeshDebugCamera(Camera *camera)
{
    CC_SAFE_RETAIN(camera);
    CC_SAFE_RELEASE(_navMeshDebugCamera);
    _navMeshDebugCamera = camera;
}

#endif

#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))

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
#if CC_USE_PHYSICS
    _physicsWorld = PhysicsWorld::construct(this);
#endif

    bool ret = false;
    do
    {
        Director * director;
        CC_BREAK_IF( ! (director = Director::getInstance()) );

        this->setContentSize(director->getWinSize());

#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
        Physics3DWorldDes info;
        CC_BREAK_IF(! (_physics3DWorld = Physics3DWorld::create(&info)));
        _physics3DWorld->retain();
#endif

        // success
        ret = true;
    } while (0);
    return ret;
}

#endif

#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH)
void Scene::stepPhysicsAndNavigation(float deltaTime)
{
#if CC_USE_PHYSICS
    if (_physicsWorld && _physicsWorld->isAutoStep())
        _physicsWorld->update(deltaTime);
#endif

#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
    if (_physics3DWorld)
    {
        _physics3DWorld->stepSimulate(1.0 / 60.0 * Director::getInstance()->getScheduler()->getTimeScale());
    }
#endif
#if CC_USE_NAVMESH
    if (_navMesh)
    {
        _navMesh->update(deltaTime);
    }
#endif
}
#endif

/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) by Igor Mats
 * http://www.tooflya.com/development/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

/**
 *
 * @Scene
 * | @Ambient;
 *
 */
void Scene::setAmbientColor1(float r, float g, float b)
{
  this->ambient.source1->setColor(Color3B(r, g, b));
}

void Scene::setAmbientColor2(float r, float g, float b)
{
  this->ambient.source2->setColor(Color3B(r, g, b));
}

void Scene::setAmbientDirection(float x, float y, float z)
{
  this->ambient.source1->setDirection(Vec3(x, y, z));
}

void Scene::setAmbient(bool state)
{
  if(state)
  {
    if(!this->ambient.state)
    {
      this->addChild(this->ambient.source1);
      this->addChild(this->ambient.source2);
    }
  }
  else
  {
    if(this->ambient.state)
    {
    }
  }

  this->ambient.state = state;
}

Vec3 Scene::getAmbientDirection()
{
  if(this->ambient.state)
  {
    return this->ambient.source1->getDirection();
  }

  return Vec3(0, 0, 0);
}

/**
 *
 * @Scene
 * | @Shadows;
 *
 */
void Scene::setShadowCamera(Camera* camera)
{
  this->shadows.camera = camera;
}

void Scene::setShadowElement(Node* element)
{
  this->shadows.element = element;
}

void Scene::setShadowFactor(float factor)
{
  this->shadows.factor = factor;
}

void Scene::setShadowValue(float value)
{
  this->shadows.value = value;
}

void Scene::setShadow(bool state)
{
  if(!Support::shadows()) return;

  if(state)
  {
    if(!this->shadows.state)
    {
      auto width = Director::getInstance()->getWinSizeInPixels().width / this->shadows.factor;
      auto height = Director::getInstance()->getWinSizeInPixels().height / this->shadows.factor;

      /**
       *
       * @Scene
       * | @Shadows;
       * | @Generate frame buffer object;
       *
       */
      /*if(false)//Support::multiSampling())
      {
        this->shadows.resolve_frame = FrameBuffer::create(1, width, height);
        this->shadows.resolve_frame->retain();
        this->shadows.resolve_frame->attachRenderTarget(RenderTarget::create(width, height));
        this->shadows.resolve_frame->attachDepthStencilTarget(RenderTargetDepthStencil::create(width, height));
        this->shadows.resolve_frame->applyFBO();

        this->shadows.frame = FrameBuffer::create(1, width, height);
        this->shadows.frame->retain();
        this->shadows.frame->attachRenderTarget(RenderTargetRenderBuffer::create(width, height, 2));
        this->shadows.frame->attachDepthStencilTarget(RenderTargetDepthStencil::create(width, height, 2));
        this->shadows.frame->applyFBO();

        this->shadows.camera->setFrameBufferObject(this->shadows.frame);
      }
      else*/
      {
        this->shadows.frame = FrameBuffer::create(1, width, height);
        this->shadows.frame->retain();
        this->shadows.frame->attachRenderTarget(RenderTarget::create(width, height));
        this->shadows.frame->attachDepthStencilTarget(RenderTargetDepthStencil::create(width, height));
        this->shadows.frame->applyFBO();

        this->shadows.camera->setFrameBufferObject(this->shadows.frame);
      }

      /**
       *
       * @Scene
       * | @Shadows;
       * | @Generate shader programs for shadows and add them to the cache;
       *
       */
      GLProgramCache::getInstance()->addGLProgram(
        GLProgram::createWithFilenames("@shadows.vert", "@shadows.frag"),
        "@shadows"
      );

      /**
       *
       *
       *
       */
      this->enableShadow(true);

      /**
       *
       * @Scene
       * | @Shadows;
       * | @Should add shadows frame buffer texture to the default 2D camera;
       *
       */
      if(true)
      {
        if(this->shadows.resolve_frame)
        {
          this->shadows.texture = new Entity(this->shadows.resolve_frame->getRenderTarget()->getTexture(), this, true);
        }
        else
        {
          this->shadows.texture = new Entity(this->shadows.frame->getRenderTarget()->getTexture(), this);
        }

        this->shadows.texture->setScaleX(1 * this->shadows.factor);
        this->shadows.texture->setScaleY(-1 * this->shadows.factor);
        this->shadows.texture->setPosition(width / 2, height / 2);
        this->shadows.texture->setGlobalZOrder(100);
      }
    }
  }
  else
  {
    if(this->shadows.state)
    {
    }
  }

  this->shadows.state = state;
}

bool Scene::getShadowState()
{
  return this->shadows.state;
}

Node* Scene::getShadowTexture()
{
  return this->shadows.texture;
}

Node* Scene::getShadowElement()
{
  return this->shadows.element;
}

Camera* Scene::getShadowCamera()
{
  return this->shadows.camera;
}

experimental::FrameBuffer* Scene::getShadowFrameBuffer()
{
  return this->shadows.frame;
}

experimental::FrameBuffer* Scene::getShadowResolveFrameBuffer()
{
  return this->shadows.resolve_frame;
}

void Scene::updateShadowElementState1(Node *element)
{
  if(element->enableShadow())
  {
    element->getGLProgramState()->setUniformFloat("value1", 0.0f);
    element->getGLProgramState()->setUniformFloat("value2", 0.0f);
  }

  /**
   *
   *
   *
   */
  for(auto el : element->getChildren())
  {
    //if(Camera::getVisitingCamera()->isVisibleInFrustum(&static_cast<Sprite3D*>(el)->getAABB()))
    {
      this->updateShadowElementState1(el);
    }
  }
}

static float matrix[16] = {
  0.5f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.5f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.5f, 0.0f,
  0.5f, 0.5f, 0.5f, 1.0f
};

Mat4 cameraViewportMatrix(matrix);
Mat4 cameraViewMatrix;
Mat4 cameraProjectionMatrix;
Mat4 cameraTransformMatrix;

void Scene::updateShadowElementState2(Node *element, bool recursive)
{
  if(!recursive)
  {
    cameraViewMatrix = this->shadows.camera->getViewMatrix();
    cameraProjectionMatrix = this->shadows.camera->getProjectionMatrix();
    cameraTransformMatrix = cameraViewportMatrix * cameraProjectionMatrix * cameraViewMatrix;
  }

  /**
   *
   *
   *
   */
  if(element->enableShadow())
  {
    if(element->enableLight())
    {
      element->getGLProgramState()->setUniformFloat("use", 1.0);
    }

    element->getGLProgramState()->setUniformFloat("value1", this->shadows.value);
    element->getGLProgramState()->setUniformFloat("value2", this->shadows.value);
    element->getGLProgramState()->setUniformFloat("sindex", static_cast<Sprite3D*>(element)->shadowIndex);
    element->getGLProgramState()->setUniformMat4("modelTransformMatrix", element->getModelViewMatrix());
    element->getGLProgramState()->setUniformMat4("cameraTransformMatrix", cameraTransformMatrix);

    /*if(this->shadows.resolve_frame)
    {
      element->getGLProgramState()->setUniformTexture("transformTexture", this->shadows.resolve_frame->getRenderTarget()->getTexture());
    }
    else*/
    {
      element->getGLProgramState()->setUniformTexture("transformTexture", this->shadows.frame->getRenderTarget()->getTexture());
    }
  }

  /**
   *
   *
   *
   */
  for(auto el : element->getChildren())
  {
    //if(Camera::getVisitingCamera()->isVisibleInFrustum(&static_cast<Sprite3D*>(el)->getAABB()))
    {
      this->updateShadowElementState2(el, true);
    }
  }
}

/**
 *
 * @Director
 * | @Capture;
 *
 */
void Scene::setCaptureCamera(Camera* camera)
{
  this->capture.camera = camera;
}

void Scene::setCaptureElement(Sprite* element)
{
  this->capture.element = element;
}

void Scene::setCaptureCount(int count)
{
  this->capture.count = count;
}

void Scene::setCaptureTime(int time)
{
  this->capture.time = time;
}

void Scene::setCaptureFactor(float factor)
{
  this->capture.factor = factor;
}

void Scene::setCaptureScale(float scale)
{
  this->capture.scale = scale;
}

void Scene::setCapturePosition(float x, float y)
{
  this->capture.x = x;
  this->capture.y = y;

  this->capture.element->setPosition(this->capture.x + this->capture.width / 2, this->capture.y + this->capture.height / 2);
}

void Scene::setCaptureSize(float width, float height)
{
  this->capture.width = width;
  this->capture.height = height;
}

void Scene::setCaptureBind(bool state)
{
  this->capture.bind = state;

  if(state)
  {
    this->capture.frames = 0;

    /**
     *
     *
     *
     */
    Ad::pauseExpensiveWork();
  }
  else
  {
    Ad::resumeExpensiveWork();
  }
}

void Scene::setCapture(bool state)
{
  if(!Support::capture()) return;

  if(state)
  {
    if(!this->capture.state)
    {
      auto size = Director::getInstance()->getWinSize();

      auto width = size.width * this->capture.factor;
      auto height = size.height * this->capture.factor;

      /**
       *
       * @Director
       * | @Capture;
       * | @Generate frame buffer object;
       *
       * @TODO: Add setting for the multisamples count;
       *
       */
      if(Support::multiSampling())
      {
        this->capture.resolve_frame = FrameBuffer::create(1, width, height);
        this->capture.resolve_frame->retain();
        this->capture.resolve_frame->attachRenderTarget(RenderTarget::create(width, height));
        this->capture.resolve_frame->applyFBO();

        this->capture.frame = FrameBuffer::create(1, width, height);
        this->capture.frame->retain();
        this->capture.frame->attachRenderTarget(RenderTargetRenderBuffer::create(width, height, 2));
        this->capture.frame->attachDepthStencilTarget(RenderTargetDepthStencil::create(width, height, 2));
        this->capture.frame->applyFBO();

        this->capture.camera->setFrameBufferObject(this->capture.frame);
      }
      else
      {
        this->capture.frame = FrameBuffer::create(1, width, height);
        this->capture.frame->retain();
        this->capture.frame->attachRenderTarget(RenderTarget::create(width, height));
        this->capture.frame->attachDepthStencilTarget(RenderTargetDepthStencil::create(width, height));
        this->capture.frame->applyFBO();

        this->capture.camera->setFrameBufferObject(this->capture.frame);
      }

      /**
       *
       * @Director
       * | @Capture;
       * | @Should create render textures based on user's configurations;
       *
       */
      auto count = this->capture.count;
      auto time = this->capture.time;

      for(int i = 0; i < count * time; i++)
      {
        auto render = RenderTexture::create(this->capture.width, this->capture.height, Texture2D::PixelFormat::RGBA8888);
        render->retain();

        this->capture.textures.push_back(render);
      }

      /**
       *
       * @Director
       * | @Capture;
       * | @Should add shadow frame buffer texture to the default 2D camera;
       *
       */
      if(Support::multiSampling())
      {
        this->capture.texture = new Entity(this->capture.resolve_frame->getRenderTarget()->getTexture(), this, true);
      }
      else
      {
        this->capture.texture = new Entity(this->capture.frame->getRenderTarget()->getTexture(), this, true);
      }

      this->capture.texture->setScaleX(1 / this->capture.factor);
      this->capture.texture->setScaleY(-1 / this->capture.factor);
      this->capture.texture->setPosition(size.width / 2, size.height / 2);
      this->capture.texture->setGlobalZOrder(-1);

      /**
       *
       * @Director
       * | @Capture;
       *
       */
      this->capture.element->initWithTexture(this->capture.texture->getTexture());
      this->capture.element->retain();

      /**
       *
       *
       *
       */
      this->capture.frames = 0;
    }
  }
  else
  {
    if(this->capture.state)
    {
    }
  }

  this->capture.state = state;
}

bool Scene::getCaptureState()
{
  return this->capture.state;
}

bool Scene::getCaptureBind()
{
  return this->capture.bind;
}

int Scene::getCaptureTexturesCount()
{
  return this->capture.textures.size();
}

int Scene::getCaptureFrames()
{
  return min(this->capture.frames, (int) this->capture.textures.size() - 1);
}

int Scene::getCaptureTime()
{
  return this->capture.time;
}

float Scene::getCaptureWidth()
{
  return this->capture.width;
}

float Scene::getCaptureHeight()
{
  return this->capture.height;
}

float Scene::getCaptureScale()
{
  return this->capture.scale;
}

RenderTexture* Scene::getCaptureRenderTextures(int index)
{
  return this->capture.textures.at(index);
}

Texture2D* Scene::getCaptureTextures(int index)
{
  return this->capture.textures.at(index)->getSprite()->getTexture();
}

Node* Scene::getCaptureTexture()
{
  return this->capture.texture;
}

Node* Scene::getCaptureElement()
{
  return this->capture.element;
}

Camera* Scene::getCaptureCamera()
{
  return this->capture.camera;
}

experimental::FrameBuffer* Scene::getCaptureFrameBuffer()
{
  return this->capture.frame;
}

experimental::FrameBuffer* Scene::getCaptureResolveFrameBuffer()
{
  return this->capture.resolve_frame;
}

void Scene::updateCapture()
{
  if(this->capture.state)
  {
    if(this->capture.bind)
    {
      this->capture.frames++;

      auto render = this->capture.textures.at(this->capture.textures.size() - 1);
      this->capture.textures.erase(this->capture.textures.begin() + this->capture.textures.size() - 1);
      this->capture.textures.insert(this->capture.textures.begin(), render);

      render = this->capture.textures.at(0);

      render->beginWithClear(1, 1, 1, 1);
      this->capture.element->setScaleX(1 * 1.0 / this->capture.scale);
      this->capture.element->setScaleY(-1 * 1.0 / this->capture.scale);
      this->capture.element->setPosition(this->capture.x + this->capture.width / 2, this->capture.y + this->capture.height / 2);
      this->capture.element->setTexture(this->capture.texture->getTexture());
      this->capture.element->Sprite::visit();
      render->end();

      this->capture.count = min<int>(this->capture.textures.size(), this->capture.count + 1);
    }
  }
}

/**
 *
 * @Scene
 * | @Render;
 *
 */
void Scene::onRenderStart()
{
}

void Scene::onRenderFinish()
{
}

void Scene::onRenderStart(int index, int step)
{
}

void Scene::onRenderFinish(int index)
{
}

NS_CC_END
