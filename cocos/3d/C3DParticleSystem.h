#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include "C3DTransform.h"
#include "C3DMesh.h"
#include "C3DVector2.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DTexture.h"
#include "Rectangle.h"

#include "C3DElementNode.h"
#include "cocos2d.h"
#include "C3DNode.h"

namespace cocos3d
{

class Node;
class C3DElementNode;
class C3DParticleEmitter;
class C3DParticleRender;
class C3DParticleAction;
class C3DBaseParticleAction;
class C3DParticle;

/**
	C3DParticleSystem represents a 3D particle system. It is loaded from .particle files.
	A C3DParticleSystem is made up of C3DParticleEmitter, C3DParticleRender, and some C3DBaseParticleAction.  
	usage: 
	1.call load(particlename) load a particle
	2.call update() and draw() every frame
	3.control the particle system use start(), stop(), pause(), resume()
*/
class C3DParticleSystem : public C3DNode
{
	friend class  C3DParticleEmitter;
	friend class  C3DParticleRender;
	friend class  C3DScalerPSA;
	friend class  C3DTintPSA;
	friend class  C3DTransformPSA;
	friend class  C3DForcePSA;
public:	

	/**
     * particle state.
     */
	enum ParticleState
	{
		STOP,
		RUNNING,
		PAUSE,
	};

	/**
     * constructor & destructor.
     */
	C3DParticleSystem(const char* id);
    ~C3DParticleSystem();
	
	/**
     * create method.
     */
	static C3DParticleSystem* create(const char* id);

	/**
     * class type inherit from C3DNode.
     */
	C3DNode::Type getType() const;

	/**
     * load & save particle system .particle.
     */
    bool load(const char* fileName);
	bool save(const char* szFile);
     
	/**
     * particle system control.
     */
    void start();
    void stop();
	void pause();
	void resume();

	/**
     * get particle state
     */
	ParticleState getParticleState() const { return _state; }
	
	/**
     * is particle system start ? 
     */
    bool isStarted() const;
	
	/**
     * is particle active ?
     */
    bool isActive() const;
	   
	/**
     * update routine
     */
    virtual void update(long elapsedTime);
	   
	/**
     * particle system draw
     */
    void draw();

	/**
     * add action to particle system to affect particles movement
     */
	void addAction(C3DBaseParticleAction* action);

	/**
     * remove particle system action
     */
	void removeAction(C3DBaseParticleAction* action);

	/**
     * get particle emitter
     */
	C3DParticleEmitter* getParticleEmitter() { return _emitter; }

	/**
     * get particle actions
     */
	const std::vector<C3DBaseParticleAction*>& getParticleActions() { return _actions; }

	/**
     * get particle render
     */
	C3DParticleRender* getParticleRender() { return _render; }

	/**
     * clone method
     */
    virtual C3DParticleSystem* clone(CloneContext& context) const;

	/**
     * set particle system scale
     */
	virtual void setScale(float scale);

	/**
     * set & get particle system last time(ms)
     */
	void setTimeLast(long timelast) 
	{ 
		_timeLast = timelast; 
	}
	long getTimeLast() const { return _timeLast; }

	/**
     * set & get particle system start time(ms)
     */
	void setTimeStart(long timestart) { _timeStart = timestart; }
	long getTimeStart() const { return _timeStart; }

	/**
     * get last time after start(ms)
     */
	long getTimeRunning() const { return _timeRunning; }

	/**
     * get & set particle maximum count
     */
	int getParticleCountMax() const { return _particleCountMax; }
	void setParticleCountMax(int particleCountMax);

	/**
     * particle system call back, called when particle system state changed 
     */
	void setStateChangeCallBack(void (*StateChanged)(const C3DParticleSystem* particle, ParticleState oldState, ParticleState newState));
    
protected:
    
	/**
     * copy method
     */
    virtual void copyFrom(const C3DTransform* other, CloneContext& context);
    
private:
	/**
     * load & save
     */
	bool load(C3DElementNode* psNode);
	void save(C3DElementNode* &psNode);

private:
		
	// particle system property

    int _particleCountMax;
    int _validParticleCount;

	C3DParticle* _p;
	C3DParticle** _particles;

	int _numTintAction;
       
    bool _started;

  
    long _timeLast; // particle system last time
    long _timeRunning; // particle system running time
	long _timeStart; // particle system start time

	C3DParticleEmitter* _emitter;
    C3DParticleRender* _render;
	std::vector<C3DBaseParticleAction*> _actions;

	ParticleState _state;

	void (*StateChanged)(const C3DParticleSystem* particle, ParticleState oldState, ParticleState newState);
};

}

#endif
