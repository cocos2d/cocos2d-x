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
: _frameType(0)
, _easingType(0)
, _frameIndex(0)
, _fTime(0.0f)
{

}
ActionFrame::~ActionFrame()
{

}

void ActionFrame::setFrameIndex(int index)
{
	_frameIndex = index;
}
int ActionFrame::getFrameIndex()
{
	return _frameIndex;
}

void ActionFrame::setFrameTime(float fTime)
{
	_fTime = fTime;
}
float ActionFrame::getFrameTime()
{
	return _fTime;
}

void ActionFrame::setFrameType(int frameType)
{
	_frameType = frameType;
}
int ActionFrame::getFrameType()
{
	return _frameType;
}

void ActionFrame::setEasingType(int easingType)
{
	_easingType = easingType;
}
int ActionFrame::getEasingType()
{
	return _easingType;
}

Action* ActionFrame::getAction(float fDuration)
{
	log("Need a definition of <getAction> for ActionFrame");
	return NULL;
}
//////////////////////////////////////////////////////////////////////////

ActionMoveFrame::ActionMoveFrame()
: _position(Point(0.0f,0.0f))
{
	_frameType = (int)kKeyframeMove;
}
ActionMoveFrame::~ActionMoveFrame()
{

}
void ActionMoveFrame::setPosition(Point pos)
{
	_position = pos;
}
Point ActionMoveFrame::getPosition()
{
	return _position;
}
Action* ActionMoveFrame::getAction(float fDuration)
{
	return MoveTo::create(fDuration,_position);
}
//////////////////////////////////////////////////////////////////////////

ActionScaleFrame::ActionScaleFrame()
: _scaleX(1.0f)
, _scaleY(1.0f)
{
	_frameType = (int)kKeyframeScale;
}

ActionScaleFrame::~ActionScaleFrame()
{

}

void ActionScaleFrame::setScaleX(float scaleX)
{
	_scaleX = scaleX;
}

float ActionScaleFrame::getScaleX()
{
	return _scaleX;
}

void ActionScaleFrame::setScaleY(float scaleY)
{
	_scaleY = scaleY;
}

float ActionScaleFrame::getScaleY()
{
	return _scaleY;
}

Action* ActionScaleFrame::getAction(float fDuration)
{
	return ScaleTo::create(fDuration,_scaleX,_scaleY);
}

ActionRotationFrame::ActionRotationFrame()
: _rotation(0.0f)
{
	_frameType = (int)kKeyframeRotate;
}

ActionRotationFrame::~ActionRotationFrame()
{

}

void ActionRotationFrame::setRotation(float rotation)
{
	_rotation = rotation;
}

float ActionRotationFrame::getRotation()
{
	return _rotation;
}

Action* ActionRotationFrame::getAction(float fDuration)
{
	return RotateTo::create(fDuration,_rotation);
}

ActionFadeFrame::ActionFadeFrame()
: _opacity(255)
{
	_frameType = (int)kKeyframeFade;
}

ActionFadeFrame::~ActionFadeFrame()
{

}

void ActionFadeFrame::setOpacity(int opacity)
{
	_opacity = opacity;
}

int ActionFadeFrame::getOpacity()
{
	return _opacity;
}

Action* ActionFadeFrame::getAction(float fDuration)
{
	return FadeTo::create(fDuration,_opacity);
}


ActionTintFrame::ActionTintFrame()
: _color(Color3B(255,255,255))
{
	_frameType = (int)kKeyframeTint;
}

ActionTintFrame::~ActionTintFrame()
{

}

void ActionTintFrame::setColor(Color3B ccolor)
{
	_color = ccolor;
}

Color3B ActionTintFrame::getColor()
{
	return _color;
}

Action* ActionTintFrame::getAction(float fDuration)
{
	return TintTo::create(fDuration,_color.r,_color.g,_color.b);
}


NS_CC_EXT_END