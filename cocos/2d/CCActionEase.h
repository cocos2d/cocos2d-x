/****************************************************************************
Copyright (c) 2008-2009 Jason Booth
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __ACTION_CCEASE_ACTION_H__
#define __ACTION_CCEASE_ACTION_H__

#include "2d/CCActionInterval.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** 
 @brief Base class for Easing actions
 @ingroup Actions
 */
class CC_DLL ActionEase : public ActionInterval
{
public:

    virtual ActionInterval* getInnerAction();

    //
    // 可重载
    //
	virtual ActionEase* clone() const override = 0;
    virtual ActionEase* reverse() const override = 0;
    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
    ActionEase() {}
    virtual ~ActionEase();
    /** 初始化这个延时动作 */
    bool initWithAction(ActionInterval *action);

protected:
    /** 这是延时动作实体 */
    ActionInterval *_inner;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ActionEase);
};

/** 
 @brief Base class for Easing actions with rate parameters
 @ingroup Actions
 */
class CC_DLL EaseRateAction : public ActionEase
{
public:
    /** 设置这个动作的频率值 */
    inline void setRate(float rate) { _rate = rate; }
    /** 获取这个动作频率值 */
    inline float getRate() const { return _rate; }

    //
    // 可重载
    //
	virtual EaseRateAction* clone() const override = 0;
    virtual EaseRateAction* reverse() const override = 0;

CC_CONSTRUCTOR_ACCESS:
    EaseRateAction() {}
    virtual ~EaseRateAction();
    /** 初始化这个延时动作并且设置频率参数值 */
    bool initWithAction(ActionInterval *pAction, float fRate);

protected:
    float _rate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseRateAction);
};

/** 
 @brief EaseIn action with a rate
 @ingroup Actions
 */
class CC_DLL EaseIn : public EaseRateAction
{
public:
    /** 创建这个延时动作并且设置频率参数值 */
    static EaseIn* create(ActionInterval* action, float rate);

    // 可重载
    virtual void update(float time) override;
	virtual EaseIn* clone() const override;
	virtual EaseIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseIn() {}
    virtual ~EaseIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseIn);
};

/** 
 @brief EaseOut action with a rate
 @ingroup Actions
 */
class CC_DLL EaseOut : public EaseRateAction
{
public:
    /** 创建这个延时动作并且设置频率参数值 */
    static EaseOut* create(ActionInterval* action, float rate);

    // Overrides
    virtual void update(float time) override;
	virtual EaseOut* clone() const  override;
	virtual EaseOut* reverse() const  override;

CC_CONSTRUCTOR_ACCESS:
    EaseOut() {}
    virtual ~EaseOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseOut);
};

/** 
 @brief EaseInOut action with a rate
 @ingroup Actions
 */
class CC_DLL EaseInOut : public EaseRateAction
{
public:
    /** 创建这个延时动作并且设置频率参数值 */
    static EaseInOut* create(ActionInterval* action, float rate);

    // 可重载
    virtual void update(float time) override;
	virtual EaseInOut* clone() const  override;
	virtual EaseInOut* reverse() const  override;

CC_CONSTRUCTOR_ACCESS:
    EaseInOut() {}
    virtual ~EaseInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseInOut);
};

/** 
 @brief Ease Exponential In
 @ingroup Actions
 */
class CC_DLL EaseExponentialIn : public ActionEase
{
public:
    /** 创建这个延时动作 */
    static EaseExponentialIn* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseExponentialIn* clone() const override;
	virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseExponentialIn() {}
    virtual ~EaseExponentialIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseExponentialIn);
};

/** 
 @brief Ease Exponential Out
 @ingroup Actions
 */
class CC_DLL EaseExponentialOut : public ActionEase
{
public:
    /** 创建这个延时动作 */
    static EaseExponentialOut* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseExponentialOut* clone() const override;
	virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseExponentialOut() {}
    virtual ~EaseExponentialOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseExponentialOut);
};

/** 
 @brief Ease Exponential InOut
 @ingroup Actions
 */
class CC_DLL EaseExponentialInOut : public ActionEase
{
public:
    /** 创建这个延时动作 */
    static EaseExponentialInOut* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseExponentialInOut* clone() const override;
	virtual EaseExponentialInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseExponentialInOut() {}
    virtual ~EaseExponentialInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseExponentialInOut);
};

/** 
 @brief Ease Sine In
 @ingroup Actions
 */
class CC_DLL EaseSineIn : public ActionEase
{
public:
    /** 创建这个延时动作 */
    static EaseSineIn* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseSineIn* clone() const override;
	virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseSineIn() {}
    virtual ~EaseSineIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseSineIn);
};

/** 
 @brief Ease Sine Out
 @ingroup Actions
 */
class CC_DLL EaseSineOut : public ActionEase
{
public:
    /** 创建这个延时动作 */
    static EaseSineOut* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseSineOut* clone() const override;
	virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseSineOut() {}
    virtual ~EaseSineOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseSineOut);
};

/** 
 @brief Ease Sine InOut
 @ingroup Actions
 */
