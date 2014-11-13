/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BILLBOARD_RENDERER_FACTORY_H__
#define __PU_BILLBOARD_RENDERER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleUniverseBillboardRenderer.h"
#include "ParticleUniverseBillboardRendererTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating a BillboardRenderer.
    */
	class _ParticleUniverseExport BillboardRendererFactory : public ParticleRendererFactory
	{
		public:
			BillboardRendererFactory(void) {};
	        virtual ~BillboardRendererFactory(void) {};

			/** See ParticleRendererFactory */
			String getRendererType(void) const
			{
				return "Billboard";
			}

			/** See ParticleRendererFactory */
			ParticleRenderer* createRenderer(void)
			{
				return _createRenderer<BillboardRenderer>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBillboardRendererTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBillboardRendererTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mBillboardRendererWriter.write(serializer, element);
			}


		protected:
			BillboardRendererWriter mBillboardRendererWriter;
			BillboardRendererTranslator mBillboardRendererTranslator;
	};

}
#endif
