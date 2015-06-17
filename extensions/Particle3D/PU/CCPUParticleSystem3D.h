/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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

#ifndef __CC_PU_PARTICLE_SYSTEM_3D_H__
#define __CC_PU_PARTICLE_SYSTEM_3D_H__

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticleSystem3D.h"
#include <vector>
#include <map>

NS_CC_BEGIN

class PUListener;
class PUObserver;
class PUBehaviour;
class PUEmitter;
class PUAffector;
class Particle3DRender;

/**
* @addtogroup _3d
* @{
*/

enum PUComponentType
{
    CT_PARTICLE,
    CT_SYSTEM,
    CT_TECHNIQUE,
    CT_EMITTER,
    CT_AFFECTOR,
    CT_OBSERVER
};

/** @struct PUParticle3D
*@brief @~english PUParticle3D inherit from Particle3D, includes all properties of PU particles.
 @~chinese PUParticle3D继承自Particle3D，包括PU粒子的所有属性。
*/
struct CC_DLL PUParticle3D : public Particle3D
{
    /**
    @property DEFAULT_TTL
    @static
    @~english Default time to alive
    @~chinese 粒子默认的生存时间
    */
    static float DEFAULT_TTL;

    /**
    @property DEFAULT_MASS
    @static
    @~english Default mass
    @~chinese 粒子默认的质量
    */
    static float DEFAULT_MASS;

    PUParticle3D();
    virtual ~PUParticle3D();

    typedef std::vector<PUBehaviour*> ParticleBehaviourList;

    enum ParticleType
    {
        PT_VISUAL,
        PT_TECHNIQUE,
        PT_EMITTER,
        PT_AFFECTOR,
        PT_SYSTEM,
    };

        /** Enumeration which lists a number of reserved event flags. Although custom flags can be used to
        indicate that a certain condition occurs, the first number of flags may not be used as custom flags.
    */
    enum ReservedParticleEventFlags
    {
        PEF_EXPIRED = 1<<0,
        PEF_EMITTED = 1<<1,
        PEF_COLLIDED = 1<<2
    };

    Ref *particleEntityPtr;
    PUEmitter* parentEmitter;

    Ref *visualData;

    ParticleType particleType;
    ///< Values that are assigned as soon as the particle is emitted (non-transformed)
    ///< Vec3 positionInWorld;
    Vec3 originalPosition;
    Vec3 latestPosition;
    ///< Direction (and speed)
    Vec3 direction;
    Vec3 originalDirection;
    float originalDirectionLength; ///< Length of the direction that has been set
    float originalVelocity;
    float originalScaledDirectionLength; ///< Length of the direction after multiplication with the velocity

    /** The rotation axis is used in combination with orientation. Because the rotation axis is part
        of the particle itself, it can be changed independently. */
    Vec3 rotationAxis;
    /** Current and original colour */

    Vec4 originalColor;

    /** The zRotationSpeed is used in combination with zRotation and defines tha actual rotationspeed
        in 2D. */
    float zRotationSpeed; //radian

    //Quaternion orientationInWorld;

    /** The orientation of the particle
    @remarks
        The orientation of the particle is only visible if the Particle Renderer - such as the Box renderer - 
        supports orientation.
    */
    Quaternion originalOrientation;


    /** The rotation is used in combination with orientation. Because the rotation speed is part
        of the particle itself, it can be changed independently. */
    float rotationSpeed;

    /** Radius of the particle, to be used for inter-particle collision and such.
    */
    float radius;

    ParticleBehaviourList behaviours;
    void copyBehaviours(const ParticleBehaviourList &list);

    float calculateVelocity() const;

    void setOwnDimensions(float newWidth, float newHeight, float newDepth);
    void calculateBoundingSphereRadius();

    void initForEmission();
    void initForExpiration(float timeElapsed);
    void process(float timeElapsed);

    /** Does this particle have it's own dimensions? */
    bool ownDimensions;

    /** Sets the event flags.
    */
    inline void setEventFlags(unsigned int flags) {eventFlags = flags;}

    /** As setEventFlags, except the flags passed as parameters are appended to the
        existing flags on this object.
    */
    inline void addEventFlags(unsigned int flags) {eventFlags |= flags;}
            
    /** The flags passed as parameters are removed from the existing flags.
    */
    inline void removeEventFlags(unsigned int flags) {eventFlags &= ~flags;}
        
