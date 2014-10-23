/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
Copyright (c) 2014      Sergey Perepelitsa

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

#ifndef __CCPHYSICSNODE_H__
#define __CCPHYSICSNODE_H__

#include "2d/CCNode.h"

NS_CC_BEGIN

class PhysicsWorld;

class CC_DLL PhysicsNode : public Node
{
public:
    /** creates a new PhysicsNode object */
    static PhysicsNode *create();

    using Node::addChild;
    virtual std::string getDescription() const override;
    
    virtual void visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    using Node::visit;

CC_CONSTRUCTOR_ACCESS:
    PhysicsNode();
    virtual ~PhysicsNode();
    virtual bool init() override;
    
protected:
    friend class Node;
    friend class ProtectedNode;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(PhysicsNode);
    
#if CC_USE_PHYSICS
public:
    virtual void addChild(Node* child, int zOrder, int tag) override;
    virtual void addChild(Node* child, int zOrder, const std::string &name) override;
    virtual void update(float delta) override;
    inline PhysicsWorld* getPhysicsWorld() { return _physicsWorld; }
    virtual PhysicsNode* getPhysicsNode() const override;
    const Mat4& getInverseModelViewTransform() const;
protected:
    bool initWithPhysics();
    void addChildToPhysicsWorld(Node* child);

    PhysicsWorld* _physicsWorld;
    Mat4 _inverseModelViewTransform;
#endif // CC_USE_PHYSICS
};

NS_CC_END

#endif // __CCPHYSICSNODE_H__
