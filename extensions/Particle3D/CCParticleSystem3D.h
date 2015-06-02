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

class Particle3DEmitter;
class Particle3DAffector;
class Particle3DRender;

/**
* @addtogroup _3d
* @{
*/

/** @struct Particle3D
*@brief @~english Particle3D is a container of particle Properties.
 @~chinese Particle3D 是粒子属性的容器
*/
struct CC_DLL Particle3D
{
    Particle3D();
    virtual ~Particle3D();

    Vec3 position; ///< position
    Quaternion orientation;///<  Orientation of the particle
    Vec4 color;  ///< particle color
    Vec2 lb_uv; ///< left bottom uv
    Vec2 rt_uv; ///< right top uv
    float width;///<Own width
    float height;///<Own height
    float depth;///<Own depth
    
    std::map<std::string, void*> userDefs; ///<user defined property
};

/** @class DataPool 
*@brief @~english DataPool is a data pool, used for recycling data.
 @~chinese DataPool 是数据池，用以数据的再利用。
*/
template<typename T>
class CC_DLL DataPool
{
public:
    typedef typename std::list<T*> PoolList;
    typedef typename std::list<T*>::iterator PoolIterator;

    DataPool(){};
    ~DataPool(){};

    /**
    * @~english Allocates a data from unallocated pool.
    * @~chinese 从未分配池中取出一个数据
    * @return @~english A allocated data. @~chinese 一个已分配的数据。
    */
    T* createData(){
        if (_locked.empty()) return nullptr;
        T* p = _locked.front();
        //_released.push_back(p);
        //_locked.erase(_locked.begin());
        _released.splice(_released.end(), _locked, _locked.begin());
        return p;
    };

    /**
    * @~english Push current data into unallocated pool.
    * @~chinese 把当前的数据放入未分配池。
    */
    void lockLatestData(){
        _locked.push_back(*_releasedIter);
        _releasedIter = _released.erase(_releasedIter);
        if (_releasedIter != _released.begin() && _releasedIter != _released.end())
        {
            --_releasedIter;
        }
    };

    /**
    * @~english Push the specified data into unallocated pool.
    * @~chinese 把指定的数据放入未分配池。
    * @param data   @~english The pointer of data. @~chinese 数据的指针。
    */
    void lockData(T *data){
        PoolIterator tempIter = _releasedIter;
        T *ptr = getFirst();
        while (ptr)
        {
            if (ptr == data) break;
            ptr = getNext();
        }
        if (ptr)
            lockLatestData();
        _releasedIter = tempIter;
    }

    /**
    * @~english Push all allocated datas into unallocated pool.
    * @~chinese 把已分配池中的所有数据放入未分配池中。
    */
    void lockAllDatas(){
        _locked.splice(_locked.end(), _released);
        //_locked.insert(_locked.end(), _released.begin(), _released.end());
        //_released.clear();
        _releasedIter = _released.begin();
    };

    /**
    * @~english Get the first data of allocated pool.
    * @~chinese 获取已分配池中的第一个数据。
    * @return @~english The pointer of data. @~chinese 数据的指针。
    */
    T* getFirst(){
        _releasedIter = _released.begin();
        if (_releasedIter == _released.end()) return nullptr;
        return *_releasedIter;
    };

    /**
    * @~english Get the next data of allocated pool.
    * @~chinese 获取已分配池中的下一个数据。
    * @return @~english The pointer of data. @~chinese 数据的指针。
    */
    T* getNext(){
        if (_releasedIter == _released.end()) return nullptr;
        ++_releasedIter;
        if (_releasedIter == _released.end()) return nullptr;
        return *_releasedIter;
    };

    /**
    * @~english Get the allocated pool.
    * @~chinese 获取已分配池。
    * @return @~english The allocated pool. @~chinese 已分配池。
    */
    const PoolList& getActiveDataList() const { return _released; };

    /**
    * @~english Get the unallocated pool.
    * @~chinese 获取未分配池。
    * @return @~english The unallocated pool. @~chinese 未分配池。
    */
    const PoolList& getUnActiveDataList() const { return _locked; };

    /**
    * @~english add a new data into unallocated pool.
    * @~chinese 添加一个新数据到未分配池中。
    */
    void addData(T* data){
        _locked.push_back(data); 
    };

    /**
    * @~english To determine whether the allocated pool is empty.
    * @~chinese 判断已分配池是否为空。
    */
    bool empty() const { return _released.empty(); };

    /**
    * @~english Remove all datas.
    * @~chinese 移除所有的数据。
    */
    void removeAllDatas(){
        lockAllDatas();
        for (auto iter : _locked){
            delete iter;
        }
        _locked.clear();
    };

private:

    PoolIterator _releasedIter;///< the iterater of allocated pool
    PoolList _released;///< allocated pool
    PoolList _locked;///< unallocated pool
};

typedef DataPool<Particle3D> ParticlePool;

/** @class ParticleSystem3D
*@brief @~english ParticleSystem3D is a base class, define interfaces.
 specific implementation decisions by different particle systems.
 a particle system consist of:
 - one Emitter(how emitted particles)
 - multiple affector(how particles motion)
 - one renderer(how to render the particles)

 @~chinese ParticleSystem3D 是3D粒子系统的基类，定义了3D粒子系统所需的各种接口。
 具体的实现由不同的粒子系统决定。
 一个粒子系统组成：
 - 一个发射器(如何发射粒子)
 - 多个影响器(粒子如何运动)
 - 一个渲染器(粒子如何渲染)
*/
class CC_DLL ParticleSystem3D : public Node, public BlendProtocol
{
public:

