/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_SCALE_EVENT_HANDLER_FACTORY_H__
#define __PU_DO_SCALE_EVENT_HANDLER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseDoScaleEventHandlerTokens.h"
#include "ParticleUniverseDoScaleEventHandler.h"

namespace ParticleUniverse
{
	/** This factory class is responsible for creation of a DoScaleEventHandler.
    */
	class _ParticleUniverseExport DoScaleEventHandlerFactory : public ParticleEventHandlerFactory
	{
		public:
			DoScaleEventHandlerFactory(void) {};
	        virtual ~DoScaleEventHandlerFactory(void) {};

			/** See ParticleEventHandlerFactory */
			virtual String getEventHandlerType(void) const
			{
				return "DoScale";
			}

			/** See ParticleEventHandlerFactory */
			virtual ParticleEventHandler* createEventHandler(void)
			{
				return _createEventHandler<DoScaleEventHandler>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mDoScaleEventHandlerTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mDoScaleEventHandlerTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mDoScaleEventHandlerWriter.write(serializer, element);
			}

		protected:
			DoScaleEventHandlerWriter mDoScaleEventHandlerWriter;
			DoScaleEventHandlerTranslator mDoScaleEventHandlerTranslator;
	};

}
#endif
