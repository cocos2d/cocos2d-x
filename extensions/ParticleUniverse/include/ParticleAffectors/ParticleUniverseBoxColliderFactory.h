/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BOX_COLLIDER_FACTORY_H__
#define __PU_BOX_COLLIDER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBoxColliderTokens.h"
#include "ParticleUniverseBoxCollider.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the BoxCollider.
    */
	class _ParticleUniverseExport BoxColliderFactory : public ParticleAffectorFactory
	{
		public:
			BoxColliderFactory(void){};
	        virtual ~BoxColliderFactory(void){};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "BoxCollider";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<BoxCollider>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBoxColliderTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBoxColliderTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mBoxColliderWriter.write(serializer, element);
			}

		protected:
			BoxColliderWriter mBoxColliderWriter;
			BoxColliderTranslator mBoxColliderTranslator;
	};

}
#endif
