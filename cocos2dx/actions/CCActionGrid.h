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
	/** returns a new clone of the action */
	virtual GridAction * clone() const = 0;

	/** returns a new reversed action.
	 The reversed action is created with the ReverseTime action.
	 */
    virtual GridAction* reverse() const;

    virtual void startWithTarget(Node *pTarget);

    /** initializes the action with size and duration */
    virtual bool initWithDuration(float duration, const Size& gridSize);

    /** returns the grid */
    virtual GridBase* getGrid(void);

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
	/** returns a new clone of the action */
	virtual Grid3DAction * clone() const = 0;

    /** returns the grid */
    virtual GridBase* getGrid(void);
    /** returns the vertex than belongs to certain position in the grid */
    ccVertex3F vertex(const Point& position);
    /** returns the non-transformed vertex than belongs to certain position in the grid */
    ccVertex3F originalVertex(const Point& position);
    /** sets a new vertex to a certain position of the grid */
    void setVertex(const Point& position, const ccVertex3F& vertex);
};

/** @brief Base class for TiledGrid3D actions */
class CC_DLL TiledGrid3DAction : public GridAction
{
public:
	/** returns a new clone of the action */
	virtual TiledGrid3DAction * clone() const = 0;

    /** returns the tile that belongs to a certain position of the grid */
    ccQuad3 tile(const Point& position);
    /** returns the non-transformed tile that belongs to a certain position of the grid */
    ccQuad3 originalTile(const Point& position);
    /** sets a new tile to a certain position of the grid */
    void setTile(const Point& position, const ccQuad3& coords);

    /** returns the grid */
    virtual GridBase* getGrid(void);

public:
    /** creates the action with size and duration */
    static TiledGrid3DAction* create(float duration, const Size& gridSize);
};

/** @brief AccelDeccelAmplitude action */
class CC_DLL AccelDeccelAmplitude : public ActionInterval
{
public:
    virtual ~AccelDeccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(Action *pAction, float duration);

	/** returns a new clone of the action */
	virtual AccelDeccelAmplitude* clone() const;
	/** returns a new reversed action */
	virtual AccelDeccelAmplitude* reverse() const;

    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

    /** get amplitude rate */
    inline float getRate(void) { return _rate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { _rate = fRate; }

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static AccelDeccelAmplitude* create(Action *pAction, float duration);

protected:
    float _rate;
    ActionInterval *_other;
};

/** @brief AccelAmplitude action */
class CC_DLL AccelAmplitude : public ActionInterval
{
public:
    ~AccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(Action *pAction, float duration);

	/** returns a new clone of the action */
	virtual AccelAmplitude* clone() const;

	/** returns a new reversed action */
	virtual AccelAmplitude* reverse() const;

    /** get amplitude rate */
    inline float getRate(void) { return _rate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { _rate = fRate; }

    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static AccelAmplitude* create(Action *pAction, float duration);
protected:
    float _rate;
    ActionInterval *_other;
};

/** @brief DeccelAmplitude action */
class CC_DLL DeccelAmplitude : public ActionInterval
{
public:
    ~DeccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(Action *pAction, float duration);

	/** returns a new clone of the action */
	virtual DeccelAmplitude* clone() const;

	/** returns a new reversed action */
	virtual DeccelAmplitude* reverse() const;

    /** get amplitude rate */
    inline float getRate(void) { return _rate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { _rate = fRate; }

    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static DeccelAmplitude* create(Action *pAction, float duration);

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
    virtual void startWithTarget(Node *pTarget);

	/** returns a new clone of the action */
	virtual StopGrid* clone() const;

	/** returns a new reversed action */
	virtual StopGrid* reverse() const;

public:
    /** Allocates and initializes the action */
    static StopGrid* create(void);
};

/** @brief ReuseGrid action */
class CC_DLL ReuseGrid : public ActionInstant
{
public:
    /** initializes an action with the number of times that the current grid will be reused */
    bool initWithTimes(int times);

    virtual void startWithTarget(Node *pTarget);

	/** returns a new clone of the action */
	virtual ReuseGrid* clone() const;

	/** returns a new reversed action */
	virtual ReuseGrid* reverse() const;

public:
    /** creates an action with the number of times that the current grid will be reused */
    static ReuseGrid* create(int times);
protected:
    int _times;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID_ACTION_H__
