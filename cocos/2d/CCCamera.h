/****************************************************************************
Copyright (c) 2014 Chukong Technologies Inc.

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
#ifndef _CCCAMERA_H__
#define _CCCAMERA_H__

#include "2d/CCNode.h"
#include "3d/CCFrustum.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class Scene;

/**
 * Note: 
 * Scene creates a default camera. And the default camera mask of Node is 1, therefore it can be seen by the default camera.
 * During rendering the scene, it draws the objects seen by each camera in the added order except default camera. The default camera is the last one being drawn with.
 * It's usually a good idea to render 3D objects in a separate camera.
 * And set the 3d camera flag to CameraFlag::USER1 or anything else except DEFAULT. Dedicate The DEFAULT camera for UI, because it is rendered at last.
 * You can change the camera order to get different result when depth test is not enabled.
 * For each camera, transparent 3d sprite is rendered after opaque 3d sprite and other 2d objects.
 */
enum class CameraFlag
{
    DEFAULT = 1,
    USER1 = 1 << 1,
    USER2 = 1 << 2,
    USER3 = 1 << 3,
    USER4 = 1 << 4,
    USER5 = 1 << 5,
    USER6 = 1 << 6,
    USER7 = 1 << 7,
    USER8 = 1 << 8,
};

/**
* Defines a camera .
*/
class CC_DLL Camera :public Node
{
    friend class Scene;
public:
    /**
    * The type of camera.
    */
    enum class Type
    {
        PERSPECTIVE = 1,
        ORTHOGRAPHIC = 2
    };
public:
    /**
    * Creates a perspective camera.
    *
    * @param fieldOfView The field of view for the perspective camera (normally in the range of 40-60 degrees).
    * @param aspectRatio The aspect ratio of the camera (normally the width of the viewport divided by the height of the viewport).
    * @param nearPlane The near plane distance.
    * @param farPlane The far plane distance.
    */
    static Camera* createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    /**
    * Creates an orthographic camera.
    *
    * @param zoomX The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).
    * @param zoomY The zoom factor along the Y-axis of the orthographic projection (the height of the ortho projection).
    * @param nearPlane The near plane distance.
    * @param farPlane The far plane distance.
    */
    static Camera* createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);

    /** create default camera, the camera type depends on Director::getProjection, the depth of the default camera is 0 */
    static Camera* create();
    
    /**
    * Gets the type of camera.
    *
    * @return The camera type.
    */
    Camera::Type getType() const { return _type; }

    /**get & set Camera flag*/
    CameraFlag getCameraFlag() const { return (CameraFlag)_cameraFlag; }
    void setCameraFlag(CameraFlag flag) { _cameraFlag = (unsigned short)flag; }

    /**
    * Make Camera looks at target
    *
    * @param target The target camera is point at
    * @param up The up vector, usually it's Y axis
    */
    virtual void lookAt(const Vec3& target, const Vec3& up = Vec3::UNIT_Y);

    /**
    * Gets the camera's projection matrix.
    *
    * @return The camera projection matrix.
    */
    const Mat4& getProjectionMatrix() const;
    /**
    * Gets the camera's view matrix.
    *
    * @return The camera view matrix.
    */
    const Mat4& getViewMatrix() const;

    /**get view projection matrix*/
    const Mat4& getViewProjectionMatrix() const;
    
    /* convert the specified point of viewport from world-space coordinates into the screen-space coordinates.
     *
     * @param src The world-space position.
     * @return The screen-space position.
     */
    Vec2 project(const Vec3& src) const;
    
    /**
     * Convert the specified point of viewport from screen-space coordinate into the world-space coordinate.
     *
     * @param src The screen-space position.
     * @return The world-space position.
     */
    Vec3 unproject(const Vec3& src) const;

    /**
     * Convert the specified point of viewport from screen-space coordinate into the world-space coordinate.
     *
     * @param viewport The viewport size to use.
     * @param src The screen-space position.
     * @param dst The world-space position.
     */
    void unproject(const Size& viewport, const Vec3* src, Vec3* dst) const;
    
    /**
     * Is this aabb visible in frustum
     */
    bool isVisibleInFrustum(const AABB* aabb) const;
    
    /**
     * Get object depth towards camera
     */
    float getDepthInView(const Mat4& transform) const;
    
    /**
     * set depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with CameraFlag::DEFAULT is 0, user defined camera is -1 by default
     */
    void setDepth(int depth);
    
    /**
     * get depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with CameraFlag::DEFAULT is 0, user defined camera is -1 by default
     */
    int getDepth() const { return _depth; }
    
    /**
     * Get the frustum's far plane.
     */
    float getFarPlane() const { return _farPlane; }

    /**
     * Get the frustum's near plane.
     */
    float getNearPlane() const { return _nearPlane; }
    
    //override
    virtual void onEnter() override;
    virtual void onExit() override;

    /**
     * Get the visiting camera , the visiting camera shall be set on Scene::render
     */
    static const Camera* getVisitingCamera() { return _visitingCamera; }

    /**
     * Get the default camera of the current running scene.
     */
    static Camera* getDefaultCamera();
    
    void clearBackground(float depth);
    
CC_CONSTRUCTOR_ACCESS:
    Camera();
    ~Camera();
    
    /**
     * Set the scene,this method shall not be invoke manually
     */
    void setScene(Scene* scene);
    
    /**set additional matrix for the projection matrix, it multiplys mat to projection matrix when called, used by WP8*/
    void setAdditionalProjection(const Mat4& mat);
    
    /** init camera */
    bool initDefault();
    bool initPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    bool initOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);
    
protected:

    Scene* _scene; //Scene camera belongs to
    Mat4 _projection;
    mutable Mat4 _view;
    mutable Mat4 _viewInv;
    mutable Mat4 _viewProjection;
    Vec3 _up;
    Camera::Type _type;
    float _fieldOfView;
    float _zoom[2];
    float _aspectRatio;
    float _nearPlane;
    float _farPlane;
    mutable bool  _viewProjectionDirty;
    unsigned short _cameraFlag; // camera flag
    mutable Frustum _frustum;   // camera frustum
    mutable bool _frustumDirty;
    int  _depth;                 //camera depth, the depth of camera with CameraFlag::DEFAULT flag is 0 by default, a camera with larger depth is drawn on top of camera with smaller detph
    static Camera* _visitingCamera;
    
    friend class Director;
};

NS_CC_END

#endif// __CCCAMERA_H_
