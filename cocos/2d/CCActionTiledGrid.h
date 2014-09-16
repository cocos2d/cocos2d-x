/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
CopyRight (c) 2013-2014 Chukong Technologies Inc.

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

#include "2d/CCActionGrid.h"

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
    static ShakyTiles3D* create(float duration, const Size& gridSize, int range, bool shakeZ);

    // Override
	virtual ShakyTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShakyTiles3D() {}
    virtual ~ShakyTiles3D() {}

    /** initializes the action with a range, whether or not to shake Z vertices, a grid size, and duration */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ);

protected:
    int _randrange;
    bool _shakeZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShakyTiles3D);
};

/** @brief ShatteredTiles3D action */
class CC_DLL ShatteredTiles3D : public TiledGrid3DAction
{
public:
    /** creates the action with a range, whether of not to shatter Z vertices, a grid size and duration */
    static ShatteredTiles3D* create(float duration, const Size& gridSize, int range, bool shatterZ);

    // Override
	virtual ShatteredTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShatteredTiles3D() {}
    virtual ~ShatteredTiles3D() {}

    /** initializes the action with a range, whether or not to shatter Z vertices, a grid size and duration */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shatterZ);

protected:
    int _randrange;
    bool _once;
    bool _shatterZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShatteredTiles3D);
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

    void shuffle(unsigned int *array, unsigned int len);
    Size getDelta(const Size& pos) const;
    void placeTile(const Vec2& pos, Tile *t);

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
	virtual ShuffleTiles* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    ShuffleTiles() {}
    virtual ~ShuffleTiles();

    /** initializes the action with a random seed, the grid size and the duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

protected:
    unsigned int _seed;
    unsigned int _tilesCount;
    unsigned int* _tilesOrder;
    Tile* _tiles;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShuffleTiles);
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
    void turnOnTile(const Vec2& pos);
    void turnOffTile(const Vec2& pos);
    virtual void transformTile(const Vec2& pos, float distance);

    // Overrides
    virtual void update(float time) override;
	virtual FadeOutTRTiles* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    FadeOutTRTiles() {}
    virtual ~FadeOutTRTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutTRTiles);
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

CC_CONSTRUCTOR_ACCESS:
    FadeOutBLTiles() {}
    virtual ~FadeOutBLTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutBLTiles);
};

/** @brief FadeOutUpTiles action.
 Fades out the tiles in upwards direction
 */
class CC_DLL FadeOutUpTiles : public FadeOutTRTiles
{
public:
    /** creates the action with the grid size and the duration */
    static FadeOutUpTiles* create(float duration, const Size& gridSize);

    virtual void transformTile(const Vec2& pos, float distance);

    // Overrides
	virtual FadeOutUpTiles* clone() const override;
    virtual float testFunc(const Size& pos, float time) override;

CC_CONSTRUCTOR_ACCESS:
    FadeOutUpTiles() {}
    virtual ~FadeOutUpTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutUpTiles);
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

CC_CONSTRUCTOR_ACCESS:
    FadeOutDownTiles() {}
    virtual ~FadeOutDownTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutDownTiles);
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

    void shuffle(unsigned int *array, unsigned int len);
    void turnOnTile(const Vec2& pos);
    void turnOffTile(const Vec2& pos);

    // Overrides
	virtual TurnOffTiles* clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TurnOffTiles() {}
    virtual ~TurnOffTiles();

    /** initializes the action with a random seed, the grid size and the duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

protected:
    unsigned int    _seed;
    unsigned int    _tilesCount;
    unsigned int*   _tilesOrder;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TurnOffTiles);
};

/** @brief WavesTiles3D action. */
class CC_DLL WavesTiles3D : public TiledGrid3DAction
{
public:
    /** creates the action with a number of waves, the waves amplitude, the grid size and the duration */
    static WavesTiles3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /** waves amplitude */
    inline float getAmplitude() const { return _amplitude; }
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /** waves amplitude rate */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual WavesTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    WavesTiles3D() {}
    virtual ~WavesTiles3D() {}

    /** initializes the action with a number of waves, the waves amplitude, the grid size and the duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(WavesTiles3D);
};

/** @brief JumpTiles3D action.
 A sin function is executed to move the tiles across the Z axis
 */
class CC_DLL JumpTiles3D : public TiledGrid3DAction
{
public:
    /** creates the action with the number of jumps, the sin amplitude, the grid size and the duration */
    static JumpTiles3D* create(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

    /** amplitude of the sin*/
    inline float getAmplitude() const { return _amplitude; }
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /** amplitude rate */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual JumpTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    JumpTiles3D() {}
    virtual ~JumpTiles3D() {}

    /** initializes the action with the number of jumps, the sin amplitude, the grid size and the duration */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

protected:
    unsigned int _jumps;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpTiles3D);
};

/** @brief SplitRows action */
class CC_DLL SplitRows : public TiledGrid3DAction
{
public :
    /** creates the action with the number of rows to split and the duration */
    static SplitRows* create(float duration, unsigned int rows);

    // Overrides
	virtual SplitRows* clone() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitRows() {}
    virtual ~SplitRows() {}

    /** initializes the action with the number of rows to split and the duration */
    bool initWithDuration(float duration, unsigned int rows);

protected:
    unsigned int _rows;
    Size _winSize;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SplitRows);
};

/** @brief SplitCols action */
class CC_DLL SplitCols : public TiledGrid3DAction
{
public:
    /** creates the action with the number of columns to split and the duration */
    static SplitCols* create(float duration, unsigned int cols);

    // Overrides
	virtual SplitCols* clone() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitCols() {}
    virtual ~SplitCols() {}

    /** initializes the action with the number of columns to split and the duration */
    bool initWithDuration(float duration, unsigned int cols);

protected:
    unsigned int _cols;
    Size _winSize;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SplitCols);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCTILEDGRID_ACTION_H__
