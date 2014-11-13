/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_ALIAS_TOKENS_H__
#define __PU_PARTICLE_ALIAS_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScriptDeserializer.h"

namespace ParticleUniverse
{
	/** The AliasTranslator parses 'Alias' tokens
	*/
	class _ParticleUniverseExport AliasTranslator : public ScriptTranslator
	{
		public:
			AliasTranslator(void);
			virtual ~AliasTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};

}
#endif
