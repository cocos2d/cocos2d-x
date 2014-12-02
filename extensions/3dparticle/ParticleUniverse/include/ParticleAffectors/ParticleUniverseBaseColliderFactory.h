/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BASE_COLLIDER_FACTORY_H__
#define __PU_BASE_COLLIDER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseColliderTokens.h"
#include "ParticleUniverseBaseCollider.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** This factory is just a dummy factory.
    */
	class _ParticleUniverseExport BaseColliderFactory : public ParticleAffectorFactory
	{
		protected:
			BaseColliderWriter mBaseColliderWriter;
			BaseColliderTranslator mBaseColliderTranslator;

		public:
			BaseColliderFactory(void) {};
	        virtual ~BaseColliderFactory(void) {};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "Dummy02"; // Dummy Factory, only for setting up token definitions.
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				EXCEPT(Exception::ERR_NOT_IMPLEMENTED, "PU: BaseColliderFactory is a dummy factory.", 
					"BaseColliderFactory::createAffector");
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBaseColliderTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBaseColliderTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mBaseColliderWriter.write(serializer, element);
			}
	};

}
#endif
