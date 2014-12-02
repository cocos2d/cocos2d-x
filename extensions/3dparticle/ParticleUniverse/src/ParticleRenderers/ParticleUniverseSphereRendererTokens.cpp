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

#include "ParticleRenderers/ParticleUniverseSphereRendererTokens.h"
#include "ParticleRenderers/ParticleUniverseSphereRenderer.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void SphereRendererWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a SphereRenderer
		const SphereRenderer* renderer = static_cast<const SphereRenderer*>(element);

		// Write the header of the SphereRenderer
		serializer->writeLine(token[TOKEN_RENDERER], renderer->getRendererType(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleRendererWriter::write(serializer, element);

		// Write own attributes

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
