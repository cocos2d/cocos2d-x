/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_POSITION_EMITTER_FACTORY_H__
#define __PU_POSITION_EMITTER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniversePositionEmitter.h"
#include "ParticleUniversePositionEmitterTokens.h"

namespace ParticleUniverse
{
	/** This is the factory class that is responsible for creating a PositionEmitter.
    */
	class _ParticleUniverseExport PositionEmitterFactory : public ParticleEmitterFactory
	{
		protected:
			PositionEmitterWriter mPositionEmitterWriter;
			PositionEmitterTranslator mPositionEmitterTranslator;

		public:
			PositionEmitterFactory(void) {};
	        virtual ~PositionEmitterFactory(void) {};

			/** See ParticleEmitterFactory */
			String getEmitterType(void) const
			{
				return "Position";
			}

			/** See ParticleEmitterFactory */
			ParticleEmitter* createEmitter(void)
			{
				return _createEmitter<PositionEmitter>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mPositionEmitterTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mPositionEmitterTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate to mPositionEmitterWriter
				mPositionEmitterWriter.write(serializer, element);
			}
	};

}
#endif
