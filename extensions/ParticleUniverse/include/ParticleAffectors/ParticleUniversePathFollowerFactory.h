/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PATH_FOLLOWER_FACTORY_H__
#define __PU_PATH_FOLLOWER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniversePathFollowerTokens.h"
#include "ParticleUniversePathFollower.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the PathFollower.
    */
	class _ParticleUniverseExport PathFollowerFactory : public ParticleAffectorFactory
	{
		public:
			PathFollowerFactory(void) {};
	        virtual ~PathFollowerFactory(void) {};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "PathFollower";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<PathFollower>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mPathFollowerTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mPathFollowerTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mPathFollowerWriter.write(serializer, element);
			}

		protected:
			PathFollowerWriter mPathFollowerWriter;
			PathFollowerTranslator mPathFollowerTranslator;
	};

}
#endif
