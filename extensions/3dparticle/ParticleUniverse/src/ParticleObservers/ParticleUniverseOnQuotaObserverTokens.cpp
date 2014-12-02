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

#include "ParticleObservers/ParticleUniverseOnQuotaObserver.h"
#include "ParticleObservers/ParticleUniverseOnQuotaObserverTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void OnQuotaObserverWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a OnQuotaObserver
		const OnQuotaObserver* observer = static_cast<const OnQuotaObserver*>(element);

		// Write the header of the OnQuotaObserver
		serializer->writeLine(token[TOKEN_OBSERVER], observer->getObserverType(), observer->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleObserverWriter::write(serializer, element);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
