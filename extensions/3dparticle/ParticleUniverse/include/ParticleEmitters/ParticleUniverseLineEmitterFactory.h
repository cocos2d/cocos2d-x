/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_LINE_EMITTER_FACTORY_H__
#define __PU_LINE_EMITTER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseLineEmitter.h"
#include "ParticleUniverseLineEmitterTokens.h"

namespace ParticleUniverse
{
	/** This is the factory class that is responsible for creating a LineEmitter.
    */
	class _ParticleUniverseExport LineEmitterFactory : public ParticleEmitterFactory
	{
		protected:
			LineEmitterWriter mLineEmitterWriter;
			LineEmitterTranslator mLineEmitterTranslator;

		public:
			LineEmitterFactory(void) {};
	        virtual ~LineEmitterFactory(void) {};

			/** See ParticleEmitterFactory */
			String getEmitterType(void) const
			{
				return "Line";
			}

			/** See ParticleEmitterFactory */
			ParticleEmitter* createEmitter(void)
			{
				return _createEmitter<LineEmitter>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mLineEmitterTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mLineEmitterTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate to mLineEmitterWriter
				mLineEmitterWriter.write(serializer, element);
			}
	};

}
#endif
