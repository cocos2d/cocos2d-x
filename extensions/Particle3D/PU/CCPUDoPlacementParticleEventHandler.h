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

#ifndef __CC_PU_PARTICLE_3D_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_H__
#define __CC_PU_PARTICLE_3D_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUListener.h"
#include "extensions/Particle3D/PU/CCPUEventHandler.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUObserver;
class PUEmitter;
class PUParticleSystem3D;

class CC_DLL PUDoPlacementParticleEventHandler : public PUEventHandler, public PUListener
{
public:
    // Constants
    static const unsigned int DEFAULT_NUMBER_OF_PARTICLES;

    static PUDoPlacementParticleEventHandler* create();

    /** Getters/Setters
    */
    bool isInheritPosition(void) const {return _inheritPosition;};
    bool isInheritDirection(void) const {return _inheritDirection;};
    bool isInheritOrientation(void) const {return _inheritOrientation;};
    bool isInheritTimeToLive(void) const {return _inheritTimeToLive;};
    bool isInheritMass(void) const {return _inheritMass;};
    bool isInheritTextureCoordinate(void) const {return _inheritTextureCoordinate;};
    bool isInheritColour(void) const {return _inheritColour;};
    bool isInheritParticleWidth(void) const {return _inheritParticleWidth;};
    bool isInheritParticleHeight(void) const {return _inheritParticleHeight;};
    bool isInheritParticleDepth(void) const {return _inheritParticleDepth;};

    void setInheritPosition(bool inheritPosition) {_inheritPosition = inheritPosition;};
    void setInheritDirection(bool inheritDirection) {_inheritDirection = inheritDirection;};
    void setInheritOrientation(bool inheritOrientation) {_inheritOrientation = inheritOrientation;};
    void setInheritTimeToLive(bool inheritTimeToLive) {_inheritTimeToLive = inheritTimeToLive;};
    void setInheritMass(bool inheritMass) {_inheritMass = inheritMass;};
    void setInheritTextureCoordinate(bool inheritTextureCoordinate) {_inheritTextureCoordinate = inheritTextureCoordinate;};
    void setInheritColour(bool inheritColour) {_inheritColour = inheritColour;};
    void setInheritParticleWidth(bool inheritParticleWidth) {_inheritParticleWidth = inheritParticleWidth;};
    void setInheritParticleHeight(bool inheritParticleHeight) {_inheritParticleHeight = inheritParticleHeight;};
    void setInheritParticleDepth(bool inheritParticleDepth) {_inheritParticleDepth = inheritParticleDepth;};

    /** Get the name of the emitter that is used to emit its particles.
    */
    const std::string& getForceEmitterName(void) const {return _forceEmitterName;};

    /** Set the name of the emitter that is used to emit its particles.
    */
    void setForceEmitterName(const std::string& forceEmitterName);

    /** Returns a pointer to the emitter that is used as a force emitter.
    */
    PUEmitter* getForceEmitter(void) const;

    /** Remove this as a listener from the technique.
    @remarks
        If a new force-emitter name has been set, the removeAsListener must be called, to remove the DoPlacementParticleEventHandler
        from the old technique (to which the force-emitter belongs. Only then the new force-emitter is used. 
        The reason why it is not called automatically in the setForceEmitterName() function is to offer some flexibility on 
        the moment the removeAsListener() is called.
    */
    void removeAsListener(void);

    /** Get the number of particles to emit.
    */
    unsigned int getNumberOfParticles(void) const {return _numberOfParticles;};

    /** Set the number of particles to emit.
    */
    void setNumberOfParticles(unsigned int numberOfParticles){_numberOfParticles = numberOfParticles;};

    /** Boolean that determines whether always the position of the particle that is handled must be used for emission of 
        the new particle.
    */
    bool alwaysUsePosition(void) const {return _alwaysUsePosition;};

    /** Set the boolean to indicate whether the position of the particle that is handled must be used for emission of 
        the new particle or whether the contact point of the physics actor must be used. This only applies if a physics angine
        is used, otherwise the default is used.
    */
    void setAlwaysUsePosition(bool alwaysUsePosition) {_alwaysUsePosition = alwaysUsePosition;};

    /** If the _handle() function of this class is invoked (by an Observer), it searches the 
        ParticleEmitter defined by the mForceEmitterName. This ParticleEmitter is either part of 
        the ParticleTechnique in which the DoPlacementParticleEventHandler is defined, and if the ParticleEmitter
        is not found, other ParticleTechniques are searched. The ParticleEmitter is 'forced' to emit the
        requested number of particles.
    */
    virtual void handle (PUParticleSystem3D* particleSystem, PUParticle3D* particle, float timeElapsed) override;

    /** Initialise the emitted particle. This means that its position is set.
    */
    virtual void particleEmitted(PUParticleSystem3D* particleSystem, PUParticle3D* particle) override;

    /** No implementation.
    */
    virtual void particleExpired(PUParticleSystem3D* particleSystem, PUParticle3D* particle) override {};

    virtual void copyAttributesTo (PUEventHandler* eventHandler) override;

CC_CONSTRUCTOR_ACCESS:
    PUDoPlacementParticleEventHandler(void);
    virtual ~PUDoPlacementParticleEventHandler(void);

protected:
    // Identifies the name of emitter
    std::string _forceEmitterName;

    // The number of particles to emit
    unsigned int _numberOfParticles;

    /** Store the technique value to keep up to speed.
    @remarks
        If the ParticleTechnique has been destroyed, the DoPlacementParticleEventHandler isn´t automatically
        notified. Using the pointer causes an exception.
    */
    PUParticleSystem3D* _system;

    /** Store the emitter value to keep up to speed.
    @remarks
        If the ParticleEmitter has been destroyed, the DoPlacementParticleEventHandler isn´t automatically
        notified. Using the pointer causes an exception.
    */
    PUEmitter* _emitter;

    /** Used to determine whether the emitter used by the DoPlacementParticleEventHandler, is already found.
    */
    bool _found;

    /** By default the place where to put a new particle is on the position of the particle in the _handle function. If 
        mAlwaysUsePosition is set to false, it tries the contact point of the physics actor that is associated with the 
        particle.
    */
    bool _alwaysUsePosition;

    /** The base particle from which the attributes are inherited
    */
    PUParticle3D* _baseParticle;

    /** These flags are used to determine which attributes must be inherited from the base particle.
    */
    bool _inheritPosition;
    bool _inheritDirection;
    bool _inheritOrientation;
    bool _inheritTimeToLive;
    bool _inheritMass;
    bool _inheritTextureCoordinate;
    bool _inheritColour;
    bool _inheritParticleWidth;
    bool _inheritParticleHeight;
    bool _inheritParticleDepth;

};

NS_CC_END

#endif