    /** Return the event flags.
    */
    inline unsigned int getEventFlags() const {return eventFlags;}

    /** Determines whether it has certain flags set.
    */
    inline bool hasEventFlags(unsigned int flags) const {return (eventFlags & flags) != 0;}

    unsigned int eventFlags; ///<event flags

    /** Returns true if the particle is freezed and doesn't move anymore.
    @remarks
    Although it is freezed, repositioning the particle is still possible.
    */
    bool isFreezed(void) const
    {
        return freezed;
    }
    
    /** Freeze the particle, so it doesn't move anymore.
    */
    void setFreezed(bool fzd)
    {
        freezed = fzd;
    }
    bool freezed;///< freezed

    ///< Time to live, number of seconds left of particles natural life
    float timeToLive;

    ///< Total Time to live, number of seconds of particles natural life
    float totalTimeToLive;

    ///< The timeFraction is calculated every update. It is used in other observers, affectors, etc. so it is
    ///< better to calculate it once at the Particle level.
    float timeFraction;

    /**  Mass of a particle.
    @remarks
        In case of simulations where mass of a particle is needed (i.e. exploding particles of different
        mass) this attribute can be used.
    */
    float mass;

    /** Animation attributes
    */
    float textureAnimationTimeStep;
    float textureAnimationTimeStepCount;
    unsigned short textureCoordsCurrent;
    bool textureAnimationDirectionUp;

    float depthInView;///< depth in camera view
    float zRotation; ///< zRotation is used to rotate the particle in 2D (around the Z-axis)   (radian)
    //float widthInWorld;
    //float heightInWorld;
    //float depthInWorld;
    
};

/** @class PUParticleSystem3D
*@brief @~english PUParticleSystem3D, the class of pu particle system, inherit from ParticleSystem3D.
 The ParticleSystem3D,the parent of PUParticleSystem3D, is derived from Node, so one particle system can contain multiple particle systems,
 You can mount a PUParticleSystem3D under another by addChild.
 Each particle system can be defined emitter,affector,renderer,etc. 
 There are three ways to create a PUParticleSystem3D:
 - Directly create an empty PUParticleSystem3D, manually add emitter, affector, etc.(useless)
 - Create PUParticleSystem3D with pu file path, pu material file will be automatically searched.(not recommended)
 - Create PUParticleSystem3D with pu file path and pu material file path.(recommended)
 The resources(textures,scripts,materials) used by pu particle system must use the following file structure and name definition(Can not be modified):
 - Folder - textures
 - --------- scripts
 - --------- materials

 @~chinese PUParticleSystem3D继承自ParticleSystem3D，是pu的粒子系统类。
 PUParticleSystem3D的父类ParticleSystem3D是从Node派生而来，所以一个粒子系统可以包含多个粒子系统，
 通过addChild的方式把一个PUParticleSystem3D挂载到另一个PUParticleSystem3D下。
 每个粒子系统都可定义发射器，影响器，渲染器等等。
 PUParticleSystem3D提供了三种创建的方式：
 - 直接创建一个空的PUParticleSystem3D，手动添加发射器，影响器等(基本不使用)
 - 通过一个pu文件路径来创建PUParticleSystem3D，pu材质文件会自动搜索。（不建议使用）
 - 通过一个pu文件路径和一个pu材质文件路径来创建PUParticleSystem3D。（建议使用）
 pu的粒子系统使用的资源(纹理、pu脚本、材质文件)需采用如下文件结构和名称（目前不可更改）：
 - Folder - textures
 - --------- scripts
 - --------- materials
*/
class CC_DLL PUParticleSystem3D : public ParticleSystem3D
{
public:

    typedef std::map<std::string, ParticlePool> ParticlePoolMap;

    /**
    @property DEFAULT_WIDTH
    @static
    @~english Default width of particle
    @~chinese 粒子默认的宽度
    */
    static const float DEFAULT_WIDTH;

    /**
    @property DEFAULT_HEIGHT
    @static
    @~english Default height of particle
    @~chinese 粒子默认的高度
    */
    static const float DEFAULT_HEIGHT;

    /**
    @property DEFAULT_DEPTH
    @static
    @~english Default depth of particle
    @~chinese 粒子默认的深度
    */
    static const float DEFAULT_DEPTH;

