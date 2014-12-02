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

#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"
#include "3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "3dparticle/CCParticle3DRender.h"

NS_CC_BEGIN

float PUParticle3D::DEFAULT_TTL = 10.0f;
float PUParticle3D::DEFAULT_MASS = 1.0f;

void PUParticle3D::setOwnDimensions( float newWidth, float newHeight, float newDepth )
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

void PUParticle3D::calculateBoundingSphereRadius()
{
    //radius = 0.5 * Math::Sqrt(width*width + height*height + depth*depth);
    radius = 0.5f * std::max(depth, std::max(width, height)); // approximation
}

void PUParticle3D::initForEmission()
{
		eventFlags = 0;
		timeFraction = 0.0f;
		/*	Note, that this flag must only be set as soon as the particle is emitted. As soon as the particle has
			been moved once, the flag must be removed again.
		*/
		addEventFlags(PUParticle3D::PEF_EMITTED);

		// Reset freeze flag
		freezed = false;
}

//-----------------------------------------------------------------------

const float PUParticleSystem3D::DEFAULT_WIDTH = 50;
const float PUParticleSystem3D::DEFAULT_HEIGHT = 50;
const float PUParticleSystem3D::DEFAULT_DEPTH = 50;

PUParticleSystem3D::PUParticleSystem3D()
: _prepared(false)
, _particleSystemScaleVelocity(0.0f)
, _defaultWidth(DEFAULT_WIDTH)
, _defaultHeight(DEFAULT_HEIGHT)
, _defaultDepth(DEFAULT_DEPTH)
{
    
}
PUParticleSystem3D::~PUParticleSystem3D()
{
	unPrepared();
}

void PUParticleSystem3D::start()
{
    if (_state != State::RUNNING)
    {
		if (_emitter)
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
			emitter->notifyStart();
        }

		for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
			affector->notifyStart();
		}

		if (_render)
			_render->notifyStart();

        scheduleUpdate();
        _state = State::RUNNING;
        _timeElapsedSinceStart = 0.0f;
    }
}

void PUParticleSystem3D::stop()
{
    if (_state != State::STOP)
    {
		if (_emitter)
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
			emitter->notifyStop();
        }

		for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
			affector->notifyStop();
		}

		if (_render)
			_render->notifyStop();

        unscheduleUpdate();
        _state = State::STOP;
    }
}

void PUParticleSystem3D::pause()
{
    if (_state == State::RUNNING)
    {
		if (_emitter)
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
			emitter->notifyPause();
        }

		for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
			affector->notifyPause();
		}
        _state = State::PAUSE;
    }
}

void PUParticleSystem3D::resume()
{
    if (_state == State::PAUSE)
    {
		if (_emitter)
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
			emitter->notifyResume();
        }

		for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
			affector->notifyResume();
		}

        _state = State::RUNNING;
    }
}

void PUParticleSystem3D::update(float delta)
{
    if (_state != State::RUNNING)
        return;

	prepared();
	emitParticles(_timeElapsedSinceStart);
	preUpdator(_timeElapsedSinceStart);
	updator(_timeElapsedSinceStart);
	postUpdator(_timeElapsedSinceStart);

    _timeElapsedSinceStart += delta;
}

float PUParticleSystem3D::getParticleSystemScaleVelocity() const
{
    return _particleSystemScaleVelocity;
}

void PUParticleSystem3D::rotationOffset( Vec3& pos )
{
    Mat4 rotMat;
    Mat4::createRotation(_rotationOffset, &rotMat);
    pos = _rotationCentre + rotMat * (pos - _rotationCentre);
}

void PUParticleSystem3D::prepared()
{
	if (!_prepared){
		if (_emitter && _emitter->isEnabled())
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
			emitter->prepare();
        }

		for (auto& it : _affectors) {
			if (it->isEnabled())
				(static_cast<PUParticle3DAffector*>(it))->prepare();
		}
		_prepared = true;
	}
}

void PUParticleSystem3D::unPrepared()
{
	if (_emitter && _emitter->isEnabled())
    {
         auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
		emitter->unPrepare();
    }

	for (auto& it : _affectors) {
		if (it->isEnabled())
			(static_cast<PUParticle3DAffector*>(it))->unPrepare();
	}
}

