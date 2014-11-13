/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSX_EXTERN_H__
#define __PU_PHYSX_EXTERN_H__

#include "ParticleUniversePrerequisites.h"
#ifdef PU_PHYSICS_PHYSX

	#include "ParticleUniversePhysicsExtern.h"
	#include "NxPhysics.h"
	#include "NxActor.h"
	#include "NxScene.h"

	namespace ParticleUniverse
	{
		class _ParticleUniverseExport PhysXActor : public PhysicsActor
		{
			public:
				// Constructor
				PhysXActor(void) : 
					PhysicsActor(),
					nxActor(0),
					nxParticleData(0){};

				// Destructor
				virtual ~PhysXActor(void) {};

				NxActor* nxActor;
				NxParticleData* nxParticleData;
		};
		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
		class ParticleStructure
		{
			public:
				// Constructor and Destructor
				ParticleStructure(void) : 
					lifetime(0),
					id(0),
					density(0),
					bufferFlag(0),
					particle(0){};
				virtual ~ParticleStructure(void) {};

				// Public attributes
				NxVec3	position;
				NxVec3  velocity;
				NxReal  lifetime;
				NxVec3	collisionNormal;
				NxU32	id;
				NxU32   bufferFlag;
				NxReal	density;
				Particle* particle;
		};
		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
		/** The PhysXExtern class is a base class for PhysX.
		*/
		class _ParticleUniverseExport PhysXExtern : public PhysicsExtern
		{
			public:
				PhysXExtern(void) : mCollisionGroup(0){};
				virtual ~PhysXExtern(void){};

				/** This function is called by the PhysXBridge. Every time it is called, the physics are updated.
				*/
				virtual void synchronize(Real timeElapsed) = 0;

				/** Get the collision group.
				*/
				virtual uint16 getCollisionGroup(void) const
				{
					return mCollisionGroup;
				};
				
				/** Set the collision group.
				*/
				virtual void setCollisionGroup(uint16 collisionGroup)
				{
					mCollisionGroup = collisionGroup;
				};

			protected:
				uint16 mCollisionGroup;
		};

	}
#endif //PU_PHYSICS_PHYSX
#endif
