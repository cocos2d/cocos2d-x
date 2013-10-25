#ifndef PARTICLEACTION_H_
#define PARTICLEACTION_H_

#include "C3DTransform.h"
#include "C3DMesh.h"
#include "C3DVector2.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DTexture.h"
#include "Rectangle.h"

#include "C3DElementNode.h"
#include "cocos2d.h"

namespace cocos3d
{

class Node;
class C3DElementNode;
class C3DParticleSystem;

/**
Defines properties for single particle
*/
class C3DParticle
{
public:
	/**
     * Constructor & Destructor
     */
	C3DParticle()
	{
		_visible = true;
		_frame = 0;

	};
	virtual ~C3DParticle(){};

public:
    C3DVector3 _position;
    C3DVector3 _velocity;
    C3DVector3 _acceleration;
    C3DVector4 _color;
    float _rotationPerParticleSpeed;
    C3DVector3 _rotationAxis;
    float _rotationSpeed;
    float _angle;
    long _age;
    float _size;   
    bool _visible;
	int _frame;
	int _frameStart;
	long _ageStart;//
};

/**
Base class of particle action
A class affect the particle's movement
*/
class C3DBaseParticleAction
{
public:
	/**
     * Constructor & Destructor
     */
	C3DBaseParticleAction(C3DParticleSystem* system);	
	virtual ~C3DBaseParticleAction();	

	/**
     * load & particle action property
     */
	virtual	void load(C3DElementNode* psaNode);
	virtual void save(C3DElementNode* psaNode);

	/**
     * particle action, affect particle movement
     */
	virtual void action(long elapsedTime){};
    
	/**
     * particle action clone method
     */
    virtual C3DBaseParticleAction* clone(C3DParticleSystem* system) const;
    
protected:
    
	/**
     * copy particle action
     */
    virtual void copyFrom(const C3DBaseParticleAction* other);

public:
	C3DParticleSystem* _system;
	char* _name;
};


}

#endif
