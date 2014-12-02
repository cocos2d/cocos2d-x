/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode
Special thanks to: M. Geissler

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSX_FLUID_EXTERN_FACTORY_H__
#define __PU_PHYSX_FLUID_EXTERN_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#ifdef PU_PHYSICS_PHYSX

	#include "ParticleUniverseExternFactory.h"
	#include "ParticleUniversePhysXFluidExtern.h"
	#include "ParticleUniversePhysXFluidExternTokens.h"

	namespace ParticleUniverse
	{
		/** Factory class responsible for creating the PhysXFluidExtern.
		*/
		class _ParticleUniverseExport PhysXFluidExternFactory : public ExternFactory
		{
			public:
				PhysXFluidExternFactory(void) : 
					ExternFactory(){};
				virtual ~PhysXFluidExternFactory(void){};

				/** 
				*/
				String getExternType(void) const
				{
					return "PhysXFluid";
				};

				/** 
				*/
				Extern* createExtern(void)
				{
					return _createExtern<PhysXFluidExtern>();
				};

				/** See ScriptReader */
				virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
				{
					return mPhysXFluidExternTranslator.translateChildProperty(compiler, node);
				};

				/** See ScriptReader */
				virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
				{
					return mPhysXFluidExternTranslator.translateChildObject(compiler, node);
				};

				/*  */
				virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
				{
					// Delegate to mPhysActorXExternWriter
					mPhysXFluidExternWriter.write(serializer, element);
				};

			protected:
				PhysXFluidExternWriter mPhysXFluidExternWriter;
				PhysXFluidExternTranslator mPhysXFluidExternTranslator;
		};

	}
#endif //PU_PHYSICS_PHYSX
#endif
