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

#ifndef __CC_PU_PARTICLE_3D_EMITTER_H__
#define __CC_PU_PARTICLE_3D_EMITTER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticle3DEmitter.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include <vector>
#include <string>

NS_CC_BEGIN
struct PUParticle3D;
class PUParticleSystem3D;

/**
* @addtogroup _3d
* @{
*/

/** @class PUEmitter
*@brief @~english PUEmitter，the base class of pu emitter，inherit from Particle3DEmitter.
 Different emitters can have their own implementation.

 @~chinese PUEmitter继承自Particle3DEmitter，是pu发射器的基类。
 具体的实现由不同的发射器类型定义。。
*/
class CC_DLL PUEmitter : public Particle3DEmitter
{
    friend class PUParticleSystem3D;
public:

    /**
    @property DEFAULT_ENABLED
    @static
    @~english Default enabled
    @~chinese 默认的启用状态
    */
    static const bool DEFAULT_ENABLED;

    /**
    @property DEFAULT_POSITION
    @static
    @~english Default position
    @~chinese 默认位置
    */
    static const Vec3 DEFAULT_POSITION;

    /**
    @property DEFAULT_KEEP_LOCAL
    @static
    @~english Default whether use local coordinate system
    @~chinese 默认是否使用局部坐标系
    */
    static const bool DEFAULT_KEEP_LOCAL;

    /**
    @property DEFAULT_DIRECTION
    @static
    @~english Default emitted direction
    @~chinese 默认发射方向
    */
    static const Vec3 DEFAULT_DIRECTION;

    /**
    @property DEFAULT_ORIENTATION
    @static
    @~english Default emitted orientation
    @~chinese 默认发射朝向
    */
    static const Quaternion DEFAULT_ORIENTATION;

    /**
    @property DEFAULT_ORIENTATION_RANGE_START
    @static
    @~english Default emitted starting orientation
    @~chinese 默认发射朝向范围起始值
    */
    static const Quaternion DEFAULT_ORIENTATION_RANGE_START;

    /**
    @property DEFAULT_ORIENTATION_RANGE_END
    @static
    @~english Default emitted ending orientation
    @~chinese 默认发射朝向范围结束值
    */
    static const Quaternion DEFAULT_ORIENTATION_RANGE_END;

    /**
    @property DEFAULT_START_TEXTURE_COORDS
    @static
    @~english Default texture starting coords
    @~chinese 默认纹理起始坐标
    */
    static const unsigned short DEFAULT_START_TEXTURE_COORDS;

    /**
    @property DEFAULT_END_TEXTURE_COORDS
    @static
    @~english Default texture ending coords
    @~chinese 默认纹理结束坐标
    */
    static const unsigned short DEFAULT_END_TEXTURE_COORDS;

    /**
    @property DEFAULT_TEXTURE_COORDS
    @static
    @~english Default texture coords
    @~chinese 默认纹理坐标
    */
    static const unsigned short DEFAULT_TEXTURE_COORDS;

    /**
    @property DEFAULT_START_COLOUR_RANGE
    @static
    @~english Default color starting range
    @~chinese 默认颜色范围起始值
    */
    static const Vec4 DEFAULT_START_COLOUR_RANGE;

    /**
    @property DEFAULT_END_COLOUR_RANGE
    @static
    @~english Default color ending range
    @~chinese 默认颜色范围结束值
    */
    static const Vec4 DEFAULT_END_COLOUR_RANGE;

    /**
    @property DEFAULT_COLOUR
    @static
    @~english Default color
    @~chinese 默认颜色值
    */
    static const Vec4 DEFAULT_COLOUR;

    /**
    @property DEFAULT_AUTO_DIRECTION
    @static
    @~english Default whether use auto direction
    @~chinese 默认是否使用自动朝向
    */
    static const bool DEFAULT_AUTO_DIRECTION;

    /**
    @property DEFAULT_FORCE_EMISSION
    @static
    @~english Default whether force emission
    @~chinese 默认是否强制发射
    */
    static const bool DEFAULT_FORCE_EMISSION;

    /**
    @property DEFAULT_EMISSION_RATE
    @static
    @~english Default emission rate
    @~chinese 默认发射率
    */
    static const float DEFAULT_EMISSION_RATE;

