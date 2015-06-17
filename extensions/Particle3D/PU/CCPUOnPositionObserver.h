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

#ifndef __CC_PU_PARTICLE_3D_ON_POSITION_OBSERVER_H__
#define __CC_PU_PARTICLE_3D_ON_POSITION_OBSERVER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUObserver.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUParticleSystem3D;
class CC_DLL PUOnPositionObserver : public PUObserver
{
public:
    // Constants
    static const Vec3 DEFAULT_POSITION_THRESHOLD;

    static PUOnPositionObserver* create();

    /** 
    */
    virtual bool observe (PUParticle3D* particle, float timeElapsed) override;

    /** 
        */
    void setPositionXThreshold(float threshold){_positionXThreshold = threshold; _positionXThresholdSet = true;};
    void setPositionYThreshold(float threshold){_positionYThreshold = threshold; _positionYThresholdSet = true;};
    void setPositionZThreshold(float threshold){_positionZThreshold = threshold; _positionZThresholdSet = true;};

    /** 
        */
    float getPositionXThreshold(void) const {return _positionXThreshold;};
    float getPositionYThreshold(void) const {return _positionYThreshold;};
    float getPositionZThreshold(void) const {return _positionZThreshold;};

    /** 
        */
    bool isPositionXThresholdSet(void) const {return _positionXThresholdSet;};
    bool isPositionYThresholdSet(void) const {return _positionYThresholdSet;};
    bool isPositionZThresholdSet(void) const {return _positionZThresholdSet;};

    /** 
        */
    void resetPositionXThreshold(void) {_positionXThresholdSet = false;};
    void resetPositionYThreshold(void) {_positionYThresholdSet = false;};
    void resetPositionZThreshold(void) {_positionZThresholdSet = false;};

    /** 
        */
    void setComparePositionX(PUComparisionOperator op){_comparePositionX = op;};
    void setComparePositionY(PUComparisionOperator op){_comparePositionY = op;};
    void setComparePositionZ(PUComparisionOperator op){_comparePositionZ = op;};

    /** 
        */
    const PUComparisionOperator getComparePositionX(void) const {return _comparePositionX;};
    const PUComparisionOperator getComparePositionY(void) const {return _comparePositionY;};
    const PUComparisionOperator getComparePositionZ(void) const {return _comparePositionZ;};

    virtual void copyAttributesTo (PUObserver* observer) override;

CC_CONSTRUCTOR_ACCESS:
    PUOnPositionObserver(void);
    virtual ~PUOnPositionObserver(void) {};

protected:

    float _positionXThreshold;
    float _positionYThreshold;
    float _positionZThreshold;
    bool _positionXThresholdSet;
    bool _positionYThresholdSet;
    bool _positionZThresholdSet;
    PUComparisionOperator _comparePositionX;
    PUComparisionOperator _comparePositionY;
    PUComparisionOperator _comparePositionZ;

};

NS_CC_END

#endif
