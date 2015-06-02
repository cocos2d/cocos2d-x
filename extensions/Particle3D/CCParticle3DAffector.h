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

#ifndef __CC_PARTICLE_3D_AFFECTOR_H__
#define __CC_PARTICLE_3D_AFFECTOR_H__

#include "base/CCRef.h"
#include <vector>

NS_CC_BEGIN

class ParticleSystem3D;
struct Particle3D;

/**
* @addtogroup _3d
* @{
*/

/** @class Particle3DAffector
*@brief @~english Particle3DAffector is a base class, define interfaces.
 Specific implementation decisions by different affectors.
 Affector is mainly bound particles behavior after launch, such as acceleration, rotation, etc.
 One particle system works well without affector.

 @~chinese Particle3DAffector 是影响器的基类，定义影响器共有接口。
 具体的实现由不同的影响器类型定义。
 影响器主要是约束粒子在发射后的行为，例如加速、旋转等。
 粒子系统可以没有影响器。
*/
class CC_DLL Particle3DAffector : public Ref
{
    friend class ParticleSystem3D;
public:
    
    /**
    * @~english Update affector(internal method).
    * @~chinese 更新影响器(内部方法)
    * @param particle   @~english The current particle. @~chinese 当前的粒子。
    * @param deltaTime   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual void updateAffector(Particle3D* particle, float deltaTime);
    
    /**
    * @~english Set the affector enable or disable.
    * @~chinese 设置影响器可用或不可用。
    * @param enabled @~english Whether the affector enabled. @~chinese 影响器是否可用。
    */
    void setEnabled (bool enabled) { _isEnabled = enabled; }
    
    /**
    * @~english Get the affector enabled.
    * @~chinese 获取影响器是否可用。
    * @return @~english Whether the affector enabled. @~chinese 影响器是否可用。
    */
    bool isEnabled(void) const { return _isEnabled; }

CC_CONSTRUCTOR_ACCESS:
    Particle3DAffector();
    virtual ~Particle3DAffector();
    
protected:
    ParticleSystem3D* _particleSystem;
    bool _isEnabled;
};

// end of _3d group
/// @}

NS_CC_END

#endif
