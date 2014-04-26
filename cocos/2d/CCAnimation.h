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
#include "base/CCGeometry.h"
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
 A frame of the animation. It contains information like:
    - sprite frame name
    - # of delay units.
    - offset
 
 @since v2.0
 */
class CC_DLL AnimationFrame : public Ref, public Clonable
{
public:
    /**
     * Creates the animation frame with a spriteframe, number of delay units and a notification user info
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

    /** Gets the units of time the frame takes */
    float getDelayUnits() const { return _delayUnits; };
    
    /** Sets the units of time the frame takes */ 
    void setDelayUnits(float delayUnits) { _delayUnits = delayUnits; };
    
    /** @brief Gets user infomation
        A AnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this dictionary as UserInfo. If UserInfo is nil, then no notification will be broadcast.
     */
    const ValueMap& getUserInfo() const { return _userInfo; };
    ValueMap& getUserInfo() { return _userInfo; };
    
    /** Sets user infomation */
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
    
    /** initializes the animation frame with a spriteframe, number of delay units and a notification user info */
    bool initWithSpriteFrame(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo);

protected:
    
    /** SpriteFrameName to be used */
    SpriteFrame* _spriteFrame;

    /**  how many units of time the frame takes */
    float _delayUnits;

    /**  A AnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this dictionary as UserInfo. If UserInfo is nil, then no notification will be broadcast. */
    ValueMap _userInfo;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(AnimationFrame);
};




/** A Animation object is used to perform animations on the Sprite objects.

The Animation object contains AnimationFrame objects, and a possible delay between the frames.
You can animate a Animation object by using the Animate action. Example:

@code
    sprite->runAction(Animate::create(animation));
@endcode

*/
class CC_DLL Animation : public Ref, public Clonable
{
public:
    /** Creates an animation
     @since v0.99.5
     */
    static Animation* create(void);

    /* Creates an animation with an array of SpriteFrame and a delay between frames in seconds.
     The frames will be added with one "delay unit".
     @since v0.99.5
     */
    static Animation* createWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);

    /* Creates an animation with an array of AnimationFrame, the delay per units in seconds and and how many times it should be executed.
     @since v2.0
     * @js NA
     */
    static Animation* create(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops = 1);

    /** Adds a SpriteFrame to a Animation.
     The frame will be added with one "delay unit".
     */
    void addSpriteFrame(SpriteFrame *frame);

    /** Adds a frame with an image filename. Internally it will create a SpriteFrame and it will add it.
     The frame will be added with one "delay unit".
     Added to facilitate the migration from v0.8 to v0.9.
     */
    void addSpriteFrameWithFile(const std::string& filename);
    /**
     @deprecated. Use addSpriteFrameWithFile() instead
     */
    CC_DEPRECATED_ATTRIBUTE void addSpriteFrameWithFileName(const std::string& filename){ addSpriteFrameWithFile(filename);}

    /** Adds a frame with a texture and a rect. Internally it will create a SpriteFrame and it will add it.
     The frame will be added with one "delay unit".
     Added to facilitate the migration from v0.8 to v0.9.
     */
    void addSpriteFrameWithTexture(Texture2D* pobTexture, const Rect& rect);

    /** Gets the total Delay units of the Animation. */
    float getTotalDelayUnits() const { return _totalDelayUnits; };
    
    /** Sets the delay in seconds of the "delay unit" */
    void setDelayPerUnit(float delayPerUnit) { _delayPerUnit = delayPerUnit; };
    
    /** Gets the delay in seconds of the "delay unit" */
    float getDelayPerUnit() const { return _delayPerUnit; };

    
    /** Gets the duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit */
    float getDuration() const;
    
    /** Gets the array of AnimationFrames */
    const Vector<AnimationFrame*>& getFrames() const { return _frames; };
    
    /** Sets the array of AnimationFrames */
    void setFrames(const Vector<AnimationFrame*>& frames)
    {
        _frames = frames;
    }
    
    /** Checks whether to restore the original frame when animation finishes. */
    bool getRestoreOriginalFrame() const { return _restoreOriginalFrame; };
    
    /** Sets whether to restore the original frame when animation finishes */
    void setRestoreOriginalFrame(bool restoreOriginalFrame) { _restoreOriginalFrame = restoreOriginalFrame; };
    
    /** Gets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... */
    unsigned int getLoops() const { return _loops; };
    
    /** Sets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... */
    void setLoops(unsigned int loops) { _loops = loops; };
    
    // overrides
	virtual Animation *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    Animation();
    virtual ~Animation(void);
    
    /** Initializes a Animation */
    bool init();
    
    /** Initializes a Animation with frames and a delay between frames
     @since v0.99.5
     */
    bool initWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);
    
    /** Initializes a Animation with AnimationFrame
     @since v2.0
     */
    bool initWithAnimationFrames(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops);

protected:
    /** total Delay units of the Animation. */
    float _totalDelayUnits;

    /** Delay in seconds of the "delay unit" */
    float _delayPerUnit;

    /** duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit */
    float _duration;

    /** array of AnimationFrames */
    Vector<AnimationFrame*> _frames;

    /** whether or not it shall restore the original frame when the animation finishes */
    bool _restoreOriginalFrame;

    /** how many times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... */
    unsigned int _loops;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Animation);
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_ANIMATION_H__
