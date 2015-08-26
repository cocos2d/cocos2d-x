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
#ifndef __ACTION_CCGRID_ACTION_H__
#define __ACTION_CCGRID_ACTION_H__

#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"

NS_CC_BEGIN

class GridBase;
class NodeGrid;

/**
 * @addtogroup actions
 * @{
 */

/** 
@class GridAction
@brief @~english Base class for Grid actions.
 * @~chinese 网格动作的基类。
@details @~english Grid actions are the actions take effect on GridBase.
 * @~chinese 网格动作是基于网格（GridBase）特效的动作。
*/
class CC_DLL GridAction : public ActionInterval
{
public:

    /** 
    @brief @~english Get the pointer of GridBase.
     * @~chinese 获得网格对象（GridBase）的指针。
    @return @~english The pointer of GridBase.
     * @~chinese 网格对象（GridBase）的指针.
    */
    virtual GridBase* getGrid();

    // overrides
    virtual GridAction * clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
    virtual GridAction* reverse() const override;
    virtual void startWithTarget(Node *target) override;

CC_CONSTRUCTOR_ACCESS:
    GridAction() {}
    virtual ~GridAction() {}
    /** 
     * @brief @~english Initializes the action with size and duration.
     * @~chinese 通过网格大小和持续时间初始化动作。
     * @param duration @~english The duration of the GridAction. It's a value in seconds.
     * @~chinese 网格动作的持续时间，以秒为单位。
     * @param gridSize @~english The size of the GridAction should be.
     * @~chinese 网格的大小。
     * @return @~english Return true when the initialization success, otherwise return false.
     * @~chinese 当初始化成功时，返回true，否则返回false
     */
    bool initWithDuration(float duration, const Size& gridSize);

protected:
    Size _gridSize;
    
    NodeGrid* _gridNodeTarget;
    
    void cacheTargetAsGridNode();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(GridAction);
};

/** 
 @brief @~english Base class for Grid3D actions.
 * @~chinese 3D网格动作基类。
 @details @~english Grid3D actions can modify a non-tiled grid.
 * @~chinese 3D网格动作可以修改一个非瓦片网格。
 */
class CC_DLL Grid3DAction : public GridAction
{
public:


    virtual GridBase* getGrid() override;
    /**
     * @brief @~english Get the vertex that belongs to certain position in the grid.
     * @~chinese 获取网格中某个位置的顶点坐标。
     * @param position @~english The position of the grid.
     * @~chinese 网格的位置。
     * @return @~english Return a pointer of vertex.
     * @~chinese 返回一个顶点指针。
     * @js vertex
     * @lua NA
     */
    Vec3 getVertex(const Vec2& position) const;

    /** @deprecated Use getVertex() instead 
     * @see `getVertex`
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE inline Vec3 vertex(const Vec2& position) { return getVertex(position); }

    /** 
     * @brief @~english Get the non-transformed vertex that belongs to certain position in the grid.
     * @~chinese 得到网格中的某个位置的未变换顶点坐标。
     * @param position @~english The position of the grid.
     * @~chinese 网格的位置。
     * @return @~english Return a pointer of vertex.
     * @~chinese 返回一个顶点指针。
     * @js originalVertex
     * @lua NA
     */
    Vec3 getOriginalVertex(const Vec2& position) const;

    /** @deprecated Use getOriginalVertex() instead 
     * @see `getOriginalVertex`
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE inline Vec3 originalVertex(const Vec2& position) { return getOriginalVertex(position); }

    /** 
     * @brief @~english Set a new vertex to a certain position of the grid.
     * @~chinese 給指定的网格位置设置一个新的顶点坐标。
     * @param position @~english The position of the grid.
     * @~chinese 网格的位置。
     * @param vertex @~english The vertex will be used on the certain position of grid.
     * @~chinese 新的顶点坐标。
     * @js setVertex
     * @lua NA
     */
    void setVertex(const Vec2& position, const Vec3& vertex);

    // Overrides
    virtual Grid3DAction * clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
    
    /**
     * @brief Get the effect grid rect.
     * @return Return the effect grid rect.
     */
    Rect getGridRect() const;
};

/**
@brief @~english Base class for TiledGrid3D actions.
 * @~chinese 3D瓦片网格动作的基类。
*/
class CC_DLL TiledGrid3DAction : public GridAction
{
public:
    /** 
     * @brief @~english Create the action with size and duration.
     * @~chinese 用网格大小和持续时间创建一个动作。
     * @param duration @~english The duration of the action. It's a value in seconds.
     * @~chinese 动作的持续时间，以秒为单位。
     * @param gridSize @~english Specify the grid size of the action.
     * @~chinese 网格大小。
     * @return @~english A pointer of TiledGrid3DAction. If creation failed, return nil.
     * @~chinese 如果创建成功则返回TiledGrid3DAction的指针，如果创建失败，返回空指针。
     * @lua NA
     */
    static TiledGrid3DAction* create(float duration, const Size& gridSize);

