/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SPHERE_RENDERER_FACTORY_H__
#define __PU_SPHERE_RENDERER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleUniverseSphereRenderer.h"
#include "ParticleUniverseSphereRendererTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating a SphereRenderer.
    */
	class _ParticleUniverseExport SphereRendererFactory : public ParticleRendererFactory
	{
		public:
			SphereRendererFactory(void) {};
	        virtual ~SphereRendererFactory(void) {};

			/** See ParticleRendererFactory */
			String getRendererType(void) const
			{
				return "Sphere";
			}

			/** See ParticleRendererFactory */
			ParticleRenderer* createRenderer(void)
			{
				return _createRenderer<SphereRenderer>();
			}

			/** See ParticleRendererFactory */
			virtual ParticleRendererWriter* getRendererWriter(void) {return &mSphereRendererWriter;};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mSphereRendererWriter.write(serializer, element);
			}

		protected:
			SphereRendererWriter mSphereRendererWriter;
	};

}
#endif
