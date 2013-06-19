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
#ifndef __ACTION_CCTILEDGRID_ACTION_H__
#define __ACTION_CCTILEDGRID_ACTION_H__

#include "CCActionGrid.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** @brief CCShakyTiles3D action */
class CC_DLL CCShakyTiles3D : public CCTiledGrid3DAction
{
public:
    /** initializes the action with a range, whether or not to shake Z vertices, a grid size, and duration */
    virtual bool initWithDuration(float duration, const CCSize& gridSize, int nRange, bool bShakeZ);

	/** returns a new clone of the action */
	virtual CCShakyTiles3D* clone() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:

    /** creates the action with a range, whether or not to shake Z vertices, a grid size, and duration */
    static CCShakyTiles3D* create(float duration, const CCSize& gridSize, int nRange, bool bShakeZ);

protected:
    int _randrange;
    bool _shakeZ;
};

/** @brief CCShatteredTiles3D action */
class CC_DLL CCShatteredTiles3D : public CCTiledGrid3DAction
{
public:
    /** initializes the action with a range, whether or not to shatter Z vertices, a grid size and duration */
    virtual bool initWithDuration(float duration, const CCSize& gridSize, int nRange, bool bShatterZ);

	/** returns a new clone of the action */
	virtual CCShatteredTiles3D* clone() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:

    /** creates the action with a range, whether of not to shatter Z vertices, a grid size and duration */
    static CCShatteredTiles3D* create(float duration, const CCSize& gridSize, int nRange, bool bShatterZ);
protected:
    int _randrange;
    bool _once;
    bool _shatterZ;
};

struct Tile;
/** @brief CCShuffleTiles action
 Shuffle the tiles in random order
 */
class CC_DLL CCShuffleTiles : public CCTiledGrid3DAction
{
public:
    ~CCShuffleTiles(void);
    /** initializes the action with a random seed, the grid size and the duration */
    virtual bool initWithDuration(float duration, const CCSize& gridSize, unsigned int seed);
    void shuffle(unsigned int *pArray, unsigned int nLen);
    CCSize getDelta(const CCSize& pos);
    void placeTile(const CCPoint& pos, Tile *t);

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

	/** returns a new clone of the action */
	virtual CCShuffleTiles* clone() const;

    virtual CCObject* copyWithZone(CCZone* pZone);

public:
    /** creates the action with a random seed, the grid size and the duration */
    static CCShuffleTiles* create(float duration, const CCSize& gridSize, unsigned int seed);
protected:
    unsigned int _seed;
    unsigned int _tilesCount;
    unsigned int* _tilesOrder;
    Tile* _tiles;
};

/** @brief CCFadeOutTRTiles action
 Fades out the tiles in a Top-Right direction
 */
class CC_DLL CCFadeOutTRTiles : public CCTiledGrid3DAction
{
public:
    virtual float testFunc(const CCSize& pos, float time);
    void turnOnTile(const CCPoint& pos);
    void turnOffTile(const CCPoint& pos);
    virtual void transformTile(const CCPoint& pos, float distance);
    virtual void update(float time);

	/** returns a new clone of the action */
	virtual CCFadeOutTRTiles* clone() const;

public:

    /** creates the action with the grid size and the duration */
    static CCFadeOutTRTiles* create(float duration, const CCSize& gridSize);
};

/** @brief CCFadeOutBLTiles action.
 Fades out the tiles in a Bottom-Left direction
 */
class CC_DLL CCFadeOutBLTiles : public CCFadeOutTRTiles
{
public:
    virtual float testFunc(const CCSize& pos, float time);

	/** returns a new clone of the action */
	virtual CCFadeOutBLTiles* clone() const;

public:

    /** creates the action with the grid size and the duration */
    static CCFadeOutBLTiles* create(float duration, const CCSize& gridSize);
};

/** @brief CCFadeOutUpTiles action.
 Fades out the tiles in upwards direction
 */
class CC_DLL CCFadeOutUpTiles : public CCFadeOutTRTiles
{
public:
    virtual float testFunc(const CCSize& pos, float time);
    virtual void transformTile(const CCPoint& pos, float distance);

	/** returns a new clone of the action */
	virtual CCFadeOutUpTiles* clone() const;

public:
    /** creates the action with the grid size and the duration */
    static CCFadeOutUpTiles* create(float duration, const CCSize& gridSize);

};

/** @brief CCFadeOutDownTiles action.
 Fades out the tiles in downwards direction
 */
