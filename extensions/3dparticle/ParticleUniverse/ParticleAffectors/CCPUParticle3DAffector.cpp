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

#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

PUParticle3DAffector::PUParticle3DAffector()
: _particleSystem(nullptr)
, _affectorScale(Vec3::ONE)
, _affectSpecialisation(AFSP_DEFAULT)
{
    
}

PUParticle3DAffector::~PUParticle3DAffector()
{
    _particleSystem = nullptr;
}

void PUParticle3DAffector::updateAffector(PUParticle3D *particle, float deltaTime)
{
    
}

const Vec3& PUParticle3DAffector::getDerivedPosition()
{
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

    //incorrect result (FIXME)
    return _position;
}

float PUParticle3DAffector::calculateAffectSpecialisationFactor( const PUParticle3D* particle )
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

void PUParticle3DAffector::notifyStart()
{

}

void PUParticle3DAffector::notifyStop()
{

}

void PUParticle3DAffector::notifyPause()
{

}

void PUParticle3DAffector::notifyResume()
{

}

void PUParticle3DAffector::preUpdateAffector( float deltaTime )
{

}

void PUParticle3DAffector::postUpdateAffector( float deltaTime )
{

}

void PUParticle3DAffector::prepare()
{

}

void PUParticle3DAffector::unPrepare()
{

}

void PUParticle3DAffector::initParticleForEmission( PUParticle3D* particle )
{

}

void PUParticle3DAffector::notifyRescaled(const Vec3& scale)
{
    _affectorScale = scale;
}

void PUParticle3DAffector::firstParticleUpdate( PUParticle3D *particle, float deltaTime )
{

}

NS_CC_END
