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
    /** creates an action with duration, grid size, waves and amplitude */
    static Waves3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /** returns the amplitude of the effect */
    inline float getAmplitude() const { return _amplitude; }
    /** sets the amplitude to the effect */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /** returns the amplitude rate */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /** sets the ampliture rate */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

	// Overrides
	virtual Waves3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Waves3D() {}
    virtual ~Waves3D() {}

    /** initializes an action with duration, grid size, waves and amplitude */
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
    /** creates the action with duration */
    static FlipX3D* create(float duration);

    // Override
	virtual FlipX3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipX3D() {}
    virtual ~FlipX3D() {}

    /** initializes the action with duration */
    bool initWithDuration(float duration);
    virtual bool initWithSize(const Size& gridSize, float duration);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipX3D);
};

/** @brief FlipY3D action */
class CC_DLL FlipY3D : public FlipX3D
{
public:
    /** creates the action with duration */
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
    /** creates the action with center position, radius, a grid size and duration */
    static Lens3D* create(float duration, const Size& gridSize, const Vector2& position, float radius);

    /** Get lens center position */
    inline float getLensEffect() const { return _lensEffect; }
    /** Set lens center position */
    inline void setLensEffect(float lensEffect) { _lensEffect = lensEffect; }
    /** Set whether lens is concave */
    inline void setConcave(bool concave) { _concave = concave; }
  
    inline const Vector2& getPosition() const { return _position; }
    void setPosition(const Vector2& position);

    // Overrides
	virtual Lens3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Lens3D() {}
    virtual ~Lens3D() {}

    /** initializes the action with center position, radius, a grid size and duration */
    bool initWithDuration(float duration, const Size& gridSize, const Vector2& position, float radius);

protected:
    /* lens center position */
    Vector2 _position;
    float _radius;
    /** lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect */
    float _lensEffect;
    /** lens is concave. (true = concave, false = convex) default is convex i.e. false */
    bool _concave;

    bool _dirty;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Lens3D);
};

/** @brief Ripple3D action */
class CC_DLL Ripple3D : public Grid3DAction
{
public:
    /** creates the action with radius, number of waves, amplitude, a grid size and duration */
    static Ripple3D* create(float duration, const Size& gridSize, const Vector2& position, float radius, unsigned int waves, float amplitude);

    /** get center position */
    inline const Vector2& getPosition() const { return _position; }
    /** set center position */
    void setPosition(const Vector2& position);

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

    /** initializes the action with radius, number of waves, amplitude, a grid size and duration */
    bool initWithDuration(float duration, const Size& gridSize, const Vector2& position, float radius, unsigned int waves, float amplitude);

protected:
    /* center position */
    Vector2 _position;
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
    /** creates the action with a range, shake Z vertices, a grid and duration */
    static Shaky3D* create(float duration, const Size& gridSize, int range, bool shakeZ);

    // Overrides
	virtual Shaky3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Shaky3D() {}
    virtual ~Shaky3D() {}
    
    /** initializes the action with a range, shake Z vertices, a grid and duration */
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
    /** creates the action with amplitude, a grid and duration */
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
    
    /** initializes the action with amplitude, a grid and duration */
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
    /** initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration */
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
    
    /** initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration */
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
    /** creates the action with center position, number of twirls, amplitude, a grid size and duration */
    static Twirl* create(float duration, const Size& gridSize, Vector2 position, unsigned int twirls, float amplitude);

    /** get twirl center */
    inline const Vector2& getPosition() const { return _position; }
    /** set twirl center */
    void setPosition(const Vector2& position);

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
    
    /** initializes the action with center position, number of twirls, amplitude, a grid size and duration */
    bool initWithDuration(float duration, const Size& gridSize, Vector2 position, unsigned int twirls, float amplitude);

protected:
    /* twirl center */
    Vector2 _position;
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
