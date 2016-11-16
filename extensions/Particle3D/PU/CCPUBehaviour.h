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

#ifndef __CC_PU_PARTICLE_3D_BEHAVIOUR_H__
#define __CC_PU_PARTICLE_3D_BEHAVIOUR_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUParticleSystem3D;

class CC_DLL PUBehaviour : public Ref
{
    friend class PUParticleSystem3D;
public:

    /** Todo
    */
    const std::string& getBehaviourType(void) const {return _behaviourType;};
    void setBehaviourType(const std::string& behaviourType) {_behaviourType = behaviourType;};

    /** Notify that the Behaviour is rescaled.
    */
    virtual void notifyRescaled(const Vec3& scale){_behaviourScale = scale;};

    virtual void prepare() {};
    virtual void unPrepare() {};

    virtual void updateBehaviour(PUParticle3D *particle, float deltaTime);

    /** Perform initialising activities as soon as the particle with which the ParticleBehaviour is
        associated, is emitted.
    */
    
    virtual void initParticleForEmission(PUParticle3D* particle);
    /** Perform some action if a particle expires.
    */
    virtual void initParticleForExpiration(PUParticle3D* particle, float timeElapsed);

    virtual PUBehaviour* clone();
    virtual void copyAttributesTo (PUBehaviour* behaviour);

CC_CONSTRUCTOR_ACCESS:
    PUBehaviour(void);
    virtual ~PUBehaviour(void);

protected:
    PUParticleSystem3D* _particleSystem;

    // Type of behaviour
    std::string _behaviourType;

    /** Although the scale is on a Particle System level, the behaviour can also be scaled.
    */
    Vec3 _behaviourScale;
};

NS_CC_END

#endif
