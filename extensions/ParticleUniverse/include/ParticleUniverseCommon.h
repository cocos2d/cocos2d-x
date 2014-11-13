/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_COMMON_H__
#define __PU_COMMON_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	enum ComparisionOperator
	{
		CO_LESS_THAN,
		CO_EQUALS,
		CO_GREATER_THAN
	};

	enum InterpolationType
	{
		IT_LINEAR,
		IT_SPLINE
	};

	/*  Identifies the different components used in the Particle Universe plugin.
	*/
	enum ComponentType
	{
		CT_VISUAL_PARTICLE,
		CT_SYSTEM,
		CT_TECHNIQUE,
		CT_EMITTER,
		CT_AFFECTOR,
		CT_OBSERVER
	};

	/*  These are the eventtypes used by the ParticleSystemListener. As soon as one of these events occurs, the handleParticleSystemEvent() function is 
		called, passing the eventtype and additional information. The eventtypes are used by several components in Particle Universe itself
		and also by external system. Therefore it is put on namespace level.
		Note, that this differs from the Observers and EventHandler components that are used for internal use. The event types listed here and their
		usage in the ParticleSystemListener is for external use (the client application).
	*/
	enum EventType
	{
		PU_EVT_SYSTEM_ATTACHING,		// Submit event when the particle system is being attached or detached.
		PU_EVT_SYSTEM_ATTACHED,			// Submit event when the particle system is attached or detached.
		PU_EVT_SYSTEM_PREPARING,		// Submit event when the particle system is preparing.
		PU_EVT_SYSTEM_PREPARED,			// Submit event when the particle system is prepared.
		PU_EVT_SYSTEM_STARTING,			// Submit event when the particle system is starting.
		PU_EVT_SYSTEM_STARTED,			// Submit event when the particle system is started.
		PU_EVT_SYSTEM_STOPPING,			// Submit event when the particle system is stopping.
		PU_EVT_SYSTEM_STOPPED,			// Submit event when the particle system is stopped.
		PU_EVT_SYSTEM_PAUSING,			// Submit event when the particle system is pausing.
		PU_EVT_SYSTEM_PAUSED,			// Submit event when the particle system is paused.
		PU_EVT_SYSTEM_RESUMING,			// Submit event when the particle system is resuming (after a pause).
		PU_EVT_SYSTEM_RESUMED,			// Submit event when the particle system is resumed (after a pause).
		PU_EVT_SYSTEM_DELETING,			// Submit event when the particle system is being deleted.
		PU_EVT_LOD_TRANSITION,			// Submit event when the particle system switches to another technique when a LOD-level is exceeded.
		PU_EVT_EMITTER_STARTED,			// Submit event when an emitter is started.
		PU_EVT_EMITTER_STOPPED,			// Submit event when an emitter is stopped.
		PU_EVT_NO_PARTICLES_LEFT,		// Submit event when all particles have been expired.
	};

	/*  This struct is used to pass specific information to a ParticleSystemListener when a certain event occurs. 
		A struct is used to make it possible to update the info in the future, without an interface change.
	*/
	struct ParticleUniverseEvent
	{
		EventType eventType;
		ComponentType componentType;
		String componentName;
		ParticleTechnique* technique; // Is filled if the componentType is a technique
		ParticleEmitter* emitter; // Is filled if the componentType is an emitter
	};

	/*  Comparison function for float/double values, which determines whether a and b are almost equal
	*/
	static bool almostEquals(Real a, Real b, Real epsilon = std::numeric_limits<Real>::epsilon())
	{
		return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon); 
	};
}

#endif
