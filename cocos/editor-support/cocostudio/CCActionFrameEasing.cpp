/****************************************************************************
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

#include <math.h>
#include "cocostudio/CCActionFrameEasing.h"
#include "cocostudio/DictionaryHelper.h"
namespace cocostudio {

#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif

ActionFrameEasing::ActionFrameEasing()
{

}
ActionFrameEasing::~ActionFrameEasing()
{

}

float ActionFrameEasing::bounceTime(float t)
{
	if (t < 1 / 2.75) {
		return 7.5625f * t * t;
	}
	else if (t < 2 / 2.75) {
		t -= 1.5f / 2.75f;
		return 7.5625f * t * t + 0.75f;
	}
	else if (t < 2.5 / 2.75) {
		t -= 2.25f / 2.75f;
		return 7.5625f * t * t + 0.9375f;
	}

	t -= 2.625f / 2.75f;
	return 7.5625f * t * t + 0.984375f;
}

float ActionFrameEasing::easeValue(float t)
{
	if (_type == FrameEasingType::kframeEasingInstant)
	{
		if (t < 1) return 0;
		else return 1;
	}
	else if (_type == FrameEasingType::kframeEasingLinear)
	{
		return t;
	}
	else if (_type == FrameEasingType::kframeEasingCubicIn)
	{
		float rate = _fValue;
		return powf(t,rate);
	}
	else if (_type == FrameEasingType::kframeEasingCubicOut)
	{
		float rate = _fValue;
		return powf(t,1/rate);
	}
	else if (_type == FrameEasingType::kframeEasingCubicInOut)
	{
		float rate = _fValue;
		t *= 2;
		if (t < 1)
		{
			return 0.5f * powf (t, rate);
		}
		else
		{
			return 1.0f - 0.5f * powf(2-t, rate);
		}
	}
	else if (_type == FrameEasingType::kframeEasingElasticIn)
	{
		float period = _fValue;
		float newT = 0;
		if (t == 0 || t == 1)
			newT = t;

		else {
			float s = period / 4;
			t = t - 1;
			newT = -powf(2, 10 * t) * sinf( (t-s) * M_PI_X_2 / period);
		}
		return newT;
	}
	else if (_type == FrameEasingType::kframeEasingElasticOut)
	{
		float period = _fValue;
		float newT = 0;
		if (t == 0 || t == 1) {
			newT = t;

		} else {
			float s = period / 4;
			newT = powf(2, -10 * t) * sinf( (t-s) *M_PI_X_2 / period) + 1;
		}
		return newT;
	}
	else if (_type == FrameEasingType::kframeEasingElasticInOut)
	{
		float period = _fValue;
		float newT = 0;
		if( t == 0 || t == 1 )
			newT = t;
		else {
			t = t * 2;
			if(! period )
				period = 0.3f * 1.5f;
			float s = period / 4;

			t = t -1;
			if( t < 0 )
				newT = -0.5f * powf(2, 10 * t) * sinf((t - s) * M_PI_X_2 / period);
			else
				newT = powf(2, -10 * t) * sinf((t - s) * M_PI_X_2 / period) * 0.5f + 1;
		}
		return newT;
	}
	else if (_type == FrameEasingType::kframeEasingBounceIn)
	{
		float newT = 1 - bounceTime(1-t);
		return newT;
	}
	else if (_type == FrameEasingType::kframeEasingBounceOut)
	{
		float newT = bounceTime(t);
		return newT;
	}
	else if (_type == FrameEasingType::kframeEasingBounceInOut)
	{
		float newT = 0;
		if (t < 0.5) {
			t = t * 2;
			newT = (1 - bounceTime(1-t) ) * 0.5f;
		} else
			newT = bounceTime(t * 2 - 1) * 0.5f + 0.5f;
		return newT;
	}
	else if (_type == FrameEasingType::kframeEasingBackIn)
	{
		float overshoot = 1.70158f;
		return t * t * ((overshoot + 1) * t - overshoot);
	}
	else if (_type == FrameEasingType::kframeEasingBackOut)
	{
		float overshoot = 1.70158f;
		t = t - 1;
		return t * t * ((overshoot + 1) * t + overshoot) + 1;
	}
	else if (_type == FrameEasingType::kframeEasingBackInOut)
	{
		float overshoot = 1.70158f * 1.525f;

		t = t * 2;
		if (t < 1)
			return (t * t * ((overshoot + 1) * t - overshoot)) / 2;
		else {
			t = t - 2;
			return (t * t * ((overshoot + 1) * t + overshoot)) / 2 + 1;
		}
	}

	return 0;
}

}