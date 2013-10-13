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
#include "CCPhysicsWorld.h"

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
, _area(0)
, _mass(0)
, _angularDamping(0)
, _tag(0)
, _enable(true)
{
    
}

PhysicsShape::~PhysicsShape()
{
    CC_SAFE_DELETE(_info);
}

bool PhysicsShape::init(Type type, PhysicsMaterial material/* = MaterialDefault*/)
{
    _info = new PhysicsShapeInfo(this);
    if (_info == nullptr) return false;
    
    _type = type;
    _material = material;
    
    return true;
}

void PhysicsShape::setMass(float mass)
{
    
}

void PhysicsShape::setEnable(bool enable)
{
    if (_enable != enable)
    {
        _enable = enable;
        
        if (_body->getWorld() && _body->isEnable())
        {
            if (enable)
            {
                _body->getWorld()->addShape(this);
            }else
            {
                _body->getWorld()->removeShape(this);
            }
        }
    }
}

void PhysicsShape::addToBody()
{
    if(_body != nullptr) _body->addShape(this);
}

PhysicsBodyInfo* PhysicsShape::bodyInfo() const
{
    if (_body != nullptr)
    {
        return _body->_info;
    }else
    {
        return nullptr;
    }
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

void PhysicsShape::initEnd()
{
    for (auto shape : _info->shapes)
    {
        cpShapeSetElasticity(shape, _material.elasticity);
        cpShapeSetFriction(shape, _material.friction);
    }
}

void PhysicsShape::setElasticity(float elasticity)
{
    for (cpShape* shape : _info->shapes)
    {
        cpShapeSetElasticity(shape, PhysicsHelper::float2cpfloat(elasticity));
    }
}

void PhysicsShape::setFriction(float friction)
{
    for (cpShape* shape : _info->shapes)
    {
        cpShapeSetFriction(shape, PhysicsHelper::float2cpfloat(friction));
    }
}

// PhysicsShapeCircle
PhysicsShapeCircle* PhysicsShapeCircle::create(float radius, PhysicsMaterial material/* = MaterialDefault*/, Point offset/* = Point(0, 0)*/)
{
    PhysicsShapeCircle* shape = new PhysicsShapeCircle();
    if (shape && shape->init(radius, material, offset))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeCircle::init(float radius, PhysicsMaterial material/* = MaterialDefault*/, Point offset /*= Point(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::CIRCLE, material));
        
        cpShape* shape = cpCircleShapeNew(_info->shareBody, radius, PhysicsHelper::point2cpv(offset));
        
        CC_BREAK_IF(shape == nullptr);
        
        _area = PhysicsHelper::cpfloat2float(cpAreaForCircle(0, radius));
        _mass = _material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : _material.density * _area;
        _angularDamping = _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY : cpMomentForCircle(_mass, 0, radius, PhysicsHelper::point2cpv(offset));
        
        _info->add(shape);
        
        initEnd();
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeEdgeSegment
PhysicsShapeEdgeSegment* PhysicsShapeEdgeSegment::create(Point a, Point b, PhysicsMaterial material/* = MaterialDefault*/, float border/* = 1*/)
{
    PhysicsShapeEdgeSegment* shape = new PhysicsShapeEdgeSegment();
    if (shape && shape->init(a, b, material, border))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgeSegment::init(Point a, Point b, PhysicsMaterial material/* = MaterialDefault*/, float border/* = 1*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGESEGMENT, material));
        
        cpShape* shape = cpSegmentShapeNew(_info->shareBody,
                                           PhysicsHelper::point2cpv(a),
                                           PhysicsHelper::point2cpv(b),
                                           PhysicsHelper::float2cpfloat(border));
        
        CC_BREAK_IF(shape == nullptr);
        
        _mass = PHYSICS_INFINITY;
        _angularDamping = PHYSICS_INFINITY;
        
        _info->add(shape);
        
        initEnd();
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeBox
PhysicsShapeBox* PhysicsShapeBox::create(Size size, PhysicsMaterial material/* = MaterialDefault*/, Point offset/* = Point(0, 0)*/)
{
    PhysicsShapeBox* shape = new PhysicsShapeBox();
    if (shape && shape->init(size, material, offset))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeBox::init(Size size, PhysicsMaterial material/* = MaterialDefault*/, Point offset /*= Point(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::BOX, material));
        
        cpShape* shape = cpBoxShapeNew(_info->shareBody, PhysicsHelper::float2cpfloat(size.width), PhysicsHelper::float2cpfloat(size.height));
        
        CC_BREAK_IF(shape == nullptr);
        
        _area = PhysicsHelper::cpfloat2float(cpAreaForPoly(4, ((cpPolyShape*)shape)->verts));
        _mass = _material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : _material.density * _area;
        _angularDamping = _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY : cpMomentForBox(_mass, PhysicsHelper::float2cpfloat(size.width), PhysicsHelper::float2cpfloat(size.height));
        
        _info->add(shape);
        
        initEnd();
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeCircle
PhysicsShapePolygon* PhysicsShapePolygon::create(Point* points, int count, PhysicsMaterial material/* = MaterialDefault*/, Point offset/* = Point(0, 0)*/)
{
    PhysicsShapePolygon* shape = new PhysicsShapePolygon();
    if (shape && shape->init(points, count, material, offset))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapePolygon::init(Point* points, int count, PhysicsMaterial material/* = MaterialDefault*/, Point offset /*= Point(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::POLYGEN, material));
        
        cpVect* vecs = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vecs, count);
        cpShape* shape = cpPolyShapeNew(_info->shareBody, count, vecs, PhysicsHelper::point2cpv(offset));
        CC_SAFE_DELETE(vecs);
        
        CC_BREAK_IF(shape == nullptr);
        
        _area = PhysicsHelper::cpfloat2float(cpAreaForPoly(((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts));
        _mass = _material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : _material.density * _area;
        _angularDamping = _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY : cpMomentForPoly(_mass, ((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts, PhysicsHelper::point2cpv(offset));
        
        _info->add(shape);
        
        initEnd();
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeEdgeBox
PhysicsShapeEdgeBox* PhysicsShapeEdgeBox::create(Size size, PhysicsMaterial material/* = MaterialDefault*/, float border/* = 1*/, Point offset/* = Point(0, 0)*/)
{
    PhysicsShapeEdgeBox* shape = new PhysicsShapeEdgeBox();
    if (shape && shape->init(size, material, border, offset))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgeBox::init(Size size, PhysicsMaterial material/* = MaterialDefault*/, float border/* = 1*/, Point offset/*= Point(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGEBOX, material));
        
        cpVect vec[4] = {};
        vec[0] = PhysicsHelper::point2cpv(Point(-size.width/2+offset.x, -size.height/2+offset.y));
        vec[1] = PhysicsHelper::point2cpv(Point(+size.width/2+offset.x, -size.height/2+offset.y));
        vec[2] = PhysicsHelper::point2cpv(Point(+size.width/2+offset.x, +size.height/2+offset.y));
        vec[3] = PhysicsHelper::point2cpv(Point(-size.width/2+offset.x, +size.height/2+offset.y));
        
        int i = 0;
        for (; i < 4; ++i)
        {
            cpShape* shape = cpSegmentShapeNew(_info->shareBody, vec[i], vec[(i+1)%4],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
            _info->add(shape);
        }
        CC_BREAK_IF(i < 4);
        
        _mass = PHYSICS_INFINITY;
        _angularDamping = PHYSICS_INFINITY;
        
        initEnd();
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeEdgeBox
PhysicsShapeEdgePolygon* PhysicsShapeEdgePolygon::create(Point* points, int count, PhysicsMaterial material/* = MaterialDefault*/, float border/* = 1*/)
{
    PhysicsShapeEdgePolygon* shape = new PhysicsShapeEdgePolygon();
    if (shape && shape->init(points, count, material, border))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgePolygon::init(Point* points, int count, PhysicsMaterial material/* = MaterialDefault*/, float border/* = 1*/)
{
    cpVect* vec = nullptr;
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGEPOLYGEN, material));
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        
        int i = 0;
        for (; i < count; ++i)
        {
            cpShape* shape = cpSegmentShapeNew(_info->shareBody, vec[i], vec[(i+1)%count],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
			cpShapeSetElasticity(shape, 1.0f);
			cpShapeSetFriction(shape, 1.0f);
            _info->add(shape);
        }
        CC_SAFE_DELETE(vec);
        
        CC_BREAK_IF(i < count);
        
        _mass = PHYSICS_INFINITY;
        _angularDamping = PHYSICS_INFINITY;
        
        initEnd();
        
        return true;
    } while (false);
    
    if (vec != nullptr) delete[] vec;
    
    return false;
}

// PhysicsShapeEdgeChain
PhysicsShapeEdgeChain* PhysicsShapeEdgeChain::create(Point* points, int count, PhysicsMaterial material/* = MaterialDefault*/, float border/* = 1*/)
{
    PhysicsShapeEdgeChain* shape = new PhysicsShapeEdgeChain();
    if (shape && shape->init(points, count, material, border))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgeChain::init(Point* points, int count, PhysicsMaterial material/* = MaterialDefault*/, float border/* = 1*/)
{
    cpVect* vec = nullptr;
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGECHAIN, material));
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        
        int i = 0;
        for (; i < count - 1; ++i)
        {
            cpShape* shape = cpSegmentShapeNew(_info->shareBody, vec[i], vec[i+1],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
			cpShapeSetElasticity(shape, 1.0f);
			cpShapeSetFriction(shape, 1.0f);
            _info->add(shape);
        }
        if (vec != nullptr) delete[] vec;
        CC_BREAK_IF(i < count);
        
        _mass = PHYSICS_INFINITY;
        _angularDamping = PHYSICS_INFINITY;
        
        initEnd();
        
        return true;
    } while (false);
    
    if (vec != nullptr) delete[] vec;
    
    return false;
}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

#endif

NS_CC_END

#endif // CC_USE_PHYSICS