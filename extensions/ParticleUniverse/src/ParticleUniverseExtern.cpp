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

#include "ParticleUniverseExtern.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void Extern::_processParticle(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed, bool firstParticle)
	{
		// Call the _firstParticle() function if the first particle in the update loop is encountered.
		if (firstParticle)
		{
			// Perform a precalculation at the first particle
			_firstParticle(particleTechnique, particle, timeElapsed);
		}

		_interface(particleTechnique, particle, timeElapsed);
	}
	//-----------------------------------------------------------------------
	void Extern::_notifyRescaled(const Vector3& scale)
	{
		_mExternScale = scale;
	}
	//-----------------------------------------------------------------------
	void Extern::copyAttributesTo(Extern* externObject)
	{
		copyParentAttributesTo(externObject);
	}
	//-----------------------------------------------------------------------
	void Extern::copyParentAttributesTo(Extern* externObject)
	{
		externObject->setName(mName);
		externObject->mParentTechnique = mParentTechnique;
		externObject->_mExternScale = _mExternScale;
	}

}
