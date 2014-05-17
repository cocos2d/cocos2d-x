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

/** @brief Base class for Grid actions */
class CC_DLL GridAction : public ActionInterval
{
public:

    /** 返回网格 */
    virtual GridBase* getGrid();

    // overrides
	virtual GridAction * clone() const override = 0;
    virtual GridAction* reverse() const override;
    virtual void startWithTarget(Node *target) override;

protected:
    GridAction() {}
    virtual ~GridAction() {}
    /** 用大小和持续时间初始化动作 */
    bool initWithDuration(float duration, const Size& gridSize);

    Size _gridSize;
    
    NodeGrid* _gridNodeTarget;
    
    void cacheTargetAsGridNode();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(GridAction);
};

/** 
 @brief 
 3D网格动作的基类
 3D网格动作可以修改一个非平铺的网格 */
class CC_DLL Grid3DAction : public GridAction
{
public:

    /** 返回网格 */
    virtual GridBase* getGrid();
    /** 返回网格中属于某个位置的顶点
     * @js NA
     * @lua NA
     */
    Vec3 getVertex(const Vec2& position) const;

    /** @deprecated 适应getVertex()代替
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE inline Vec3 vertex(const Vec2& position) { return getVertex(position); }

    /** 返回网格中属于某个位置的原始顶点（未经过变换）
     * @js NA
     * @lua NA
     */
    Vec3 getOriginalVertex(const Vec2& position) const;

    /** @deprecated 使用getOriginalVertex()代替
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE inline Vec3 originalVertex(const Vec2& position) { return getOriginalVertex(position); }

    /** 设置一个新的顶点到网格中的一定位置
     * @js NA
     * @lua NA
     */
    void setVertex(const Vec2& position, const Vec3& vertex);

    // Overrides
	virtual Grid3DAction * clone() const override = 0;
};

/** @brief 平铺的3Dgrid动作的基类 */
class CC_DLL TiledGrid3DAction : public GridAction
{
public:
    /** 用大小和持续时间来创建动作
     * @js NA
     * @lua NA
     */
    static TiledGrid3DAction* create(float duration, const Size& gridSize);

    /** 返回网格中某个位置的格子
     * @js NA
     * @lua NA
     */
    Quad3 getTile(const Vec2& position) const;

    /** @deprecated 使用getTile() 代替
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 tile(const Vec2& position) { return getTile(position); }

    /**  返回网格中某个位置的原始格子（未经过变换）
     * @js NA
     * @lua NA
     */
    Quad3 getOriginalTile(const Vec2& position) const;

    /** @deprecated 视同getOriginalTile()代替
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 originalTile(const Vec2& position) { return getOriginalTile(position); }

    /**  设置网格中某个位置的格子
     * @js NA
     * @lua NA
     */
    void setTile(const Vec2& position, const Quad3& coords);

    /** 返回网格 */
    virtual GridBase* getGrid();

    // Override
    virtual TiledGrid3DAction * clone() const override = 0;
};

/** @brief AccelDeccelAmplitude 动作 */
class CC_DLL AccelDeccelAmplitude : public ActionInterval
{
public:
    /** 使用一个包含振幅属性的内部动作和持续时间创建动作 */
    static AccelDeccelAmplitude* create(Action *action, float duration);

    /** 获取振幅率 */
    inline float getRate(void) const { return _rate; }
    /** 设置振幅率 */
    inline void setRate(float fRate) { _rate = fRate; }

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
	virtual AccelDeccelAmplitude* clone() const override;
	virtual AccelDeccelAmplitude* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    AccelDeccelAmplitude() {}
    virtual ~AccelDeccelAmplitude();
    
    /** 用一个包含振幅属性的内部动作和持续时间来初始化该动作 */
    bool initWithAction(Action *pAction, float duration);

protected:
    float _rate;
    ActionInterval *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(AccelDeccelAmplitude);
};

/** @brief AccelAmplitude 动作 */
class CC_DLL AccelAmplitude : public ActionInterval
{
public:
    /** 用一个包含振幅属性的内部动作和持续时间创建动作 */
    static AccelAmplitude* create(Action *action, float duration);

    /** 获取振幅率 */
    inline float getRate() const { return _rate; }
    /** 设置振幅率 */
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

/** @brief DeccelAmplitude 动作 */
class CC_DLL DeccelAmplitude : public ActionInterval
{
public:
    /** 用一个包含振幅属性的内部动作和持续时间来创建动作 */
    static DeccelAmplitude* create(Action *action, float duration);

    /** 获取振幅率 */
    inline float getRate(void) const { return _rate; }
    /** 设置振幅率 */
    inline void setRate(float rate) { _rate = rate; }

    // overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
	virtual DeccelAmplitude* clone() const override;
	virtual DeccelAmplitude* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    DeccelAmplitude() {}
    virtual ~DeccelAmplitude();

    /** 用一个包含振幅属性的内部动作和持续时间初始化该动作 */
    bool initWithAction(Action *action, float duration);

protected:
    float _rate;
    ActionInterval *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(DeccelAmplitude);
};

/** @brief StopGrid action.
 @warning 如果另一个网格动作激活了，不要调用这个动作。
 如果你想要移除网格特效，则调用。如： Sequence::actions(Lens::action(...), StopGrid::action(...), nullptr);
 */
class CC_DLL StopGrid : public ActionInstant
{
public:
    /** 分配空间和初始化动作 */
    static StopGrid* create();

    // Overrides
    virtual void startWithTarget(Node *target) override;
	virtual StopGrid* clone() const override;
	virtual StopGrid* reverse() const override;

protected:
    StopGrid() {}
    virtual ~StopGrid() {}
    
    NodeGrid* _gridNodeTarget;
    
    void cacheTargetAsGridNode();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(StopGrid);
};

/** @brief ReuseGrid 动作 */
class CC_DLL ReuseGrid : public ActionInstant
{
public:
    /** 用当前网格将被使用的次数来创建一个动作 */
    static ReuseGrid* create(int times);

    // Override
    virtual void startWithTarget(Node *target) override;
	virtual ReuseGrid* clone() const override;
	virtual ReuseGrid* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    ReuseGrid() {}
    virtual ~ReuseGrid() {}
    
    /** 用当前网格将被使用的次数创建一个动作 */
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
