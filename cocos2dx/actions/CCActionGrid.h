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
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);

    /** initializes the action with size and duration */
    virtual bool initWithSize(const ccGridSize& gridSize, float duration);
    /** returns the grid */
    virtual CCGridBase* getGrid(void);

public:
    /** creates the action with size and duration 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCGridAction* actionWithSize(const ccGridSize& gridSize, float duration);
    /** creates the action with size and duration */
    static CCGridAction* create(const ccGridSize& gridSize, float duration);
protected:
    ccGridSize m_sGridSize;
};

/** 
 @brief Base class for CCGrid3D actions.
 Grid3D actions can modify a non-tiled grid.
 */
class CC_DLL CCGrid3DAction : public CCGridAction
{
public:
    /** returns the grid */
    virtual CCGridBase* getGrid(void);
    /** returns the vertex than belongs to certain position in the grid */
    ccVertex3F vertex(const ccGridSize& pos);
    /** returns the non-transformed vertex than belongs to certain position in the grid */
    ccVertex3F originalVertex(const ccGridSize& pos);
    /** sets a new vertex to a certain position of the grid */
    void setVertex(const ccGridSize& pos, const ccVertex3F& vertex);

public:
    /** creates the action with size and duration 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCGrid3DAction* actionWithSize(const ccGridSize& gridSize, float duration);
    /** creates the action with size and duration */
    static CCGrid3DAction* create(const ccGridSize& gridSize, float duration);
};

/** @brief Base class for CCTiledGrid3D actions */
class CC_DLL CCTiledGrid3DAction : public CCGridAction
{
public:
    /** returns the tile that belongs to a certain position of the grid */
    ccQuad3 tile(const ccGridSize& pos);
    /** returns the non-transformed tile that belongs to a certain position of the grid */
    ccQuad3 originalTile(const ccGridSize& pos);
    /** sets a new tile to a certain position of the grid */
    void setTile(const ccGridSize& pos, const ccQuad3& coords);

    /** returns the grid */
    virtual CCGridBase* getGrid(void);

public:
    /** creates the action with size and duration 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCTiledGrid3DAction* actionWithSize(const ccGridSize& gridSize, float duration);
    /** creates the action with size and duration */
    static CCTiledGrid3DAction* create(const ccGridSize& gridSize, float duration);
};

/** @brief CCAccelDeccelAmplitude action */
class CC_DLL CCAccelDeccelAmplitude : public CCActionInterval
{
public:
    virtual ~CCAccelDeccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(CCAction *pAction, float duration);

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

    /** get amplitude rate */
    inline float getRate(void) { return m_fRate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { m_fRate = fRate; }

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCAccelDeccelAmplitude* actionWithAction(CCAction *pAction, float duration);
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static CCAccelDeccelAmplitude* create(CCAction *pAction, float duration);

protected:
    float m_fRate;
    CCActionInterval *m_pOther;
};

/** @brief CCAccelAmplitude action */
class CC_DLL CCAccelAmplitude : public CCActionInterval
{
public:
    ~CCAccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(CCAction *pAction, float duration);

    /** get amplitude rate */
    inline float getRate(void) { return m_fRate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { m_fRate = fRate; }

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCAccelAmplitude* actionWithAction(CCAction *pAction, float duration);
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static CCAccelAmplitude* create(CCAction *pAction, float duration);
protected:
    float m_fRate;
    CCActionInterval *m_pOther;
};

/** @brief CCDeccelAmplitude action */
class CC_DLL CCDeccelAmplitude : public CCActionInterval
{
public:
    ~CCDeccelAmplitude(void);
    /** initializes the action with an inner action that has the amplitude property, and a duration time */
    bool initWithAction(CCAction *pAction, float duration);

    /** get amplitude rate */
    inline float getRate(void) { return m_fRate; }
    /** set amplitude rate */
    inline void setRate(float fRate) { m_fRate = fRate; }

    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);

public:
    /** creates the action with an inner action that has the amplitude property, and a duration time 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCDeccelAmplitude* actionWithAction(CCAction *pAction, float duration);
    /** creates the action with an inner action that has the amplitude property, and a duration time */
    static CCDeccelAmplitude* create(CCAction *pAction, float duration);

protected:
    float m_fRate;
    CCActionInterval *m_pOther;
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

public:
    /** Allocates and initializes the action 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCStopGrid* action(void);
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

public:
    /** creates an action with the number of times that the current grid will be reused 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCReuseGrid* actionWithTimes(int times);
    /** creates an action with the number of times that the current grid will be reused */
    static CCReuseGrid* create(int times);
protected:
    int m_nTimes;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID_ACTION_H__
