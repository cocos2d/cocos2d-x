/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	// Constants
	const bool ParticleObserver::DEFAULT_ENABLED = true;
	const Particle::ParticleType ParticleObserver::DEFAULT_PARTICLE_TYPE = Particle::PT_VISUAL;
	const Real ParticleObserver::DEFAULT_INTERVAL = 0.05f;
	const bool ParticleObserver::DEFAULT_UNTIL_EVENT = false;

	//-----------------------------------------------------------------------
	ParticleObserver::ParticleObserver(void) : 
		IAlias(),
		IElement(),
		mParentTechnique(0),
		mEnabled(DEFAULT_ENABLED),
		mOriginalEnabled(DEFAULT_ENABLED),
		mOriginalEnabledSet(false),
		mObserve(true),
		mParticleTypeToObserve(DEFAULT_PARTICLE_TYPE),
		mParticleTypeToObserveSet(false),
		mName(StringUtil::BLANK),
		_mObserverScale(Vector3::UNIT_SCALE),
		mObserverInterval(DEFAULT_INTERVAL),
		mObserverIntervalRemainder(0.0),
		mObserverIntervalSet(false),
		mObserveUntilEvent(DEFAULT_UNTIL_EVENT),
		mEventHandlersExecuted(false)
	{
		mAliasType = AT_OBSERVER;
	}
	//-----------------------------------------------------------------------
	ParticleObserver::~ParticleObserver(void)
	{
		destroyAllEventHandlers();
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::_notifyStart (void)
	{
		mEventHandlersExecuted = false;
		mObserve = true;
		setEnabled(mOriginalEnabled);
	}
	//-----------------------------------------------------------------------
	bool ParticleObserver::isEnabled(void) const
	{
		return mEnabled;
	}
	//-----------------------------------------------------------------------
	bool ParticleObserver::_getOriginalEnabled(void) const
	{
		return mOriginalEnabled;
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::setEnabled(bool enabled)
	{
		mEnabled = enabled;
		if (!mOriginalEnabledSet)
		{
			// Only one time is permitted
			mOriginalEnabled = enabled;
			mOriginalEnabledSet = true;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::_resetEnabled(void)
	{
		mOriginalEnabledSet = false;
	}
	//-----------------------------------------------------------------------
	Real ParticleObserver::getObserverInterval(void) const
	{
		return mObserverInterval;
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::setObserverInterval(Real observerInterval)
	{
		mObserverInterval = observerInterval;
		mObserverIntervalSet = true;
	}
	//-----------------------------------------------------------------------
	bool ParticleObserver::getObserveUntilEvent(void) const
	{
		return mObserveUntilEvent;
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::setObserveUntilEvent(bool observeUntilEvent)
	{
		mObserveUntilEvent = observeUntilEvent;
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::_notifyRescaled(const Vector3& scale)
	{
		_mObserverScale = scale;

		if (mEventHandlers.empty())
			return;

		ParticleEventHandlerConstIterator it;
		ParticleEventHandlerConstIterator itEnd = mEventHandlers.end();
		for (it = mEventHandlers.begin(); it != itEnd; ++it)
		{
			(*it)->_notifyRescaled(scale);
		}
	}
	//-----------------------------------------------------------------------
	ParticleEventHandler* ParticleObserver::createEventHandler(const String& eventHandlerType)
	{
		assert(eventHandlerType != StringUtil::BLANK && "eventHandlerType is empty!");
		ParticleEventHandler* eventHandler = ParticleSystemManager::getSingletonPtr()->createEventHandler(eventHandlerType);
		addEventHandler(eventHandler);
		return eventHandler;
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::addEventHandler(ParticleEventHandler* eventHandler)
	{
		assert(eventHandler && "EventHandler is null!");
		mEventHandlers.push_back(eventHandler);
		eventHandler->setParentObserver(this);
		eventHandler->_notifyRescaled(_mObserverScale);
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::removeEventHandler(ParticleEventHandler* eventHandler)
	{
		assert(eventHandler && "EventHandler is null!");
		ParticleEventHandlerIterator it;
		for (it = mEventHandlers.begin(); it != mEventHandlers.end(); ++it)
		{
			if (*it == eventHandler)
			{
				// Remove it
				mEventHandlers.erase(it);
				break;
			}
		}

		eventHandler->setParentObserver(0);
	}
	//-----------------------------------------------------------------------
	ParticleEventHandler* ParticleObserver::getEventHandler (size_t index) const
	{
		assert(index < mEventHandlers.size() && "EventHandler index out of bounds!");
		return mEventHandlers[index];
	}
	//-----------------------------------------------------------------------
	ParticleEventHandler* ParticleObserver::getEventHandler (const String& eventHandlerName) const
	{
		if (eventHandlerName == StringUtil::BLANK)
			return 0;

		ParticleEventHandlerConstIterator it;
		ParticleEventHandlerConstIterator itEnd = mEventHandlers.end();
		for (it = mEventHandlers.begin(); it != itEnd; ++it)
		{
			if ((*it)->getName() == eventHandlerName)
			{
				return *it;
			}
		}
		
		return 0;
	}
	//-----------------------------------------------------------------------
	size_t ParticleObserver::getNumEventHandlers (void) const
	{
		return mEventHandlers.size();
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::destroyEventHandler(ParticleEventHandler* eventHandler)
	{
		assert(eventHandler && "EventHandler is null!");
		ParticleEventHandlerIterator it;
		for (it = mEventHandlers.begin(); it != mEventHandlers.end(); ++it)
		{
			if (*it == eventHandler)
			{
				// Detroy it
				ParticleSystemManager::getSingletonPtr()->destroyEventHandler(*it);
				mEventHandlers.erase(it);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::destroyEventHandler (size_t index)
	{
		destroyEventHandler(getEventHandler(index));
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::destroyAllEventHandlers (void)
	{
		ParticleEventHandlerIterator it;
		for (it = mEventHandlers.begin(); it != mEventHandlers.end(); ++it)
		{
			ParticleSystemManager::getSingletonPtr()->destroyEventHandler(*it);
		}
		mEventHandlers.clear();
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::copyAttributesTo(ParticleObserver* observer)
	{
		copyParentAttributesTo(observer);
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::copyParentAttributesTo(ParticleObserver* observer)
	{
		// Copy attributes
		observer->setName(mName);
		observer->mParticleTypeToObserve = mParticleTypeToObserve;
		observer->mParticleTypeToObserveSet = mParticleTypeToObserveSet;
		observer->mParentTechnique = mParentTechnique;
		observer->_mObserverScale = _mObserverScale;
		observer->mObserverInterval = mObserverInterval;
		observer->mObserverIntervalRemainder = mObserverIntervalRemainder;
		observer->mObserverIntervalSet = mObserverIntervalSet;
		observer->mObserveUntilEvent = mObserveUntilEvent;
		observer->mEventHandlersExecuted = mEventHandlersExecuted;
        observer->mEnabled = mEnabled;
		observer->mOriginalEnabled = mOriginalEnabled;
		observer->mOriginalEnabledSet = mOriginalEnabledSet;

		// Copy event handlers
		size_t i = 0;
		ParticleEventHandler* eventHandler = 0;
		ParticleEventHandler* clonedEventHandler = 0;
		for(i = 0; i < getNumEventHandlers(); ++i)
		{
			eventHandler = getEventHandler(i);
			clonedEventHandler = ParticleSystemManager::getSingletonPtr()->cloneEventHandler(eventHandler);
			observer->addEventHandler(clonedEventHandler);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::setParticleTypeToObserve(const Particle::ParticleType particleTypeToObserve)
	{
		mParticleTypeToObserve = particleTypeToObserve;
		mParticleTypeToObserveSet = true;
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::_preProcessParticles(ParticleTechnique* technique, Real timeElapsed)
	{
		if (!mEnabled)
			return;

		if (mObserverIntervalSet)
		{
			mObserverIntervalRemainder -= timeElapsed;
			if (mObserverIntervalRemainder < 0)
			{
				mObserverIntervalRemainder += mObserverInterval;
				mObserve = true;
			}
			else
			{
				mObserve = false;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::_processParticle(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed, bool firstParticle)
	{
		if (!mEnabled)
			return;

		// Call the _firstParticle() function if the first particle in the update loop is encountered.
		if (firstParticle)
		{
			_firstParticle(particleTechnique, particle, timeElapsed);
		}

		if (mParticleTypeToObserveSet && particle->particleType != mParticleTypeToObserve)
			return;

		// Observe
		_handleObserve(particleTechnique, particle, timeElapsed);
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::_handleObserve (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (mEnabled && mObserve)
		{
			if (mObserveUntilEvent && mEventHandlersExecuted)
			{
				// Don't continue if mObserveUntilEvent is set and the event handlers are already called once.
				return;
			}
			if (_observe(particleTechnique, particle, timeElapsed))
			{
				// Handle the event
				_handleEvent (particleTechnique, particle, timeElapsed);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleObserver::_handleEvent (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (mEventHandlers.empty())
			return;

		ParticleEventHandlerConstIterator it;
		ParticleEventHandlerConstIterator itEnd = mEventHandlers.end();
		for (it = mEventHandlers.begin(); it != itEnd; ++it)
		{
			(*it)->_handle(particleTechnique, particle, timeElapsed);
		}
		mEventHandlersExecuted = true;
	}
	//-----------------------------------------------------------------------
	bool ParticleObserver::isParticleTypeToObserveSet(void) const
	{
		return mParticleTypeToObserveSet;
	}

}
