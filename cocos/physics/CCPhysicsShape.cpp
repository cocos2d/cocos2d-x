/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
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

#include "physics/CCPhysicsShape.h"
#if CC_USE_PHYSICS

#include <climits>

#include "chipmunk.h"

#include "physics/CCPhysicsBody.h"
#include "physics/CCPhysicsWorld.h"

#include "chipmunk/CCPhysicsBodyInfo_chipmunk.h"
#include "chipmunk/CCPhysicsShapeInfo_chipmunk.h"
#include "chipmunk/CCPhysicsHelper_chipmunk.h"

NS_CC_BEGIN
extern const float PHYSICS_INFINITY;

PhysicsShape::PhysicsShape()
: _body(nullptr)
, _info(nullptr)
, _type(Type::UNKNOWN)
, _area(0)
, _mass(0)
, _moment(0)
, _tag(0)
, _categoryBitmask(UINT_MAX)
, _collisionBitmask(UINT_MAX)
, _contactTestBitmask(0)
, _group(0)
{
    
}

PhysicsShape::~PhysicsShape()
{
    CC_SAFE_DELETE(_info);
}

bool PhysicsShape::init(Type type)
{
    _info = new PhysicsShapeInfo(this);
    if (_info == nullptr) return false;
    
    _type = type;
    
    return true;
}

void PhysicsShape::setMass(float mass)
{
    if (mass < 0)
    {
        return;
    }
    
    if (_body)
    {
        _body->addMass(-_mass);
        _body->addMass(mass);
    };
    
    _mass = mass;
}

void PhysicsShape::setMoment(float moment)
{
    if (moment < 0)
    {
        return;
    }
    
    if (_body)
    {
        _body->addMoment(-_moment);
        _body->addMoment(moment);
    };
    
    _moment = moment;
}

