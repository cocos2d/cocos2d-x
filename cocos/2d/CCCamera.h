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

/**@~english
 * Note: 
 * Scene creates a default camera. And the default camera mask of Node is 1, therefore it can be seen by the default camera.
 * During rendering the scene, it draws the objects seen by each camera in the added order except default camera. The default camera is the last one being drawn with.
 * It's usually a good idea to render 3D objects in a separate camera.
 * And set the 3d camera flag to CameraFlag::USER1 or anything else except DEFAULT. Dedicate The DEFAULT camera for UI, because it is rendered at last.
 * You can change the camera order to get different result when depth test is not enabled.
 * For each camera, transparent 3d sprite is rendered after opaque 3d sprite and other 2d objects.
 * @~chinese 
 * 注意:
 * 场景创建一个默认的相机。节点的默认相机掩码是1,因此它可以被默认的相机看到。
 * 在渲染场景期间，除了默认相机以外，其余相机会通过按添加顺序对所看到的物体进行绘制，默认的相机是最后一个进行绘制的。
 * 这对使用一个单独的相机来渲染3d对象来说是一个不错的主意。
 * 除了DEFAULT以外，可以使用CameraFlag::USER1或者其他值来设置3d相机标识，把默认的相机留给UI,是因为它最后渲染。
 * 当不启用深度测试时你可以改变相机以得到不同的结果。
 * 对于每一个相机,会先渲染完不透明的3d精灵和2d对象后才会渲染透明的3d精灵。
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

/**@~english
* Defines a camera .
 * @~chinese 
 * 定义了一个相机。
*/
class CC_DLL Camera :public Node
{
    friend class Scene;
public:
    /**@~english
    * The type of camera.
     * @~chinese 
     * 相机的类型。
    */
    enum class Type
    {
        PERSPECTIVE = 1,
        ORTHOGRAPHIC = 2
    };
public:
    /**@~english
    * Creates a perspective camera.
    *
     * @~chinese 
     * 创建一个透视相机。
     * 
    * @param fieldOfView @~english The field of view for the perspective camera (normally in the range of 40-60 degrees).
     * @~chinese 透视相机的可视角度 (一般是在40-60度之间).
    * @param aspectRatio @~english The aspect ratio of the camera (normally the width of the viewport divided by the height of the viewport).
     * @~chinese 相机的长宽比(通常会使用视窗的宽度除以视窗的高度)。
    * @param nearPlane @~english The near plane distance.
     * @~chinese 近平面的距离。
    * @param farPlane @~english The far plane distance.
     * @~chinese 远平面的距离。
    */
    static Camera* createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    /**@~english
    * Creates an orthographic camera.
    *
     * @~chinese 
     * 创建一个正交相机。
     * 
    * @param zoomX @~english The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).
    * @~chinese 沿x轴的正交投影的缩放因子(正交投影的宽度)。
    * @param zoomY @~english The zoom factor along the Y-axis of the orthographic projection (the height of the ortho projection).
    * @~chinese 沿y轴的正交投影的缩放因子(正交投影的高度)。
    * @param nearPlane @~english The near plane distance.
     * @~chinese 近平面的距离。
    * @param farPlane @~english The far plane distance.
     * @~chinese 远平面的距离。
    */
    static Camera* createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);

    /** @~english create default camera, the camera type depends on Director::getProjection, the depth of the default camera is 0
     * @~chinese 创建默认的相机,相机的类型取决于Director::getProjection,默认的相机深度是0*/
    static Camera* create();
    
    /**@~english
    * Gets the type of camera.
    *
     * @~chinese 
     * 得到相机的类型。
     * 
    * @return @~english The camera type.
     * @~chinese 相机的类型。
    */
    Camera::Type getType() const { return _type; }

    /**@~english get & set Camera flag @~chinese 获取和设置相机标识*/
    CameraFlag getCameraFlag() const { return (CameraFlag)_cameraFlag; }
    void setCameraFlag(CameraFlag flag) { _cameraFlag = (unsigned short)flag; }

    /**@~english
    * Make Camera looks at target
    *
     * @~chinese 
     * 使相机看着目标
     * 
    * @param target @~english The target camera is point at
     * @~chinese 目标的位置
    * @param up @~english The up vector, usually it's Y axis
     * @~chinese 相机向上的向量,通常这是Y轴
    */
    virtual void lookAt(const Vec3& target, const Vec3& up = Vec3::UNIT_Y);

    /**@~english
    * Gets the camera's projection matrix.
    *
     * @~chinese 
     * 获取相机的投影矩阵。
     * 
    * @return @~english The camera projection matrix.
     * @~chinese 相机投影矩阵。
    */
    const Mat4& getProjectionMatrix() const;
    /**@~english
    * Gets the camera's view matrix.
    *
     * @~chinese 
     * 获取相机的视图矩阵。
     * 
    * @return @~english The camera view matrix.
     * @~chinese 相机视图矩阵。
    */
    const Mat4& getViewMatrix() const;

    /**@~english get view projection matrix @~chinese 得到视图投影矩阵*/
    const Mat4& getViewProjectionMatrix() const;
    
    /* @~english convert the specified point of viewport from world-space coordinates into the screen-space coordinates.
     *
     * @~chinese 把指定坐标点从世界坐标转换为屏幕坐标。
     * 
     * @param src @~english The world-space position.
     * @~chinese 世界的位置。
     * @return @~english The screen-space position.
     * @~chinese 屏幕的位置。
     */
    Vec2 project(const Vec3& src) const;
    
    /**@~english
     * Convert the specified point of viewport from screen-space coordinate into the world-space coordinate.
     *
     * @~chinese 
     * 把指定坐标点从屏幕坐标转换为世界坐标。
     * 
     * @param src @~english The screen-space position.
     * @~chinese 屏幕的位置。
     * @return @~english The world-space position.
     * @~chinese 世界的位置。
     */
    Vec3 unproject(const Vec3& src) const;

    /**@~english
     * Convert the specified point of viewport from screen-space coordinate into the world-space coordinate.
     *
     * @~chinese 
     * 把指定坐标点从屏幕坐标转换为世界坐标。
     *
     * @param viewport @~english The viewport size to use.
     * @~chinese 使用的视窗大小。
     * @param src @~english The screen-space position.
     * @~chinese 屏幕的位置。
     * @param dst @~english The world-space position.
     * @~chinese 世界的位置。
     */
    void unproject(const Size& viewport, const Vec3* src, Vec3* dst) const;
    
    /**@~english
     * Is this aabb visible in frustum
     * @~chinese 
     * aabb在视椎体内是否可见
     */
    bool isVisibleInFrustum(const AABB* aabb) const;
    
    /**@~english
     * Get object depth towards camera
     * @~chinese 
     * 获取朝向相机的物体深度
     */
    float getDepthInView(const Mat4& transform) const;
    
    /**@~english
     * set depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with CameraFlag::DEFAULT is 0, user defined camera is -1 by default
     * @~chinese
     * 设置深度，相比深度小的，深度较大的相机会绘制在顶端，标识是CameraFlag::DEFAULT的相机深度是0，用户定义的相机深度默认为-1
     */
    void setDepth(int depth);
    
    /**@~english
     * get depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with CameraFlag::DEFAULT is 0, user defined camera is -1 by default
     * @~chinese 
     * 获取深度，相比深度小的，深度较大的相机会绘制在顶端，标识是CameraFlag::DEFAULT的相机深度是0，用户定义的相机深度默认为-1
     */
    int getDepth() const { return _depth; }
    
    /**@~english
     * Get the frustum's far plane.
     * @~chinese 
     * 获取视椎体远平面。
     */
    float getFarPlane() const { return _farPlane; }

    /**@~english
     * Get the frustum's near plane.
     * @~chinese 
     * 获取视椎体近平面。
     */
    float getNearPlane() const { return _nearPlane; }
    
    //override
    virtual void onEnter() override;
    virtual void onExit() override;

    /**@~english
     * Get the visiting camera , the visiting camera shall be set on Scene::render
     * @~chinese 
     * 获取绘制的相机,绘制的相机会在Scene::render中设置。
     */
    static const Camera* getVisitingCamera() { return _visitingCamera; }

    /**@~english
     * Get the default camera of the current running scene.
     * @~chinese 
     * 获取到当前运行场景的默认相机。
     */
    static Camera* getDefaultCamera();
    
    void clearBackground(float depth);
    
CC_CONSTRUCTOR_ACCESS:
    Camera();
    ~Camera();
    
    /**@~english
     * Set the scene,this method shall not be invoke manually
     * @~chinese 
     * 设置场景,这种方法不应该手动调用
     */
    void setScene(Scene* scene);
    
    /**@~english set additional matrix for the projection matrix, it multiplys mat to projection matrix when called, used by WP8
     * @~chinese 对投影矩阵设置额外的矩阵,WP8使用时，调用的时候它会乘以投影矩阵*/
    void setAdditionalProjection(const Mat4& mat);
    
    /** @~english init camera  @~chinese 初始化相机*/
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
