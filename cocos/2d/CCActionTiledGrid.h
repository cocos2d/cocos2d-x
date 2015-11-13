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
@brief @~english ShakyTiles3D action.
 * @~chinese ShakyTiles3D动作。
@details @~english This action is make the target node shake with many tiles.
        You can create the action by these parameters:
        duration, grid size, range, whether shake on the z axis.
 * @~chinese 这是一个让目标节点以多个瓦片的形式晃动的动作。
 * 您可以用这些参数创建动作:
 * 持续时间、网格大小、范围、是否在z轴上动摇。
 */
class CC_DLL ShakyTiles3D : public TiledGrid3DAction
{
public:
    /** 
    @brief @~english Create the action with a range, shake Z vertices, a grid and duration.
    * @~chinese 根据抖动范围、Z顶点是否抖动、网格大小和持续时间创建ShakyTiles3D动作。
    @param duration @~english Specify the duration of the ShakyTiles3D action. It's a value in seconds.
    * @~chinese 指定ShakyTiles3D动作的持续时间。这是一个以秒为单位的值。
    @param gridSize @~english Specify the size of the grid.
    * @~chinese 指定网格的大小。
    @param range @~english Specify the range of the shaky effect.
    * @~chinese 指定摇动效果的范围。
    @param shakeZ @~english Specify whether shake on the z axis.
    * @~chinese 指定是否在z轴上动摇。
    @return @~english If the creation success, return a pointer of ShakyTiles3D action; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个指向ShakyTiles3D动作的指针;否则,返回空。
    */
    static ShakyTiles3D* create(float duration, const Size& gridSize, int range, bool shakeZ);

    // Override
	virtual ShakyTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShakyTiles3D() {}
    virtual ~ShakyTiles3D() {}

    /** 
    @brief @~english Initializes the action with a range, shake Z vertices, grid size and duration.
     * @~chinese 根据抖动范围、Z顶点是否抖动、网格大小和持续时间初始化ShakyTiles3D动作。
    @param duration @~english Specify the duration of the ShakyTiles3D action. It's a value in seconds.
     * @~chinese 指定ShakyTiles3D动作的持续时间。这是一个以秒为单位的值。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    @param range @~english Specify the range of the shaky effect.
     * @~chinese  指定摇动效果的范围。
    @param shakeZ @~english Specify whether shake on the z axis.
     * @~chinese 指定是否在z轴上动摇。

    @return @~english If the Initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功,返回true,否则返回false。
    */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ);

protected:
    int _randrange;
    bool _shakeZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShakyTiles3D);
};

/**
@brief @~english ShatteredTiles3D action.
 * @~chinese ShatteredTiles3D 动作。
@details @~english This action make the target node shattered with many tiles.
        You can create the action by these parameters:
        duration, grid size, range, whether shatter on the z axis.
        * @~chinese 这是一个让目标节点以多个瓦片的形式摇动的动作
        * 您可以用这些参数创建动作:
        * 持续时间、网格大小、范围、是否在z轴上动摇。
*/
class CC_DLL ShatteredTiles3D : public TiledGrid3DAction
{
public:
    /** 
     * @brief @~english Create the action with a range, whether of not to shatter Z vertices, grid size and duration.
     * @~chinese 根据抖动范围、Z顶点是否抖动、网格大小和持续时间创建动作。
     * @param duration @~english Specify the duration of the ShatteredTiles3D action. It's a value in seconds.
     * @~chinese 指定ShakyTiles3D动作的持续时间。这是一个以秒为单位的值。
     * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
     * @param range @~english Specify the range of the shatter effect.
     * @~chinese 指定范围的粉碎效果。
     * @param shatterZ @~english Specify whether shatter on the z axis.
     * @~chinese 指定摇动效果的范围。
     * @return @~english If the creation success, return a pointer of ShatteredTiles3D action; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个指向ShatteredTiles3D的指针。否则,返回空。
     */
    static ShatteredTiles3D* create(float duration, const Size& gridSize, int range, bool shatterZ);

    // Override
	virtual ShatteredTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShatteredTiles3D() {}
    virtual ~ShatteredTiles3D() {}