    /** 
     * @brief @~english Get the tile that belongs to a certain position of the grid.
     * @~chinese 获取网格中特定位置的瓦片。
     * @param position @~english The position of the tile want to get.
     * @~chinese 网格中的一个位置。
     * @return @~english A quadrilateral of the tile. 
     * @~chinese 一个四边形瓦片。
     * @js tile
     * @lua NA
     */
    Quad3 getTile(const Vec2& position) const;

    /** @deprecated Use getTile() instead 
     * @see `getTile`
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 tile(const Vec2& position) { return getTile(position); }

    /** 
     * @brief @~english Get the non-transformed tile that belongs to a certain position of the grid.
     * @~chinese 得到网格中的某个位置的未变换瓦片。
     * @param position @~english The position of the tile want to get.
     * @~chinese 瓦想要的位置。
     * @return @~english A quadrilateral of the tile. 
     * @~chinese 一个四边形的瓦片。
     * @js originalTile
     * @lua NA
     */
    Quad3 getOriginalTile(const Vec2& position) const;

    /** @deprecated Use getOriginalTile() instead.
     * @see `getOriginalTile`
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 originalTile(const Vec2& position) { return getOriginalTile(position); }

    /** 
     * @brief @~english Set a new tile to a certain position of the grid.
     * @~chinese 給网格中指定位置设置一个新的瓦片。
     * @param position @~english The position of the tile.
     * @~chinese 瓦片的位置。
     * @param coords @~english The quadrilateral of the new tile.
     * @~chinese 新的四边形瓦片。
     * @lua NA
     */
    void setTile(const Vec2& position, const Quad3& coords);

    /** @~english returns the grid  @~chinese 返回网格对象 */
    virtual GridBase* getGrid() override;

    // Override
    virtual TiledGrid3DAction * clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
};

/**
@brief @~english AccelDeccelAmplitude action.
 * @~chinese AccelDeccelAmplitude动作。
@js NA
*/
class CC_DLL AccelDeccelAmplitude : public ActionInterval
{
public:
    /**
    @brief @~english Create the action with an inner action that has the amplitude property, and a duration time.
     * @~chinese 用一个包含振幅（amplitude）属性的动作和持续时间创建AccelDeccelAmplitude动作。
    @param action @~english A pointer of the inner action.
     * @~chinese 内部动作的指针。
    @param duration @~english Specify the duration of the AccelDeccelAmplitude action.
     * @~chinese AccelDeccelAmplitude动作的持续时间。
    @return @~english Return a pointer of AccelDeccelAmplitude action. When the creation failed, return nil.
     * @~chinese 返回一个AccelDeccelAmplitude动作指针，如果创建失败，返回空指针。
    */
    static AccelDeccelAmplitude* create(Action *action, float duration);

    /** 
    @brief @~english Get the value of amplitude rate.
     * @~chinese 获取振幅值。
    @return @~english the value of amplitude rate.
     * @~chinese 振幅值。
    */
    inline float getRate(void) const { return _rate; }
    /**
    @brief @~english Set the value of amplitude rate.
     * @~chinese 设置振幅。
    @param rate @~english Specify the value of amplitude rate.
     * @~chinese 振幅。
     */
    inline void setRate(float rate) { _rate = rate; }

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    virtual AccelDeccelAmplitude* clone() const override;
    virtual AccelDeccelAmplitude* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    AccelDeccelAmplitude() {}
    virtual ~AccelDeccelAmplitude();
    
    /** 
    @brief @~english Initializes the action with an inner action that has the amplitude property, and a duration time.
     * @~chinese 用一个包含振幅（amplitude）属性的动作和持续时间初始化AccelDeccelAmplitude动作。
    @param action @~english A pointer of the inner action.
     * @~chinese 内部动作的指针。
    @param duration @~english Specify the duration of the AccelDeccelAmplitude action.
     * @~chinese AccelDeccelAmplitude动作的持续时间。
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    bool initWithAction(Action *action, float duration);

protected:
    float _rate;
    ActionInterval *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(AccelDeccelAmplitude);
};

/**
@brief @~english AccelAmplitude action.
 * @~chinese AccelAmplitude行动。
@js NA
*/
class CC_DLL AccelAmplitude : public ActionInterval
{
public:
    /** 
    @brief @~english Create the action with an inner action that has the amplitude property, and a duration time.
     * @~chinese 用一个包含振幅（amplitude）属性的动作和持续时间创建AccelAmplitude动作。
    @param action @~english A pointer of the inner action.
     * @~chinese 内部动作的指针。
    @param duration @~english Specify the duration of the AccelAmplitude action.
     * @~chinese 指定的持续时间。
    @return @~english Return a pointer of AccelAmplitude action. When the creation failed, return nil.
     * @~chinese 返回一个指针AccelAmplitude行动。当创建失败，返回空指针。
     */
    static AccelAmplitude* create(Action *action, float duration);

