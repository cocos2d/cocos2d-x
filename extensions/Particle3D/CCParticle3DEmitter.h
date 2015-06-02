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

#ifndef __CC_PARTICLE_3D_EMITTER_H__
#define __CC_PARTICLE_3D_EMITTER_H__

#include "base/CCRef.h"
#include <vector>

NS_CC_BEGIN

class ParticleSystem3D;
struct Particle3D;

/**
* @addtogroup _3d
* @{
*/

/** @class Particle3DEmitter
*@brief @~english Particle3DEmitter is a base class, define interfaces.
 Specific implementation decisions by different emitters.
 Emitter is mainly determined how particles emitted, such as point emission, spherical emission, etc.
 One particle system must have a emitter.

 @~chinese Particle3DEmitter 是发射器的基类，定义发射器共有接口。
 具体的实现由不同的发射器类型定义。
 发射器主要是决定粒子如何发射，例如点发射，球面发射。
 粒子系统必须要有发射器。
*/
class CC_DLL Particle3DEmitter : public Ref
{
    friend class ParticleSystem3D;
public:
    
    /**
    * @~english Update emitter(internal method).
    * @~chinese 更新发射器(内部方法)。
    * @param particle   @~english The current particle. @~chinese 当前的粒子。
    * @param deltaTime   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    */
    virtual void updateEmitter(Particle3D* particle, float deltaTime);
    
    /**
    * @~english Emit particles(internal method).
    * @~chinese 更新粒子(内部方法)。
    * @param count   @~english The number of emitted particles. @~chinese 发射粒子的数量。
    */
    virtual void emit(int count);
    
    /**
    * @~english Set the emitter enable or disable.
    * @~chinese 设置发射器可用或不可用。
    * @param enabled @~english Whether the emitter enabled. @~chinese 发射器是否可用。
    */
    void setEnabled (bool enabled) { _isEnabled = enabled; }
    
    /**
    * @~english Get the emitter enabled.
    * @~chinese 获取发射器是否可用。
    * @return @~english Whether the emitter enabled. @~chinese 发射器是否可用。
    */
    bool isEnabled(void) const { return _isEnabled; }

CC_CONSTRUCTOR_ACCESS:
    Particle3DEmitter();
    virtual ~Particle3DEmitter();
    
protected:
    ParticleSystem3D* _particleSystem;
    int _emitRate;
    bool _isEnabled;
};

// end of _3d group
/// @}

NS_CC_END

#endif