    /**
    @property DEFAULT_TIME_TO_LIVE
    @static
    @~english Default particle time to live
    @~chinese 默认粒子生存时间
    */
    static const float DEFAULT_TIME_TO_LIVE;

    /**
    @property DEFAULT_MASS
    @static
    @~english Default particle mass
    @~chinese 默认粒子质量
    */
    static const float DEFAULT_MASS;

    /**
    @property DEFAULT_VELOCITY
    @static
    @~english Default particle velocity
    @~chinese 默认粒子速率
    */
    static const float DEFAULT_VELOCITY;

    /**
    @property DEFAULT_DURATION
    @static
    @~english Default emitted duration
    @~chinese 默认发射持续时间
    */
    static const float DEFAULT_DURATION;

    /**
    @property DEFAULT_REPEAT_DELAY
    @static
    @~english Default emitted repeat delay
    @~chinese 默认重复发射间隔
    */
    static const float DEFAULT_REPEAT_DELAY;

    /**
    @property DEFAULT_ANGLE
    @static
    @~english Default emitted angle
    @~chinese 默认发射角度
    */
    static const float DEFAULT_ANGLE;

    /**
    @property DEFAULT_DIMENSIONS
    @static
    @~english Default emitted particle dimensions
    @~chinese 默认发射粒子尺寸
    */
    static const float DEFAULT_DIMENSIONS;

    /**
    @property DEFAULT_WIDTH
    @static
    @~english Default emitted particle width
    @~chinese 默认发射粒子宽度
    */
    static const float DEFAULT_WIDTH;

    /**
    @property DEFAULT_HEIGHT
    @static
    @~english Default emitted particle height
    @~chinese 默认发射粒子高度
    */
    static const float DEFAULT_HEIGHT;

    /**
    @property DEFAULT_DEPTH
    @static
    @~english Default emitted particle depth
    @~chinese 默认发射粒子深度
    */
    static const float DEFAULT_DEPTH;

    PUEmitter();
    virtual ~PUEmitter();
    
    /**
    * @~english Perform activities when a emitter is started(internal method).
    * @~chinese 当发射器开始运行时执行(内部方法)。
    */
    virtual void notifyStart();

    /**
    * @~english Perform activities when a emitter is stopped(internal method).
    * @~chinese 当发射器停止运行时执行(内部方法)。
    */
    virtual void notifyStop();

    /**
    * @~english Perform activities when a emitter is paused(internal method).
    * @~chinese 当发射器暂停运行时执行(内部方法)。
    */
    virtual void notifyPause();

    /**
    * @~english Perform activities when a emitter is paused(internal method).
    * @~chinese 当发射器恢复运行时执行(内部方法)。
    */
    virtual void notifyResume();

    /**
    * @~english Notify that the emitter is rescaled(internal method).
    * @~chinese 当发射器需要缩放时执行(内部方法)。
    */
    virtual void notifyRescaled(const Vec3& scale);

    /**
    * @~english The function is automatically called during initialisation (prepare) activities of a ParticleSystem(internal method).
    * @~chinese 当一个粒子系统初始化时自动执行(内部方法)。
    */
    virtual void prepare();

    /**
    * @~english The function is automatically called when a ParticleSystem is expired(internal method).
    * @~chinese 当一个粒子系统失效时自动执行(内部方法)。
    */
    virtual void unPrepare();

    /**
    * @~english This function is called before the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese 在粒子系统更新循环粒子遍历前执行(内部方法)。
    * @param deltaTime   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual void preUpdateEmitter(float deltaTime);

    /**
    * @~english This function is called when the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese 在粒子系统更新循环粒子遍历时执行(内部方法)。
    * @param particle   @~english The current traversed particle. @~chinese 当前遍历到的粒子。
    * @param deltaTime   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual void updateEmitter(Particle3D *particle, float deltaTime) override;

    /**
    * @~english This function is called after the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese 在粒子系统更新循环粒子遍历后执行(内部方法)。
    * @param deltaTime   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual void postUpdateEmitter(float deltaTime);

    /**
    * @~english Calculate the number of particles that the emitter wants to emit.
    * @~chinese 计算想要发射粒子的数量。
    * @param timeElapsed   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual unsigned short calculateRequestedParticles(float timeElapsed);
    
    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see Particle3DEmitter emit(int count);
    */
    virtual void emit(int count) override;

