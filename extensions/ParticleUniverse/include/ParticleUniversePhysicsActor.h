/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSICS_ACTOR_H__
#define __PU_PHYSICS_ACTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniversePhysicsShape.h"

namespace ParticleUniverse
{
	/** PhysicsActorDesc contains the properties of the actor and is used to create a actor.
	*/
	class _ParticleUniverseExport PhysicsActorDesc
	{
		public:
			// Constructor
			PhysicsActorDesc(void) : 
				position(Vector3::ZERO),
				direction(Vector3::ZERO),
				orientation(Quaternion::IDENTITY),
				mass(1.0f),
				collisionGroup(0){};

			// Destructor
			virtual ~PhysicsActorDesc(void) {}

			// Public attributes
			Vector3 position;
			Vector3 direction;
			Quaternion orientation;
			Real mass;
			uint16 collisionGroup;
	};

	/** A PhysicsActor is an element of the physical world and has no visual representation by itself. It only has physical properties. 
		The PhysicsActor is an abstraction class of the real underlying physics engine, such as PhysX, Havok or Bullet.
	*/
	class _ParticleUniverseExport PhysicsActor
	{
		public:
			// Constructor
			PhysicsActor(void) : 
				position(Vector3::ZERO),
				direction(Vector3::ZERO),
				orientation(Quaternion::IDENTITY),
				mass(1.0f),
				collisionGroup(0),
				contactPoint(Vector3::ZERO),
				contactNormal(Vector3::ZERO){};

			// Destructor
			virtual ~PhysicsActor(void) {};

			// Public attributes
			Vector3 position;
			Vector3 direction;
			Quaternion orientation;
			Real mass;
			uint16 collisionGroup;
			Vector3 contactPoint;
			Vector3 contactNormal;
	};

}
#endif
