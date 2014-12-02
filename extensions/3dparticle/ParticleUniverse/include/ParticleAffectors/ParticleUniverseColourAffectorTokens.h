/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_COLOUR_AFFECTOR_TOKENS_H__
#define __PU_COLOUR_AFFECTOR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorTokens.h"

namespace ParticleUniverse
{
	/** The ColourAffectorTranslator parses 'ColourAffector' tokens
	*/
	class _ParticleUniverseExport ColourAffectorTranslator : public ScriptTranslator
	{
		public:
			ColourAffectorTranslator(void){};
			~ColourAffectorTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport ColourAffectorWriter : public ParticleAffectorWriter
	{
		public:

			ColourAffectorWriter(void) {};
			virtual ~ColourAffectorWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