    /**
    * @~english Set position of emitter.
    * @~chinese 设置发射器的位置。
    * @param pos   @~english The position in local coordinate system. @~chinese 局部坐标系下的位置。
    */
    void setLocalPosition(const Vec3 &pos) { _position = pos; };

    /**
    * @~english Get position of emitter.
    * @~chinese 获取发射器的位置。
    * @return   @~english The position in local coordinate system. @~chinese 局部坐标系下的位置。
    */
    const Vec3 getLocalPosition() const { return _position; };

    /**
    * @~english Calculate the world position of the emitter.
    * @~chinese 计算发射器的世界位置。
    * @return      @~english The position in world coordinate system. @~chinese 发射器在世界坐标系下的位置。
    */
    const Vec3& getDerivedPosition();
    
    /**
    * @~english Set the emitter enable or disable.
    * @~chinese 设置发射器可用或不可用。
    * @param enabled @~english Whether the emitter enabled. @~chinese 发射器是否可用。
    */
    void setEnabled (bool enabled);

    /**
    * @~english Get the emitter enabled.
    * @~chinese 获取发射器是否可用。
    * @return @~english Whether the emitter enabled. @~chinese 发射器是否可用。
    */
    bool isEnabled(void) const;

    /**
    * @~english Is the emitter emission done.
    * @~chinese 发射器是否发射完成。
    * @return @~english Whether the emission done. @~chinese 发射是否完成。
    */
    bool isEmitterDone() const;

    /**
    * @~english Get the emitter type.
    * @~chinese 获取发射器类型。
    * @return @~english The type. @~chinese 类型。
    */
    inline const std::string& getEmitterType(void) const {return _emitterType;};

    /**
    * @~english Set the emitter type.
    * @~chinese 设置发射器类型。
    * @param emitterType @~english The type. @~chinese 类型。
    */
    void setEmitterType(const std::string& emitterType) {_emitterType = emitterType;};

    /**
    * @~english Get the name of emitter.
    * @~chinese 获取发射器名称。
    * @return @~english The name. @~chinese 名称。
    */
    inline const std::string& getName(void) const {return _name;};

    /**
    * @~english Set the name of emitter.
    * @~chinese 设置发射器名称。
    * @param name @~english The name. @~chinese 名称。
    */
    void setName(const std::string& name) {_name = name;};

    /**
    * @~english Get the emission angle attribute.
    * @~chinese 获取发射角属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynAngle(void) const {return _dynAngle;};

    /**
    * @~english Set the emission angle attribute.
    * @~chinese 设置发射角属性。
    * @param dynAngle @~english The attribute. @~chinese 属性。
    */
    void setDynAngle(PUDynamicAttribute* dynAngle);

    /**
    * @~english Get the emission rate attribute.
    * @~chinese 获取发射率属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynEmissionRate(void) const {return _dynEmissionRate;};

    /**
    * @~english Set the emission rate attribute.
    * @~chinese 设置发射率属性。
    * @param dynEmissionRate @~english The attribute. @~chinese 属性。
    */
    void setDynEmissionRate(PUDynamicAttribute* dynEmissionRate);

    /**
    * @~english Get the time to live attribute.
    * @~chinese 获取存活时间属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynTotalTimeToLive(void) const {return _dynTotalTimeToLive;};

    /**
    * @~english Set the time to live attribute.
    * @~chinese 设置存活时间属性。
    * @param dynTotalTimeToLive @~english The attribute. @~chinese 属性。
    */
    void setDynTotalTimeToLive(PUDynamicAttribute* dynTotalTimeToLive);

    /**
    * @~english Get the mass of emission particle.
    * @~chinese 获取发射粒子的质量。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynParticleMass(void) const {return _dynParticleMass;};

    /**
    * @~english Set the mass of emission particle.
    * @~chinese 设置发射粒子的质量。
    * @param dynParticleMass @~english The attribute. @~chinese 属性。
    */
    void setDynParticleMass(PUDynamicAttribute* dynParticleMass);

