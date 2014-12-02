/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSICS_SHAPE_H__
#define __PU_PHYSICS_SHAPE_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/** 
    */
	class GroupsMask
	{
		public:
		GroupsMask(void){};
		GroupsMask(uint32 nbits0, uint32 nbits1, uint32 nbits2, uint32 nbits3) : 
			bits0(nbits0),
			bits1(nbits1),
			bits2(nbits2),
			bits3(nbits3){};
		~GroupsMask(void){};
		uint32 bits0, bits1, bits2, bits3;

        inline GroupsMask& operator = (const GroupsMask& groupsMask)
        {
            bits0 = groupsMask.bits0;
            bits1 = groupsMask.bits1;
            bits2 = groupsMask.bits2;
            bits3 = groupsMask.bits3;
            return *this;
        }

		inline bool operator == (const GroupsMask& groupsMask) const
        {
            return (bits0 == groupsMask.bits0 && bits1 == groupsMask.bits1 && bits2 == groupsMask.bits2 && bits3 == groupsMask.bits3);
        }

        inline bool operator != (const GroupsMask& groupsMask) const
        {
            return (bits0 != groupsMask.bits0 || bits1 != groupsMask.bits1 || bits2 != groupsMask.bits2 || bits3 != groupsMask.bits3);
        }
	};

	/**
	*/
	enum PhysicsShapeType
	{
		ST_BOX,
		ST_SPHERE,
		ST_CAPSULE,
	};

	/** PhysicsShapeDesc contains the properties of the shape and is used to create a shape.
	*/
	class _ParticleUniverseExport PhysicsShapeDesc
	{
		public:
			// Constructors
			PhysicsShapeDesc(void) : 
				mCollisionGroup(0),
				mAngularVelocity(Vector3::ZERO),
				mAngularDamping(0.5f),
				mMaterialIndex(0)
			{
				mGroupMask.bits0 = 0;
				mGroupMask.bits1 = 0;
				mGroupMask.bits2 = 0;
				mGroupMask.bits3 = 0;
			};

			// Copy Constructor
			PhysicsShapeDesc(const PhysicsShapeDesc& physicsShapeDesc)
			{
				mCollisionGroup = physicsShapeDesc.mCollisionGroup;
				mGroupMask.bits0 = physicsShapeDesc.mGroupMask.bits0;
				mGroupMask.bits1 = physicsShapeDesc.mGroupMask.bits1;
				mGroupMask.bits2 = physicsShapeDesc.mGroupMask.bits2;
				mGroupMask.bits3 = physicsShapeDesc.mGroupMask.bits3;
				mAngularVelocity = physicsShapeDesc.mAngularVelocity;
				mAngularDamping = physicsShapeDesc.mAngularDamping;
				mMaterialIndex = physicsShapeDesc.mMaterialIndex;
			};

			// Destructor
			virtual ~PhysicsShapeDesc(void) {};

			// Public attributes
			PhysicsShapeType mPhysicsShapeType;
			uint16 mCollisionGroup;
			GroupsMask mGroupMask;
			Vector3 mAngularVelocity;
			Real mAngularDamping;
			uint16 mMaterialIndex;
	};

	/** Sphere
    */
	class _ParticleUniverseExport PhysicsSphereDesc : public PhysicsShapeDesc
	{
		public:
			// Constructors
			PhysicsSphereDesc(void) : mRadius(1.0f)
			{
				mPhysicsShapeType = ST_SPHERE;
			};

			PhysicsSphereDesc(const Real radius) :
				PhysicsShapeDesc(),
				mRadius(radius)
			{
				mPhysicsShapeType = ST_SPHERE;
			};
			
			// Copy Constructor
			PhysicsSphereDesc(const PhysicsSphereDesc& physicsSphereDesc) :
				PhysicsShapeDesc(physicsSphereDesc)
			{
				mRadius = physicsSphereDesc.mRadius;
				mPhysicsShapeType = ST_SPHERE;
			};

			// Public attribute
			Real mRadius;
	};

	/** Box
    */
	class _ParticleUniverseExport PhysicsBoxDesc : public PhysicsShapeDesc
	{
		public:
			// Constructors
			PhysicsBoxDesc(void) : mDimensions(Vector3::UNIT_SCALE)
			{
				mPhysicsShapeType = ST_BOX;
			};

			PhysicsBoxDesc(const Vector3 dimensions) :
  				PhysicsShapeDesc(),
				mDimensions(dimensions)
			{
				mPhysicsShapeType = ST_BOX;
			};

			// Copy Constructor
			PhysicsBoxDesc(const PhysicsBoxDesc& physicsBoxDesc) :
  				PhysicsShapeDesc(physicsBoxDesc)
			{
				mDimensions = physicsBoxDesc.mDimensions;
				mPhysicsShapeType = ST_BOX;
			};

			// Public attribute
			// Dimensions in Particle Universe are width, height and depth, while PhysX uses half these lengths
			Vector3 mDimensions;
	};

	/** Box
    */
	class _ParticleUniverseExport PhysicsCapsuleDesc : public PhysicsShapeDesc
	{
		public:
			// Constructors
			PhysicsCapsuleDesc(void) : mRadius(1.0f), mHeight(100.0f)
			{
				mPhysicsShapeType = ST_CAPSULE;
			};

			PhysicsCapsuleDesc(const Real radius, const Real height) :
  				PhysicsShapeDesc(),
				mRadius(radius),
				mHeight(height)
			{
				mPhysicsShapeType = ST_CAPSULE;
			};

			// Copy Constructor
			PhysicsCapsuleDesc(const PhysicsCapsuleDesc& physicsCapsuleDesc) :
  				PhysicsShapeDesc(physicsCapsuleDesc)
			{
				mRadius = physicsCapsuleDesc.mRadius;
				mHeight = physicsCapsuleDesc.mHeight;
				mPhysicsShapeType = ST_CAPSULE;
			};

			// Public attribute
			Real mRadius;
			Real mHeight;
	};

	/** The PhysicsShape gives a PhysicsActor a real physical shape.
	@remarks
		Possible shapes are Box, Sphere, Capsule, ...
	*/
	class _ParticleUniverseExport PhysicsShape
	{
		public:
			// Constructor
			PhysicsShape(void) {};

			// Destructor
			virtual ~PhysicsShape(void) {};
	};

}
#endif
