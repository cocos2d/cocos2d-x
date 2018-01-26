/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#ifndef __CC_PU_PARTICLE_3D_DO_ENABLE_COMPONENT_EVENT_HANDLER_H__
#define __CC_PU_PARTICLE_3D_DO_ENABLE_COMPONENT_EVENT_HANDLER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUEventHandler.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUObserver;
class PUParticleSystem3D;

class CC_DLL PUDoEnableComponentEventHandler : public PUEventHandler
{
public:

    static PUDoEnableComponentEventHandler* create();

    /** Get the name of the component that must be enabled or disabled.
    */
    const std::string& getComponentName(void) const {return _componentName;};

    /** Set the name of the component that must be enabled or disables.
    */
    void setComponentName(const std::string& componentName){_componentName = componentName;};

    /** Get the value that identifies whether the component must be enabled or disabled.
    */
    bool isComponentEnabled(void) const {return _componentEnabled;};

    /** Set the value that identifies whether the component must be enabled or disabled.
    */
    void setComponentEnabled(bool enabled){_componentEnabled = enabled;};

    /** Get the value that identifies whether the component must be enabled or disabled.
    */
    PUComponentType getComponentType(void) const {return _componentType;};

    /** Set the value that identifies whether the component must be enabled or disabled.
    */
    void setComponentType(PUComponentType componentType){_componentType = componentType;};

    /** If the _handle() function of this class is invoked (by an Observer), it searches the 
        ParticleEmitter, ParticleAffector or ParticleTechnique defined by the its name. 
        The ParticleEmitter/Affector is either part of the ParticleTechnique in which the 
        DoEnableComponentEventHandler is defined, or if the ParticleEmitter/Affector is not 
        found, other ParticleTechniques are searched.
    */
    virtual void handle (PUParticleSystem3D* particleSystem, PUParticle3D* particle, float timeElapsed) override;

    virtual void copyAttributesTo (PUEventHandler* eventHandler) override;

CC_CONSTRUCTOR_ACCESS:
    PUDoEnableComponentEventHandler(void);
    virtual ~PUDoEnableComponentEventHandler(void) {};

protected:
    // Identifies the name of component
    std::string _componentName;

    // Identifies the type of component
    PUComponentType _componentType;

    /** Determines whether the Component must be enabled or disabled.
    */
    bool _componentEnabled;

};

NS_CC_END

#endif