    /** 
    @brief @~english Initializes the action with a range, shatter Z vertices, grid size and duration.
    * @~chinese 根据抖动范围、Z顶点是否抖动、网格大小和持续时间初始化动作。
    @param duration @~english Specify the duration of the ShatteredTiles3D action. It's a value in seconds.
    * @~chinese 指定ShakyTiles3D动作的持续时间。这是一个以秒为单位的值。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    @param range @~english Specify the range of the shatter effect.
    * @~chinese 指定范围的粉碎效果。
    @param shatterZ @~english Specify whether shake on the z axis.
    * @~chinese 指定摇动效果的范围。
    @return @~english If the Initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功,返回true,否则返回false。
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
@brief @~english ShuffleTiles action.
 * @~chinese ShuffleTiles 动作。
@details @~english This action make the target node shuffle with many tiles in random order.
        You can create the action by these parameters:
        duration, grid size, the random seed.
 * @~chinese 这是一个让目标节点以多个瓦片的形式随机洗牌的动作
 * 您可以用这些参数创建动作:
 * 持续时间、网格大小,随机种子。
*/
class CC_DLL ShuffleTiles : public TiledGrid3DAction
{
public:
    /** 
    * @brief @~english Create the action with grid size, random seed and duration.
     * @~chinese 使用网格大小的,随机种子和持续时间创建动作。
    * @param duration @~english Specify the duration of the ShuffleTiles action. It's a value in seconds.
    * @~chinese 指定ShuffleTile动作的持续时间。这是一个以秒为单位的值。
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    * @param seed @~english Specify the random seed.
     * @~chinese 指定随机种子。
    * @return @~english If the creation success, return a pointer of ShuffleTiles action; otherwise, return nil.
    * @~chinese 如果创建成功,返回一个指向ShuffleTile的指针。否则,返回空。
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
    * @brief @~english Initializes the action with grid size, random seed and duration.
    * @~chinese 使用网格大小的,随机种子和持续时间初始化动作。
    * @param duration @~english Specify the duration of the ShuffleTiles action. It's a value in seconds.
    * @~chinese 指定ShuffleTile动作的持续时间。这是一个以秒为单位的值。
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    * @param seed @~english Specify the random seed.
     * @~chinese 指定随机种子。
    * @return @~english If the Initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功,返回true,否则返回false。
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
@brief @~english FadeOutTRTiles action.
 * @~chinese FadeOutTRTiles行动。
@details @~english Fades out the target node with many tiles from Bottom-Left to Top-Right.
* @~chinese 这是一个让目标节点以多个瓦片的形式从左下到右上淡出的动作。
 */
class CC_DLL FadeOutTRTiles : public TiledGrid3DAction
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
     * @~chinese 使用网格大小和持续时间创建动作。
    * @param duration @~english Specify the duration of the FadeOutTRTiles action. It's a value in seconds.
    * @~chinese 指定FadeOutTRTile动作的持续时间。这是一个以秒为单位的值。
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    * @return @~english If the creation success, return a pointer of FadeOutTRTiles action; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个指向FadeOutTRTiles动作的指针;否则,返回空。
    */
    static FadeOutTRTiles* create(float duration, const Size& gridSize);

    /**
    @brief @~english Calculate the percentage a tile should be shown.
     * @~chinese 计算一个tile应该显示的百分比。
    @param pos @~english The position index of the tile.
     * @~chinese tile的位置索引。
    @param time @~english The current percentage of the action.
     * @~chinese 当前动作的百分比。
    @return @~english Return the percentage the tile should be shown.
     * @~chinese 返回tile应该显示的百分比。
    */
    virtual float testFunc(const Size& pos, float time);

    /**
    @brief @~english Show the tile at specified position.
     * @~chinese 显示指定位置的tile。
    @param pos @~english The position index of the tile should be shown.
     * @~chinese 应该显示的tile的位置索引。
    */
    void turnOnTile(const Vec2& pos);

    /**
    @brief @~english Hide the tile at specified position.
     * @~chinese 隐藏指定位置的tile。
    @param pos @~english The position index of the tile should be hide.
    * @~chinese 应该隐藏的tile的位置索引
    */
    void turnOffTile(const Vec2& pos);