    /**
    * @~english Get the emission velocity.
    * @~chinese 获取发射速率。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynVelocity(void) const {return _dynVelocity;};

    /**
    * @~english Set the emission velocity.
    * @~chinese 设置发射速率。
    * @param dynVelocity @~english The attribute. @~chinese 属性。
    */
    void setDynVelocity(PUDynamicAttribute* dynVelocity);

    /**
    * @~english Get the emission duration.
    * @~chinese 获取发射持续时间。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynDuration(void) const {return _dynDuration;};

    /**
    * @~english Set the emission duration.
    * @~chinese 设置发射持续时间。
    * @param dynDuration @~english The attribute. @~chinese 属性。
    */
    void setDynDuration(PUDynamicAttribute* dynDuration);

    /**
    * @~english Whether use duration(unused means infinite time).
    * @~chinese 是否设置持续时间(不设置意味无限时间)。
    * @param durationSet @~english Whether use. @~chinese 是否使用。
    */
    void setDynDurationSet(bool durationSet);

    /**
    * @~english Get the delay of repeat emission.
    * @~chinese 获取重复发射的间隔时间。
    * @return @~english The delay. @~chinese 间隔时间。
    */
    inline PUDynamicAttribute* getDynRepeatDelay(void) const {return _dynRepeatDelay;};

    /**
    * @~english Set the delay of repeat emission.
    * @~chinese 设置重复发射的间隔时间。
    * @param dynRepeatDelay @~english The delay. @~chinese 间隔时间。
    */
    void setDynRepeatDelay(PUDynamicAttribute* dynRepeatDelay);

    /**
    * @~english Whether use delay of repeat emission(unused means emit once).
    * @~chinese 是否设置重复间隔（不设置意味发射一次）。
    * @param repeatDelaySet @~english Whether use. @~chinese 是否使用。
    */
    void setDynRepeatDelaySet(bool repeatDelaySet);

    /**
    * @~english Get the all dimensions attribute of particle.
    * @~chinese 获取粒子所有维度属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynParticleAllDimensions(void) const {return _dynParticleAllDimensions;};

    /**
    * @~english Set the all dimensions attribute of particle.
    * @~chinese 设置粒子所有维度属性。
    * @param dynParticleAllDimensions @~english The attribute. @~chinese 属性。
    */
    void setDynParticleAllDimensions(PUDynamicAttribute* dynParticleAllDimensions);

    /**
    * @~english Whether use all dimensions setting.
    * @~chinese 是否使用所有维度的设置。
    * @param particleAllDimensionsSet @~english Whether use. @~chinese 是否使用。
    */
    void setDynParticleAllDimensionsSet(bool particleAllDimensionsSet);

    /**
    * @~english Get the attribute of particle width.
    * @~chinese 获取粒子宽度的属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynParticleWidth(void) const {return _dynParticleWidth;};

    /**
    * @~english Set the attribute of particle width.
    * @~chinese 设置粒子宽度的属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    void setDynParticleWidth(PUDynamicAttribute* dynParticleWidth);

    /**
    * @~english Whether use the attribute of particle width.
    * @~chinese 是否使用粒子宽度的属性。
    * @param particleWidthSet @~english Whether use. @~chinese 是否使用。
    */
    void setDynParticleWidthSet(bool particleWidthSet);

    /**
    * @~english Get the attribute of particle height.
    * @~chinese 获取粒子高度的属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynParticleHeight(void) const {return _dynParticleHeight;};

    /**
    * @~english Set the attribute of particle height.
    * @~chinese 设置粒子高度的属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    void setDynParticleHeight(PUDynamicAttribute* dynParticleHeight);

    /**
    * @~english Whether use the attribute of particle height.
    * @~chinese 是否使用粒子高度的属性。
    * @param particleHeightSet @~english Whether use. @~chinese 是否使用。
    */
    void setDynParticleHeightSet(bool particleHeightSet);

    /**
    * @~english Get the attribute of particle depth.
    * @~chinese 获取粒子深度的属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    inline PUDynamicAttribute* getDynParticleDepth(void) const {return _dynParticleDepth;};

    /**
    * @~english Set the attribute of particle depth.
    * @~chinese 设置粒子深度的属性。
    * @return @~english The attribute. @~chinese 属性。
    */
    void setDynParticleDepth(PUDynamicAttribute* dynParticleDepth);

