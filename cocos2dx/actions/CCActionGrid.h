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
#ifndef __ACTION_CCGRID_ACTION_H__
#define __ACTION_CCGRID_ACTION_H__

#include "CCActionInterval.h"
#include "CCActionInstant.h"

NS_CC_BEGIN

class GridBase;

/**
 * @addtogroup actions
 * @{
 */

/** @brief Base class for Grid actions */
class CC_DLL GridAction : public ActionInterval
{
public:
    /** initializes the action with size and duration */
    bool initWithDuration(float duration, const Size& gridSize);

    /** returns the grid */
    virtual GridBase* getGrid();

    // overrides
	virtual GridAction * clone() const override = 0;
    virtual GridAction* reverse() const override;
    virtual void startWithTarget(Node *target) override;

protected:
    Size _gridSize;
};

/** 
 @brief Base class for Grid3D actions.
 Grid3D actions can modify a non-tiled grid.
 */
class CC_DLL Grid3DAction : public GridAction
{
public:

    /** returns the grid */
    virtual GridBase* getGrid(void);
    /** returns the vertex than belongs to certain position in the grid */
    Vertex3F getVertex(const Point& position) const;

    /** @deprecated Use getVertex() instead */
    CC_DEPRECATED_ATTRIBUTE inline Vertex3F vertex(const Point& position) { return getVertex(position); }

    /** returns the non-transformed vertex than belongs to certain position in the grid */
    Vertex3F getOriginalVertex(const Point& position) const;

    /** @deprecated Use getOriginalVertex() instead */
    CC_DEPRECATED_ATTRIBUTE inline Vertex3F originalVertex(const Point& position) { return getOriginalVertex(position); }

    /** sets a new vertex to a certain position of the grid */
    void setVertex(const Point& position, const Vertex3F& vertex);

    // Overrides
	virtual Grid3DAction * clone() const override = 0;
};

/** @brief Base class for TiledGrid3D actions */
class CC_DLL TiledGrid3DAction : public GridAction
{
public:
    /** creates the action with size and duration */
    static TiledGrid3DAction* create(float duration, const Size& gridSize);

    /** returns the tile that belongs to a certain position of the grid */
    Quad3 getTile(const Point& position) const;

    /** @deprecatd Use getTile() instead */
    CC_DEPRECATED_ATTRIBUTE Quad3 tile(const Point& position) { return getTile(position); }

    /** returns the non-transformed tile that belongs to a certain position of the grid */
    Quad3 getOriginalTile(const Point& position) const;

    /** @deprecatd Use getOriginalTile() instead */
    CC_DEPRECATED_ATTRIBUTE Quad3 originalTile(const Point& position) { return getOriginalTile(position); }

    /** sets a new tile to a certain position of the grid */
    void setTile(const Point& position, const Quad3& coords);

    /** returns the grid */
    virtual GridBase* getGrid(void);

    // Override
    virtual TiledGrid3DAction * clone() const override = 0;
};

/** @brief AccelDeccelAmplitude action */
class CC_DLL AccelDeccelAmplitude : public ActionInterval
{
public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static AccelDeccelAmplitude* create(Action *pAction, float duration);

    virtual ~AccelDeccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(Action *pAction, float duration);

	/** returns a new clone of the action */
	virtual AccelDeccelAmplitude* clone() const;
	/** returns a new reversed action */
	virtual AccelDeccelAmplitude* reverse() const;

    /** get amplitude rate */
    inline float getRate(void) const { return _rate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { _rate = fRate; }

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

protected:
    float _rate;
    ActionInterval *_other;
};

/** @brief AccelAmplitude action */
class CC_DLL AccelAmplitude : public ActionInterval
{
public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static AccelAmplitude* create(Action *pAction, float duration);

    virtual ~AccelAmplitude(void);

    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(Action *pAction, float duration);

    /** get amplitude rate */
    inline float getRate(void) const { return _rate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { _rate = fRate; }

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
	virtual AccelAmplitude* clone() const override;
	virtual AccelAmplitude* reverse() const override;

protected:
    float _rate;
    ActionInterval *_other;
};

/** @brief DeccelAmplitude action */
class CC_DLL DeccelAmplitude : public ActionInterval
{
public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static DeccelAmplitude* create(Action *pAction, float duration);

    virtual ~DeccelAmplitude();
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(Action *pAction, float duration);

    /** get amplitude rate */
    inline float getRate(void) const { return _rate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { _rate = fRate; }

    // overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
	virtual DeccelAmplitude* clone() const;
	virtual DeccelAmplitude* reverse() const;

protected:
    float _rate;
    ActionInterval *_other;
};

/** @brief StopGrid action.
 @warning Don't call this action if another grid action is active.
 Call if you want to remove the the grid effect. Example:
 Sequence::actions(Lens::action(...), StopGrid::action(...), NULL);
 */
class CC_DLL StopGrid : public ActionInstant
{
public:
    /** Allocates and initializes the action */
    static StopGrid* create(void);

    // Overrides
    virtual void startWithTarget(Node *target) override;
	virtual StopGrid* clone() const override;
	virtual StopGrid* reverse() const override;
};

/** @brief ReuseGrid action */
class CC_DLL ReuseGrid : public ActionInstant
{
public:
    /** creates an action with the number of times that the current grid will be reused */
    static ReuseGrid* create(int times);

    /** initializes an action with the number of times that the current grid will be reused */
    bool initWithTimes(int times);

    // Override
    virtual void startWithTarget(Node *target) override;
	virtual ReuseGrid* clone() const override;
	virtual ReuseGrid* reverse() const override;

protected:
    int _times;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID_ACTION_H__
