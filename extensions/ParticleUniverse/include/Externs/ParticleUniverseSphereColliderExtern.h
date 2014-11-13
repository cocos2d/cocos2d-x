/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SPHERE_COLLIDER_EXTERN_H__
#define __PU_SPHERE_COLLIDER_EXTERN_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleAffectors/ParticleUniverseSphereCollider.h"
#include "ParticleUniverseAttachable.h"

namespace ParticleUniverse
{
	/** The SphereColliderExtern is a wrapper of the SphereCollider, adding the functionality of a MovableObject.
		This makes it possible to let particles collide with a SphereCollider that is attached to a different 
		SceneNode, than the ParticleSystem with which particles it collides.
    */
	class _ParticleUniverseExport SphereColliderExtern : public Attachable, public SphereCollider
	{
		public:
			SphereColliderExtern(void) : 
				Attachable(),
				SphereCollider() {};
	        virtual ~SphereColliderExtern(void) {};

			/** see Extern::_preProcessParticles */
			virtual void _preProcessParticles(ParticleTechnique* technique, Real timeElapsed);

			/** see Extern::_interface */
			virtual void _interface(ParticleTechnique* technique, 
				Particle* particle, 
				Real timeElapsed);

			/** Copy both the Extern and the derived SphereCollider properties.
	        */
			virtual void copyAttributesTo (Extern* externObject);

		protected:
	};

}
#endif
