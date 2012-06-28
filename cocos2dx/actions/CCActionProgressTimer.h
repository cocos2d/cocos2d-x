/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (C) 2010      Lam Pham

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
#ifndef __ACTION_CCPROGRESS_TIMER_H__
#define __ACTION_CCPROGRESS_TIMER_H__

#include "CCActionInterval.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/**
@brief Progress to percentage
@since v0.99.1
*/
class CC_DLL CCProgressTo : public CCActionInterval
{
public:
    /** Initializes with a duration and a percent */
    bool initWithDuration(float duration, float fPercent);

    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** Creates and initializes with a duration and a percent 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCProgressTo* actionWithDuration(float duration, float fPercent);
    /** Creates and initializes with a duration and a percent */
    static CCProgressTo* create(float duration, float fPercent);
protected:
    float m_fTo;
    float m_fFrom;
};

/**
@brief Progress from a percentage to another percentage
@since v0.99.1
*/
class CC_DLL CCProgressFromTo : public CCActionInterval
{
public:
    /** Initializes the action with a duration, a "from" percentage and a "to" percentage */
    bool initWithDuration(float duration, float fFromPercentage, float fToPercentage);

    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual CCActionInterval* reverse(void);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);

public:
    /** Creates and initializes the action with a duration, a "from" percentage and a "to" percentage 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCProgressFromTo* actionWithDuration(float duration, float fFromPercentage, float fToPercentage);
    /** Creates and initializes the action with a duration, a "from" percentage and a "to" percentage */
    static CCProgressFromTo* create(float duration, float fFromPercentage, float fToPercentage);
protected:
    float m_fTo;
    float m_fFrom;
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCPROGRESS_TIMER_H__
