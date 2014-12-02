/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_TEXTURE_ANIMATION_FACTORY_H__
#define __PU_TEXTURE_ANIMATION_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseTextureAnimatorTokens.h"
#include "ParticleUniverseTextureAnimator.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the TextureAnimator.
    */
	class _ParticleUniverseExport TextureAnimatorFactory : public ParticleAffectorFactory
	{
		public:
			TextureAnimatorFactory(void){};
	        virtual ~TextureAnimatorFactory(void){};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "TextureAnimator";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<TextureAnimator>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mTextureAnimatorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mTextureAnimatorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mTextureAnimatorWriter.write(serializer, element);
			}

		protected:
			TextureAnimatorWriter mTextureAnimatorWriter;
			TextureAnimatorTranslator mTextureAnimatorTranslator;
	};

}
#endif
