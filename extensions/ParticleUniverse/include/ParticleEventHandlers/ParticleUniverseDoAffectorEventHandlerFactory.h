/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_AFFECTOR_EVENT_HANDLER_FACTORY_H__
#define __PU_DO_AFFECTOR_EVENT_HANDLER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseDoAffectorEventHandlerTokens.h"
#include "ParticleUniverseDoAffectorEventHandler.h"

namespace ParticleUniverse
{
	/** This factory class is responsible for creation of a DoAffectorEventHandler.
    */
	class _ParticleUniverseExport DoAffectorEventHandlerFactory : public ParticleEventHandlerFactory
	{
		public:
			DoAffectorEventHandlerFactory(void) {};
	        virtual ~DoAffectorEventHandlerFactory(void) {};

			/** See ParticleEventHandlerFactory */
			virtual String getEventHandlerType(void) const
			{
				return "DoAffector";
			}

			/** See ParticleEventHandlerFactory */
			virtual ParticleEventHandler* createEventHandler(void)
			{
				return _createEventHandler<DoAffectorEventHandler>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mDoAffectorEventHandlerTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mDoAffectorEventHandlerTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mDoAffectorEventHandlerWriter.write(serializer, element);
			}

		protected:
			DoAffectorEventHandlerWriter mDoAffectorEventHandlerWriter;
			DoAffectorEventHandlerTranslator mDoAffectorEventHandlerTranslator;
	};

}
#endif
