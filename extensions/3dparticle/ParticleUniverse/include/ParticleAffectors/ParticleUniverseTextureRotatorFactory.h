/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_TEXTURE_ROTATOR_FACTORY_H__
#define __PU_TEXTURE_ROTATOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseTextureRotatorTokens.h"
#include "ParticleUniverseTextureRotator.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the TextureRotator.
    */
	class _ParticleUniverseExport TextureRotatorFactory : public ParticleAffectorFactory
	{
		public:
			TextureRotatorFactory(void){};
	        virtual ~TextureRotatorFactory(void){};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "TextureRotator";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<TextureRotator>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mTextureRotatorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mTextureRotatorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mTextureRotatorWriter.write(serializer, element);
			}

		protected:
			TextureRotatorWriter mTextureRotatorWriter;
			TextureRotatorTranslator mTextureRotatorTranslator;
	};

}
#endif
