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
/**
 * @addtogroup scene
 * @{
 */

/** @brief Scene is a subclass of Node that is used only as an abstract concept.

Scene and Node are almost identical with the difference that Scene has its
anchor point (by default) at the center of the screen.

For the moment Scene has no other logic than that, but in future releases it might have
additional logic.

It is a good practice to use a Scene as the parent of all your nodes.
*/
class CC_DLL Scene : public Node
{
public:
    /** creates a new Scene object */
    static Scene *create();

    /** creates a new Scene object with a predefined Size */
    static Scene *createWithSize(const Size& size);

    // Overrides
    virtual Scene *getScene() const override;

    using Node::addChild;
    virtual std::string getDescription() const override;
    
    /** get all cameras */
    const std::vector<Camera*>& getCameras() const { return _cameras; }

    const std::vector<BaseLight*>& getLights() const { return _lights; }
    
    /** render the scene */
    void render(Renderer* renderer);
    
CC_CONSTRUCTOR_ACCESS:
    Scene();
    virtual ~Scene();
    
    bool init();
    bool initWithSize(const Size& size);
    
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
    EventListenerCustom*       _event;

    std::vector<BaseLight *> _lights;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Scene);
    
#if CC_USE_PHYSICS
public:
    virtual void addChild(Node* child, int zOrder, int tag) override;
    virtual void addChild(Node* child, int zOrder, const std::string &name) override;
    virtual void update(float delta) override;
    inline PhysicsWorld* getPhysicsWorld() { return _physicsWorld; }
    static Scene *createWithPhysics();
    
CC_CONSTRUCTOR_ACCESS:
    bool initWithPhysics();
    
protected:
    void addChildToPhysicsWorld(Node* child);

    PhysicsWorld* _physicsWorld;
#endif // CC_USE_PHYSICS
};

// end of scene group
/// @}

NS_CC_END

#endif // __CCSCENE_H__
