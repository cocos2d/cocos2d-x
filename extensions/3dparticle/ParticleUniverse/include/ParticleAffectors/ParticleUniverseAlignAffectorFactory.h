/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ALIGN_AFFECTOR_FACTORY_H__
#define __PU_ALIGN_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorFactory.h"
#include "ParticleUniverseAlignAffector.h"
#include "ParticleUniverseAlignAffectorTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the AlignAffector.
    */
	class _ParticleUniverseExport AlignAffectorFactory : public ParticleAffectorFactory
	{
		public:
			AlignAffectorFactory(void) {};
	        virtual ~AlignAffectorFactory(void) {};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "Align";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<AlignAffector>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mAlignAffectorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mAlignAffectorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mAlignAffectorWriter.write(serializer, element);
			}

		protected:
			AlignAffectorWriter mAlignAffectorWriter;
			AlignAffectorTranslator mAlignAffectorTranslator;
	};

}
#endif
