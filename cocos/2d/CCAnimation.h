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

#include "base/CCPlatformConfig.h"
#include "base/CCRef.h"
#include "base/CCValue.h"
#include "math/CCGeometry.h"
#include "2d/CCSpriteFrame.h"
#include "base/CCVector.h"

#include <string>

NS_CC_BEGIN

class Texture2D;
class SpriteFrame;

/**
 * @addtogroup sprite_nodes
 * @{
 */

/** AnimationFrame
 动画帧
 动画的一帧. 它包含以下信息:
    - 精灵帧的名称
    - # 延迟时间长度(单位: 秒).
    - 偏移量
 
 @since v2.0
 */
class CC_DLL AnimationFrame : public Ref, public Clonable
{
public:
    
    struct DisplayedEventInfo
    {
        Node* target;
        const ValueMap* userInfo;
    };
    
    /**
     * 用一个精灵帧(spriteframe), 延迟时间长度(delay units) 和 将通知的用户信息(user info)创建并初始化动画帧.  
     * @since 3.0
     */
    static AnimationFrame* create(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo);

    SpriteFrame* getSpriteFrame() const { return _spriteFrame; };
    
    void setSpriteFrame(SpriteFrame* frame)
    {
        CC_SAFE_RETAIN(frame);
        CC_SAFE_RELEASE(_spriteFrame);
        _spriteFrame = frame;
    }

    /** 获取这些帧将要使用的时间长度 */
    float getDelayUnits() const { return _delayUnits; };
    
    /** 设置这些帧将要使用的时间长度 */ 
    void setDelayUnits(float delayUnits) { _delayUnits = delayUnits; };
    
    /** @brief 获取用户信息
        一个通知(AnimationFrameDisplayedNotification 的实例 notification)将被传播, 当这些以字典(Map)方式存储
        用户信息的帧显示时. 如果用户信息是空值(nil), 不会有通知(同上)被广播.
     */
    const ValueMap& getUserInfo() const { return _userInfo; };
    ValueMap& getUserInfo() { return _userInfo; };
    
    /** 设置用户信息 */
    void setUserInfo(const ValueMap& userInfo)
    {
        _userInfo = userInfo;
    }
    
    // 重写方法
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
    
    /** 用一个精灵帧(spriteframe), 延迟时间长度(delay units) 和 将通知的用户信息(user info)初始化动画帧 */
    bool initWithSpriteFrame(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo);

protected:
    
    /** 待使用的精灵帧名称 */
    SpriteFrame* _spriteFrame;

    /** 这些帧播放结束使用的时间长度*/
    float _delayUnits;

    /** 一个通知(AnimationFrameDisplayedNotification 的实例 notification)将被传播, 当这些以字典(Map)方式存储
        用户信息的帧显示时. 如果用户信息是空值(nil), 不会有通知(同上)被广播.
     */
    ValueMap _userInfo;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(AnimationFrame);
};




/** 一个用来在精灵对象上表现动画的动画对象. 

动画对象包含动画帧对象, 还可能有一个设定这些帧之间延迟的参数. 
你可以用动画动作(Animate action)来创建一个动画对象(Animation object):

@code
    sprite->runAction(Animate::create(animation));
@endcode

*/
class CC_DLL Animation : public Ref, public Clonable
{
public:
    /** 创建并初始化一个动画
     @since v0.99.5
     */
    static Animation* create(void);

