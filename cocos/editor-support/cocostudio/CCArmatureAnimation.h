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


#ifndef __CCANIMATION_H__
#define __CCANIMATION_H__

#include "cocostudio/CCProcessBase.h"
#include "cocostudio/CCTween.h"
#include "cocostudio/CocosStudioExport.h"
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

typedef void (cocos2d::Ref::*SEL_MovementEventCallFunc)(Armature *, MovementEventType, const std::string&);
typedef void (cocos2d::Ref::*SEL_FrameEventCallFunc)(Bone *, const std::string&, int, int);

#define movementEvent_selector(_SELECTOR) (cocostudio::SEL_MovementEventCallFunc)(&_SELECTOR)
#define frameEvent_selector(_SELECTOR) (cocostudio::SEL_FrameEventCallFunc)(&_SELECTOR)

struct FrameEvent
{
    Bone *bone;
    std::string frameEventName;
    int originFrameIndex;
    int currentFrameIndex;
};

struct MovementEvent
{
    Armature *armature;
    MovementEventType movementType;
    std::string movementID;
};

class  CC_STUDIO_DLL ArmatureAnimation : public ProcessBase
{
public:
    /**
    * @~english Create with a Armature.
    * @~chinese 使用一套骨骼来创建骨骼动画。
    * @param armature  @~english The Armature ArmatureAnimation will bind to.
    * @~chinese 将要绑定动画的骨骼。
    * @return @~english Binded armature animation.
    * @~chinese 已绑定的骨骼动画。
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
    * @~english Init with a Armature.
    * @~chinese 使用一套骨骼进行初始化。
    * @param armature  @~english The Armature ArmatureAnimation will bind to.
    * @~chinese 将要绑定动画的骨骼。
    */
    virtual bool init(Armature *armature);

    /** @deprecated Use `setSpeedScale(float speedScale)` instead */
    CC_DEPRECATED_ATTRIBUTE virtual void setAnimationScale(float animationScale);
    /** @deprecated Use `getSpeedScale()` instead */
    CC_DEPRECATED_ATTRIBUTE virtual float getAnimationScale() const;

    /**
    * @~english Scale animation play speed.
    * @~chinese 缩放动画播放速度。
    * @param speedScale @~english Scale value.
    * @~chinese 动画播放速度缩放值。
    */
    virtual void setSpeedScale(float speedScale);

    /**
    * @~english Get animation play speed scale.
    * @~chinese 获取动画播放速度缩放值。
    * @return @~english Scale value.
    * @~chinese 动画播放速度缩放值。
    */
    virtual float getSpeedScale() const;

    using ProcessBase::play;
    /**
    * @~english Play animation by animation name.
    * @~chinese 根据动画名称播放动画。
    * @param  animationName  @~english The animation name you want to play
    * @~chinese 要播放的动画名称。
    * @param  durationTo @~english The frames between two animation changing-over.
    *         It's meaning is changing to this animation need how many frames
    *         -1 : use the value from MovementData get from flash design panel
    * @~chinese 两个动画切换时的需要的帧数。意味着切换到该动画时需要多少帧。
    *    -1：使用Flash的设计面板中MovementData中的值
    * @param  loop @~english  Whether the animation is loop
    *         loop < 0 : use the value from MovementData get from flash design panel
    *         loop = 0 : this animation is not loop
    *         loop > 0 : this animation is loop
    * @~chinese 动画是否循环。
    *         loop < 0 : 使用Flash的设计面板中MovementData中的值
    *         loop = 0 : 不循环
    *         loop > 0 : 循环
    */
    virtual void play(const std::string& animationName, int durationTo = -1,  int loop = -1);

    /** @deprecated Use `playWithIndex(int animationIndex,  int durationTo, int loop)` instead */
    CC_DEPRECATED_ATTRIBUTE virtual void playByIndex(int animationIndex,  int durationTo = -1, int loop = -1);

    /**
    * @~english Play animation by index, the other param is the same to `play`.
    * @~chinese 根据帧索引播放动画，其余参数含义见`play`。
    * @param  animationIndex  @~english the animation index you want to play.
    * @~chinese 要播放的动画起始帧索引。
    */
    virtual void playWithIndex(int animationIndex,  int durationTo = -1, int loop = -1);

    /**
    * @~english Update movementList and play animation, the other param is the same to `play`.
    * @~chinese 刷新动画列表并播放动画，其余参数含义见`play`。
    * @param movementNames @~english New movement names.
    * @~chinese 新的动画列表名称集合。
    */
    virtual void playWithNames(const std::vector<std::string>& movementNames, int durationTo = -1, bool loop = true);

    /**
    * @~english Update movementList and play animation, the other param is the same to `play`.
    * @~chinese 刷新动画列表并播放动画，其余参数含义见`play`。
    * @param movementIndexes @~english New movement indexes.
    * @~chinese 新的动画列表索引集合。
    */
    virtual void playWithIndexes(const std::vector<int>& movementIndexes, int durationTo = -1, bool loop = true);

    /**
     * @~english Go to specified frame and play current movement.
     * You need first switch to the movement you want to play, then call this function.
     * @~chinese 跳转至指定的帧并从该帧开始播放当前动作。
     *  需要先切换至要播放的动作，再调用该函数。
     * 
     * example : 
     *@code
     *           playByIndex(0);
     *           gotoAndPlay(0);
     *           playByIndex(1);
     *           gotoAndPlay(0);
     *           gotoAndPlay(15);
     *@endcode
     * @param frameIndex @~english Index of frame.
     * @~chinese 要跳转的帧索引。
     */
    virtual void gotoAndPlay(int frameIndex);

