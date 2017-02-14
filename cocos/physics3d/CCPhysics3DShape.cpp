/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "physics3d/CCPhysics3D.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)
#include "bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

NS_CC_BEGIN

Physics3DShape::ShapeType Physics3DShape::getShapeType() const
{
    return _shapeType;
}

Physics3DShape::Physics3DShape()
: _shapeType(ShapeType::UNKNOWN)
{
#if (CC_ENABLE_BULLET_INTEGRATION)
    _btShape = nullptr;
    _heightfieldData = nullptr;
#endif
}
Physics3DShape::~Physics3DShape()
{
#if (CC_ENABLE_BULLET_INTEGRATION)
    CC_SAFE_DELETE(_btShape);
    CC_SAFE_DELETE_ARRAY(_heightfieldData);
    for (auto iter : _compoundChildShapes){
        CC_SAFE_RELEASE(iter);
    }
    _compoundChildShapes.clear();
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

Physics3DShape* Physics3DShape::createHeightfield( int heightStickWidth,int heightStickLength
                                                  , const void* heightfieldData, float heightScale
                                                  , float minHeight, float maxHeight
                                                  , bool useFloatDatam, bool flipQuadEdges
                                                  , bool useDiamondSubdivision)
{
    auto shape = new (std::nothrow) Physics3DShape();
    shape->initHeightfield(heightStickWidth, heightStickLength, heightfieldData, heightScale, minHeight, maxHeight, useFloatDatam, flipQuadEdges, useDiamondSubdivision);
    shape->autorelease();
    return shape;	
}

Physics3DShape* Physics3DShape::createCompoundShape( const std::vector<std::pair<Physics3DShape *, Mat4>> &shapes )
{
    auto shape = new (std::nothrow) Physics3DShape();
    shape->initCompoundShape(shapes);
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
    for (int i = 0; i < numTriangles * 3; i += 3){
        mesh->addTriangle(convertVec3TobtVector3(triangles[i]), convertVec3TobtVector3(triangles[i + 1]), convertVec3TobtVector3(triangles[i + 2]));
    }
    _btShape = new btBvhTriangleMeshShape(mesh, true);
    return true;
}

bool Physics3DShape::initHeightfield( int heightStickWidth,int heightStickLength 
                                     , const void* heightfieldData, float heightScale 
                                     , float minHeight, float maxHeight 
                                     , bool useFloatDatam, bool flipQuadEdges
                                     , bool useDiamondSubdivision)
{
    _shapeType = ShapeType::HEIGHT_FIELD;
    PHY_ScalarType type = PHY_UCHAR;
    unsigned int dataSizeInByte = heightStickWidth * heightStickLength;
    if (useFloatDatam){
        type = PHY_FLOAT;
        dataSizeInByte *= sizeof(float);
    }
    _heightfieldData = new unsigned char[dataSizeInByte];
    memcpy(_heightfieldData, heightfieldData, dataSizeInByte);
    auto heightfield = new btHeightfieldTerrainShape(heightStickWidth, heightStickLength, _heightfieldData, heightScale, minHeight, maxHeight, 1, type, flipQuadEdges);
    heightfield->setUseDiamondSubdivision(useDiamondSubdivision);
    _btShape = heightfield;
    return true;
}

bool Physics3DShape::initCompoundShape( const std::vector<std::pair<Physics3DShape *, Mat4>> &shapes )
{
    _shapeType = ShapeType::COMPOUND;
    auto compound = new btCompoundShape;
    for (auto iter : shapes){
        compound->addChildShape(convertMat4TobtTransform(iter.second), iter.first->getbtShape());
        CC_SAFE_RETAIN(iter.first);
        _compoundChildShapes.push_back(iter.first);
    }
    _btShape = compound;
    return true;
}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // CC_USE_3D_PHYSICS
