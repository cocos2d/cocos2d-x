/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011 Zynga Inc.

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
#include "ccTypeInfo.h"
#include "CCAction.h"

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
    // Overrides
    //
	virtual ActionInstant* clone() const override = 0;
    virtual ActionInstant * reverse(void) const override = 0;
    virtual bool isDone(void) const override;
    virtual void step(float dt) override;
    virtual void update(float time) override;
};

/** @brief Show the node
*/
class CC_DLL Show : public ActionInstant
{
public:
    /** Allocates and initializes the action */
    static Show * create();

    Show(){}

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual ActionInstant* reverse(void) const override;
	virtual Show* clone() const override;
};

/** 
@brief Hide the node
*/
class CC_DLL Hide : public ActionInstant
{
public:
    /** Allocates and initializes the action */
    static Hide * create();

    Hide(){}

    //
    // Overrides
    //
    virtual void update(float time) override;
	virtual ActionInstant* reverse() const override;
	virtual Hide* clone() const override;
};

/** @brief Toggles the visibility of a node
*/
class CC_DLL ToggleVisibility : public ActionInstant
{
public:
    /** Allocates and initializes the action */
    static ToggleVisibility * create();

    ToggleVisibility(){}

    //
    // Overrides
    //
    virtual void update(float time) override;
	virtual ToggleVisibility* reverse() const override;
	virtual ToggleVisibility* clone() const override;
};

/** 
@brief Remove the node
*/
class CC_DLL RemoveSelf : public ActionInstant
{
public:
	/** create the action */
	static RemoveSelf * create(bool isNeedCleanUp = true);

    RemoveSelf():_isNeedCleanUp(true)
	{}

	/** init the action */
	bool init(bool isNeedCleanUp);

	//
    // Override
    //
	virtual void update(float time) override;
	virtual RemoveSelf* clone() const override;
	virtual RemoveSelf* reverse() const override;

protected:
	bool _isNeedCleanUp;
};

/** 
@brief Flips the sprite horizontally
@since v0.99.0
*/
class CC_DLL FlipX : public ActionInstant
{
public:
    /** create the action */
    static FlipX * create(bool x);

    FlipX()
        :_flipX(false)
    {}

    /** init the action */
    bool initWithFlipX(bool x);

    //
    // Overrides
    //
    virtual void update(float time) override;
	virtual FlipX* reverse() const override;
	virtual FlipX* clone() const override;

protected:
    bool    _flipX;
};

/** 
@brief Flips the sprite vertically
@since v0.99.0
*/
class CC_DLL FlipY : public ActionInstant
{
public:
    /** create the action */
    static FlipY * create(bool y);

    FlipY()
        :_flipY(false)
    {}

    /** init the action */
    bool initWithFlipY(bool y);

    //
    // Overrides
    //
    virtual void update(float time) override;
	virtual FlipY* reverse() const override;
	virtual FlipY* clone() const override;

protected:
    bool    _flipY;
};

/** @brief Places the node in a certain position
*/
class CC_DLL Place : public ActionInstant //<NSCopying>
{
public:
    Place(){}

    /** creates a Place action with a position */
    static Place * create(const Point& pos);
    /** Initializes a Place action with a position */
    bool initWithPosition(const Point& pos);

    //
    // Overrides
    //
    virtual void update(float time) override;
	virtual Place* reverse() const override;
	virtual Place* clone() const override;

protected:
    Point _position;
};


/** @brief Calls a 'callback'
*/
class CC_DLL CallFunc : public ActionInstant //<NSCopying>
{
public:
	/** creates the action with the callback of type std::function<void()>.
	 This is the preferred way to create the callback.
	 */
    static CallFunc * create(const std::function<void()>& func);

    /** creates the action with the callback

     typedef void (Object::*SEL_CallFunc)();
	 @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE static CallFunc * create(Object* pSelectorTarget, SEL_CallFunc selector);

public:
    CallFunc()
        : _selectorTarget(NULL)
        , _callFunc(NULL)
		, _function(nullptr)
    {
    }
    virtual ~CallFunc();

	/** initializes the action with the callback 
    typedef void (Object::*SEL_CallFunc)();
    @deprecated Use the std::function API instead.
    */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Object* pSelectorTarget);

	/** initializes the action with the std::function<void()>
	 */
    bool initWithFunction(const std::function<void()>& func);

    /** executes the callback */
    virtual void execute();

    inline Object* getTargetCallback()
    {
        return _selectorTarget;
    }

    inline void setTargetCallback(Object* pSel)
    {
        if (pSel != _selectorTarget)
        {
            CC_SAFE_RETAIN(pSel);
            CC_SAFE_RELEASE(_selectorTarget);
            _selectorTarget = pSel; 
        }
    }
    //
    // Overrides
    //
    virtual void update(float time) override;
	virtual CallFunc* reverse() const override;
	virtual CallFunc* clone() const override;

protected:
    /** Target that will be called */
    Object*   _selectorTarget;

    union
    {
        SEL_CallFunc    _callFunc;
        SEL_CallFuncN    _callFuncN;
    };
    
    /** function that will be called */
	std::function<void()> _function;
};

/** 
@brief Calls a 'callback' with the node as the first argument
N means Node
*/
class CC_DLL CallFuncN : public CallFunc, public TypeInfo
{
public:
    /** creates the action with the callback of type std::function<void()>.
	 This is the preferred way to create the callback.
	 */
    static CallFuncN * create(const std::function<void(Node*)>& func);

    /** creates the action with the callback 

    typedef void (Object::*SEL_CallFuncN)(Node*);
     @deprecated Use the std::function API instead.
    */
    CC_DEPRECATED_ATTRIBUTE static CallFuncN * create(Object* pSelectorTarget, SEL_CallFuncN selector);
public:
    CallFuncN():_functionN(nullptr){}

    /** initializes the action with the std::function<void(Node*)>
	 */
    bool initWithFunction(const std::function<void(Node*)>& func);

    /** initializes the action with the callback 

    typedef void (Object::*SEL_CallFuncN)(Node*);
    @deprecated Use the std::function API instead.
    */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Object* pSelectorTarget, SEL_CallFuncN selector);

    virtual long getClassTypeInfo() {
		static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CallFunc).name());
		return id;
    }

    //
    // Overrides
    //
	virtual CallFuncN* clone() const override;
    virtual void execute() override;

protected:
    /** function that will be called with the "sender" as the 1st argument */
    std::function<void(Node*)> _functionN;
};

/**
 @deprecated Please use CallFuncN instead.
 @brief Calls a 'callback' with the node as the first argument and the 2nd argument is data
 * ND means: Node and Data. Data is void *, so it could be anything.
 */

class CC_DLL  __CCCallFuncND : public CallFunc
{
public:
    /** creates the action with the callback and the data to pass as an argument */
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncND * create(Object* selectorTarget, SEL_CallFuncND selector, void* d);
    
    virtual long getClassTypeInfo() {
        static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CallFunc).name());
		return id;
    }
    
protected:
    /** initializes the action with the callback and the data to pass as an argument */
    bool initWithTarget(Object* selectorTarget, SEL_CallFuncND selector, void* d);
    
public:
    //
    // Overrides
    //
	virtual __CCCallFuncND* clone() const override;
    virtual void execute() override;
    
protected:
    SEL_CallFuncND _callFuncND;
    void* _data;
};


/**
 @deprecated Please use CallFuncN instead.
 @brief Calls a 'callback' with an object as the first argument.
 O means Object.
 @since v0.99.5
 */

class CC_DLL __CCCallFuncO : public CallFunc, public TypeInfo
{
public:
    /** creates the action with the callback
     
     typedef void (Object::*SEL_CallFuncO)(Object*);
     */
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncO * create(Object* selectorTarget, SEL_CallFuncO selector, Object* object);
    
    __CCCallFuncO();
    virtual ~__CCCallFuncO();
    
    virtual long getClassTypeInfo() {
	    static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CallFunc).name());
		return id;
    }
    
protected:
    /** initializes the action with the callback
     
     typedef void (Object::*SEL_CallFuncO)(Object*);
     */
    bool initWithTarget(Object* selectorTarget, SEL_CallFuncO selector, Object* object);
    
public:
    //
    // Overrides
    //
	virtual __CCCallFuncO* clone() const override;
    virtual void execute() override;
    
    Object* getObject() const;
    void setObject(Object* obj);
    
protected:
    /** object to be passed as argument */
    Object* _object;
    SEL_CallFuncO _callFuncO;
};

// end of actions group
/// @}

NS_CC_END

#endif //__CCINSTANT_ACTION_H__