    /* 用一组(vector)精灵帧(SpriteFrame), 这组精灵帧之间延迟的时间创建并初始化一个动画对象(Animation). 
     这些帧会被添加到一个时间单位(delay unit).
     @since v0.99.5
     */
    static Animation* createWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);

    /* 用一组(vector)精灵帧(SpriteFrame), 每单位时间的延迟和执行次数创建并初始化一个动画对象(Animation).
     @since v2.0
     * @js NA
     */
    static Animation* create(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops = 1);

    /** 添加一个精灵帧到动画中.
     这个帧会以一个单位时间延迟(delay unit)添加.
     */
    void addSpriteFrame(SpriteFrame *frame);

    /** 用图片名称加一个精灵帧到动画中. 此方法内部会创建一个精灵帧然后添加它.
     这个帧会以一个单位时间延迟(delay unit)添加.
     添加这个方法使移植更容易了. from v0.8 to v0.9.
     */
    void addSpriteFrameWithFile(const std::string& filename);
    /**
     @deprecated. 使用 addSpriteFrameWithFile() 替代此方法.
     CC_DEPRECATED_ATTRIBUTE 标记此方法不建议使用. 
     在将来的cocos2d-x中,此方法很有可能会被抛弃,现在保留这个方法只为了向下兼容.
     */
    CC_DEPRECATED_ATTRIBUTE void addSpriteFrameWithFileName(const std::string& filename){ addSpriteFrameWithFile(filename);}

    /** 用一个2D纹理(Texture2D)和矩形添加一个帧. 此方法内部会创建一个精灵帧然后添加它.
     这个帧会以一个单位时间延迟(delay unit)添加.
     添加这个方法使移植更容易了. from v0.8 to v0.9.
     */
    void addSpriteFrameWithTexture(Texture2D* pobTexture, const Rect& rect);

    /** 获取动画的延迟单位时间总数目. */
    float getTotalDelayUnits() const { return _totalDelayUnits; };
    
    /** 设置每单位时间延迟(delay unit). 单位: 秒 */
    void setDelayPerUnit(float delayPerUnit) { _delayPerUnit = delayPerUnit; };
    
    /** 获取每单位时间延迟(delay unit). 单位: 秒*/
    float getDelayPerUnit() const { return _delayPerUnit; };

    
    /** 获取整个动画的持续时间, 单位: 秒.它是总延迟时间单位(totalDelayUnits)的结果. */
    float getDuration() const;
    
    /** 获取一组(vector)动画帧(AnimationFrame) */
    const Vector<AnimationFrame*>& getFrames() const { return _frames; };
    
    /** 设置一组(vector)动画帧(AnimationFrame) */
    void setFrames(const Vector<AnimationFrame*>& frames)
    {
        _frames = frames;
    }
    
    /** 检查当动画结束时,是否要存储这些原始帧. */
    bool getRestoreOriginalFrame() const { return _restoreOriginalFrame; };
    
    /** 设置"当动画结束时,是否要存储这些原始帧". */
    void setRestoreOriginalFrame(bool restoreOriginalFrame) { _restoreOriginalFrame = restoreOriginalFrame; };
    
    /** 获取动画将要循环执行的次数. 0 表示动画不执行. 1 表示动画执行一次, ... */
    unsigned int getLoops() const { return _loops; };
    
    /** 设置动画将要循环执行的次数. 0 表示动画不执行. 1 表示动画执行一次, ... */
    void setLoops(unsigned int loops) { _loops = loops; };
    
    // 重写方法
	virtual Animation *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    Animation();
    virtual ~Animation(void);
    
    /** 初始化一个动画 */
    bool init();
    
    /** 用一组(vector)精灵帧(SpriteFrame), 这组精灵帧之间延迟的时间初始化一个动画对象(Animation).
     @since v0.99.5
     */
    bool initWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);
    
    /** 用一组(vector)动画帧(AnimationFrame)初始化动画帧. 
     @since v2.0
     */
    bool initWithAnimationFrames(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops);

protected:
    /** 动画延迟时间单位的总数. */
    float _totalDelayUnits;

    /** 单位延迟(delay unit)的延迟时间, 单位: 秒. */
    float _delayPerUnit;

    /** 整个动画的持续时间, 单位: 秒.它是总延迟时间单位(totalDelayUnits)的结果. */
    float _duration;

    /** 一组(vector)动画帧(AnimationFrame) */
    Vector<AnimationFrame*> _frames;

    /** 当动画结束时,是否要存储这些原始帧 */
    bool _restoreOriginalFrame;

    /** 动画将要循环执行的次数. 0 表示动画不执行. 1 表示动画执行一次, ... */
    unsigned int _loops;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Animation);
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_ANIMATION_H__
