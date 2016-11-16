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

#include "extensions/Particle3D/PU/CCPUDoEnableComponentEventHandler.h"
#include "extensions/Particle3D/PU/CCPUAffector.h"
#include "extensions/Particle3D/PU/CCPUEmitter.h"
#include "extensions/Particle3D/PU/CCPUObserver.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
PUDoEnableComponentEventHandler::PUDoEnableComponentEventHandler(void) : 
    PUEventHandler(),
    _componentType(CT_EMITTER),
    _componentEnabled(true)
{
}
//-----------------------------------------------------------------------
void PUDoEnableComponentEventHandler::handle (PUParticleSystem3D* particleSystem, PUParticle3D* /*particle*/, float /*timeElapsed*/)
{
    /** Search for the component.
    */
    //ParticleTechnique* technique = 0;
    switch (_componentType)
    {
        case CT_EMITTER:
        {
            PUEmitter* emitter = particleSystem->getEmitter(_componentName);
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
            PUAffector* affector = particleSystem->getAffector(_componentName);
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
            PUObserver* observer = particleSystem->getObserver(_componentName);
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
                    PUParticleSystem3D *child = dynamic_cast<PUParticleSystem3D *>(iter);
                    if (child && child->getName() == _componentName){
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

PUDoEnableComponentEventHandler* PUDoEnableComponentEventHandler::create()
{
    auto peh = new (std::nothrow) PUDoEnableComponentEventHandler();
    peh->autorelease();
    return peh;
}

void PUDoEnableComponentEventHandler::copyAttributesTo( PUEventHandler* eventHandler )
{
    PUEventHandler::copyAttributesTo(eventHandler);
    PUDoEnableComponentEventHandler* doEnableComponentEventHandler = static_cast<PUDoEnableComponentEventHandler*>(eventHandler);
    doEnableComponentEventHandler->setComponentType(_componentType);
    doEnableComponentEventHandler->setComponentName(_componentName);
    doEnableComponentEventHandler->setComponentEnabled(_componentEnabled);
}

NS_CC_END
