/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_ENABLE_COMPONENT_EVENT_HANDLER_H__
#define __PU_DO_ENABLE_COMPONENT_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseSystem.h"

namespace ParticleUniverse
{
	/** This class makes it possible to enable or disable a Component. This component is an 
		named emitter, affector or technique.
    */
	class _ParticleUniverseExport DoEnableComponentEventHandler : public ParticleEventHandler
	{
		protected:
			// Identifies the name of component
			String mComponentName;

			// Identifies the type of component
			ComponentType mComponentType;

			/** Determines whether the Component must be enabled or disabled.
	        */
			bool mComponentEnabled;

		public:
			DoEnableComponentEventHandler(void);
	        virtual ~DoEnableComponentEventHandler(void) {};

			/** Get the name of the component that must be enabled or disabled.
	        */
			const String& getComponentName(void) const {return mComponentName;};

			/** Set the name of the component that must be enabled or disables.
	        */
			void setComponentName(const String& componentName){mComponentName = componentName;};

			/** Get the value that identifies whether the component must be enabled or disabled.
	        */
			bool isComponentEnabled(void) const {return mComponentEnabled;};

			/** Set the value that identifies whether the component must be enabled or disabled.
	        */
			void setComponentEnabled(bool enabled){mComponentEnabled = enabled;};

			/** Get the value that identifies whether the component must be enabled or disabled.
	        */
			ComponentType getComponentType(void) const {return mComponentType;};

			/** Set the value that identifies whether the component must be enabled or disabled.
	        */
			void setComponentType(ComponentType componentType){mComponentType = componentType;};

			/** If the _handle() function of this class is invoked (by an Observer), it searches the 
				ParticleEmitter, ParticleAffector or ParticleTechnique defined by the its name. 
				The ParticleEmitter/Affector is either part of the ParticleTechnique in which the 
				DoEnableComponentEventHandler is defined, or if the ParticleEmitter/Affector is not 
				found, other ParticleTechniques are searched.
	        */
			virtual void _handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** Copy attributes to another event handler.
	        */
			virtual void copyAttributesTo (ParticleEventHandler* eventHandler);
	};

}
#endif
