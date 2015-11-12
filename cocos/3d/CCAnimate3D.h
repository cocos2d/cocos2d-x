/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCANIMATE3D_H__
#define __CCANIMATE3D_H__

#include <map>
#include <unordered_map>

#include "3d/CCAnimation3D.h"
#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "2d/CCActionInterval.h"

NS_CC_BEGIN

/**
* @addtogroup _3d
* @{
*/
class Bone3D;
class Sprite3D;
class EventCustom;

/**
 * @enum Animate3DQuality
 * @brief @~english This enum control the animation's quality.
 * @~chinese 该枚举用于控制动画的质量
 */
enum class Animate3DQuality
{
    /**
     * @~english It'll be ignore the curve-evaluating(the animation looks like stop), just acculate transition time.
     * @~chinese 忽略动画播放时的曲线求解（插值），动画会有卡顿，仅能加速动画过渡时间
     **/
    QUALITY_NONE = 0, 

    /**
    * @~english Low animation quality, it'll be more efficient.
    * @~chinese 低动画质量，较高动画质量而言，效率更高
    **/
    QUALITY_LOW, 

    /**
    * @~english High animation quality, which also means more cpu time occupy.
    * @~chinese 高动画质量，效果最好，同时也意味着更多的CPU时间占用
    **/
    QUALITY_HIGH,              
};



/**
 * @class Animate3D
 * @brief @~english Animate3D, Animates a Sprite3D given with an Animation3D
 * @~chinese Animate3D 通过指定的Animation3D创建的动作，用以给Sprite3D播放动画
 */
class CC_DLL Animate3D: public ActionInterval
{
public:
    
    /**
     * @~english Create Animate3D using Animation.
     * @~chinese 使用Animation3D来创建Animate3D对象
     * @param animation @~english The specified Animation3D object.
     * @~chinese 指定的Animation3D对象
     * @return @~english The Animate3D object.
     * @~chinese 被创建的Animate3D对象
     */
    static Animate3D* create(Animation3D* animation);
    
    /**
     * @~english create Animate3D
     * @~chinese 通过Animation3D对象，开始时间，以及持续时间来构造Animate3D
     * @param animation @~english Animation used to generate animate3D
     * @~chinese 指定的Animation3D对象
     * @param fromTime @~english FormTime. 
     * @~chinese 开始时间
     * @param duration @~english Duration Time the Animate3D lasts.
     * @~chinese 动画播放的持续时间
     * @return @~english The Animate3D object.
     * @~chinese 被创建的Animate3D对象
     */
    static Animate3D* create(Animation3D* animation, float fromTime, float duration);
    
    /**
     * @~english Create Animate3D by frame section, [startFrame, endFrame)
     * @~chinese 通过Animation3D，起始帧，结束帧，以及帧率来创建Animate3D对象
     * @param animation @~english Animation used to generate animate3D
     * @~chinese Animation3D对象
     * @param startFrame @~english The start frame.
     * @~chinese 起始帧
     * @param endFrame @~english The end frame
     * @~chinese 结束帧
     * @param frameRate @~english The frameRate, default is 30 per second
     * @~chinese 帧率，默认是三十帧每秒
     * @return @~english Animate3D created using animate
     * @~chinese 被创建的Animate3D对象
     */
    static Animate3D* createWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate = 30.f);
    
    //
    // Overrides
    //
    virtual void stop() override;
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual Animate3D* reverse() const override;
    virtual Animate3D *clone() const override;
    
    virtual void update(float t) override;
    
    /**
     * @~english Get speed, negative speed means playing reverse 
     * @~chinese 获取播放速度，负数的速度意味着动画正在倒放
     * @return @~english The speed
     * @~chinese 速度
     */
    float getSpeed() const;

    /**
    * @~english Set speed, negative speed means playing reverse
    * @~chinese 设置播放速度，负数的速度意味着动画将会倒放
    * @param speed @~english the speed
    * @~chinese 速度
    */
    void setSpeed(float speed);
    
    /**
     * Get the blend weight
     * @~chinese 获取动画混合权重
     * @return the blend weight
     * @~chinese 
     */
    float getWeight() const { return _weight; }

    /**
     * @~english Set the blend weight. It is internally used currently. For example, Sprite3D is playing an Animate3D,
     * and then another Animate3D is going to be played. This function will be used to make the transition from on 
     * Animate3D to another smoothly. 
     * @~chinese 设置动画混合权重，该函数目前仅在内部使用，举例来说，当一个Sprite3D对象处在播放一个动画同时另一个动画即将要被播放的情形下，
     * 该函数将被用来调整从一个动画到另一个动画之间的过渡.
     * @param weight @~english The blend weight, the blend weight must be positive
     * @~chinese 权重，权值必须为正
     */
    void setWeight(float weight);
    
    /**
     * @~english Set origin interval.
     * @~chinese 设置初始播放间隔
     * @param interval @~english The new interval
     * @~chinese 新的播放间隔
     */
    void setOriginInterval(float interval);

    /**
    * @~english Get origin interval
    * @~chinese 获取初始播放间隔
    * @return @~english Get the origin interval.
    * @~chinese 播放间隔
    */
    float getOriginInterval() const {return _originInterval; }
    
    /**
     * @~english Get animate transition time between 3d animations
     * @~chinese 获取动画之间的过渡时间
     * @return @~english The tarnsition time.
     * @~chinese 过渡时间
     */
    static float getTransitionTime() { return _transTime; }
    
    /**
     * @~english Set animate transition time between 3d animations
     * @~chinese 设置动画之间的过渡时间
     * @param transTime @~english The transition time
     * @~chinese 新过渡时间
     */
    static void setTransitionTime(float transTime) { if (transTime >= 0.f) _transTime = transTime; }
    
    /**get & set play reverse, these are deprecated, use set negative speed instead*/
    CC_DEPRECATED_ATTRIBUTE bool getPlayBack() const { return _playReverse; }
    CC_DEPRECATED_ATTRIBUTE void setPlayBack(bool reverse) { _playReverse = reverse; }
    
    /**
     * @~english Set the animate quality, see also Animate3DQuality
     * @~chinese 设置动画质量，关于动画质量的详情请见Animate3DQuality枚举
     * @param quality @~english The animate quality
     * @~chinese 动画质量的枚举
     * */
    void setQuality(Animate3DQuality quality);
    
    /**
     * @~english Get animate quality, see also Animate3DQuality
     * @~chinese 获取当前动画的动画质量，光宇动画质量的详情请见Animate3DQuality枚举
     * @return @~english The animate quality
     * @~chinese 动画质量的枚举
     **/
    Animate3DQuality getQuality() const;


    struct Animate3DDisplayedEventInfo
    {
        int frame;
        Node* target;
        const ValueMap* userInfo;
    };
    void setKeyFrameUserInfo(int keyFrame, const ValueMap &userInfo);
    const ValueMap* getKeyFrameUserInfo(int keyFrame) const;
    ValueMap* getKeyFrameUserInfo(int keyFrame);
    

    