class CC_DLL EaseSineInOut : public ActionEase
{
public:
    /** 创建这个延时动作 */
    static EaseSineInOut* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseSineInOut* clone() const override;
	virtual EaseSineInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseSineInOut() {}
    virtual ~EaseSineInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseSineInOut);
};

/** 
 @brief Ease Elastic abstract class
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElastic : public ActionEase
{
public:

    /** 获得周期波的弧度值. 默认值为0.3 */
    inline float getPeriod() const { return _period; }
    /** 设置周期波的弧度值. */
    inline void setPeriod(float fPeriod) { _period = fPeriod; }

    //
    // Overrides
    //
	virtual EaseElastic* clone() const override = 0;
	virtual EaseElastic* reverse() const override = 0;

CC_CONSTRUCTOR_ACCESS:
    EaseElastic() {}
    virtual ~EaseElastic() {}
    /** 初始化这个延时动作并且其初始化周期波弧度值默认值为0.3f */
    bool initWithAction(ActionInterval *action, float period = 0.3f);

protected:
    float _period;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElastic);

};

/** 
 @brief Ease Elastic In action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticIn : public EaseElastic
{
public:
    /** 创建这个延时动作并且其初始化周期波弧度值默认值为0.3f */
    static EaseElasticIn* create(ActionInterval *action, float period);
    static EaseElasticIn* create(ActionInterval *action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseElasticIn* clone() const override;
	virtual EaseElastic* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseElasticIn() {}
    virtual ~EaseElasticIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElasticIn);
};

/** 
 @brief Ease Elastic Out action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticOut : public EaseElastic
{
public:
    /** 创建这个延时动作并且其初始化周期波弧度值默认值为0.3f */
    static EaseElasticOut* create(ActionInterval *action, float period);
    static EaseElasticOut* create(ActionInterval *action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseElasticOut* clone() const override;
	virtual EaseElastic* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseElasticOut() {}
    virtual ~EaseElasticOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElasticOut);
};

/** 
 @brief Ease Elastic InOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseElasticInOut : public EaseElastic
{
public:
    /** 创建这个延时动作并且其初始化周期波弧度值默认值为0.3f */
    static EaseElasticInOut* create(ActionInterval *action, float period);
    static EaseElasticInOut* create(ActionInterval *action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseElasticInOut* clone() const override;
	virtual EaseElasticInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseElasticInOut() {}
    virtual ~EaseElasticInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseElasticInOut);
};

/** 
 @brief EaseBounce abstract class.
 @since v0.8.2
 @ingroup Actions
*/
class CC_DLL EaseBounce : public ActionEase
{
public:

    // 可重载
	virtual EaseBounce* clone() const override = 0;
	virtual EaseBounce* reverse() const override = 0;

CC_CONSTRUCTOR_ACCESS:
    EaseBounce() {}
    virtual ~EaseBounce() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBounce);
};

/** 
 @brief EaseBounceIn action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
*/
class CC_DLL EaseBounceIn : public EaseBounce
{
public:
    /** 创建这个延时动作 */
    static EaseBounceIn* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseBounceIn* clone() const override;
	virtual EaseBounce* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBounceIn() {}
    virtual ~EaseBounceIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBounceIn);
};

/** 
 @brief EaseBounceOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBounceOut : public EaseBounce
{
public:
    /** 创建这个延时动作 */
    static EaseBounceOut* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseBounceOut* clone() const override;
	virtual EaseBounce* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBounceOut() {}
    virtual ~EaseBounceOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBounceOut);
};

/** 
 @brief EaseBounceInOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBounceInOut : public EaseBounce
{
public:
    /** 创建这个延时动作 */
    static EaseBounceInOut* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseBounceInOut* clone() const override;
	virtual EaseBounceInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBounceInOut() {}
    virtual ~EaseBounceInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBounceInOut);
};

/** 
 @brief EaseBackIn action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackIn : public ActionEase
{
public:
    /** 创建这个延时动作 */
    static EaseBackIn* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseBackIn* clone() const override;
	virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBackIn() {}
    virtual ~EaseBackIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBackIn);
};

/** 
 @brief EaseBackOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackOut : public ActionEase
{
public:
    /** 创建这个延时动作 */
    static EaseBackOut* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseBackOut* clone() const override;
	virtual ActionEase* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBackOut() {}
    virtual ~EaseBackOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBackOut);
};

/** 
 @brief EaseBackInOut action.
 @warning This action doesn't use a bijective function. Actions like Sequence might have an unexpected result when used with this action.
 @since v0.8.2
 @ingroup Actions
 */
class CC_DLL EaseBackInOut : public ActionEase
{
public:
    /** 创建这个延时动作 */
    static EaseBackInOut* create(ActionInterval* action);

    // 可重载
    virtual void update(float time) override;
	virtual EaseBackInOut* clone() const override;
	virtual EaseBackInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
    EaseBackInOut() {}
    virtual ~EaseBackInOut() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseBackInOut);
};


/** 
@brief Ease Bezier
@ingroup Actions
*/
class EaseBezierAction : public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseBezierAction* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseBezierAction* clone() const override;
	virtual EaseBezierAction* reverse() const override;

	virtual void setBezierParamer( float p0, float p1, float p2, float p3);

