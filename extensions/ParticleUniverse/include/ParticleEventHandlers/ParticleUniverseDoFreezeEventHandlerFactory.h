/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_FREEZE_EVENT_HANDLER_FACTORY_H__
#define __PU_DO_FREEZE_EVENT_HANDLER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseDoFreezeEventHandler.h"
#include "ParticleUniverseDoFreezeEventHandlerTokens.h"

namespace ParticleUniverse
{
	/** This factory class is responsible for creation of a DoFreezeEventHandler.
    */
	class _ParticleUniverseExport DoFreezeEventHandlerFactory : public ParticleEventHandlerFactory
	{
		public:
			DoFreezeEventHandlerFactory(void) {};
	        virtual ~DoFreezeEventHandlerFactory(void) {};

			/** See ParticleEventHandlerFactory*/
			virtual String getEventHandlerType(void) const
			{
				return "DoFreeze";
			}

			/** See ParticleEventHandlerFactory*/
			virtual ParticleEventHandler* createEventHandler(void)
			{
				return _createEventHandler<DoFreezeEventHandler>();
			}

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mDoFreezeEventHandlerWriter.write(serializer, element);
			}

		protected:
			DoFreezeEventHandlerWriter mDoFreezeEventHandlerWriter;
	};

}
#endif
