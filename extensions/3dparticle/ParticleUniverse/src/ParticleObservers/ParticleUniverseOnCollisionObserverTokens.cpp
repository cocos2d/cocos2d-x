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

#include "ParticleObservers/ParticleUniverseOnCollisionObserver.h"
#include "ParticleObservers/ParticleUniverseOnCollisionObserverTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void OnCollisionObserverWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a OnCollisionObserver
		const OnCollisionObserver* observer = static_cast<const OnCollisionObserver*>(element);

		// Write the header of the OnCollisionObserver
		serializer->writeLine(token[TOKEN_OBSERVER], observer->getObserverType(), observer->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleObserverWriter::write(serializer, element);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
