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

#include "ParticleEventHandlers/ParticleUniverseDoStopSystemEventHandler.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void DoStopSystemEventHandler::_handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		particleTechnique->getParentSystem()->stop();
	}
}
