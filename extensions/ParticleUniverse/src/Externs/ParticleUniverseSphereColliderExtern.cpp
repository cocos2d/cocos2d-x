/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "Externs/ParticleUniverseSphereColliderExtern.h"
#include "OgreNode.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void SphereColliderExtern::_preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		if (isAttached())
		{
			// Use the position of the parent node in this case.
			position = getParentNode()->_getDerivedPosition();
			mDerivedPosition = position;
			mSphere.setCenter(mDerivedPosition);
		}
	}
	//-----------------------------------------------------------------------
	void SphereColliderExtern::_interface(ParticleTechnique* technique, 
		Particle* particle, 
		Real timeElapsed)
	{
		if (isAttached())
		{
			if (mDistanceThresholdSet && mDerivedPosition.distance(particle->position) > mDistanceThreshold)
				return;

			// Use the derived SphereCollider functionality here
			_affect(technique, particle, timeElapsed);
		}
	}
	//-----------------------------------------------------------------------
	void SphereColliderExtern::copyAttributesTo (Extern* externObject)
	{
		Attachable::copyAttributesTo(externObject);

		SphereColliderExtern* sphereColliderExtern = static_cast<SphereColliderExtern*>(externObject);
		SphereCollider* sphereCollider = static_cast<SphereCollider*>(sphereColliderExtern);
		SphereCollider::copyAttributesTo(sphereCollider);
	}
}
