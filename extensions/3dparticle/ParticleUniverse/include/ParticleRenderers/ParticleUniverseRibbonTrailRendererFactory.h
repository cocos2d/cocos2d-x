/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_RIBBONTRAIL_RENDERER_FACTORY_H__
#define __PU_RIBBONTRAIL_RENDERER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleUniverseRibbonTrailRenderer.h"
#include "ParticleUniverseRibbonTrailRendererTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating a RibbonTrailRenderer.
    */
	class _ParticleUniverseExport RibbonTrailRendererFactory : public ParticleRendererFactory
	{
		public:
			RibbonTrailRendererFactory(void) {};
	        virtual ~RibbonTrailRendererFactory(void) {};

			/** See ParticleRendererFactory */
			String getRendererType(void) const
			{
				return "RibbonTrail";
			}

			/** See ParticleRendererFactory */
			ParticleRenderer* createRenderer(void)
			{
				return _createRenderer<RibbonTrailRenderer>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mRibbonTrailRendererTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mRibbonTrailRendererTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mRibbonTrailRendererWriter.write(serializer, element);
			}


		protected:
			RibbonTrailRendererWriter mRibbonTrailRendererWriter;
			RibbonTrailRendererTranslator mRibbonTrailRendererTranslator;
	};

}
#endif
