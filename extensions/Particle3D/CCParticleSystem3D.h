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

#ifndef __CC_PARTICLE_SYSTEM_3D_H__
#define __CC_PARTICLE_SYSTEM_3D_H__

#include "2d/CCNode.h"
#include "math/CCMath.h"
#include <vector>
#include <map>
#include <list>

NS_CC_BEGIN

/**
 * 3d particle system
 */
class Particle3DEmitter;
class Particle3DAffector;
class Particle3DRender;

struct CC_DLL Particle3D
{
    Particle3D();
    virtual ~Particle3D();
    // property of particles
    Vec3 position; // position
    Quaternion orientation;//  Orientation of the particle.
    Vec4 color;  // particle color
    Vec2 lb_uv; // left bottom uv
    Vec2 rt_uv; // right top uv
    float width;//Own width
    float height;//Own height
    float depth;//Own depth
    
    //user defined property
    std::map<std::string, void*> userDefs;
};

class CC_DLL ParticlePool
{
public:
    typedef std::vector<Particle3D *> PoolList;
    typedef std::vector<Particle3D *>::iterator PoolIterator;

    ParticlePool();
    ~ParticlePool();

    Particle3D* createParticle();
    void lockLatestParticle();
    void lockAllParticles();
    Particle3D* getFirst();
    Particle3D* getNext();
    const PoolList& getActiveParticleList() const;
    void addParticle(Particle3D *particle);
    bool empty() const;
    void removeAllParticles(bool needDelete = false);

private:

    PoolIterator _releasedIter;
    PoolList _released;
    PoolList _locked;
};

class CC_DLL ParticleSystem3D : public Node, public BlendProtocol
{
public:
    enum class State
    {
        STOP,
        RUNNING,
        PAUSE,
    };
    
    virtual void update(float delta) override;
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    
    virtual const BlendFunc &getBlendFunc() const override;
    
    /**
     * particle system play control
     */
    virtual void startParticleSystem();
    
    /**
     * stop particle
     */
    virtual void stopParticleSystem();
    
    /**
     * pause particle
     */
    virtual void pauseParticleSystem();
    
    /**
     * resume particle
     */
    virtual void resumeParticleSystem();
    
    /**
     * set emitter for particle system, can set your own particle emitter
     */
    void setEmitter(Particle3DEmitter* emitter);
    /**
     * set particle render, can set your own particle render
     */
    void setRender(Particle3DRender* render);
    /**
     * add particle affector
     */
    void addAffector(Particle3DAffector* affector);
    
    /**
     * remove affector by index
     */
    void removeAffector(int index);
    
    /**
     * remove all particle affector
     */
    void removeAllAffector();

        /** 
    */
    unsigned int getParticleQuota() const;
    void setParticleQuota(unsigned int quota);
    
    /**
     * get particle affector by index
     */
    Particle3DAffector* getAffector(int index);
    
    const ParticlePool& getParticlePool()
    {
        return  _particlePool;
    }
    
    virtual int getAliveParticleCount() const
    {
        return 0;
    }
    
    State getState() const { return _state; }

    bool isKeepLocal(void) const { return _keepLocal; }
    void setKeepLocal(bool keepLocal);

     /** Enables or disables the system.
     */
    void setEnabled (bool enabled);
    
    bool isEnabled(void) const { return _isEnabled; }

CC_CONSTRUCTOR_ACCESS:
    ParticleSystem3D();
    virtual ~ParticleSystem3D();
    
protected:
    
    State                            _state;
    Particle3DEmitter*               _emitter;
    std::vector<Particle3DAffector*> _affectors;
    Particle3DRender*                _render;
    
    //particles
    ParticlePool                _particlePool;

    unsigned int            _particleQuota;
    
    BlendFunc                        _blend;

    bool _keepLocal;
    bool _isEnabled;
};

NS_CC_END

#endif
