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

#ifndef __CC_PU_PARTICLE_3D_ON_TIME_OBSERVER_H__
#define __CC_PU_PARTICLE_3D_ON_TIME_OBSERVER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUObserver.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUParticleSystem3D;
class CC_DLL PUOnTimeObserver : public PUObserver
{
public:
    // Constants
    static const float DEFAULT_THRESHOLD;
    static const bool DEFAULT_SINCE_START_SYSTEM;

    static PUOnTimeObserver* create();

    /** In case there are no particles, but the observation returns true, the event handlers must still be
        called.
    */
    virtual void preUpdateObserver(float deltaTime) override;

    /** 
    */
    virtual bool observe (PUParticle3D* particle, float timeElapsed) override;

    /** 
    */
    float getThreshold(void) const {return _threshold;};
    void setThreshold(float threshold){_threshold = threshold;};

    /** 
    */
    const PUComparisionOperator getCompare(void) const {return _compare;};
    void setCompare(PUComparisionOperator op){_compare = op;};

    /** 
    */
    bool isSinceStartSystem(void) const {return _sinceStartSystem;};
    void setSinceStartSystem(bool sinceStartSystem){_sinceStartSystem = sinceStartSystem;};

    virtual void copyAttributesTo (PUObserver* observer) override;

CC_CONSTRUCTOR_ACCESS:
    PUOnTimeObserver(void);
    virtual ~PUOnTimeObserver(void) {};

protected:
    float _threshold;
    PUComparisionOperator _compare;
    bool _sinceStartSystem;
};

NS_CC_END

#endif
