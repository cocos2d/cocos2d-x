/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "CCPUPositionEmitter.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const bool PUPositionEmitter::DEFAULT_RANDOMIZE = true;

//-----------------------------------------------------------------------
PUPositionEmitter::PUPositionEmitter() : 
    PUEmitter(),
    _randomized(DEFAULT_RANDOMIZE),
    _index(0)
{
}
//-----------------------------------------------------------------------
bool PUPositionEmitter::isRandomized() const
{
    return _randomized;
}
//-----------------------------------------------------------------------
void PUPositionEmitter::setRandomized(bool randomized)
{
    _randomized = randomized;
}
//-----------------------------------------------------------------------
const std::vector<Vec3>& PUPositionEmitter::getPositions() const
{
    return _positionList;
}
//-----------------------------------------------------------------------
void PUPositionEmitter::addPosition(const Vec3& position)
{
    _positionList.push_back(position);
}
//-----------------------------------------------------------------------
void PUPositionEmitter::notifyStart()
{
    PUEmitter::notifyStart();
    _index = 0;
}
//-----------------------------------------------------------------------
void PUPositionEmitter::removeAllPositions()
{
    _index = 0;
    _positionList.clear();
}
//-----------------------------------------------------------------------
unsigned short PUPositionEmitter::calculateRequestedParticles(float timeElapsed)
{
    // Fast rejection
    if (_positionList.empty())
        return 0;

    if (_randomized)
    {
        return PUEmitter::calculateRequestedParticles(timeElapsed);
    }
    else if (_index < _positionList.size())
    {
        unsigned short requested = PUEmitter::calculateRequestedParticles(timeElapsed);
        unsigned short size = static_cast<unsigned short>(_positionList.size() - _index);
        if (requested > size)
        {
            return size;
        }
        else
        {
            return requested;
        }
    }

    return 0;
}
//-----------------------------------------------------------------------
void PUPositionEmitter::initParticlePosition(PUParticle3D* particle)
{
    // Fast rejection
    if (_positionList.empty())
        return;

    /** Remark: Don't take the orientation of the node into account, because the positions shouldn't be affected by the rotated node.
    */
    if (_randomized)
    {
        size_t i = (size_t)(CCRANDOM_0_1() * (_positionList.size() - 1));
        particle->position = getDerivedPosition() + Vec3(_emitterScale.x * _positionList[i].x, _emitterScale.y * _positionList[i].y, _emitterScale.z * _positionList[i].z);
    }
    else if (_index < _positionList.size())
    {
        particle->position = getDerivedPosition() + Vec3(_emitterScale.x * _positionList[_index].x, _emitterScale.y * _positionList[_index].y, _emitterScale.z * _positionList[_index].z);
        _index++;
    }

    particle->originalPosition = particle->position;
}

PUPositionEmitter* PUPositionEmitter::create()
{
    auto pe = new (std::nothrow) PUPositionEmitter();
    pe->autorelease();
    return pe;
}

void PUPositionEmitter::copyAttributesTo( PUEmitter* emitter )
{
    PUEmitter::copyAttributesTo(emitter);
    PUPositionEmitter* positionEmitter = static_cast<PUPositionEmitter*>(emitter);
    positionEmitter->_randomized = _randomized;
    positionEmitter->_positionList = _positionList;
}

PUPositionEmitter* PUPositionEmitter::clone()
{
    auto be = PUPositionEmitter::create();
    copyAttributesTo(be);
    return be;
}

NS_CC_END
