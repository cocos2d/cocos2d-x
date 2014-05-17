/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCINSTANT_ACTION_H__
#define __CCINSTANT_ACTION_H__

#include <string>
#include <functional>

#include "CCStdC.h"
#include "2d/CCAction.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** 
@brief Instant actions are immediate actions. They don't have a duration like
the IntervalAction actions.
*/ 
class CC_DLL ActionInstant : public FiniteTimeAction //<NSCopying>
{
public:
    //
    // 重载
    //
	virtual ActionInstant* clone() const override = 0;
    virtual ActionInstant * reverse() const override = 0;
    virtual bool isDone() const override;
    virtual void step(float dt) override;
    virtual void update(float time) override;
};

/** @brief Show the node
*/
class CC_DLL Show : public ActionInstant
{
public:
    /** 分配内存和初始化动作*/
    static Show * create();


    //
    // 重载
    //
    virtual void update(float time) override;
    virtual ActionInstant* reverse() const override;
	virtual Show* clone() const override;

protected:
    Show(){}
    virtual ~Show(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Show);
};

/** 
@brief Hide the node
*/
class CC_DLL Hide : public ActionInstant
{
public:
    /** 配置和初始化动作 */
    static Hide * create();

    //
    // 重载
    //
    virtual void update(float time) override;
	virtual ActionInstant* reverse() const override;
	virtual Hide* clone() const override;

protected:
    Hide(){}
    virtual ~Hide(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Hide);
};

/** @brief Toggles the visibility of a node
*/
class CC_DLL ToggleVisibility : public ActionInstant
{
public:
    /** 配置和初始化动作 */
    static ToggleVisibility * create();

    //
    // 重载
    //
    virtual void update(float time) override;
	virtual ToggleVisibility* reverse() const override;
	virtual ToggleVisibility* clone() const override;

protected:
    ToggleVisibility(){}
    virtual ~ToggleVisibility(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ToggleVisibility);
};

/** 
@brief Remove the node
*/
class CC_DLL RemoveSelf : public ActionInstant
{
public:
	/** 创建动作 */
	static RemoveSelf * create(bool isNeedCleanUp = true);

	//
    // 重载
    //
	virtual void update(float time) override;
	virtual RemoveSelf* clone() const override;
	virtual RemoveSelf* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    RemoveSelf() : _isNeedCleanUp(true){}
    virtual ~RemoveSelf(){}

	/** 初始化动作 */
	bool init(bool isNeedCleanUp);

protected:
	bool _isNeedCleanUp;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RemoveSelf);
};

/** 
@brief Flips the sprite horizontally
@since v0.99.0
*/
class CC_DLL FlipX : public ActionInstant
{
public:
    /** 创建动作 */
    static FlipX * create(bool x);

    //
    //重载
    //
    virtual void update(float time) override;
	virtual FlipX* reverse() const override;
	virtual FlipX* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipX() :_flipX(false) {}
    virtual ~FlipX() {}

    /** 初始化动作 */
    bool initWithFlipX(bool x);

protected:
    bool    _flipX;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipX);
};

/** 
@brief Flips the sprite vertically
@since v0.99.0
*/
class CC_DLL FlipY : public ActionInstant
{
public:
    /*创建动作 */
    static FlipY * create(bool y);

    //
    // 重载
    //
    virtual void update(float time) override;
	virtual FlipY* reverse() const override;
	virtual FlipY* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipY() :_flipY(false) {}
    virtual ~FlipY() {}

    /** 初始化动作 */
    bool initWithFlipY(bool y);

protected:
    bool    _flipY;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipY);
};

/** @brief Places the node in a certain position
*/
class CC_DLL Place : public ActionInstant //<NSCopying>
{
public:

    /** 用一个点创建位置动作 */
    static Place * create(const Vec2& pos);

    //
    // 重载
    //
    virtual void update(float time) override;
	virtual Place* reverse() const override;
	virtual Place* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    Place(){}
    virtual ~Place(){}

    /** 用一个点初始化位置动作 */
    bool initWithPosition(const Vec2& pos);

protected:
    Vec2 _position;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Place);
};


/** @brief Calls a 'callback'
*/
class CC_DLL CallFunc : public ActionInstant //<NSCopying>
{
public:
	/** 用std::function<void()>类型的回调函数为参数创建动作。
	 这是创建回调函数的首选方式。
     * 当这个函数局限于js或者lua语言的时候，输入参数将会被改变
     * 在 js中: var create(var func, var this, var [data]) or var create(var func)
     * 在lua中:local create(local funcID)
	 */
    static CallFunc * create(const std::function<void()>& func);

    /** 用回调函数为参数创建动作

     typedef void (Ref::*SEL_CallFunc)();
	 @deprecated Use the std::function API instead.
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static CallFunc * create(Ref* target, SEL_CallFunc selector);

public:
    /** 执行回调函数 */
    virtual void execute();

