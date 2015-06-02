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

#ifndef __CC_PU_PARTICLE_3D_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_AFFECTOR_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticle3DAffector.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUParticleSystem3D;

/**
* @addtogroup _3d
* @{
*/

/** @class PUAffector
*@brief @~english PUAffector inherit from Particle3DAffector, the base class of pu affector.
 affectors modify particles in a particle system over their lifetime. This class defines
 the interface, and provides a few implementations of some basic functions.

 @~chinese PUAffector继承自Particle3DAffector，是pu影响器的基类。
 影响器是在粒子的生命周期内改变粒子行为的一个工具，当前类定义了接口，
 并且提供了一些已经实现基本函数供子类使用。
*/
class CC_DLL PUAffector : public Particle3DAffector
{
    friend class PUParticleSystem3D;
public:
    /**
        The AffectSpecialisation enumeration is used to specialise the affector even more. This enumeration 
        isn't used by all affectors; in some cases it isn't even applicable.
    */
    enum AffectSpecialisation
    {
        AFSP_DEFAULT,
        AFSP_TTL_INCREASE,
        AFSP_TTL_DECREASE
    };
    
    /**
    * @~english Perform activities when a affector is started(internal method).
    * @~chinese 当影响器开始运行时执行(内部方法)
    */
    virtual void notifyStart();

    /**
    * @~english Perform activities when a affector is stopped(internal method).
    * @~chinese 当影响器停止运行时执行(内部方法)
    */
    virtual void notifyStop();

    /**
    * @~english Perform activities when a affector is paused(internal method).
    * @~chinese 当影响器暂停运行时执行(内部方法)
    */
    virtual void notifyPause();

    /**
    * @~english Perform activities when a affector is resumed(internal method).
    * @~chinese 当影响器恢复运行时执行(内部方法)
    */
    virtual void notifyResume();

    /**
    * @~english Notify that the affector is rescaled(internal method).
    * @~chinese 当影响器需要缩放时执行(内部方法)
    */
    virtual void notifyRescaled(const Vec3& scale);

    /**
    * @~english The function is automatically called during initialisation (prepare) activities of a ParticleSystem(internal method).
    * @~chinese 当一个粒子系统初始化时自动执行(内部方法)
    */
    virtual void prepare();

    /**
    * @~english The function is automatically called when a ParticleSystem is expired(internal method).
    * @~chinese 当一个粒子系统失效时自动执行(内部方法)
    */
    virtual void unPrepare();

    /**
    * @~english This function is called before the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese 在粒子系统更新循环粒子遍历前执行(内部方法)
    * @param deltaTime   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual void preUpdateAffector(float deltaTime);

    /**
    * @~english This function is called when the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese 在粒子系统更新循环粒子遍历时执行(内部方法)
    * @param particle   @~english The current traversed particle. @~chinese 当前遍历到的粒子。
    * @param delta   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual void updatePUAffector(PUParticle3D* particle, float delta);

    /**
    * @~english This function is called after the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese 在粒子系统更新循环粒子遍历后执行(内部方法)
    * @param deltaTime   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual void postUpdateAffector(float deltaTime);

    /**
    * @~english This function is called when the first particle in the update-loop is processed(internal method).
    * @~chinese 粒子遍历时第一个粒子执行(内部方法)
    * @param particle   @~english The current traversed particle. @~chinese 当前遍历到的粒子。
    * @param deltaTime   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual void firstParticleUpdate(PUParticle3D *particle, float deltaTime);

    /**
    * @~english Initialise a newly emitted particle(internal method).
    * @~chinese 初始化一个被发射的粒子(内部方法)
    * @param particle   @~english Particle pointer to a particle to initialise. @~chinese 需要初始化粒子的指针。
    */
    virtual void initParticleForEmission(PUParticle3D* particle);

    /**
    * @~english Process a particle(internal method).
    * @~chinese 处理一个粒子(内部方法)
    * @param particle   @~english The particle to be processed. @~chinese 要被处理的粒子。
    * @param delta   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    * @param firstParticle   @~english Is the first particle. @~chinese 是否是第一个粒子。
    */
    void process(PUParticle3D* particle, float delta, bool firstParticle);

    /**
    * @~english Set position of affector.
    * @~chinese 设置影响器的位置
    * @param pos   @~english The position in local coordinate system. @~chinese 局部坐标系下的位置。
    */
    void setLocalPosition(const Vec3 &pos) { _position = pos; };

