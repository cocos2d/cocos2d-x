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

#include "CCPUParticle3DSineForceAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const float PUParticle3DSineForceAffector::DEFAULT_FREQ_MIN = 1.0f;
const float PUParticle3DSineForceAffector::DEFAULT_FREQ_MAX = 1.0f;

//-----------------------------------------------------------------------
PUParticle3DSineForceAffector::PUParticle3DSineForceAffector(void) : 
    PUParticle3DBaseForceAffector(),
    _angle(361),
    _frequencyMin(DEFAULT_FREQ_MIN),
    _frequencyMax(DEFAULT_FREQ_MAX),
    _frequency(1.0f)
{
}
PUParticle3DSineForceAffector::~PUParticle3DSineForceAffector( void )
{

}
//-----------------------------------------------------------------------
void PUParticle3DSineForceAffector::preUpdateAffector(float deltaTime)
{
    // Scale by time
    _angle += _frequency * deltaTime;
    float sineValue = sin(_angle);
    _scaledVector = _forceVector * deltaTime * sineValue;

    if (_angle > M_PI * 2.0f)
    {
        _angle = 0.0f;

        if (_frequencyMin != _frequencyMax)
        {
            _frequency = cocos2d::random(_frequencyMin, _frequencyMax);
        }
    }
}
//-----------------------------------------------------------------------
const float PUParticle3DSineForceAffector::getFrequencyMin(void) const
{
    return _frequencyMin;
}
//-----------------------------------------------------------------------
void PUParticle3DSineForceAffector::setFrequencyMin(const float frequencyMin)
{
    _frequencyMin = frequencyMin;
    if (frequencyMin > _frequencyMax)
    {
        _frequency = frequencyMin;
    }
}
//-----------------------------------------------------------------------
const float PUParticle3DSineForceAffector::getFrequencyMax(void) const
{
    return _frequencyMax;
}
//-----------------------------------------------------------------------
void PUParticle3DSineForceAffector::setFrequencyMax(const float frequencyMax)
{
    _frequencyMax = frequencyMax;
    _frequency = frequencyMax;
}
//-----------------------------------------------------------------------

void PUParticle3DSineForceAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        // Affect the direction
        if (_forceApplication == FA_ADD)
        {
            particle->direction += _scaledVector;
        }
        else
        {
            particle->direction = (particle->direction + _forceVector) / 2;
        }
    }
}

PUParticle3DSineForceAffector* PUParticle3DSineForceAffector::create()
{
    auto psfa = new (std::nothrow) PUParticle3DSineForceAffector();
    psfa->autorelease();
    return psfa;
}

NS_CC_END