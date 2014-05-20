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

#include "2d/CCNode.h"
#include "physics/CCPhysicsWorld.h"

NS_CC_BEGIN

/**
 * @addtogroup scene
 * @{
 */

/** @brief Scene(场景)是一个抽象的概念，仅被用作Node(节点)的一个子类.

Scene(场景)和Node(节点)几乎相同，不同的是Scene的默认锚点在屏幕的中心. 
 
 现在 scene 没有其它的逻辑，但在未来的版本中它可能有
 额外的逻辑.
 
 把 Scene 作为所有 node 的parent 是一个很好的做法.
*/
class CC_DLL Scene : public Node
{
public:
    /** 创建一个新的Scene对象 */
    static Scene *create();

    // Overrides
    virtual Scene *getScene() override;

    using Node::addChild;
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    Scene();
    virtual ~Scene();
    
    virtual bool init() override;

protected:
    friend class Node;
    friend class ProtectedNode;
    friend class SpriteBatchNode;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Scene);
    
#if CC_USE_PHYSICS
public:
    virtual void addChild(Node* child, int zOrder, int tag) override;
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
