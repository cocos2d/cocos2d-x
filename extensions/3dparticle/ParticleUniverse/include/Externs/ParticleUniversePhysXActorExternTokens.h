/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSX_EXTERN_TOKENS_H__
#define __PU_PHYSX_EXTERN_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#ifdef PU_PHYSICS_PHYSX
	#include "ParticleUniverseExternTokens.h"

	namespace ParticleUniverse
	{
		/** The PhysXActorExternTranslator parses 'PhysXActorExtern' tokens
		*/
		class _ParticleUniverseExport PhysXActorExternTranslator : public ScriptTranslator
		{
			public:
				PhysXActorExternTranslator(void){};
				~PhysXActorExternTranslator(void){};
				virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
				virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
		};
		//-------------------------------------------------------------------------
		//-------------------------------------------------------------------------
		//-------------------------------------------------------------------------

		/** The PhysXShapeTranslator also parses 'PhysXActorExtern' tokens
		*/
		class _ParticleUniverseExport PhysXShapeTranslator : public ScriptTranslator
		{
			public:
				PhysXShapeTranslator(void){};
				~PhysXShapeTranslator(void){};
				virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
		};
		//-------------------------------------------------------------------------
		//-------------------------------------------------------------------------
		//-------------------------------------------------------------------------

		/** 
		*/
		class _ParticleUniverseExport PhysXActorExternWriter : public ExternWriter
		{
			public:

				PhysXActorExternWriter(void) {};
				virtual ~PhysXActorExternWriter(void) {};

				/** @see
					ScriptWriter::write
				*/
				virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
		};

	}
#endif //PU_PHYSICS_PHYSX
#endif
