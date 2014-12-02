/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SCALE_VELOCITY_AFFECTOR_FACTORY_H__
#define __PU_SCALE_VELOCITY_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScaleVelocityAffectorTokens.h"
#include "ParticleUniverseScaleVelocityAffector.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the ScaleVelocityAffector.
    */
	class _ParticleUniverseExport ScaleVelocityAffectorFactory : public ParticleAffectorFactory
	{
		public:
			ScaleVelocityAffectorFactory(void) {};
	        virtual ~ScaleVelocityAffectorFactory(void) {};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "ScaleVelocity";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<ScaleVelocityAffector>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mScaleVelocityAffectorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mScaleVelocityAffectorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mScaleVelocityAffectorWriter.write(serializer, element);
			}

		protected:
			ScaleVelocityAffectorWriter mScaleVelocityAffectorWriter;
			ScaleVelocityAffectorTranslator mScaleVelocityAffectorTranslator;
	};

}
#endif
