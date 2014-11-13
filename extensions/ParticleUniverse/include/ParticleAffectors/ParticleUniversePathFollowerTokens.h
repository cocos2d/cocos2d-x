/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PATH_FOLLOWER_TOKENS_H__
#define __PU_PATH_FOLLOWER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorTokens.h"

namespace ParticleUniverse
{
	/** The PathFollowerTranslator parses 'PathFollower' tokens
	*/
	class _ParticleUniverseExport PathFollowerTranslator : public ScriptTranslator
	{
		public:
			PathFollowerTranslator(void){};
			~PathFollowerTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport PathFollowerWriter : public ParticleAffectorWriter
	{
		public:

			PathFollowerWriter(void) {};
			virtual ~PathFollowerWriter(void) {};


			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
