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

#include "CCPUSlaveEmitter.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUSlaveBehaviour.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
PUSlaveEmitter::PUSlaveEmitter(void) : 
    PUEmitter(),
    PUListener(),
    _masterParticle(0),
    _masterTechniqueName(),
    _masterEmitterName(),
    _masterEmitterNameSet(false)
{
}
//-----------------------------------------------------------------------
const std::string& PUSlaveEmitter::getMasterTechniqueName(void) const
{
    return _masterTechniqueName;
}
//-----------------------------------------------------------------------
void PUSlaveEmitter::setMasterTechniqueName(const std::string& masterTechniqueName)
{
    _masterTechniqueName = masterTechniqueName;
}
//-----------------------------------------------------------------------
const std::string& PUSlaveEmitter::getMasterEmitterName(void) const
{
    return _masterEmitterName;
}
//-----------------------------------------------------------------------
void PUSlaveEmitter::setMasterEmitterName(const std::string& masterEmitterName)
{
    _masterEmitterName = masterEmitterName;
    _masterEmitterNameSet = true;
}
//-----------------------------------------------------------------------
void PUSlaveEmitter::particleEmitted(PUParticleSystem3D* /*particleSystem*/, PUParticle3D* particle)
{
    if (_masterEmitterNameSet && _masterEmitterName != particle->parentEmitter->getName())
    {
        // Ignore particle
        return;
    }

    /** Keep the data of the emitted particle from the master technique/emitter.
        Emission if a particle in this emitter may NOT be done in the main _update() method of the ParticleSystem,
        but only from here ( a slave afterall). That is why the emitter is enabled and disabled again.
    */
    _masterPosition = particle->position;
    _masterDirection = particle->direction;
    _masterParticle = particle;
    _isEnabled = true;
    static_cast<PUParticleSystem3D *>(_particleSystem)->forceEmission(this, 1); // Just emit one, to be in sync with the master.
    _isEnabled = false;
}

void PUSlaveEmitter::particleExpired(PUParticleSystem3D* /*particleSystem*/, PUParticle3D* /*particle*/)
{}

//-----------------------------------------------------------------------
void PUSlaveEmitter::initParticlePosition(PUParticle3D* particle)
{
    // Remark: Don't take the orientation of the node into account, because the position of the master particle is leading.
    particle->position = _masterPosition;
    particle->originalPosition = particle->position;
}
//-----------------------------------------------------------------------
void PUSlaveEmitter::initParticleDirection(PUParticle3D* particle)
{
    particle->direction = _masterDirection;
    particle->originalDirection = particle->direction;
    particle->originalDirectionLength = particle->direction.length();

    // Make use of the opportunity to set the master particle in the behaviour object (if available)

    for (auto iter : particle->behaviours) {
        if (iter->getBehaviourType() == "Slave"){
            static_cast<PUSlaveBehaviour *>(iter)->masterParticle = _masterParticle;
        }
    }
}
//-----------------------------------------------------------------------
void PUSlaveEmitter::prepare()
{
    PUEmitter::prepare();
    PUParticleSystem3D* system = dynamic_cast<PUParticleSystem3D *>(_particleSystem)->getParentParticleSystem();
    if (system)
    {
        auto children = system->getChildren();
        for (auto it : children){
            if (it->getName() == _masterTechniqueName){
                static_cast<PUParticleSystem3D *>(it)->addListener(this);
                break;
            }
        }

        _isEnabled = false;
    }
}
//-----------------------------------------------------------------------
void PUSlaveEmitter::unPrepare()
{
    PUEmitter::unPrepare();
    PUParticleSystem3D* system = dynamic_cast<PUParticleSystem3D *>(_particleSystem)->getParentParticleSystem();
    if (system)
    {
        auto children = system->getChildren();
        for (auto it : children){
            if (it->getName() == _masterTechniqueName){
                static_cast<PUParticleSystem3D *>(it)->removeListener(this);
                break;
            }
        }
    }

    PUEmitter::unPrepare();
}
//-----------------------------------------------------------------------
void PUSlaveEmitter::notifyStart (void)
{
    PUEmitter::notifyStart();
    setEnabled(false);
}

PUSlaveEmitter* PUSlaveEmitter::create()
{
    auto pe = new (std::nothrow) PUSlaveEmitter();
    pe->autorelease();
    return pe;
}

void PUSlaveEmitter::copyAttributesTo( PUEmitter* emitter )
{
    PUEmitter::copyAttributesTo(emitter);

    PUSlaveEmitter* slaveEmitter = static_cast<PUSlaveEmitter*>(emitter);
    slaveEmitter->_masterTechniqueName = _masterTechniqueName;
    slaveEmitter->_masterEmitterName = _masterEmitterName;
    slaveEmitter->_masterEmitterNameSet = _masterEmitterNameSet;
}

PUSlaveEmitter* PUSlaveEmitter::clone()
{
    auto be = PUSlaveEmitter::create();
    copyAttributesTo(be);
    return be;
}

NS_CC_END