    /**
    * @~english Whether use the attribute of particle depth.
    * @~chinese 是否使用粒子高度的属性。
    * @param particleDepthSet @~english Whether use. @~chinese 是否使用。
    */
    void setDynParticleDepthSet(bool particleDepthSet);

    ///** Todo
    //*/
    //inline ParticleType getEmitsType(void) const {return mEmitsType;};
    //void setEmitsType(ParticleType emitsType) {mEmitsType = emitsType;};

    /**
    * @~english Get the name of emits.
    * @~chinese 获取发射对象的名称。
    * @return @~english The name. @~chinese 名称。
    */
    inline const std::string& getEmitsName(void) const {return _emitsName;};

    /**
    * @~english Set the name of emits.
    * @~chinese 设置发射对象的名称。
    * @return @~english The name. @~chinese 名称。
    */
    void setEmitsName(const std::string& emitsName);

    /**
    * @~english Get the type of emits.
    * @~chinese 获取发射对象的类型。
    * @see ParticleType
    * @return @~english The type. @~chinese 类型。
    */
    inline PUParticle3D::ParticleType getEmitsType() const {return _emitsType;};

    /**
    * @~english Set the type of emits.
    * @~chinese 设置发射对象的类型。
    * @see ParticleType
    * @param type @~english The type. @~chinese 类型。
    */
    void setEmitsType(PUParticle3D::ParticleType type) {_emitsType = type;};

    /**
    * @~english Get the pointer of emits(PUEmitter, PUParticleSystem3D, etc).
    * @~chinese 获取发射对象的指针（PUEmitter, PUParticleSystem3D等）。
    * @return @~english The pointer of emits. @~chinese 发射对象指针。
    */
    Ref* getEmitsEntityPtr() const;

    /**
    * @~english Whether this emitter marked for emission.
    * @~chinese 当前发射器是否标记为被发射对象。
    * @return @~english The pointer of emits. @~chinese 发射对象指针。
    */
    bool isMarkedForEmission() const {return _isMarkedForEmission;};

    /**
    * @~english Set this emitter marked for emission.
    * @~chinese 标记当前发射器为被发射对象。
    * @param isMarked @~english Whether marked. @~chinese 是否标记。
    */
    void setMarkedForEmission(bool isMarked) {_isMarkedForEmission = isMarked;};

    /**
    * @~english Returns the base direction of the particle that is going to be emitted.
    * @~chinese 返回发射粒子的基准方向。
    * @return @~english The base direction of the particle. @~chinese 粒子方向。
    */
    const Vec3& getParticleDirection(void);

    /**
    * @~english Returns the originally set particle direction. This value is not affected by affectors, angle, etc.
    * @~chinese 返回粒子初始方向，该值不会被修改。
    * @return @~english The originally set particle direction. @~chinese 粒子初始方向。
    */
    const Vec3& getOriginalParticleDirection(void) const;

    /**
    * @~english Returns the base orientation of the particle that is going to be emitted.
    * @~chinese 返回发射粒子的基准朝向。
    * @return @~english The base orientation of the particle. @~chinese 粒子基准朝向。
    */
    const Quaternion& getParticleOrientation(void) const;

    /**
    * @~english Set the orientation of the particle.
    * @~chinese 设置粒子的朝向。
    * @param orientation @~english The orientation. @~chinese 朝向。
    */
    void setParticleOrientation(const Quaternion& orientation);

    /**
    * @~english Returns the start orientation of the particle that is going to be emitted
    * @~chinese 返回被发射粒子的起始朝向。
    * @return @~english The start orientation. @~chinese 起始朝向。
    */
    const Quaternion& getParticleOrientationRangeStart(void) const;

    /**
    * @~english Set start orientation of the particle that is going to be emitted.
    * @~chinese 设置被发射粒子的起始朝向。
    * @param orientationRangeStart @~english The start orientation. @~chinese 起始朝向。
    */
    void setParticleOrientationRangeStart(const Quaternion& orientationRangeStart);

    /**
    * @~english Returns the end orientation of the particle that is going to be emitted.
    * @~chinese 返回被发射粒子的终止朝向。
    * @return @~english The end orientation. @~chinese 终止朝向。
    */
    const Quaternion& getParticleOrientationRangeEnd(void) const;

