/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_CIRCLE_EMITTER_FACTORY_H__
#define __PU_CIRCLE_EMITTER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseCircleEmitter.h"
#include "ParticleUniverseCircleEmitterTokens.h"

namespace ParticleUniverse
{
	/** This is the factory class that is responsible for creating a CircleEmitter.
    */
	class _ParticleUniverseExport CircleEmitterFactory : public ParticleEmitterFactory
	{
		protected:
			CircleEmitterWriter mCircleEmitterWriter;
			CircleEmitterTranslator mCircleEmitterTranslator;

		public:
			CircleEmitterFactory(void) {};
	        virtual ~CircleEmitterFactory(void) {};

			/** See ParticleEmitterFactory */
			String getEmitterType(void) const
			{
				return "Circle";
			}

			/** See ParticleEmitterFactory */
			ParticleEmitter* createEmitter(void)
			{
				return _createEmitter<CircleEmitter>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mCircleEmitterTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mCircleEmitterTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate to mCircleEmitterWriter
				mCircleEmitterWriter.write(serializer, element);
			}
	};

}
#endif
