#ifndef FORCE_PSA_H_
#define FORCE_PSA_H_

#include "C3DVector3.h"
#include "C3DElementNode.h"
#include "C3DParticleSystemCommon.h"

namespace cocos3d
{


class C3DElementNode;
class C3DParticleSystem;

/** 
A C3DForcePSA affects particle's action by force.
It is a optional for a particle system
*/
class C3DForcePSA : public C3DBaseParticleAction
{
public:
	
	/** 
	constructor & destructor
	*/
	C3DForcePSA(C3DParticleSystem* system);
	virtual ~C3DForcePSA();
	
	/** 
	load C3DForcePSA from element node
	*/
	virtual	void load(C3DElementNode* properties);

	/** 
	save C3DForcePSA to element node
	*/
	virtual void save(C3DElementNode* properties);

	/** 
	change particle state, called by C3DParticleSystem
	*/
	virtual void action(long elapsedTime);
	
	/** 
	set & get force affect the particles
	*/
	void setForce(const C3DVector3& force) { _force = force; }
	C3DVector3 getForce() const { return _force; }
    
	/** 
	clone method
	*/
    virtual C3DBaseParticleAction* clone(C3DParticleSystem* system) const;

private:

   C3DVector3 _force;

	


};

}

#endif
