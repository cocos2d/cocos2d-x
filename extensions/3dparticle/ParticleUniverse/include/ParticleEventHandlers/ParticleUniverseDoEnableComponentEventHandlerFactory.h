/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_ENABLE_COMPONENT_EVENT_HANDLER_FACTORY_H__
#define __PU_DO_ENABLE_COMPONENT_EVENT_HANDLER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseDoEnableComponentEventHandlerTokens.h"
#include "ParticleUniverseDoEnableComponentEventHandler.h"

namespace ParticleUniverse
{
	/** This factory class is responsible for creation of a DoEnableComponentEventHandler.
    */
	class _ParticleUniverseExport DoEnableComponentEventHandlerFactory : public ParticleEventHandlerFactory
	{
		public:
			DoEnableComponentEventHandlerFactory(void) {};
	        virtual ~DoEnableComponentEventHandlerFactory(void) {};

			/** See ParticleEventHandlerFactory */
			virtual String getEventHandlerType(void) const
			{
				return "DoEnableComponent";
			}

			/** See ParticleEventHandlerFactory */
			virtual ParticleEventHandler* createEventHandler(void)
			{
				return _createEventHandler<DoEnableComponentEventHandler>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mDoEnableComponentEventHandlerTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mDoEnableComponentEventHandlerTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mDoEnableComponentEventHandlerWriter.write(serializer, element);
			}

		protected:
			DoEnableComponentEventHandlerWriter mDoEnableComponentEventHandlerWriter;
			DoEnableComponentEventHandlerTranslator mDoEnableComponentEventHandlerTranslator;
	};

}
#endif
