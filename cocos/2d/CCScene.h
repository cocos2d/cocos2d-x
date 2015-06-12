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

#ifndef __CCSCENE_H__
#define __CCSCENE_H__

#include <string>
#include "2d/CCNode.h"

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
/**
 * @addtogroup _2d
 * @{
 */

/** @class Scene
 * @brief @~english Scene is a subclass of Node that is used only as an abstract concept.
 * Scene and Node are almost identical with the difference that Scene has its
 * anchor point (by default) at the center of the screen.
 * 
 * It is a good practice to use a Scene as the parent of all your nodes.
 *  
 * Scene will create a default camera for you.
 * @~chinese 场景是 Node 的子类，仅作为一个抽象的概念。
 * 
 * 场景和节点是几乎相同，区别在于默认情况下场景的锚点在屏幕的中心。
 * 
 * 推荐使用一个场景做为父节点，场景将为您创建一个默认的相机。
*/
class CC_DLL Scene : public Node
{
public:
    /** @~english Creates a new Scene object. 
     *
     * @~chinese 创建一个新场景对象。
     * 
     * @return @~english An autoreleased Scene object.
     * @~chinese 一个 autorelease 的场景对象。
     */
    static Scene *create();

    /** @~english Creates a new Scene object with a predefined Size. 
     *
     * @~chinese 使用指定的大小创建一个新场景对象。
     * 
     * @param size @~english The predefined size of scene.
     * @~chinese 预定义的场景的大小。
     * @return @~english An autoreleased Scene object.
     * @~chinese 一个 autorelease 的场景对象。
     * @js NA
     */
    static Scene *createWithSize(const Size& size);

    using Node::addChild;
    virtual std::string getDescription() const override;
    
    /** @~english Get all cameras.
     * 
     * @~chinese 获取所有相机。
     * 
     * @return @~english The vector of all cameras.
     * @~chinese 相机对象的数组。
     * @js NA
     */
    const std::vector<Camera*>& getCameras() const { return _cameras; }

    /** @~english Get the default camera.
     * @~chinese 获取默认的相机。
     * @return @~english The default camera of scene.
     * @~chinese 默认的相机对象。
     * @js NA
     */
    Camera* getDefaultCamera() const { return _defaultCamera; }

    /** @~english Get lights.
     * @~chinese 获取灯光数组
     * @return @~english The vector of lights.
     * @~chinese 灯光对象的数组
     * @js NA
     */
    const std::vector<BaseLight*>& getLights() const { return _lights; }
    
    /** @~english Render the scene.
     * @~chinese 渲染场景。
     * @param renderer @~english The renderer use to render the scene.
     * @~chinese 渲染场景使用的渲染器。
     * @js NA
     */
    void render(Renderer* renderer);
    
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
    Camera*              _defaultCamera; //weak ref, default camera created by scene, _cameras[0], Caution that the default camera can not be added to _cameras before onEnter is called
    bool                 _cameraOrderDirty; // order is dirty, need sort
    EventListenerCustom*       _event;

    std::vector<BaseLight *> _lights;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Scene);
    
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
public:
    virtual void addChild(Node* child, int zOrder, int tag) override;
    virtual void addChild(Node* child, int zOrder, const std::string &name) override;
    
#if CC_USE_PHYSICS
    /** @~english Get the physics world of the scene.
     * @~chinese 获取场景使用的物理世界对象。
     * @return @~english The physics world of the scene.
     * @~chinese 物理世界对象。
     * @js NA
     */
    inline PhysicsWorld* getPhysicsWorld() { return _physicsWorld; }
#endif
    
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
    /** @~english Get the 3d physics world of the scene.
     * @~chinese 获得场景的 3D 物理世界。
     * @return @~english The 3d physics world of the scene.
     * @~chinese 3D 物理世界对象。
     * @js NA
     */
    inline Physics3DWorld* getPhysics3DWorld() { return _physics3DWorld; }
    
    /** @~english
     * Set Physics3D debug draw camera.
     * @~chinese 
     * 设置 Physics3D 调试相机。
     */
    void setPhysics3DDebugCamera(Camera* camera);
#endif
    
    /** @~english Create a scene with physics.
     * @~chinese 创建一个包含物理世界的场景。
     * @return @~english An autoreleased Scene object with physics.
     * @~chinese 一个包含物理世界的场景（已经被 autorelease）。
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
};

// end of _2d group
/// @}

NS_CC_END

#endif // __CCSCENE_H__
