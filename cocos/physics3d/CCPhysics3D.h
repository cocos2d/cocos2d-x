/**************************************************************************
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

#ifndef __PHYSICS_3D_H__
#define __PHYSICS_3D_H__

#include "base/ccConfig.h"
#include "math/CCMath.h"

#if CC_USE_3D_PHYSICS

#include "CCPhysics3DShape.h"
#include "CCPhysicsSprite3D.h"
#include "CCPhysics3DWorld.h"
#include "CCPhysics3DDebugDrawer.h"
#include "CCPhysics3DObject.h"
#include "CCPhysics3DComponent.h"
#include "CCPhysics3DConstraint.h"

NS_CC_BEGIN

CC_DLL const char* physics3dVersion();

NS_CC_END

#if (CC_ENABLE_BULLET_INTEGRATION)

//include bullet header files
#include "bullet/LinearMath/btTransform.h"
#include "bullet/LinearMath/btVector3.h"
#include "bullet/LinearMath/btQuaternion.h"

#include "bullet/btBulletCollisionCommon.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "bullet/BulletCollision/CollisionDispatch/btGhostObject.h"

/**
    @~english convert between cocos and bullet
    @~chinese 在cocos和bullet之间执行转换
    @param btVec3 @~english  a vector3 of bullet module which will be converted to cocos2d module @~chinese bullet中的vector3
    @return @~english a Vec3 in module of cocos2d @~chinese cocos中的Vec3
*/
cocos2d::Vec3 convertbtVector3ToVec3(const btVector3& btVec3);

/**
    @~english convert between cocos and bullet
    @~chinese 在cocos和bullet之间执行转换转换
    @param vec3 @~english  a vector3 of cocos2d module which will be converted to bullet module @~chinese cocos中的Vec3
    @return @~english a Vec3 in module of bullet @~chinese bullet中的vector3
*/
btVector3 convertVec3TobtVector3(const cocos2d::Vec3& vec3);

/**
    @~english convert between cocos and bullet
    @~chinese 在cocos和bullet之间执行转换
    @param btTrans @~english  a transform of bullet module which will be converted to cocos2d module @~chinese bullet模块中的btTransform
    @return @~english a Mat4 in module of cocos2d @~chinese cocos模块中Mat4
*/
cocos2d::Mat4 convertbtTransformToMat4(const btTransform& btTrans);

/**
    @~english convert between cocos and bullet
    @~chinese 在cocos和bullet之间执行转换
    @param mat4 @~english  a transform of cocos2d module which will be converted to bullet module @~chinese cocos模块中Mat4
    @return @~english a btTransform in module of bullet @~chinese bullet模块中的btTransform
*/
btTransform convertMat4TobtTransform(const cocos2d::Mat4& mat4);

/**
    @~english convert between cocos and bullet
    @~chinese 在cocos和bullet之间执行转换
    @param btQuaternion @~english  a quaternion of bullet module which will be converted to cocos2d module @~chinese bullet模块中的btQuaternion
    @return @~english a Quaternion in module of cocos2d @~chinese cocos模块中Quaternion
*/
cocos2d::Quaternion convertbtQuatToQuat(const btQuaternion& btQuat);

/**
    @~english convert between cocos and bullet
    @~chinese 在cocos和bullet之间执行转换
    @param quat @~english  a quaternion of cocos2d module which will be converted to bullet module @~chinese cocos模块中Quaternion
    @return @~english a btQuaternion in module of bullet @~chinese bullet模块中的btQuaternion
*/
btQuaternion convertQuatTobtQuat(const cocos2d::Quaternion& quat);

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_H__
