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

#include "extensions/Particle3D/PU/CCPUAffector.h"
#include "extensions/Particle3D/PU/CCPUEmitter.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

PUAffector::PUAffector()
: _affectorScale(Vec3::ONE)
, _affectSpecialisation(AFSP_DEFAULT)
, _mass(1.0f)
{
    
}

PUAffector::~PUAffector()
{
    _particleSystem = nullptr;
}

void PUAffector::updatePUAffector(PUParticle3D* particle, float delta)
{
    
}

const Vec3& PUAffector::getDerivedPosition()
{
    PUParticleSystem3D *ps = static_cast<PUParticleSystem3D *>(_particleSystem);
    if (ps){
        Mat4 rotMat;
        Mat4::createRotation(ps->getDerivedOrientation(), &rotMat);
        _derivedPosition = ps->getDerivedPosition() + rotMat * Vec3(_position.x * _affectorScale.x, _position.y * _affectorScale.y, _position.z * _affectorScale.z);
        //_particleSystem->getNodeToWorldTransform().transformPoint(_position, &_derivedPosition);
    }
    else
        _derivedPosition = _position;

    return _derivedPosition;

    //if (mMarkedForEmission)
    //{
    //	// Use the affector position, because it is emitted
    //	// If a particle is emitted, position and derived position are the same
    //	_derivedPosition = position;
    //}
    //else
    //{
    //	// Add the techniques' derived position
    //	_derivedPosition = mParentTechnique->getDerivedPosition() + 
    //		mParentTechnique->getParentSystem()->getDerivedOrientation() * (_mAffectorScale * position);
    //}
    //return _derivedPosition;
}

float PUAffector::calculateAffectSpecialisationFactor( const PUParticle3D* particle )
{
    // Assume that particle->totalTimeToLive != 0, which is reasonable
    switch (_affectSpecialisation)
    {
    case AFSP_DEFAULT:
        return 1.0f;
        break;

        // This means that older particles will be affected MORE than just emitted particles
    case AFSP_TTL_INCREASE:
        {
            if (particle)
            {
                return particle->timeFraction;
            }
            else
            {
                return 1.0f;
            }
        }
        break;

        // This means that older particles will be affected LESS than just emitted particles
    case AFSP_TTL_DECREASE:
        {
            if (particle)
            {
                return 1.0f - particle->timeFraction;
            }
            else
            {
                return 1.0f;
            }
        }
        break;

    default:
        return 1.0f;
        break;
    }
}

void PUAffector::notifyStart()
{

}

void PUAffector::notifyStop()
{

}

void PUAffector::notifyPause()
{

}

void PUAffector::notifyResume()
{

}

void PUAffector::preUpdateAffector( float deltaTime )
{

}

void PUAffector::postUpdateAffector( float deltaTime )
{

}

void PUAffector::prepare()
{

}

void PUAffector::unPrepare()
{

}

void PUAffector::initParticleForEmission( PUParticle3D* particle )
{

}

void PUAffector::notifyRescaled(const Vec3& scale)
{
    _affectorScale = scale;
}

void PUAffector::firstParticleUpdate( PUParticle3D *particle, float deltaTime )
{

}

void PUAffector::setMass( float mass )
{
    _mass =  mass;
}

float PUAffector::getMass() const
{
    return _mass;
}

void PUAffector::copyAttributesTo( PUAffector* affector )
{
    affector->setName(_name);
    affector->_isEnabled = _isEnabled;
    affector->_particleSystem = _particleSystem;
    affector->_affectorScale = _affectorScale;
    affector->_affectSpecialisation = _affectSpecialisation;
}

void PUAffector::addEmitterToExclude( const std::string& emitterName )
{
    auto iter  = std::find(_excludedEmitters.begin(), _excludedEmitters.end(), emitterName);
    if (iter == _excludedEmitters.end()){
        _excludedEmitters.push_back(emitterName);
    }
}

void PUAffector::removeEmitterToExclude( const std::string& emitterName )
{
    auto iter  = std::find(_excludedEmitters.begin(), _excludedEmitters.end(), emitterName);
    if (iter != _excludedEmitters.end()){
        _excludedEmitters.erase(iter);
    }
}

void PUAffector::process( PUParticle3D* particle, float delta, bool firstParticle )
{
    if (firstParticle){
        firstParticleUpdate(particle, delta);
    }

    if (!_excludedEmitters.empty() && particle->parentEmitter){
        // Return if the emitter which emits this particle is part of the vector
        std::string emitterName = particle->parentEmitter->getName();
        auto iter = std::find(_excludedEmitters.begin(), _excludedEmitters.end(), emitterName);
        if (iter != _excludedEmitters.end())
        {
            return;
        }
    }

    updatePUAffector(particle, delta);
}

NS_CC_END
