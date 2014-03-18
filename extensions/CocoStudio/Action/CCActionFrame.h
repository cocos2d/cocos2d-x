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

#ifndef __ActionFRAME_H__
#define __ActionFRAME_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

enum FrameType
{
	kKeyframeMove = 0,
	kKeyframeScale,
	kKeyframeRotate,
	kKeyframeTint,
	kKeyframeFade,
	kKeyframeMax
};

enum FrameEaseType
{
	FrameEase_Custom = -1,

	FrameEase_Linear = 0,

	FrameEase_Sine_EaseIn,
	FrameEase_Sine_EaseOut,
	FrameEase_Sine_EaseInOut,


	FrameEase_Quad_EaseIn,
	FrameEase_Quad_EaseOut,
	FrameEase_Quad_EaseInOut,

	FrameEase_Cubic_EaseIn,
	FrameEase_Cubic_EaseOut,
	FrameEase_Cubic_EaseInOut,

	FrameEase_Quart_EaseIn,
	FrameEase_Quart_EaseOut,
	FrameEase_Quart_EaseInOut,

	FrameEase_Quint_EaseIn,
	FrameEase_Quint_EaseOut,
	FrameEase_Quint_EaseInOut,

	FrameEase_Expo_EaseIn,
	FrameEase_Expo_EaseOut,
	FrameEase_Expo_EaseInOut,

	FrameEase_Circ_EaseIn,
	FrameEase_Circ_EaseOut,
	FrameEase_Circ_EaseInOut,

	FrameEase_Elastic_EaseIn,
	FrameEase_Elastic_EaseOut,
	FrameEase_Elastic_EaseInOut,

	FrameEase_Back_EaseIn,
	FrameEase_Back_EaseOut,
	FrameEase_Back_EaseInOut,

	FrameEase_Bounce_EaseIn,
	FrameEase_Bounce_EaseOut,
	FrameEase_Bounce_EaseInOut,

	FrameEase_TWEEN_EASING_MAX = 10000
};
/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL ActionFrame:public CCObject
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
     * Gets the CCAction of ActionFrame.
     *
     * @parame fDuration   the duration time of ActionFrame
     *
     * @return CCAction
     */
	virtual CCActionInterval* getAction(float fDuration);
	    /**
     * Gets the CCAction of ActionFrame.
     *
     * @parame fDuration   the duration time of ActionFrame
	 *
	 * @parame fDuration   the source ActionFrame
     *
     * @return CCAction
     */
	virtual CCActionInterval* getAction(float fDuration,ActionFrame* srcFrame);

	/**
	*Set the CCAction easing parameter.
	*
	*@parame parameter   the parameter for frame ease
	*
	*/
	virtual void setEasingParameter(std::vector<float> parameter);
protected:
    /**
     * Gets the Easing Action of ActionFrame.
     *
     * @parame action   the duration time of ActionFrame
     *
     * @return CCAction
     */
	virtual CCActionInterval* getEasingAction(CCActionInterval* action);
protected:
	int m_frameType;	
	int m_frameIndex;
	float m_fTime;
	FrameEaseType m_easingType;
	std::vector<float> m_Parameter;
};
/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL ActionMoveFrame:public ActionFrame
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
	void setPosition(CCPoint pos);
    
    /**
     * Gets the move action position.
     *
     * @return the move action position.
     */
	CCPoint getPosition();

    /**
     * Gets the CCAction of ActionFrame.
     *
     * @parame fDuration   the duration time of ActionFrame
     *
     * @return CCAction
     */
	virtual CCActionInterval* getAction(float fDuration);
protected:
	CCPoint m_position;
};
/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL ActionScaleFrame:public ActionFrame
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
     * Gets the CCAction of ActionFrame.
     *
     * @parame fDuration   the duration time of ActionFrame
     *
     * @return CCAction
     */
	virtual CCActionInterval* getAction(float fDuration);
protected:
	float m_scaleX;
	float m_scaleY;
};
/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL ActionRotationFrame:public ActionFrame
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
     * Gets the CCAction of ActionFrame.
     *
     * @parame fDuration   the duration time of ActionFrame
     *
     * @return CCAction
     */
	virtual CCActionInterval* getAction(float fDuration);
		    /**
     * Gets the CCAction of ActionFrame.
     *
     * @parame fDuration   the duration time of ActionFrame
	 *
	 * @parame fDuration   the source ActionFrame
     *
     * @return CCAction
     */
	virtual CCActionInterval* getAction(float fDuration,ActionFrame* srcFrame);
public:
	float m_rotation;
};
/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL ActionFadeFrame:public ActionFrame
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
     * Gets the CCAction of ActionFrame.
     *
     * @parame fDuration   the duration time of ActionFrame
     *
     * @return CCAction
     */
	virtual CCActionInterval* getAction(float fDuration);
protected:
	float m_opacity;
};
/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL ActionTintFrame:public ActionFrame
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
	void setColor(ccColor3B ccolor);
    
    /**
     * Gets the tint action color.
     *
     * @return the tint action color.
     */
	ccColor3B getColor();
    
    /**
     * Gets the CCAction of ActionFrame.
     *
     * @parame fDuration   the duration time of ActionFrame
     *
     * @return CCAction
     */
	virtual CCActionInterval* getAction(float fDuration);
protected:
	ccColor3B m_color;
};

NS_CC_EXT_END

#endif
