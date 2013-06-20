/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      On-Core

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

#include "CCActionGrid.h"

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
    inline float getAmplitude(void) { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    /** initializes an action with duration, grid size, waves and amplitude */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

	/** returns a new clone of the action */
	virtual Waves3D* clone() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void update(float time);

public:
    /** creates an action with duration, grid size, waves and amplitude */
    static Waves3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);
protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
};

/** @brief FlipX3D action */
class CC_DLL FlipX3D : public Grid3DAction
{
public:
    /** initializes the action with duration */
    virtual bool initWithDuration(float duration);
    virtual bool initWithSize(const Size& gridSize, float duration);

	/** returns a new clone of the action */
	virtual FlipX3D* clone() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void update(float time);

public:
    /** creates the action with duration */
    static FlipX3D* create(float duration);
};

/** @brief FlipY3D action */
class CC_DLL FlipY3D : public FlipX3D
{
public:
    virtual void update(float time);
    virtual Object* copyWithZone(Zone* pZone);

public:
    /** creates the action with duration */
    static FlipY3D* create(float duration);
};

/** @brief Lens3D action */
class CC_DLL Lens3D : public Grid3DAction
{
public:
    /** Get lens center position */
    inline float getLensEffect(void) { return _lensEffect; }
    /** Set lens center position */
    inline void setLensEffect(float fLensEffect) { _lensEffect = fLensEffect; }
    /** Set whether lens is concave */
    inline void setConcave(bool bConcave) { _concave = bConcave; }
  
    inline const Point& getPosition(void) { return _position; }
    void setPosition(const Point& position);

    /** initializes the action with center position, radius, a grid size and duration */
    bool initWithDuration(float duration, const Size& gridSize, const Point& position, float radius);

	/** returns a new clone of the action */
	virtual Lens3D* clone() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void update(float time);

public:
    /** creates the action with center position, radius, a grid size and duration */
    static Lens3D* create(float duration, const Size& gridSize, const Point& position, float radius);
protected:
    /* lens center position */
    Point _position;
    float _radius;
    /** lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect */
    float _lensEffect;
    /** lens is concave. (true = concave, false = convex) default is convex i.e. false */
    bool _concave;

    bool    _dirty;
};

/** @brief Ripple3D action */
class CC_DLL Ripple3D : public Grid3DAction
{
public:
    /** get center position */
    inline const Point& getPosition(void) { return _position; }
    /** set center position */
    void setPosition(const Point& position);

    inline float getAmplitude(void) { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    /** initializes the action with radius, number of waves, amplitude, a grid size and duration */
    bool initWithDuration(float duration, const Size& gridSize, const Point& position, float radius, unsigned int waves, float amplitude);

	/** returns a new clone of the action */
	virtual Ripple3D* clone() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void update(float time);

public:
    /** creates the action with radius, number of waves, amplitude, a grid size and duration */
    static Ripple3D* create(float duration, const Size& gridSize, const Point& position, float radius, unsigned int waves, float amplitude);
protected:
    /* center position */
    Point _position;
    float _radius;
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
};

/** @brief Shaky3D action */
class CC_DLL Shaky3D : public Grid3DAction
{
public:
    /** initializes the action with a range, shake Z vertices, a grid and duration */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ);

	/** returns a new clone of the action */
	virtual Shaky3D* clone() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void update(float time);

public:
    /** creates the action with a range, shake Z vertices, a grid and duration */
    static Shaky3D* create(float duration, const Size& gridSize, int range, bool shakeZ);
protected:
    int _randrange;
    bool _shakeZ;
};

/** @brief Liquid action */
class CC_DLL Liquid : public Grid3DAction
{
public:
    inline float getAmplitude(void) { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    /** initializes the action with amplitude, a grid and duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

	/** returns a new clone of the action */
	virtual Liquid* clone() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void update(float time);

public:
    /** creates the action with amplitude, a grid and duration */
    static Liquid* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);
protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
};

/** @brief Waves action */
class CC_DLL Waves : public Grid3DAction
{
public:
    inline float getAmplitude(void) { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    /** initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);

	/** returns a new clone of the action */
	virtual Waves* clone() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void update(float time);

public:

    /** initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration */
    static Waves* create(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);
protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
    bool _vertical;
    bool _horizontal;
};

/** @brief Twirl action */
class CC_DLL Twirl : public Grid3DAction
{
public:
    /** get twirl center */
    inline const Point& getPosition(void) { return _position; }
    /** set twirl center */
    void setPosition(const Point& position);

    inline float getAmplitude(void) { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    /** initializes the action with center position, number of twirls, amplitude, a grid size and duration */
    bool initWithDuration(float duration, const Size& gridSize, Point position, unsigned int twirls, float amplitude);

	/** returns a new clone of the action */
	virtual Twirl* clone() const;

    virtual Object* copyWithZone(Zone* pZone);
    virtual void update(float time);

public:
    /** creates the action with center position, number of twirls, amplitude, a grid size and duration */
    static Twirl* create(float duration, const Size& gridSize, Point position, unsigned int twirls, float amplitude);
protected:
    /* twirl center */
    Point _position;
    unsigned int _twirls;
    float _amplitude;
    float _amplitudeRate;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID3D_ACTION_H__