    /**
    * @~english Get position of affector.
    * @~chinese 获取影响器的位置
    * @return   @~english The position in local coordinate system. @~chinese 局部坐标系下的位置。
    */
    const Vec3 getLocalPosition() const { return _position; };

    /**
    * @~english Set the mass of affector.
    * @~chinese 设置影响器的质量
    * @param mass      @~english The mass of affector. @~chinese 影响器的质量。
    */
    void setMass(float mass);

    /**
    * @~english Get the mass of affector.
    * @~chinese 获取影响器的质量
    * @return      @~english The mass of affector. @~chinese 影响器的质量。
    */
    float getMass() const;

    /**
    * @~english Calculate the world position of the affector.
    * @~chinese 计算影响器的世界位置
    * @return      @~english The position in world coordinate system. @~chinese 影响器在世界坐标系下的位置。
    */
    const Vec3& getDerivedPosition();

    /**
    * @~english Get the AffectSpecialisation enumeration，isn't used by all affectors.
    * @~chinese 获取AffectSpecialisation的枚举值，非所有影响器都使用。
    * @return      @~english The enumeration. @~chinese 枚举量。
    */
    const AffectSpecialisation& getAffectSpecialisation(void) const {return _affectSpecialisation;};

    /**
    * @~english Set the AffectSpecialisation enumeration.
    * @~chinese 设置AffectSpecialisation的枚举值。
    * @param affectSpecialisation      @~english The enumeration. @~chinese 枚举量。
    */
    void setAffectSpecialisation(const AffectSpecialisation& affectSpecialisation) {_affectSpecialisation = affectSpecialisation;};

    /**
    * @~english Get the type of affector.
    * @~chinese 获取影响器类型。
    * @return      @~english The type. @~chinese 类型。
    */
    const std::string& getAffectorType(void) const {return _affectorType;};

    /**
    * @~english Set the type of affector.
    * @~chinese 设置影响器类型。
    * @param affectorType      @~english The type. @~chinese 类型。
    */
    void setAffectorType(const std::string& affectorType) {_affectorType = affectorType;};

    /**
    * @~english Add a emitter name that excludes Particles emitted by this emitter from being affected。
    * @~chinese 添加一个发射器名称，影响器不会影响该发射器发射的粒子。
    * @param emitterName      @~english The name of emitter. @~chinese 发射器名称。
    */
    void addEmitterToExclude(const std::string& emitterName);

    /**
    * @~english Remove a emitter name that excludes particles emitted by this emitter.
    * @~chinese 移除一个发射器名称，影响器就能影响该发射器发射的粒子。
    * @param emitterName      @~english The name of emitter. @~chinese 发射器名称。
    */
    void removeEmitterToExclude(const std::string& emitterName);

    /**
    * @~english Get the name of affector
    * @~chinese 获取影响器的名称。
    * @return      @~english The name of affector. @~chinese 影响器名称。
    */
    const std::string& getName(void) const {return _name;};

    /**
    * @~english Set the name of affector
    * @~chinese 设置影响器的名称。
    * @param name      @~english The name of affector. @~chinese 影响器名称。
    */
    void setName(const std::string& name) {_name = name;};

    /**
    * @~english Copy one affector's attributes to another's(internal method).
    * @~chinese 拷贝一个影响器的属性到另外一个(内部方法)。
    * @param affector @~english The affector need be copied. @~chinese 拷贝属性的影响器。
    */
    virtual void copyAttributesTo (PUAffector* affector);

CC_CONSTRUCTOR_ACCESS:
    PUAffector();
    virtual ~PUAffector();

protected:

    float calculateAffectSpecialisationFactor (const PUParticle3D* particle);
    
protected:

    Vec3 _position; ///< Although the scale is on a Particle System level, the affector can also be scaled.

    Vec3 _affectorScale; ///< affector scale
    Vec3 _derivedPosition; ///< Because the public attribute position is sometimes used for both localspace and worldspace position, the _derivedPosition attribute is introduced.

    AffectSpecialisation _affectSpecialisation;///< The _affectSpecialisation is used to specialise the affector.

    std::string _affectorType;///< Type of the affector

    std::vector<std::string> _excludedEmitters; //< Excluded emitter list

    std::string _name;///< Name of the affector (optional)

    float _mass;///< The mass of affector
};

// end of _3d group
/// @}

NS_CC_END

#endif