    /**
    @brief @~english Show part of the tile.
     * @~chinese 展示tile的一部分。
    @param pos @~english The position index of the tile should be shown.
    * @~chinese 应该显示的tile的位置索引。
    @param distance @~english The percentage that the tile should be shown.
    * @~chinese 应该显示的tile的百分比。
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
@brief @~english FadeOutBLTiles action.
 * @~chinese FadeOutBLTiles动作。
@details @~english Fades out the target node with many tiles from Top-Right to Bottom-Left.
* @~chinese 这是一个让目标节点以多个瓦片的形式从右上到左下淡出的动作。
 */
class CC_DLL FadeOutBLTiles : public FadeOutTRTiles
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
    * @~chinese 使用网格大小和持续时间创建动作。
    * @param duration @~english Specify the duration of the FadeOutBLTiles action. It's a value in seconds.
    * @~chinese 指定FadeOutBLTiles动作的持续时间。这是一个以秒为单位的值。
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    * @return @~english If the creation success, return a pointer of FadeOutBLTiles action; otherwise, return nil.
    * @~chinese 如果创建成功,返回一个指向FadeOutBLTiles动作的指针;否则,返回空。
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
@brief @~english FadeOutUpTiles action.
 * @~chinese FadeOutUpTiles动作。
@details @~english Fades out the target node with many tiles from bottom to top.
* @~chinese 这是一个让目标节点以多个瓦片的形式从下到上淡出的动作
 */
class CC_DLL FadeOutUpTiles : public FadeOutTRTiles
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
    * @~chinese  使用网格大小和持续时间创建动作。
    * @param duration @~english Specify the duration of the FadeOutUpTiles action. It's a value in seconds.
    * @~chinese 指定FadeOutUpTiles动作的持续时间。这是一个以秒为单位的值。
    * @param gridSize @~english Specify the size of the grid.
    * @~chinese 指定网格的大小
    * @return @~english If the creation success, return a pointer of FadeOutUpTiles action; otherwise, return nil.
    * @~chinese 如果创建成功,返回一个指向FadeOutUpTiles动作的指针;否则,返回空。
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
@brief @~english FadeOutDownTiles action.
 * @~chinese FadeOutDownTiles动作。
@details @~english Fades out the target node with many tiles from top to bottom.
* @~chinese 这是一个让目标节点以多个瓦片的形式从上到下淡出的动作
 */
class CC_DLL FadeOutDownTiles : public FadeOutUpTiles
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
    * @~chinese 使用网格大小和持续时间创建动作
    * @param duration @~english Specify the duration of the FadeOutDownTiles action. It's a value in seconds.
    * @~chinese 指定FadeOutDownTiles动作的持续时间。这是一个以秒为单位的值。
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    * @return @~english If the creation success, return a pointer of FadeOutDownTiles action; otherwise, return nil.
    * @~chinese 如果创建成功,返回一个指向FadeOutDownTiles动作的指针;否则,返回空。
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
@brief @~english TurnOffTiles action.
 * @~chinese TurnOffTiles动作。
@details @~english Turn off the target node with many tiles in random order.
* @~chinese 这是一个让目标节点以多个瓦片的形式随机关闭的动作
 */
class CC_DLL TurnOffTiles : public TiledGrid3DAction
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
    * @~chinese 使用网格大小和持续时间创建动作。
    * @param duration @~english Specify the duration of the TurnOffTiles action. It's a value in seconds.
    * @~chinese 指定TurnOffTiles动作的持续时间。这是一个以秒为单位的值。
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    * @return @~english If the creation success, return a pointer of TurnOffTiles action; otherwise, return nil.
    * @~chinese 如果创建成功,返回一个指向TurnOffTiles动作的指针;否则,返回空。
    */
    static TurnOffTiles* create(float duration, const Size& gridSize);
    /** 
    * @brief @~english Create the action with the grid size, the duration and random seed.
    * @~chinese 使用网格大小，持续时间和随机种子创建动作。
    * @param duration @~english Specify the duration of the TurnOffTiles action. It's a value in seconds.
    * @~chinese 指定TurnOffTiles动作的持续时间。这是一个以秒为单位的值。
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    * @param seed @~english Specify the random seed.
     * @~chinese 指定随机种子。
    * @return @~english If the creation success, return a pointer of TurnOffTiles action; otherwise, return nil.
    * @~chinese 如果创建成功,返回一个指向TurnOffTiles动作的指针;否则,返回空。
    */
    static TurnOffTiles* create(float duration, const Size& gridSize, unsigned int seed);

    /**
    @brief @~english Shuffle the array specified.
     * @~chinese 指定的随机数组。
    @param array @~english The array will be shuffled.
     * @~chinese 要被随机打乱的数组。
    @param len @~english The size of the array.
     * @~chinese 数组的大小。
    */
    void shuffle(unsigned int *array, unsigned int len);

    /**
    @brief @~english Show the tile at specified position.
     * @~chinese 显示指定位置的tile。
    @param pos @~english The position index of the tile should be shown.
     * @~chinese 应该显示的tile的位置索引。
    */
    void turnOnTile(const Vec2& pos);

