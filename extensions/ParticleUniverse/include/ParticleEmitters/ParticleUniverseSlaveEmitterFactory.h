/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SLAVE_EMITTER_FACTORY_H__
#define __PU_SLAVE_EMITTER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseSlaveEmitter.h"
#include "ParticleUniverseSlaveEmitterTokens.h"

namespace ParticleUniverse
{
	/** This is the factory class that is responsible for creating a SlaveEmitter.
    */
	class _ParticleUniverseExport SlaveEmitterFactory : public ParticleEmitterFactory
	{
		protected:
			SlaveEmitterWriter mSlaveEmitterWriter;
			SlaveEmitterTranslator mSlaveEmitterTranslator;

		public:
			SlaveEmitterFactory(void) {};
	        virtual ~SlaveEmitterFactory(void) {};

			/** See ParticleEmitterFactory */
			String getEmitterType(void) const
			{
				return "Slave";
			}

			/** See ParticleEmitterFactory */
			ParticleEmitter* createEmitter(void)
			{
				return _createEmitter<SlaveEmitter>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mSlaveEmitterTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mSlaveEmitterTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate to mSlaveEmitterWriter
				mSlaveEmitterWriter.write(serializer, element);
			}
	};

}
#endif
