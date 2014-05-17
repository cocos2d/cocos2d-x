/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
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
#ifndef __ACTION_CCGRID3D_ACTION_H__
#define __ACTION_CCGRID3D_ACTION_H__

#include "2d/CCActionGrid.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** 
@brief Waves3D action 
*/
class CC_DLL Waves3D : public Grid3DAction
{
public:
    /** 用持续时间、网格大小、波的数目和振幅创建一个动作 */
    static Waves3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /** 获取特效的振幅 */
    inline float getAmplitude() const { return _amplitude; }
    /** 设置特效的振幅  */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /** 获取振幅率 */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /** 设置振幅率 */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

	// Overrides
	virtual Waves3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Waves3D() {}
    virtual ~Waves3D() {}

    /** 用持续时间、网格大小、波的数目和振幅初始化一个动作 */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Waves3D);
};

/** @brief FlipX3D action */
class CC_DLL FlipX3D : public Grid3DAction
{
public:
    /** 用持续时间创建动作 */
    static FlipX3D* create(float duration);

    // Override
	virtual FlipX3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipX3D() {}
    virtual ~FlipX3D() {}

    /** 用持续时间初始化动作 */
    bool initWithDuration(float duration);
    virtual bool initWithSize(const Size& gridSize, float duration);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipX3D);
};

/** @brief FlipY3D action */
class CC_DLL FlipY3D : public FlipX3D
{
public:
    /** 用持续时间创建动作 */
    static FlipY3D* create(float duration);

    // Overrides
    virtual void update(float time) override;
	virtual FlipY3D* clone() const override;

protected:
    FlipY3D() {}
    virtual ~FlipY3D() {}
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipY3D);
};

/** @brief Lens3D action */
class CC_DLL Lens3D : public Grid3DAction
{
public:
    /** 用中心坐标、半径、网格大小和持续时间创建动作 */
    static Lens3D* create(float duration, const Size& gridSize, const Vec2& position, float radius);

    /** 获取透镜的中心坐标 */
    inline float getLensEffect() const { return _lensEffect; }
    /** 设置透镜的中心坐标 */
    inline void setLensEffect(float lensEffect) { _lensEffect = lensEffect; }
    /** 设置透镜是否凹的 */
    inline void setConcave(bool concave) { _concave = concave; }
  
    inline const Vec2& getPosition() const { return _position; }
    void setPosition(const Vec2& position);

    // Overrides
	virtual Lens3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Lens3D() {}
    virtual ~Lens3D() {}

    /** 用中心坐标、半径、网格大小和持续时间初始化动作 */
    bool initWithDuration(float duration, const Size& gridSize, const Vec2& position, float radius);

protected:
    /* 透镜中心坐标 */
    Vec2 _position;
    float _radius;
    /** 透镜特效。默认 0.7。 0 代表没有特效，1代表非常强烈特效。*/
    float _lensEffect;
    /** 透镜是否凹的。（true 代表 凹的，false代表凸的） 默认是凸的，也就是false。
     lens is concave. (true = concave, false = convex) default is convex i.e. false */
    bool _concave;

    bool _dirty;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Lens3D);
};

/** @brief Ripple3D action */
class CC_DLL Ripple3D : public Grid3DAction
{
public:
    /** 用半径、波浪的数量、振幅、网格大小和持续时间创建动作 */
    static Ripple3D* create(float duration, const Size& gridSize, const Vec2& position, float radius, unsigned int waves, float amplitude);
 
    /** 获取中心坐标 */
    inline const Vec2& getPosition() const { return _position; }
    /** 设置中心坐标 */
    void setPosition(const Vec2& position);

    inline float getAmplitude() const { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    inline float getAmplitudeRate() const { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    // Override
	virtual Ripple3D* clone() const override;
    virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
    Ripple3D() {}
    virtual ~Ripple3D() {}

    /** 用半径、波浪的数目、振幅、网格大小和持续时间初始化动作 */
    bool initWithDuration(float duration, const Size& gridSize, const Vec2& position, float radius, unsigned int waves, float amplitude);

protected:
    /* 中心位置 */
    Vec2 _position;
    float _radius;
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Ripple3D);
};

/** @brief Shaky3D action */
class CC_DLL Shaky3D : public Grid3DAction
{
public:
    /** 用一个范围、是否晃动的z轴顶点、网格大小和持续时间创建动作 */
    static Shaky3D* create(float duration, const Size& gridSize, int range, bool shakeZ);

    // Overrides
	virtual Shaky3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Shaky3D() {}
    virtual ~Shaky3D() {}
    
    /** 用一个范围、是否晃动的z轴顶点、网格大小和持续时间初始化动作 */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ);

protected:
    int _randrange;
    bool _shakeZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Shaky3D);
};

/** @brief Liquid action */
class CC_DLL Liquid : public Grid3DAction
{
public:
    /** 用振幅、网格大小和持续时间创建动作 */
    static Liquid* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);
    
    inline float getAmplitude() const { return _amplitude; }
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    inline float getAmplitudeRate() const { return _amplitudeRate; }
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Overrides
	virtual Liquid* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Liquid() {}
    virtual ~Liquid() {}
    
    /** 用振幅、网格大小和持续时间初始化动作 */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Liquid);
};

/** @brief Waves action */
class CC_DLL Waves : public Grid3DAction
{
public:
    /** 用振幅、水平正弦、垂直正弦、网格大小和持续时间创建动作 */
    static Waves* create(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);

    inline float getAmplitude() const { return _amplitude; }
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    inline float getAmplitudeRate() const { return _amplitudeRate; }
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Overrides
	virtual Waves* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Waves() {}
    virtual ~Waves() {}
    
    /** 用振幅、水平正弦、垂直正弦、网格大小和持续时间初始化动作 */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
    bool _vertical;
    bool _horizontal;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Waves);
};

/** @brief Twirl action */
class CC_DLL Twirl : public Grid3DAction
{
public:
    /** 用中心坐标、螺旋数、振幅、网格大小和持续时间创建动作 */
    static Twirl* create(float duration, const Size& gridSize, Vec2 position, unsigned int twirls, float amplitude);

    /** 获取螺旋坐标 */
    inline const Vec2& getPosition() const { return _position; }
    /**设置螺旋坐标 */
    void setPosition(const Vec2& position);

    inline float getAmplitude() const { return _amplitude; }
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    inline float getAmplitudeRate() const { return _amplitudeRate; }
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }


    // Overrides
	virtual Twirl* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Twirl() {}
    virtual ~Twirl() {}
    
    /** 用中心坐标、螺旋数、振幅、网格大小和持续时间初始化动作 */
    bool initWithDuration(float duration, const Size& gridSize, Vec2 position, unsigned int twirls, float amplitude);

protected:
    /* 螺旋中心 */
    Vec2 _position;
    unsigned int _twirls;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Twirl);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID3D_ACTION_H__
