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

#ifndef __ActionFRAME_H__
#define __ActionFRAME_H__

#include "base/CCGeometry.h"
#include "2d/CCActionInterval.h"

namespace cocostudio {
    
USING_NS_CC_MATH;

enum FrameType
{
	kKeyframeMove = 0,
	kKeyframeScale,
	kKeyframeRotate,
	kKeyframeTint,
	kKeyframeFade,
	kKeyframeMax
};

enum class FrameEaseType
{
	Custom = -1,

	LINERAR = 0,

    SINE_EASEIN,
	SINE_EASEOUT,
	SINE_EASEINOUT,

    QUAD_EASEIN,
	QUAD_EASEOUT,
    QUAD_EASEINOUT,

    CUBIC_EASEIN,
    CUBIC_EASEOUT,
    CUBIC_EASEINOUT,

    QUART_EASEIN,
    QUART_EASEOUT,
    QUART_EASEINOUT,

    QUINT_EASEIN,
	QUINT_EASEOUT,
    QUINT_EASEINOUT,

    EXPO_EASEIN,
    EXPO_EASEOUT,
    EXPO_EASEINOUT,

    CIRC_EASEIN,
    CIRC_EASEOUT,
    CIRC_EASEINOUT,

    ELASTIC_EASEIN,
    ELASTIC_EASEOUT,
    ELASTIC_EASEINOUT,

    BACK_EASEIN,
    BACK_EASEOUT,
    BACK_EASEINOUT,

    BOUNCE_EASEIN,
    BOUNCE_EASEOUT,
    BOUNCE_EASEINOUT,

	TWEEN_EASING_MAX = 10000
};
/**
*  @js NA
*  @lua NA
*/
class ActionFrame: public cocos2d::Ref
{

public:

	/**
	* Default constructor
	*/
	ActionFrame();

	/**
	* Default destructor
	*/
	virtual ~ActionFrame();

	/**
	* Changes the index of action frame
	*
	* @param index   the index of action frame
	*/
	void setFrameIndex(int index);

	/**
	* Gets the index of action frame
	*
	* @return the index of action frame
	*/
	int getFrameIndex();

	/**
	* Changes the time of action frame
	*
	* @param fTime  the time of action frame
	*/
	void setFrameTime(float fTime);

	/**
	* Gets the time of action frame
	*
	* @return fTime  the time of action frame
	*/
	float getFrameTime();

	/**
	* Changes the type of action frame
	*
	* @param frameType   the type of action frame
	*/
	void setFrameType(int frameType);

	/**
	* Gets the type of action frame
	*
	* @return the type of action frame
	*/
	int getFrameType();

	/**
	* Changes the easing type.
	*
	* @param easingType the easing type.
	*/
	void setEasingType(int easingType);

	/**
	* Gets the easing type.
	*
	* @return the easing type.
	*/
	int getEasingType();

	/**
	* Gets the ActionInterval of ActionFrame.
	*
	* @parame duration   the duration time of ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
	/**
	* Gets the ActionInterval of ActionFrame.
	*
	* @parame duration   the duration time of ActionFrame
	*
	* @parame duration   the source ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration,ActionFrame* srcFrame);

	/**
	*Set the ActionInterval easing parameter.
	*
	*@parame parameter   the parameter for frame ease
	*
	*/
	virtual void setEasingParameter(std::vector<float>& parameter);
protected:
	/**
	* Gets the Easing Action of ActionFrame.
	*
	* @parame action   the duration time of ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getEasingAction(cocos2d::ActionInterval* action);
protected:
	int _frameType;	
	int _frameIndex;
	float _fTime;
	FrameEaseType _easingType;
	std::vector<float> _Parameter;
};

/**
*  @js NA
*  @lua NA
*/
class ActionMoveFrame:public ActionFrame
{
public:

	/**
	* Default constructor
	*/
	ActionMoveFrame();

	/**
	* Default destructor
	*/
	virtual ~ActionMoveFrame();

	/**
	* Changes the move action position.
	*
	* @param the move action position.
	*/
	void setPosition(Vector2 pos);

	/**
	* Gets the move action position.
	*
	* @return the move action position.
	*/
	Vector2 getPosition();

	/**
	* Gets the ActionInterval of ActionFrame.
	*
	* @parame duration   the duration time of ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
protected:
    Vector2 _position;
};

/**
*  @js NA
*  @lua NA
*/
class ActionScaleFrame:public ActionFrame
{
public:

	/**
	* Default constructor
	*/
	ActionScaleFrame();

	/**
	* Default destructor
	*/
	virtual ~ActionScaleFrame();

	/**
	* Changes the scale action scaleX.
	*
	* @param the scale action scaleX.
	*/
	void setScaleX(float scaleX);

	/**
	* Gets the scale action scaleX.
	*
	* @return the scale action scaleX.
	*/
	float getScaleX();

	/**
	* Changes the scale action scaleY.
	*
	* @param rotation the scale action scaleY.
	*/
	void setScaleY(float scaleY);

	/**
	* Gets the scale action scaleY.
	*
	* @return the the scale action scaleY.
	*/
	float getScaleY();

	/**
	* Gets the ActionInterval of ActionFrame.
	*
	* @parame duration   the duration time of ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
protected:
	float _scaleX;
	float _scaleY;
};
/**
*  @js NA
*  @lua NA
*/
class ActionRotationFrame:public ActionFrame
{
public:

	/**
	* Default constructor
	*/
	ActionRotationFrame();

	/**
	* Default destructor
	*/
	virtual ~ActionRotationFrame();

	/**
	* Changes rotate action rotation.
	*
	* @param rotation rotate action rotation.
	*/
	void setRotation(float rotation);

	/**
	* Gets the rotate action rotation.
	*
	* @return the rotate action rotation.
	*/
	float getRotation();

	/**
	* Gets the ActionInterval of ActionFrame.
	*
	* @parame duration   the duration time of ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
	/**
	* Gets the ActionInterval of ActionFrame.
	*
	* @parame duration   the duration time of ActionFrame
	*
	* @parame duration   the source ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration,ActionFrame* srcFrame);
public:
	float _rotation;
};
/**
*  @js NA
*  @lua NA
*/
class ActionFadeFrame:public ActionFrame
{
public:

	/**
	* Default constructor
	*/
	ActionFadeFrame();

	/**
	* Default destructor
	*/
	virtual ~ActionFadeFrame();

	/**
	* Changes the fade action opacity.
	*
	* @param opacity the fade action opacity
	*/
	void setOpacity(int opacity);

	/**
	* Gets the fade action opacity.
	*
	* @return the fade action opacity.
	*/
	int getOpacity();

	/**
	* Gets the ActionInterval of ActionFrame.
	*
	* @parame duration   the duration time of ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
protected:
	float _opacity;
};
/**
*  @js NA
*  @lua NA
*/
class ActionTintFrame:public ActionFrame
{

public:

	/**
	* Default constructor
	*/
	ActionTintFrame();

	/**
	* Default destructor
	*/
	virtual ~ActionTintFrame();

	/**
	* Changes the tint action color.
	*
	* @param ccolor the tint action color
	*/
	void setColor(cocos2d::Color3B ccolor);

	/**
	* Gets the tint action color.
	*
	* @return the tint action color.
	*/
	cocos2d::Color3B getColor();

	/**
	* Gets the ActionInterval of ActionFrame.
	*
	* @parame duration   the duration time of ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
protected:
	cocos2d::Color3B _color;
};

}

#endif
