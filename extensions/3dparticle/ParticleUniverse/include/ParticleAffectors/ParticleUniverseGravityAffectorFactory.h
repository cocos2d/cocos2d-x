/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_GRAVITY_AFFECTOR_FACTORY_H__
#define __PU_GRAVITY_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseGravityAffectorTokens.h"
#include "ParticleUniverseGravityAffector.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the GravityAffector.
    */
	class _ParticleUniverseExport GravityAffectorFactory : public ParticleAffectorFactory
	{
		public:
			GravityAffectorFactory(void){};
	        virtual ~GravityAffectorFactory(void){};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "Gravity";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<GravityAffector>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mGravityAffectorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mGravityAffectorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mGravityAffectorWriter.write(serializer, element);
			}

		protected:
			GravityAffectorWriter mGravityAffectorWriter;
			GravityAffectorTranslator mGravityAffectorTranslator;
	};

}
#endif
