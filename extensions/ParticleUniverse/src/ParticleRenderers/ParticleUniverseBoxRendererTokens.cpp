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

#include "ParticleRenderers/ParticleUniverseBoxRendererTokens.h"
#include "ParticleRenderers/ParticleUniverseBoxRenderer.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void BoxRendererWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a BoxRenderer
		const BoxRenderer* renderer = static_cast<const BoxRenderer*>(element);

		// Write the header of the BoxRenderer
		serializer->writeLine(token[TOKEN_RENDERER], renderer->getRendererType(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleRendererWriter::write(serializer, element);

		// Write own attributes

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
