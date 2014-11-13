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

#include "ParticleObservers/ParticleUniverseOnClearObserver.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void OnClearObserver::_notifyStart (void)
	{
		ParticleObserver::_notifyStart();
		mContinue = false;
	}
	//-----------------------------------------------------------------------
	bool OnClearObserver::_observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		// This function always returns false, but is never called (but it must be implemented).
		return false;
	}
	//-----------------------------------------------------------------------
	void OnClearObserver::_processParticle(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed, bool firstParticle)
	{
		// Override the _processParticle() function, because we don't observe individual particles.
		if (firstParticle)
		{
			// Only continue to validate if there was at least 1 particle emitted, otherwise the event-
			// handlers are already called at the very start (when there are no particle yet).
			mContinue = true;
		}
	}
	//-----------------------------------------------------------------------
	void OnClearObserver::_postProcessParticles(ParticleTechnique* technique, Real timeElapsed)
	{
		if (mContinue)
		{
			if (!(technique->getNumberOfEmittedParticles() > 0))
			{
				/** Handle the event. Use 0 as the particle pointer. This means that not all eventhandlers
					are suitable. If they expect a particle (and most eventhandlers do), it could
					result in an exception. Handlers such as the DoEnableComponentEventHandler and the
					DoStopSystemEventHandler however can be used without any problem.
				*/
				_handleEvent (technique, 0, timeElapsed);
				mContinue = false;
			}
		}
	}

}
