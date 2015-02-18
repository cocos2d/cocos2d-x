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

#include "CCPUParticle3DJetAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticle3DJetAffector::DEFAULT_ACCELERATION = 1.0f;

//-----------------------------------------------------------------------
PUParticle3DJetAffector::PUParticle3DJetAffector (void) : 
    PUParticle3DAffector(),
    _scaled(0.0f)
{
    _dynAcceleration = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynAcceleration))->setValue(DEFAULT_ACCELERATION);
}
//-----------------------------------------------------------------------
PUParticle3DJetAffector::~PUParticle3DJetAffector (void)
{
    if (!_dynAcceleration)
        return;

    CC_SAFE_DELETE(_dynAcceleration);
    _dynAcceleration = 0;
}
//-----------------------------------------------------------------------
void PUParticle3DJetAffector::setDynAcceleration(PUDynamicAttribute* dynAcceleration)
{
    if (_dynAcceleration)
        CC_SAFE_DELETE(_dynAcceleration);

    _dynAcceleration = dynAcceleration;
}

void PUParticle3DJetAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
   // for (auto iter : _particleSystem->getParticles())
    {
       // PUParticle3D *particle = iter;
        _scaled = deltaTime * (_dynAcceleration->getValue(particle->timeFraction));
        if (particle->direction == Vec3::ZERO)
        {
            // Existing direction is zero, so use original direction
            particle->direction += (particle->originalDirection * _scaled);
        }
        else
        {
            particle->direction += (particle->direction * _scaled);
        }
    }
}

PUParticle3DJetAffector* PUParticle3DJetAffector::create()
{
    auto pja = new (std::nothrow) PUParticle3DJetAffector();
    pja->autorelease();
    return pja;
}

NS_CC_END