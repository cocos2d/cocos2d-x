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

/** @brief ShakyTiles3D action */
class CC_DLL ShakyTiles3D : public TiledGrid3DAction
{
public:
    /** creates the action with a range, whether or not to shake Z vertices, a grid size, and duration */
    static ShakyTiles3D* create(float duration, const Size& gridSize, int nRange, bool bShakeZ);

    /** initializes the action with a range, whether or not to shake Z vertices, a grid size, and duration */
    bool initWithDuration(float duration, const Size& gridSize, int nRange, bool bShakeZ);

    // Override
	virtual ShakyTiles3D* clone() const override;
    virtual void update(float time) override;

protected:
    int _randrange;
    bool _shakeZ;
};

/** @brief ShatteredTiles3D action */
class CC_DLL ShatteredTiles3D : public TiledGrid3DAction
{
public:
    /** creates the action with a range, whether of not to shatter Z vertices, a grid size and duration */
    static ShatteredTiles3D* create(float duration, const Size& gridSize, int nRange, bool bShatterZ);

    /** initializes the action with a range, whether or not to shatter Z vertices, a grid size and duration */
    bool initWithDuration(float duration, const Size& gridSize, int nRange, bool bShatterZ);

    // Override
	virtual ShatteredTiles3D* clone() const override;
    virtual void update(float time) override;

protected:
    int _randrange;
    bool _once;
    bool _shatterZ;
};

struct Tile;
/** @brief ShuffleTiles action
 Shuffle the tiles in random order
 */
class CC_DLL ShuffleTiles : public TiledGrid3DAction
{
public:
    /** creates the action with a random seed, the grid size and the duration */
    static ShuffleTiles* create(float duration, const Size& gridSize, unsigned int seed);

    virtual ~ShuffleTiles(void);
    /** initializes the action with a random seed, the grid size and the duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

    void shuffle(unsigned int *array, unsigned int nLen);
    Size getDelta(const Size& pos) const;
    void placeTile(const Point& pos, Tile *t);

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
	virtual ShuffleTiles* clone() const override;

protected:
    unsigned int _seed;
    unsigned int _tilesCount;
    unsigned int* _tilesOrder;
    Tile* _tiles;
};

/** @brief FadeOutTRTiles action
 Fades out the tiles in a Top-Right direction
 */
class CC_DLL FadeOutTRTiles : public TiledGrid3DAction
{
public:
    /** creates the action with the grid size and the duration */
    static FadeOutTRTiles* create(float duration, const Size& gridSize);

    virtual float testFunc(const Size& pos, float time);
    void turnOnTile(const Point& pos);
    void turnOffTile(const Point& pos);
    virtual void transformTile(const Point& pos, float distance);

    // Overrides
    virtual void update(float time) override;
	virtual FadeOutTRTiles* clone() const override;
};

/** @brief FadeOutBLTiles action.
 Fades out the tiles in a Bottom-Left direction
 */
class CC_DLL FadeOutBLTiles : public FadeOutTRTiles
{
public:
    /** creates the action with the grid size and the duration */
    static FadeOutBLTiles* create(float duration, const Size& gridSize);

    // Overrides
    virtual float testFunc(const Size& pos, float time) override;
	virtual FadeOutBLTiles* clone() const override;
};

/** @brief FadeOutUpTiles action.
 Fades out the tiles in upwards direction
 */
class CC_DLL FadeOutUpTiles : public FadeOutTRTiles
{
public:
    /** creates the action with the grid size and the duration */
    static FadeOutUpTiles* create(float duration, const Size& gridSize);

    virtual void transformTile(const Point& pos, float distance);

    // Overrides
	virtual FadeOutUpTiles* clone() const override;
    virtual float testFunc(const Size& pos, float time) override;
};

/** @brief FadeOutDownTiles action.
 Fades out the tiles in downwards direction
 */
class CC_DLL FadeOutDownTiles : public FadeOutUpTiles
{
public:
    /** creates the action with the grid size and the duration */
    static FadeOutDownTiles* create(float duration, const Size& gridSize);

    // Overrides
	virtual FadeOutDownTiles* clone() const override;
    virtual float testFunc(const Size& pos, float time) override;
};

/** @brief TurnOffTiles action.
 Turn off the files in random order
 */
class CC_DLL TurnOffTiles : public TiledGrid3DAction
{
public:
    /** creates the action with the grid size and the duration */
    static TurnOffTiles* create(float duration, const Size& gridSize);
    /** creates the action with a random seed, the grid size and the duration */
    static TurnOffTiles* create(float duration, const Size& gridSize, unsigned int seed);

    ~TurnOffTiles(void);
    /** initializes the action with a random seed, the grid size and the duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

    void shuffle(unsigned int *pArray, unsigned int nLen);
    void turnOnTile(const Point& pos);
    void turnOffTile(const Point& pos);

    // Overrides
	virtual TurnOffTiles* clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

protected:
    unsigned int    _seed;
    unsigned int    _tilesCount;
    unsigned int*   _tilesOrder;
};

/** @brief WavesTiles3D action. */
class CC_DLL WavesTiles3D : public TiledGrid3DAction
{
public:
    /** creates the action with a number of waves, the waves amplitude, the grid size and the duration */
    static WavesTiles3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /** initializes the action with a number of waves, the waves amplitude, the grid size and the duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /** waves amplitude */
    inline float getAmplitude(void) const { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    /** waves amplitude rate */
    inline float getAmplitudeRate(void) const { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    // Override
	virtual WavesTiles3D* clone() const override;
    virtual void update(float time) override;

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
};

/** @brief JumpTiles3D action.
 A sin function is executed to move the tiles across the Z axis
 */
class CC_DLL JumpTiles3D : public TiledGrid3DAction
{
public:
    /** creates the action with the number of jumps, the sin amplitude, the grid size and the duration */
    static JumpTiles3D* create(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

    /** initializes the action with the number of jumps, the sin amplitude, the grid size and the duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

    /** amplitude of the sin*/
    inline float getAmplitude(void) const { return _amplitude; }
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    /** amplitude rate */
    inline float getAmplitudeRate(void) const { return _amplitudeRate; }
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    // Override
	virtual JumpTiles3D* clone() const override;
    virtual void update(float time) override;

protected:
    unsigned int _jumps;
    float _amplitude;
    float _amplitudeRate;
};

/** @brief SplitRows action */
class CC_DLL SplitRows : public TiledGrid3DAction
{
public :
    /** creates the action with the number of rows to split and the duration */
    static SplitRows* create(float duration, unsigned int nRows);

    /** initializes the action with the number of rows to split and the duration */
    bool initWithDuration(float duration, unsigned int nRows);

    // Overrides
	virtual SplitRows* clone() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;

protected:
    unsigned int _rows;
    Size _winSize;
};

/** @brief SplitCols action */
class CC_DLL SplitCols : public TiledGrid3DAction
{
public:
    /** creates the action with the number of columns to split and the duration */
    static SplitCols* create(float duration, unsigned int nCols);

    /** initializes the action with the number of columns to split and the duration */
    bool initWithDuration(float duration, unsigned int nCols);

    // Overrides
	virtual SplitCols* clone() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;

protected:
    unsigned int _cols;
    Size _winSize;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCTILEDGRID_ACTION_H__
