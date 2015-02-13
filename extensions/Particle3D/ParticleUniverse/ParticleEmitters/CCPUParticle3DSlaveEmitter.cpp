/****************************************************************************
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

#include "CCPUParticle3DSlaveEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
PUParticle3DSlaveEmitter::PUParticle3DSlaveEmitter(void) : 
    PUParticle3DEmitter(),
    //TechniqueListener(),
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
////-----------------------------------------------------------------------
//void Particle3DSlaveEmitter::particleEmitted(ParticleTechnique* particleTechnique, PUParticle3D* particle)
//{
//	if (_masterEmitterNameSet && _masterEmitterName != particle->parentEmitter->getName())
//	{
//		// Ignore particle
//		return;
//	}
//
//	/** Keep the data of the emitted particle from the master technique/emitter.
//		Emission if a particle in this emitter may NOT be done in the main _update() method of the ParticleSystem,
//		but only from here (it´s a slave afterall). That is why the emitter is enabled and disabled again.
//	*/
//	_masterPosition = particle->position;
//	_masterDirection = particle->direction;
//	_masterParticle = particle;
//	mEnabled = true;
//	mParentTechnique->forceEmission(this, 1); // Just emit one, to be in sync with the master.
//	mEnabled = false;
//}
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

    //// Make use of the opportunity to set the master particle in the behaviour object (if available)
    //SlaveBehaviour* behaviour = static_cast<SlaveBehaviour*>(particle->getBehaviour("Slave"));
    //if (behaviour)
    //{
    //	behaviour->masterParticle = _masterParticle;
    //}
}
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::prepare()
{
    //ParticleSystem* system = particleTechnique->getParentSystem();
    //if (system)
    //{
    //	ParticleTechnique* masterTechnique = system->getTechnique(_masterTechniqueName);
    //	if (masterTechnique)
    //	{
    //		masterTechnique->addTechniqueListener(this);
    //	}
    //	mEnabled = false;
    //}
}
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::unPrepare()
{
    //ParticleSystem* system = particleTechnique->getParentSystem();
    //if (system)
    //{
    //	ParticleTechnique* masterTechnique = system->getTechnique(_masterTechniqueName);
    //	if (masterTechnique)
    //	{
    //		masterTechnique->removeTechniqueListener(this);
    //	}
    //}
}
//-----------------------------------------------------------------------
void PUParticle3DSlaveEmitter::notifyStart (void)
{
    PUParticle3DEmitter::notifyStart();
    setEnabled(false);
}

PUParticle3DSlaveEmitter* PUParticle3DSlaveEmitter::create()
{
    auto pe = new (std::nothrow) PUParticle3DSlaveEmitter();
    pe->autorelease();
    return pe;
}

NS_CC_END