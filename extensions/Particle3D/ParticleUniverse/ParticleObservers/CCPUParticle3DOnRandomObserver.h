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

#ifndef __CC_PU_PARTICLE_3D_ON_RANDOM_OBSERVER_H__
#define __CC_PU_PARTICLE_3D_ON_RANDOM_OBSERVER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DObserver.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUParticleSystem3D;
class CC_DLL PUParticle3DOnRandomObserver : public PUParticle3DObserver
{
public:
    // Constants
    static const float DEFAULT_THRESHOLD;

    static PUParticle3DOnRandomObserver* create();

    /** See ParticleObserver::_preProcessParticles()
    */
    virtual void preUpdateObserver(float deltaTime) override;

    /** See ParticleObserver::_processParticle()
    */
    virtual void updateObserver(PUParticle3D *particle, float deltaTime, bool firstParticle) override;

    /** 
    */
    virtual bool observe (PUParticle3D* particle, float timeElapsed) override;

    /** 
    */
    float getThreshold(void) const {return _threshold;};
    void setThreshold(float threshold){_threshold = threshold;};

    virtual void copyAttributesTo (PUParticle3DObserver* observer);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DOnRandomObserver(void);
    virtual ~PUParticle3DOnRandomObserver(void) {};

protected:
    float _threshold; // Value between 0..1
};

NS_CC_END

#endif
