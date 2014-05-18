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
/** @brief ShakeTiels3D动作 */
class CC_DLL ShakyTiles3D : public TiledGrid3DAction
{
public:
	/** 根据抖动范围、Z顶点是否抖动、网格大小和持续时间创建ShakyTiles3D动作 */
    static ShakyTiles3D* create(float duration, const Size& gridSize, int range, bool shakeZ);

    // Override
	virtual ShakyTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShakyTiles3D() {}
    virtual ~ShakyTiles3D() {}
    /** 根据抖动范围、Z顶点是否抖动、网格大小和持续时间初始化ShakyTiles3D动作 */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ);

protected:
    int _randrange;
    bool _shakeZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShakyTiles3D);
};

/** @brief ShatteredTiles3D动作 */
class CC_DLL ShatteredTiles3D : public TiledGrid3DAction
{
public:
	/** 根据范围、Z顶点是否打碎、网格大小和持续时间创建ShatteredTiles3D动作 */
    static ShatteredTiles3D* create(float duration, const Size& gridSize, int range, bool shatterZ);

    // Override
	virtual ShatteredTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShatteredTiles3D() {}
    virtual ~ShatteredTiles3D() {}

	/** 根据范围、Z顶点是否打碎、网格大小和持续时间初始化ShatteredTiles3D动作 */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shatterZ);

protected:
    int _randrange;
    bool _once;
    bool _shatterZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShatteredTiles3D);
};

struct Tile;
/** @brief ShuffleTiles动作
 随机排列瓦片
 */
class CC_DLL ShuffleTiles : public TiledGrid3DAction
{
public:
	/** 根据随机种子、网格大小和持续时间创建ShuffleTiles动作 */
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

	/** 根据随机种子、网格大小和持续时间初始化ShuffleTiles动作 */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

protected:
    unsigned int _seed;
    unsigned int _tilesCount;
    unsigned int* _tilesOrder;
    Tile* _tiles;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShuffleTiles);
};

/** @brief FadeOutTRTiles动作
 从左下角向右上角依次淡出所有瓦片
 */
class CC_DLL FadeOutTRTiles : public TiledGrid3DAction
{
public:
	/** 根据网格大小和持续时间创建FadeOutTRTiles动作 */
    static FadeOutTRTiles* create(float duration, const Size& gridSize);

    virtual float testFunc(const Size& pos, float time);
    void turnOnTile(const Vec2& pos);
    void turnOffTile(const Vec2& pos);
    virtual void transformTile(const Vec2& pos, float distance);

    // Overrides
    virtual void update(float time) override;
	virtual FadeOutTRTiles* clone() const override;

protected:
    FadeOutTRTiles() {}
    virtual ~FadeOutTRTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutTRTiles);
};

/** @brief FadeOutBLTiles动作
 从右上角向左下角依次淡出所有瓦片
 */
class CC_DLL FadeOutBLTiles : public FadeOutTRTiles
{
public:
	/** 根据网格大小和持续时间创建FadeOutTRTiles动作 */
    static FadeOutBLTiles* create(float duration, const Size& gridSize);

    // Overrides
    virtual float testFunc(const Size& pos, float time) override;
	virtual FadeOutBLTiles* clone() const override;

protected:
    FadeOutBLTiles() {}
    virtual ~FadeOutBLTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutBLTiles);
};

/** @brief FadeOutUpTiles动作
 从下往上依次淡出所有瓦片
 */
class CC_DLL FadeOutUpTiles : public FadeOutTRTiles
{
public:
	/** 根据网格大小和持续时间创建FadeOutTRTiles动作 */
    static FadeOutUpTiles* create(float duration, const Size& gridSize);

    virtual void transformTile(const Vec2& pos, float distance);

    // Overrides
	virtual FadeOutUpTiles* clone() const override;
    virtual float testFunc(const Size& pos, float time) override;

protected:
    FadeOutUpTiles() {}
    virtual ~FadeOutUpTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutUpTiles);
};

