/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_VELOCITY_MATCHING_AFFECTOR_FACTORY_H__
#define __PU_VELOCITY_MATCHING_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorFactory.h"
#include "ParticleUniverseVelocityMatchingAffector.h"
#include "ParticleUniverseVelocityMatchingAffectorTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the VelocityMatchingAffector.
    */
	class _ParticleUniverseExport VelocityMatchingAffectorFactory : public ParticleAffectorFactory
	{
		public:
			VelocityMatchingAffectorFactory(void) {};
	        virtual ~VelocityMatchingAffectorFactory(void) {};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "VelocityMatching";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<VelocityMatchingAffector>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mVelocityMatchingAffectorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mVelocityMatchingAffectorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mVelocityMatchingAffectorWriter.write(serializer, element);
			}

		protected:
			VelocityMatchingAffectorWriter mVelocityMatchingAffectorWriter;
			VelocityMatchingAffectorTranslator mVelocityMatchingAffectorTranslator;
	};

}
#endif
