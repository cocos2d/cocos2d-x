/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BULLET_COLLISION_COMMON_H
#define BULLET_COLLISION_COMMON_H

///Common headerfile includes for Bullet Collision Detection

///Bullet's btCollisionWorld and btCollisionObject definitions
#include "bullet/BulletCollision//CollisionDispatch/btCollisionWorld.h"
#include "bullet/BulletCollision//CollisionDispatch/btCollisionObject.h"

///Collision Shapes
#include "bullet/BulletCollision//CollisionShapes/btBoxShape.h"
#include "bullet/BulletCollision//CollisionShapes/btSphereShape.h"
#include "bullet/BulletCollision//CollisionShapes/btCapsuleShape.h"
#include "bullet/BulletCollision//CollisionShapes/btCylinderShape.h"
#include "bullet/BulletCollision//CollisionShapes/btConeShape.h"
#include "bullet/BulletCollision//CollisionShapes/btStaticPlaneShape.h"
#include "bullet/BulletCollision//CollisionShapes/btConvexHullShape.h"
#include "bullet/BulletCollision//CollisionShapes/btTriangleMesh.h"
#include "bullet/BulletCollision//CollisionShapes/btConvexTriangleMeshShape.h"
#include "bullet/BulletCollision//CollisionShapes/btBvhTriangleMeshShape.h"
#include "bullet/BulletCollision//CollisionShapes/btScaledBvhTriangleMeshShape.h"
#include "bullet/BulletCollision//CollisionShapes/btTriangleMeshShape.h"
#include "bullet/BulletCollision//CollisionShapes/btTriangleIndexVertexArray.h"
#include "bullet/BulletCollision//CollisionShapes/btCompoundShape.h"
#include "bullet/BulletCollision//CollisionShapes/btTetrahedronShape.h"
#include "bullet/BulletCollision//CollisionShapes/btEmptyShape.h"
#include "bullet/BulletCollision//CollisionShapes/btMultiSphereShape.h"
#include "bullet/BulletCollision//CollisionShapes/btUniformScalingShape.h"

///Narrowphase Collision Detector
#include "bullet/BulletCollision//CollisionDispatch/btSphereSphereCollisionAlgorithm.h"

//#include "bullet/BulletCollision//CollisionDispatch/btSphereBoxCollisionAlgorithm.h"
#include "bullet/BulletCollision//CollisionDispatch/btDefaultCollisionConfiguration.h"

///Dispatching and generation of collision pairs (broadphase)
#include "bullet/BulletCollision//CollisionDispatch/btCollisionDispatcher.h"
#include "bullet/BulletCollision//BroadphaseCollision/btSimpleBroadphase.h"
#include "bullet/BulletCollision//BroadphaseCollision/btAxisSweep3.h"
#include "bullet/BulletCollision//BroadphaseCollision/btMultiSapBroadphase.h"
#include "bullet/BulletCollision//BroadphaseCollision/btDbvtBroadphase.h"

///Math library & Utils
#include "bullet/LinearMath/btQuaternion.h"
#include "bullet/LinearMath/btTransform.h"
#include "bullet/LinearMath/btDefaultMotionState.h"
#include "bullet/LinearMath/btQuickprof.h"
#include "bullet/LinearMath/btIDebugDraw.h"
#include "bullet/LinearMath/btSerializer.h"


#endif //BULLET_COLLISION_COMMON_H