    inline Ref* getTargetCallback()
    {
        return _selectorTarget;
    }

    inline void setTargetCallback(Ref* sel)
    {
        if (sel != _selectorTarget)
        {
            CC_SAFE_RETAIN(sel);
            CC_SAFE_RELEASE(_selectorTarget);
            _selectorTarget = sel;
        }
    }
    //
    // 重载
    //
    virtual void update(float time) override;
	virtual CallFunc* reverse() const override;
	virtual CallFunc* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    CallFunc()
    : _selectorTarget(nullptr)
    , _callFunc(nullptr)
    , _function(nullptr)
    {
    }
    virtual ~CallFunc();

	/** 用回调函数初始化动作
     typedef void (Ref::*SEL_CallFunc)();
     @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target);
    
	/** 以std::function<void()>为参数，初始化动作
     * @js NA
     * @lua NA
	 */
    bool initWithFunction(const std::function<void()>& func);

protected:
    /** 讲被调用的目标变量*/
    Ref*   _selectorTarget;

    union
    {
        SEL_CallFunc    _callFunc;
        SEL_CallFuncN    _callFuncN;
    };
    
    /** 将被调用的函数 */
	std::function<void()> _function;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(CallFunc);
};

/** 
@brief Calls a 'callback' with the node as the first argument
N means Node
*/
class CC_DLL CallFuncN : public CallFunc
{
public:
    /** 用std::function<void()>类型的回调函数为参数创建动作。
	 这是创建回调函数的首选方式。
	 */
    static CallFuncN * create(const std::function<void(Node*)>& func);

    /** 以回调函数为参数创建动作 

    typedef void (Ref::*SEL_CallFuncN)(Node*);
     @deprecated Use the std::function API instead.
    */
    CC_DEPRECATED_ATTRIBUTE static CallFuncN * create(Ref* target, SEL_CallFuncN selector);

    //
    // 重载
    //
	virtual CallFuncN* clone() const override;
    virtual void execute() override;
    
CC_CONSTRUCTOR_ACCESS:
    CallFuncN():_functionN(nullptr){}
    virtual ~CallFuncN(){}

    /** 以std::function<void(Node*)> 为参数初始化*/
    bool initWithFunction(const std::function<void(Node*)>& func);
    
    /** 以回调函数为参数初始化动作
     
     typedef void (Ref::*SEL_CallFuncN)(Node*);
     @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target, SEL_CallFuncN selector);

protected:
    /** 将被调用并以“sneder作为第一参数的函数” */
    std::function<void(Node*)> _functionN;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(CallFuncN);
};

/**
 @deprecated Please use CallFuncN instead.
 @brief Calls a 'callback' with the node as the first argument and the 2nd argument is data
 * ND means: Node and Data. Data is void *, so it could be anything.
 */

class CC_DLL  __CCCallFuncND : public CallFunc
{
public:
    /**以回调函数为参数创建动作并将数据作为参数传递进去*/
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncND * create(Ref* target, SEL_CallFuncND selector, void* d);
    
    //
    // 重载
    //
	virtual __CCCallFuncND* clone() const override;
    virtual void execute() override;
    
protected:
    __CCCallFuncND() {}
    virtual ~__CCCallFuncND() {}
    
    /**以回调函数为参数创建动作并将数据作为参数传递进去*/
    bool initWithTarget(Ref* target, SEL_CallFuncND selector, void* d);

    SEL_CallFuncND _callFuncND;
    void* _data;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__CCCallFuncND);
};


/**
 @deprecated Please use CallFuncN instead.
 @brief Calls a 'callback' with an object as the first argument.
 O means Object.
 @since v0.99.5
 */

class CC_DLL __CCCallFuncO : public CallFunc
{
public:
    /** 以回调函数为参数创建动作
     
     typedef void (Ref::*SEL_CallFuncO)(Ref*);
     */
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncO * create(Ref* target, SEL_CallFuncO selector, Ref* object);
    //
    // 重载
    //
	virtual __CCCallFuncO* clone() const override;
    virtual void execute() override;
    
    Ref* getObject() const;
    void setObject(Ref* obj);
    
protected:
    __CCCallFuncO();
    virtual ~__CCCallFuncO();
    /** 以回调函数为参数初始化动作

     typedef void (Ref::*SEL_CallFuncO)(Ref*);
     */
    bool initWithTarget(Ref* target, SEL_CallFuncO selector, Ref* object);
    

    /** 作为参数传递进去的对象 */
    Ref* _object;
    SEL_CallFuncO _callFuncO;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__CCCallFuncO);
};

// 结束
/// @}

NS_CC_END

#endif //__CCINSTANT_ACTION_H__
