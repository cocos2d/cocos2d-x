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

#include "ParticleEventHandlers/ParticleUniverseDoAffectorEventHandler.h"

namespace ParticleUniverse
{
	// Constants
	const bool DoAffectorEventHandler::DEFAULT_PRE_POST = false;

	//-----------------------------------------------------------------------
	DoAffectorEventHandler::DoAffectorEventHandler(void) : 
		ParticleEventHandler(),
		mPrePost(DEFAULT_PRE_POST),
		mAffectorName(StringUtil::BLANK)
	{
	}
	//-----------------------------------------------------------------------
	void DoAffectorEventHandler::_handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		/** Search for the affector.
		*/
		ParticleTechnique* technique = 0;
		ParticleAffector* affector = particleTechnique->getAffector(mAffectorName);
		if (!affector)
		{
			// Search all techniques in this ParticleSystem for an affector with the correct name
			ParticleSystem* system = particleTechnique->getParentSystem();
			size_t size = system->getNumTechniques();
			for(size_t i = 0; i < size; ++i)
			{
				technique = system->getTechnique(i);
				affector = technique->getAffector(mAffectorName);
				if (affector)
				{
					break;
				}
			}
		}

		if (affector)
		{
			// Call the affector even if it has enabled set to 'false'.
			if (mPrePost)
			{
				affector->_preProcessParticles(particleTechnique, timeElapsed);
				affector->_affect(particleTechnique, particle, timeElapsed);
				affector->_postProcessParticles(particleTechnique, timeElapsed);
			}
			else
			{
				affector->_affect(particleTechnique, particle, timeElapsed);
			}
		}
	}
	//-----------------------------------------------------------------------
	void DoAffectorEventHandler::copyAttributesTo (ParticleEventHandler* eventHandler)
	{
		ParticleEventHandler::copyAttributesTo(eventHandler);
		DoAffectorEventHandler* doAffectorEventHandler = static_cast<DoAffectorEventHandler*>(eventHandler);
		doAffectorEventHandler->setAffectorName(mAffectorName);
		doAffectorEventHandler->setPrePost(mPrePost);
	}

}