class CC_DLL CCFadeOutDownTiles : public CCFadeOutUpTiles
{
public:
	/** returns a new clone of the action */
	virtual CCFadeOutDownTiles* clone() const;

    virtual float testFunc(const CCSize& pos, float time);

public:

    /** creates the action with the grid size and the duration */
    static CCFadeOutDownTiles* create(float duration, const CCSize& gridSize);
};

/** @brief CCTurnOffTiles action.
 Turn off the files in random order
 */
class CC_DLL CCTurnOffTiles : public CCTiledGrid3DAction
{
public:
    ~CCTurnOffTiles(void);
    /** initializes the action with a random seed, the grid size and the duration */
    virtual bool initWithDuration(float duration, const CCSize& gridSize, unsigned int seed);
    void shuffle(unsigned int *pArray, unsigned int nLen);
    void turnOnTile(const CCPoint& pos);
    void turnOffTile(const CCPoint& pos);

	/** returns a new clone of the action */
	virtual CCTurnOffTiles* clone() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:

    /** creates the action with the grid size and the duration */
    static CCTurnOffTiles* create(float duration, const CCSize& gridSize);
    /** creates the action with a random seed, the grid size and the duration */
    static CCTurnOffTiles* create(float duration, const CCSize& gridSize, unsigned int seed);

protected:
    unsigned int    _seed;
    unsigned int    _tilesCount;
    unsigned int*   _tilesOrder;
};

/** @brief CCWavesTiles3D action. */
class CC_DLL CCWavesTiles3D : public CCTiledGrid3DAction
{
public:
    /** waves amplitude */
    inline float getAmplitude(void) { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    /** waves amplitude rate */
    inline float getAmplitudeRate(void) { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    /** initializes the action with a number of waves, the waves amplitude, the grid size and the duration */
    virtual bool initWithDuration(float duration, const CCSize& gridSize, unsigned int waves, float amplitude);

	/** returns a new clone of the action */
	virtual CCWavesTiles3D* clone() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:
    /** creates the action with a number of waves, the waves amplitude, the grid size and the duration */
    static CCWavesTiles3D* create(float duration, const CCSize& gridSize, unsigned int waves, float amplitude);
protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
};

/** @brief CCJumpTiles3D action.
 A sin function is executed to move the tiles across the Z axis
 */
class CC_DLL CCJumpTiles3D : public CCTiledGrid3DAction
{
public:
    /** amplitude of the sin*/
    inline float getAmplitude(void) { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    /** amplitude rate */
    inline float getAmplitudeRate(void) { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    /** initializes the action with the number of jumps, the sin amplitude, the grid size and the duration */
    bool initWithDuration(float duration, const CCSize& gridSize, unsigned int numberOfJumps, float amplitude);

	/** returns a new clone of the action */
	virtual CCJumpTiles3D* clone() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);

public:

    /** creates the action with the number of jumps, the sin amplitude, the grid size and the duration */
    static CCJumpTiles3D* create(float duration, const CCSize& gridSize, unsigned int numberOfJumps, float amplitude);
protected:
    unsigned int _jumps;
    float _amplitude;
    float _amplitudeRate;
};

/** @brief CCSplitRows action */
class CC_DLL CCSplitRows : public CCTiledGrid3DAction
{
public :
    /** initializes the action with the number of rows to split and the duration */
    virtual bool initWithDuration(float duration, unsigned int nRows);

	/** returns a new clone of the action */
	virtual CCSplitRows* clone() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);
    virtual void startWithTarget(CCNode *pTarget);

public:

    /** creates the action with the number of rows to split and the duration */
    static CCSplitRows* create(float duration, unsigned int nRows);
protected:
    unsigned int _rows;
    CCSize _winSize;
};

/** @brief CCSplitCols action */
class CC_DLL CCSplitCols : public CCTiledGrid3DAction
{
public:
    /** initializes the action with the number of columns to split and the duration */
    virtual bool initWithDuration(float duration, unsigned int nCols);

	/** returns a new clone of the action */
	virtual CCSplitCols* clone() const;

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void update(float time);
    virtual void startWithTarget(CCNode *pTarget);

public:
    /** creates the action with the number of columns to split and the duration */
    static CCSplitCols* create(float duration, unsigned int nCols);
protected:
    unsigned int _cols;
    CCSize _winSize;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCTILEDGRID_ACTION_H__
