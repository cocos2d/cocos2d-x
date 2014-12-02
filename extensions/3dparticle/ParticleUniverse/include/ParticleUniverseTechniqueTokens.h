/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_TECHNIQUE_TOKENS_H__
#define __PU_TECHNIQUE_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScriptWriter.h"
#include "ParticleUniverseScriptDeserializer.h"

namespace ParticleUniverse
{
	/** The TechniqueTranslator parses all 'technique' tokens
	*/
	class _ParticleUniverseExport TechniqueTranslator : public ScriptTranslator
	{
		protected:
			ParticleTechnique* mTechnique;
		public:
			TechniqueTranslator(void);
			virtual ~TechniqueTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** The ParticleTechniqueWriter writes all 'technique' tokens
    */
	class _ParticleUniverseExport ParticleTechniqueWriter : public ScriptWriter
	{
		public:

			ParticleTechniqueWriter(void) {};
			virtual ~ParticleTechniqueWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
