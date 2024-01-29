/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "physics3d/CCPhysics3DShape.h"
#include "physics3d/CCPhysicsSprite3D.h"
#include "physics3d/CCPhysics3DWorld.h"
#include "physics3d/CCPhysics3DDebugDrawer.h"
#include "physics3d/CCPhysics3DObject.h"
#include "physics3d/CCPhysics3DComponent.h"
#include "physics3d/CCPhysics3DConstraint.h"

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

//convert between cocos and bullet
cocos2d::Vec3 convertbtVector3ToVec3(const btVector3 &btVec3);
btVector3 convertVec3TobtVector3(const cocos2d::Vec3 &vec3);
cocos2d::Mat4 convertbtTransformToMat4(const btTransform &btTrans);
btTransform convertMat4TobtTransform(const cocos2d::Mat4 &mat4);
cocos2d::Quaternion convertbtQuatToQuat(const btQuaternion &btQuat);
btQuaternion convertQuatTobtQuat(const cocos2d::Quaternion &quat);

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_H__
