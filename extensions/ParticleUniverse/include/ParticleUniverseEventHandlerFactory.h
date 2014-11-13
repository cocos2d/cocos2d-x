/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_EVENT_HANDLER_FACTORY_H__
#define __PU_EVENT_HANDLER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseEventHandlerTokens.h"
#include "ParticleUniverseScriptDeserializer.h"
#include "ParticleUniverseScriptReader.h"

namespace ParticleUniverse
{
	/** This is the base factory of all ParticleEventHandler implementations.
    */
	class _ParticleUniverseExport ParticleEventHandlerFactory : public ScriptReader, public ScriptWriter, public FactoryAlloc
	{
	    protected:

			/** 
	        */
			template <class T>
			ParticleEventHandler* _createEventHandler(void)
			{
				ParticleEventHandler* particleEventHandler = PU_NEW_T(T, MEMCATEGORY_SCENE_OBJECTS)();
				particleEventHandler->setEventHandlerType(getEventHandlerType());
				return particleEventHandler;
			};

	public:
			ParticleEventHandlerFactory(void) {};
	        virtual ~ParticleEventHandlerFactory(void) {};

		    /** Returns the type of the factory, which identifies the event handler type this factory creates. */
			virtual String getEventHandlerType(void) const = 0;

			/** Creates a new event handler instance.
		    @remarks
	        */
		    virtual ParticleEventHandler* createEventHandler(void) = 0;

			/** Delete an event handler
	        */
			void destroyEventHandler (ParticleEventHandler* eventHandler)
			{
				PU_DELETE_T(eventHandler, ParticleEventHandler, MEMCATEGORY_SCENE_OBJECTS);
			};
	};

}
#endif