    /** 
    @property DEFAULT_PARTICLE_QUOTA
    @static
    @~english Default quota of particle
    @~chinese 粒子默认的数量上限
    */
    static const unsigned int DEFAULT_PARTICLE_QUOTA;

    /**
    @property DEFAULT_EMITTED_EMITTER_QUOTA
    @static
    @~english Default quota of emitted emitter
    @~chinese 被发射的发射器默认的数量上限
    */
    static const unsigned int DEFAULT_EMITTED_EMITTER_QUOTA;

    /**
    @property DEFAULT_EMITTED_SYSTEM_QUOTA
    @static
    @~english Default quota of emitted system
    @~chinese 被发射的粒子系统默认的数量上限
    */
    static const unsigned int DEFAULT_EMITTED_SYSTEM_QUOTA;

    /**
    @property DEFAULT_MAX_VELOCITY
    @static
    @~english Default maximum velocity of particle
    @~chinese 粒子默认的最大速度
    */
    static const float DEFAULT_MAX_VELOCITY;

    /**
    * @~english Create a empty particle system.
    * @~chinese 创建一个空的粒子系统。
    */
    static PUParticleSystem3D* create();

    /**
    * @~english Create a particle system with pu file.
    * @~chinese 通过pu文件创建一个粒子系统。
    * @param filePath @~english The file path of pu. @~chinese pu文件路径。
    */
    static PUParticleSystem3D* create(const std::string &filePath);

    /**
    * @~english Create a particle system with pu file and pu material file.
    * @~chinese 通过pu文件和材质文件创建一个粒子系统。
    * @param filePath @~english  The file path of pu. @~chinese pu文件路径。
    * @param materialPath @~english The file path of pu material. @~chinese pu材质文件路径。
    */
    static PUParticleSystem3D* create(const std::string &filePath, const std::string &materialPath);
    
    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see node draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see node update(float delta);
    */
    virtual void update(float delta) override;

    /**
    * @~english Force update system.
    * @~chinese 强制更新粒子系统。
    * @param delta @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    void forceUpdate(float delta);
    
    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see ParticleSystem3D startParticleSystem();
    */
    virtual void startParticleSystem() override;
    
    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see ParticleSystem3D stopParticleSystem();
    */
    virtual void stopParticleSystem() override;
    
    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see ParticleSystem3D pauseParticleSystem();
    */
    virtual void pauseParticleSystem() override;
    
    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see ParticleSystem3D resumeParticleSystem();
    */
    virtual void resumeParticleSystem() override;

    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see ParticleSystem3D getAliveParticleCount();
    */
    virtual int getAliveParticleCount() const override;

    /**
    * @~english Get the velocity scale, used for scale all particles velocity.
    * @~chinese 获取缩放速率，常用于缩放所有的粒子。
    * @return @~english The velocity scale. @~chinese 缩放速率。
    */
    float getParticleSystemScaleVelocity() const;

    /**
    * @~english Set the velocity scale, used for scale all particles velocity.
    * @~chinese 设置缩放速率，常用于缩放所有的粒子。
    * @param scaleVelocity @~english The velocity scale. @~chinese 缩放速率。
    */
    void setParticleSystemScaleVelocity(float scaleVelocity) { _particleSystemScaleVelocity = scaleVelocity; }

    /**
    * @~english Set the rotation offset(internal method).
    * If the orientation of the particle system has been changed since the last update, the passed vector is rotated accordingly.
    * @~chinese 设置旋转偏移量(内部方法)。
    * 如果粒子系统的朝向自从上次更新后改变了，传递的向量也需要相应旋转。
    * @param pos @~english The position. @~chinese 位置。
    */
    void rotationOffset(Vec3& pos);

    /**
    * @~english Get the time elapsed since sysytem started.
    * @~chinese 获取自从粒子系统开始运行后流逝的时间。
    * @return @~english The time. @~chinese 流逝的时间。
    */
    inline float getTimeElapsedSinceStart(void) const {return _timeElapsedSinceStart;};

    /**
    * @~english Get the default width of particle.
    * @~chinese 获取粒子默认的宽度。
    * @return @~english The width of particle. @~chinese 粒子的宽度。
    */
    const float getDefaultWidth(void) const;

    /**
    * @~english Set the default width of particle.
    * @~chinese 设置粒子默认的宽度。
    * @param width @~english The width of particle. @~chinese 粒子的宽度。
    */
    void setDefaultWidth(const float width);

