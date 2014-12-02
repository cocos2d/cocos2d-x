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

#include "CCParticle3DBaseForceAffector.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const Vec3 Particle3DBaseForceAffector::DEFAULT_FORCE_VECTOR(0, 0, 0);
const Particle3DBaseForceAffector::ForceApplication Particle3DBaseForceAffector::DEFAULT_FORCE_APPL = Particle3DBaseForceAffector::FA_ADD;

//-----------------------------------------------------------------------
Particle3DBaseForceAffector::Particle3DBaseForceAffector() 
    : PUParticle3DAffector()
    , _forceVector(DEFAULT_FORCE_VECTOR)
    , _scaledVector(Vec3::ZERO)
    , _forceApplication(DEFAULT_FORCE_APPL)
{
}

Particle3DBaseForceAffector::~Particle3DBaseForceAffector()
{
}

const Vec3& Particle3DBaseForceAffector::getForceVector() const
{
    return _forceVector;
}

void Particle3DBaseForceAffector::setForceVector( const Vec3& forceVector )
{
    _forceVector = forceVector;
}

Particle3DBaseForceAffector::ForceApplication Particle3DBaseForceAffector::getForceApplication() const
{
    return _forceApplication;
}

void Particle3DBaseForceAffector::setForceApplication( ForceApplication forceApplication )
{
    _forceApplication = forceApplication;
}

NS_CC_END