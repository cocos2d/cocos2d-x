/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BEAM_RENDERER_FACTORY_H__
#define __PU_BEAM_RENDERER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleUniverseBeamRenderer.h"
#include "ParticleUniverseBeamRendererTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating a BeamRenderer.
    */
	class _ParticleUniverseExport BeamRendererFactory : public ParticleRendererFactory
	{
		public:
			BeamRendererFactory(void) {};
	        virtual ~BeamRendererFactory(void) {};

			/** See ParticleRendererFactory */
			String getRendererType(void) const
			{
				return "Beam";
			}

			/** See ParticleRendererFactory */
			ParticleRenderer* createRenderer(void)
			{
				return _createRenderer<BeamRenderer>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBeamRendererTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBeamRendererTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mBeamRendererWriter.write(serializer, element);
			}


		protected:
			BeamRendererWriter mBeamRendererWriter;
			BeamRendererTranslator mBeamRendererTranslator;
	};

}
#endif