    /**
    * @~english Get the default height of particle.
    * @~chinese 获取粒子默认的高度。
    * @return @~english The height of particle. @~chinese 粒子的高度。
    */
    const float getDefaultHeight(void) const;

    /**
    * @~english Set the default height of particle.
    * @~chinese 设置粒子默认的高度。
    * @param height @~english The height of particle. @~chinese 粒子的高度。
    */
    void setDefaultHeight(const float height);

    /**
    * @~english Get the default depth of particle.
    * @~chinese 获取粒子默认的深度。
    * @return @~english The depth of particle. @~chinese 粒子的深度。
    */
    const float getDefaultDepth(void) const;

    /**
    * @~english Set the default depth of particle.
    * @~chinese 设置粒子默认的深度。
    * @param depth @~english The depth of particle. @~chinese 粒子的深度。
    */
    void setDefaultDepth(const float depth);

    /**
    * @~english Get the world position of system.
    * @~chinese 获取粒子系统世界坐标系下的位置。
    * @return @~english The world position. @~chinese 世界坐标系位置。
    */
    Vec3 getDerivedPosition();

    /**
    * @~english Get the world rotation of system.
    * @~chinese 获取粒子系统世界坐标系下的旋转。
    * @return @~english The world rotation. @~chinese 世界坐标系旋转。
    */
    Quaternion getDerivedOrientation();

    /**
    * @~english Get the world scale of system.
    * @~chinese 获取粒子系统世界坐标系下的缩放。
    * @return @~english The world scale. @~chinese 世界坐标系缩放。
    */
    Vec3 getDerivedScale();

    /**
    * @~english Get the maximum velocity of particle.
    * Return the maximum velocity a particle can have, even if the velocity of the particle has been set higher (either by initialisation of the particle or by means of an affector).
    * @~chinese 获取粒子最大速率。
    * 返回的是粒子的最大速率，就算速率被设为更高的值，也会被截取到范围以内。
    * @return @~english The maximum velocity. @~chinese 粒子最大速率。
    */
    float getMaxVelocity() const;

    /**
    * @~english Set the maximum velocity of particle.
    * @~chinese 设置粒子的最大速率。
    * @param maxVelocity @~english The maximum velocity. @~chinese 粒子最大速率。
    */
    void setMaxVelocity(float maxVelocity);

    /**
    * @~english Set the using material of this system(internal method).
    * @~chinese 设置粒子系统使用的材质名称(内部方法)。
    * @param name @~english The name of material. @~chinese 材质名称。
    */
    void setMaterialName(const std::string &name) { _matName = name; };

    /**
    * @~english Get the using material of this system(internal method).
    * @~chinese 获取粒子系统使用的材质名称(内部方法)。
    * @return @~english The name of material. @~chinese 材质名称。
    */
    const std::string getMaterialName() const { return _matName; };

    /**
    * @~english Forces emission of particles.
    * The number of requested particles are the exact number that are emitted
    * @~chinese 强制发射指定数目的粒子。
    * requested指定的值是发射数目的确切值。
    * @param emitter @~english Which emitter need emit particle. @~chinese 需要发射粒子的发射器。
    * @param requested @~english The number of requested particles. @~chinese 请求发射粒子的数量。
    */
    void forceEmission(PUEmitter* emitter, unsigned requested);

    /**
    * @~english Add a Emitter.
    * The pu particle system allows the use of multiple emitters
    * @~chinese 添加一个发射器。
    * pu粒子系统允许使用多个发射器。
    * @param emitter @~english The pointer of emitter. @~chinese 发射器指针。
    */
    void addEmitter(PUEmitter* emitter);

    /**
    * @~english Get the affector by name.
    * @~chinese 根据名称获取影响器。
    * @return @~english The name of affector. @~chinese 影响器名称。
    */
    PUAffector* getAffector(const std::string &name);

    /**
    * @~english Get the emitter by name.
    * @~chinese 根据名称获取发射器。
    * @return @~english The name of emitter. @~chinese 发射器名称。
    */
    PUEmitter* getEmitter(const std::string &name);

    /**
    * @~english Remove all emitters.
    * @~chinese 移除所有的发射器。
    */
    void removeAllEmitter();

