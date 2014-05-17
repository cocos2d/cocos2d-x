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

#include "cocostudio/CCActionFrame.h"
#include "2d/CCActionEase.h"

using namespace cocos2d;

namespace cocostudio {

ActionFrame::ActionFrame()
: _frameType(0)
, _frameIndex(0)
, _fTime(0.0f)
, _easingType(FrameEaseType::LINERAR)
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
	_easingType = (FrameEaseType)easingType;
}
int ActionFrame::getEasingType()
{
	return (int)_easingType;
}

ActionInterval* ActionFrame::getAction(float fDuration)
{
	log("Need a definition of <getAction> for ActionFrame");
	return nullptr;
}
ActionInterval* ActionFrame::getAction(float fDuration,ActionFrame* srcFrame)
{
	return this->getAction(fDuration);
}

void ActionFrame::setEasingParameter(std::vector<float>& parameter)
{
	_Parameter.clear();

	for (size_t i = 0; i<parameter.size(); i++)
	{
		_Parameter.push_back(parameter[i]);
	}
}

ActionInterval* ActionFrame::getEasingAction(ActionInterval* action)
{
	if (action == nullptr)
	{
		return nullptr;
	}

	switch (_easingType)
	{
	case FrameEaseType::Custom:
		{
			EaseBezierAction* cAction = EaseBezierAction::create(action);
			cAction->setBezierParamer(_Parameter[0],_Parameter[1],_Parameter[2],_Parameter[3]);
			return cAction;
		}
		break;
	case FrameEaseType::LINERAR:
		return action;
		break;
	case FrameEaseType::SINE_EASEIN:
		return EaseSineIn::create(action);
		break;
	case FrameEaseType::SINE_EASEOUT:
		return EaseSineOut::create(action);
		break;
	case FrameEaseType::SINE_EASEINOUT:
		return EaseSineInOut::create(action);
		break;
	case FrameEaseType::QUAD_EASEIN:
		return EaseQuadraticActionIn::create(action);
		break;
	case FrameEaseType::QUAD_EASEOUT:
		return EaseQuadraticActionOut::create(action);
		break;
	case FrameEaseType::QUAD_EASEINOUT:
		return EaseQuadraticActionInOut::create(action);
		break;
	case FrameEaseType::CUBIC_EASEIN:
		return EaseCubicActionIn::create(action);
		break;
	case FrameEaseType::CUBIC_EASEOUT:
		return EaseCubicActionOut::create(action);
		break;
	case FrameEaseType::CUBIC_EASEINOUT:
		return EaseCubicActionInOut::create(action);
		break;
	case FrameEaseType::QUART_EASEIN:
		return EaseQuarticActionIn::create(action);
		break;
	case FrameEaseType::QUART_EASEOUT:
		return EaseQuadraticActionOut::create(action);
		break;
	case FrameEaseType::QUART_EASEINOUT:
		return EaseQuarticActionInOut::create(action);
		break;
	case FrameEaseType::QUINT_EASEIN:
		return EaseQuinticActionIn::create(action);
		break;
	case FrameEaseType::QUINT_EASEOUT:
		return EaseQuinticActionOut::create(action);
		break;
	case FrameEaseType::QUINT_EASEINOUT:
		return EaseQuinticActionInOut::create(action);
		break;
	case FrameEaseType::EXPO_EASEIN:
		return EaseExponentialIn::create(action);
		break;
	case FrameEaseType::EXPO_EASEOUT:
		return EaseExponentialOut::create(action);
		break;
	case FrameEaseType::EXPO_EASEINOUT:
		return EaseExponentialInOut::create(action);
		break;
	case FrameEaseType::CIRC_EASEIN:
		return EaseCircleActionIn::create(action);
		break;
	case FrameEaseType::CIRC_EASEOUT:
		return EaseCircleActionOut::create(action);
		break;
	case FrameEaseType::CIRC_EASEINOUT:
		return EaseCircleActionInOut::create(action);
		break;
	case FrameEaseType::ELASTIC_EASEIN:
		{
			return EaseElasticIn::create(action);
		}
		break;
	case FrameEaseType::ELASTIC_EASEOUT:
		{
			return EaseElasticOut::create(action);
		}
		break;
	case FrameEaseType::ELASTIC_EASEINOUT:
		{
			return EaseElasticInOut::create(action);
		}
		break;
	case FrameEaseType::BACK_EASEIN:
		return EaseBackIn::create(action);
		break;
	case FrameEaseType::BACK_EASEOUT:
		return EaseBackOut::create(action);
		break;
	case FrameEaseType::BACK_EASEINOUT:
		return EaseBackInOut::create(action);
		break;
	case FrameEaseType::BOUNCE_EASEIN:
		return EaseBounceIn::create(action);
		break;
	case FrameEaseType::BOUNCE_EASEOUT:
		return EaseBounceOut::create(action);
		break;
	case FrameEaseType::BOUNCE_EASEINOUT:
		return EaseBounceInOut::create(action);
		break;
	default:
		return action;
		break;
	}
}
//////////////////////////////////////////////////////////////////////////

ActionMoveFrame::ActionMoveFrame()
	: _position(Vec2(0.0f,0.0f))
{
	_frameType = (int)kKeyframeMove;
}
ActionMoveFrame::~ActionMoveFrame()
{

}
void ActionMoveFrame::setPosition(Vec2 pos)
{
	_position = pos;
}
Vec2 ActionMoveFrame::getPosition()
{
	return _position;
}
ActionInterval* ActionMoveFrame::getAction(float fDuration)
{
	return this->getEasingAction(MoveTo::create(fDuration,_position));
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

ActionInterval* ActionScaleFrame::getAction(float fDuration)
{
	return this->getEasingAction(ScaleTo::create(fDuration,_scaleX,_scaleY));
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

ActionInterval* ActionRotationFrame::getAction(float fDuration)
{
	return this->getEasingAction(RotateTo::create(fDuration,_rotation));
}
ActionInterval* ActionRotationFrame::getAction(float fDuration,ActionFrame* srcFrame)
{
	ActionRotationFrame* srcRotationFrame = static_cast<ActionRotationFrame*>(srcFrame);
	if (srcRotationFrame == nullptr)
	{
		return this->getAction(fDuration);
	}
	else
	{
		float diffRotation = _rotation - srcRotationFrame->_rotation;
		return this->getEasingAction(RotateBy::create(fDuration,diffRotation));
	}
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

ActionInterval* ActionFadeFrame::getAction(float fDuration)
{
	return this->getEasingAction(FadeTo::create(fDuration,_opacity));
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

ActionInterval* ActionTintFrame::getAction(float fDuration)
{
	return this->getEasingAction(TintTo::create(fDuration,_color.r,_color.g,_color.b));
}


}