/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DObserver.h"
#include "Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DEventHandler.h"
#include "Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DEventHandlerManager.h"
#include "base/ccMacros.h"

NS_CC_BEGIN

// Constants
const bool PUParticle3DObserver::DEFAULT_ENABLED = true;
const PUParticle3D::ParticleType PUParticle3DObserver::DEFAULT_PARTICLE_TYPE = PUParticle3D::PT_VISUAL;
const float PUParticle3DObserver::DEFAULT_INTERVAL = 0.05f;
const bool PUParticle3DObserver::DEFAULT_UNTIL_EVENT = false;

//-----------------------------------------------------------------------
PUParticle3DObserver::PUParticle3DObserver(void) : 
    _particleSystem(nullptr),
    _enabled(DEFAULT_ENABLED),
    _originalEnabled(DEFAULT_ENABLED),
    _originalEnabledSet(false),
    _observe(true),
    _particleTypeToObserve(DEFAULT_PARTICLE_TYPE),
    _particleTypeToObserveSet(false),
    _observerScale(Vec3::ONE),
    _observerInterval(DEFAULT_INTERVAL),
    _observerIntervalRemainder(0.0),
    _observerIntervalSet(false),
    _observeUntilEvent(DEFAULT_UNTIL_EVENT),
    _eventHandlersExecuted(false)
{
    //mAliasType = AT_OBSERVER;
}
//-----------------------------------------------------------------------
PUParticle3DObserver::~PUParticle3DObserver(void)
{
    destroyAllEventHandlers();
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::notifyStart (void)
{
    _eventHandlersExecuted = false;
    _observe = true;
    setEnabled(_originalEnabled);
}
//-----------------------------------------------------------------------
bool PUParticle3DObserver::isEnabled(void) const
{
    return _enabled;
}
//-----------------------------------------------------------------------
bool PUParticle3DObserver::_getOriginalEnabled(void) const
{
    return _originalEnabled;
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::setEnabled(bool enabled)
{
    _enabled = enabled;
    if (!_originalEnabledSet)
    {
        // Only one time is permitted
        _originalEnabled = enabled;
        _originalEnabledSet = true;
    }
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::_resetEnabled(void)
{
    _originalEnabledSet = false;
}
//-----------------------------------------------------------------------
float PUParticle3DObserver::getObserverInterval(void) const
{
    return _observerInterval;
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::setObserverInterval(float observerInterval)
{
    _observerInterval = observerInterval;
    _observerIntervalSet = true;
}
//-----------------------------------------------------------------------
bool PUParticle3DObserver::getObserveUntilEvent(void) const
{
    return _observeUntilEvent;
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::setObserveUntilEvent(bool observeUntilEvent)
{
    _observeUntilEvent = observeUntilEvent;
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::notifyRescaled(const Vec3& scale)
{
    _observerScale = scale;

    if (_eventHandlers.empty())
        return;

    ParticleEventHandlerConstIterator it;
    ParticleEventHandlerConstIterator itEnd = _eventHandlers.end();
    for (it = _eventHandlers.begin(); it != itEnd; ++it)
    {
        (*it)->notifyRescaled(scale);
    }
}
//-----------------------------------------------------------------------
PUParticle3DEventHandler* PUParticle3DObserver::createEventHandler(const std::string& eventHandlerType)
{
    PUParticle3DEventHandler* eventHandler = PUParticle3DEventHandlerManager::Instance()->createEventHandler(eventHandlerType);
    addEventHandler(eventHandler);
    return eventHandler;
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::addEventHandler(PUParticle3DEventHandler* eventHandler)
{
    eventHandler->retain();
    _eventHandlers.push_back(eventHandler);
    eventHandler->setParentObserver(this);
    eventHandler->notifyRescaled(_observerScale);
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::removeEventHandler(PUParticle3DEventHandler* eventHandler)
{
    ParticleEventHandlerIterator it;
    for (it = _eventHandlers.begin(); it != _eventHandlers.end(); ++it)
    {
        if (*it == eventHandler)
        {
            // Remove it
            (*it)->release();
            _eventHandlers.erase(it);
            break;
        }
    }

    eventHandler->setParentObserver(0);
}
//-----------------------------------------------------------------------
PUParticle3DEventHandler* PUParticle3DObserver::getEventHandler (size_t index) const
{
    CCASSERT(index < _eventHandlers.size(), "EventHandler index out of bounds!");
    return _eventHandlers[index];
}
//-----------------------------------------------------------------------
PUParticle3DEventHandler* PUParticle3DObserver::getEventHandler (const std::string& eventHandlerName) const
{
    if (eventHandlerName.empty())
        return 0;

    ParticleEventHandlerConstIterator it;
    ParticleEventHandlerConstIterator itEnd = _eventHandlers.end();
    for (it = _eventHandlers.begin(); it != itEnd; ++it)
    {
        if ((*it)->getName() == eventHandlerName)
        {
            return *it;
        }
    }

    return 0;
}
//-----------------------------------------------------------------------
size_t PUParticle3DObserver::getNumEventHandlers (void) const
{
    return _eventHandlers.size();
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::destroyEventHandler(PUParticle3DEventHandler* eventHandler)
{
    CCASSERT(eventHandler, "EventHandler is null!");
    ParticleEventHandlerIterator it;
    for (it = _eventHandlers.begin(); it != _eventHandlers.end(); ++it)
    {
        if (*it == eventHandler)
        {
            // Detroy it
            //ParticleSystemManager::getSingletonPtr()->destroyEventHandler(*it);
            (*it)->release();
            _eventHandlers.erase(it);
            break;
        }
    }
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::destroyEventHandler (size_t index)
{
    destroyEventHandler(getEventHandler(index));
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::destroyAllEventHandlers (void)
{
    ParticleEventHandlerIterator it;
    for (it = _eventHandlers.begin(); it != _eventHandlers.end(); ++it)
    {
        (*it)->release();
        //ParticleSystemManager::getSingletonPtr()->destroyEventHandler(*it);
    }
    _eventHandlers.clear();
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::setParticleTypeToObserve(const PUParticle3D::ParticleType particleTypeToObserve)
{
    _particleTypeToObserve = particleTypeToObserve;
    _particleTypeToObserveSet = true;
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::handleObserve (PUParticle3D* particle, float timeElapsed)
{
    if (_enabled && _observe)
    {
        if (_observeUntilEvent && _eventHandlersExecuted)
        {
            // Don't continue if mObserveUntilEvent is set and the event handlers are already called once.
            return;
        }
        if (observe(particle, timeElapsed))
        {
            // Handle the event
            handleEvent (particle, timeElapsed);
        }
    }
}
//-----------------------------------------------------------------------
void PUParticle3DObserver::handleEvent (PUParticle3D* particle, float timeElapsed)
{
    if (_eventHandlers.empty())
        return;

    ParticleEventHandlerConstIterator it;
    ParticleEventHandlerConstIterator itEnd = _eventHandlers.end();
    for (it = _eventHandlers.begin(); it != itEnd; ++it)
    {
        (*it)->handle(_particleSystem, particle, timeElapsed);
    }
    _eventHandlersExecuted = true;
}
//-----------------------------------------------------------------------
bool PUParticle3DObserver::isParticleTypeToObserveSet(void) const
{
    return _particleTypeToObserveSet;
}

void PUParticle3DObserver::preUpdateObserver( float deltaTime )
{
    if (!_enabled)
        return;

    if (_observerIntervalSet)
    {
        _observerIntervalRemainder -= deltaTime;
        if (_observerIntervalRemainder < 0)
        {
            _observerIntervalRemainder += _observerInterval;
            _observe = true;
        }
        else
        {
            _observe = false;
        }
    }
}

void PUParticle3DObserver::updateObserver( PUParticle3D *particle, float deltaTime, bool firstParticle )
{
    if (!_enabled)
        return;

    // Call the _firstParticle() function if the first particle in the update loop is encountered.
    if (firstParticle)
    {
        firstParticleUpdate(particle, deltaTime);
    }

    if (_particleTypeToObserveSet && particle->particleType != _particleTypeToObserve)
        return;

    // Observe
    handleObserve(particle, deltaTime);
}

void PUParticle3DObserver::postUpdateObserver( float deltaTime )
{

}

void PUParticle3DObserver::firstParticleUpdate( PUParticle3D *particle, float deltaTime )
{

}

void PUParticle3DObserver::copyAttributesTo( PUParticle3DObserver* observer )
{
    // Copy attributes
    observer->setName(_name);
    observer->_particleTypeToObserve = _particleTypeToObserve;
    observer->_particleTypeToObserveSet = _particleTypeToObserveSet;
    observer->_particleSystem = _particleSystem;
    observer->_observerScale = _observerScale;
    observer->_observerInterval = _observerInterval;
    observer->_observerIntervalRemainder = _observerIntervalRemainder;
    observer->_observerIntervalSet = _observerIntervalSet;
    observer->_observeUntilEvent = _observeUntilEvent;
    observer->_eventHandlersExecuted = _eventHandlersExecuted;
    observer->_enabled = _enabled;
    observer->_originalEnabled = _originalEnabled;
    observer->_originalEnabledSet = _originalEnabledSet;

    // Copy event handlers
    size_t i = 0;
    PUParticle3DEventHandler* eventHandler = 0;
    for(i = 0; i < getNumEventHandlers(); ++i)
    {
        eventHandler = getEventHandler(i);
        PUParticle3DEventHandler *clonedEventHandler = PUParticle3DEventHandlerManager::Instance()->createEventHandler(eventHandler->getEventHandlerType());
        eventHandler->copyAttributesTo(clonedEventHandler);
        observer->addEventHandler(clonedEventHandler);
    }
}

NS_CC_END
