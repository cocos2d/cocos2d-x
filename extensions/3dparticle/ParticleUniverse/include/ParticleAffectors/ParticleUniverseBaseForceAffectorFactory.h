/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BASE_ATTRACTOR_FACTORY_H__
#define __PU_BASE_ATTRACTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseForceAffectorTokens.h"
#include "ParticleUniverseBaseForceAffector.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** This factory is just a dummy factory.
    */
	class _ParticleUniverseExport BaseForceAffectorFactory : public ParticleAffectorFactory
	{
		protected:
			BaseForceAffectorWriter mBaseForceAffectorWriter;
			BaseForceAffectorTranslator mBaseForceAffectorTranslator;

		public:
			BaseForceAffectorFactory(void) {};
	        virtual ~BaseForceAffectorFactory(void) {};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "Dummy01"; // Dummy Factory, only for setting up token definitions.
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				EXCEPT(Exception::ERR_NOT_IMPLEMENTED, "PU: BaseForceAffectorFactory is a dummy factory.", 
					"BaseForceAffectorFactory::createAffector");
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBaseForceAffectorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBaseForceAffectorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mBaseForceAffectorWriter.write(serializer, element);
			}
	};

}
#endif