    /**
    * @~english Set end orientation of the particle that is going to be emitted.
    * @~chinese 设置被发射粒子的终止朝向。
    * @param orientationRangeEnd @~english The end orientation. @~chinese 终止朝向。
    */
    void setParticleOrientationRangeEnd(const Quaternion& orientationRangeEnd);
            
    /**
    * @~english Sets the direction of the particle that the emitter is emitting.
    * @~chinese 设置被发射粒子的方向。
    * @param direction @~english The base direction of emitted particles. @~chinese 粒子基准方向。
    */
    void setParticleDirection(const Vec3& direction);

    /**
    * @~english Whether use auto direction.
    * @~chinese 是否使用自动方向计算。
    * @return @~english Whether use. @~chinese 是否使用。
    */
    bool isAutoDirection(void) const;

    /**
    * @~english Set use auto direction.
    * @~chinese 设置使用自动方向计算。
    * @param autoDirection @~english Whether use. @~chinese 是否使用。
    */
    void setAutoDirection(bool autoDirection);

    /**
    * @~english Whether force emission.
    * @~chinese 是否强制发射。
    * @return @~english Whether force. @~chinese 是否强制。
    */
    bool isForceEmission(void) const;

    /**
    * @~english Set force emission.
    * @~chinese 设置强制发射。
    * @param forceEmission @~english Whether force. @~chinese 是否强制。
    */
    void setForceEmission(bool forceEmission);

    /**
    * @~english Get the color of a particle that will be emitted.
    * @~chinese 获取发射粒子的颜色。
    * @return @~english The color of a particle. @~chinese 粒子颜色。
    */
    const Vec4& getParticleColor(void) const;

    /**
    * @~english Set the color of an emitted particle.
    * @~chinese 设置粒子颜色。
    * @param particleColour @~english The color of a particle. @~chinese 粒子颜色。
    */
    void setParticleColor(const Vec4& particleColour);

    /**
    * @~english Get the color range start of an emitted particle.
    * @~chinese 获取发射粒子的颜色范围的起始值。
    * @return @~english The color range start. @~chinese 颜色范围起始值。
    */
    const Vec4& getParticleColorRangeStart(void) const;

    /**
    * @~english Set the color range start of an emitted particle
    * @~chinese 设置发射粒子的颜色范围的起始值。
    * @param particleColourRangeStart @~english The color range start. @~chinese 颜色范围起始值。
    */
    void setParticleColorRangeStart(const Vec4& particleColourRangeStart);

    /**
    * @~english Get the color range end of an emitted particle.
    * @~chinese 获取发射粒子的颜色范围的终止值。
    * @return @~english The color range end. @~chinese 颜色范围终止值。
    */
    const Vec4& getParticleColorRangeEnd(void) const;

    /**
    * @~english Set the color range end of an emitted particle
    * @~chinese 设置发射粒子的颜色范围的终止值。
    * @param particleColourRangeEnd @~english The color range end. @~chinese 颜色范围终止值。
    */
    void setParticleColorRangeEnd(const Vec4& particleColourRangeEnd);

    /**
    * @~english Get the texture coords of an emitted particle.
    * @~chinese 获取发射粒子的纹理坐标。
    * @return @~english The texture coords. @~chinese 纹理坐标。
    */
    const unsigned short& getParticleTextureCoords(void) const;

    /**
    * @~english Set the texture coords of an emitted particle.
    * @~chinese 设置发射粒子的纹理坐标。
    * @param particleTextureCoords @~english The texture coords. @~chinese 纹理坐标。
    */
    void setParticleTextureCoords(const unsigned short& particleTextureCoords);

    /**
    * @~english Get the texture coords range start  of an emitted particle.
    * @~chinese 获取发射粒子的纹理坐标范围的起始值。
    * @return @~english The texture coords range start. @~chinese 纹理坐标范围的起始值。
    */
    const unsigned short& getParticleTextureCoordsRangeStart(void) const;

    /**
    * @~english Set the texture coords range start of an emitted particle.
    * @~chinese 设置发射粒子的纹理坐标范围的起始值。
    * @param particleTextureCoordsRangeStart @~english The texture coords range start. @~chinese 纹理坐标范围的起始值。
    */
    void setParticleTextureCoordsRangeStart(const unsigned short& particleTextureCoordsRangeStart);
            
