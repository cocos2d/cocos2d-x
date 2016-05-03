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

/**
@brief ShakyTiles3D action.
@details This action is make the target node shake with many tiles.
        You can create the action by these parameters:
        duration, grid size, range, whether shake on the z axis.
 */
class CC_DLL ShakyTiles3D : public TiledGrid3DAction
{
public:
    /** 
    @brief Create the action with a range, shake Z vertices, a grid and duration.
    @param duration Specify the duration of the ShakyTiles3D action. It's a value in seconds.
    @param gridSize Specify the size of the grid.
    @param range Specify the range of the shaky effect.
    @param shakeZ Specify whether shake on the z axis.
    @return If the creation success, return a pointer of ShakyTiles3D action; otherwise, return nil.
    */
    static ShakyTiles3D* create(float duration, const Size& gridSize, int range, bool shakeZ);

    // Override
	virtual ShakyTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShakyTiles3D() {}
    virtual ~ShakyTiles3D() {}

    /** 
    @brief Initializes the action with a range, shake Z vertices, grid size and duration.
    @param duration Specify the duration of the ShakyTiles3D action. It's a value in seconds.
    @param gridSize Specify the size of the grid.
    @param range Specify the range of the shaky effect.
    @param shakeZ Specify whether shake on the z axis.
    @return If the Initialization success, return true; otherwise, return false.
    */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ);

protected:
    int _randrange;
    bool _shakeZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShakyTiles3D);
};

/**
@brief ShatteredTiles3D action.
@details This action make the target node shattered with many tiles.
        You can create the action by these parameters:
        duration, grid size, range, whether shatter on the z axis.
*/
class CC_DLL ShatteredTiles3D : public TiledGrid3DAction
{
public:
    /** 
     * @brief Create the action with a range, whether of not to shatter Z vertices, grid size and duration.
     * @param duration Specify the duration of the ShatteredTiles3D action. It's a value in seconds.
     * @param gridSize Specify the size of the grid.
     * @param range Specify the range of the shatter effect.
     * @param shatterZ Specify whether shatter on the z axis.
     * @return If the creation success, return a pointer of ShatteredTiles3D action; otherwise, return nil.
     */
    static ShatteredTiles3D* create(float duration, const Size& gridSize, int range, bool shatterZ);

    // Override
	virtual ShatteredTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShatteredTiles3D() {}
    virtual ~ShatteredTiles3D() {}

    /** 
    @brief Initializes the action with a range, shatter Z vertices, grid size and duration.
    @param duration Specify the duration of the ShatteredTiles3D action. It's a value in seconds.
    @param gridSize Specify the size of the grid.
    @param range Specify the range of the shatter effect.
    @param shatterZ Specify whether shake on the z axis.
    @return If the Initialization success, return true; otherwise, return false.
    */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shatterZ);

protected:
    int _randrange;
    bool _once;
    bool _shatterZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShatteredTiles3D);
};

struct Tile;
/**
@brief ShuffleTiles action.
@details This action make the target node shuffle with many tiles in random order.
        You can create the action by these parameters:
        duration, grid size, the random seed.
*/
class CC_DLL ShuffleTiles : public TiledGrid3DAction
{
public:
    /** 
    * @brief Create the action with grid size, random seed and duration.
    * @param duration Specify the duration of the ShuffleTiles action. It's a value in seconds.
    * @param gridSize Specify the size of the grid.
    * @param seed Specify the random seed.
    * @return If the creation success, return a pointer of ShuffleTiles action; otherwise, return nil.
    */
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

    /** 
    * @brief Initializes the action with grid size, random seed and duration.
    * @param duration Specify the duration of the ShuffleTiles action. It's a value in seconds.
    * @param gridSize Specify the size of the grid.
    * @param seed Specify the random seed.
    * @return If the Initialization success, return true; otherwise, return false.
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

protected:
    unsigned int _seed;
    unsigned int _tilesCount;
    unsigned int* _tilesOrder;
    Tile* _tiles;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShuffleTiles);
};

/**
@brief FadeOutTRTiles action.
@details Fades out the target node with many tiles from Bottom-Left to Top-Right.
 */
class CC_DLL FadeOutTRTiles : public TiledGrid3DAction
{
public:
    /** 
    * @brief Create the action with the grid size and the duration.
    * @param duration Specify the duration of the FadeOutTRTiles action. It's a value in seconds.
    * @param gridSize Specify the size of the grid.
    * @return If the creation success, return a pointer of FadeOutTRTiles action; otherwise, return nil.
    */
    static FadeOutTRTiles* create(float duration, const Size& gridSize);

    /**
    @brief Calculate the percentage a tile should be shown.
    @param pos The position index of the tile.
    @param time The current percentage of the action.
    @return Return the percentage the tile should be shown.
    */
    virtual float testFunc(const Size& pos, float time);