CC_CONSTRUCTOR_ACCESS:
	EaseBezierAction() {}
	virtual ~EaseBezierAction() {}

protected:
	float _p0;
	float _p1;
	float _p2;
	float _p3;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseBezierAction);
};

/** 
@brief Ease Quadratic In
@ingroup Actions
*/
class EaseQuadraticActionIn:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseQuadraticActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuadraticActionIn* clone() const override;
	virtual EaseQuadraticActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseQuadraticActionIn() {}
	virtual ~EaseQuadraticActionIn() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseQuadraticActionIn);

};

/** 
@brief Ease Quadratic Out
@ingroup Actions
*/
class EaseQuadraticActionOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseQuadraticActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuadraticActionOut* clone() const override;
	virtual EaseQuadraticActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseQuadraticActionOut() {}
	virtual ~EaseQuadraticActionOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseQuadraticActionOut);

};

/** 
@brief Ease Quadratic InOut
@ingroup Actions
*/
class EaseQuadraticActionInOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseQuadraticActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuadraticActionInOut* clone() const override;
	virtual EaseQuadraticActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseQuadraticActionInOut() {}
	virtual ~EaseQuadraticActionInOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseQuadraticActionInOut);
};

/** 
@brief Ease Quartic In
@ingroup Actions
*/
class EaseQuarticActionIn:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseQuarticActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuarticActionIn* clone() const override;
	virtual EaseQuarticActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseQuarticActionIn() {}
	virtual ~EaseQuarticActionIn() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseQuarticActionIn);
};

/** 
@brief Ease Quartic Out
@ingroup Actions
*/
class EaseQuarticActionOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseQuarticActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuarticActionOut* clone() const override;
	virtual EaseQuarticActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseQuarticActionOut() {}
	virtual ~EaseQuarticActionOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseQuarticActionOut);
};

/** 
@brief Ease Quartic InOut
@ingroup Actions
*/
class EaseQuarticActionInOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseQuarticActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuarticActionInOut* clone() const override;
	virtual EaseQuarticActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseQuarticActionInOut() {}
	virtual ~EaseQuarticActionInOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseQuarticActionInOut);
};


/** 
@brief Ease Quintic In
@ingroup Actions
*/
class EaseQuinticActionIn:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseQuinticActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuinticActionIn* clone() const override;
	virtual EaseQuinticActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseQuinticActionIn() {}
	virtual ~EaseQuinticActionIn() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseQuinticActionIn);
};

/** 
@brief Ease Quintic Out
@ingroup Actions
*/
class EaseQuinticActionOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseQuinticActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuinticActionOut* clone() const override;
	virtual EaseQuinticActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseQuinticActionOut() {}
	virtual ~EaseQuinticActionOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseQuinticActionOut);
};

/** 
@brief Ease Quintic InOut
@ingroup Actions
*/
class EaseQuinticActionInOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseQuinticActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuinticActionInOut* clone() const override;
	virtual EaseQuinticActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseQuinticActionInOut() {}
	virtual ~EaseQuinticActionInOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseQuinticActionInOut);
};

/** 
@brief Ease Circle In
@ingroup Actions
*/
class EaseCircleActionIn:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseCircleActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCircleActionIn* clone() const override;
	virtual EaseCircleActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseCircleActionIn() {}
	virtual ~EaseCircleActionIn() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseCircleActionIn);
};

/** 
@brief Ease Circle Out
@ingroup Actions
*/
class EaseCircleActionOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseCircleActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCircleActionOut* clone() const override;
	virtual EaseCircleActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseCircleActionOut() {}
	virtual ~EaseCircleActionOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseCircleActionOut);
};

/** 
@brief Ease Circle InOut
@ingroup Actions
*/
class EaseCircleActionInOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseCircleActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCircleActionInOut* clone() const override;
	virtual EaseCircleActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseCircleActionInOut() {}
	virtual ~EaseCircleActionInOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseCircleActionInOut);
};

/** 
@brief Ease Cubic In
@ingroup Actions
*/
class EaseCubicActionIn:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseCubicActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCubicActionIn* clone() const override;
	virtual EaseCubicActionIn* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseCubicActionIn() {}
	virtual ~EaseCubicActionIn() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseCubicActionIn);
};

/** 
@brief Ease Cubic Out
@ingroup Actions
*/
class EaseCubicActionOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseCubicActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCubicActionOut* clone() const override;
	virtual EaseCubicActionOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseCubicActionOut() {}
	virtual ~EaseCubicActionOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseCubicActionOut);
};

/** 
@brief Ease Cubic InOut
@ingroup Actions
*/
class EaseCubicActionInOut:public cocos2d::ActionEase
{
public:
	/** 创建这个延时动作 */
	static EaseCubicActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCubicActionInOut* clone() const override;
	virtual EaseCubicActionInOut* reverse() const override;

CC_CONSTRUCTOR_ACCESS:
	EaseCubicActionInOut() {}
	virtual ~EaseCubicActionInOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseCubicActionInOut);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCEASE_ACTION_H__