    /**
    * @~english Get the texture coords range end of an emitted particle.
    * @~chinese 获取发射粒子的纹理坐标范围的终止值。
    * @return @~english The texture coords range end. @~chinese 纹理坐标范围的终止值。
    */
    const unsigned short& getParticleTextureCoordsRangeEnd(void) const;

    /**
    * @~english Set the texture coords range end of an emitted particle.
    * @~chinese 设置发射粒子的纹理坐标范围的终止值。
    * @param particleTextureCoordsRangeEnd @~english The texture coords range end. @~chinese 纹理坐标范围的终止值。
    */
    void setParticleTextureCoordsRangeEnd(const unsigned short& particleTextureCoordsRangeEnd);

    /**
    * @~english Whether use local coordinate system.
    * @~chinese 是否使用局部坐标系。
    * @return @~english Whether use. @~chinese 是否使用。
    */
    bool isKeepLocal(void) const;

    /**
    * @~english Set use local coordinate system, If this attribute is set to 'true', the particles are emitted relative to the emitter.
    * @~chinese 设置使用局部坐标系,如果设置的值为true，粒子的位置和发射器位置是相关的。
    * @param keepLocal @~english Whether use. @~chinese 是否使用。
    */
    void setKeepLocal(bool keepLocal);

    /**
    * @~english Transforms the particle position in a local position relative to the emitter
    * @~chinese 把粒子的位置变换到发射器的局部坐标系下。
    * @param particle @~english The transformed particle. @~chinese 需要变换的粒子。
    */
    bool makeParticleLocal(PUParticle3D* particle);

    /**
    * @~english Clone this emitter.
    * @~chinese 拷贝当前发射器。
    */
    virtual PUEmitter* clone() = 0;

    /**
    * @~english Copy attributes to another emitter(internal method).
    * @~chinese 拷贝属性到另外一个发射器(内部方法)。
    * @param emitter @~english The emitter. @~chinese 发射器。
    */
    virtual void copyAttributesTo (PUEmitter* emitter);

protected:

    /** Todo
    */
    virtual void initParticlePosition(PUParticle3D* particle);

    /**  Internal method for generating the particle direction.
    */
    virtual void initParticleDirection(PUParticle3D* particle);

    /**  Internal method for generating the particle orientation.
    */
    virtual void initParticleOrientation(PUParticle3D* particle);

    virtual void initParticleVelocity(PUParticle3D* particle);

    virtual void initParticleMass(PUParticle3D* particle);

    virtual void initParticleColor(PUParticle3D* particle);

    virtual void initParticleTextureCoords(PUParticle3D* particle);

    virtual float initParticleTimeToLive();

    virtual void initParticleDimensions(PUParticle3D* particle);

    virtual void initParticleForEmission(PUParticle3D* particle);

    /** Initialise some attributes that are time-based.
    */
    inline void initTimeBased(void);

        /**  Internal method for generating the angle.
    */
    void generateAngle(float &angle);
    
protected:

    Vec3 _position;

    Vec3 _latestPosition;
    Vec3 _latestPositionDiff;

    Vec3 _derivedPosition;
    Vec3 _emitterScale;///<Although the scale is on a Particle System level, the emitter can also be scaled.

    std::string _emitterType;///<Type of the emitter

    std::string _name;///<Name of the emitter (optional)

    Vec3 _particleDirection;///<Direction (and speed) of the emitted particle
            
    Vec3 _originalParticleDirection;///<The original direction of the emitted particle

    Quaternion _particleOrientation;///<Orientation of the particle as soon as it is emitted.


    Quaternion _particleOrientationRangeStart;///<Orientation range start
    Quaternion _particleOrientationRangeEnd;///<Orientation range end
    bool _particleOrientationRangeSet;///<If set, the range generates a random orientation between start and end.

    PUDynamicAttribute* _dynAngle;///< Angle around direction which particles may be emitted

    PUDynamicAttribute* _dynEmissionRate;///<Rate of particle emission

    //// Identifies the type of particle this emitter emits (default is visual particle).
    //ParticleType mEmitsType;

    std::string _emitsName;///<Identifies the name of particle this emitter emits (default is visual particle, so there is no name)

