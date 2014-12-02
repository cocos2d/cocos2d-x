/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_VELOCITY_MATCHING_AFFECTOR_TOKENS_H__
#define __PU_VELOCITY_MATCHING_AFFECTOR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorTokens.h"

namespace ParticleUniverse
{
	/** The VelocityMatchingAffectorTranslator parses 'VelocityMatchingAffector' tokens
	*/
	class _ParticleUniverseExport VelocityMatchingAffectorTranslator : public ScriptTranslator
	{
		public:
			VelocityMatchingAffectorTranslator(void){};
			~VelocityMatchingAffectorTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport VelocityMatchingAffectorWriter : public ParticleAffectorWriter
	{
		public:

			VelocityMatchingAffectorWriter(void) {};
			virtual ~VelocityMatchingAffectorWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
