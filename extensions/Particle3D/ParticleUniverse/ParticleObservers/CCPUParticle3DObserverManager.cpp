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

#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DObserverManager.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnClearObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnCollisionObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnCountObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnEmissionObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnEventFlagObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnExpireObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnPositionObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnQuotaObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnRandomObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnTimeObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnVelocityObserver.h"

NS_CC_BEGIN
PUParticle3DObserverManager::PUParticle3DObserverManager()
{
    
}

PUParticle3DObserverManager::~PUParticle3DObserverManager()
{
    
}

PUParticle3DObserverManager* PUParticle3DObserverManager::Instance()
{
    static PUParticle3DObserverManager pem;
    return &pem;
}

PUScriptTranslator* PUParticle3DObserverManager::getTranslator( const std::string &type )
{
    if (type == "OnClear"){
        return &_onClearObserverTranslator;
    }else if (type == "OnCollision"){
        return &_onCollisionObserverTranslator;
    }else if (type == "OnCount"){
        return &_onCountObserverTranslator;
    }else if (type == "OnEmission"){
        return &_onEmissionObserverTranslator;
    }else if (type == "OnEventFlag"){
        return &_onEventFlagObserverTranslator;
    }else if (type == "OnExpire"){
        return &_onExpireObserverTranslator;
    }else if (type == "OnPosition"){
        return &_onPositionObserverTranslator;
    }else if (type == "OnQuota"){
        return &_onQuotaObserverTranslator;
    }else if (type == "OnRandom"){
        return &_onRandomObserverTranslator;
    }else if (type == "OnTime"){
        return &_onTimeObserverTranslator;
    }else if (type == "OnVelocity"){
        return &_onVelocityObserverTranslator;
    }
    return nullptr;
}

PUParticle3DObserver* PUParticle3DObserverManager::createObserver( const std::string &type )
{
    if (type == "OnClear"){
        return PUParticle3DOnClearObserver::create();
    }else if (type == "OnCollision"){
        return PUParticle3DOnCollisionObserver::create();
    }else if (type == "OnCount"){
        return PUParticle3DOnCountObserver::create();
    }else if (type == "OnEmission"){
        return PUParticle3DOnEmissionObserver::create();
    }else if (type == "OnEventFlag"){
        return PUParticle3DOnEventFlagObserver::create();
    }else if (type == "OnExpire"){
        return PUParticle3DOnExpireObserver::create();
    }else if (type == "OnPosition"){
        return PUParticle3DOnPositionObserver::create();
    }else if (type == "OnQuota"){
        return PUParticle3DOnQuotaObserver::create();
    }else if (type == "OnRandom"){
        return PUParticle3DOnRandomObserver::create();
    }else if (type == "OnTime"){
        return PUParticle3DOnTimeObserver::create();
    }else if (type == "OnVelocity"){
        return PUParticle3DOnVelocityObserver::create();
    }
    return nullptr;
}

NS_CC_END