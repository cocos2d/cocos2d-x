/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSICS_EXTERN_H__
#define __PU_PHYSICS_EXTERN_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseExtern.h"
#include "ParticleUniversePhysicsActor.h"

namespace ParticleUniverse
{
	/** PhysicsExtern is a pure virtual class that must be subclassed. The child class forms the connection between Particle Universe and
		the physics engine.
	*/
	class _ParticleUniverseExport PhysicsExtern : public Extern
	{
		public:
			PhysicsExtern(void) : Extern() {};
			virtual ~PhysicsExtern(void) {};

		/** As soon as a particle is emitted it can be processed by the PhysicsExtern. One of the actions is to assign a PhysicsActor and
			shape to the particle.
		*/
		virtual void _initParticleForEmission(Particle* particle) = 0;

		/** As soon as a particle is expired it can be processed by the PhysicsExtern. One of the actions is to remove a PhysicsActor from
			the particle.
		*/
		virtual void _initParticleForExpiration(Particle* particle) = 0;
	};

}
#endif
