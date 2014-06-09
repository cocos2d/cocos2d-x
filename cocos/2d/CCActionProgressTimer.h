/****************************************************************************
Copyright (C) 2010      Lam Pham
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
#ifndef __ACTION_CCPROGRESS_TIMER_H__
#define __ACTION_CCPROGRESS_TIMER_H__

#include "2d/CCActionInterval.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/**
@brief Progress to percentage
@since v0.99.1
*/
class CC_DLL ProgressTo : public ActionInterval
{
public:
    /** Creates and initializes with a duration and a percent */
    static ProgressTo* create(float duration, float percent);

    //
    // Overrides
    //
	virtual ProgressTo* clone() const override;
	virtual ProgressTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ProgressTo() {}
    virtual ~ProgressTo() {}

    /** Initializes with a duration and a percent */
    bool initWithDuration(float duration, float percent);

protected:
    float _to;
    float _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressTo);
};

/**
@brief Progress from a percentage to another percentage
@since v0.99.1
*/
class CC_DLL ProgressFromTo : public ActionInterval
{
public:
    /** Creates and initializes the action with a duration, a "from" percentage and a "to" percentage */
    static ProgressFromTo* create(float duration, float fromPercentage, float toPercentage);

    //
    // Overrides
    //
	virtual ProgressFromTo* clone() const override;
	virtual ProgressFromTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ProgressFromTo() {}
    virtual ~ProgressFromTo() {}

    /** Initializes the action with a duration, a "from" percentage and a "to" percentage */
    bool initWithDuration(float duration, float fromPercentage, float toPercentage);

protected:
    float _to;
    float _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressFromTo);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCPROGRESS_TIMER_H__
