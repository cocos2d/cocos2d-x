/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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


typedef enum {
	/// Radial Counter-Clockwise 
	kCCProgressTimerTypeRadialCCW,
	/// Radial ClockWise
	kCCProgressTimerTypeRadialCW,
	/// Horizontal Left-Right
	kCCProgressTimerTypeHorizontalBarLR,
	/// Horizontal Right-Left
	kCCProgressTimerTypeHorizontalBarRL,
	/// Vertical Bottom-top
	kCCProgressTimerTypeVerticalBarBT,
	/// Vertical Top-Bottom
	kCCProgressTimerTypeVerticalBarTB,
} CCProgressTimerType;/// @todo to be deleted

#include "CCTransition.h"

///@todo #include "CCProgressTimer.h"
///@todo #include "CCProgressTimerActions.h"

///
//	A counter colock-wise radial transition to the next scene
///
class CCRadialCCWTransition : public CCTransitionScene
{
public:
	CCRadialCCWTransition();
	virtual ~CCRadialCCWTransition();

	virtual void onEnter();
	virtual void onExit();

protected:
	virtual void sceneOrder();
	virtual CCProgressTimerType radialType();
};

///
//	A counter colock-wise radial transition to the next scene
///
class CCRadialCWTransition : public CCRadialCCWTransition
{
public:
	CCRadialCWTransition();
	virtual ~CCRadialCWTransition();
protected:
	virtual CCProgressTimerType radialType();
};


#endif __CCRADIAL_TRANSITION_H__