void PUParticleSystem3D::preUpdator( float elapsedTime )
{
	if (_emitter && _emitter->isEnabled())
    {
         auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
		emitter->preUpdateEmitter(elapsedTime);
    }

	for (auto& it : _affectors) {
		if (it->isEnabled())
			(static_cast<PUParticle3DAffector*>(it))->preUpdateAffector(elapsedTime);
	}
}

void PUParticleSystem3D::updator( float elapsedTime )
{
	bool firstActiveParticle = true; // The first non-expired particle
	for (auto iter : _particles){
		PUParticle3D *particle = static_cast<PUParticle3D*>(iter);
		if (!isExpired(particle, elapsedTime))
		{
			particle->timeFraction = (particle->totalTimeToLive - particle->timeToLive) / particle->totalTimeToLive;

			if (_emitter && _emitter->isEnabled())
				_emitter->updateEmitter(particle, elapsedTime);

			for (auto& it : _affectors) {
                auto affector = (static_cast<PUParticle3DAffector*>(it));
				if (it->isEnabled()){
					if (firstActiveParticle)
						affector->firstParticleUpdate(particle, elapsedTime);
					affector->updateAffector(particle, elapsedTime);
				}
			}

			//need update render?

			//processMotion(Particle* particle, Real timeElapsed, bool firstParticle)

			firstActiveParticle = false;
		}

		if (particle->hasEventFlags(PUParticle3D::PEF_EXPIRED))
		{
			particle->setEventFlags(0);
			particle->addEventFlags(PUParticle3D::PEF_EXPIRED);
		}
		else
		{
			particle->setEventFlags(0);
		}

		particle->timeToLive -= elapsedTime;
	}
}

void PUParticleSystem3D::postUpdator( float elapsedTime )
{
	if (_emitter && _emitter->isEnabled())
    {
        auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
		emitter->postUpdateEmitter(elapsedTime);
    }

	for (auto& it : _affectors) {
		if (it->isEnabled())
        {
            auto affector = static_cast<PUParticle3DAffector*>(it);
			affector->postUpdateAffector(elapsedTime);
        }
	}
}

void PUParticleSystem3D::emitParticles( float elapsedTime )
{
	if (!_emitter || !_emitter->isEnabled()) return;

    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
	unsigned short requested = emitter->calculateRequestedParticles(elapsedTime);
	float timePoint = 0.0f;
	float timeInc = elapsedTime / requested;

	for (unsigned short i = 0; i < requested; ++i)
	{
		PUParticle3D *particle = static_cast<PUParticle3D*>(_particles[i]);
		particle->initForEmission();
		emitter->initParticleForEmission(particle);

		particle->direction = (/*getDerivedOrientation() * */particle->direction);
		particle->originalDirection = (/*getDerivedOrientation() * */particle->originalDirection);

		for (auto& it : _affectors) {
			if (it->isEnabled())
            {
				(static_cast<PUParticle3DAffector*>(it))->initParticleForEmission(particle);
            }
		}

		particle->position += (particle->direction * _particleSystemScaleVelocity * timePoint);
		// Increment time fragment
		timePoint += timeInc;
	}
}

const float PUParticleSystem3D::getDefaultWidth( void ) const
{
	return _defaultWidth;
}

void PUParticleSystem3D::setDefaultWidth( const float width )
{
	_defaultWidth = width;
}

const float PUParticleSystem3D::getDefaultHeight( void ) const
{
	return _defaultHeight;
}

void PUParticleSystem3D::setDefaultHeight( const float height )
{
	_defaultHeight = height;
}

const float PUParticleSystem3D::getDefaultDepth( void ) const
{
	return _defaultDepth;
}

void PUParticleSystem3D::setDefaultDepth( const float depth )
{
	_defaultDepth = depth;
}

bool PUParticleSystem3D::isExpired( PUParticle3D* particle, float timeElapsed )
{
	bool expired = particle->timeToLive < timeElapsed;
	if (expired)
	{
		// Set the flag to indicate that the particle has been expired
		particle->addEventFlags(PUParticle3D::PEF_EXPIRED);
	}

	return expired;
}

NS_CC_END
