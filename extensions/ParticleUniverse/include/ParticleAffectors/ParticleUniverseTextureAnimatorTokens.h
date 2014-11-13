/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_TEXTURE_ANIMATION_TOKENS_H__
#define __PU_TEXTURE_ANIMATION_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorTokens.h"

namespace ParticleUniverse
{
	/** The TextureAnimatorTranslator parses 'TextureAnimator' tokens
	*/
	class _ParticleUniverseExport TextureAnimatorTranslator : public ScriptTranslator
	{
		public:
			TextureAnimatorTranslator(void){};
			~TextureAnimatorTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport TextureAnimatorWriter : public ParticleAffectorWriter
	{
		public:

			TextureAnimatorWriter(void) {};
			virtual ~TextureAnimatorWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
