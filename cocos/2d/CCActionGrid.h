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

    /** returns the grid */
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
    /** initializes the action with size and duration */
    bool initWithDuration(float duration, const Size& gridSize);

protected:
    Size _gridSize;
    
    NodeGrid* _gridNodeTarget;
    
    void cacheTargetAsGridNode();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(GridAction);
};

/** 
 @brief Base class for Grid3D actions.
 Grid3D actions can modify a non-tiled grid.
 */
class CC_DLL Grid3DAction : public GridAction
{
public:

    /** returns the grid */
    virtual GridBase* getGrid();
    /** returns the vertex than belongs to certain position in the grid 
     * @js NA
     * @lua NA
     */
    Vec3 getVertex(const Vec2& position) const;

    /** @deprecated Use getVertex() instead 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE inline Vec3 vertex(const Vec2& position) { return getVertex(position); }

    /** returns the non-transformed vertex than belongs to certain position in the grid 
     * @js NA
     * @lua NA
     */
    Vec3 getOriginalVertex(const Vec2& position) const;

    /** @deprecated Use getOriginalVertex() instead 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE inline Vec3 originalVertex(const Vec2& position) { return getOriginalVertex(position); }

    /** sets a new vertex to a certain position of the grid 
     * @js NA
     * @lua NA
     */
    void setVertex(const Vec2& position, const Vec3& vertex);

    // Overrides
    virtual Grid3DAction * clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
};

/** @brief Base class for TiledGrid3D actions */
class CC_DLL TiledGrid3DAction : public GridAction
{
public:
    /** creates the action with size and duration 
     * @js NA
     * @lua NA
     */
    static TiledGrid3DAction* create(float duration, const Size& gridSize);

    /** returns the tile that belongs to a certain position of the grid 
     * @js NA
     * @lua NA
     */
    Quad3 getTile(const Vec2& position) const;

    /** @deprecated Use getTile() instead 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 tile(const Vec2& position) { return getTile(position); }

    /** returns the non-transformed tile that belongs to a certain position of the grid 
     * @js NA
     * @lua NA
     */
    Quad3 getOriginalTile(const Vec2& position) const;

    /** @deprecated Use getOriginalTile() instead 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 originalTile(const Vec2& position) { return getOriginalTile(position); }

    /** sets a new tile to a certain position of the grid 
     * @js NA
     * @lua NA
     */
    void setTile(const Vec2& position, const Quad3& coords);

    /** returns the grid */
    virtual GridBase* getGrid();

    // Override
    virtual TiledGrid3DAction * clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
};

/** @brief AccelDeccelAmplitude action */
class CC_DLL AccelDeccelAmplitude : public ActionInterval
{
public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static AccelDeccelAmplitude* create(Action *action, float duration);

    /** get amplitude rate */
    inline float getRate(void) const { return _rate; }
    /** set amplitude rate */
    inline void setRate(float rate) { _rate = rate; }

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    virtual AccelDeccelAmplitude* clone() const override;
    virtual AccelDeccelAmplitude* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    AccelDeccelAmplitude() {}
    virtual ~AccelDeccelAmplitude();
    
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(Action *action, float duration);

protected:
    float _rate;
    ActionInterval *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(AccelDeccelAmplitude);
};

/** @brief AccelAmplitude action */
class CC_DLL AccelAmplitude : public ActionInterval
{
public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static AccelAmplitude* create(Action *action, float duration);

    /** get amplitude rate */
    inline float getRate() const { return _rate; }
    /** set amplitude rate */
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

/** @brief DeccelAmplitude action */
class CC_DLL DeccelAmplitude : public ActionInterval
{
public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static DeccelAmplitude* create(Action *action, float duration);

    /** get amplitude rate */
    inline float getRate() const { return _rate; }
    /** set amplitude rate */
    inline void setRate(float rate) { _rate = rate; }

    // overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    virtual DeccelAmplitude* clone() const override;
    virtual DeccelAmplitude* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    DeccelAmplitude() {}
    virtual ~DeccelAmplitude();

    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(Action *action, float duration);

protected:
    float _rate;
    ActionInterval *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(DeccelAmplitude);
};

/** @brief StopGrid action.
 @warning Don't call this action if another grid action is active.
 Call if you want to remove the the grid effect. Example:
 Sequence::actions(Lens::action(...), StopGrid::action(...), nullptr);
 */
class CC_DLL StopGrid : public ActionInstant
{
public:
    /** Allocates and initializes the action */
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

/** @brief ReuseGrid action */
class CC_DLL ReuseGrid : public ActionInstant
{
public:
    /** creates an action with the number of times that the current grid will be reused */
    static ReuseGrid* create(int times);

    // Override
    virtual void startWithTarget(Node *target) override;
    virtual ReuseGrid* clone() const override;
    virtual ReuseGrid* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    ReuseGrid() {}
    virtual ~ReuseGrid() {}
    
    /** initializes an action with the number of times that the current grid will be reused */
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
