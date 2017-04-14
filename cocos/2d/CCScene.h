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

#ifndef __CCSCENE_H__
#define __CCSCENE_H__

#include <string>
#include "2d/CCNode.h"
#include "2d/CCLight.h"
#include "2d/CCSprite.h"

NS_CC_BEGIN

class Camera;
class BaseLight;
class Renderer;
class EventListenerCustom;
class EventCustom;
#if CC_USE_PHYSICS
class PhysicsWorld;
#endif
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
class Physics3DWorld;
#endif
#if CC_USE_NAVMESH
class NavMesh;
#endif

class RenderTexture;

namespace experimental
{
  class FrameBuffer;
}

/**
 * @addtogroup _2d
 * @{
 */

/** @class Scene
* @brief Scene is a subclass of Node that is used only as an abstract concept.

Scene and Node are almost identical with the difference that Scene has its
anchor point (by default) at the center of the screen.

For the moment Scene has no other logic than that, but in future releases it might have
additional logic.

It is a good practice to use a Scene as the parent of all your nodes.
 
Scene will create a default camera for you.
*/
class CC_DLL Scene : public Node
{
public:
    /** Creates a new Scene object. 
     *
     * @return An autoreleased Scene object.
     */
    static Scene *create();

    /** Creates a new Scene object with a predefined Size. 
     *
     * @param size The predefined size of scene.
     * @return An autoreleased Scene object.
     * @js NA
     */
    static Scene *createWithSize(const Size& size);

    using Node::addChild;
    virtual std::string getDescription() const override;
    
    /** Get all cameras.
     * 
     * @return The vector of all cameras, ordered by camera depth.
     * @js NA
     */
    const std::vector<Camera*>& getCameras();

    /** Get lights.
     * @return The vector of lights.
     * @js NA
     */
    const std::vector<BaseLight*>& getLights() const { return _lights; }

    /** Render the scene.
     * @param renderer The renderer use to render the scene.
     * @param eyeTransform The AdditionalTransform of camera.
     * @param eyeProjection The projection matrix of camera.
     * @js NA
     */
    virtual void render(Renderer* renderer, const Mat4& eyeTransform, const Mat4* eyeProjection = nullptr);

    /** Render the scene.
     * @param renderer The renderer use to render the scene.
     * @param eyeTransforms The AdditionalTransform List of camera of multiView.
     * @param eyeProjections The projection matrix List of camera of multiView.
     * @param multiViewCount The number of multiView.
     * @js NA
     */
    virtual void render(Renderer* renderer, const Mat4* eyeTransforms, const Mat4* eyeProjections, unsigned int multiViewCount);

    /** override function */
    virtual void removeAllChildren() override;
    
CC_CONSTRUCTOR_ACCESS:
    Scene();
    virtual ~Scene();
    
    bool init() override;
    bool initWithSize(const Size& size);
    
    void setCameraOrderDirty() { _cameraOrderDirty = true; }
    
    void onProjectionChanged(EventCustom* event);

protected:
    friend class Node;
    friend class ProtectedNode;
    friend class SpriteBatchNode;
    friend class Camera;
    friend class BaseLight;
    friend class Renderer;
    
    std::vector<Camera*> _cameras; //weak ref to Camera
    bool                 _cameraOrderDirty; // order is dirty, need sort
    EventListenerCustom*       _event;

    std::vector<BaseLight *> _lights;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Scene);
    
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
public:
    
#if CC_USE_PHYSICS
    /** Get the physics world of the scene.
     * @return The physics world of the scene.
     * @js NA
     */
    PhysicsWorld* getPhysicsWorld() const { return _physicsWorld; }
#endif
    
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
    /** Get the 3d physics world of the scene.
     * @return The 3d physics world of the scene.
     * @js NA
     */
    Physics3DWorld* getPhysics3DWorld() { return _physics3DWorld; }
    
    /** 
     * Set Physics3D debug draw camera.
     */
    void setPhysics3DDebugCamera(Camera* camera);
#endif
    
    /** Create a scene with physics.
     * @return An autoreleased Scene object with physics.
     * @js NA
     */
    static Scene *createWithPhysics();
    
CC_CONSTRUCTOR_ACCESS:
    bool initWithPhysics();
    
protected:
    void addChildToPhysicsWorld(Node* child);

#if CC_USE_PHYSICS
    PhysicsWorld* _physicsWorld;
#endif
    
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
    Physics3DWorld*            _physics3DWorld;
    Camera*                    _physics3dDebugCamera; //
#endif
#endif // (CC_USE_PHYSICS || CC_USE_3D_PHYSICS)
    
