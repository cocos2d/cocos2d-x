/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_FOLLOWER_FACTORY_H__
#define __PU_PARTICLE_FOLLOWER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseParticleFollowerTokens.h"
#include "ParticleUniverseParticleFollower.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the ParticleFollower.
    */
	class _ParticleUniverseExport ParticleFollowerFactory : public ParticleAffectorFactory
	{
		public:
			ParticleFollowerFactory(void){};
	        virtual ~ParticleFollowerFactory(void){};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "ParticleFollower";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<ParticleFollower>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mParticleFollowerTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mParticleFollowerTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mParticleFollowerWriter.write(serializer, element);
			}

		protected:
			ParticleFollowerWriter mParticleFollowerWriter;
			ParticleFollowerTranslator mParticleFollowerTranslator;
	};

}
#endif
