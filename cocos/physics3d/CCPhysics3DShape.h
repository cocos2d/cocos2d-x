﻿/****************************************************************************
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

#ifndef __PHYSICS_3D_SHAPE_H__
#define __PHYSICS_3D_SHAPE_H__

#include "base/CCRef.h"
#include "base/ccConfig.h"
#include "math/CCMath.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

class btCollisionShape;

NS_CC_BEGIN
/**
    @addtogroup _3d
    @{
*/

/**
    @brief @~english Create a physical shape(box, sphere, cylinder, capsule, convexhull, mesh and heightfield)
    @~chinese 创建一个物理形状（盒，球面，柱面，胶囊剂，凸形轮廓，网和heightfield ）
*/
class CC_DLL Physics3DShape : public Ref
{
public:
    enum class ShapeType
    {
        UNKNOWN = 0,
        BOX,
        SPHERE,
        CYLINDER,
        CAPSULE,
        CONVEX,
        MESH,
        HEIGHT_FIELD,
        COMPOUND
    };

    /** @~english get shape type
        @~chinese 得到的形状类型
    */
    virtual ShapeType getShapeType() const;

    /** @~english create box shape
        @~chinese 创建箱体形状
        @param extent @~english  The extent of sphere. @~chinese 球体的程度。
    */
    static Physics3DShape* createBox(const cocos2d::Vec3& extent);

    /** @~english create sphere shape
        @~chinese 创建球体形状
        @param radius @~english  The radius of sphere. @~chinese 球半径。
    */
    static Physics3DShape* createSphere(float radius);

    /** @~english create cylinder shape
        @~chinese 创建圆柱体
        @param radius @~english  The radius of cylinder. @~chinese 圆柱体的半径。
        @param height @~english  The height. @~chinese 高度。
    */
    static Physics3DShape* createCylinder(float radius, float height);

    /** @~english create capsule shape
        @~chinese 创建胶囊的形状
        @param radius @~english  The radius of casule. @~chinese 对胶囊的半径。
        @param height @~english  The height (cylinder part). @~chinese 高度（筒）。
    */
    static Physics3DShape* createCapsule(float radius, float height);

    /** @~english create convex hull
        @~chinese 创建凸壳
        @param points @~english  The vertices of convex hull @~chinese 凸壳的顶点
        @param numPoints @~english  The number of vertices. @~chinese 顶点个数。
    */
    static Physics3DShape* createConvexHull(const cocos2d::Vec3* points, int numPoints);

    /** @~english create mesh
        @~chinese 创建网格
        @param triangles @~english  The pointer of triangle list @~chinese 三角形列表的指针
        @param numTriangles @~english  The number of triangles. @~chinese 三角形数。

    */
    static Physics3DShape* createMesh(const cocos2d::Vec3* triangles, int numTriangles);

    /** @~english create heightfield
        @~chinese 创建地形
        @param heightStickWidth @~english  The Width of heightfield @~chinese 对地形的宽度
        @param heightStickLength @~english  The Length of heightfield. @~chinese 对地形的长度。
        @param heightfieldData @~english  The Data of heightfield. @~chinese 对地形数据。
        @param minHeight @~english  The minHeight of heightfield. @~chinese 对地形的minheight。
        @param maxHeight @~english  The maxHeight of heightfield. @~chinese 对地形的最大高度。
        @param flipQuadEdges @~english  if flip QuadEdges @~chinese 如果quadedges翻转

    */
    static Physics3DShape* createHeightfield(int heightStickWidth,int heightStickLength
            , const void* heightfieldData, float heightScale
            , float minHeight, float maxHeight
            , bool useFloatDatam, bool flipQuadEdges, bool useDiamondSubdivision = false);

    /** @~english create Compound Shape
        @~chinese 创建复合形状
        @param shapes @~english  The list of child shape @~chinese 儿童形状列表
    */
    static Physics3DShape* createCompoundShape(const std::vector<std::pair<Physics3DShape*, Mat4>>& shapes);


#if CC_ENABLE_BULLET_INTEGRATION
    btCollisionShape* getbtShape() const
    {
        return _btShape;
    }
#endif

protected:
    Physics3DShape();
    ~Physics3DShape();

    bool initBox(const cocos2d::Vec3& ext);
    bool initSphere(float radius);
    bool initCylinder(float radius, float height);
    bool initCapsule(float radius, float height);
    bool initConvexHull(const cocos2d::Vec3* points, int numPoints);
    bool initMesh(const cocos2d::Vec3* triangles, int numTriangles);
    bool initHeightfield(int heightStickWidth,int heightStickLength
                         , const void* heightfieldData, float heightScale
                         , float minHeight, float maxHeight
                         , bool useFloatDatam, bool flipQuadEdges
                         , bool useDiamondSubdivision);
    bool initCompoundShape(const std::vector<std::pair<Physics3DShape*, Mat4>>& shapes);


    ShapeType _shapeType; //shape type

#if (CC_ENABLE_BULLET_INTEGRATION)
    btCollisionShape*  _btShape;
    unsigned char* _heightfieldData;
    std::vector<Physics3DShape*> _compoundChildShapes;
#endif
};

// end of 3d group
/// @}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_SHAPE_H__
