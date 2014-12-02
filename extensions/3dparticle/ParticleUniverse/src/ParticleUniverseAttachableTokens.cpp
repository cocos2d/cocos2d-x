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

#include "ParticleUniverseAttachableTokens.h"

namespace ParticleUniverse
{
	void AttachableWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a AlignAffector
		const Attachable* attachable = static_cast<const Attachable*>(element);

		if (attachable->getDistanceThreshold() != std::numeric_limits<float>::max()) serializer->writeLine(
			token[TOKEN_DISTANCE_THRESHOLD], StringConverter::toString(attachable->getDistanceThreshold()), 12);
	}

}
