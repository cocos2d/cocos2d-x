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
#include <unordered_map>

#include "chipmunk.h"
#include "chipmunk_unsafe.h"

#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"
#include "CCPhysicsHelper.h"

NS_CC_BEGIN
extern const float PHYSICS_INFINITY;
std::unordered_map<cpShape*, PhysicsShape*> s_physicsShapeMap;
static cpBody* s_sharedBody = nullptr;

PhysicsShape::PhysicsShape()
: _body(nullptr)
, _type(Type::UNKNOWN)
, _area(0.0f)
, _mass(0.0f)
, _moment(0.0f)
, _sensor(false)
, _scaleX(1.0f)
, _scaleY(1.0f)
, _newScaleX(1.0f)
, _newScaleY(1.0f)
, _tag(0)
, _categoryBitmask(UINT_MAX)
, _collisionBitmask(UINT_MAX)
, _contactTestBitmask(0)
, _group(0)
{
    if (s_sharedBody == nullptr)
    {
        s_sharedBody = cpBodyNewStatic();
    }
}

PhysicsShape::~PhysicsShape()
{
    for (auto shape : _cpShapes)
    {
        s_physicsShapeMap.erase(shape);

        cpShapeFree(shape);
    }
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

void PhysicsShape::setScale(float scaleX, float scaleY)
{
    if (_scaleX != scaleX || _scaleY != scaleY)
    {
        if (_type == Type::CIRCLE && scaleX != scaleY)
        {
            CCLOG("PhysicsShapeCircle WARNING: CANNOT support setScale with different x and y");
            return;
        }
        _newScaleX = scaleX;
        _newScaleY = scaleY;
        updateScale();
    }
}

void PhysicsShape::updateScale()
{
    _scaleX = _newScaleX;
    _scaleY = _newScaleY;
}

void PhysicsShape::addShape(cpShape* shape)
{
    if (shape)
    {
        cpShapeSetGroup(shape, _group);
        _cpShapes.push_back(shape);
        s_physicsShapeMap.insert(std::pair<cpShape*, PhysicsShape*>(shape, this));
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
    
    for (cpShape* shape : _cpShapes)
    {
        cpShapeSetElasticity(shape, PhysicsHelper::float2cpfloat(restitution));
    }
}

void PhysicsShape::setFriction(float friction)
{
    _material.friction = friction;
    
    for (cpShape* shape : _cpShapes)
    {
        cpShapeSetFriction(shape, PhysicsHelper::float2cpfloat(friction));
    }
}

void PhysicsShape::setSensor(bool sensor)
{
    if (sensor != _sensor)
    {
        for (cpShape* shape : _cpShapes)
        {
            cpShapeSetSensor(shape, sensor);
        }
        _sensor = sensor;
    }
}

void PhysicsShape::recenterPoints(Vec2* points, int count, const Vec2& center)
{
    cpVect* cpvs = new cpVect[count];
    cpRecenterPoly(count, PhysicsHelper::points2cpvs(points, cpvs, count));
    PhysicsHelper::cpvs2points(cpvs, points, count);
    delete[] cpvs;
    
    if (center != Vec2::ZERO)
    {
        for (int i = 0; i < count; ++i)
        {
            points[i] += center;
        }
    }
}

Vec2 PhysicsShape::getPolyonCenter(const Vec2* points, int count)
{
    cpVect* cpvs = new cpVect[count];
    cpVect center = cpCentroidForPoly(count, PhysicsHelper::points2cpvs(points, cpvs, count));
    delete[] cpvs;
    
    return PhysicsHelper::cpv2point(center);
}

void PhysicsShape::setBody(PhysicsBody *body)
{
    // already added
    if (body && _body == body)
    {
        return;
    }
    
    if (_body)
    {
        _body->removeShape(this);
    }
    
    for (auto shape : _cpShapes)
    {
        cpShapeSetBody(shape, body == nullptr ? s_sharedBody : body->_cpBody);
    }
    _body = body;
}

// PhysicsShapeCircle
PhysicsShapeCircle* PhysicsShapeCircle::create(float radius, const PhysicsMaterial& material/* = MaterialDefault*/, const Vec2& offset/* = Vec2(0, 0)*/)
{
    PhysicsShapeCircle* shape = new (std::nothrow) PhysicsShapeCircle();
    if (shape && shape->init(radius, material, offset))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeCircle::init(float radius, const PhysicsMaterial& material/* = MaterialDefault*/, const Vec2& offset /*= Vec2(0, 0)*/)
{
    do
    {
        _type = Type::CIRCLE;
        
        auto shape = cpCircleShapeNew(s_sharedBody, radius, PhysicsHelper::point2cpv(offset));
        
        CC_BREAK_IF(shape == nullptr);
        
        addShape(shape);
        
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

float PhysicsShapeCircle::calculateMoment(float mass, float radius, const Vec2& offset)
{
    return mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForCircle(PhysicsHelper::float2cpfloat(mass),
                                                     0,
                                                     PhysicsHelper::float2cpfloat(radius),
                                                     PhysicsHelper::point2cpv(offset)));
}

float PhysicsShapeCircle::calculateArea()
{
    return PhysicsHelper::cpfloat2float(cpAreaForCircle(0, cpCircleShapeGetRadius(_cpShapes.front())));
}

float PhysicsShapeCircle::calculateDefaultMoment()
{
    auto shape = _cpShapes.front();
    
    return _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForCircle(PhysicsHelper::float2cpfloat(_mass),
                                                     0,
                                                     cpCircleShapeGetRadius(shape),
                                                     cpCircleShapeGetOffset(shape)));
}

float PhysicsShapeCircle::getRadius() const
{
    return PhysicsHelper::cpfloat2float(cpCircleShapeGetRadius(_cpShapes.front()));
}

Vec2 PhysicsShapeCircle::getOffset()
{
    return PhysicsHelper::cpv2point(cpCircleShapeGetOffset(_cpShapes.front()));
}

void PhysicsShapeCircle::updateScale()
{
    cpFloat factor = std::abs(PhysicsHelper::float2cpfloat(_newScaleX / _scaleX));

    cpShape* shape = _cpShapes.front();
    cpVect v = cpCircleShapeGetOffset(shape);
    v = cpvmult(v, PhysicsHelper::float2cpfloat(factor));
    ((cpCircleShape*)shape)->c = v;

    cpCircleShapeSetRadius(shape, cpCircleShapeGetRadius(shape) * factor);

    PhysicsShape::updateScale();
}

// PhysicsShapeEdgeSegment
PhysicsShapeEdgeSegment* PhysicsShapeEdgeSegment::create(const Vec2& a, const Vec2& b, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
{
    PhysicsShapeEdgeSegment* shape = new (std::nothrow) PhysicsShapeEdgeSegment();
    if (shape && shape->init(a, b, material, border))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgeSegment::init(const Vec2& a, const Vec2& b, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
{
    do
    {
        _type = Type::EDGESEGMENT;
        
        auto shape = cpSegmentShapeNew(s_sharedBody,
                                           PhysicsHelper::point2cpv(a),
                                           PhysicsHelper::point2cpv(b),
                                           PhysicsHelper::float2cpfloat(border));
        
        CC_BREAK_IF(shape == nullptr);
        
        addShape(shape);
        
        _mass = PHYSICS_INFINITY;
        _moment = PHYSICS_INFINITY;
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

Vec2 PhysicsShapeEdgeSegment::getPointA() const
{
    return PhysicsHelper::cpv2point(((cpSegmentShape*)(_cpShapes.front()))->ta);
}

Vec2 PhysicsShapeEdgeSegment::getPointB() const
{
    return PhysicsHelper::cpv2point(((cpSegmentShape*)(_cpShapes.front()))->tb);
}

Vec2 PhysicsShapeEdgeSegment::getCenter()
{
    auto a = PhysicsHelper::cpv2point(cpSegmentShapeGetA(_cpShapes.front()));
    auto b = PhysicsHelper::cpv2point(cpSegmentShapeGetB(_cpShapes.front()));
    return ( a + b ) / 2;
}

void PhysicsShapeEdgeSegment::updateScale()
{
    cpFloat factorX = PhysicsHelper::float2cpfloat(_newScaleX / _scaleX);
    cpFloat factorY = PhysicsHelper::float2cpfloat(_newScaleY / _scaleY);

    cpShape* shape = _cpShapes.front();
    cpVect a = cpSegmentShapeGetA(shape);
    a.x *= factorX;
    a.y *= factorY;
    cpVect b = cpSegmentShapeGetB(shape);
    b.x *= factorX;
    b.y *= factorY;
    cpSegmentShapeSetEndpoints(shape, a, b);

    PhysicsShape::updateScale();
}

// PhysicsShapeBox
PhysicsShapeBox* PhysicsShapeBox::create(const Size& size, const PhysicsMaterial& material/* = MaterialDefault*/, const Vec2& offset/* = Vec2(0, 0)*/)
{
    PhysicsShapeBox* shape = new (std::nothrow) PhysicsShapeBox();
    if (shape && shape->init(size, material, offset))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeBox::init(const Size& size, const PhysicsMaterial& material/* = MaterialDefault*/, const Vec2& offset /*= Vec2(0, 0)*/)
{
    do
    {
        _type = Type::BOX;
        
        auto wh = PhysicsHelper::size2cpv(size);
        cpVect vec[4] =
        {
            {-wh.x/2.0f, -wh.y/2.0f}, {-wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, -wh.y/2.0f}
        };
        
        auto shape = cpPolyShapeNew(s_sharedBody, 4, vec, PhysicsHelper::point2cpv(offset));
        
        CC_BREAK_IF(shape == nullptr);
        
        addShape(shape);
        
        _area = calculateArea();
        _mass = material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : material.density * _area;
        _moment = calculateDefaultMoment();
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

Size PhysicsShapeBox::getSize() const
{
    cpShape* shape = _cpShapes.front();
    return PhysicsHelper::cpv2size(cpv(cpvdist(cpPolyShapeGetVert(shape, 1), cpPolyShapeGetVert(shape, 2)),
                                       cpvdist(cpPolyShapeGetVert(shape, 0), cpPolyShapeGetVert(shape, 1))));
}

// PhysicsShapePolygon
PhysicsShapePolygon* PhysicsShapePolygon::create(const Vec2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, const Vec2& offset/* = Vec2(0, 0)*/)
{
    PhysicsShapePolygon* shape = new (std::nothrow) PhysicsShapePolygon();
    if (shape && shape->init(points, count, material, offset))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapePolygon::init(const Vec2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, const Vec2& offset/* = Vec2(0, 0)*/)
{
    do
    {
        _type = Type::POLYGEN;
        
        auto vecs = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vecs, count);
        auto shape = cpPolyShapeNew(s_sharedBody, count, vecs, PhysicsHelper::point2cpv(offset));
        CC_SAFE_DELETE_ARRAY(vecs);
        
        CC_BREAK_IF(shape == nullptr);
        
        addShape(shape);
        
        _area = calculateArea();
        _mass = material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : material.density * _area;
        _moment = calculateDefaultMoment();
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsShapePolygon::calculateArea(const Vec2* points, int count)
{
    cpVect* vecs = new cpVect[count];
    PhysicsHelper::points2cpvs(points, vecs, count);
    float area = PhysicsHelper::cpfloat2float(cpAreaForPoly(count, vecs));
    CC_SAFE_DELETE_ARRAY(vecs);
    
    return area;
}

float PhysicsShapePolygon::calculateMoment(float mass, const Vec2* points, int count, const Vec2& offset)
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
    auto shape = _cpShapes.front();
    return PhysicsHelper::cpfloat2float(cpAreaForPoly(((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts));
}

float PhysicsShapePolygon::calculateDefaultMoment()
{
    auto shape = _cpShapes.front();
    return _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForPoly(_mass, ((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts, cpvzero));
}

Vec2 PhysicsShapePolygon::getPoint(int i) const
{
    return PhysicsHelper::cpv2point(cpPolyShapeGetVert(_cpShapes.front(), i));
}

void PhysicsShapePolygon::getPoints(Vec2* outPoints) const
{
    auto shape = _cpShapes.front();
    PhysicsHelper::cpvs2points(((cpPolyShape*)shape)->verts, outPoints, ((cpPolyShape*)shape)->numVerts);
}

int PhysicsShapePolygon::getPointsCount() const
{
    return ((cpPolyShape*)_cpShapes.front())->numVerts;
}

Vec2 PhysicsShapePolygon::getCenter()
{
    return PhysicsHelper::cpv2point(cpCentroidForPoly(((cpPolyShape*)_cpShapes.front())->numVerts, ((cpPolyShape*)_cpShapes.front())->verts));
}

void PhysicsShapePolygon::updateScale()
{
    cpFloat factorX = PhysicsHelper::float2cpfloat(_newScaleX / _scaleX);
    cpFloat factorY = PhysicsHelper::float2cpfloat(_newScaleY / _scaleY);

    auto shape = _cpShapes.front();
    int count = cpPolyShapeGetNumVerts(shape);
    cpVect* vects = ((cpPolyShape*)shape)->verts;
    cpSplittingPlane* planes = ((cpPolyShape*)shape)->planes;

    for (int i = 0; i < count; ++i)
    {
        vects[i].x *= factorX;
        vects[i].y *= factorY;
    }

    // convert hole to clockwise
    if (factorX * factorY < 0)
    {
        for (int i = 0; i < count / 2; ++i)
        {
            cpVect v = vects[i];
            vects[i] = vects[count - i - 1];
            vects[count - i - 1] = v;
        }
    }

    for (int i = 0; i < count; ++i)
    {
        cpVect n = cpvnormalize(cpvperp(cpvsub(vects[i], vects[(i + 1) % count])));

        planes[i].n = n;
        planes[i].d = cpvdot(n, vects[i]);
    }
    
    PhysicsShape::updateScale();
}

// PhysicsShapeEdgeBox
PhysicsShapeEdgeBox* PhysicsShapeEdgeBox::create(const Size& size, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/, const Vec2& offset/* = Vec2(0, 0)*/)
{
    PhysicsShapeEdgeBox* shape = new (std::nothrow) PhysicsShapeEdgeBox();
    if (shape && shape->init(size, material, border, offset))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgeBox::init(const Size& size, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/, const Vec2& offset/*= Vec2(0, 0)*/)
{
    do
    {
        _type = Type::EDGEBOX;
        
        cpVect vec[4] = {};
        vec[0] = PhysicsHelper::point2cpv(Vec2(-size.width/2+offset.x, -size.height/2+offset.y));
        vec[1] = PhysicsHelper::point2cpv(Vec2(+size.width/2+offset.x, -size.height/2+offset.y));
        vec[2] = PhysicsHelper::point2cpv(Vec2(+size.width/2+offset.x, +size.height/2+offset.y));
        vec[3] = PhysicsHelper::point2cpv(Vec2(-size.width/2+offset.x, +size.height/2+offset.y));
        
        int i = 0;
        for (; i < 4; ++i)
        {
            auto shape = cpSegmentShapeNew(s_sharedBody, vec[i], vec[(i + 1) % 4],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
            addShape(shape);
        }
        CC_BREAK_IF(i < 4);
        
        _mass = PHYSICS_INFINITY;
        _moment = PHYSICS_INFINITY;
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

// PhysicsShapeEdgeBox
PhysicsShapeEdgePolygon* PhysicsShapeEdgePolygon::create(const Vec2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
{
    PhysicsShapeEdgePolygon* shape = new (std::nothrow) PhysicsShapeEdgePolygon();
    if (shape && shape->init(points, count, material, border))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

bool PhysicsShapeEdgePolygon::init(const Vec2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
{
    cpVect* vec = nullptr;
    do
    {
        _type = Type::EDGEPOLYGEN;
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        
        int i = 0;
        for (; i < count; ++i)
        {
            auto shape = cpSegmentShapeNew(s_sharedBody, vec[i], vec[(i + 1) % count],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
            cpShapeSetElasticity(shape, 1.0f);
            cpShapeSetFriction(shape, 1.0f);
            addShape(shape);
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

Vec2 PhysicsShapeEdgePolygon::getCenter()
{
    int count = (int)_cpShapes.size();
    cpVect* points = new cpVect[count];
    int i = 0;
    for(auto shape : _cpShapes)
    {
        points[i++] = ((cpSegmentShape*)shape)->a;
    }
    
    Vec2 center = PhysicsHelper::cpv2point(cpCentroidForPoly(count, points));
    delete[] points;
    
    return center;
}

void PhysicsShapeEdgePolygon::getPoints(cocos2d::Vec2 *outPoints) const
{
    int i = 0;
    for(auto shape : _cpShapes)
    {
        outPoints[i++] = PhysicsHelper::cpv2point(((cpSegmentShape*)shape)->a);
    }
}

int PhysicsShapeEdgePolygon::getPointsCount() const
{
    return static_cast<int>(_cpShapes.size());
}

// PhysicsShapeEdgeChain
PhysicsShapeEdgeChain* PhysicsShapeEdgeChain::create(const Vec2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
{
    PhysicsShapeEdgeChain* shape = new (std::nothrow) PhysicsShapeEdgeChain();
    if (shape && shape->init(points, count, material, border))
    {
        shape->autorelease();
        return shape;
    }
    
    CC_SAFE_DELETE(shape);
    return nullptr;
}

void PhysicsShapeEdgePolygon::updateScale()
{
    cpFloat factorX = PhysicsHelper::float2cpfloat(_newScaleX / _scaleX);
    cpFloat factorY = PhysicsHelper::float2cpfloat(_newScaleY / _scaleY);

    for (auto shape : _cpShapes)
    {
        cpVect a = cpSegmentShapeGetA(shape);
        a.x *= factorX;
        a.y *= factorY;
        cpVect b = cpSegmentShapeGetB(shape);
        b.x *= factorX;
        b.y *= factorY;
        cpSegmentShapeSetEndpoints(shape, a, b);
    }
    
    PhysicsShape::updateScale();
}

bool PhysicsShapeEdgeChain::init(const Vec2* points, int count, const PhysicsMaterial& material/* = MaterialDefault*/, float border/* = 1*/)
{
    cpVect* vec = nullptr;
    do
    {
        _type = Type::EDGECHAIN;
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        
        int i = 0;
        for (; i < count - 1; ++i)
        {
            auto shape = cpSegmentShapeNew(s_sharedBody, vec[i], vec[i + 1],
                                               PhysicsHelper::float2cpfloat(border));
            CC_BREAK_IF(shape == nullptr);
            cpShapeSetElasticity(shape, 1.0f);
            cpShapeSetFriction(shape, 1.0f);
            addShape(shape);
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

Vec2 PhysicsShapeEdgeChain::getCenter()
{
    int count = (int)_cpShapes.size() + 1;
    cpVect* points = new cpVect[count];
    int i = 0;
    for(auto shape : _cpShapes)
    {
        points[i++] = ((cpSegmentShape*)shape)->a;
    }
    
    points[i++] = ((cpSegmentShape*)_cpShapes.back())->b;
    
    Vec2 center = PhysicsHelper::cpv2point(cpCentroidForPoly(count, points));
    delete[] points;
    
    return center;
}

void PhysicsShapeEdgeChain::getPoints(Vec2* outPoints) const
{
    int i = 0;
    for(auto shape : _cpShapes)
    {
        outPoints[i++] = PhysicsHelper::cpv2point(((cpSegmentShape*)shape)->a);
    }
    
    outPoints[i++] = PhysicsHelper::cpv2point(((cpSegmentShape*)_cpShapes.back())->b);
}

int PhysicsShapeEdgeChain::getPointsCount() const
{
    return static_cast<int>(_cpShapes.size() + 1);
}

void PhysicsShapeEdgeChain::updateScale()
{
    cpFloat factorX = PhysicsHelper::float2cpfloat(_newScaleX / _scaleX);
    cpFloat factorY = PhysicsHelper::float2cpfloat(_newScaleY / _scaleY);

    for (auto shape : _cpShapes)
    {
        cpVect a = cpSegmentShapeGetA(shape);
        a.x *= factorX;
        a.y *= factorY;
        cpVect b = cpSegmentShapeGetB(shape);
        b.x *= factorX;
        b.y *= factorY;
        cpSegmentShapeSetEndpoints(shape, a, b);
    }
    
    PhysicsShape::updateScale();
}

void PhysicsShape::setGroup(int group)
{
    if (group < 0)
    {
        for (auto shape : _cpShapes)
        {
            cpShapeSetGroup(shape, (cpGroup)group);
        }
    }
    
    _group = group;
}

bool PhysicsShape::containsPoint(const Vec2& point) const
{
    for (auto shape : _cpShapes)
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
