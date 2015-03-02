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

#ifndef __CC_PU_PARTICLE_3D_OBSERVER_MANAGER_H__
#define __CC_PU_PARTICLE_3D_OBSERVER_MANAGER_H__

#include "base/CCRef.h"
#include "Particle3D/ParticleUniverse/CCPUParticle3DScriptTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnClearObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnCollisionObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnCountObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnEmissionObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnEventFlagObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnExpireObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnPositionObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnQuotaObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnRandomObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnTimeObserverTranslator.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnVelocityObserverTranslator.h"


NS_CC_BEGIN
class PUParticle3DObserverManager
{
public:
    
    static PUParticle3DObserverManager* Instance();

    /**
     */
    PUScriptTranslator* getTranslator(const std::string &type);
    PUParticle3DObserver* createObserver(const std::string &type);

    
CC_CONSTRUCTOR_ACCESS:

    PUParticle3DObserverManager();
    ~PUParticle3DObserverManager();

protected:

    PUParticle3DOnClearObserverTranslator _onClearObserverTranslator;
    PUParticle3DOnCollisionObserverTranslator _onCollisionObserverTranslator;
    PUParticle3DOnCountObserverTranslator _onCountObserverTranslator;
    PUParticle3DOnEmissionObserverTranslator _onEmissionObserverTranslator;
    PUParticle3DOnEventFlagObserverTranslator _onEventFlagObserverTranslator;
    PUParticle3DOnExpireObserverTranslator _onExpireObserverTranslator;
    PUParticle3DOnPositionObserverTranslator _onPositionObserverTranslator;
    PUParticle3DOnQuotaObserverTranslator _onQuotaObserverTranslator;
    PUParticle3DOnRandomObserverTranslator _onRandomObserverTranslator;
    PUParticle3DOnTimeObserverTranslator _onTimeObserverTranslator;
    PUParticle3DOnVelocityObserverTranslator _onVelocityObserverTranslator;
};

NS_CC_END


#endif 