    /**
    @brief @~english Hide the tile at specified position.
     * @~chinese 隐藏指定位置的tile。
    @param pos @~english The position index of the tile should be hide.
     * @~chinese 应该隐藏的tile的位置索引。
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
    * @brief @~english Initializes the action with grid size, random seed and duration.
    * @~chinese 使用网格大小，持续时间，随机种子初始化动作。
    * @param duration @~english Specify the duration of the TurnOffTiles action. It's a value in seconds.
    * @~chinese 指定TurnOffTiles动作的持续时间。这是一个以秒为单位的值。
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    * @param seed @~english Specify the random seed.
     * @~chinese 指定随机种子。
    * @return @~english If the Initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功,返回true,否则返回false。
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
@brief @~english WavesTiles3D action.
 * @~chinese WavesTiles3D动作。
@details @~english This action wave the target node with many tiles.
* @~chinese 这是一个让目标节点以多个瓦片的形式波动的动作
*/
class CC_DLL WavesTiles3D : public TiledGrid3DAction
{
public:
    /** 
     * @brief @~english Create the action with a number of waves, the waves amplitude, the grid size and the duration.
     * @~chinese 使用波数,波振幅,网格大小和持续时间来创建动作。
     * @param duration @~english Specify the duration of the WavesTiles3D action. It's a value in seconds.
     * @~chinese  指定WavesTiles3D动鞯某中奔洹Ｕ馐且桓鲆悦胛ノ坏闹怠�
     * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
     * @param waves @~english Specify the waves count of the WavesTiles3D action.
     * @~chinese 指定WavesTiles3D动作的波数。
     * @param amplitude @~english Specify the amplitude of the WavesTiles3D action.
     * @~chinese 指定WavesTiles3D动作的振幅。
     * @return @~english If the creation success, return a pointer of WavesTiles3D action; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个指向WavesTiles3D动作的指针;否则,返回空。
     */
    static WavesTiles3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese 获取振幅。
    @return @~english Return the amplitude of the effect.
     * @~chinese 振幅。
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese 设置振幅。
    @param amplitude @~english The value of amplitude will be set.
    * @~chinese 将被设置的幅值。
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese 获得振幅率。
    @return @~english Return the amplitude rate of the effect.
     * @~chinese 返回振幅率。
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese 设置ampliture率。
    @param amplitudeRate @~english The value of amplitude rate will be set.
    * @~chinese 将被设置的振幅率。
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual WavesTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    WavesTiles3D() {}
    virtual ~WavesTiles3D() {}

