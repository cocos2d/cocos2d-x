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

#ifndef __ActionEaseEx_H__
#define __ActionEaseEx_H__

#include "cocostudio/CocoStudio.h"

namespace cocostudio {

/** 
@brief Ease Bezier
@ingroup Actions
*/
class EaseBezierAction : public cocos2d::ActionEase
{
public:
	/** creates the action */
	static EaseBezierAction* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseBezierAction* clone() const override;
	virtual EaseBezierAction* reverse() const override;

	virtual void setBezierParamer( float p0, float p1, float p2, float p3);

protected:
	EaseBezierAction() {}
	virtual ~EaseBezierAction() {}

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
	/** creates the action */
	static EaseQuadraticActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuadraticActionIn* clone() const override;
	virtual EaseQuadraticActionIn* reverse() const override;

protected:
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
	/** creates the action */
	static EaseQuadraticActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuadraticActionOut* clone() const override;
	virtual EaseQuadraticActionOut* reverse() const override;

protected:
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
	/** creates the action */
	static EaseQuadraticActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuadraticActionInOut* clone() const override;
	virtual EaseQuadraticActionInOut* reverse() const override;

protected:
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
	/** creates the action */
	static EaseQuarticActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuarticActionIn* clone() const override;
	virtual EaseQuarticActionIn* reverse() const override;

protected:
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
	/** creates the action */
	static EaseQuarticActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuarticActionOut* clone() const override;
	virtual EaseQuarticActionOut* reverse() const override;

protected:
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
	/** creates the action */
	static EaseQuarticActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuarticActionInOut* clone() const override;
	virtual EaseQuarticActionInOut* reverse() const override;

protected:
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
	/** creates the action */
	static EaseQuinticActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuinticActionIn* clone() const override;
	virtual EaseQuinticActionIn* reverse() const override;

protected:
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
	/** creates the action */
	static EaseQuinticActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuinticActionOut* clone() const override;
	virtual EaseQuinticActionOut* reverse() const override;

protected:
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
	/** creates the action */
	static EaseQuinticActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseQuinticActionInOut* clone() const override;
	virtual EaseQuinticActionInOut* reverse() const override;

protected:
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
	/** creates the action */
	static EaseCircleActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCircleActionIn* clone() const override;
	virtual EaseCircleActionIn* reverse() const override;

protected:
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
	/** creates the action */
	static EaseCircleActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCircleActionOut* clone() const override;
	virtual EaseCircleActionOut* reverse() const override;

protected:
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
	/** creates the action */
	static EaseCircleActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCircleActionInOut* clone() const override;
	virtual EaseCircleActionInOut* reverse() const override;

protected:
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
	/** creates the action */
	static EaseCubicActionIn* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCubicActionIn* clone() const override;
	virtual EaseCubicActionIn* reverse() const override;

protected:
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
	/** creates the action */
	static EaseCubicActionOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCubicActionOut* clone() const override;
	virtual EaseCubicActionOut* reverse() const override;

protected:
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
	/** creates the action */
	static EaseCubicActionInOut* create(cocos2d::ActionInterval* action);

	virtual void update(float time) override;
	virtual EaseCubicActionInOut* clone() const override;
	virtual EaseCubicActionInOut* reverse() const override;

protected:
	EaseCubicActionInOut() {}
	virtual ~EaseCubicActionInOut() {}

private:
	CC_DISALLOW_COPY_AND_ASSIGN(EaseCubicActionInOut);
};

}

#endif
