/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __CCPARTICLE_EXAMPLE_H__
#define __CCPARTICLE_EXAMPLE_H__

#include "2d/CCParticleSystemQuad.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

/** @class ParticleFire
 * @brief @~english A fire particle system.
 * @~chinese 一个火焰粒子系统.
 */
class CC_DLL ParticleFire : public ParticleSystemQuad
{
public:
    /** @~english Create a fire particle system.
     *
     * @~chinese 创建一个火焰粒子系统。
     * 
     * @return @~english An autoreleased ParticleFire object.
     * @~chinese 一个标记为自动释放的ParticleFire对象。
     */
    static ParticleFire* create();

    /** @~english Create a fire particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的火焰粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleFire object.
     * @~chinese 一个标记为自动释放的ParticleFire对象。
     * @js NA
     */
    static ParticleFire* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleFire(){}
    virtual ~ParticleFire(){}

    bool init() override { return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(int numberOfParticles) override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleFire);
};

/** @class ParticleFireworks
 * @brief @~english A fireworks particle system.
 * @~chinese 一个烟花粒子系统。
 */
class CC_DLL ParticleFireworks : public ParticleSystemQuad
{
public:
    /** @~english Create a fireworks particle system.
     *
     * @~chinese 创建一个烟花粒子系统。
     * 
     * @return @~english An autoreleased ParticleFireworks object.
     * @~chinese 一个标记为自动释放的ParticleFireworks对象。
     */
    static ParticleFireworks* create();

    /** @~english Create a fireworks particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的烟花粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleFireworks object.
     * @~chinese 一个标记为自动释放的ParticleFireworks对象。
     * @js NA
     */
    static ParticleFireworks* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleFireworks(){}
    virtual ~ParticleFireworks(){}

    bool init(){ return initWithTotalParticles(1500); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleFireworks);

};

/** @class ParticleSun
 * @brief @~english A sun particle system.
 * @~chinese 一个太阳粒子系统。
 */
class CC_DLL ParticleSun : public ParticleSystemQuad
{
public:
    /** @~english Create a sun particle system.
     *
     * @~chinese 创建一个太阳粒子系统。
     * 
     * @return @~english An autoreleased ParticleSun object.
     * @~chinese 一个标记为自动释放的ParticleSun对象。
     */
    static ParticleSun* create();

    /** @~english Create a sun particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的太阳粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleSun object.
     * @~chinese 一个标记为自动释放的ParticleSun对象。
     * @js NA
     */
    static ParticleSun* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleSun(){}
    virtual ~ParticleSun(){}

    bool init(){ return initWithTotalParticles(350); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSun);

};

/** @class ParticleGalaxy
 * @brief @~english A galaxy particle system.
 * @~chinese 一个星系粒子系统。
 */
class CC_DLL ParticleGalaxy : public ParticleSystemQuad
{
public:
    /** @~english Create a galaxy particle system.
     *
     * @~chinese 创建一个星系粒子系统。
     * 
     * @return @~english An autoreleased ParticleGalaxy object.
     * @~chinese 一个标记为自动释放的ParticleGalaxy对象。
     */
    static ParticleGalaxy* create();

    /** @~english Create a galaxy particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的星系粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleGalaxy object.
     * @~chinese 一个标记为自动释放的ParticleGalaxy对象。
     * @js NA
     */
    static ParticleGalaxy* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleGalaxy(){}
    virtual ~ParticleGalaxy(){}

    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleGalaxy);

};

/** @class ParticleFlower
 * @brief @~english A flower particle system.
 * @~chinese 一个花束粒子系统。
 */
class CC_DLL ParticleFlower : public ParticleSystemQuad
{
public:
    /** @~english Create a flower particle system.
     *
     * @~chinese 创建一个花束粒子系统。
     * 
     * @return @~english An autoreleased ParticleFlower object.
     * @~chinese 一个标记为自动释放的ParticleFlower对象。
     */
    static ParticleFlower* create();

    /** @~english Create a flower particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的花束粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleFlower object.
     * @~chinese 一个标记为自动释放的ParticleFlower对象。
     * @js NA
     */
    static ParticleFlower* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleFlower(){}
    virtual ~ParticleFlower(){}

    bool init(){ return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleFlower);
};

/** @class ParticleMeteor
 * @brief @~english A meteor particle system.
 * @~chinese 一个流星粒子系统。
 */
class CC_DLL ParticleMeteor : public ParticleSystemQuad
{
public:
    /** @~english Create a meteor particle system.
     *
     * @~chinese 创建一个流星粒子系统。
     * 
     * @return @~english An autoreleased ParticleMeteor object.
     * @~chinese 一个标记为自动释放的ParticleMeteor对象。
     */
    static ParticleMeteor * create();

