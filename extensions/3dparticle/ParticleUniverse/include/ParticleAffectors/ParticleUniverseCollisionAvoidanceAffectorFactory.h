/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_COLLISION_AVOIDANCE_AFFECTOR_FACTORY_H__
#define __PU_COLLISION_AVOIDANCE_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorFactory.h"
#include "ParticleUniverseCollisionAvoidanceAffector.h"
#include "ParticleUniverseCollisionAvoidanceAffectorTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the CollisionAvoidanceAffector.
    */
	class _ParticleUniverseExport CollisionAvoidanceAffectorFactory : public ParticleAffectorFactory
	{
		public:
			CollisionAvoidanceAffectorFactory(void) {};
	        virtual ~CollisionAvoidanceAffectorFactory(void) {};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "CollisionAvoidance";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<CollisionAvoidanceAffector>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mCollisionAvoidanceAffectorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mCollisionAvoidanceAffectorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mCollisionAvoidanceAffectorWriter.write(serializer, element);
			}

		protected:
			CollisionAvoidanceAffectorWriter mCollisionAvoidanceAffectorWriter;
			CollisionAvoidanceAffectorTranslator mCollisionAvoidanceAffectorTranslator;
	};

}
#endif
