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

#ifndef __CCActionEaseEx_H__
#define __CCActionEaseEx_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

/** 
 @brief Ease Bezier
 @ingroup Actions
 */
class CC_EX_DLL CCEaseBezierAction:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

	virtual void setBezierParamer( float p0, float p1, float p2, float p3);

public:
	/** creates the action */
	static CCEaseBezierAction* create(CCActionInterval* pAction);

private:
	float m_p0;
	float m_p1;
	float m_p2;
	float m_p3;
};

/** 
 @brief Ease Quadratic In
 @ingroup Actions
 */
class CCEaseQuadraticActionIn:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseQuadraticActionIn* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Quadratic Out
 @ingroup Actions
 */
class CCEaseQuadraticActionOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseQuadraticActionOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Quadratic InOut
 @ingroup Actions
 */
class CCEaseQuadraticActionInOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseQuadraticActionInOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Quartic In
 @ingroup Actions
 */
class CCEaseQuarticActionIn:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseQuarticActionIn* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Quartic Out
 @ingroup Actions
 */
class CCEaseQuarticActionOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseQuarticActionOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Quartic InOut
 @ingroup Actions
 */
class CCEaseQuarticActionInOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseQuarticActionInOut* create(CCActionInterval* pAction);
};


/** 
 @brief Ease Quintic In
 @ingroup Actions
 */
class CCEaseQuinticActionIn:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseQuinticActionIn* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Quintic Out
 @ingroup Actions
 */
class CCEaseQuinticActionOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseQuinticActionOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Quintic InOut
 @ingroup Actions
 */
class CCEaseQuinticActionInOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseQuinticActionInOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Circle In
 @ingroup Actions
 */
class CCEaseCircleActionIn:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseCircleActionIn* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Circle Out
 @ingroup Actions
 */
class CCEaseCircleActionOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseCircleActionOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Circle InOut
 @ingroup Actions
 */
class CCEaseCircleActionInOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseCircleActionInOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Cubic In
 @ingroup Actions
 */
class CCEaseCubicActionIn:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseCubicActionIn* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Cubic Out
 @ingroup Actions
 */
class CCEaseCubicActionOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseCubicActionOut* create(CCActionInterval* pAction);
};

/** 
 @brief Ease Cubic InOut
 @ingroup Actions
 */
class CCEaseCubicActionInOut:public CCActionEase
{
public:
	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual CCObject* copyWithZone(CCZone* pZone);

public:
	/** creates the action */
	static CCEaseCubicActionInOut* create(CCActionInterval* pAction);
};
NS_CC_EXT_END

#endif