    /** 
    @brief @~english Get the value of amplitude rate.
     * @~chinese 获取振幅值。
    @return @~english The value of amplitude rate.
     * @~chinese 振幅值。
    */
    inline float getRate() const { return _rate; }
    /**
    @brief @~english Set the value of amplitude rate.
     * @~chinese 设置振幅值。
    @param rate @~english Specify the value of amplitude rate.
     * @~chinese 振幅。
    */
    inline void setRate(float rate) { _rate = rate; }

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    virtual AccelAmplitude* clone() const override;
    virtual AccelAmplitude* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    AccelAmplitude() {}
    virtual ~AccelAmplitude();

    bool initWithAction(Action *action, float duration);

protected:
    float _rate;
    ActionInterval *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(AccelAmplitude);
};

/**
@brief @~english DeccelAmplitude action.
 * @~chinese DeccelAmplitude动作。
@js NA
*/
class CC_DLL DeccelAmplitude : public ActionInterval
{
public:
    /** 
    @brief @~english Creates the action with an inner action that has the amplitude property, and a duration time.
     * @~chinese 用一个包含振幅（amplitude）属性的动作和持续时间创建DeccelAmplitude动作。
    @param action @~english A pointer of the inner action.
     * @~chinese 内部动作的指针。
    @param duration @~english Specify the duration of the DeccelAmplitude action.
     * @~chinese 指定的持续时间。
    @return @~english Return a pointer of DeccelAmplitude. When the creation failed, return nil.
     * @~chinese 返回一个DeccelAmplitude指针。当创建失败，返回空指针。
    */
    static DeccelAmplitude* create(Action *action, float duration);

    /** 
    @brief @~english Get the value of amplitude rate.
     * @~chinese 获得振幅值。
    @return @~english The value of amplitude rate.
     * @~chinese 振幅。
    */
    inline float getRate() const { return _rate; }
    /**
    @brief @~english Set the value of amplitude rate.
     * @~chinese 设置振幅值。
    @param rate @~english Specify the value.
     * @~chinese 振幅。
    */
    inline void setRate(float rate) { _rate = rate; }

    // overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    virtual DeccelAmplitude* clone() const override;
    virtual DeccelAmplitude* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    DeccelAmplitude() {}
    virtual ~DeccelAmplitude();

    /** 
    @brief @~english Initializes the action with an inner action that has the amplitude property, and a duration time.
     * @~chinese 用一个包含振幅（amplitude）属性的动作和持续时间初始化动作。
    @param action @~english The pointer of inner action.
     * @~chinese 内部动作指针。
    @param duration @~english The duration of the DeccelAmplitude action.
     * @~chinese 持续时间。
    @return @~english If the initilization sucess, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    bool initWithAction(Action *action, float duration);

protected:
    float _rate;
    ActionInterval *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(DeccelAmplitude);
};

/**
 @brief @~english StopGrid action.
 * @~chinese StopGrid动作。
 @warning @~english It can stop a running grid action. Example:
 * @~chinese 可以用来停止正在执行的网格动作。例子:
 * @code
 * Sequence::actions(Lens::action(...), StopGrid::action(...), nullptr);
 * @endcode
 */
class CC_DLL StopGrid : public ActionInstant
{
public:
    /** 
    @brief @~english Create a StopGrid Action.
     * @~chinese 创建一个StopGrid动作。
    @return @~english Return a pointer of StopGrid. When the creation failed, return nil.
     * @~chinese 返回一个StopGrid动作指针。当创建失败，返回空指针。
    */
    static StopGrid* create();

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual StopGrid* clone() const override;
    virtual StopGrid* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    StopGrid() {}
    virtual ~StopGrid() {}
    
protected:
    NodeGrid* _gridNodeTarget;
    
    void cacheTargetAsGridNode();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(StopGrid);
};

/** 
@brief @~english ReuseGrid action.
 * @~chinese ReuseGrid行动。
*/
class CC_DLL ReuseGrid : public ActionInstant
{
public:
    /** 
    @brief @~english Create an action with the number of times that the current grid will be reused.
     * @~chinese 用当前网格将被重用的次数来创建一个复用网格动作。
    @param times @~english Specify times the grid will be reused.
     * @~chinese 当前网格将被重用的次数。
    @return @~english Return a pointer of ReuseGrid. When the creation failed, return nil.
     * @~chinese 返回一个ReuseGrid指针。当创建失败，返回空指针。
    */
    static ReuseGrid* create(int times);

    // Override
    virtual void startWithTarget(Node *target) override;
    virtual ReuseGrid* clone() const override;
    virtual ReuseGrid* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    ReuseGrid() {}
    virtual ~ReuseGrid() {}
    
    /** 
    @brief @~english Initializes an action with the number of times that the current grid will be reused.
     * @~chinese 用当前网格将被重用的次数来初始化动作。
    @param times @~english Specify times the grid will be reused.
     * @~chinese 当前网格将被重用的次数。
    @return @~english If the initialization sucess, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    bool initWithTimes(int times);

protected:
    NodeGrid* _gridNodeTarget;
    
    void cacheTargetAsGridNode();
    
    int _times;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ReuseGrid);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID_ACTION_H__
