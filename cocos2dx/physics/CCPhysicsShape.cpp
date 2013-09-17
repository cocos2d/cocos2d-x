/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "CCPhysicsShape.h"
#ifdef CC_USE_PHYSICS

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
#include "chipmunk.h"
#elif (CC_PHYSICS_ENGINE == CCPHYSICS_BOX2D)
#include "Box2D.h"
#endif

#include "CCPhysicsBody.h"

#include "chipmunk/CCPhysicsBodyInfo.h"
#include "Box2D/CCPhysicsBodyInfo.h"
#include "chipmunk/CCPhysicsShapeInfo.h"
#include "Box2D/CCPhysicsShapeInfo.h"
#include "chipmunk/CCPhysicsHelper.h"

NS_CC_BEGIN

PhysicsShape::PhysicsShape()
: _body(nullptr)
, _info(nullptr)
, _type(Type::UNKNOWN)
{
    
}

PhysicsShape::~PhysicsShape()
{
    CC_SAFE_DELETE(_info);
}

bool PhysicsShape::init(PhysicsBody* body, Type type)
{
    if (body == nullptr) return false;
    
    _body = body;
    
    _info = new PhysicsShapeInfo(this);
    if (_info == nullptr) return false;
    
    _type = type;
    
    return true;
}

void PhysicsShape::addToBody()
{
    if(_body != nullptr) _body->addShape(this);
}

PhysicsBodyInfo* PhysicsShape::bodyInfo() const
{
    return _body->_info;
}

PhysicsShapeCircle::PhysicsShapeCircle()
{
    
}

PhysicsShapeCircle::~PhysicsShapeCircle()
{
    
}

PhysicsShapeBox::PhysicsShapeBox()
{
    
}

PhysicsShapeBox::~PhysicsShapeBox()
{
    
}

PhysicsShapePolygon::PhysicsShapePolygon()
{
    
}

PhysicsShapePolygon::~PhysicsShapePolygon()
{
    
}

PhysicsShapeEdgeBox::PhysicsShapeEdgeBox()
{
    
}

PhysicsShapeEdgeBox::~PhysicsShapeEdgeBox()
{
    
}

PhysicsShapeEdgeChain::PhysicsShapeEdgeChain()
{
    
}

PhysicsShapeEdgeChain::~PhysicsShapeEdgeChain()
{
    
}

PhysicsShapeEdgePolygon::PhysicsShapeEdgePolygon()
{
    
}

PhysicsShapeEdgePolygon::~PhysicsShapeEdgePolygon()
{
    
}

PhysicsShapeEdgeSegment::PhysicsShapeEdgeSegment()
{
    
}

PhysicsShapeEdgeSegment::~PhysicsShapeEdgeSegment()
{
    
}

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)