#if CC_USE_NAVMESH
public:
    /** set navigation mesh */
    void setNavMesh(NavMesh* navMesh);
    /** get navigation mesh */
    NavMesh* getNavMesh() const { return _navMesh; }
    /**
    * Set NavMesh debug draw camera.
    */
    void setNavMeshDebugCamera(Camera *camera);

protected:
    NavMesh*        _navMesh;
    Camera *        _navMeshDebugCamera;
#endif
    
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH)
public:
    void stepPhysicsAndNavigation(float deltaTime);
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
  protected:
    Camera* camera;

    /**
     *
     * @Scene
     * | @Ambient;
     *
     */
    struct Ambient {
      bool state = false;

      DirectionLight* source1;
      AmbientLight* source2;
    };

    Ambient ambient;

    /**
     *
     * @Scene
     * | @Shadows;
     *
     */
    struct Shadows {
      bool state = false;

      float factor;
      float value;

      experimental::FrameBuffer* frame = nullptr;
      experimental::FrameBuffer* resolve_frame = nullptr;
      Camera* camera;
      Node* element;
      Node* texture;
    };

    Shadows shadows;

    /**
     *
     * @Scene
     * | @Capture;
     *
     */
    struct Capture {
      bool state = false;
      bool bind = false;

      int count;
      int time;
      int frames;
      float scale;
      float factor;
      float x;
      float y;
      float width;
      float height;

      experimental::FrameBuffer* frame = nullptr;
      experimental::FrameBuffer* resolve_frame = nullptr;
      Camera* camera;
      Sprite* texture;
      Sprite* element;

      std::vector<RenderTexture*> textures;
    };

    Capture capture;

    /**
     *
     *
     *
     */
  public:
    virtual Camera* setCamera(Camera* _camera) { this->camera = _camera; return this->camera; };
    virtual Camera* getCamera() { return this->camera; };

    /**
     *
     * @Scene
     * | @Ambient;
     *
     */
    virtual void setAmbientColor1(float r, float g, float b);
    virtual void setAmbientColor2(float r, float g, float b);
    virtual void setAmbientDirection(float x, float y, float z);
    virtual void setAmbient(bool state);

    virtual Vec3 getAmbientDirection();

    /**
     *
     * @Scene
     * | @Shadows;
     *
     */
    virtual void setShadowCamera(Camera* camera);
    virtual void setShadowElement(Node* element);
    virtual void setShadowFactor(float factor);
    virtual void setShadowValue(float value);
    virtual void setShadow(bool state);

    virtual void updateShadowElementState1(Node* element);
    virtual void updateShadowElementState2(Node* element, bool recursive = false);

    virtual bool getShadowState();
    virtual Node* getShadowTexture();
    virtual Node* getShadowElement();

    virtual Camera* getShadowCamera();

    virtual experimental::FrameBuffer* getShadowFrameBuffer();
    virtual experimental::FrameBuffer* getShadowResolveFrameBuffer();

    /**
     *
     * @Scene
     * | @Capture;
     *
     */
    virtual void setCaptureCamera(Camera* camera);
    virtual void setCaptureElement(Sprite* element);
    virtual void setCaptureCount(int count);
    virtual void setCaptureTime(int time);
    virtual void setCaptureFactor(float factor);
    virtual void setCaptureScale(float scale);
    virtual void setCapturePosition(float x, float y);
    virtual void setCaptureSize(float width, float height);
    virtual void setCaptureBind(bool state);
    virtual void setCapture(bool state);

    virtual void updateCapture();

    virtual bool getCaptureState();
    virtual bool getCaptureBind();

    virtual int getCaptureTexturesCount();
    virtual int getCaptureFrames();
    virtual int getCaptureTime();

    virtual float getCaptureWidth();
    virtual float getCaptureHeight();

    virtual float getCaptureScale();

    virtual RenderTexture* getCaptureRenderTextures(int index);
    virtual Texture2D* getCaptureTextures(int index);

    virtual Node* getCaptureTexture();
    virtual Node* getCaptureElement();

    virtual Camera* getCaptureCamera();

    virtual experimental::FrameBuffer* getCaptureFrameBuffer();
    virtual experimental::FrameBuffer* getCaptureResolveFrameBuffer();

    /**
     *
     * @Scene
     * | @Render;
     *
     */
    virtual void onRenderStart();
    virtual void onRenderFinish();
    virtual void onRenderStart(int index, int step);
    virtual void onRenderFinish(int index);
};

// end of _2d group
/// @}

NS_CC_END

#endif // __CCSCENE_H__