    enum class State
    {
        STOP,
        RUNNING,
        PAUSE,
    };
    
    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see node update(float delta);
    */
    virtual void update(float delta) override;
    
    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see node draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    /**
    * @~english Set the blend function.
    * @~chinese 设置透明的混合方程。
    * @param blendFunc   @~english The parameter of blend. @~chinese 混合参数。
    * @see glBlendFunc(GLenum sfactor,GLenum dfactor);
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    
    /**
    * @~english Get the blend function.
    * @~chinese 获取透明的混合方程。
    * @return @~english The parameter of blend. @~chinese 混合参数。
    */
    virtual const BlendFunc &getBlendFunc() const override;
    
    /**
    * @~english Start particle system simulation.
    * @~chinese 开始粒子系统模拟。
    */
    virtual void startParticleSystem();
    
    /**
    * @~english Stop particle system simulation.
    * @~chinese 停止粒子系统模拟。
    */
    virtual void stopParticleSystem();
    
    /**
    * @~english Pause particle system simulation.
    * @~chinese 暂停粒子系统模拟。
    */
    virtual void pauseParticleSystem();
    
    /**
    * @~english Resume particle system simulation.
    * @~chinese 恢复粒子系统模拟。
    */
    virtual void resumeParticleSystem();
    
    /**
    * @~english Set Emitter.
    * @~chinese 设置发射器。
    * @param emitter   @~english The pointer of emitter. @~chinese 发射器指针。
    */
    void setEmitter(Particle3DEmitter* emitter);

    /**
    * @~english Set Render.
    * @~chinese 设置渲染器。
    * @param render   @~english The pointer of render. @~chinese 渲染器指针。
    */
    void setRender(Particle3DRender* render);

    /**
    * @~english Add one affector.
    * @~chinese 添加一个影响器。
    * @param affector   @~english The pointer of affector. @~chinese 影响器指针。
    */
    void addAffector(Particle3DAffector* affector);
    
    /**
    * @~english Remove one affector.
    * @~chinese 移除一个影响器。
    * @param index   @~english The index of affector. @~chinese 影响器的索引号。
    */
    void removeAffector(int index);
    
    /**
    * @~english Remove all affectors.
    * @~chinese 移除所有的影响器。
    */
    void removeAllAffector();

    /**
    * @~english Get the quota of particle.
    * @~chinese 获取可发射的粒子数量上限。
    * @return @~english The quota. @~chinese 上限值。
    */
    unsigned int getParticleQuota() const;

    /**
    * @~english Set particle quota.
    * @~chinese 设置可发射粒子最大上限。
    * @param quota   @~english The quota. @~chinese 上限值。
    */
    void setParticleQuota(unsigned int quota);
    
    /**
    * @~english Get one affector.
    * @~chinese 获取发射器。
    * @return @~english The pointer of affector. @~chinese 发射器指针。
    */
    Particle3DAffector* getAffector(int index);
    
    /**
    * @~english Get particle pool.
    * @~chinese 获取粒子池。
    * @return @~english The particle pool. @~chinese 粒子池。
    */
    const ParticlePool& getParticlePool()
    {
        return  _particlePool;
    }
    
    /**
    * @~english Get the number of alive particles .
    * @~chinese 获取存活的粒子数量。
    * @return @~english The number of alive particles. @~chinese 存活的粒子数量。
    */
    virtual int getAliveParticleCount() const
    {
        return 0;
    }
    
    /**
    * @~english Get the state of particle system(running, paused, stopped).
    * @~chinese 获取当前粒子系统的状态(运行、暂停、停止)。
    * @return @~english The state. @~chinese 当前状态。
    */
    State getState() const { return _state; }

    /**
    * @~english Checks whether the particle using local coordinate.
    * @~chinese 判断是否粒子是否采用局部坐标系。
    * @return @~english Whether the particle using local coordinate. @~chinese 粒子是否采用局部坐标系。
    */
    bool isKeepLocal(void) const { return _keepLocal; }

    /**
    * @~english Set the particle using local coordinate or world coordinate.
    * @~chinese 设置粒子采用局部坐标系或全局坐标系。
    * @return @~english Whether the particle using local coordinate. @~chinese 粒子是否采用局部坐标系。
    */
    void setKeepLocal(bool keepLocal);

    /**
    * @~english Set the particle System enable or disable.
    * @~chinese 设置粒子系统可用或不可用。
    * @param enabled @~english Whether the particle system enabled. @~chinese 粒子系统是否可用。
    */
    void setEnabled (bool enabled);
    
    /**
    * @~english Get the particle System enabled.
    * @~chinese 获取粒子系统是否可用。
    * @return @~english Whether the particle system enabled. @~chinese 粒子系统是否可用。
    */
    bool isEnabled(void) const { return _isEnabled; }

CC_CONSTRUCTOR_ACCESS:
    ParticleSystem3D();
    virtual ~ParticleSystem3D();
    
protected:
    
    State                            _state; ///< current state
    Particle3DEmitter*               _emitter; ///< the emitter
    std::vector<Particle3DAffector*> _affectors; ///< the list of affector
    Particle3DRender*                _render; ///< the renderer
    
    //particles
    ParticlePool                     _particlePool; ///< particle pool
    int                              _aliveParticlesCnt; ///< the number of alive particles
    unsigned int                     _particleQuota; ///< the quota of particle
    
    BlendFunc                        _blend; ///< the blend function

    bool _keepLocal; ///< use local coordinate
    bool _isEnabled;
};

// end of _3d group
/// @}

NS_CC_END

#endif
