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

#include "CCPUBaseForceAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const Vec3 PUBaseForceAffector::DEFAULT_FORCE_VECTOR(0, 0, 0);
const PUBaseForceAffector::ForceApplication PUBaseForceAffector::DEFAULT_FORCE_APPL = PUBaseForceAffector::FA_ADD;

//-----------------------------------------------------------------------
PUBaseForceAffector::PUBaseForceAffector() 
    : PUAffector()
    , _forceVector(DEFAULT_FORCE_VECTOR)
    , _forceApplication(DEFAULT_FORCE_APPL)
{
}

PUBaseForceAffector::~PUBaseForceAffector()
{
}

const Vec3& PUBaseForceAffector::getForceVector() const
{
    return _forceVector;
}

void PUBaseForceAffector::setForceVector( const Vec3& forceVector )
{
    _forceVector = forceVector;
}

PUBaseForceAffector::ForceApplication PUBaseForceAffector::getForceApplication() const
{
    return _forceApplication;
}

void PUBaseForceAffector::setForceApplication( ForceApplication forceApplication )
{
    _forceApplication = forceApplication;
}

void PUBaseForceAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUBaseForceAffector* baseForceAffector = static_cast<PUBaseForceAffector*>(affector);
    baseForceAffector->_forceVector = _forceVector;
    baseForceAffector->_forceApplication = _forceApplication;
}

NS_CC_END
