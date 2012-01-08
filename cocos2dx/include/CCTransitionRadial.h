/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009      Lam Pham

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

#ifndef __CCRADIAL_TRANSITION_H__
#define __CCRADIAL_TRANSITION_H__
#include "CCTransition.h"
#include "CCProgressTimer.h"

namespace   cocos2d {

/**
 @brief A counter colock-wise radial transition to the next scene
 */
class CC_DLL CCTransitionRadialCCW : public CCTransitionScene
{
public:
	CCTransitionRadialCCW(){}
	virtual ~CCTransitionRadialCCW(){}

	virtual void onEnter();
	virtual void onExit();

    static CCTransitionRadialCCW* transitionWithDuration(ccTime t, CCScene* scene);

protected:
	virtual void sceneOrder();
	virtual CCProgressTimerType radialType();
};

/**
 @brief A counter colock-wise radial transition to the next scene
 */
class CC_DLL CCTransitionRadialCW : public CCTransitionRadialCCW
{
public:
	CCTransitionRadialCW(){}
	virtual ~CCTransitionRadialCW(){}
    static CCTransitionRadialCW* transitionWithDuration(ccTime t, CCScene* scene);

protected:
	virtual CCProgressTimerType radialType();
};

}//namespace   cocos2d 

#endif //__CCRADIAL_TRANSITION_H__