    /**
     * @~english Go to specified frame and pause current movement.
     * @~chinese 跳转至指定的帧并暂停当前动作。
     * @param frameIndex @~english Index of frame.
     * @~chinese 要跳转的帧索引。
     */
    virtual void gotoAndPause(int frameIndex);

    virtual void pause() override;
    virtual void resume() override;
    virtual void stop() override;

    /**
    * @~english Get movement count.
    * @~chinese 获得动作数量。
    * @return @~english Movement count.
    * @~chinese 动作数量。
    */
    ssize_t getMovementCount() const;

    virtual void update(float dt) override;

    /**
     * @~english Get current movementID
     * @~chinese 获得当前动作ID
     * @return @~english The name of current movement
     * @~chinese 获得当前动作名称
     */
    std::string getCurrentMovementID() const;

    /** @deprecated Use `setMovementEventCallFunc(std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> listener)` instead */
    CC_DEPRECATED_ATTRIBUTE void setMovementEventCallFunc(cocos2d::Ref *target, SEL_MovementEventCallFunc callFunc);
    /** @deprecated Use `setFrameEventCallFunc(std::function<void(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)> listener)` instead */
    CC_DEPRECATED_ATTRIBUTE void setFrameEventCallFunc(cocos2d::Ref *target, SEL_FrameEventCallFunc callFunc);
    
    /**
    * @~english Set armature's movement event callback function.
    * To disconnect this event, just `setMovementEventCallFunc(nullptr, nullptr)`;
    * @~chinese 设置骨骼的动作事件回调函数， 要对该事件取消关联，请调用`setMovementEventCallFunc(nullptr, nullptr);`
    * @param frameIndex @~english Movement event callback function.
    * @~chinese 动作事件回调函数。
    */
    void setMovementEventCallFunc(std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> listener);

    /**
    * @~english Set armature's frame event callback function.
    * To disconnect this event, just `setFrameEventCallFunc(nullptr, nullptr)`;
    * @~chinese 设置骨骼的帧事件回调函数， 要对该事件取消关联，请调用`setFrameEventCallFunc(nullptr, nullptr);`
    * @param frameIndex @~english Frame event callback function.
    * @~chinese 帧事件回调函数。
    */
    void setFrameEventCallFunc(std::function<void(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)> listener);

    /**
    * @~english Set animation data.
    * @~chinese 设置动画数据。
    * @param data @~english Animation data.
    * @~chinese 动画数据。
    */
    virtual void setAnimationData(AnimationData *data) 
    {
        if (_animationData != data)
        {
            CC_SAFE_RETAIN(data);
            CC_SAFE_RELEASE(_animationData);
            _animationData = data; 
        }
    }

    /**
    * @~english Get animation data.
    * @~chinese 获取动画数据。
    * @return @~english Animation data.
    * @~chinese 动画数据。
    */
    virtual AnimationData *getAnimationData() const { return _animationData; }


    /** 
     * @~english Returns a user assigned Object. Similar to userData, but instead of holding a void* it holds an object
     * @~chinese 返回用户分配的对象，类似于userData，但并非void*而是一个对象。
     * @return @~english A user assigned Object
     * @~chinese 用户分配的对象。
     * @js NA
     * @lua NA
     */
    virtual Ref* getUserObject() { return _userObject; }
    /** 
    * @js NA
    * @lua NA
    */
    virtual const Ref* getUserObject() const { return _userObject; }

    /**
     * @~english Returns a user assigned Object. Similar to UserData, but instead of holding a void* it holds an object.
     * The UserObject will be retained once in this method, and the previous UserObject (if existed) will be relese.
     * The UserObject will be released in Node's destructure.
     * @~chinese 返回用户分配的对象，类似于userData，但并非void*而是一个对象。
     * 用户对象将在该方法中保留一次，同时上一个用户对象（如果存在）将被释放。
     * 用户对象会在节点的析构函数中释放。
     *
     * @param userObject  @~english  A user assigned Object
     * @~chinese 返回用户分配的对象。
     */
    virtual void setUserObject(Ref *userObject);
protected:

    /**
     * Update(float dt) will call this handler, you can handle your logic here
     * @js NA
     * @lua NA
     */
    void updateHandler() override;

    /**
     * Update current key frame, and process auto stop, pause
     * @js NA
     * @lua NA
     */
    void updateFrameData(float currentPercent);

    /**
     * Emit a frame event
     * @js NA
     * @lua NA
     */
    void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);

    /**
     * Emit a movement event
     */
    void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);

    void updateMovementList();

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

    cocos2d::Vector<Tween*> _tweenList;

    bool _ignoreFrameEvent;
    
    std::queue<FrameEvent*> _frameEventQueue;
    std::queue<MovementEvent*> _movementEventQueue;

    std::vector<std::string> _movementList;
    
    bool _onMovementList;
    bool _movementListLoop;
    unsigned int _movementIndex;
    int _movementListDurationTo;

    cocos2d::Ref *_userObject;
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


    cocos2d::Ref *_movementEventTarget;
    cocos2d::Ref *_frameEventTarget;
    
    
    std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> _movementEventListener;
    std::function<void(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)> _frameEventListener;
};

}

#endif /*__CCANIMATION_H__*/
