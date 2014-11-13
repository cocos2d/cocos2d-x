/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_OBSERVER_H__
#define __PU_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseParticle.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** ParticleObservers are used to observe whether a certain condition occurs. This condition is often related to 
		the state of a Particle, but also certain situations regarding a ParticleTechnique, ParticleEmitter or even
		the ParticleSystem can be validated.
	@remarks
		ParticleEventHandlers can be added to a ParticleObserve to handle the condition that is registered by the
		ParticleObserver. This mechanism provides a extendable framework for determination of events and processing
		these events.
	@par
		ParticleObservers are defined on the same level as a ParticleEmitter and not as part of a ParticleEmitter. 
		This is because the ParticleObserver observes ALL particles in the ParticleTechniques´ Particle pool.
	@par
		A ParticleObserver can contain one or more ParticleEventHandlers.
	*/
	class _ParticleUniverseExport ParticleObserver : public IAlias, public IElement
	{
		public:
			// Default values
			static const bool DEFAULT_ENABLED;
			static const Particle::ParticleType DEFAULT_PARTICLE_TYPE;
			static const Real DEFAULT_INTERVAL;
			static const bool DEFAULT_UNTIL_EVENT;

			typedef vector<ParticleEventHandler*>::iterator ParticleEventHandlerIterator;
			typedef vector<ParticleEventHandler*>::const_iterator ParticleEventHandlerConstIterator;
			typedef vector<ParticleEventHandler*> ParticleEventHandlerList;

			ParticleObserver(void);
			virtual ~ParticleObserver(void);

			/** Todo
	        */
			const String& getObserverType(void) const {return mObserverType;};
			void setObserverType(const String& observerType) {mObserverType = observerType;};

			/** Todo
	        */
			virtual bool isEnabled(void) const;

			/** Returns the 'enabled' value that was set in setEnabled() and not altered during execution.
	        */
			bool _getOriginalEnabled(void) const;

			/** Todo
	        */
			virtual void setEnabled(bool enabled);

			/** Reset internal values for 'enabled'. This means that both the mEnabled and mOriginalEnabled can be set again using setEnabled.
			@remarks
				Using _resetEnabled() makes it possible to use setEnabled() without the restriction of having a fixed mOriginalEnabled value.
	        */
			void _resetEnabled(void);

			/** Todo
	        */
			ParticleTechnique* getParentTechnique(void) const {return mParentTechnique;};
			void setParentTechnique(ParticleTechnique* parentTechnique){mParentTechnique = parentTechnique;};

			/** Todo
	        */
			const String& getName(void) const {return mName;};
			void setName(const String& name) {mName = name;};

			/** Todo
	        */
			const Particle::ParticleType& getParticleTypeToObserve(void) const {return mParticleTypeToObserve;};
			void setParticleTypeToObserve(const Particle::ParticleType particleTypeToObserve);

			/** Perform activities when a ParticleTechnique is started.
			*/
			virtual void _notifyStart (void);

			/** Perform activities when a ParticleTechnique is stopped.
			*/
			virtual void _notifyStop (void){/* Do nothing */};

			/** Notify that the Particle System is rescaled.
	        */
			virtual void _notifyRescaled(const Vector3& scale);

			/** Perform activities before the individual particles are processed.
	        */
			virtual void _preProcessParticles(ParticleTechnique* technique, Real timeElapsed);

			/** Executes the ParticleObserver.
			@remarks
				This function calls the _observe() function to determine whether the event must be handled or not.
	        */
			virtual void _processParticle(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed, bool firstParticle);

			/** Perform precalculations if the first Particle in the update-loop is processed.
			*/
			virtual void _firstParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Real timeElapsed) { /* by default do nothing */ }

			/** Perform activities after the individual particles are processed.
	        */
			virtual void _postProcessParticles(ParticleTechnique* technique, Real timeElapsed){/* Do nothing */};

			/** This function determines whether a condition (the event) is true or false.
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed) = 0;

			/** Todo
	        */
			ParticleEventHandler* createEventHandler(const String& eventHandlerType);

			/** Todo
	        */
			void addEventHandler(ParticleEventHandler* eventHandler);

			/** Todo
	        */
			void removeEventHandler(ParticleEventHandler* eventHandler);

			/** Todo
	        */
			ParticleEventHandler* getEventHandler (size_t index) const;

			/** Todo
	        */
			ParticleEventHandler* getEventHandler (const String& eventHandlerName) const;

			/** Todo
	        */
			size_t getNumEventHandlers (void) const;

			/** Todo
	        */
			void destroyEventHandler(ParticleEventHandler* eventHandler);

			/** Todo
	        */
			void destroyEventHandler (size_t index);

			/** Todo
	        */
			void destroyAllEventHandlers (void);

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);

			/** Copy parent attributes to another observer.
	        */
			virtual void copyParentAttributesTo (ParticleObserver* observer);

			/** Return the interval value, which defines at what interval the observer is called.
	        */
			Real getObserverInterval(void) const;

			/** Set the interval value, which defines at what interval the observer is called.
	        */
			void setObserverInterval(Real observerInterval);

			/** Return the value of mObserveUntilEvent.
	        */
			bool getObserveUntilEvent(void) const;

			/** Sets the value of mObserveUntilEvent. This value determines whether observation must be continued
				after an event ocurred and the event handlers are called.
	        */
			void setObserveUntilEvent(bool observeUntilEvent);

			/** Returns true if the particle type to observe specifically has been set.
	        */
			bool isParticleTypeToObserveSet(void) const;

		protected:
			ParticleTechnique* mParentTechnique;

			// Type of observer
			String mObserverType;

			// Name of the observer (optional)
			String mName;

			/** Determines whether an observer is activated.
	        */
			bool mEnabled;
			bool mOriginalEnabled;
			bool mOriginalEnabledSet;

			/** Determines whether the _observe() function must be executed.
			@remarks
				This is independent of mEnabled, which means that an observer can be enabled, but if mObserve has
				been set to false, it still doesn't observe. It is used to enable/disable execution of the _observe() 
				function in combination with the update interval.
	        */
			bool mObserve;

			/** Observes until an event takes place. If the event occurs, the event handlers are called and after that
				the observer doesn't observe anymore.
	        */
			bool mObserveUntilEvent;

			/** Flag that is set if the event handler(s) are called at least once.
	        */
			bool mEventHandlersExecuted;

			/** Although the scale is on a Particle System level, the observer can also be scaled.
			*/
			Vector3 _mObserverScale;

			// Particle type to be observed. Default is that all particles are observed.
			Particle::ParticleType mParticleTypeToObserve;

			/** Determines whether mParticleTypeToObserve is set. If ´true´, only that particles of the specified type
				are observed. If ´false´ (= default), all particles are observed.
			*/
			bool mParticleTypeToObserveSet;

			// List with EventHandlers, which will be triggered if the condition that this observer validates occurs.
			ParticleEventHandlerList mEventHandlers;

			/** Values that determine that the observer is called after every interval.
	        */
			Real mObserverInterval;
			Real mObserverIntervalRemainder;
			bool mObserverIntervalSet;

			/** Handle the observer implementation.
	        */
			virtual void _handleObserve (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** Handle the event.
			@remarks
				This function iterates over all at the observer registered handlers and executes them.				
	        */
			virtual void _handleEvent (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);
	};

}
#endif
