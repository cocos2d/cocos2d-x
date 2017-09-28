/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.
 
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
#pragma once

#include "Macros.h"
#include "Collider.h"

NS_CCR_BEGIN

class Contract : public cocos2d::Ref
{
public:
    enum class CollisionType
    {
        NONE,
        ENTER,
        STAY,
        EXIT
    };
    
    Collider* getCollider1() const;
    Collider* getCollider2() const;
    
private:
    friend class ColliderManager;
    
    Contract(Collider* collider1, Collider* collider2);
    ~Contract();
    CollisionType updateState();
    bool test() const;
    
    static bool isBoxCollider(Collider* collider);
    static bool isPolygonCollider(Collider* collider);
    static bool isCircleCollider(Collider* collider);
    
    Collider* _collider1;
    Collider* _collider2;
    bool _touching;
    bool _isPolygonPolygon;
    bool _isCircleCircle;
    bool _isPolygonCircle;
    
    CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(Contract);
};

NS_CCR_END
