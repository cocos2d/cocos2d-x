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

#include "Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DDoEnableComponentEventHandler.h"
#include "Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DObserver.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
PUParticle3DDoEnableComponentEventHandler::PUParticle3DDoEnableComponentEventHandler(void) : 
    PUParticle3DEventHandler(),
    _componentType(CT_EMITTER),
    _componentEnabled(true)
{
}
//-----------------------------------------------------------------------
void PUParticle3DDoEnableComponentEventHandler::handle (PUParticleSystem3D* particleSystem, PUParticle3D* particle, float timeElapsed)
{
    /** Search for the component.
    */
    //ParticleTechnique* technique = 0;
    switch (_componentType)
    {
        case CT_EMITTER:
        {
            PUParticle3DEmitter* emitter = particleSystem->getEmitter(_componentName);
            if (!emitter)
            {
                // Search all techniques in this ParticleSystem for an emitter with the correct name
                PUParticleSystem3D* system = particleSystem->getParentParticleSystem();
                if (system){
                    auto children = system->getChildren();
                    for(auto iter : children)		
                    {
                        PUParticleSystem3D *child  = dynamic_cast<PUParticleSystem3D *>(iter);
                        if (child){
                            emitter = child->getEmitter(_componentName);
                            if (emitter)
                            {
                                break;
                            }
                        }
                    }
                }
            }
            if (emitter)
            {
                emitter->setEnabled(_componentEnabled);
            }
        }
        break;

        case CT_AFFECTOR:
        {
            PUParticle3DAffector* affector = particleSystem->getAffector(_componentName);
            if (!affector)
            {
                // Search all techniques in this ParticleSystem for an emitter with the correct name
                PUParticleSystem3D* system = particleSystem->getParentParticleSystem();
                if (system){
                    auto children = system->getChildren();
                    for(auto iter : children)		
                    {
                        PUParticleSystem3D *child  = dynamic_cast<PUParticleSystem3D *>(iter);
                        if (child){
                            affector = child->getAffector(_componentName);
                            if (affector)
                            {
                                break;
                            }
                        }
                    }
                }
            }
            if (affector)
            {
                affector->setEnabled(_componentEnabled);
            }
        }
        break;

        case CT_OBSERVER:
        {
            PUParticle3DObserver* observer = particleSystem->getObserver(_componentName);
            if (!observer)
            {
                // Search all techniques in this ParticleSystem for an emitter with the correct name
                PUParticleSystem3D* system = particleSystem->getParentParticleSystem();
                if (system){
                    auto children = system->getChildren();
                    for(auto iter : children)		
                    {
                        PUParticleSystem3D *child  = dynamic_cast<PUParticleSystem3D *>(iter);
                        if (child){
                            observer = child->getObserver(_componentName);
                            if (observer)
                            {
                                break;
                            }
                        }
                    }
                }
            }
            if (observer)
            {
                observer->setEnabled(_componentEnabled);
            }
        }
        break;

        case CT_TECHNIQUE:
        {
            // Search in this ParticleSystem for a technique with the correct name
            PUParticleSystem3D* system = particleSystem->getParentParticleSystem();
            if (system){
                auto children = system->getChildren();
                for (auto iter : children){
                    PUParticleSystem3D *child = static_cast<PUParticleSystem3D *>(system);
                    if (child->getName() == _componentName){
                        child->setEnabled(_componentEnabled);
                        break;
                    }
                }
            }
        }
        break;
        default:
            break;
    }
}

PUParticle3DDoEnableComponentEventHandler* PUParticle3DDoEnableComponentEventHandler::create()
{
    auto peh = new PUParticle3DDoEnableComponentEventHandler();
    peh->autorelease();
    return peh;
}

void PUParticle3DDoEnableComponentEventHandler::copyAttributesTo( PUParticle3DEventHandler* eventHandler )
{
    PUParticle3DEventHandler::copyAttributesTo(eventHandler);
    PUParticle3DDoEnableComponentEventHandler* doEnableComponentEventHandler = static_cast<PUParticle3DDoEnableComponentEventHandler*>(eventHandler);
    doEnableComponentEventHandler->setComponentType(_componentType);
    doEnableComponentEventHandler->setComponentName(_componentName);
    doEnableComponentEventHandler->setComponentEnabled(_componentEnabled);
}

NS_CC_END