    /** 
    @brief @~english Initializes an action with duration, grid size, waves count and amplitude.
    * @~chinese 使用波数,波振幅,网格大小和持续时间初始化动作。
    @param duration @~english Specify the duration of the WavesTiles3D action. It's a value in seconds.
    * @~chinese 指定WavesTiles3D动作的持续时间。这是一个以秒为单位的值。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
    @param waves @~english Specify the waves count of the WavesTiles3D action.
    * @~chinese 指定WavesTiles3D动作的波数。
    @param amplitude @~english Specify the amplitude of the WavesTiles3D action.
    * @~chinese 指定WavesTiles3D动作的振幅。
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功,返回true,否则返回false。
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
@brief @~english JumpTiles3D action.
 * @~chinese JumpTiles3D动作。
@details @~english Move the tiles of a target node across the Z axis.
* @~chinese 这是一个让目标节点以多个瓦片的形式沿z轴移动的动作
*/
class CC_DLL JumpTiles3D : public TiledGrid3DAction
{
public:
    /** 
     * @brief @~english Create the action with the number of jumps, the sin amplitude, the grid size and the duration.
     * @~chinese 使用跳跃数，正弦振幅,网格大小和持续时间创建动作。
     * @param duration @~english Specify the duration of the JumpTiles3D action. It's a value in seconds.
     * @~chinese 指定JumpTiles3D动作的持续时间。这是一个以秒为单位的值。。
     * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
     * @param numberOfJumps @~english Specify the jump tiles count.
     * @~chinese 指定跳跃次数。
     * @param amplitude @~english Specify the amplitude of the JumpTiles3D action.
     * @~chinese 指定JumpTiles3D动作的振幅。
     * @return @~english If the creation success, return a pointer of JumpTiles3D action; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个指向JumpTiles3D动作的指针;否则,返回空。
     */
    static JumpTiles3D* create(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese 获取振幅。
    @return @~english Return the amplitude of the effect.
     * @~chinese 振幅。
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese 设置振幅。
    @param amplitude @~english The value of amplitude will be set.
    * @~chinese 将被设置的幅。
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese 获得振幅率。
    @return @~english Return the amplitude rate of the effect.
     * @~chinese 振幅率。
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the amplitude rate of the effect.
     * @~chinese 设置是指振幅率。
    @param amplitudeRate @~english The value of amplitude rate will be set.
    * @~chinese  将被设置的振幅率。
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual JumpTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    JumpTiles3D() {}
    virtual ~JumpTiles3D() {}

    /** 
     * @brief @~english Initializes the action with the number of jumps, the sin amplitude, the grid size and the duration.
     * @~chinese 使用跳跃数,波振幅,网格大小和持续时间初始化动作。。
     * @param duration @~english Specify the duration of the JumpTiles3D action. It's a value in seconds.
     * @~chinese 指定JumpTiles3D动作的持续时间。这是一个以秒为单位的值。
     * @param gridSize @~english Specify the size of the grid.
     * @~chinese 指定网格的大小。
     * @param numberOfJumps @~english Specify the jump tiles count.
     * @~chinese 指定跳跃次数。
     * @param amplitude @~english Specify the amplitude of the JumpTiles3D action.
     * @~chinese 指定JumpTiles3D动作的振幅。
     * @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功,返回true,否则返回false。
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
@brief @~english SplitRows action.
 * @~chinese SplitRows动作。
@details @~english Split the target node in many rows.
        Then move out some rows from left, move out the other rows from right.
 * @~chinese 将目标节点分割为多行。
 * 然后从左边移出去一些行,从右边移出去另一些行。
*/
class CC_DLL SplitRows : public TiledGrid3DAction
{
public :
    /** 
     * @brief @~english Create the action with the number of rows and the duration.
     * @~chinese 使用指定行数和持续时间创建动作。
     * @param duration @~english Specify the duration of the SplitRows action. It's a value in seconds.
     * @~chinese 为SplitRows动作指定持续时间。这是一个以秒为单位的值。
     * @param rows @~english Specify the rows count should be splited.
     * @~chinese 指定应该分割的行数。
     * @return @~english If the creation success, return a pointer of SplitRows action; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个指向SplitRows动作指针;否则,返回空。
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
     * @brief @~english Initializes the action with the number rows and the duration.
     * @~chinese 使用指定行数和持续时间初始化动作。
     * @param duration @~english Specify the duration of the SplitRows action. It's a value in seconds.
     * @~chinese 为SplitRows动作指定持续时间。这是一个以秒为单位的值。
     * @param rows @~english Specify the rows count should be splited.
     * @~chinese 指定应该分割的行数。
     * @return @~english If the creation success, return true; otherwise, return false.
     * @~chinese 如果创建成功,返回true,否则返回false。
     */
    bool initWithDuration(float duration, unsigned int rows);

protected:
    unsigned int _rows;
    Size _winSize;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SplitRows);
};

/**
@brief @~english SplitCols action.
 * @~chinese SplitCols动作。
@details @~english Split the target node in many columns.
        Then move out some columns from top, move out the other columns from bottom.
 * @~chinese 将目标节点分割为多列。
 * 然后从上边移出去一些列,从下边移出去另一些列。
*/
class CC_DLL SplitCols : public TiledGrid3DAction
{
public:
    
    /** 
     * @brief @~english Create the action with the number of columns and the duration.
     * @~chinese 使用指定列数和持续时间创建动作。
     * @param duration @~english Specify the duration of the SplitCols action. It's a value in seconds.
     * @~chinese 指为SplitCols动作指定持续时间。这是一个以秒为单位的值。
     * @param cols @~english Specify the columns count should be splited.
     * @~chinese 指定应该分割的列数。
     * @return @~english If the creation success, return a pointer of SplitCols action; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个指向SplitCols动作的指针;否则,返回零。
     */
    static SplitCols* create(float duration, unsigned int cols);

    // Overrides
	virtual SplitCols* clone() const override;
    /**
     * @param time @~english in seconds
     * @~chinese 以秒为单位
     */
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitCols() {}
    virtual ~SplitCols() {}

    /** 
     * @brief @~english Initializes the action with the number columns and the duration.
     * @~chinese 使用指定列数和持续时间初始化动作。
     * @param duration @~english Specify the duration of the SplitCols action. It's a value in seconds.
     * @~chinese 为SplitCols动作指定持续时间。这是一个以秒为单位的值。
     * @param cols @~english Specify the columns count should be splited.
     * @~chinese 指定应该分割的列数。
     * @return @~english If the creation success, return true; otherwise, return false.
     * @~chinese 如果创建成功,返回true,否则返回false。
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