    /**
    @brief Show the tile at specified position.
    @param pos The position index of the tile should be shown.
    */
    void turnOnTile(const Vec2& pos);

    /**
    @brief Hide the tile at specified position.
    @param pos The position index of the tile should be hide.
    */
    void turnOffTile(const Vec2& pos);

    /**
    @brief Show part of the tile.
    @param pos The position index of the tile should be shown.
    @param distance The percentage that the tile should be shown.
    */
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

/**
@brief FadeOutBLTiles action.
@details Fades out the target node with many tiles from Top-Right to Bottom-Left.
 */
class CC_DLL FadeOutBLTiles : public FadeOutTRTiles
{
public:
    /** 
    * @brief Create the action with the grid size and the duration.
    * @param duration Specify the duration of the FadeOutBLTiles action. It's a value in seconds.
    * @param gridSize Specify the size of the grid.
    * @return If the creation success, return a pointer of FadeOutBLTiles action; otherwise, return nil.
    */
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

/**
@brief FadeOutUpTiles action.
@details Fades out the target node with many tiles from bottom to top.
 */
class CC_DLL FadeOutUpTiles : public FadeOutTRTiles
{
public:
    /** 
    * @brief Create the action with the grid size and the duration.
    * @param duration Specify the duration of the FadeOutUpTiles action. It's a value in seconds.
    * @param gridSize Specify the size of the grid.
    * @return If the creation success, return a pointer of FadeOutUpTiles action; otherwise, return nil.
    */
    static FadeOutUpTiles* create(float duration, const Size& gridSize);

    virtual void transformTile(const Vec2& pos, float distance) override;

    // Overrides
	virtual FadeOutUpTiles* clone() const override;
    virtual float testFunc(const Size& pos, float time) override;

CC_CONSTRUCTOR_ACCESS:
    FadeOutUpTiles() {}
    virtual ~FadeOutUpTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutUpTiles);
};

/**
@brief FadeOutDownTiles action.
@details Fades out the target node with many tiles from top to bottom.
 */
class CC_DLL FadeOutDownTiles : public FadeOutUpTiles
{
public:
    /** 
    * @brief Create the action with the grid size and the duration.
    * @param duration Specify the duration of the FadeOutDownTiles action. It's a value in seconds.
    * @param gridSize Specify the size of the grid.
    * @return If the creation success, return a pointer of FadeOutDownTiles action; otherwise, return nil.
    */
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

/**
@brief TurnOffTiles action.
@details Turn off the target node with many tiles in random order.
 */
class CC_DLL TurnOffTiles : public TiledGrid3DAction
{
public:
    /** 
    * @brief Create the action with the grid size and the duration.
    * @param duration Specify the duration of the TurnOffTiles action. It's a value in seconds.
    * @param gridSize Specify the size of the grid.
    * @return If the creation success, return a pointer of TurnOffTiles action; otherwise, return nil.
    */
    static TurnOffTiles* create(float duration, const Size& gridSize);
    /** 
    * @brief Create the action with the grid size and the duration.
    * @param duration Specify the duration of the TurnOffTiles action. It's a value in seconds.
    * @param gridSize Specify the size of the grid.
    * @param seed Specify the random seed.
    * @return If the creation success, return a pointer of TurnOffTiles action; otherwise, return nil.
    */
    static TurnOffTiles* create(float duration, const Size& gridSize, unsigned int seed);

    /**
    @brief Shuffle the array specified.
    @param array The array will be shuffled.
    @param len The size of the array.
    */
    void shuffle(unsigned int *array, unsigned int len);

    /**
    @brief Show the tile at specified position.
    @param pos The position index of the tile should be shown.
    */
    void turnOnTile(const Vec2& pos);

    /**
    @brief Hide the tile at specified position.
    @param pos The position index of the tile should be hide.
    */
    void turnOffTile(const Vec2& pos);

    // Overrides
	virtual TurnOffTiles* clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TurnOffTiles() {}
    virtual ~TurnOffTiles();

