/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_FORCE_FIELD_AFFECTOR_FACTORY_H__
#define __PU_FORCE_FIELD_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorFactory.h"
#include "ParticleUniverseForceFieldAffector.h"
#include "ParticleUniverseForceFieldAffectorTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the ForceFieldAffector.
    */
	class _ParticleUniverseExport ForceFieldAffectorFactory : public ParticleAffectorFactory
	{
		public:
			ForceFieldAffectorFactory(void) {};
	        virtual ~ForceFieldAffectorFactory(void) {};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "ForceField";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<ForceFieldAffector>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mForceFieldAffectorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mForceFieldAffectorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mForceFieldAffectorWriter.write(serializer, element);
			}

		protected:
			ForceFieldAffectorWriter mForceFieldAffectorWriter;
			ForceFieldAffectorTranslator mForceFieldAffectorTranslator;
	};

}
#endif
