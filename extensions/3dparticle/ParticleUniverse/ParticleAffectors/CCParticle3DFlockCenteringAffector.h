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


#ifndef __CC_PU_PARTICLE_3D_FLOCK_CENTERING_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_FLOCK_CENTERING_AFFECTOR_H__

#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"

NS_CC_BEGIN

class  Particle3DFlockCenteringAffector : public PUParticle3DAffector
{
public:
    Particle3DFlockCenteringAffector();
    virtual ~Particle3DFlockCenteringAffector();

    virtual void preUpdateAffector(float deltaTime) override;
    virtual void updateAffector(PUParticle3D *particle, float deltaTime) override;

protected:

    Vec3 _sum;
    Vec3 _average;
    float _count;
};
NS_CC_END

#endif