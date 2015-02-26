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


#ifndef __CC_PU_PARTICLE_3D_PARTICLE_FOLLOWER_H__
#define __CC_PU_PARTICLE_3D_PARTICLE_FOLLOWER_H__

#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  CC_DLL PUParticle3DParticleFollower : public PUParticle3DAffector
{
public:
    // Constants
    static const float DEFAULT_MAX_DISTANCE;
    static const float DEFAULT_MIN_DISTANCE;

    static PUParticle3DParticleFollower* create();

    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;
    virtual void firstParticleUpdate(PUParticle3D *particle, float deltaTime) override;

    /** 
    */
    float getMaxDistance(void) const;
    void setMaxDistance(float maxDistance);

    /** 
    */
    float getMinDistance(void) const;
    void setMinDistance(float minDistance);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DParticleFollower(void);
    virtual ~PUParticle3DParticleFollower(void);

protected:
    float _minDistance;
    float _maxDistance;
    Vec3 _positionPreviousParticle;
    bool _first;
};
NS_CC_END

#endif