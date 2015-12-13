/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#ifndef __CC_PU_PARTICLE_3D_OBSERVER_H__
#define __CC_PU_PARTICLE_3D_OBSERVER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUParticleSystem3D;
class PUEventHandler;

enum PUComparisionOperator
{
    CO_LESS_THAN,
    CO_EQUALS,
    CO_GREATER_THAN
};

class CC_DLL PUObserver : public Ref
{
    friend class PUParticleSystem3D;
public:
    // Default values
    static const bool DEFAULT_ENABLED;
    static const PUParticle3D::ParticleType DEFAULT_PARTICLE_TYPE;
    static const float DEFAULT_INTERVAL;
    static const bool DEFAULT_UNTIL_EVENT;

    typedef std::vector<PUEventHandler*>::iterator ParticleEventHandlerIterator;
    typedef std::vector<PUEventHandler*>::const_iterator ParticleEventHandlerConstIterator;
    typedef std::vector<PUEventHandler*> ParticleEventHandlerList;

    /** Todo
    */
    const std::string& getObserverType(void) const {return _observerType;};
    void setObserverType(const std::string& observerType) {_observerType = observerType;};

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

    ///** Todo
    //*/
    //PUParticleSystem3D* getParentSystem(void) const {return mParentTechnique;};
    //void setParentSystem(PUParticleSystem3D* parentTechnique){mParentTechnique = parentTechnique;};

    /** Todo
    */
    const std::string& getName(void) const {return _name;};
    void setName(const std::string& name) {_name = name;};

    /** Todo
    */
    const PUParticle3D::ParticleType& getParticleTypeToObserve(void) const {return _particleTypeToObserve;};
    void setParticleTypeToObserve(const PUParticle3D::ParticleType particleTypeToObserve);


    virtual void notifyStart (void);
    virtual void notifyStop (void){/* Do nothing */};
    virtual void notifyRescaled(const Vec3& scale);
    virtual void preUpdateObserver(float deltaTime);
    virtual void updateObserver(PUParticle3D *particle, float deltaTime, bool firstParticle);
    virtual void postUpdateObserver(float deltaTime);
    virtual void firstParticleUpdate(PUParticle3D *particle, float deltaTime);

    /** This function determines whether a condition (the event) is true or false.
    */
    virtual bool observe (PUParticle3D* particle, float timeElapsed) = 0;

    /** Todo
    */
    PUEventHandler* createEventHandler(const std::string& eventHandlerType);

    /** Todo
    */
    void addEventHandler(PUEventHandler* eventHandler);

    /** Todo
    */
    void removeEventHandler(PUEventHandler* eventHandler);

    /** Todo
    */
    PUEventHandler* getEventHandler (size_t index) const;

    /** Todo
    */
    PUEventHandler* getEventHandler (const std::string& eventHandlerName) const;

    /** Todo
    */
    size_t getNumEventHandlers (void) const;

    /** Todo
    */
    void destroyEventHandler(PUEventHandler* eventHandler);

    /** Todo
    */
    void destroyEventHandler (size_t index);

    /** Todo
    */
    void destroyAllEventHandlers (void);

    /** Return the interval value, which defines at what interval the observer is called.
    */
    float getObserverInterval(void) const;

    /** Set the interval value, which defines at what interval the observer is called.
    */
    void setObserverInterval(float observerInterval);

    /** Return the value of mObserveUntilEvent.
    */
    bool getObserveUntilEvent(void) const;

    /** Sets the value of mObserveUntilEvent. This value determines whether observation must be continued
        after an event occurred and the event handlers are called.
    */
    void setObserveUntilEvent(bool observeUntilEvent);

    /** Returns true if the particle type to observe specifically has been set.
    */
    bool isParticleTypeToObserveSet(void) const;

    virtual void copyAttributesTo (PUObserver* observer);

CC_CONSTRUCTOR_ACCESS:
    PUObserver(void);
    virtual ~PUObserver(void);

protected:

    PUParticleSystem3D* _particleSystem;

    // Type of observer
    std::string _observerType;

    // Name of the observer (optional)
    std::string _name;

    /** Determines whether an observer is activated.
    */
    bool _enabled;
    bool _originalEnabled;
    bool _originalEnabledSet;

    /** Determines whether the _observe() function must be executed.
    @remarks
        This is independent of mEnabled, which means that an observer can be enabled, but if mObserve has
        been set to false, it still doesn't observe. It is used to enable/disable execution of the _observe() 
        function in combination with the update interval.
    */
    bool _observe;

    /** Observes until an event takes place. If the event occurs, the event handlers are called and after that
        the observer doesn't observe anymore.
    */
    bool _observeUntilEvent;

    /** Flag that is set if the event handler(s) are called at least once.
    */
    bool _eventHandlersExecuted;

    /** Although the scale is on a Particle System level, the observer can also be scaled.
    */
    Vec3 _observerScale;

    // Particle type to be observed. Default is that all particles are observed.
    PUParticle3D::ParticleType _particleTypeToObserve;

    /** Determines whether mParticleTypeToObserve is set. If true only that particles of the specified type
        are observed. If false (= default), all particles are observed.
    */
    bool _particleTypeToObserveSet;

    // List with EventHandlers, which will be triggered if the condition that this observer validates occurs.
    ParticleEventHandlerList _eventHandlers;

    /** Values that determine that the observer is called after every interval.
    */
    float _observerInterval;
    float _observerIntervalRemainder;
    bool _observerIntervalSet;

    /** Handle the observer implementation.
    */
    virtual void handleObserve (PUParticle3D* particle, float timeElapsed);

    /** Handle the event.
    @remarks
        This function iterates over all at the observer registered handlers and executes them.				
    */
    virtual void handleEvent (PUParticle3D* particle, float timeElapsed);
};

NS_CC_END

#endif
