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

class CCGridBase;

/**
 * @addtogroup actions
 * @{
 */

/** @brief Base class for Grid actions */
class CC_DLL CCGridAction : public CCActionInterval
{
public:
	/** returns a new clone of the action */
	virtual CCGridAction * clone() const = 0;

	/** returns a new reversed action.
	 The reversed action is created with the CCReverseTime action.
	 */
    virtual CCGridAction* reverse() const;

    virtual void startWithTarget(CCNode *pTarget);

    /** initializes the action with size and duration */
    virtual bool initWithDuration(float duration, const CCSize& gridSize);

    /** returns the grid */
    virtual CCGridBase* getGrid(void);

protected:
    CCSize _gridSize;
};

/** 
 @brief Base class for CCGrid3D actions.
 Grid3D actions can modify a non-tiled grid.
 */
class CC_DLL CCGrid3DAction : public CCGridAction
{
public:
	/** returns a new clone of the action */
	virtual CCGrid3DAction * clone() const = 0;

    /** returns the grid */
    virtual CCGridBase* getGrid(void);
    /** returns the vertex than belongs to certain position in the grid */
    ccVertex3F vertex(const CCPoint& position);
    /** returns the non-transformed vertex than belongs to certain position in the grid */
    ccVertex3F originalVertex(const CCPoint& position);
    /** sets a new vertex to a certain position of the grid */
    void setVertex(const CCPoint& position, const ccVertex3F& vertex);
};

/** @brief Base class for CCTiledGrid3D actions */
class CC_DLL CCTiledGrid3DAction : public CCGridAction
{
public:
	/** returns a new clone of the action */
	virtual CCTiledGrid3DAction * clone() const = 0;

    /** returns the tile that belongs to a certain position of the grid */
    ccQuad3 tile(const CCPoint& position);
    /** returns the non-transformed tile that belongs to a certain position of the grid */
    ccQuad3 originalTile(const CCPoint& position);
    /** sets a new tile to a certain position of the grid */
    void setTile(const CCPoint& position, const ccQuad3& coords);

    /** returns the grid */
    virtual CCGridBase* getGrid(void);

public:
    /** creates the action with size and duration */
    static CCTiledGrid3DAction* create(float duration, const CCSize& gridSize);
};

/** @brief CCAccelDeccelAmplitude action */
class CC_DLL CCAccelDeccelAmplitude : public CCActionInterval
{
public:
    virtual ~CCAccelDeccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(CCAction *pAction, float duration);

	/** returns a new clone of the action */
	virtual CCAccelDeccelAmplitude* clone() const;
	/** returns a new reversed action */
	virtual CCAccelDeccelAmplitude* reverse() const;

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

    /** get amplitude rate */
    inline float getRate(void) { return _rate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { _rate = fRate; }

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static CCAccelDeccelAmplitude* create(CCAction *pAction, float duration);

protected:
    float _rate;
    CCActionInterval *_other;
};

/** @brief CCAccelAmplitude action */
class CC_DLL CCAccelAmplitude : public CCActionInterval
{
public:
    ~CCAccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(CCAction *pAction, float duration);

	/** returns a new clone of the action */
	virtual CCAccelAmplitude* clone() const;

	/** returns a new reversed action */
	virtual CCAccelAmplitude* reverse() const;

    /** get amplitude rate */
    inline float getRate(void) { return _rate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { _rate = fRate; }

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static CCAccelAmplitude* create(CCAction *pAction, float duration);
protected:
    float _rate;
    CCActionInterval *_other;
};

/** @brief CCDeccelAmplitude action */
class CC_DLL CCDeccelAmplitude : public CCActionInterval
{
public:
    ~CCDeccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(CCAction *pAction, float duration);

	/** returns a new clone of the action */
	virtual CCDeccelAmplitude* clone() const;

	/** returns a new reversed action */
	virtual CCDeccelAmplitude* reverse() const;

    /** get amplitude rate */
    inline float getRate(void) { return _rate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { _rate = fRate; }

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static CCDeccelAmplitude* create(CCAction *pAction, float duration);

protected:
    float _rate;
    CCActionInterval *_other;
};

/** @brief CCStopGrid action.
 @warning Don't call this action if another grid action is active.
 Call if you want to remove the the grid effect. Example:
 CCSequence::actions(Lens::action(...), CCStopGrid::action(...), NULL);
 */
class CC_DLL CCStopGrid : public CCActionInstant
{
public:
    virtual void startWithTarget(CCNode *pTarget);

	/** returns a new clone of the action */
	virtual CCStopGrid* clone() const;

	/** returns a new reversed action */
	virtual CCStopGrid* reverse() const;

public:
    /** Allocates and initializes the action */
    static CCStopGrid* create(void);
};

/** @brief CCReuseGrid action */
class CC_DLL CCReuseGrid : public CCActionInstant
{
public:
    /** initializes an action with the number of times that the current grid will be reused */
    bool initWithTimes(int times);

    virtual void startWithTarget(CCNode *pTarget);

	/** returns a new clone of the action */
	virtual CCReuseGrid* clone() const;

	/** returns a new reversed action */
	virtual CCReuseGrid* reverse() const;

public:
    /** creates an action with the number of times that the current grid will be reused */
    static CCReuseGrid* create(int times);
protected:
    int _times;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID_ACTION_H__
