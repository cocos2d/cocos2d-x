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
#ifndef __cocos2d_libs__CCPhysicsNode__
#define __cocos2d_libs__CCPhysicsNode__

#include "cocos2d.h"


NS_CC_BEGIN

class PhysicsNode : public Scene {
public:
    static PhysicsNode* create();
    
    virtual ~PhysicsNode() {}
    PhysicsNode();

    virtual Mat4 getNodeToWorldTransform() const;
    void setGravity(cocos2d::Point& gravity);
    cocos2d::Point getGravity();
    
protected:
    bool initWithPhysics();

};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCPhysicsNode__) */