    /** @~english Create a meteor particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的流星粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleMeteor object.
     * @~chinese 一个标记为自动释放的ParticleMeteor对象。
     * @js NA
     */
    static ParticleMeteor* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:  
    ParticleMeteor(){}
    virtual ~ParticleMeteor(){}

    bool init(){ return initWithTotalParticles(150); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleMeteor);
};

/** @class ParticleSpiral
 * @brief @~english An spiral particle system.
 * @~chinese 一个漩涡粒子系统。
 */
class CC_DLL ParticleSpiral : public ParticleSystemQuad
{
public:
    /** @~english Create a spiral particle system.
     *
     * @~chinese 创建一个漩涡粒子系统。
     * 
     * @return @~english An autoreleased ParticleSpiral object.
     * @~chinese 一个标记为自动释放的ParticleSpiral对象。
     */
    static ParticleSpiral* create();

    /** @~english Create a spiral particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的漩涡粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleSpiral object.
     * @~chinese 一个标记为自动释放的ParticleSpiral对象。
     * @js NA
     */
    static ParticleSpiral* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleSpiral(){}
    virtual ~ParticleSpiral(){}

    bool init(){ return initWithTotalParticles(500); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSpiral);

};

/** @class ParticleExplosion
 * @brief @~english An explosion particle system.
 * @~chinese 一个爆炸粒子系统。
 */
class CC_DLL ParticleExplosion : public ParticleSystemQuad
{
public:
    /** @~english Create a explosion particle system.
     *
     * @~chinese 创建一个爆炸粒子系统。
     * 
     * @return @~english An autoreleased ParticleExplosion object.
     * @~chinese 一个标记为自动释放的ParticleExplosion对象。
     */
    static ParticleExplosion* create();

    /** @~english Create a explosion particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的爆炸粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleExplosion object.
     * @~chinese 一个标记为自动释放的ParticleExplosion对象。
     * @js NA
     */
    static ParticleExplosion* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleExplosion(){}
    virtual ~ParticleExplosion(){}

    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleExplosion);
};

/** @class ParticleSmoke
 * @brief @~english An smoke particle system.
 * @~chinese 一个烟粒子系统。
 */
class CC_DLL ParticleSmoke : public ParticleSystemQuad
{
public:
    /** @~english Create a smoke particle system.
     *
     * @~chinese 创建一个烟粒子系统。
     * 
     * @return @~english An autoreleased ParticleSmoke object.
     * @~chinese 一个标记为自动释放的ParticleSmoke对象。
     */
    static ParticleSmoke* create();

    /** @~english Create a smoke particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的烟粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleSmoke object.
     * @~chinese 一个标记为自动释放的ParticleSmoke对象。
     * @js NA
     */
    static ParticleSmoke* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleSmoke(){}
    virtual ~ParticleSmoke(){}

    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSmoke);
};

/** @class ParticleSnow
 * @brief @~english An snow particle system.
 * @~chinese 一个雪粒子系统。
 */
class CC_DLL ParticleSnow : public ParticleSystemQuad
{
public:
    /** @~english Create a snow particle system.
     *
     * @~chinese 创建一个雪粒子系统。
     * 
     * @return @~english An autoreleased ParticleSnow object.
     * @~chinese 一个标记为自动释放的ParticleSnow对象。
     */
    static ParticleSnow* create();

    /** @~english Create a snow particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的雪粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleSnow object.
     * @~chinese 一个标记为自动释放的ParticleSnow对象。
     * @js NA
     */
    static ParticleSnow* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleSnow(){}
    virtual ~ParticleSnow(){}

    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSnow);
};

/** @class ParticleRain
 * @brief @~english A rain particle system.
 * @~chinese 一个雨粒子系统。
 */
class CC_DLL ParticleRain : public ParticleSystemQuad
{
public:
    /** @~english Create a rain particle system.
     *
     * @~chinese 创建一个雨粒子系统。
     * 
     * @return @~english An autoreleased ParticleRain object.
     * @~chinese 一个标记为自动释放的ParticleRain对象。
     */
    static ParticleRain* create();

    /** @~english Create a rain particle system withe a fixed number of particles.
     *
     * @~chinese 创建一个给定粒子数量的雨粒子系统。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 粒子数量。
     * @return @~english An autoreleased ParticleRain object.
     * @~chinese 一个标记为自动释放的ParticleRain对象。
     * @js NA
     */
    static ParticleRain* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleRain(){}
    virtual ~ParticleRain(){}

    bool init(){ return initWithTotalParticles(1000); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleRain);
};

// end of _2d group
/// @}

NS_CC_END

#endif //__CCPARTICLE_EXAMPLE_H__
