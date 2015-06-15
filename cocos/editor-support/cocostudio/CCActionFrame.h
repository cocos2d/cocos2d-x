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

#include "math/CCGeometry.h"
#include "2d/CCActionInterval.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {
    
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
class CC_STUDIO_DLL ActionFrame: public cocos2d::Ref
{

public:

    /**
    * @~english Default constructor.
    * @~chinese 默认构造函数.
    */
    ActionFrame();

    /**
    * @~english Default destructor.
    * @~chinese 默认析构函数.
    */
    virtual ~ActionFrame();

	/**
	* @~english Changes the index of action frame.
    * @~chinese 改变动作帧的索引值.
    *
	* @param index   @~english the index of action frame @~chinese 动作帧索引值
	*/
	void setFrameIndex(int index);

	/**
	* @~english Gets the index of action frame.
    * @~chinese 获取动作帧的索引值.
    *
	* @return @~english the index of action frame @~chinese 动作帧的索引值
	*/
	int getFrameIndex();

	/**
	* @~english Changes the time of action frame.
    * @~chinese 改变动作帧时间.
    *
	* @param fTime  @~english the time of action frame @~chinese 动作帧时间
	*/
	void setFrameTime(float fTime);

	/**
	* @~english Gets the time of action frame.
    * @~chinese 获取动作帧时间.
    *
	* @return fTime  @~english the time of action frame @~chinese 动作帧时间
	*/
	float getFrameTime();

	/**
	* @~english Changes the type of action frame.
    * @~chinese 改变动作帧类型.
    *
	* @param frameType   @~english the type of action frame @~chinese 动作帧类型
	*/
	void setFrameType(int frameType);

	/**
	* @~english Gets the type of action frame.
    * @~chinese 获取动作帧类型.
    *
	* @return @~english the type of action frame @~chinese 动作帧类型
	*/
	int getFrameType();

	/**
	* @~english Changes the easing type.
    * @~chinese 改变缓动类型.
    *
	* @param easingType @~english the easing type. @~chinese 缓动类型
	*/
	void setEasingType(int easingType);

	/**
	* @~english Gets the easing type.
    * @~chinese 获取缓动类型.
    *
	* @return @~english the easing type. @~chinese 缓动类型
	*/
	int getEasingType();

	/**
	* @~english Gets the ActionInterval of ActionFrame.
    * @~chinese 获取动作帧的动作间隔
    *
	* @parame duration   @~english the duration time of ActionFrame @~chinese 动作帧的动作持续时间
	*
	* @return @~english ActionInterval @~chinese 动作间隔
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
	/**
    * @~english Gets the ActionInterval of ActionFrame.
    * @~chinese 获取动作帧的动作间隔
    *
    * @parame duration   @~english the duration time of ActionFrame @~chinese 动作帧的动作持续时间
    *
	* @parame srcFrame   @~english the source ActionFrame @~chinese 源动作帧
	*
    * @return @~english ActionInterval @~chinese 动作间隔
    */
	virtual cocos2d::ActionInterval* getAction(float duration,ActionFrame* srcFrame);

	/**
	* @~english Set the ActionInterval easing parameter.
    * @~chinese 设定动作间隔缓动参数.
    *
	* @parame parameter   @~english the parameter for frame ease @~chinese 帧缓动参数
	*
	*/
	virtual void setEasingParameter(std::vector<float>& parameter);
protected:
	/**
	* @~english Gets the Easing Action of ActionFrame.
    * @~chinese 获取动作帧的缓动参数.
    *
	* @parame action   @~english the duration time of ActionFrame @~chinese 动作帧持续时间
	*
	* @return @~english ActionInterval @~chinese 动作间隔
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
class CC_STUDIO_DLL ActionMoveFrame:public ActionFrame
{
public:

    /**
    * @~english Default constructor.
    * @~chinese 默认构造函数.
    */
    ActionMoveFrame();

    /**
    * @~english Default destructor.
    * @~chinese 默认析构函数.
    */
    virtual ~ActionMoveFrame();

	/**
    * @~english Changes the move action position.
    * @~chinese 改变位移动作位置.
    *
	* @param pos  @~english the move action position. @~chinese 位移动作位置
	*/
	void setPosition(cocos2d::Vec2 pos);

    /**
    * @~english Gets the move action position.
    * @~chinese 获取位移动作位置.
    *
	* @return @~english the move action position. @~chinese 位移动作位置
	*/
	cocos2d::Vec2 getPosition();

	/**
	* @~english Gets the ActionInterval of ActionFrame.
    * @~chinese 获取动作帧的动作间隔.
    *
	* @parame duration   @~english the duration time of ActionFrame @~chinese 动作帧的持续时间
	*
	* @return @~english ActionInterval @~chinese 动作间隔
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
protected:
    cocos2d::Vec2 _position;
};

/**
*  @js NA
*  @lua NA
*/
class CC_STUDIO_DLL ActionScaleFrame:public ActionFrame
{
public:

    /**
    * @~english Default constructor.
    * @~chinese 默认构造函数.
    */
    ActionScaleFrame();

    /**
    * @~english Default destructor.
    * @~chinese 默认析构函数.
    */
    virtual ~ActionScaleFrame();

	/**
	* @~english Changes the scale action scaleX.
    * @~chinese 改变缩放动作的X轴缩放因子.
    *
	* @param @~english the scale action scaleX. @~chinese X轴缩放因子
	*/
	void setScaleX(float scaleX);