CC_CONSTRUCTOR_ACCESS:
    
    Animate3D();
    virtual ~Animate3D();
    
    /**
    * @~english Remove this action from map
    * @~chinese 从map中删除当前action
    */
    void removeFromMap();
    
    /** 
     * @~english Init method, init from the specified animation.
     * @~chinese 通过指定的Animation3D对象初始化
     * @param animation @~english The specified animation.
     * @~chinese 指定的Animation3D对象
     * @return @~english Return true if success, otherwise return false.
     * @~chinese 当初始化成功时返回true,反之返回false
     */
    bool init(Animation3D* animation);

    /** 
     * @~english Init method, init from the start time and duration.
     * @~chinese 初始化函数，通过开始时间以及持续时间初始化
     * @param animation @~english The specified animation.
     * @~chinese 指定的Animation3D对象
     * @param fromTime @~english The start time.
     * @~chinese 开始时间
     * @param duration @~english The animate's duration
     * @~chinese 动画持续时间
     * @return @~english Return true if success, otherwise return false.
     * @~chinese 当初始化成功时返回true,反之返回false
     */
    bool init(Animation3D* animation, float fromTime, float duration);

    /**
    * @~english Init with frames
    * @~chinese 通过起始帧，结束帧，帧率来创建动画
    * @param animation @~english The specified animation
    * @~chinese 指定的Animation3D对象
    * @param startFrame @~english The start frame
    * @~chinese 起始帧
    * @param endFrame @~english The end frame
    * @~chinese 结束帧
    * @param frameRate @~english The frame rate
    * @~chinese 帧率
    * @return @~english Return true if success, otherwise return false.
    * @~chinese 当初始化成功时返回true,反之返回false
    */
    bool initWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate);
    
protected:
    
    enum class Animate3DState
    {
        FadeIn,
        FadeOut,
        Running,
    };
    Animate3DState _state; //animation state
    Animation3D* _animation; //animation data

    float      _absSpeed; //playing speed
    float      _weight; //blend weight
    float      _start; //start time 0 - 1, used to generate sub Animate3D
    float      _last; //last time 0 - 1, used to generate sub Animate3D
    bool       _playReverse; // is playing reverse
    static float      _transTime; //transition time from one animate3d to another
    float      _accTransTime; // accumulate transition time
    float      _lastTime;     // last t (0 - 1)
    float      _originInterval;// save origin interval time
    float      _frameRate;
    
    // animation quality
    EvaluateType _translateEvaluate;
    EvaluateType _roteEvaluate;
    EvaluateType _scaleEvaluate;
    Animate3DQuality _quality;
    
    std::unordered_map<Bone3D*, Animation3D::Curve*> _boneCurves; //weak ref
    std::unordered_map<Node*, Animation3D::Curve*> _nodeCurves;
    
    std::unordered_map<int, ValueMap> _keyFrameUserInfos;
    std::unordered_map<int, EventCustom*> _keyFrameEvent;
    std::unordered_map<int, Animate3DDisplayedEventInfo> _displayedEventInfo;

    //sprite animates
    static std::unordered_map<Node*, Animate3D*> s_fadeInAnimates;
    static std::unordered_map<Node*, Animate3D*> s_fadeOutAnimates;
    static std::unordered_map<Node*, Animate3D*> s_runningAnimates;
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCANIMATE3D_H__
