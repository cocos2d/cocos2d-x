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

NS_CC_EXT_BEGIN

ActionFrame::ActionFrame()
: m_frameType(0)
, m_easingType(0)
, m_frameIndex(0)
, m_fTime(0.0f)
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
	m_easingType = easingType;
}
int ActionFrame::getEasingType()
{
	return m_easingType;
}

CCAction* ActionFrame::getAction(float fDuration)
{
	CCLog("Need a definition of <getAction> for ActionFrame");
	return NULL;
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
CCAction* ActionMoveFrame::getAction(float fDuration)
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

CCAction* ActionScaleFrame::getAction(float fDuration)
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

CCAction* ActionRotationFrame::getAction(float fDuration)
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

CCAction* ActionFadeFrame::getAction(float fDuration)
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

CCAction* ActionTintFrame::getAction(float fDuration)
{
	return CCTintTo::create(fDuration,m_color.r,m_color.g,m_color.b);
}


NS_CC_EXT_END