	/**
	* @~english Gets the scale action scaleX.
    * @~chinese 获取缩放动作的X轴缩放因子.
    *
	* @return @~english the scale action scaleX. @~chinese 缩放动作的X轴缩放因子
	*/
	float getScaleX();

	/**
    * @~english Changes the scale action scaleY.
    * @~chinese 改变缩放动作的Y轴缩放因子.
    *
    * @param @~english the scale action scaleY. @~chinese Y轴缩放因子
    */
	void setScaleY(float scaleY);

	/**
    * @~english Gets the scale action scaleY.
    * @~chinese 获取缩放动作的Y轴缩放因子.
    *
    * @return @~english the scale action scaleY. @~chinese 缩放动作的Y轴缩放因子
    */
	float getScaleY();

	/**
	* @~english Gets the ActionInterval of ActionFrame.
    * @~chinese 获取动作帧的动作间隔
	*
	* @parame duration   @~english the duration time of ActionFrame @~chinese 动作帧的持续时间
	*
	* @return @~english ActionInterval @~chinese 动作间隔
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
class CC_STUDIO_DLL ActionRotationFrame:public ActionFrame
{
public:

    /**
    * @~english Default constructor.
    * @~chinese 默认构造函数.
    */
    ActionRotationFrame();

    /**
    * @~english Default destructor.
    * @~chinese 默认析构函数.
    */
    virtual ~ActionRotationFrame();

	/**
	* @~english Changes rotate action rotation.
    * @~chinese 改变旋转动作的旋转角度.
    *
	* @param rotation   @~english rotate action rotation. @~chinese 旋转动作的旋转角度.
	*/
	void setRotation(float rotation);

	/**
	* @~english Gets the rotate action rotation.
    * @~chinese 获取旋转动作的旋转角度.
    *
	* @return @~english the rotate action rotation. @~chinese 旋转动作的旋转角度.
	*/
	float getRotation();

    /**
    * @~english Gets the ActionInterval of ActionFrame.
    * @~chinese 获取动作帧的动作间隔
    *
    * @parame duration   @~english the duration time of ActionFrame @~chinese 动作帧的持续时间
    *
    * @return @~english ActionInterval @~chinese 动作间隔
    */
    virtual cocos2d::ActionInterval* getAction(float duration);
    /**
    * @~english Gets the ActionInterval of ActionFrame.
    * @~chinese 获取动作帧的动作间隔
    *
    * @parame duration   @~english the duration time of ActionFrame @~chinese 动作帧的动作持续时间
    *
    * @parame srcFrame   @~english the source ActionFrame @~chinese 源动作帧
    *
    * @return @~english ActionInterval @~chinese 动作间隔
    */
    virtual cocos2d::ActionInterval* getAction(float duration, ActionFrame* srcFrame);
public:
	float _rotation;
};
/**
*  @js NA
*  @lua NA
*/
class CC_STUDIO_DLL ActionFadeFrame:public ActionFrame
{
public:

    /**
    * @~english Default constructor.
    * @~chinese 默认构造函数.
    */
    ActionFadeFrame();

    /**
    * @~english Default destructor.
    * @~chinese 默认析构函数.
    */
    virtual ~ActionFadeFrame();

	/**
	* @~english Changes the fade action opacity.
    * @~chinese 改变淡入淡出动作的不透明度.
    *
	* @param opacity @~english the fade action opacity @~chinese 淡入淡出动作的不透明度
	*/
	void setOpacity(int opacity);

	/**
	* @~english Gets the fade action opacity.
    * @~chinese 获取淡入淡出动作的不透明度.
    *
	* @return @~english the fade action opacity. @~chinese 淡入淡出动作的不透明度.
	*/
	int getOpacity();

    /**
    * @~english Gets the ActionInterval of ActionFrame.
    * @~chinese 获取动作帧的动作间隔
    *
    * @parame duration   @~english the duration time of ActionFrame @~chinese 动作帧的持续时间
    *
    * @return @~english ActionInterval @~chinese 动作间隔
    */
    virtual cocos2d::ActionInterval* getAction(float duration);
protected:
	float _opacity;
};
/**
*  @js NA
*  @lua NA
*/
class CC_STUDIO_DLL ActionTintFrame:public ActionFrame
{

public:

    /**
    * @~english Default constructor.
    * @~chinese 默认构造函数.
    */
    ActionTintFrame();

    /**
    * @~english Default destructor.
    * @~chinese 默认析构函数.
    */
    virtual ~ActionTintFrame();

	/**
	* @~english Changes the tint action color.
    * @~chinese 改变颜色渐变动画的颜色.
    *
	* @param ccolor  @~english the tint action color @~chinese 颜色渐变动画的颜色
	*/
	void setColor(cocos2d::Color3B ccolor);

	/**
	* @~english Gets the tint action color.
    * @~chinese 获取颜色动画的颜色.
    *
	* @return @~english the tint action color. @~chinese 颜色动画的颜色.
	*/
	cocos2d::Color3B getColor();

    /**
    * @~english Gets the ActionInterval of ActionFrame.
    * @~chinese 获取动作帧的动作间隔
    *
    * @parame duration   @~english the duration time of ActionFrame @~chinese 动作帧的持续时间
    *
    * @return @~english ActionInterval @~chinese 动作间隔
    */
    virtual cocos2d::ActionInterval* getAction(float duration);
protected:
	cocos2d::Color3B _color;
};

}

#endif
