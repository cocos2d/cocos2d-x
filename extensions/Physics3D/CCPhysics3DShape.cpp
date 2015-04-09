/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "CCPhysics3D.h"

#if (CC_ENABLE_BULLET_INTEGRATION)


NS_CC_EXT_BEGIN

Physics3DShape::ShapeType Physics3DShape::getShapeType() const
{
    return _shapeType;
}

Physics3DShape::Physics3DShape()
: _shapeType(ShapeType::UNKNOWN)
{
#if (CC_ENABLE_BULLET_INTEGRATION)
    _btShape = nullptr;
#endif
}
Physics3DShape::~Physics3DShape()
{
#if (CC_ENABLE_BULLET_INTEGRATION)
    CC_SAFE_DELETE(_btShape);
#endif
}

Physics3DShape* Physics3DShape::createBox(const cocos2d::Vec3& extent)
{
    auto shape = new (std::nothrow) Physics3DShape();
    shape->initBox(extent);
    shape->autorelease();
    return shape;
}

Physics3DShape* Physics3DShape::createSphere(float radius)
{
    auto shape = new (std::nothrow) Physics3DShape();
    shape->initSphere(radius);
    shape->autorelease();
    return shape;
}

Physics3DShape* Physics3DShape::createCylinder(float radius, float height)
{
    auto shape = new (std::nothrow) Physics3DShape();
    shape->initCylinder(radius, height);
    shape->autorelease();
    return shape;
}

Physics3DShape* Physics3DShape::createCapsule(float radius, float height)
{
    auto shape = new (std::nothrow) Physics3DShape();
    shape->initCapsule(radius, height);
    shape->autorelease();
    return shape;
}

Physics3DShape* Physics3DShape::createConvexHull( const cocos2d::Vec3 *points, int numPoints )
{
    auto shape = new (std::nothrow) Physics3DShape();
    shape->initConvexHull(points, numPoints);
    shape->autorelease();
    return shape;
}

Physics3DShape* Physics3DShape::createMesh( const cocos2d::Vec3 *triangles, int numTriangles )
{
    auto shape = new (std::nothrow) Physics3DShape();
    shape->initMesh(triangles, numTriangles);
    shape->autorelease();
    return shape;
}

bool Physics3DShape::initBox(const cocos2d::Vec3& ext)
{
    _shapeType = ShapeType::BOX;
    _btShape = new btBoxShape(convertVec3TobtVector3(ext * 0.5f));
    return true;
}
bool Physics3DShape::initSphere(float radius)
{
    _shapeType = ShapeType::SPHERE;
    _btShape = new btSphereShape(radius);
    return true;
}
bool Physics3DShape::initCylinder(float radius, float height)
{
    _shapeType = ShapeType::CYLINDER;
    _btShape = new btCylinderShape(convertVec3TobtVector3(cocos2d::Vec3(radius, height, radius) * 0.5f));
    return true;
}
bool Physics3DShape::initCapsule(float radius, float height)
{
    _shapeType = ShapeType::CAPSULE;
    _btShape = new btCapsuleShape(radius, height);
    return true;
}

bool Physics3DShape::initConvexHull( const cocos2d::Vec3 *points, int numPoints )
{
    _shapeType = ShapeType::CONVEX;
    _btShape = new btConvexHullShape((btScalar *)points, numPoints, sizeof(cocos2d::Vec3));
    return true;
}

bool Physics3DShape::initMesh( const cocos2d::Vec3 *triangles, int numTriangles )
{
    _shapeType = ShapeType::MESH;
    auto mesh = new btTriangleMesh(false);
    for (int i = 0; i < numTriangles * 3; ++i){
        mesh->addTriangle(convertVec3TobtVector3(triangles[i]), convertVec3TobtVector3(triangles[i + 1]), convertVec3TobtVector3(triangles[i + 2]));
    }
    _btShape = new btBvhTriangleMeshShape(mesh, true);
    return true;
}

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION
