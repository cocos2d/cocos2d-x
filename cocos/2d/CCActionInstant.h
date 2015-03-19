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

#include <functional>
#include "2d/CCAction.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** @class ActionInstant
* @brief Instant actions are immediate actions. They don't have a duration like the IntervalAction actions.
**/
class CC_DLL ActionInstant : public FiniteTimeAction //<NSCopying>
{
public:
    //
    // Overrides
    //
    virtual ActionInstant* clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
    
    virtual ActionInstant * reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

    virtual bool isDone() const override;
    /**
     * @param dt In seconds.
     */
    virtual void step(float dt) override;
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
};

/** @class Show
* @brief Show the node.
**/
class CC_DLL Show : public ActionInstant
{
public:
    /** Allocates and initializes the action.
     *
     * @return  An autoreleased Show object.
     */
    static Show * create();

    //
    // Overrides
    //
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    virtual ActionInstant* reverse() const override;
    virtual Show* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    Show(){}
    virtual ~Show(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Show);
};

/** @class Hide
* @brief Hide the node.
*/
class CC_DLL Hide : public ActionInstant
{
public:
    /** Allocates and initializes the action.
     *
     * @return An autoreleased Hide object.
     */
    static Hide * create();

    //
    // Overrides
    //
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    virtual ActionInstant* reverse() const override;
    virtual Hide* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    Hide(){}
    virtual ~Hide(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Hide);
};

/** @class ToggleVisibility
* @brief Toggles the visibility of a node.
*/
class CC_DLL ToggleVisibility : public ActionInstant
{
public:
    /** Allocates and initializes the action.
     *
     * @return An autoreleased ToggleVisibility object.
     */
    static ToggleVisibility * create();

    //
    // Overrides
    //
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    virtual ToggleVisibility* reverse() const override;
    virtual ToggleVisibility* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    ToggleVisibility(){}
    virtual ~ToggleVisibility(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ToggleVisibility);
};

/** @class RemoveSelf
* @brief Remove the node.
*/
class CC_DLL RemoveSelf : public ActionInstant
{
public:
    /** Create the action.
     *
     * @param isNeedCleanUp Is need to clean up, the default value is true.
     * @return An autoreleased RemoveSelf object.
     */
    static RemoveSelf * create(bool isNeedCleanUp = true);

    //
    // Override
    //
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    virtual RemoveSelf* clone() const override;
    virtual RemoveSelf* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    RemoveSelf() : _isNeedCleanUp(true){}
    virtual ~RemoveSelf(){}

    /** init the action */
    bool init(bool isNeedCleanUp);

protected:
    bool _isNeedCleanUp;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RemoveSelf);
};

/** @class FlipX
* @brief Flips the sprite horizontally.
* @since v0.99.0
*/
class CC_DLL FlipX : public ActionInstant
{
public:
    /** Create the action.
     *
     * @param x Flips the sprite horizontally if true.
     * @return  An autoreleased FlipX object.
     */
    static FlipX * create(bool x);

    //
    // Overrides
    //
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    virtual FlipX* reverse() const override;
    virtual FlipX* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipX() :_flipX(false) {}
    virtual ~FlipX() {}

    /** init the action */
    bool initWithFlipX(bool x);

protected:
    bool    _flipX;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipX);
};

/** @class FlipY
* @brief Flips the sprite vertically.
* @since v0.99.0
*/
class CC_DLL FlipY : public ActionInstant
{
public:
    /** Create the action.
     *
     * @param y Flips the sprite vertically if true.
     * @return An autoreleased FlipY object.
     */
    static FlipY * create(bool y);

    //
    // Overrides
    //
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    virtual FlipY* reverse() const override;
    virtual FlipY* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipY() :_flipY(false) {}
    virtual ~FlipY() {}

    /** init the action */
    bool initWithFlipY(bool y);

protected:
    bool    _flipY;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipY);
};

/** @class Place
* @brief Places the node in a certain position.
*/
class CC_DLL Place : public ActionInstant //<NSCopying>
{
public:

    /** Creates a Place action with a position.
     *
     * @param pos  A certain position.
     * @return  An autoreleased Place object.
     */
    static Place * create(const Vec2& pos);

    //
    // Overrides
    //
    /**
     * @param time In seconds.
     */
    virtual void update(float time) override;
    virtual Place* reverse() const override;
    virtual Place* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    Place(){}
    virtual ~Place(){}

    /** Initializes a Place action with a position */
    bool initWithPosition(const Vec2& pos);

protected:
    Vec2 _position;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Place);
};


/** @class CallFunc
* @brief Calls a 'callback'.
*/
class CC_DLL CallFunc : public ActionInstant //<NSCopying>
{
public:
    /** Creates the action with the callback of type std::function<void()>.
     This is the preferred way to create the callback.
     * When this funtion bound in js or lua ,the input param will be changed.
     * In js: var create(var func, var this, var [data]) or var create(var func).
     * In lua:local create(local funcID).
     *
     * @param func  A callback function need to be excuted.
     * @return  An autoreleased CallFunc object.
     */
    static CallFunc * create(const std::function<void()>& func);

    /** Creates the action with the callback

     typedef void (Ref::*SEL_CallFunc)();
     @deprecated Use the std::function API instead.
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static CallFunc * create(Ref* target, SEL_CallFunc selector);

public:
    /** Executes the callback.
     */
    virtual void execute();

    /** Get the selector target.
     *
     * @return The selector target.
     */
    inline Ref* getTargetCallback()
    {
        return _selectorTarget;
    }

    /** Set the selector target.
     *
     * @param The selector target.
     */
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
    // Overrides
    //
    /**
     * @param time In seconds.
     */
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

    /** initializes the action with the callback
     typedef void (Ref::*SEL_CallFunc)();
     @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target);
    
    /** initializes the action with the std::function<void()>
     * @lua NA
     */
    bool initWithFunction(const std::function<void()>& func);

protected:
    /** Target that will be called */
    Ref*   _selectorTarget;

    union
    {
        SEL_CallFunc    _callFunc;
        SEL_CallFuncN    _callFuncN;
    };
    
    /** function that will be called */
    std::function<void()> _function;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(CallFunc);
};

/** @class CallFuncN
* @brief Calls a 'callback' with the node as the first argument. N means Node.
* @js NA
*/
class CC_DLL CallFuncN : public CallFunc
{
public:
    /** Creates the action with the callback of type std::function<void()>.
     This is the preferred way to create the callback.
     *
     * @param func  A callback function need to be excuted.
     * @return  An autoreleased CallFuncN object.
     */
    static CallFuncN * create(const std::function<void(Node*)>& func);

    /** Creates the action with the callback.

    typedef void (Ref::*SEL_CallFuncN)(Node*);
     @deprecated Use the std::function API instead.
    */
    CC_DEPRECATED_ATTRIBUTE static CallFuncN * create(Ref* target, SEL_CallFuncN selector);

    //
    // Overrides
    //
    virtual CallFuncN* clone() const override;
    virtual void execute() override;
    
CC_CONSTRUCTOR_ACCESS:
    CallFuncN():_functionN(nullptr){}
    virtual ~CallFuncN(){}

    /** initializes the action with the std::function<void(Node*)> */
    bool initWithFunction(const std::function<void(Node*)>& func);
    
    /** initializes the action with the callback
     
     typedef void (Ref::*SEL_CallFuncN)(Node*);
     @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target, SEL_CallFuncN selector);

protected:
    /** function that will be called with the "sender" as the 1st argument */
    std::function<void(Node*)> _functionN;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(CallFuncN);
};

/** @class __CCCallFuncND
 * @deprecated Please use CallFuncN instead.
 * @brief Calls a 'callback' with the node as the first argument and the 2nd argument is data.
 * ND means: Node and Data. Data is void *, so it could be anything.
 * @js NA
 */
class CC_DLL  __CCCallFuncND : public CallFunc
{
public:
    /** Creates the action with the callback and the data to pass as an argument.
     *
     * @param target    A certain target.
     * @param selector  The callback need to be excuted.
     * @param d Data, is void* type.
     * @return An autoreleased __CCCallFuncND object.
     */
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncND * create(Ref* target, SEL_CallFuncND selector, void* d);
    
    //
    // Overrides
    //
    virtual __CCCallFuncND* clone() const override;
    virtual void execute() override;
    
CC_CONSTRUCTOR_ACCESS:
    __CCCallFuncND() {}
    virtual ~__CCCallFuncND() {}
    
    /** initializes the action with the callback and the data to pass as an argument */
    bool initWithTarget(Ref* target, SEL_CallFuncND selector, void* d);

protected:
    SEL_CallFuncND _callFuncND;
    void* _data;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__CCCallFuncND);
};


/** @class __CCCallFuncO
 @deprecated Please use CallFuncN instead.
 @brief Calls a 'callback' with an object as the first argument. O means Object.
 @since v0.99.5
 @js NA
 */

class CC_DLL __CCCallFuncO : public CallFunc
{
public:
    /** Creates the action with the callback.
        typedef void (Ref::*SEL_CallFuncO)(Ref*);
     *
     * @param target    A certain target.
     * @param selector  The callback need to be excuted.
     * @param object    An object as the callback's first argument.
     * @return An autoreleased __CCCallFuncO object.
     */
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncO * create(Ref* target, SEL_CallFuncO selector, Ref* object);
    //
    // Overrides
    //
    virtual __CCCallFuncO* clone() const override;
    virtual void execute() override;
    
    Ref* getObject() const;
    void setObject(Ref* obj);
    
CC_CONSTRUCTOR_ACCESS:
    __CCCallFuncO();
    virtual ~__CCCallFuncO();
    /** initializes the action with the callback

     typedef void (Ref::*SEL_CallFuncO)(Ref*);
     */
    bool initWithTarget(Ref* target, SEL_CallFuncO selector, Ref* object);
    
protected:
    /** object to be passed as argument */
    Ref* _object;
    SEL_CallFuncO _callFuncO;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__CCCallFuncO);
};

// end of actions group
/// @}

NS_CC_END

#endif //__CCINSTANT_ACTION_H__
