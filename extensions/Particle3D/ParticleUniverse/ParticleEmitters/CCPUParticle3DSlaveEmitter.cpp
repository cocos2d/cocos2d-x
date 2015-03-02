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

#include "CCPUParticle3DSlaveEmitter.h"
#include "Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "Particle3D/ParticleUniverse/ParticleBehaviours/CCPUParticle3DSlaveBehaviour.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
PUParticle3DSlaveEmitter::PUParticle3DSlaveEmitter(void) : 
    PUParticle3DEmitter(),
    PUParticle3DListener(),
    _masterParticle(0),
    _masterTechniqueName(),
    _masterEmitterName(),
    _masterPosition(Vec3::ZERO),
    _masterDirection(Vec3::ZERO),
    _masterEmitterNameSet(false)
{
}
//-----------------------------------------------------------------------
const std::string& PUParticle3DSlaveEmitter::getMasterTechniqueName(void) const
{
    return _masterTechniqueName;
}
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::setMasterTechniqueName(const std::string& masterTechniqueName)
{
    _masterTechniqueName = masterTechniqueName;
}
//-----------------------------------------------------------------------
const std::string& PUParticle3DSlaveEmitter::getMasterEmitterName(void) const
{
    return _masterEmitterName;
}
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::setMasterEmitterName(const std::string& masterEmitterName)
{
    _masterEmitterName = masterEmitterName;
    _masterEmitterNameSet = true;
}
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::particleEmitted(PUParticleSystem3D* particleSystem, PUParticle3D* particle)
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
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::initParticlePosition(PUParticle3D* particle)
{
    // Remark: Don't take the orientation of the node into account, because the position of the master particle is leading.
    particle->position = _masterPosition;
    particle->originalPosition = particle->position;
}
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::initParticleDirection(PUParticle3D* particle)
{
    particle->direction = _masterDirection;
    particle->originalDirection = particle->direction;
    particle->originalDirectionLength = particle->direction.length();

    // Make use of the opportunity to set the master particle in the behaviour object (if available)

    for (auto iter : particle->behaviours) {
        if (iter->getBehaviourType() == "Slave"){
            static_cast<PUParticle3DSlaveBehaviour *>(iter)->masterParticle = _masterParticle;
        }
    }
}
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::prepare()
{
    PUParticle3DEmitter::prepare();
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
void PUParticle3DSlaveEmitter::unPrepare()
{
    PUParticle3DEmitter::unPrepare();
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

    PUParticle3DEmitter::unPrepare();
}
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::notifyStart (void)
{
    PUParticle3DEmitter::notifyStart();
    setEnabled(false);
}

PUParticle3DSlaveEmitter* PUParticle3DSlaveEmitter::create()
{
    auto pe = new PUParticle3DSlaveEmitter();
    pe->autorelease();
    return pe;
}

void PUParticle3DSlaveEmitter::copyAttributesTo( PUParticle3DEmitter* emitter )
{
    PUParticle3DEmitter::copyAttributesTo(emitter);

    PUParticle3DSlaveEmitter* slaveEmitter = static_cast<PUParticle3DSlaveEmitter*>(emitter);
    slaveEmitter->_masterTechniqueName = _masterTechniqueName;
    slaveEmitter->_masterEmitterName = _masterEmitterName;
    slaveEmitter->_masterEmitterNameSet = _masterEmitterNameSet;
}

PUParticle3DSlaveEmitter* PUParticle3DSlaveEmitter::clone()
{
    auto be = PUParticle3DSlaveEmitter::create();
    copyAttributesTo(be);
    return be;
}

NS_CC_END