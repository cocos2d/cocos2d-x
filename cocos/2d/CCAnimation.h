/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
CopyRight (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __CC_ANIMATION_H__
#define __CC_ANIMATION_H__

#include "platform/CCPlatformConfig.h"
#include "base/CCRef.h"
#include "base/CCValue.h"
#include "base/CCVector.h"
#include "2d/CCSpriteFrame.h"

#include <string>

NS_CC_BEGIN

class Texture2D;
class SpriteFrame;

/**
 * @addtogroup _2d
 * @{
 */

/** @class AnimationFrame
 *
 * @~english A frame of the animation. It contains information like:
 * - sprite frame name.
 * - # of delay units.
 * - offset
 * @~chinese 帧动画中的一帧，它包含了一些信息：精灵帧名，时间，偏移。
 
 @since v2.0
 */
class CC_DLL AnimationFrame : public Ref, public Clonable
{
public:
    /** @struct @~english DisplayedEventInfo
     * When the animation display,Dispatches the event of UserData.
     * @~chinese DisplayedEventInfo
     * 当显示帧动画时，分发UserData事件。
     */
    struct DisplayedEventInfo
    {
        Node* target;
        const ValueMap* userInfo;
    };
    
    /**@~english
     * Creates the animation frame with a spriteframe, number of delay units and a notification user info.
     *
     * @~chinese 
     * 使用精灵帧,时间和用户信息通知的数量创建动画帧。
     * 
     * @param spriteFrame @~english The animation frame with a spriteframe.
     * @~chinese 精灵帧。
     * @param delayUnits @~english Number of delay units.
     * @~chinese 时间。
     * @param userInfo @~english A notification user info.
     * @~chinese 用户信息通知。
     * @since 3.0
     */
    static AnimationFrame* create(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo);
    /** @~english Return a SpriteFrameName to be used.
     *
     * @~chinese 返回一个使用的精灵帧。
     * 
     * @return @~english a SpriteFrameName to be used.
     * @~chinese 使用中的精灵帧。
     */
    SpriteFrame* getSpriteFrame() const { return _spriteFrame; };
    /** @~english Set the SpriteFrame.
     *
     * @~chinese 设置精灵帧。
     * 
     * @param frame @~english A SpriteFrame will be used.
     * @~chinese 待使用的精灵帧。
     */
    void setSpriteFrame(SpriteFrame* frame)
    {
        CC_SAFE_RETAIN(frame);
        CC_SAFE_RELEASE(_spriteFrame);
        _spriteFrame = frame;
    }

    /** @~english Gets the units of time the frame takes.
     *
     * @~chinese 获取帧花费的时间。
     * 
     * @return @~english The units of time the frame takes.
     * @~chinese 帧花费的时间。
     */
    float getDelayUnits() const { return _delayUnits; };
    
    /** @~english Sets the units of time the frame takes.
     *
     * @~chinese 设置帧花费的时间。
     * 
     * @param delayUnits @~english The units of time the frame takes.
     * @~chinese 。
     */
    void setDelayUnits(float delayUnits) { _delayUnits = delayUnits; };
    
    /** @brief @~english Gets user infomation
     * A AnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this dictionary as UserInfo. 
     * If UserInfo is nil, then no notification will be broadcast.
     *
     * @~chinese 获取用户信息
     * 当帧使用这个字典作为UserInfo显示时，AnimationFrameDisplayedNotification通知将会被广播。
     * 如果UserInfo是空,那么不会有广播通知。
     * 
     * @return @~english A dictionary as UserInfo
     * @~chinese 一个作为UserInfo的字典
     */
    const ValueMap& getUserInfo() const { return _userInfo; };
    ValueMap& getUserInfo() { return _userInfo; };
    
    /** @~english Sets user infomation.
     * @~chinese 设置用户信息。
     * @param userInfo @~english A dictionary as UserInfo.
     * @~chinese 一个作为UserInfo的字典
     */
    void setUserInfo(const ValueMap& userInfo)
    {
        _userInfo = userInfo;
    }
    
    // Overrides
	virtual AnimationFrame *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    AnimationFrame();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~AnimationFrame();
    
    /** @~english initializes the animation frame with a spriteframe, number of delay units and a notification user info
     * @~chinese 使用精灵帧,时间和用户信息通知的数量初始化动画帧。
     */
    bool initWithSpriteFrame(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo);

protected:
    
    /** @~english SpriteFrameName to be used  @~chinese 待使用的SpriteFrameName*/
    SpriteFrame* _spriteFrame;

    /**  @~english how many units of time the frame takes  @~chinese 帧花费的时间*/
    float _delayUnits;

    /**  @~english A AnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this dictionary as UserInfo. If UserInfo is nil, then no notification will be broadcast.  、
     * @~chinese 当帧使用这个字典作为UserInfo显示时，AnimationFrameDisplayedNotification通知将会被广播。如果UserInfo是空,那么不会有广播通知。*/
    ValueMap _userInfo;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(AnimationFrame);
};


/** @class Animation
 * @~english A Animation object is used to perform animations on the Sprite objects.
 * The Animation object contains AnimationFrame objects, and a possible delay between the frames.
 * You can animate a Animation object by using the Animate action. Example:
 * @~chinese 一个给精灵对象执行的帧动画对象。
 * 帧动画对象包含动画帧对象，和帧间时长。
 * 你你可以使用一个Animate运动来包含一个Animation对象。
 * @code
 * sprite->runAction(Animate::create(animation));
 * @endcode
*/
class CC_DLL Animation : public Ref, public Clonable
{
public:
    /** @~english Creates an animation.
     * @~chinese 创建一个动画。
     * @since v0.99.5
     */
    static Animation* create(void);

    /* @~english Creates an animation with an array of SpriteFrame and a delay between frames in seconds.
     * The frames will be added with one "delay unit".
     * @~chinese 使用一组SpriteFrame和帧间时长创建一个动画。
     * 每个时间之间将会添加一个帧。
     * @since v0.99.5
     * @param arrayOfSpriteFrameNames @~english An array of SpriteFrame.
     * @~chinese 一组SpriteFrame。
     * @param delay @~english A delay between frames in seconds.
     * @~chinese 帧之间的延迟秒。
     * @param loops @~english The times the animation is going to loop.
     * @~chinese 循环次数。
     */
    static Animation* createWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);

    /* @~english Creates an animation with an array of AnimationFrame, the delay per units in seconds and and how many times it should be executed.
     * @~chinese 使用一组AnimationFrame,帧间延迟秒数和执行次数来创建一个动画。
     * @since v2.0
     * @param arrayOfAnimationFrameNames @~english An animation with an array of AnimationFrame.
     * @~chinese 一组AnimationFrame。
     * @param delayPerUnit @~english The delay per units in seconds and and how many times it should be executed.
     * @~chinese 帧间延迟秒数和执行次数来创建一个动画。
     * @param loops @~english The times the animation is going to loop.
     * @~chinese 循环次数。
     */
    static Animation* create(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops = 1);

    /** @~english Adds a SpriteFrame to a Animation.
     *
     * @~chinese 添加一个SpriteFrame到动画中。
     * 
     * @param frame @~english The frame will be added with one "delay unit".
     * @~chinese 时间间隔，将会添加一帧。
     */
    void addSpriteFrame(SpriteFrame *frame);

    /** @~english Adds a frame with an image filename. Internally it will create a SpriteFrame and it will add it.
     * The frame will be added with one "delay unit".
     * Added to facilitate the migration from v0.8 to v0.9.
     * @~chinese 使用图片名添加一个帧。内部将会创建一个SpriteFrame并添加它。
     * 时间间隔，将会添加一帧。
     * Added to facilitate the migration from v0.8 to v0.9.
     * @param filename @~english The path of SpriteFrame.
     * @~chinese SpriteFrame的路径。
     */
    void addSpriteFrameWithFile(const std::string& filename);
    /**
     * @deprecated. Use addSpriteFrameWithFile() instead.
	 @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void addSpriteFrameWithFileName(const std::string& filename){ addSpriteFrameWithFile(filename);}

    /** @~english Adds a frame with a texture and a rect. Internally it will create a SpriteFrame and it will add it.
     * The frame will be added with one "delay unit".
     * Added to facilitate the migration from v0.8 to v0.9.
     * @~chinese 使用纹理和对应矩形添加一个帧。内部将会创建一个SpriteFrame并添加它。
     * 时间间隔，将会添加一帧。。
     * 
     * @param pobTexture @~english A frame with a texture.
     * @~chinese 帧纹理。
     * @param rect @~english The Texture of rect.
     * @~chinese 纹理对应矩形
     */
    void addSpriteFrameWithTexture(Texture2D* pobTexture, const Rect& rect);

    /** @~english Gets the total Delay units of the Animation. 
     *
     * @~chinese 获取动画总时间。
     * 
     * @return @~english The total Delay units of the Animation.
     * @~chinese 动画总时间。
     */
    float getTotalDelayUnits() const { return _totalDelayUnits; };
    
    /** @~english Sets the delay in seconds of the "delay unit".
     *
     * @~chinese 总时间，以秒为单位。
     * 
     * @param delayPerUnit @~english The delay in seconds of the "delay unit".
     * @~chinese 总时间，以秒为单位。
     */
    void setDelayPerUnit(float delayPerUnit) { _delayPerUnit = delayPerUnit; };
    
    /** @~english Gets the delay in seconds of the "delay unit".
     * 
     * @~chinese 设置时间，以秒为单位。
     * 
     * @return @~english The delay in seconds of the "delay unit".
     * @~chinese  时间，以秒为单位。
     */
    float getDelayPerUnit() const { return _delayPerUnit; };

    
    /** @~english Gets the duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit.
     *
     * @~chinese 获取整个动画的持续时间，以秒为单位。这是totalDelayUnits * delayPerUnit的结果。
     * 
     * @return @~english Result of totalDelayUnits * delayPerUnit.
     * @~chinese totalDelayUnits * delayPerUnit的结果。
     */
    float getDuration() const;
    
    /** @~english Gets the array of AnimationFrames.
     * 
     * @~chinese 获取AnimationFrames数组。
     * 
     * @return @~english The array of AnimationFrames.
     * @~chinese AnimationFrames数组。
     */
    const Vector<AnimationFrame*>& getFrames() const { return _frames; };
    
    /** @~english Sets the array of AnimationFrames. 
     *
     * @~chinese 设置AnimationFrames数组。
     * 
     * @param frames @~english The array of AnimationFrames.
     * @~chinese AnimationFrames数组。
     */
    void setFrames(const Vector<AnimationFrame*>& frames)
    {
        _frames = frames;
    }
    
    /** @~english Checks whether to restore the original frame when animation finishes. 
     *
     * @~chinese 检查是否在动画结束时恢复至初始帧。
     * 
     * @return @~english Restore the original frame when animation finishes.
     * @~chinese 是否在动画结束时恢复至初始帧。
     */
    bool getRestoreOriginalFrame() const { return _restoreOriginalFrame; };
    
    /** @~english Sets whether to restore the original frame when animation finishes. 
     *
     * @~chinese 设置是否在动画结束时恢复至初始帧。
     * 
     * @param restoreOriginalFrame @~english Whether to restore the original frame when animation finishes.
     * @~chinese 是否在动画结束时恢复至初始帧。
     */
    void setRestoreOriginalFrame(bool restoreOriginalFrame) { _restoreOriginalFrame = restoreOriginalFrame; };
    
    /** @~english Gets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... 
     *
     * @~chinese 获取动画循环次数。0表示动画不执行。1表示动画执行一次,……
     * 
     * @return @~english The times the animation is going to loop.
     * @~chinese 动画循环次数。
     */
    unsigned int getLoops() const { return _loops; };
    
    /** @~english Sets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... 
     *
     * @~chinese 设置动画循环次数。0表示动画不执行。1表示动画执行一次,……
     * 
     * @param loops @~english The times the animation is going to loop.
     * @~chinese 动画循环次数。
     */
    void setLoops(unsigned int loops) { _loops = loops; };
    
    // overrides
	virtual Animation *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    Animation();
    virtual ~Animation(void);
    
    /** @~english Initializes a Animation.  @~chinese 初始化一个动画。*/
    bool init();
    
    /** @~english Initializes a Animation with frames and a delay between frames.
     * @~chinese 使用动画帧与帧之间的延迟初始化动画。
     * @since v0.99.5
     */
    bool initWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);
    
    /** @~english Initializes a Animation with AnimationFrame.
     * @~chinese 使用AnimationFrame初始化动画。
     * @since v2.0
     */
    bool initWithAnimationFrames(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops);

protected:
    /** @~english total Delay units of the Animation.  @~chinese 动画的总时间。*/
    float _totalDelayUnits;

    /** @~english Delay in seconds of the "delay unit".  @~chinese “时间，以秒为单位”。*/
    float _delayPerUnit;

    /** @~english duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit.  @~chinese 整个动画的时间，以秒为单位。这是totalDelayUnits * delayPerUnit的结果。*/
    float _duration;

    /** @~english array of AnimationFrames.  @~chinese AnimationFrames数组。*/
    Vector<AnimationFrame*> _frames;

    /** @~english whether or not it shall restore the original frame when the animation finishes.  @~chinese 是否在动画结束时恢复至初始帧。*/
    bool _restoreOriginalFrame;

    /** @~english how many times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ...
     * @~chinese 动画循环次数。0表示动画不执行。1表示动画执行一次,……
     */
    unsigned int _loops;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Animation);
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_ANIMATION_H__
