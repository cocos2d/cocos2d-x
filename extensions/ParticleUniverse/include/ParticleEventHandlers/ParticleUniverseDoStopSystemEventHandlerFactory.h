/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_STOP_SYSTEM_EVENT_HANDLER_FACTORY_H__
#define __PU_DO_STOP_SYSTEM_EVENT_HANDLER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseDoStopSystemEventHandler.h"
#include "ParticleUniverseDoStopSystemEventHandlerTokens.h"

namespace ParticleUniverse
{
	/** This factory class is responsible for creation of a DoStopSystemEventHandler.
    */
	class _ParticleUniverseExport DoStopSystemEventHandlerFactory : public ParticleEventHandlerFactory
	{
		public:
			DoStopSystemEventHandlerFactory(void) {};
	        virtual ~DoStopSystemEventHandlerFactory(void) {};

			/** See ParticleEventHandlerFactory*/
			virtual String getEventHandlerType(void) const
			{
				return "DoStopSystem";
			}

			/** See ParticleEventHandlerFactory*/
			virtual ParticleEventHandler* createEventHandler(void)
			{
				return _createEventHandler<DoStopSystemEventHandler>();
			}

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mDoStopSystemEventHandlerWriter.write(serializer, element);
			}

		protected:
			DoStopSystemEventHandlerWriter mDoStopSystemEventHandlerWriter;
	};

}
#endif
