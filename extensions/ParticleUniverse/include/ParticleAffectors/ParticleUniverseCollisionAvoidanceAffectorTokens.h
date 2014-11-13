/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_COLLISION_AVOIDANCE_AFFECTOR_TOKENS_H__
#define __PU_COLLISION_AVOIDANCE_AFFECTOR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorTokens.h"

namespace ParticleUniverse
{
	/** The CollisionAvoidanceAffectorTranslator parses 'CollisionAvoidanceAffector' tokens
	*/
	class _ParticleUniverseExport CollisionAvoidanceAffectorTranslator : public ScriptTranslator
	{
		public:
			CollisionAvoidanceAffectorTranslator(void){};
			~CollisionAvoidanceAffectorTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport CollisionAvoidanceAffectorWriter : public ParticleAffectorWriter
	{
		public:

			CollisionAvoidanceAffectorWriter(void) {};
			virtual ~CollisionAvoidanceAffectorWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
