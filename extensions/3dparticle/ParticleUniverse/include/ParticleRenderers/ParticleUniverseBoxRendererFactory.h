/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BOX_RENDERER_FACTORY_H__
#define __PU_BOX_RENDERER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleUniverseBoxRenderer.h"
#include "ParticleUniverseBoxRendererTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating a BoxRenderer.
    */
	class _ParticleUniverseExport BoxRendererFactory : public ParticleRendererFactory
	{
		public:
			BoxRendererFactory(void) {};
	        virtual ~BoxRendererFactory(void) {};

			/** See ParticleRendererFactory */
			String getRendererType(void) const
			{
				return "Box";
			}

			/** See ParticleRendererFactory */
			ParticleRenderer* createRenderer(void)
			{
				return _createRenderer<BoxRenderer>();
			}

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mBoxRendererWriter.write(serializer, element);
			}

		protected:
			BoxRendererWriter mBoxRendererWriter;
	};

}
#endif