    /** 
    * @brief Initializes the action with grid size, random seed and duration.
    * @param duration Specify the duration of the TurnOffTiles action. It's a value in seconds.
    * @param gridSize Specify the size of the grid.
    * @param seed Specify the random seed.
    * @return If the Initialization success, return true; otherwise, return false.
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

protected:
    unsigned int    _seed;
    unsigned int    _tilesCount;
    unsigned int*   _tilesOrder;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TurnOffTiles);
};

/**
@brief WavesTiles3D action.
@details This action wave the target node with many tiles.
*/
class CC_DLL WavesTiles3D : public TiledGrid3DAction
{
public:
    /** 
     * @brief Create the action with a number of waves, the waves amplitude, the grid size and the duration.
     * @param duration Specify the duration of the WavesTiles3D action. It's a value in seconds.
     * @param gridSize Specify the size of the grid.
     * @param waves Specify the waves count of the WavesTiles3D action.
     * @param amplitude Specify the amplitude of the WavesTiles3D action.
     * @return If the creation success, return a pointer of WavesTiles3D action; otherwise, return nil.
     */
    static WavesTiles3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /**
    @brief Get the amplitude of the effect.
    @return Return the amplitude of the effect.
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief Set the amplitude to the effect.
    @param amplitude The value of amplitude will be set.
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief Get the amplitude rate of the effect.
    @return Return the amplitude rate of the effect.
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief Set the amplitude rate of the effect.
    @param amplitudeRate The value of amplitude rate will be set.
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual WavesTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    WavesTiles3D() {}
    virtual ~WavesTiles3D() {}

    /** 
    @brief Initializes an action with duration, grid size, waves count and amplitude.
    @param duration Specify the duration of the WavesTiles3D action. It's a value in seconds.
    @param gridSize Specify the size of the grid.
    @param waves Specify the waves count of the WavesTiles3D action.
    @param amplitude Specify the amplitude of the WavesTiles3D action.
    @return If the initialization success, return true; otherwise, return false.
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(WavesTiles3D);
};

/**
@brief JumpTiles3D action.
@details Move the tiles of a target node across the Z axis.
*/
class CC_DLL JumpTiles3D : public TiledGrid3DAction
{
public:
    /** 
     * @brief Create the action with the number of jumps, the sin amplitude, the grid size and the duration.
     * @param duration Specify the duration of the JumpTiles3D action. It's a value in seconds.
     * @param gridSize Specify the size of the grid.
     * @param numberOfJumps Specify the jump tiles count.
     * @param amplitude Specify the amplitude of the JumpTiles3D action.
     * @return If the creation success, return a pointer of JumpTiles3D action; otherwise, return nil.
     */
    static JumpTiles3D* create(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

    /**
    @brief Get the amplitude of the effect.
    @return Return the amplitude of the effect.
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief Set the amplitude to the effect.
    @param amplitude The value of amplitude will be set.
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief Get the amplitude rate of the effect.
    @return Return the amplitude rate of the effect.
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief Set the amplitude rate of the effect.
    @param amplitudeRate The value of amplitude rate will be set.
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual JumpTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    JumpTiles3D() {}
    virtual ~JumpTiles3D() {}

    /** 
     * @brief Initializes the action with the number of jumps, the sin amplitude, the grid size and the duration.
     * @param duration Specify the duration of the JumpTiles3D action. It's a value in seconds.
     * @param gridSize Specify the size of the grid.
     * @param numberOfJumps Specify the jump tiles count.
     * @param amplitude Specify the amplitude of the JumpTiles3D action.
     * @return If the initialization success, return true; otherwise, return false.
     */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

protected:
    unsigned int _jumps;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpTiles3D);
};

/**
@brief SplitRows action.
@details Split the target node in many rows.
        Then move out some rows from left, move out the other rows from right.
*/
class CC_DLL SplitRows : public TiledGrid3DAction
{
public :
    /** 
     * @brief Create the action with the number of rows and the duration.
     * @param duration Specify the duration of the SplitRows action. It's a value in seconds.
     * @param rows Specify the rows count should be split.
     * @return If the creation success, return a pointer of SplitRows action; otherwise, return nil.
     */
    static SplitRows* create(float duration, unsigned int rows);

    // Overrides
	virtual SplitRows* clone() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitRows() {}
    virtual ~SplitRows() {}

    /** 
     * @brief Initializes the action with the number rows and the duration.
     * @param duration Specify the duration of the SplitRows action. It's a value in seconds.
     * @param rows Specify the rows count should be split.
     * @return If the creation success, return true; otherwise, return false.
     */
    bool initWithDuration(float duration, unsigned int rows);

protected:
    unsigned int _rows;
    Size _winSize;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SplitRows);
};

/**
@brief SplitCols action.
@details Split the target node in many columns.
        Then move out some columns from top, move out the other columns from bottom.
*/
class CC_DLL SplitCols : public TiledGrid3DAction
{
public:
    
    /** 
     * @brief Create the action with the number of columns and the duration.
     * @param duration Specify the duration of the SplitCols action. It's a value in seconds.
     * @param cols Specify the columns count should be split.
     * @return If the creation success, return a pointer of SplitCols action; otherwise, return nil.
     */
    static SplitCols* create(float duration, unsigned int cols);

    // Overrides
	virtual SplitCols* clone() const override;
    /**
     * @param time in seconds
     */
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitCols() {}
    virtual ~SplitCols() {}

    /** 
     * @brief Initializes the action with the number columns and the duration.
     * @param duration Specify the duration of the SplitCols action. It's a value in seconds.
     * @param cols Specify the columns count should be split.
     * @return If the creation success, return true; otherwise, return false.
     */
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
