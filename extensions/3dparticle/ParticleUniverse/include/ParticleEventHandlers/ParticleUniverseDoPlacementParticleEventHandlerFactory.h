/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_FACTORY_H__
#define __PU_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseDoPlacementParticleEventHandlerTokens.h"
#include "ParticleUniverseDoPlacementParticleEventHandler.h"

namespace ParticleUniverse
{
	/** This factory class is responsible for creation of a DoPlacementParticleEventHandler.
    */
	class _ParticleUniverseExport DoPlacementParticleEventHandlerFactory : public ParticleEventHandlerFactory
	{
		public:
			DoPlacementParticleEventHandlerFactory(void) {};
	        virtual ~DoPlacementParticleEventHandlerFactory(void) {};

			/** See ParticleEventHandlerFactory */
			virtual String getEventHandlerType(void) const
			{
				return "DoPlacementParticle";
			}

			/** See ParticleEventHandlerFactory */
			virtual ParticleEventHandler* createEventHandler(void)
			{
				return _createEventHandler<DoPlacementParticleEventHandler>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mDoPlacementParticleEventHandlerTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mDoPlacementParticleEventHandlerTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mDoPlacementParticleEventHandlerWriter.write(serializer, element);
			}

		protected:
			DoPlacementParticleEventHandlerWriter mDoPlacementParticleEventHandlerWriter;
			DoPlacementParticleEventHandlerTranslator mDoPlacementParticleEventHandlerTranslator;
	};

}
#endif
