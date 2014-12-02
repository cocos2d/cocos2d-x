/*
 *
 * Copyright (c) 2014 Nguyen Thai Duong
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __cocos2d_libs__CCBPhysicsWorld__
#define __cocos2d_libs__CCBPhysicsWorld__

#include <iostream>
#include "cocos2d.h"
#include "CCPhysicsNode.h"

namespace spritebuilder {
    
    class CCBPhysicsWorld : public cocos2d::PhysicsWorld {
    public:

    protected:
        virtual void update(float delta);
        virtual void debugDraw();        
        static CCBPhysicsWorld* construct(cocos2d::PhysicsNode& scene);
        friend class cocos2d::PhysicsNode;
    };
 
    class CCBPhysicsDebugDraw : public cocos2d::PhysicsDebugDraw
    {
    public:
        virtual void drawShape(cocos2d::PhysicsShape& shape);
        virtual void drawJoint(cocos2d::PhysicsJoint& joint);
        virtual void drawContact();
    protected:
        CCBPhysicsDebugDraw(CCBPhysicsWorld& world);
        friend class CCBPhysicsWorld;
    };
    extern const float PHYSICS_INFINITY;
}

#endif /* defined(__cocos2d_libs__CCBPhysicsWorld__) */