/** @brief FadeOutDownTiles动作。
 从上往下依次淡出所有瓦片
 */
class CC_DLL FadeOutDownTiles : public FadeOutUpTiles
{
public:
	/** 根据网格大小和持续时间创建FadeOutTRTiles动作 */
    static FadeOutDownTiles* create(float duration, const Size& gridSize);

    // Overrides
	virtual FadeOutDownTiles* clone() const override;
    virtual float testFunc(const Size& pos, float time) override;

protected:
    FadeOutDownTiles() {}
    virtual ~FadeOutDownTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutDownTiles);
};

/** @brief TurnOffTiles动作。
 随机关闭瓦片。
 */
class CC_DLL TurnOffTiles : public TiledGrid3DAction
{
public:
	/** 根据网格大小和持续时间创建FadeOutTRTiles动作 */
    static TurnOffTiles* create(float duration, const Size& gridSize);
	/** 根据随机种子、网格大小和持续时间创建FadeOutTRTiles动作 */
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

	/** 根据随机种子、网格大小和持续时间初始化FadeOutTRTiles动作 */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

protected:
    unsigned int    _seed;
    unsigned int    _tilesCount;
    unsigned int*   _tilesOrder;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TurnOffTiles);
};

/** @brief WavesTiles3D动作。 */
class CC_DLL WavesTiles3D : public TiledGrid3DAction
{
public:
	/** 根据波动次数、振幅、网格大小和持续时间创建WavesTiles3D动作 */
    /** creates the action with a number of waves, the waves amplitude, the grid size and the duration */
    static WavesTiles3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

	/** 振幅 */
    inline float getAmplitude(void) const { return _amplitude; }
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

	/** 振幅系数 */ 
    inline float getAmplitudeRate(void) const { return _amplitudeRate; }
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual WavesTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    WavesTiles3D() {}
    virtual ~WavesTiles3D() {}

	/** 根据波动次数、振幅、网格大小和持续时间初始化WavesTiles3D动作 */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(WavesTiles3D);
};

/** @brief JumpTiles3D动作。
 以Z轴为轴，根据正弦函数曲线移动瓦片。
 */
class CC_DLL JumpTiles3D : public TiledGrid3DAction
{
public:
	/** 根据跳跃次数、正弦曲线振幅、网格大小以及持续时间创建JumpTiles3D动作 */
    static JumpTiles3D* create(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

	/** 正弦曲线振幅 */
    inline float getAmplitude(void) const { return _amplitude; }
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

	/** 振幅系数 */
    inline float getAmplitudeRate(void) const { return _amplitudeRate; }
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual JumpTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    JumpTiles3D() {}
    virtual ~JumpTiles3D() {}

	/** 根据跳跃次数、正弦曲线振幅、网格大小以及持续时间初始化JumpTiles3D动作 */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

protected:
    unsigned int _jumps;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpTiles3D);
};

/** @brief SplitRows动作*/
class CC_DLL SplitRows : public TiledGrid3DAction
{
public :
	/** 根据分割的行数和持续时间创建SplitRows动作 */
    static SplitRows* create(float duration, unsigned int rows);

    // Overrides
	virtual SplitRows* clone() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitRows() {}
    virtual ~SplitRows() {}

	/** 根据分割的行数和持续时间初始化SplitRows动作 */
    bool initWithDuration(float duration, unsigned int rows);

protected:
    unsigned int _rows;
    Size _winSize;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SplitRows);
};

/** @brief SplitCols动作 */
class CC_DLL SplitCols : public TiledGrid3DAction
{
public:
	/** 根据分割的列数和持续时间创建SplitCols动作 */
    static SplitCols* create(float duration, unsigned int cols);

    // Overrides
	virtual SplitCols* clone() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitCols() {}
    virtual ~SplitCols() {}

	/** 根据分割的列数和持续时间初始化SplitCols动作 */
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
