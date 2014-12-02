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

#include "CCPhysicsNode.h"
#include "CCBPhysicsWorld.h"

NS_CC_BEGIN


PhysicsNode::PhysicsNode() {
}

PhysicsNode* PhysicsNode::create() {
    PhysicsNode* ret = new PhysicsNode();
    
    if (ret->initWithPhysics()) {
        ret->autorelease();
        return ret;
    }
    return NULL;
}

Mat4 PhysicsNode::getNodeToWorldTransform() const
{
    return this->getNodeToParentTransform();
}

bool PhysicsNode::initWithPhysics()
{
    bool ret = false;
//    ret = Scene::initWithPhysics();
    
    do
    {
        Director * director;
        CC_BREAK_IF( ! (director = Director::getInstance()) );
        this->setContentSize(director->getWinSize());
        CC_BREAK_IF(! (_physicsWorld = spritebuilder::CCBPhysicsWorld::construct(*this)));
        
        this->scheduleUpdate();
        // success
        ret = true;
    } while (0);
    return ret;
    
    this->setContentSize(Size(0, 0));
    //this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    return ret;
}
void PhysicsNode::setGravity(cocos2d::Point& gravity) {
    getPhysicsWorld()->setGravity(Vect(gravity.x, gravity.y));
}
cocos2d::Point PhysicsNode::getGravity() {
    Vect gravity = getPhysicsWorld()->getGravity();
    return cocos2d::Point(gravity.x, gravity.y);
}


NS_CC_END
