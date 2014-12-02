/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode
Special thanks to: M. Geissler

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSX_FLUID_EXTERN_TOKENS_H__
#define __PU_PHYSX_FLUID_EXTERN_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#ifdef PU_PHYSICS_PHYSX
	#include "ParticleUniverseExternTokens.h"

	namespace ParticleUniverse
	{
		/** The PhysXFluidExternTranslator parses 'PhysXFluidExtern' tokens
		*/
		class _ParticleUniverseExport PhysXFluidExternTranslator : public ScriptTranslator
		{
			public:
				PhysXFluidExternTranslator(void){};
				~PhysXFluidExternTranslator(void){};
				virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
				virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
		};
		//-------------------------------------------------------------------------
		//-------------------------------------------------------------------------
		//-------------------------------------------------------------------------

		/** The PhysXFluidFlagTranslator also parses 'PhysXFluidExtern' tokens
		*/
		class _ParticleUniverseExport PhysXFluidFlagTranslator : public ScriptTranslator
		{
			public:
				PhysXFluidFlagTranslator(void){};
				~PhysXFluidFlagTranslator(void){};
				virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
		};

		/** 
		*/
		class _ParticleUniverseExport PhysXFluidExternWriter : public ExternWriter
		{
			public:

				PhysXFluidExternWriter(void) {};
				virtual ~PhysXFluidExternWriter(void) {};

				/** @see
					ScriptWriter::write
				*/
				virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
		};

	}
#endif //PU_PHYSICS_PHYSX
#endif
