/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_LIGHT_RENDERER_FACTORY_H__
#define __PU_LIGHT_RENDERER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleUniverseLightRenderer.h"
#include "ParticleUniverseLightRendererTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating a LightRenderer.
    */
	class _ParticleUniverseExport LightRendererFactory : public ParticleRendererFactory
	{
		public:
			LightRendererFactory(void) {};
	        virtual ~LightRendererFactory(void) {};

			/** See ParticleRendererFactory */
			String getRendererType(void) const
			{
				return "Light";
			}

			/** See ParticleRendererFactory */
			ParticleRenderer* createRenderer(void)
			{
				return _createRenderer<LightRenderer>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mLightRendererTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mLightRendererTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mLightRendererWriter.write(serializer, element);
			}


		protected:
			LightRendererWriter mLightRendererWriter;
			LightRendererTranslator mLightRendererTranslator;
	};

}
#endif
