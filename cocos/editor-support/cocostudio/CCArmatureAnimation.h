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


#ifndef __CCANIMATION_H__
#define __CCANIMATION_H__

#include "cocostudio/CCProcessBase.h"
#include <queue>

namespace cocostudio {


enum MovementEventType
{
    START,
    COMPLETE,
    LOOP_COMPLETE
};


class Armature;
class Bone;

typedef void (cocos2d::Object::*SEL_MovementEventCallFunc)(Armature *, MovementEventType, const char *);
typedef void (cocos2d::Object::*SEL_FrameEventCallFunc)(Bone *, const char *, int, int);

#define movementEvent_selector(_SELECTOR) (cocostudio::SEL_MovementEventCallFunc)(&_SELECTOR)
#define frameEvent_selector(_SELECTOR) (cocostudio::SEL_FrameEventCallFunc)(&_SELECTOR)

struct FrameEvent
{
    Bone *bone;
    const char *frameEventName;
    int originFrameIndex;
    int currentFrameIndex;
};

class  ArmatureAnimation : public ProcessBase
{
public:
    /**
     * Create with a Armature
     * @param armature The Armature ArmatureAnimation will bind to
     */
    static ArmatureAnimation *create(Armature *armature);
public:
	/**
     * @js ctor
     */
    ArmatureAnimation();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ArmatureAnimation(void);

    /**
     * Init with a Armature
     * @param armature The Armature ArmatureAnimation will bind to
     */
    virtual bool init(Armature *armature);

    /**
     * Scale animation play speed.
     * This method is deprecated, please use setSpeedScale.
     * @param animationScale Scale value
     */
    CC_DEPRECATED_ATTRIBUTE virtual void setAnimationScale(float animationScale);
    CC_DEPRECATED_ATTRIBUTE virtual float getAnimationScale() const;

    /**
     * Scale animation play speed.
     * @param animationScale Scale value
     */
    virtual void setSpeedScale(float speedScale);
    virtual float getSpeedScale() const;

    //! The animation update speed
    virtual void setAnimationInternal(float animationInternal);

    using ProcessBase::play;
    /**
     * Play animation by animation name.
     *
     * @param  animationName  The animation name you want to play
     * @param  durationTo The frames between two animation changing-over.
     *         It's meaning is changing to this animation need how many frames
     *
     *         -1 : use the value from MovementData get from flash design panel
     * @param  durationTween  The frame count you want to play in the game.
     *         if  _durationTween is 80, then the animation will played 80 frames in a loop
     *
     *         -1 : use the value from MovementData get from flash design panel
     *
     * @param  loop   Whether the animation is loop
     *
     *         loop < 0 : use the value from MovementData get from flash design panel
     *         loop = 0 : this animation is not loop
     *         loop > 0 : this animation is loop
     *
     * @param  tweenEasing Tween easing is used for calculate easing effect
     *
     *         TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
     *         -1 : fade out
     *         0  : line
     *         1  : fade in
     *         2  : fade in and out
     *
     */
    void play(const char *animationName, int durationTo = -1, int durationTween = -1,  int loop = -1, int tweenEasing = TWEEN_EASING_MAX);

    /**
     * Play animation by index, the other param is the same to play.
     * @param  animationIndex  the animation index you want to play
     */
    void playByIndex(int animationIndex,  int durationTo = -1, int durationTween = -1,  int loop = -1, int tweenEasing = TWEEN_EASING_MAX);

    /**
     * Go to specified frame and play current movement.
     * You need first switch to the movement you want to play, then call this function.
     * 
     * example : playByIndex(0);
     *           gotoAndPlay(0);
     *           playByIndex(1);
     *           gotoAndPlay(0);
     *           gotoAndPlay(15);
     */
    virtual void gotoAndPlay(int frameIndex);

    /**
     * Go to specified frame and pause current movement.
     */
    virtual void gotoAndPause(int frameIndex);

    /**
     * Pause the Process
     */
    virtual void pause();
    /**
     * Resume the Process
     */
    virtual void resume();
    /**
     * Stop the Process
     */
    virtual void stop();


    /**
     * Get movement count
     */
    int getMovementCount() const;

    void update(float dt);

    /**
     * Get current movementID
     * @return The name of current movement
     */
    std::string getCurrentMovementID() const;

    /**
     * Set armature's movement event callback function
     * To disconnect this event, just setMovementEventCallFunc(nullptr, nullptr);
     */
    void setMovementEventCallFunc(cocos2d::Object *target, SEL_MovementEventCallFunc callFunc);

    /**
     * Set armature's frame event callback function
     * To disconnect this event, just setFrameEventCallFunc(nullptr, nullptr);
     */
    void setFrameEventCallFunc(cocos2d::Object *target, SEL_FrameEventCallFunc callFunc);

    virtual void setAnimationData(AnimationData *data) 
    {
        if (_animationData != data)
        {
            CC_SAFE_RETAIN(data);
            CC_SAFE_RELEASE(_animationData);
            _animationData = data; 
        }
    }
    virtual AnimationData *getAnimationData() const { return _animationData; }


    /** 
     * Returns a user assigned Object
     * 
     * Similar to userData, but instead of holding a void* it holds an object
     *
     * @return A user assigned Object
     * @js NA
     * @lua NA
     */
    virtual Object* getUserObject() { return _userObject; }
    /** 
    * @js NA
    * @lua NA
    */
    virtual const Object* getUserObject() const { return _userObject; }

    /**
     * Returns a user assigned Object
     *
     * Similar to UserData, but instead of holding a void* it holds an object.
     * The UserObject will be retained once in this method,
     * and the previous UserObject (if existed) will be relese.
     * The UserObject will be released in Node's destructure.
     *
     * @param userObject    A user assigned Object
     */
    virtual void setUserObject(Object *userObject);
protected:

    /**
     * Update(float dt) will call this handler, you can handle your logic here
     */
    void updateHandler();

    /**
     * Update current key frame, and process auto stop, pause
     */
    void updateFrameData(float currentPercent);

    /**
     * Emit a frame event
     */
    void frameEvent(Bone *bone, const char *frameEventName, int originFrameIndex, int currentFrameIndex);

    bool isIgnoreFrameEvent() const { return _ignoreFrameEvent; }

    friend class Tween;
protected:
    //! AnimationData save all MovementDatas this animation used.
    AnimationData *_animationData;

    //! Scale the animation speed
    float _speedScale;

    MovementData *_movementData;				//! MovementData save all MovementFrameDatas this animation used.

    Armature *_armature;						//! A weak reference of armature

    std::string _movementID;				//! Current movment's name

    int _toIndex;								//! The frame index in MovementData->m_pMovFrameDataArr, it's different from m_iFrameIndex.

    cocos2d::Array *_tweenList;

    bool _ignoreFrameEvent;
    
    std::queue<FrameEvent*> _frameEventQueue;

    cocos2d::Object *_userObject;
protected:
    /**
     * MovementEvent CallFunc.
     * @param Armature* a Armature
     * @param MovementEventType, Event Type, like START, COMPLETE.
     * @param const char*, Movement ID, also called Movement Name
     */
    SEL_MovementEventCallFunc _movementEventCallFunc;

    /**
     * FrameEvent CallFunc.
     * @param Bone*, a Bone
     * @param const char*, the name of this frame event
     * @param int, origin frame index
     * @param int, current frame index, animation may be delayed
     */
    SEL_FrameEventCallFunc _frameEventCallFunc;


    cocos2d::Object *_movementEventTarget;
    cocos2d::Object *_frameEventTarget;
};

}

#endif /*__CCANIMATION_H__*/
