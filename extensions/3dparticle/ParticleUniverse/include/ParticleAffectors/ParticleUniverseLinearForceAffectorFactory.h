/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_LINEAR_FORCE_AFFECTOR_FACTORY_H__
#define __PU_LINEAR_FORCE_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseForceAffectorTokens.h"
#include "ParticleUniverseLinearForceAffector.h"
#include "ParticleUniverseLinearForceAffectorTokens.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the LinearForceAffector.
    */
	class _ParticleUniverseExport LinearForceAffectorFactory : public ParticleAffectorFactory
	{
		public:
			LinearForceAffectorFactory(void) {};
	        virtual ~LinearForceAffectorFactory(void) {};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "LinearForce";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<LinearForceAffector>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mLinearForceAffectorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mLinearForceAffectorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mLinearForceAffectorWriter.write(serializer, element);
			}

		protected:
			LinearForceAffectorWriter mLinearForceAffectorWriter;
			LinearForceAffectorTranslator mLinearForceAffectorTranslator;
	};

}
#endif
