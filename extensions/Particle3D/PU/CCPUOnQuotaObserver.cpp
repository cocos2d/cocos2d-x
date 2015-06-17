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

#include "extensions/Particle3D/PU/CCPUOnQuotaObserver.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

//-----------------------------------------------------------------------
bool PUOnQuotaObserver::observe (PUParticle3D* particle, float timeElapsed)
{
    return _result;
}
//-----------------------------------------------------------------------
void PUOnQuotaObserver::postUpdateObserver(float deltaTime)
{
    _result = false;
    unsigned int quota = 0;
    if (_particleTypeToObserveSet)
    {
        // Type to observe is set, so validate only that one
        switch (_particleTypeToObserve)
        {
        case PUParticle3D::PT_VISUAL:
            quota = _particleSystem->getParticleQuota();
            break;
        case PUParticle3D::PT_EMITTER:
            quota = static_cast<PUParticleSystem3D *>(_particleSystem)->getEmittedEmitterQuota();
            break;
        //case PUParticle3D::PT_AFFECTOR:
        //	quota = particleTechnique->getEmittedAffectorQuota();
        //	break;
        case PUParticle3D::PT_TECHNIQUE:
            quota = static_cast<PUParticleSystem3D *>(_particleSystem)->getEmittedSystemQuota();
            break;
        //case PUParticle3D::PT_SYSTEM:
        //	quota = particleTechnique->getEmittedAffectorQuota();
        //	break;
        default:
            break;
        }

        //_result = particleTechnique->getNumberOfEmittedParticles(_particleTypeToObserve) >= quota;
        _result = static_cast<PUParticleSystem3D *>(_particleSystem)->getAliveParticleCount() >= quota;
    }
    else
    {
        // Type to observe is not set, so check them all
        //quota = particleTechnique->getVisualParticleQuota() + 
        //	particleTechnique->getEmittedEmitterQuota() + 
        //	particleTechnique->getEmittedTechniqueQuota() + 
        //	particleTechnique->getEmittedAffectorQuota() +
        //	particleTechnique->getEmittedSystemQuota();
        quota = _particleSystem->getParticleQuota()
            + static_cast<PUParticleSystem3D *>(_particleSystem)->getEmittedEmitterQuota()
            + static_cast<PUParticleSystem3D *>(_particleSystem)->getEmittedSystemQuota();
        //_result = particleTechnique->getNumberOfEmittedParticles() >= quota;
        _result = static_cast<PUParticleSystem3D *>(_particleSystem)->getAliveParticleCount() >= quota;
    }
}

PUOnQuotaObserver* PUOnQuotaObserver::create()
{
    auto pqo = new (std::nothrow) PUOnQuotaObserver();
    pqo->autorelease();
    return pqo;
}

NS_CC_END