void PhysicsShape::setMaterial(const PhysicsMaterial& material)
{
    setDensity(material.density);
    setRestitution(material.restitution);
    setFriction(material.friction);
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

void PhysicsShape::setDensity(float density)
{
    if (density < 0)
    {
        return;
    }
    
    _material.density = density;
    
    if (_material.density == PHYSICS_INFINITY)
    {
        setMass(PHYSICS_INFINITY);
    }else if (_area > 0)
    {
        setMass(PhysicsHelper::float2cpfloat(_material.density * _area));
    }
}

void PhysicsShape::setRestitution(float restitution)
{
    _material.restitution = restitution;
    
    for (cpShape* shape : _info->getShapes())
    {
        cpShapeSetElasticity(shape, PhysicsHelper::float2cpfloat(restitution));
    }
}

void PhysicsShape::setFriction(float friction)
{
    _material.friction = friction;
    
    for (cpShape* shape : _info->getShapes())
    {
        cpShapeSetFriction(shape, PhysicsHelper::float2cpfloat(friction));
    }
}


void PhysicsShape::recenterPoints(Vector2* points, int count, const Vector2& center)
{
    cpVect* cpvs = new cpVect[count];
    cpRecenterPoly(count, PhysicsHelper::points2cpvs(points, cpvs, count));
    PhysicsHelper::cpvs2points(cpvs, points, count);
    delete[] cpvs;
    
    if (center != Vector2::ZERO)
    {
        for (int i = 0; i < count; ++i)
        {
            points[i] += center;
        }
    }
}

Vector2 PhysicsShape::getPolyonCenter(const Vector2* points, int count)
{
    cpVect* cpvs = new cpVect[count];
    cpVect center = cpCentroidForPoly(count, PhysicsHelper::points2cpvs(points, cpvs, count));
    delete[] cpvs;
    
    return PhysicsHelper::cpv2point(center);
}

void PhysicsShape::setBody(PhysicsBody *body)
{
    // already added
    if (body != nullptr && _body == body)
    {
        return;
    }
    
    if (_body != nullptr)
    {
        _body->removeShape(this);
    }
    
    if (body == nullptr)
    {
        _info->setBody(nullptr);
        _body = nullptr;
    }else
    {
        _info->setBody(body->_info->getBody());
        _body = body;
    }
}

// PhysicsShapeCircle
PhysicsShapeCircle* PhysicsShapeCircle::create(float radius, const PhysicsMaterial& material/* = MaterialDefault*/, const Vector2& offset/* = Vector2(0, 0)*/)
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

bool PhysicsShapeCircle::init(float radius, const PhysicsMaterial& material/* = MaterialDefault*/, const Vector2& offset /*= Vector2(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::CIRCLE));
        
        cpShape* shape = cpCircleShapeNew(_info->getSharedBody(), radius, PhysicsHelper::point2cpv(offset));
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        
        _area = calculateArea();
        _mass = material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : material.density * _area;
        _moment = calculateDefaultMoment();
        
        setMaterial(material);
        return true;
    } while (false);
    
    return false;
}

float PhysicsShapeCircle::calculateArea(float radius)
{
    return PhysicsHelper::cpfloat2float(cpAreaForCircle(0, radius));
}

float PhysicsShapeCircle::calculateMoment(float mass, float radius, const Vector2& offset)
{
    return mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForCircle(PhysicsHelper::float2cpfloat(mass),
                                                     0,
                                                     PhysicsHelper::float2cpfloat(radius),
                                                     PhysicsHelper::point2cpv(offset)));
}

float PhysicsShapeCircle::calculateArea()
{
    return PhysicsHelper::cpfloat2float(cpAreaForCircle(0, cpCircleShapeGetRadius(_info->getShapes().front())));
}

float PhysicsShapeCircle::calculateDefaultMoment()
{
    cpShape* shape = _info->getShapes().front();
    
    return _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForCircle(PhysicsHelper::float2cpfloat(_mass),
                                                     0,
                                                     cpCircleShapeGetRadius(shape),
                                                     cpCircleShapeGetOffset(shape)));
}

float PhysicsShapeCircle::getRadius() const
{
    return PhysicsHelper::cpfloat2float(cpCircleShapeGetRadius(_info->getShapes().front()));
}

Vector2 PhysicsShapeCircle::getOffset()
{
    return PhysicsHelper::cpv2point(cpCircleShapeGetOffset(_info->getShapes().front()));
}

// PhysicsShapeEdgeSegment
PhysicsShapeEdgeSegment* PhysicsShapeEdgeSegment::create(const Vector2& a, const Vector2& b, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
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

bool PhysicsShapeEdgeSegment::init(const Vector2& a, const Vector2& b, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGESEGMENT));
        
        cpShape* shape = cpSegmentShapeNew(_info->getSharedBody(),
                                           PhysicsHelper::point2cpv(a),
                                           PhysicsHelper::point2cpv(b),
                                           PhysicsHelper::float2cpfloat(border));
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        
        _mass = PHYSICS_INFINITY;
        _moment = PHYSICS_INFINITY;
        _center = a.getMidpoint(b);
        
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

Vector2 PhysicsShapeEdgeSegment::getPointA() const
{
    return PhysicsHelper::cpv2point(((cpSegmentShape*)(_info->getShapes().front()))->ta);
}

Vector2 PhysicsShapeEdgeSegment::getPointB() const
{
    return PhysicsHelper::cpv2point(((cpSegmentShape*)(_info->getShapes().front()))->tb);
}

Vector2 PhysicsShapeEdgeSegment::getCenter()
{
    return _center;
}

// PhysicsShapeBox
PhysicsShapeBox* PhysicsShapeBox::create(const Size& size, const PhysicsMaterial& material/* = MaterialDefault*/, const Vector2& offset/* = Vector2(0, 0)*/)
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

bool PhysicsShapeBox::init(const Size& size, const PhysicsMaterial& material/* = MaterialDefault*/, const Vector2& offset /*= Vector2(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::BOX));
        
        cpVect wh = PhysicsHelper::size2cpv(size);
        cpVect vec[4] =
        {
            {-wh.x/2.0f, -wh.y/2.0f}, {-wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, -wh.y/2.0f}
        };
        
        cpShape* shape = cpPolyShapeNew(_info->getSharedBody(), 4, vec, PhysicsHelper::point2cpv(offset));
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        
        _offset = offset;
        _area = calculateArea();
        _mass = material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : material.density * _area;
        _moment = calculateDefaultMoment();
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsShapeBox::calculateArea(const Size& size)
{
    cpVect wh = PhysicsHelper::size2cpv(size);
    cpVect vec[4] =
    {
        {-wh.x/2.0f, -wh.y/2.0f}, {-wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, -wh.y/2.0f}
    };
    return PhysicsHelper::cpfloat2float(cpAreaForPoly(4, vec));
}

float PhysicsShapeBox::calculateMoment(float mass, const Size& size, const Vector2& offset)
{
    cpVect wh = PhysicsHelper::size2cpv(size);
    cpVect vec[4] =
    {
        {-wh.x/2.0f, -wh.y/2.0f}, {-wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, -wh.y/2.0f}
    };
    
    return mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForPoly(PhysicsHelper::float2cpfloat(mass),
                                                   4,
                                                   vec,
                                                   PhysicsHelper::point2cpv(offset)));
}

float PhysicsShapeBox::calculateArea()
{
    cpShape* shape = _info->getShapes().front();
    return PhysicsHelper::cpfloat2float(cpAreaForPoly(((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts));
}

float PhysicsShapeBox::calculateDefaultMoment()
{
    cpShape* shape = _info->getShapes().front();
    return _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForPoly(_mass, ((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts, cpvzero));
}

void PhysicsShapeBox::getPoints(Vector2* points) const
{
    cpShape* shape = _info->getShapes().front();
    PhysicsHelper::cpvs2points(((cpPolyShape*)shape)->verts, points, ((cpPolyShape*)shape)->numVerts);
}

Size PhysicsShapeBox::getSize() const
{
    cpShape* shape = _info->getShapes().front();
    return PhysicsHelper::cpv2size(cpv(cpvdist(cpPolyShapeGetVert(shape, 1), cpPolyShapeGetVert(shape, 2)),
                                       cpvdist(cpPolyShapeGetVert(shape, 0), cpPolyShapeGetVert(shape, 1))));
}

// PhysicsShapePolygon
PhysicsShapePolygon* PhysicsShapePolygon::create(const Vector2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, const Vector2& offset/* = Vector2(0, 0)*/)
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

bool PhysicsShapePolygon::init(const Vector2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, const Vector2& offset/* = Vector2(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::POLYGEN));
        
        cpVect* vecs = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vecs, count);
        cpShape* shape = cpPolyShapeNew(_info->getSharedBody(), count, vecs, PhysicsHelper::point2cpv(offset));
        CC_SAFE_DELETE_ARRAY(vecs);
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        
        _area = calculateArea();
        _mass = material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : material.density * _area;
        _moment = calculateDefaultMoment();
        _center = PhysicsHelper::cpv2point(cpCentroidForPoly(((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts));
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsShapePolygon::calculateArea(const Vector2* points, int count)
{
    cpVect* vecs = new cpVect[count];
    PhysicsHelper::points2cpvs(points, vecs, count);
    float area = PhysicsHelper::cpfloat2float(cpAreaForPoly(count, vecs));
    CC_SAFE_DELETE_ARRAY(vecs);
    
    return area;
}

float PhysicsShapePolygon::calculateMoment(float mass, const Vector2* points, int count, const Vector2& offset)
{
    cpVect* vecs = new cpVect[count];
    PhysicsHelper::points2cpvs(points, vecs, count);
    float moment = mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForPoly(mass, count, vecs, PhysicsHelper::point2cpv(offset)));
    CC_SAFE_DELETE_ARRAY(vecs);
    
    return moment;
}

float PhysicsShapePolygon::calculateArea()
{
    cpShape* shape = _info->getShapes().front();
    return PhysicsHelper::cpfloat2float(cpAreaForPoly(((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts));
}

float PhysicsShapePolygon::calculateDefaultMoment()
{
    cpShape* shape = _info->getShapes().front();
    return _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForPoly(_mass, ((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts, cpvzero));
}

Vector2 PhysicsShapePolygon::getPoint(int i) const
{
    return PhysicsHelper::cpv2point(cpPolyShapeGetVert(_info->getShapes().front(), i));
}

void PhysicsShapePolygon::getPoints(Vector2* outPoints) const
{
    cpShape* shape = _info->getShapes().front();
    PhysicsHelper::cpvs2points(((cpPolyShape*)shape)->verts, outPoints, ((cpPolyShape*)shape)->numVerts);
}

int PhysicsShapePolygon::getPointsCount() const
{
    return ((cpPolyShape*)_info->getShapes().front())->numVerts;
}

Vector2 PhysicsShapePolygon::getCenter()
{
    return _center;
}

// PhysicsShapeEdgeBox
PhysicsShapeEdgeBox* PhysicsShapeEdgeBox::create(const Size& size, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/, const Vector2& offset/* = Vector2(0, 0)*/)
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

bool PhysicsShapeEdgeBox::init(const Size& size, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/, const Vector2& offset/*= Vector2(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGEBOX));
        
        cpVect vec[4] = {};
        vec[0] = PhysicsHelper::point2cpv(Vector2(-size.width/2+offset.x, -size.height/2+offset.y));
        vec[1] = PhysicsHelper::point2cpv(Vector2(+size.width/2+offset.x, -size.height/2+offset.y));
        vec[2] = PhysicsHelper::point2cpv(Vector2(+size.width/2+offset.x, +size.height/2+offset.y));
        vec[3] = PhysicsHelper::point2cpv(Vector2(-size.width/2+offset.x, +size.height/2+offset.y));
        
        int i = 0;
        for (; i < 4; ++i)
        {
            cpShape* shape = cpSegmentShapeNew(_info->getSharedBody(), vec[i], vec[(i+1)%4],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
            _info->add(shape);
        }
        CC_BREAK_IF(i < 4);
        
        _offset = offset;
        _mass = PHYSICS_INFINITY;
        _moment = PHYSICS_INFINITY;
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsShapeEdgeBox::getPoints(cocos2d::Vector2 *outPoints) const
{
    int i = 0;
    for(auto shape : _info->getShapes())
    {
        outPoints[i++] = PhysicsHelper::cpv2point(((cpSegmentShape*)shape)->a);
    }
}

// PhysicsShapeEdgeBox
PhysicsShapeEdgePolygon* PhysicsShapeEdgePolygon::create(const Vector2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
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

bool PhysicsShapeEdgePolygon::init(const Vector2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
{
    cpVect* vec = nullptr;
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGEPOLYGEN));
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        _center = PhysicsHelper::cpv2point(cpCentroidForPoly(count, vec));
        
        int i = 0;
        for (; i < count; ++i)
        {
            cpShape* shape = cpSegmentShapeNew(_info->getSharedBody(), vec[i], vec[(i+1)%count],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
			cpShapeSetElasticity(shape, 1.0f);
			cpShapeSetFriction(shape, 1.0f);
            _info->add(shape);
        }
        CC_SAFE_DELETE_ARRAY(vec);
        
        CC_BREAK_IF(i < count);
        
        _mass = PHYSICS_INFINITY;
        _moment = PHYSICS_INFINITY;
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    CC_SAFE_DELETE_ARRAY(vec);
    
    return false;
}

Vector2 PhysicsShapeEdgePolygon::getCenter()
{
    return _center;
}

void PhysicsShapeEdgePolygon::getPoints(cocos2d::Vector2 *outPoints) const
{
    int i = 0;
    for(auto shape : _info->getShapes())
    {
        outPoints[i++] = PhysicsHelper::cpv2point(((cpSegmentShape*)shape)->a);
    }
}

int PhysicsShapeEdgePolygon::getPointsCount() const
{
    return static_cast<int>(_info->getShapes().size() + 1);
}

// PhysicsShapeEdgeChain
PhysicsShapeEdgeChain* PhysicsShapeEdgeChain::create(const Vector2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
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

bool PhysicsShapeEdgeChain::init(const Vector2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
{
    cpVect* vec = nullptr;
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGECHAIN));
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        _center = PhysicsHelper::cpv2point(cpCentroidForPoly(count, vec));
        
        int i = 0;
        for (; i < count - 1; ++i)
        {
            cpShape* shape = cpSegmentShapeNew(_info->getSharedBody(), vec[i], vec[i+1],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
			cpShapeSetElasticity(shape, 1.0f);
			cpShapeSetFriction(shape, 1.0f);
            _info->add(shape);
        }
        CC_SAFE_DELETE_ARRAY(vec);
        CC_BREAK_IF(i < count - 1);
        
        _mass = PHYSICS_INFINITY;
        _moment = PHYSICS_INFINITY;
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    CC_SAFE_DELETE_ARRAY(vec);
    
    return false;
}

Vector2 PhysicsShapeEdgeChain::getCenter()
{
    return _center;
}

void PhysicsShapeEdgeChain::getPoints(Vector2* outPoints) const
{
    int i = 0;
    for(auto shape : _info->getShapes())
    {
        outPoints[i++] = PhysicsHelper::cpv2point(((cpSegmentShape*)shape)->a);
    }
    
    outPoints[i++] = PhysicsHelper::cpv2point(((cpSegmentShape*)_info->getShapes().back())->a);
}

int PhysicsShapeEdgeChain::getPointsCount() const
{
    return static_cast<int>(_info->getShapes().size() + 1);
}

void PhysicsShape::setGroup(int group)
{
    if (group < 0)
    {
        for (auto shape : _info->getShapes())
        {
            cpShapeSetGroup(shape, (cpGroup)group);
        }
    }
    
    _group = group;
}

bool PhysicsShape::containsPoint(const Vector2& point) const
{
    for (auto shape : _info->getShapes())
    {
        if (cpShapePointQuery(shape, PhysicsHelper::point2cpv(point)))
        {
            return true;
        }
    }
    
    return false;
}

NS_CC_END

#endif // CC_USE_PHYSICS