    /**
    * @~english Add a Listener(internal method).
    * Listener is mainly used to monitor particle emission and death.
    * @~chinese 添加一个监听器。
    * 监听器主要用来监听粒子发射和消亡。
    * @see PUListener
    * @param listener @~english The pointer of listener. @~chinese 监听器指针。
    */
    void addListener(PUListener *listener);

    /**
    * @~english Remove a Listener(internal method).
    * @~chinese 移除一个监听器。
    * @param listener @~english The pointer of listener. @~chinese 监听器指针。
    */
    void removeListener(PUListener *listener);

    /**
    * @~english Add a Emitter.
    * The pu particle system allows the use of multiple emitters
    * @~chinese 添加一个发射器。
    * pu粒子系统允许使用多个发射器。
    */
    void removeAllListener();

    /**
    * @~english Add a Observer.
    * @~chinese 添加一个观察器。
    * @see PUObserver
    * @param observer @~english The pointer of observer. @~chinese 观察器指针。
    */
    void addObserver(PUObserver *observer);

    /**
    * @~english Get a Observer.
    * @~chinese 获取一个观察器。
    * @see PUObserver
    * @return @~english The name of observer. @~chinese 观察器名称。
    */
    PUObserver* getObserver(const std::string &name);

    /**
    * @~english Remove all Observers.
    * @~chinese 移除所有观察器。
    */
    void removerAllObserver();

    /**
    * @~english Add a behaviour template of particle(internal method).
    * @~chinese 添加一个粒子的行为模板。
    * @see PUBehaviour
    * @param behaviour @~english The pointer of behaviour. @~chinese 行为模板指针。
    */
    void addBehaviourTemplate(PUBehaviour *behaviour);

    /**
    * @~english Remove all behaviour templates.
    * @~chinese 移除所有行为模板。
    */
    void removeAllBehaviourTemplate();

    /**
    * @~english Check this system is mark for emission.
    * @~chinese 检查当前粒子系统是否标记为被发射器发射。
    * @return @~english Whether this system is mark for emission. @~chinese 当前粒子系统是否标记为发射。
    */
    bool isMarkedForEmission() const {return _isMarkedForEmission;};

    /**
    * @~english Mark this system for emission.
    * @~chinese 标记当前粒子系统被发射器发射。
    * @param isMarked @~english Whether this system is mark for emission. @~chinese 当前粒子系统是否标记为发射。
    */
    void setMarkedForEmission(bool isMarked) {_isMarkedForEmission = isMarked;};

    /**
    * @~english Clear all particles.
    * @~chinese 清除所有粒子。
    */
    void clearAllParticles();

    /**
    * @~english Get the quota of emitted emitters .
    * @~chinese 获取被发射的发射器上限值。
    * @return @~english The quota of emitted emitters. @~chinese 被发射的发射器上限值。
    */
    unsigned int getEmittedEmitterQuota() const { return _emittedEmitterQuota; };

    /**
    * @~english Set the quota of emitted emitters .
    * @~chinese 设置被发射的发射器上限值。
    * @param quota @~english The quota of emitted emitters. @~chinese 被发射的发射器上限值。
    */
    void setEmittedEmitterQuota(unsigned int quota) { _emittedEmitterQuota = quota; };

    /**
    * @~english Get the quota of emitted systems .
    * @~chinese 获取被发射的粒子系统上限值。
    * @return @~english The quota of emitted systems. @~chinese 被发射的粒子系统上限值。
    */
    unsigned int getEmittedSystemQuota() const { return _emittedSystemQuota; };

    /**
    * @~english Set the quota of emitted systems .
    * @~chinese 设置被发射的粒子系统上限值。
    * @param quota @~english The quota of emitted systems. @~chinese 被发射的粒子系统上限值。
    */
    void setEmittedSystemQuota(unsigned int quota) { _emittedSystemQuota = quota; };

    /**
    * @~english Get the partent system of this system.
    * @~chinese 获取当前粒子系统的父系统。
    * @return @~english The partent system of this system. @~chinese 粒子系统的父系统。
    */
    PUParticleSystem3D* getParentParticleSystem()const { return _parentParticleSystem; };

    /**
    * @~english Get the emitted emitter pool.
    * @~chinese 获取被发射的发射器数据池。
    * @return @~english The emitted emitter pool. @~chinese 发射器数据池。
    */
    const ParticlePoolMap& getEmittedEmitterParticlePool() const { return _emittedEmitterParticlePool; };

