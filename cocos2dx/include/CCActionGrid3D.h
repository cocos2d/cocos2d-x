/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
@brief CCWaves3D action 
*/
class CC_DLL CCWaves3D : public CCGrid3DAction
{
public:
    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** init the action */
    bool initWithWaves(int wav, float amp, const ccGridSize& gridSize, ccTime duration);

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(ccTime time);

public:
    /** create the action */
    static CCWaves3D* actionWithWaves(int wav, float amp, const ccGridSize& gridSize, ccTime duration);

protected:
    int m_nWaves;
    float m_fAmplitude;
    float m_fAmplitudeRate;
};

/** @brief CCFlipX3D action */
class CC_DLL CCFlipX3D : public CCGrid3DAction
{
public:
    /** initializes the action with duration */
    bool initWithDuration(ccTime duration);
    virtual bool initWithSize(const ccGridSize& gridSize, ccTime duration);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(ccTime time);

public:
    /** creates the action with duration */
    static CCFlipX3D* actionWithDuration(ccTime duration);
};

/** @brief CCFlipY3D action */
class CC_DLL CCFlipY3D : public CCFlipX3D
{
public:
    virtual void update(ccTime time);
    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action with duration */
    static CCFlipY3D* actionWithDuration(ccTime duration);
};

/** @brief CCLens3D action */
class CC_DLL CCLens3D : public CCGrid3DAction
{
public:
    /** Get lens center position */
    inline float getLensEffect(void) { return m_fLensEffect; }
    /** Set lens center position */
    inline void setLensEffect(float fLensEffect) { m_fLensEffect = fLensEffect; }
    
    inline const CCPoint& getPosition(void) { return m_position; }
    void setPosition(const CCPoint& position);

    /** initializes the action with center position, radius, a grid size and duration */
    bool initWithPosition(const CCPoint& pos, float r, const ccGridSize& gridSize, ccTime duration);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(ccTime time);

public:
    /** creates the action with center position, radius, a grid size and duration */
    static CCLens3D* actionWithPosition(const CCPoint& pos, float r, const ccGridSize& gridSize, ccTime duration);
protected:
    /* lens center position */
    CCPoint m_position;
    float m_fRadius;
    /** lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect */
    float m_fLensEffect;

    /* @since v0.99.5 */
    // CCPoint m_lastPosition;
    CCPoint m_positionInPixels;
    bool    m_bDirty;
};

/** @brief CCRipple3D action */
class CC_DLL CCRipple3D : public CCGrid3DAction
{
public:
    /** get center position */
    inline const CCPoint& getPosition(void) { return m_position; }
    /** set center position */
    void setPosition(const CCPoint& position);

    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** initializes the action with radius, number of waves, amplitude, a grid size and duration */
    bool initWithPosition(const CCPoint& pos, float r, int wav, float amp, 
        const ccGridSize& gridSize, ccTime duration);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(ccTime time);

public:
    /** creates the action with radius, number of waves, amplitude, a grid size and duration */
    static CCRipple3D* actionWithPosition(const CCPoint& pos, float r, int wav, float amp, 
        const ccGridSize& gridSize, ccTime duration);
protected:
    /* center position */
    CCPoint m_position;
    float m_fRadius;
    int m_nWaves;
    float m_fAmplitude;
    float m_fAmplitudeRate;

    /*@since v0.99.5*/
    CCPoint m_positionInPixels;
};

/** @brief CCShaky3D action */
class CC_DLL CCShaky3D : public CCGrid3DAction
{
public:
    /** initializes the action with a range, shake Z vertices, a grid and duration */
    bool initWithRange(int range, bool shakeZ, const ccGridSize& gridSize, ccTime duration);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(ccTime time);

public:
    /** creates the action with a range, shake Z vertices, a grid and duration */
    static CCShaky3D* actionWithRange(int range, bool shakeZ, const ccGridSize& gridSize, ccTime duration);

protected:
    int m_nRandrange;
    bool m_bShakeZ;
};

/** @brief CCLiquid action */
class CC_DLL CCLiquid : public CCGrid3DAction
{
public:
    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** initializes the action with amplitude, a grid and duration */
    bool initWithWaves(int wav, float amp, const ccGridSize& gridSize, ccTime duration);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(ccTime time);

public:
    /** creates the action with amplitude, a grid and duration */
    static CCLiquid* actionWithWaves(int wav, float amp, const ccGridSize& gridSize, ccTime duration);

protected:
    int m_nWaves;
    float m_fAmplitude;
    float m_fAmplitudeRate;
};

/** @brief CCWaves action */
class CC_DLL CCWaves : public CCGrid3DAction
{
public:
    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration */
    bool initWithWaves(int wav, float amp, bool h, bool v, const ccGridSize& gridSize,
        ccTime duration);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(ccTime time);

public:
    /** initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration */
    static CCWaves* actionWithWaves(int wav, float amp, bool h, bool v, const ccGridSize& gridSize,
        ccTime duration);
protected:
    int m_nWaves;
    float m_fAmplitude;
    float m_fAmplitudeRate;
    bool m_bVertical;
    bool m_bHorizontal;
};

/** @brief CCTwirl action */
class CC_DLL CCTwirl : public CCGrid3DAction
{
public:
    /** get twirl center */
    inline const CCPoint& getPosition(void) { return m_position; }
    /** set twirl center */
    void setPosition(const CCPoint& position);

    inline float getAmplitude(void) { return m_fAmplitude; }
    inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }

    inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

    /** initializes the action with center position, number of twirls, amplitude, a grid size and duration */
    bool initWithPosition(const CCPoint& pos, int t, float amp, const ccGridSize& gridSize,
        ccTime duration);
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(ccTime time);

public:
    /** creates the action with center position, number of twirls, amplitude, a grid size and duration */
    static CCTwirl* actionWithPosition(CCPoint pos, int t, float amp, const ccGridSize& gridSize,
        ccTime duration);
protected:
    /* twirl center */
    CCPoint m_position;
    int m_nTwirls;
    float m_fAmplitude;
    float m_fAmplitudeRate;

    /*@since v0.99.5 */
    CCPoint m_positionInPixels;
};

NS_CC_END

#endif // __ACTION_CCGRID3D_ACTION_H__
