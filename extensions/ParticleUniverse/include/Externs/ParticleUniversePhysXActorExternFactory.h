/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSX_ACTOR_EXTERN_FACTORY_H__
#define __PU_PHYSX_ACTOR_EXTERN_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#ifdef PU_PHYSICS_PHYSX
	#include "ParticleUniverseExternFactory.h"
	#include "ParticleUniversePhysXActorExtern.h"
	#include "ParticleUniversePhysXActorExternTokens.h"

	namespace ParticleUniverse
	{
		/** Factory class responsible for creating the PhysXActorExtern.
		*/
		class _ParticleUniverseExport PhysXActorExternFactory : public ExternFactory
		{
			public:
				PhysXActorExternFactory(void) : 
					ExternFactory(){};
				virtual ~PhysXActorExternFactory(void){};

				/** 
				*/
				String getExternType(void) const
				{
					return "PhysXActor";
				};

				/** 
				*/
				Extern* createExtern(void)
				{
					return _createExtern<PhysXActorExtern>();
				};

				/** See ScriptReader */
				virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
				{
					return mPhysXActorExternTranslator.translateChildProperty(compiler, node);
				};

				/** See ScriptReader */
				virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
				{
					return mPhysXActorExternTranslator.translateChildObject(compiler, node);
				};

				/*  */
				virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
				{
					// Delegate to mPhysActorXExternWriter
					mPhysXActorExternWriter.write(serializer, element);
				};

			protected:
				PhysXActorExternWriter mPhysXActorExternWriter;
				PhysXActorExternTranslator mPhysXActorExternTranslator;
		};

	}
#endif //PU_PHYSICS_PHYSX
#endif
