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

#include "CCPUParticle3DLinearForceAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

//-----------------------------------------------------------------------
void PUParticle3DLinearForceAffector::preUpdateAffector(float deltaTime)
{
    // Scale force
    _scaledVector = _forceVector * deltaTime;
}
//-----------------------------------------------------------------------


void PUParticle3DLinearForceAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        // Affect the direction and take the specialisation into account
        if (_forceApplication == FA_ADD)
        {
            particle->direction += _scaledVector * calculateAffectSpecialisationFactor(particle);
        }
        else
        {
            particle->direction = (particle->direction + _forceVector) / 2;
        }
    }

}

PUParticle3DLinearForceAffector* PUParticle3DLinearForceAffector::create()
{
    auto plfa = new (std::nothrow) PUParticle3DLinearForceAffector();
    plfa->autorelease();
    return plfa;
}

NS_CC_END