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

#include "CCPUParticle3DPositionEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const bool PUParticle3DPositionEmitter::DEFAULT_RANDOMIZE = true;

//-----------------------------------------------------------------------
PUParticle3DPositionEmitter::PUParticle3DPositionEmitter(void) : 
    PUParticle3DEmitter(),
    _randomized(DEFAULT_RANDOMIZE),
    _index(0)
{
}
//-----------------------------------------------------------------------
bool PUParticle3DPositionEmitter::isRandomized() const
{
    return _randomized;
}
//-----------------------------------------------------------------------
void PUParticle3DPositionEmitter::setRandomized(bool randomized)
{
    _randomized = randomized;
}
//-----------------------------------------------------------------------
const std::vector<Vec3>& PUParticle3DPositionEmitter::getPositions(void) const
{
    return _positionList;
}
//-----------------------------------------------------------------------
void PUParticle3DPositionEmitter::addPosition(const Vec3& position)
{
    _positionList.push_back(position);
}
//-----------------------------------------------------------------------
void PUParticle3DPositionEmitter::notifyStart(void)
{
    PUParticle3DEmitter::notifyStart();
    _index = 0;
}
//-----------------------------------------------------------------------
void PUParticle3DPositionEmitter::removeAllPositions(void)
{
    _index = 0;
    _positionList.clear();
}
//-----------------------------------------------------------------------
unsigned short PUParticle3DPositionEmitter::calculateRequestedParticles(float timeElapsed)
{
    // Fast rejection
    if (_positionList.empty())
        return 0;

    if (_randomized)
    {
        return PUParticle3DEmitter::calculateRequestedParticles(timeElapsed);
    }
    else if (_index < _positionList.size())
    {
        unsigned short requested = PUParticle3DEmitter::calculateRequestedParticles(timeElapsed);
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
void PUParticle3DPositionEmitter::initParticlePosition(PUParticle3D* particle)
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

PUParticle3DPositionEmitter* PUParticle3DPositionEmitter::create()
{
    auto pe = new (std::nothrow) PUParticle3DPositionEmitter();
    pe->autorelease();
    return pe;
}

NS_CC_END