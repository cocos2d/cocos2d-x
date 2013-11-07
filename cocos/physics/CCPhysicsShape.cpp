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

#include "chipmunk/CCPhysicsBodyInfo_chipmunk.h"
#include "box2d/CCPhysicsBodyInfo_box2d.h"
#include "chipmunk/CCPhysicsShapeInfo_chipmunk.h"
#include "box2d/CCPhysicsShapeInfo_box2d.h"
#include "chipmunk/CCPhysicsHelper_chipmunk.h"

NS_CC_BEGIN

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

void PhysicsShape::setMaterial(PhysicsMaterial material)
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

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
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
    
    for (cpShape* shape : _info->shapes)
    {
        cpShapeSetElasticity(shape, PhysicsHelper::float2cpfloat(restitution));
    }
}

void PhysicsShape::setFriction(float friction)
{
    _material.friction = friction;
    
    for (cpShape* shape : _info->shapes)
    {
        cpShapeSetFriction(shape, PhysicsHelper::float2cpfloat(friction));
    }
}


Point* PhysicsShape::recenterPoints(Point* points, int count, Point center)
{
    cpVect* cpvs = new cpVect[count];
    cpRecenterPoly(count, PhysicsHelper::points2cpvs(points, cpvs, count));
    PhysicsHelper::cpvs2points(cpvs, points, count);
    delete[] cpvs;
    
    if (center != Point::ZERO)
    {
        for (int i = 0; i < count; ++i)
        {
            points[i] += center;
        }
    }
    
    return points;
}

Point PhysicsShape::getPolyonCenter(Point* points, int count)
{
    cpVect* cpvs = new cpVect[count];
    cpVect center = cpCentroidForPoly(count, PhysicsHelper::points2cpvs(points, cpvs, count));
    delete[] cpvs;
    
    return PhysicsHelper::cpv2point(center);
}

void PhysicsShape::setBody(PhysicsBody *body)
{
    // already added
    if (_body == body)
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
        //_info->setGroup(CP_NO_GROUP);
        _body = nullptr;
    }else
    {
        _info->setBody(body->_info->body);
        //_info->setGroup(body->_info->group);
        _body = body;
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
        CC_BREAK_IF(!PhysicsShape::init(Type::CIRCLE));
        
        cpShape* shape = cpCircleShapeNew(_info->shareBody, radius, PhysicsHelper::point2cpv(offset));
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        
        _area = calculateDefaultArea();
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

float PhysicsShapeCircle::calculateMoment(float mass, float radius, Point offset)
{
    return mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForCircle(PhysicsHelper::float2cpfloat(mass),
                                                     0,
                                                     PhysicsHelper::float2cpfloat(radius),
                                                     PhysicsHelper::point2cpv(offset)));
}

float PhysicsShapeCircle::calculateDefaultArea()
{
    return PhysicsHelper::cpfloat2float(cpAreaForCircle(0, cpCircleShapeGetRadius(_info->shapes.front())));
}

float PhysicsShapeCircle::calculateDefaultMoment()
{
    cpShape* shape = _info->shapes.front();
    
    return _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForCircle(PhysicsHelper::float2cpfloat(_mass),
                                                     0,
                                                     cpCircleShapeGetRadius(shape),
                                                     cpCircleShapeGetOffset(shape)));
}

float PhysicsShapeCircle::getRadius() const
{
    return PhysicsHelper::cpfloat2float(cpCircleShapeGetRadius(_info->shapes.front()));
}

