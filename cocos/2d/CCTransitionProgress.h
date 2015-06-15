/****************************************************************************
Copyright (c) 2009      Lam Pham
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2012      Ricardo Quesada
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
#ifndef __CCTRANSITIONPROGRESS_H__
#define __CCTRANSITIONPROGRESS_H__

#include "2d/CCTransition.h"

NS_CC_BEGIN

class ProgressTimer;
class RenderTexture;

/**
 * @addtogroup _2d
 * @{
 */
/** 
 * @brief @~english A base class of progress transition.
 * @~chinese 一个TransitionScene的子类。
 */
class CC_DLL TransitionProgress : public TransitionScene
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 使用持续时间、传入的场景创建一个过渡.
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english An autoreleased TransitionProgress object.
     * @~chinese autoreleased TransitionProgress对象。
     */
    static TransitionProgress* create(float t, Scene* scene);

    //
    // Overrides
    //
    virtual void onEnter() override;
    virtual void onExit() override;

CC_CONSTRUCTOR_ACCESS:
    TransitionProgress();
    virtual ~TransitionProgress(){}

protected:
    virtual void sceneOrder() override;

protected:
    virtual ProgressTimer* progressTimerNodeWithRenderTexture(RenderTexture* texture);
    virtual void setupTransition();

protected:
    float _to;
    float _from;
    Scene* _sceneToBeModified;
};


/** 
 * @brief @~english TransitionRadialCCW transition.
 A counter clock-wise radial transition to the next scene
 * @~chinese TransitionRadialCCW过渡。
 * 逆时针放射状过渡到下一个场景
 */
class CC_DLL TransitionProgressRadialCCW : public TransitionProgress
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 使用持续时间、传入的场景创建一个逆时针放射状过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english An autoreleased TransitionProgressRadialCCW object.
     * @~chinese autoreleased TransitionProgressRadialCCW对象。
     */
    static TransitionProgressRadialCCW* create(float t, Scene* scene);

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    TransitionProgressRadialCCW(){}
    virtual ~TransitionProgressRadialCCW(){}

protected:
    //
    // Overrides
    //
    virtual ProgressTimer* progressTimerNodeWithRenderTexture(RenderTexture* texture) override;
  
};


/** 
 * @brief @~english TransitionRadialCW transition.
 A counter clock-wise radial transition to the next scene.
 * @~chinese TransitionRadialCW过渡。
 * 逆时针放射状过渡到下一个场景
*/
class CC_DLL TransitionProgressRadialCW : public TransitionProgress
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 使用持续时间、传入的场景创建一个逆时针放射状过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english An autoreleased TransitionProgressRadialCW object.
     * @~chinese autoreleased TransitionProgressRadialCW对象。
     */
    static TransitionProgressRadialCW* create(float t, Scene* scene);

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    TransitionProgressRadialCW(){}
    virtual ~TransitionProgressRadialCW(){}

protected:
    //
    // Overrides
    //
    virtual ProgressTimer* progressTimerNodeWithRenderTexture(RenderTexture* texture) override;

};

/** 
  * @brief @~english TransitionProgressHorizontal transition.
 A  clock-wise radial transition to the next scene
 * @~chinese TransitionProgressHorizontal过渡。
 * 顺时针放射状过渡到下一个场景
 */
class CC_DLL TransitionProgressHorizontal : public TransitionProgress
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 使用持续时间、传入的场景创建一个过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english An autoreleased TransitionProgressHorizontal object.
     * @~chinese autoreleased TransitionProgressHorizontal对象。
     */
    static TransitionProgressHorizontal* create(float t, Scene* scene);

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    TransitionProgressHorizontal(){}
    virtual ~TransitionProgressHorizontal(){}

protected:
    //
    // Overrides
    //
    virtual ProgressTimer* progressTimerNodeWithRenderTexture(RenderTexture* texture) override;
};

/** 
 * @brief @~english TransitionProgressVertical transition.
 * @~chinese TransitionProgressVertical 过渡.
 */
class CC_DLL TransitionProgressVertical : public TransitionProgress
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 使用持续时间、传入的场景创建一个过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english An autoreleased TransitionProgressVertical object.
     * @~chinese An autoreleased TransitionProgressVertical object.
     */
    static TransitionProgressVertical* create(float t, Scene* scene);

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    TransitionProgressVertical(){}
    virtual ~TransitionProgressVertical(){}

protected:
    //
    // Overrides
    //
    virtual ProgressTimer* progressTimerNodeWithRenderTexture(RenderTexture* texture) override;
};

/** 
 * @brief @~english TransitionProgressInOut transition.
 * @~chinese TransitionProgressInOut过渡。
 */
class CC_DLL TransitionProgressInOut : public TransitionProgress
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 使用持续时间、传入的场景创建一个过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english An autoreleased TransitionProgressInOut object.
     * @~chinese autoreleased TransitionProgressInOut对象。
     */
    static TransitionProgressInOut* create(float t, Scene* scene);

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    TransitionProgressInOut(){}
    virtual ~TransitionProgressInOut(){}

protected:
    //
    // Overrides
    //
    virtual ProgressTimer* progressTimerNodeWithRenderTexture(RenderTexture* texture) override;
    virtual void sceneOrder() override;
    virtual void setupTransition() override;
};

/** 
 * @brief @~english TransitionProgressOutIn transition.
 * @~chinese TransitionProgressOutIn过渡。
 */
class CC_DLL TransitionProgressOutIn : public TransitionProgress
{
public:
    /** @~english Creates a transition with duration and incoming scene.
     *
     * @~chinese 使用持续时间、传入的场景创建一个过渡。
     * 
     * @param t @~english Duration time, in seconds.
     * @~chinese 持续时间,以秒为单位。
     * @param scene @~english A given scene.
     * @~chinese 一个给定的场景。
     * @return @~english An autoreleased TransitionProgressOutIn object.
     * @~chinese autoreleased TransitionProgressOutIn对象。
     */
    static TransitionProgressOutIn* create(float t, Scene* scene);

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    TransitionProgressOutIn(){}
    virtual ~TransitionProgressOutIn(){}

protected:
    //
    // Overrides
    //
    virtual ProgressTimer* progressTimerNodeWithRenderTexture(RenderTexture* texture) override;

};

// end of _2d group
/// @}

NS_CC_END

#endif /* __CCTRANSITIONPROGRESS_H__ */