    PUDynamicAttribute* _dynTotalTimeToLive;///<Dynamic attribute used to generate the total time to live.

    PUDynamicAttribute* _dynParticleMass;///<Dynamic attribute used to generate the mass of a particle.


    PUDynamicAttribute* _dynVelocity;///<Dynamic attribute used to generate the velocity of a particle.

    PUDynamicAttribute* _dynDuration;///<Dynamic attribute used to define the duration of the emitter.

    PUDynamicAttribute* _dynRepeatDelay;///<Dynamic attribute used to define the repeat/delay of the emitter.

    PUDynamicAttribute* _dynParticleAllDimensions;///<Dynamic attribute used to define the (own) dimensions of a particle.
    bool _dynParticleAllDimensionsSet;///<Whether use dynamic attribute to define the dimensions of a particle.

    PUDynamicAttribute* _dynParticleWidth;///<Dynamic attribute used to define the (own) width of a particle.
    bool _dynParticleWidthSet;///<Whether use dynamic attribute to define the width of a particle.

    PUDynamicAttribute* _dynParticleHeight;///<Dynamic attribute used to define the (own) height of a particle.
    bool _dynParticleHeightSet;///<Whether use dynamic attribute to define the height of a particle.

    PUDynamicAttribute* _dynParticleDepth;///<Dynamic attribute used to define the (own) depth of a particle.
    bool _dynParticleDepthSet;///<Whether use dynamic attribute to define the depth of a particle.

    Vec3 _upVector;///<Notional up vector, just used to speed up generation of variant directions.

    float _remainder;///<As you know that the emitted particles must be int.
                     ///<This is the time left by last emit circle which is not enough to emit one particle.

    ///** Helper factory
    //*/
    //DynamicAttributeFactory mDynamicAttributeFactory;

    PUDynamicAttributeHelper _dynamicAttributeHelper;///<Helper class

    float _durationRemain;///<Duration remainder.

    bool _dynDurationSet;///<Indication to determine whether duration is set.

    float _repeatDelayRemain;///<Repeat/delay remainder.

    bool _dynRepeatDelaySet;///<Indication to determine whether repeat/delay is set.

    bool _autoDirection;///<Auto direction means that the direction of a particle is not determined by the direction vector that has been set,
                        ///<but the direction vector is generated based on the shape of the emitter.
                        ///<In most cases this means that the particle direction is perpendicular on the shape of the emitter.

    bool _forceEmission; ///<In normal cases, emission is regulated by time. This prevents that too much particles are
                         ///<emitted at once, which causes a drop in the framerate. In some cases you just want to emit
                         ///<all particles immediately without any delay. Setting the 'mForceEmission' to true enables this.
                         ///<In that case, the emission rate defines the number of particles that are emitted immediately.
                         ///<If the emission rate is 100, the emitter emits 100 particles at once and then disables.

    bool _originalForceEmission;///<Original value, used to set it back.

    bool _forceEmissionExecuted;///<If mForceEmission has been set to true and if all particles are emitted, the mForceEmissionExecuted
                                ///<is also set to true, preventing any further 'forced emission'.

    bool _originalForceEmissionExecuted;///<Original value, used to set it back.

    Vec4 _particleColor;///<Color that is assigned to an emitted particle.

    Vec4 _particleColorRangeStart;///<Used to randomize the colour of an emitted particle.

    Vec4 _particleColorRangeEnd;///<Used to randomize the colour of an emitted particle.

    bool _particleColorRangeSet;///<Used to determine whether the colour range has been set.

    bool _keepLocal;///<Determines whether particle positions should be kept local in relation to the emitter.

    unsigned short _particleTextureCoords;///<Texture coords that is assigned to an emitted particle (only works if the renderer uses it)

    unsigned short _particleTextureCoordsRangeStart;///<Used to randomize the texture coords of an emitted particle.
                
    unsigned short _particleTextureCoordsRangeEnd;///<Used to randomize the texture coords of an emitted particle.

    bool _particleTextureCoordsRangeSet;///<Used to determine whether the texture coords range has been set.

    bool _originEnabled;
    bool _originEnabledSet;

    PUParticle3D::ParticleType _emitsType;
    Ref *_emitsEntity;

    bool _isMarkedForEmission;
};

// end of _3d group
/// @}

NS_CC_END

#endif
