/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "CCActionFrame.h"
#include "CCActionEaseEx.h"

NS_CC_EXT_BEGIN

ActionFrame::ActionFrame()
: m_frameType(0)
, m_frameIndex(0)
, m_fTime(0.0f)
, m_easingType(FrameEaseType::FrameEase_Linear)
{
}
ActionFrame::~ActionFrame()
{
	
}

void ActionFrame::setFrameIndex(int index)
{
	m_frameIndex = index;
}
int ActionFrame::getFrameIndex()
{
	return m_frameIndex;
}

void ActionFrame::setFrameTime(float fTime)
{
	m_fTime = fTime;
}
float ActionFrame::getFrameTime()
{
	return m_fTime;
}

void ActionFrame::setFrameType(int frameType)
{
	m_frameType = frameType;
}
int ActionFrame::getFrameType()
{
	return m_frameType;
}

void ActionFrame::setEasingType(int easingType)
{
	m_easingType = (FrameEaseType)easingType;
}
int ActionFrame::getEasingType()
{
	return (int)m_easingType;
}

CCActionInterval* ActionFrame::getAction(float fDuration)
{
	CCLog("Need a definition of <getAction> for ActionFrame");
	return NULL;
}

void ActionFrame::setEasingParameter(std::vector<float> parameter)
{
	m_Parameter.clear();
	for (int i = 0; i<parameter.size(); i++)
	{
		m_Parameter.push_back(parameter[i]);
	}
}

CCActionInterval* ActionFrame::getEasingAction(CCActionInterval* action)
{
	if (action == NULL)
	{
		return NULL;
	}

	switch (m_easingType)
	{
	case FrameEase_Custom:
		{
			CCEaseBezierAction* cAction = CCEaseBezierAction::create(action);
			cAction->setBezierParamer(m_Parameter[1],m_Parameter[3],m_Parameter[5],m_Parameter[7]);
			return cAction;
		}
		break;
	case FrameEase_Linear:
		return action;
		break;
	case FrameEase_Sine_EaseIn:
		return CCEaseSineIn::create(action);
		break;
	case FrameEase_Sine_EaseOut:
		return CCEaseSineOut::create(action);
		break;
	case FrameEase_Sine_EaseInOut:
		return CCEaseSineInOut::create(action);
		break;
	case FrameEase_Quad_EaseIn:
		return CCEaseQuadraticActionIn::create(action);
		break;
	case FrameEase_Quad_EaseOut:
		return CCEaseQuadraticActionOut::create(action);
		break;
	case FrameEase_Quad_EaseInOut:
		return CCEaseQuadraticActionInOut::create(action);
		break;
	case FrameEase_Cubic_EaseIn:
		return CCEaseCubicActionIn::create(action);
		break;
	case FrameEase_Cubic_EaseOut:
		return CCEaseCubicActionOut::create(action);
		break;
	case FrameEase_Cubic_EaseInOut:
		return CCEaseCubicActionInOut::create(action);
		break;
	case FrameEase_Quart_EaseIn:
		return CCEaseQuarticActionIn::create(action);
		break;
	case FrameEase_Quart_EaseOut:
		return CCEaseQuadraticActionOut::create(action);
		break;
	case FrameEase_Quart_EaseInOut:
		return CCEaseQuarticActionInOut::create(action);
		break;
	case FrameEase_Quint_EaseIn:
		return CCEaseQuinticActionIn::create(action);
		break;
	case FrameEase_Quint_EaseOut:
		return CCEaseQuinticActionOut::create(action);
		break;
	case FrameEase_Quint_EaseInOut:
		return CCEaseQuinticActionInOut::create(action);
		break;
	case FrameEase_Expo_EaseIn:
		return CCEaseExponentialIn::create(action);
		break;
	case FrameEase_Expo_EaseOut:
		return CCEaseExponentialOut::create(action);
		break;
	case FrameEase_Expo_EaseInOut:
		return CCEaseExponentialInOut::create(action);
		break;
	case FrameEase_Circ_EaseIn:
		return CCEaseCircleActionIn::create(action);
		break;
	case FrameEase_Circ_EaseOut:
		return CCEaseCircleActionOut::create(action);
		break;
	case FrameEase_Circ_EaseInOut:
		return CCEaseCircleActionInOut::create(action);
		break;
	case FrameEase_Elastic_EaseIn:
		{
			CCEaseElasticIn* cAction = CCEaseElasticIn::create(action);
			cAction->setPeriod(m_Parameter[0]);
			return cAction;
		}
		break;
	case FrameEase_Elastic_EaseOut:
		{
			CCEaseElasticOut* cAction = CCEaseElasticOut::create(action);
			cAction->setPeriod(m_Parameter[0]);
			return cAction;
		}
		break;
	case FrameEase_Elastic_EaseInOut:
		{
			CCEaseElasticInOut* cAction = CCEaseElasticInOut::create(action);
			cAction->setPeriod(m_Parameter[0]);
			return cAction;
		}
		break;
	case FrameEase_Back_EaseIn:
		return CCEaseBackIn::create(action);
		break;
	case FrameEase_Back_EaseOut:
		return CCEaseBackOut::create(action);
		break;
	case FrameEase_Back_EaseInOut:
		return CCEaseBackInOut::create(action);
		break;
	case FrameEase_Bounce_EaseIn:
		return CCEaseBounceIn::create(action);
		break;
	case FrameEase_Bounce_EaseOut:
		return CCEaseBounceOut::create(action);
		break;
	case FrameEase_Bounce_EaseInOut:
		return CCEaseBounceInOut::create(action);
		break;
	default:
		return action;
		break;
	}
}
//////////////////////////////////////////////////////////////////////////

