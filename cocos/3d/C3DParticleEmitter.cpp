#include "Base.h"
#include "C3DParticleEmitter.h"
#include "C3DParticleSystem.h"

#include "C3DElementNode.h"
#include "C3DParticleSystemCommon.h"
#include "C3DParticleRender.h"


#define PARTICLE_COUNT_MAX                       100
#define PARTICLE_EMISSION_RATE                   10
#define PARTICLE_EMISSION_RATE_TIME_INTERVAL     1000.0f / (float)PARTICLE_EMISSION_RATE

namespace cocos3d
{

C3DParticleEmitter::C3DParticleEmitter(C3DParticleSystem* system) :
    _system(system),   
    _emissionRate(PARTICLE_EMISSION_RATE), _started(false), _ellipsoid(false),
    _sizeStartMin(1.0f), _sizeStartMax(1.0f),
    _ageMin(1000L), _ageMax(1000L),   
    _position(C3DVector3::zero()), _positionVar(C3DVector3::zero()),
    _velocity(C3DVector3::zero()), _velocityVar(C3DVector3::one()),
    _rotationPerParticleSpeedMin(0.0f), _rotationPerParticleSpeedMax(0.0f),
    _rotationSpeedMin(0.0f), _rotationSpeedMax(0.0f),
    _rotationAxis(C3DVector3::zero()), _rotation(C3DMatrix::identity()),    
    _orbitPosition(false), _orbitVelocity(false), _orbitAcceleration(false),
    _timePerEmission(PARTICLE_EMISSION_RATE_TIME_INTERVAL), _timeLast(0L), _timeRunning(0L)
{
   

}

C3DParticleEmitter::~C3DParticleEmitter()
{
       
}


void C3DParticleEmitter::load(C3DElementNode* properties)
{ 
    int emissionRate = (unsigned int)properties->getElement("emissionRate",(int*)0);
    if (emissionRate == 0)
    {
        emissionRate = PARTICLE_EMISSION_RATE;
    }

    bool ellipsoid = properties->getElement("ellipsoid",(bool*)0);

    float sizeStartMin = properties->getElement("sizeStartMin",(float*)0);
    float sizeStartMax = properties->getElement("sizeStartMax",(float*)0);
   
    long ageMin = properties->getElement("ageMin",(long*)0);
    long ageMax = properties->getElement("ageMax",(long*)0);	   

    C3DVector3 position;
    C3DVector3 positionVar;
    C3DVector3 velocity;
    C3DVector3 velocityVar;
   
    C3DVector3 rotationAxis;
    C3DVector3 rotationAxisVar;	
	
    properties->getElement("position", &position);
    properties->getElement("positionVar", &positionVar);
    properties->getElement("velocity", &velocity);
    properties->getElement("velocityVar", &velocityVar);
   
    float rotationPerParticleSpeedMin = properties->getElement("rotationPerParticleSpeedMin",&rotationPerParticleSpeedMin);
    float rotationPerParticleSpeedMax = properties->getElement("rotationPerParticleSpeedMax",&rotationPerParticleSpeedMax);
    float rotationSpeedMin = properties->getElement("rotationSpeedMin",&rotationSpeedMin);
    float rotationSpeedMax = properties->getElement("rotationSpeedMax",&rotationSpeedMax);
    properties->getElement("rotationAxis", &rotationAxis);
    properties->getElement("rotationAxisVar", &rotationAxisVar);
    bool orbitPosition = properties->getElement("orbitPosition",(bool*)0);
    bool orbitVelocity = properties->getElement("orbitVelocity",(bool*)0);
    bool orbitAcceleration = properties->getElement("orbitAcceleration",(bool*)0);
	
    setEmissionRate(emissionRate);
    setEllipsoid(ellipsoid);
    setSize(sizeStartMin, sizeStartMax);
    setAge(ageMin, ageMax);
   
    setPosition(position, positionVar);
    setVelocity(velocity, velocityVar);
  
    setRotationPerParticle(rotationPerParticleSpeedMin, rotationPerParticleSpeedMax);
    setRotation(rotationSpeedMin, rotationSpeedMax, rotationAxis, rotationAxisVar);
	
    setOrbit(orbitPosition, orbitVelocity, orbitAcceleration);
	    
}

void C3DParticleEmitter::save(C3DElementNode* properties)
{
	properties->setElement("emissionRate", &_emissionRate);
	properties->setElement("ellipsoid", &_ellipsoid);

	properties->setElement("sizeStartMin", &_sizeStartMin);
	properties->setElement("sizeStartMax", &_sizeStartMax);

	properties->setElement("ageMin", &_ageMin);
	properties->setElement("ageMax", &_ageMax);

	properties->setElement("position", &_position);
	properties->setElement("positionVar", &_positionVar);
	properties->setElement("velocity", &_velocity);
	properties->setElement("velocityVar", &_velocityVar);

	properties->setElement("rotationPerParticleSpeedMin",&_rotationPerParticleSpeedMin);
	properties->setElement("rotationPerParticleSpeedMax",&_rotationPerParticleSpeedMax);
	properties->setElement("rotationSpeedMin",&_rotationSpeedMin);
	properties->setElement("rotationSpeedMax",&_rotationSpeedMax);
	properties->setElement("rotationAxis", &_rotationAxis);
	properties->setElement("rotationAxisVar", &_rotationAxisVar);
	properties->setElement("orbitPosition",&_orbitPosition);
	properties->setElement("orbitVelocity",&_orbitVelocity);
	properties->setElement("orbitAcceleration",&_orbitAcceleration);
}

unsigned int C3DParticleEmitter::getEmissionRate() const
{
    return _emissionRate;
}

void C3DParticleEmitter::setEmissionRate(unsigned int rate)
{
    _emissionRate = rate;
    _timePerEmission = 1000.0f / (float)_emissionRate;
}


void C3DParticleEmitter::setEllipsoid(bool ellipsoid)
{
    _ellipsoid = ellipsoid;
}

void C3DParticleEmitter::setSize(float startMin, float startMax)
{
    _sizeStartMin = startMin;
    _sizeStartMax = startMax;
}

void C3DParticleEmitter::setSizeStartMin(float startMin)
{
	_sizeStartMin = startMin;
}
void C3DParticleEmitter::setSizeStartMax(float startMax)
{
	_sizeStartMax = startMax;
}

float C3DParticleEmitter::getSizeStartMin() const
{
    return _sizeStartMin;
}

float C3DParticleEmitter::getSizeStartMax() const
{
    return _sizeStartMax;
}


void C3DParticleEmitter::setAge(long ageMin, long ageMax)
{
    _ageMin = ageMin;
    _ageMax = ageMax;
}

void C3DParticleEmitter::setAgeMin(long ageMin)
{
	_ageMin = ageMin;
}
void C3DParticleEmitter::setAgeMax(long ageMax)
{
	_ageMax = ageMax;
}

long C3DParticleEmitter::getAgeMin() const
{
    return _ageMin;
}

long C3DParticleEmitter::getAgeMax() const
{
    return _ageMax;
}


void C3DParticleEmitter::setPosition(const C3DVector3& position, const C3DVector3& positionVar)
{
    _position.set(position);
    _positionVar.set(positionVar);
}

void C3DParticleEmitter::setPosition(const C3DVector3& position)
{
	_position = position;
}

void C3DParticleEmitter::setPositionVariance(const C3DVector3& positionVariance)
{
	_positionVar = positionVariance;
}

const C3DVector3& C3DParticleEmitter::getPosition() const
{
    return _position;
}

const C3DVector3& C3DParticleEmitter::getPositionVariance() const
{
    return _positionVar;
}

const C3DVector3& C3DParticleEmitter::getVelocity() const
{
    return _velocity;
}

const C3DVector3& C3DParticleEmitter::getVelocityVariance() const
{
    return _velocityVar;
}

void C3DParticleEmitter::setVelocity(const C3DVector3& velocity, const C3DVector3& velocityVar)
{
    _velocity.set(velocity);
    _velocityVar.set(velocityVar);
}
void C3DParticleEmitter::setVelocity(const C3DVector3& velocity)
{
	_velocity.set(velocity);
}

void C3DParticleEmitter::setVelocityVariance(const C3DVector3& velocityVariance)
{
	_velocityVar = velocityVariance;
}

void C3DParticleEmitter::setRotationPerParticle(float speedMin, float speedMax)
{
    _rotationPerParticleSpeedMin = speedMin;
    _rotationPerParticleSpeedMax = speedMax;
}

void C3DParticleEmitter::setRotationPerParticleSpeedMin(float speedMin)
{
	_rotationPerParticleSpeedMin = speedMin;
}

void C3DParticleEmitter::setRotationPerParticleSpeedMax(float speedMax)
{
	_rotationPerParticleSpeedMax = speedMax;
}

float C3DParticleEmitter::getRotationPerParticleSpeedMin() const
{
    return _rotationPerParticleSpeedMin;
}

float C3DParticleEmitter::getRotationPerParticleSpeedMax() const
{
    return _rotationPerParticleSpeedMax;
}

void C3DParticleEmitter::setRotation(float speedMin, float speedMax, const C3DVector3& axis, const C3DVector3& axisVariance)
{
    _rotationSpeedMin = speedMin;
    _rotationSpeedMax = speedMax;
    _rotationAxis.set(axis);
    _rotationAxisVar.set(axisVariance);
}

void C3DParticleEmitter::setRotationAxis(const C3DVector3& axis)
{
	_rotationAxis.set(axis);
}

void C3DParticleEmitter::setRotationAxisVariance(const C3DVector3& variance)
{
	_rotationAxisVar.set(variance);
}

float C3DParticleEmitter::getRotationSpeedMin() const
{
    return _rotationSpeedMin;
}

float C3DParticleEmitter::getRotationSpeedMax() const
{
    return _rotationSpeedMax;
}

const C3DVector3& C3DParticleEmitter::getRotationAxis() const
{
    return _rotationAxis;
}

const C3DVector3& C3DParticleEmitter::getRotationAxisVariance() const
{
    return _rotationAxisVar;
}



void C3DParticleEmitter::setOrbit(bool orbitPosition, bool orbitVelocity, bool orbitAcceleration)
{
    _orbitPosition = orbitPosition;
    _orbitVelocity = orbitVelocity;
    _orbitAcceleration = orbitAcceleration;
}

long C3DParticleEmitter::generateScalar(long min, long max)
{
    // Note: this is not a very good RNG, but it should be suitable for our purposes.
    long r = 0;
    for (unsigned int i = 0; i < sizeof(long)/sizeof(int); i++)
    {
        r = r << 8; // sizeof(int) * CHAR_BITS
        r |= rand();
    }

    // Now we have a random long between 0 and MAX_LONG.  We need to clamp it between min and max.
    r %= max - min;
    r += min;

    return r;
}

float C3DParticleEmitter::generateScalar(float min, float max)
{
    return min + (max - min) * MATH_RANDOM_0_1();
}

void C3DParticleEmitter::generateVectorInRect(const C3DVector3& base, const C3DVector3& variance, C3DVector3* dst)
{
    // Scale each component of the variance vector by a random float
    // between -1 and 1, then add this to the corresponding base component.
    dst->x = base.x + variance.x * MATH_RANDOM_MINUS1_1();
    dst->y = base.y + variance.y * MATH_RANDOM_MINUS1_1();
    dst->z = base.z + variance.z * MATH_RANDOM_MINUS1_1();
}

void C3DParticleEmitter::generateVectorInEllipsoid(const C3DVector3& center, const C3DVector3& scale, C3DVector3* dst)
{
    // Generate a point within a unit cube, then reject if the point is not in a unit sphere.
    do
    {
        dst->x = MATH_RANDOM_MINUS1_1();
        dst->y = MATH_RANDOM_MINUS1_1();
        dst->z = MATH_RANDOM_MINUS1_1();
    } while (dst->length() > 1.0f);
    
    // Scale this point by the scaling vector.
    dst->x *= scale.x;
    dst->y *= scale.y;
    dst->z *= scale.z;

    // Translate by the center point.
    dst->add(center);
}

void C3DParticleEmitter::generateVector(const C3DVector3& base, const C3DVector3& variance, C3DVector3* dst, bool ellipsoid)
{
    if (ellipsoid)
    {
        generateVectorInEllipsoid(base, variance, dst);
    }
    else
    {
        generateVectorInRect(base, variance, dst);
    }
}

void C3DParticleEmitter::emit(unsigned int particleCount)
{
    // Limit particleCount so as not to go over _particleCountMax.
	if (particleCount + _system->_validParticleCount > _system->_particleCountMax)
    {
        particleCount = _system->_particleCountMax - _system->_validParticleCount;
    }

    C3DVector3 translation;
	
    C3DMatrix world = _system->getWorldMatrix();
    world.getPosition(&translation);

    // Take translation out of world matrix so it can be used to rotate orbiting properties.
    world.m[12] = 0.0f;
    world.m[13] = 0.0f;
    world.m[14] = 0.0f;
	

    // Emit the new particles.
	C3DParticle**& _particles = _system->_particles;
	int& _validParticleCount = _system->_validParticleCount;
	
    for (int i = 0; i < particleCount; i++)
    {
		C3DParticle* p = _particles[_validParticleCount++];				
		
        p->_age = generateScalar(_ageMin, _ageMax);
		p->_ageStart = p->_age;
		int Frm = _system->getParticleRender()->getSpriteFrameRandomOffset();
		p->_frameStart = (Frm == 0 ? 0 : generateScalar((long)0, (long)Frm));
        p->_size = generateScalar(_sizeStartMin, _sizeStartMax);
        p->_rotationPerParticleSpeed = generateScalar(_rotationPerParticleSpeedMin, _rotationPerParticleSpeedMax);
        p->_angle = generateScalar(0.0f, p->_rotationPerParticleSpeed);
        p->_rotationSpeed = generateScalar(_rotationSpeedMin, _rotationSpeedMax);

        // Only initial position can be generated within an ellipsoidal domain.
        generateVector(_position, _positionVar, &p->_position, _ellipsoid);
        generateVector(_velocity, _velocityVar, &p->_velocity, false);    
        generateVector(_rotationAxis, _rotationAxisVar, &p->_rotationAxis, false);

        // Initial position, velocity and acceleration can all be relative to the emitter's transform.
        // Rotate specified properties by the node's rotation.
        if (_orbitPosition)
        {
            world.transformPoint(p->_position, &p->_position);
        }

        if (_orbitVelocity)
        {
            world.transformPoint(p->_velocity, &p->_velocity);
        }
		     

        // The rotation axis always orbits the node.
        if (p->_rotationSpeed != 0.0f && !p->_rotationAxis.isZero())
        {
            world.transformPoint(p->_rotationAxis, &p->_rotationAxis);
        }


        // Translate position relative to the node's world space.
        p->_position.add(translation);                
    }
}

void C3DParticleEmitter::update(long elapsedTime)
{  
    // Calculate how much time has passed since we last emitted particles.
    _timeRunning += elapsedTime;

    // How many particles should we emit this frame?
    unsigned int emitCount = _timeRunning / _timePerEmission;            
   
    _timeRunning -= (int) (emitCount * _timePerEmission);    

	if(emitCount > 0)
		emit(emitCount);
   
	
}

C3DParticleEmitter* C3DParticleEmitter::clone(C3DParticleSystem* system) const
{
    C3DParticleEmitter* emitter = new C3DParticleEmitter(system);
    
    emitter->_emissionRate = _emissionRate;
    emitter->_started = _started;
    emitter->_ellipsoid = _ellipsoid;
    emitter->_sizeStartMin = _sizeStartMin;
    emitter->_sizeStartMax = _sizeStartMax;
    emitter->_ageMin = _ageMin;
    emitter->_ageMax = _ageMax;
    
    emitter->_position = _position;
    emitter->_positionVar = _positionVar;
    emitter->_velocity = _velocity;
    emitter->_velocityVar = _velocityVar;
    
    emitter->_rotationPerParticleSpeedMin = _rotationPerParticleSpeedMin;
    emitter->_rotationPerParticleSpeedMax = _rotationPerParticleSpeedMax;
    emitter->_rotationSpeedMin = _rotationSpeedMin;
    emitter->_rotationSpeedMax = _rotationSpeedMax;
    emitter->_rotationAxis = _rotationAxis;
    emitter->_rotationAxisVar = _rotationAxisVar;
    emitter->_rotation = _rotation;
    
    emitter->_orbitPosition = _orbitPosition;
    emitter->_orbitVelocity = _orbitVelocity;
    emitter->_orbitAcceleration = _orbitAcceleration;
    emitter->_timePerEmission = _timePerEmission;
    emitter->_timeLast = _timeLast;
    emitter->_timeRunning = _timeRunning;

    return emitter;
}

}