Point PhysicsShapeCircle::getOffset()
{
    return PhysicsHelper::cpv2point(cpCircleShapeGetOffset(_info->shapes.front()));
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
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGESEGMENT));
        
        cpShape* shape = cpSegmentShapeNew(_info->shareBody,
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

Point PhysicsShapeEdgeSegment::getPointA() const
{
    return PhysicsHelper::cpv2point(((cpSegmentShape*)(_info->shapes.front()))->ta);
}

Point PhysicsShapeEdgeSegment::getPointB() const
{
    return PhysicsHelper::cpv2point(((cpSegmentShape*)(_info->shapes.front()))->tb);
}

Point PhysicsShapeEdgeSegment::getCenter()
{
    return _center;
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
        CC_BREAK_IF(!PhysicsShape::init(Type::BOX));
        
        cpVect wh = PhysicsHelper::size2cpv(size);
        cpVect vec[4] =
        {
            {-wh.x/2.0f, -wh.y/2.0f}, {-wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, -wh.y/2.0f}
        };
        
        cpShape* shape = cpPolyShapeNew(_info->shareBody, 4, vec, PhysicsHelper::point2cpv(offset));
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        
        _offset = offset;
        _area = calculateDefaultArea();
        _mass = material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : material.density * _area;
        _moment = calculateDefaultMoment();
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsShapeBox::calculateArea(Size size)
{
    cpVect wh = PhysicsHelper::size2cpv(size);
    cpVect vec[4] =
    {
        {-wh.x/2.0f, -wh.y/2.0f}, {-wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, wh.y/2.0f}, {wh.x/2.0f, -wh.y/2.0f}
    };
    return PhysicsHelper::cpfloat2float(cpAreaForPoly(4, vec));
}

float PhysicsShapeBox::calculateMoment(float mass, Size size, Point offset)
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

float PhysicsShapeBox::calculateDefaultArea()
{
    cpShape* shape = _info->shapes.front();
    return PhysicsHelper::cpfloat2float(cpAreaForPoly(((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts));
}

float PhysicsShapeBox::calculateDefaultMoment()
{
    cpShape* shape = _info->shapes.front();
    return _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForPoly(_mass, ((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts, cpvzero));
}

Point* PhysicsShapeBox::getPoints(Point* points) const
{
    cpShape* shape = _info->shapes.front();
    return PhysicsHelper::cpvs2points(((cpPolyShape*)shape)->verts, points, ((cpPolyShape*)shape)->numVerts);
    
    return points;
}

Size PhysicsShapeBox::getSize() const
{
    cpShape* shape = _info->shapes.front();
    return PhysicsHelper::cpv2size(cpv(cpvdist(cpPolyShapeGetVert(shape, 0), cpPolyShapeGetVert(shape, 1)),
                                       cpvdist(cpPolyShapeGetVert(shape, 1), cpPolyShapeGetVert(shape, 2))));
}

// PhysicsShapePolygon
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

bool PhysicsShapePolygon::init(Point* points, int count, PhysicsMaterial material/* = MaterialDefault*/, Point offset/* = Point(0, 0)*/)
{
    do
    {
        CC_BREAK_IF(!PhysicsShape::init(Type::POLYGEN));
        
        cpVect* vecs = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vecs, count);
        cpShape* shape = cpPolyShapeNew(_info->shareBody, count, vecs, PhysicsHelper::point2cpv(offset));
        CC_SAFE_DELETE(vecs);
        
        CC_BREAK_IF(shape == nullptr);
        
        _info->add(shape);
        
        _area = calculateDefaultArea();
        _mass = material.density == PHYSICS_INFINITY ? PHYSICS_INFINITY : material.density * _area;
        _moment = calculateDefaultMoment();
        _center = PhysicsHelper::cpv2point(cpCentroidForPoly(((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts));
        
        setMaterial(material);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsShapePolygon::calculateArea(Point* points, int count)
{
    cpVect* vecs = new cpVect[count];
    PhysicsHelper::points2cpvs(points, vecs, count);
    float area = PhysicsHelper::cpfloat2float(cpAreaForPoly(count, vecs));
    CC_SAFE_DELETE(vecs);
    
    return area;
}

float PhysicsShapePolygon::calculateMoment(float mass, Point* points, int count, Point offset)
{
    cpVect* vecs = new cpVect[count];
    PhysicsHelper::points2cpvs(points, vecs, count);
    float moment = mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForPoly(mass, count, vecs, PhysicsHelper::point2cpv(offset)));
    CC_SAFE_DELETE(vecs);
    
    return moment;
}

float PhysicsShapePolygon::calculateDefaultArea()
{
    cpShape* shape = _info->shapes.front();
    return PhysicsHelper::cpfloat2float(cpAreaForPoly(((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts));
}

float PhysicsShapePolygon::calculateDefaultMoment()
{
    cpShape* shape = _info->shapes.front();
    return _mass == PHYSICS_INFINITY ? PHYSICS_INFINITY
    : PhysicsHelper::cpfloat2float(cpMomentForPoly(_mass, ((cpPolyShape*)shape)->numVerts, ((cpPolyShape*)shape)->verts, cpvzero));
}

Point* PhysicsShapePolygon::getPoints(Point* points) const
{
    cpShape* shape = _info->shapes.front();
    return PhysicsHelper::cpvs2points(((cpPolyShape*)shape)->verts, points, ((cpPolyShape*)shape)->numVerts);
}

long PhysicsShapePolygon::getPointsCount() const
{
    return ((cpPolyShape*)_info->shapes.front())->numVerts;
}

Point PhysicsShapePolygon::getCenter()
{
    return _center;
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
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGEBOX));
        
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
        
        _offset = offset;
        _mass = PHYSICS_INFINITY;
        _moment = PHYSICS_INFINITY;
        
        setMaterial(material);
        
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
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGEPOLYGEN));
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        _center = PhysicsHelper::cpv2point(cpCentroidForPoly(count, vec));
        
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

Point PhysicsShapeEdgePolygon::getCenter()
{
    return _center;
}

long PhysicsShapeEdgePolygon::getPointsCount() const
{
    return _info->shapes.size() + 1;
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
        CC_BREAK_IF(!PhysicsShape::init(Type::EDGECHAIN));
        
        vec = new cpVect[count];
        PhysicsHelper::points2cpvs(points, vec, count);
        _center = PhysicsHelper::cpv2point(cpCentroidForPoly(count, vec));
        
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

Point PhysicsShapeEdgeChain::getCenter()
{
    return _center;
}

long PhysicsShapeEdgeChain::getPointsCount() const
{
    return _info->shapes.size() + 1;
}

void PhysicsShape::setGroup(int group)
{
    if (group < 0)
    {
        for (auto shape : _info->shapes)
        {
            cpShapeSetGroup(shape, (cpGroup)group);
        }
    }
}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

#endif

NS_CC_END

#endif // CC_USE_PHYSICS