// PhysicsShapeCircle
PhysicsShapeCircle* PhysicsShapeCircle::create(PhysicsBody* body, float radius, Point offset/* = Point(0, 0)*/)
{
    PhysicsShapeCircle* shape = new PhysicsShapeCircle();
    if (shape && shape->init(body, radius, offset))
    {
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeCircle::init(PhysicsBody* body, float radius, Point offset /*= Point(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(body, Type::CIRCLE));
        
        cpShape* shape = cpCircleShapeNew(bodyInfo()->body, radius, PhysicsHelper::point2cpv(offset));
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        addToBody();
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeEdgeSegment
PhysicsShapeEdgeSegment* PhysicsShapeEdgeSegment::create(PhysicsBody* body, Point a, Point b, float border/* = 1*/)
{
    PhysicsShapeEdgeSegment* shape = new PhysicsShapeEdgeSegment();
    if (shape && shape->init(body, a, b, border))
    {
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgeSegment::init(PhysicsBody* body, Point a, Point b, float border/* = 1*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(body, Type::EDGESEGMENT));
        
        cpShape* shape = cpSegmentShapeNew(bodyInfo()->body,
                                           PhysicsHelper::point2cpv(a),
                                           PhysicsHelper::point2cpv(b),
                                           PhysicsHelper::float2cpfloat(border));
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        addToBody();
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeBox
PhysicsShapeBox* PhysicsShapeBox::create(PhysicsBody* body, Size size, Point offset/* = Point(0, 0)*/)
{
    PhysicsShapeBox* shape = new PhysicsShapeBox();
    if (shape && shape->init(body, size, offset))
    {
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeBox::init(PhysicsBody* body, Size size, Point offset /*= Point(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(body, Type::BOX));
        
        cpShape* shape = cpBoxShapeNew(bodyInfo()->body, PhysicsHelper::float2cpfloat(size.width), PhysicsHelper::float2cpfloat(size.height));
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        addToBody();
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeCircle
PhysicsShapePolygon* PhysicsShapePolygon::create(PhysicsBody* body, Point* points, int count, Point offset/* = Point(0, 0)*/)
{
    PhysicsShapePolygon* shape = new PhysicsShapePolygon();
    if (shape && shape->init(body, points, count, offset))
    {
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapePolygon::init(PhysicsBody* body, Point* points, int count, Point offset /*= Point(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(body, Type::POLYGEN));
        
        cpVect* vecs = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vecs, count);
        cpShape* shape = cpPolyShapeNew(bodyInfo()->body, count, vecs, PhysicsHelper::point2cpv(offset));
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        addToBody();
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeEdgeBox
PhysicsShapeEdgeBox* PhysicsShapeEdgeBox::create(PhysicsBody* body, Size size, float border/* = 1*/, Point offset/* = Point(0, 0)*/)
{
    PhysicsShapeEdgeBox* shape = new PhysicsShapeEdgeBox();
    if (shape && shape->init(body, size, border, offset))
    {
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgeBox::init(PhysicsBody* body, Size size, float border/* = 1*/, Point offset/*= Point(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(body, Type::EDGEBOX));
        
        Point bodyPos = body->getPosition();
        
        cpVect vec[4] = {};
        vec[0] = PhysicsHelper::point2cpv(Point(bodyPos.x-size.width/2+offset.x, bodyPos.y-size.height/2+offset.y));
        vec[1] = PhysicsHelper::point2cpv(Point(bodyPos.x+size.width/2+offset.x, bodyPos.y-size.height/2+offset.y));
        vec[2] = PhysicsHelper::point2cpv(Point(bodyPos.x+size.width/2+offset.x, bodyPos.y+size.height/2+offset.y));
        vec[3] = PhysicsHelper::point2cpv(Point(bodyPos.x-size.width/2+offset.x, bodyPos.y+size.height/2+offset.y));
        
        int i = 0;
        for (; i < 4; ++i)
        {
            cpShape* shape = cpSegmentShapeNew(bodyInfo()->body, vec[i], vec[(i+1)%4],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
			cpShapeSetElasticity(shape, 1.0f);
			cpShapeSetFriction(shape, 1.0f);
            _info->add(shape);
        }
        CC_BREAK_IF(i < 4);
        
        addToBody();
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeEdgeBox
PhysicsShapeEdgePolygon* PhysicsShapeEdgePolygon::create(PhysicsBody* body, Point* points, int count, float border/* = 1*/)
{
    PhysicsShapeEdgePolygon* shape = new PhysicsShapeEdgePolygon();
    if (shape && shape->init(body, points, count, border))
    { 
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgePolygon::init(PhysicsBody* body, Point* points, int count, float border/* = 1*/)
{
    cpVect* vec = nullptr;
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(body, Type::EDGEPOLYGEN));
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        
        int i = 0;
        for (; i < count; ++i)
        {
            cpShape* shape = cpSegmentShapeNew(bodyInfo()->body, vec[i], vec[(i+1)%count],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
			cpShapeSetElasticity(shape, 1.0f);
			cpShapeSetFriction(shape, 1.0f);
            _info->add(shape);
        }
        CC_BREAK_IF(i < count);
        
        addToBody();
        
        if (vec != nullptr) delete[] vec;
        return true;
    } while (false);
    
    if (vec != nullptr) delete[] vec;
    
    return false;
}

// PhysicsShapeEdgeChain
PhysicsShapeEdgeChain* PhysicsShapeEdgeChain::create(PhysicsBody* body, Point* points, int count, float border/* = 1*/)
{
    PhysicsShapeEdgeChain* shape = new PhysicsShapeEdgeChain();
    if (shape && shape->init(body, points, count, border))
    {
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgeChain::init(PhysicsBody* body, Point* points, int count, float border/* = 1*/)
{
    cpVect* vec = nullptr;
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(body, Type::EDGECHAIN));
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        
        int i = 0;
        for (; i < count - 1; ++i)
        {
            cpShape* shape = cpSegmentShapeNew(bodyInfo()->body, vec[i], vec[i+1],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
			cpShapeSetElasticity(shape, 1.0f);
			cpShapeSetFriction(shape, 1.0f);
            _info->add(shape);
        }
        CC_BREAK_IF(i < count);
        
        addToBody();
        
        if (vec != nullptr) delete[] vec;
        return true;
    } while (false);
    
    if (vec != nullptr) delete[] vec;
    
    return false;
}


#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

#endif

NS_CC_END

#endif // CC_USE_PHYSICS