    /**
    * @~english Get the emitted system pool.
    * @~chinese 获取被发射的粒子系统数据池。
    * @return @~english The emitted system pool. @~chinese 粒子系统数据池。
    */
    const ParticlePoolMap& getEmittedSystemParticlePool() const { return _emittedSystemParticlePool; };

    /**
    * @~english Calculate the real position of the particle(internal method).
    * @~chinese 计算粒子的真实位置(内部方法)。
    * @param particle @~english Need handled particle. @~chinese 需要被处理的粒子。
    */
    bool makeParticleLocal(PUParticle3D* particle);

    /**
    * @~english Calculate rotation offset(internal method).
    * @~chinese 计算旋转偏移量(内部方法)。
    */
    void calulateRotationOffset(void);

    /**
    * @~english Clone this system.
    * @~chinese 克隆当前粒子系统。
    */
    virtual PUParticleSystem3D* clone();

    /**
    * @~english Copy attributes to another particle system(internal method).
    * @~chinese 拷贝属性到另外一个粒子系统(内部方法)。
    * @param system @~english The particle system. @~chinese 粒子系统。
    */
    virtual void copyAttributesTo(PUParticleSystem3D* system);

CC_CONSTRUCTOR_ACCESS:
    PUParticleSystem3D();
    virtual ~PUParticleSystem3D();

    bool initWithFilePath(const std::string &filePath);
    bool initWithFilePathAndMaterialPath (const std::string &filePath, const std::string &materialPath);

protected:

    void prepared();
    void unPrepared();
    void preUpdator(float elapsedTime);
    void updator(float elapsedTime);
    void postUpdator(float elapsedTime);
    void emitParticles(float elapsedTime);
    void executeEmitParticles(PUEmitter* emitter, unsigned requested, float elapsedTime);
    void emitParticles(ParticlePool &pool, PUEmitter* emitter, unsigned requested, float elapsedTime);
    void processParticle(ParticlePool &pool, bool &firstActiveParticle, bool &firstParticle, float elapsedTime);
    void processMotion(PUParticle3D* particle, float timeElapsed, bool firstParticle);
    void notifyRescaled(const Vec3 &scl);
    void initParticleForEmission(PUParticle3D* particle);
    void initParticleForExpiration(PUParticle3D* particle, float timeElapsed);
    void forceStopParticleSystem();
    
    inline bool isExpired(PUParticle3D* particle, float timeElapsed);

    bool initSystem(const std::string &filePath);
    static void convertToUnixStylePath(std::string &path);

protected:

    std::vector<PUEmitter*>      _emitters;///< The emitter list
    std::vector<PUObserver *>    _observers;///< The observer list

    ParticlePoolMap              _emittedEmitterParticlePool;///< The emitted emitter pool
    ParticlePoolMap              _emittedSystemParticlePool;///< The emitted system pool

    unsigned int                 _emittedEmitterQuota;///< The quota of emitted emitter
    unsigned int                 _emittedSystemQuota;///< The quota of emitted system

    //internal
    PUParticle3D::ParticleBehaviourList _behaviourTemplates;///< Used by particle
    std::vector<PUListener *>           _listeners;///< Used by system

    bool                                _prepared;
    bool                                _poolPrepared;///<Used by pools

    float                               _particleSystemScaleVelocity;///< scale velocity of particles
    float                               _timeElapsedSinceStart;

    Quaternion                          _rotationOffset; ///< Rotation offset between 2 updates.

    Vec3                                _rotationCentre; ///< The rotation centre.

    float                               _defaultWidth; ///< Default width of each visual particle.

    float                               _defaultHeight; ///< Default height of each visual particle.

    float                               _defaultDepth; ///< Default depth of each visual particle.
    
    float                               _maxVelocity; ///< Attributes that limit the velocity of the particles in this technique.
    bool                                _maxVelocitySet;

    std::string                         _matName;///< material name

    bool                                _isMarkedForEmission;///< True means this system emitted by one emitter

    Vec3                                _latestPositionDiff;
    Vec3                                _latestPosition;///<  Keep latest position

    Quaternion                          _latestOrientation;

    PUParticleSystem3D *                _parentParticleSystem;
};

// end of _3d group
/// @}

NS_CC_END

#endif
