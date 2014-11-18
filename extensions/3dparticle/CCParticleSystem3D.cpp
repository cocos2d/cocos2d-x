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

#include "CCParticleSystem3D.h"
#include "CCParticle3DEmitter.h"
#include "CCParticle3DAffector.h"

NS_CC_BEGIN


void Particle3D::setOwnDimensions( float newWidth, float newHeight, float newDepth )
{
	ownDimensions = true;
	if (newWidth)
		width = newWidth;
	if (newHeight)
		height = newHeight;
	if (newDepth)
		depth = newDepth;
	calculateBoundingSphereRadius();
	//parentEmitter->getParentTechnique()->_notifyParticleResized();
}

void Particle3D::calculateBoundingSphereRadius()
{
	//radius = 0.5 * Math::Sqrt(width*width + height*height + depth*depth);
	radius = 0.5f * std::max(depth, std::max(width, height)); // approximation
}

//-----------------------------------------------------------------------

ParticleSystem3D::ParticleSystem3D()
: _emitter(nullptr)
, _render(nullptr)
, _aliveParticlesCnt(0)
, _state(State::RUNNING)
{
    
}
ParticleSystem3D::~ParticleSystem3D()
{
    
}

void ParticleSystem3D::start()
{
    
}

void ParticleSystem3D::stop()
{
    
}

void ParticleSystem3D::pause()
{
    
}

void ParticleSystem3D::resume()
{
    
}

void ParticleSystem3D::setEmitter(Particle3DEmitter* emitter)
{
    
}

void ParticleSystem3D::setRender(Particle3DRender* render)
{
    
}

void ParticleSystem3D::addAffector(Particle3DAffector* affector)
{
    if (std::find(_affectors.begin(), _affectors.end(), affector) != _affectors.end()){
        affector->_particleSystem = this;
        _affectors.push_back(affector);
    }
}

void ParticleSystem3D::removeAffector(int index)
{
    CCASSERT((unsigned int)index < _affectors.size(), "wrong index");
    _affectors.erase(_affectors.begin() + index);
}

void ParticleSystem3D::removeAllAffector()
{
    //release all affectors
    _affectors.clear();
}

Particle3DAffector* ParticleSystem3D::getAffector(int index)
{
    CCASSERT((unsigned int)index < _affectors.size(), "wrong index");
    return _affectors[index];
}

void ParticleSystem3D::update(float delta)
{
    if (_state != State::RUNNING)
        return;
    
    if (_emitter)
        _emitter->updateEmitter(delta);
    
    for (auto& it : _affectors) {
        it->updateAffector(delta);
    }
        
}

const std::vector<Particle3D*>& ParticleSystem3D::getParticles()
{
    return _particles;
}

NS_CC_END