ActionMoveFrame::ActionMoveFrame()
: m_position(ccp(0.0f,0.0f))
{
	m_frameType = (int)kKeyframeMove;
}
ActionMoveFrame::~ActionMoveFrame()
{

}
void ActionMoveFrame::setPosition(CCPoint pos)
{
	m_position = pos;
}
CCPoint ActionMoveFrame::getPosition()
{
	return m_position;
}
CCActionInterval* ActionMoveFrame::getAction(float fDuration)
{
	return CCMoveTo::create(fDuration,m_position);
}
//////////////////////////////////////////////////////////////////////////

ActionScaleFrame::ActionScaleFrame()
: m_scaleX(1.0f)
, m_scaleY(1.0f)
{
	m_frameType = (int)kKeyframeScale;
}

ActionScaleFrame::~ActionScaleFrame()
{

}

void ActionScaleFrame::setScaleX(float scaleX)
{
	m_scaleX = scaleX;
}

float ActionScaleFrame::getScaleX()
{
	return m_scaleX;
}

void ActionScaleFrame::setScaleY(float scaleY)
{
	m_scaleY = scaleY;
}

float ActionScaleFrame::getScaleY()
{
	return m_scaleY;
}

CCActionInterval* ActionScaleFrame::getAction(float fDuration)
{
	return CCScaleTo::create(fDuration,m_scaleX,m_scaleY);
}

ActionRotationFrame::ActionRotationFrame()
: m_rotation(0.0f)
{
	m_frameType = (int)kKeyframeRotate;
}

ActionRotationFrame::~ActionRotationFrame()
{

}

void ActionRotationFrame::setRotation(float rotation)
{
	m_rotation = rotation;
}

float ActionRotationFrame::getRotation()
{
	return m_rotation;
}

CCActionInterval* ActionRotationFrame::getAction(float fDuration)
{
	return CCRotateTo::create(fDuration,m_rotation);
}

ActionFadeFrame::ActionFadeFrame()
: m_opacity(255)
{
	m_frameType = (int)kKeyframeFade;
}

ActionFadeFrame::~ActionFadeFrame()
{

}

void ActionFadeFrame::setOpacity(int opacity)
{
	m_opacity = opacity;
}

int ActionFadeFrame::getOpacity()
{
	return m_opacity;
}

CCActionInterval* ActionFadeFrame::getAction(float fDuration)
{
	return CCFadeTo::create(fDuration,m_opacity);
}


ActionTintFrame::ActionTintFrame()
: m_color(ccc3(255,255,255))
{
	m_frameType = (int)kKeyframeTint;
}

ActionTintFrame::~ActionTintFrame()
{

}

void ActionTintFrame::setColor(ccColor3B ccolor)
{
	m_color = ccolor;
}

ccColor3B ActionTintFrame::getColor()
{
	return m_color;
}

CCActionInterval* ActionTintFrame::getAction(float fDuration)
{
	return CCTintTo::create(fDuration,m_color.r,m_color.g,m_color.b);
}


NS_CC_EXT_END