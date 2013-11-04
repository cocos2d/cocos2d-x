#ifndef TRANSFORM_PSA_H_
#define TRANSFORM_PSA_H_

#include "C3DTransform.h"
#include "C3DMesh.h"
#include "C3DVector2.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DTexture.h"
#include "Rectangle.h"

#include "C3DElementNode.h"
#include "cocos2d.h"
#include "C3DParticleSystemCommon.h"
namespace cocos3d
{


class C3DElementNode;
class C3DParticleSystem;

/**
Defines particle system transform action
It is a compulsory component for particle system
It updates particle rotation, age, size, frame, velocity, and so on
*/
class C3DTransformPSA : public C3DBaseParticleAction
{
public:
	
	/**
     * Constructor & Destructor
     */
	C3DTransformPSA(C3DParticleSystem* system);
	virtual ~C3DTransformPSA();
	
	/**
     * load & save particle action
     */
	virtual	void load(C3DElementNode* properties);
	virtual void save(C3DElementNode* properties);

	/**
     * particle action, change particle state by elapsed time
     */
	virtual void action(long elapsedTime);

	/**
     * get & set end size
     */
    void setEndSize(float size) { _endSize = size; }
	float getEndSize() const { return _endSize; }

	/**
     * get & set size rate
     */
	void setSizeRate( float rate) { _sizeRate = rate; }
	float getSizeRate() const { return _sizeRate; }
    
	/**
     * clone method
     */
    virtual C3DBaseParticleAction* clone(C3DParticleSystem* system) const;

private:

	// property
    C3DMatrix _rotation;

	float _endSize;		// Eventual size of the particles.
	float _sizeRate;		// Increment per second towards the size.


};

}

#endif
