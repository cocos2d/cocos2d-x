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

#include "Externs/ParticleUniverseBoxColliderExtern.h"
#include "OgreNode.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void BoxColliderExtern::_preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		if (isAttached())
		{
			// Use the position of the parent node in this case.
			position = getParentNode()->_getDerivedPosition();
			mDerivedPosition = position;
			populateAlignedBox(mBox, mDerivedPosition, mWidth, mHeight, mDepth);
			_calculateBounds();
		}
	}
	//-----------------------------------------------------------------------
	void BoxColliderExtern::_interface(ParticleTechnique* technique, 
		Particle* particle, 
		Real timeElapsed)
	{
		if (isAttached())
		{
			if (mDistanceThresholdSet && mDerivedPosition.distance(particle->position) > mDistanceThreshold)
				return;

			// Use the derived BoxCollider functionality here
			_affect(technique, particle, timeElapsed);
		}
	}
	//-----------------------------------------------------------------------
	void BoxColliderExtern::copyAttributesTo (Extern* externObject)
	{
		Attachable::copyAttributesTo(externObject);

		BoxColliderExtern* boxColliderExtern = static_cast<BoxColliderExtern*>(externObject);
		BoxCollider* boxCollider = static_cast<BoxCollider*>(boxColliderExtern);
		BoxCollider::copyAttributesTo(boxCollider);
	}
}
