/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __CC_FRUSTUM_H_
#define __CC_FRUSTUM_H_

#include "base/ccMacros.h"
#include "math/CCMath.h"
#include "3d/CCAABB.h"
#include "3d/CCOBB.h"
#include "3d/CCPlane.h"

NS_CC_BEGIN

/**
* @addtogroup _3d
* @{
*/
class Camera;

/**
 * @class Frustum
 * @brief @~english The frustum is a six-side geometry, usually use the frustum to do fast-culling:
 * check a entity whether is a potential visible entity.
 * @~chinese 平截头体，平截头体是一个六面的几何体，通常使用它来进行快速的裁剪，来确定一个物体是否是潜在可见的.
 * @js NA
 * @lua NA
 */
class CC_DLL Frustum
{
    friend class Camera;
public:
    /**
     * @~english Constructor.
     * @~chinese 构造函数
     */
    Frustum(): _clipZ(true), _initialized(false) {}
    /**
    * @~english Destructor.
    * @~chinese 析构函数
    */
    ~Frustum(){}

    /**
     * @~english Init frustum from camera.
     * @~chinese 通过相机来初始化平截头体
     * @param camera @~english The specified camera.
     * @~chinese 指定的相机
     * @return @~english Return true if success, otherwise return false.
     * @~chinese 创建成功返回true，反之返回false
     */
    bool initFrustum(const Camera* camera);

    /**
     * @~english Check an AABB whether out of frustum or not.
     * @~chinese 检查一个AABB包围盒是否在平截头体之外
     * @param aabb @~english The specified AABB object.
     * @~chinese 指定的AABB包围盒
     * @return @~english Return true if the specified AABB object is out of the frustum, otherwise return false.
     * @~chinese 若指定的AABB包围盒在平截头体之外返回true，反之返回false
     */
    bool isOutOfFrustum(const AABB& aabb) const;
    /**
     * @~english Check is an OBB whether out of frustum or not.
     * @~chinese 检查一个OBB包围盒是否在平截头体之外
     * @param obb @~english The specified OBB object.
     * @~chinese 指定的OBB包围盒
     * @return @~english Return true if the specified OBB object is out of the frustum, otherwise return false.
     * @~chinese 若指定的OBB包围盒在平截头体之外返回true，反之返回false
     */
    bool isOutOfFrustum(const OBB& obb) const;

    /**
     * @~english Set z clip.
     * @~chinese 设置Z裁剪
     * @param clipZ @~english If clipz == true use the near and far plane.
     * @~chinese Z裁剪，如果Z裁剪为true，则使用相机的近裁面与远裁面.
     */
    void setClipZ(bool clipZ) { _clipZ = clipZ; }
    /**
     * @~english Get Z clip.
     * @~chinese 获取平截头体是否使用了Z裁剪
     * @return @~english Return true if use the near and far plane, otherwise return false.
     * @~chinese 如果使用了相机的近裁面和远裁面进行Z裁剪返回true，反之返回false.
     */
    bool isClipZ() { return _clipZ; }
    
protected:
    /**
     * create clip plane
     */
    void createPlane(const Camera* camera);

    Plane _plane[6];             // clip plane, left, right, top, bottom, near, far
    bool _clipZ;                // use near and far clip plane
    bool _initialized;
};

// end of 3d group
/// @}

NS_CC_END

#endif//__CC_FRUSTUM_H_
