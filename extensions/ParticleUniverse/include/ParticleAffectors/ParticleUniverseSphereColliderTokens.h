/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SPHERE_COLLIDER_TOKENS_H__
#define __PU_SPHERE_COLLIDER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseColliderTokens.h"

namespace ParticleUniverse
{
	/** The SphereColliderTranslator parses 'SphereCollider' tokens
	*/
	class _ParticleUniverseExport SphereColliderTranslator : public ScriptTranslator
	{
		public:
			SphereColliderTranslator(void){};
			~SphereColliderTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport SphereColliderWriter : public BaseColliderWriter
	{
		public:

			SphereColliderWriter(void) {};
			virtual ~SphereColliderWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
