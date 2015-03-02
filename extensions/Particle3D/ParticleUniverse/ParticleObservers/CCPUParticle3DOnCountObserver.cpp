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

#include "extensions/Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnCountObserver.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const unsigned int PUParticle3DOnCountObserver::DEFAULT_THRESHOLD = 0;
const PUComparisionOperator PUParticle3DOnCountObserver::DEFAULT_COMPARE = CO_LESS_THAN;

//-----------------------------------------------------------------------
PUParticle3DOnCountObserver::PUParticle3DOnCountObserver(void) : PUParticle3DObserver(),
    _count(1),
    _threshold(DEFAULT_THRESHOLD),
    _compare(DEFAULT_COMPARE)
{
}
//-----------------------------------------------------------------------
void PUParticle3DOnCountObserver::notifyStart (void)
{
    PUParticle3DObserver::notifyStart();

    // At a restart the counter must be reset again.
    _count = 1;
}
//-----------------------------------------------------------------------
bool PUParticle3DOnCountObserver::observe (PUParticle3D* particle, float timeElapsed)
{
    if (!particle)
        return false;

    if (!particle->hasEventFlags(PUParticle3D::PEF_EMITTED))
        return false;

    if (_compare == CO_GREATER_THAN)
    {
        if (_count > _threshold)
        {
            return true;
        }
        else
        {
            _count++;
            return false;
        }
    }
    else if (_compare == CO_LESS_THAN)
    {
        if (_count < _threshold)
        {
            _count++;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (_count == _threshold)
        {
            _count++;
            return true;
        }
        else
        {
            _count++;
            return false;
        }
    }

    return false;
}

PUParticle3DOnCountObserver* PUParticle3DOnCountObserver::create()
{
    auto pco = new (std::nothrow) PUParticle3DOnCountObserver();
    pco->autorelease();
    return pco;
}

void PUParticle3DOnCountObserver::copyAttributesTo( PUParticle3DObserver* observer )
{
    PUParticle3DObserver::copyAttributesTo(observer);

    PUParticle3DOnCountObserver* onCountObserver = static_cast<PUParticle3DOnCountObserver*>(observer);
    onCountObserver->_count = _count;
    onCountObserver->_threshold = _threshold;
    onCountObserver->_compare = _compare;
}

NS_CC_END
