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
    virtual ~ActionInstant(){}
    // Action methods

	/** returns a new clone of the action */
	virtual ActionInstant* clone() const = 0;
    /** returns a new reversed action */
    virtual ActionInstant * reverse(void) const = 0;

    virtual bool isDone(void);
    virtual void step(float dt);
    virtual void update(float time);
};

/** @brief Show the node
*/
class CC_DLL Show : public ActionInstant
{
public:
    Show(){}
    virtual ~Show(){}
    //super methods
    virtual void update(float time);

	/** returns a new reversed action */
    virtual ActionInstant * reverse(void) const;
	/** returns a new clone of the action */
	virtual Show* clone() const;

    virtual Object* copyWithZone(Zone *pZone);
public:

    /** Allocates and initializes the action */
    static Show * create();
};



/** 
@brief Hide the node
*/
class CC_DLL Hide : public ActionInstant
{
public:
    Hide(){}
    virtual ~Hide(){}
    //super methods
    virtual void update(float time);
	/** returns a new reversed action */
	virtual ActionInstant* reverse() const;
	/** returns a new clone of the action */
	virtual Hide* clone() const;
    virtual Object* copyWithZone(Zone *pZone);
public:

    /** Allocates and initializes the action */
    static Hide * create();
};

/** @brief Toggles the visibility of a node
*/
class CC_DLL ToggleVisibility : public ActionInstant
{
public:
    ToggleVisibility(){}
    virtual ~ToggleVisibility(){}
    //super method
    virtual void update(float time);
	/** returns a new reversed action */
	virtual ToggleVisibility* reverse() const;
	/** returns a new clone of the action */
	virtual ToggleVisibility* clone() const;
    virtual Object* copyWithZone(Zone *pZone);
public:

    /** Allocates and initializes the action */
    static ToggleVisibility * create();
};

/** 
@brief Remove the node
*/
class CC_DLL RemoveSelf : public ActionInstant
{
public:
	RemoveSelf(){}
	virtual ~RemoveSelf(){}
	//super methods
	virtual void update(float time);
	/** returns a new clone of the instance */
	virtual RemoveSelf* clone() const;
	/** returns a new reversed action */
	virtual RemoveSelf* reverse() const;
	virtual Object* copyWithZone(Zone *pZone);
public:
	/** create the action */
	static RemoveSelf * create(bool isNeedCleanUp = true);
	/** init the action */
	bool init(bool isNeedCleanUp);
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
    FlipX()
        :_flipX(false)
    {}
    virtual ~FlipX(){}

    /** create the action */
    static FlipX * create(bool x);

    /** init the action */
    bool initWithFlipX(bool x);
    //super methods
    virtual void update(float time);
	/** returns a new reversed action */
	virtual FlipX* reverse() const;
	/** returns a new clone of the action */
	virtual FlipX* clone() const;
    virtual Object* copyWithZone(Zone *pZone);

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
    FlipY()
        :_flipY(false)
    {}
    virtual ~FlipY(){}

    /** create the action */
    static FlipY * create(bool y);

    /** init the action */
    bool initWithFlipY(bool y);
    //super methods
    virtual void update(float time);
	/** returns a new reversed action */
	virtual FlipY* reverse() const;
	/** returns a new clone of the action */
	virtual FlipY* clone() const;
    virtual Object* copyWithZone(Zone *pZone);

protected:
    bool    _flipY;
};

/** @brief Places the node in a certain position
*/
class CC_DLL Place : public ActionInstant //<NSCopying>
{
public:
    Place(){}
    virtual ~Place(){}

    /** creates a Place action with a position */
    static Place * create(const Point& pos);
    /** Initializes a Place action with a position */
    bool initWithPosition(const Point& pos);
    //super methods
    virtual void update(float time);
	/** returns a new reversed action */
	virtual Place* reverse() const;
	/** returns a new clone of the action */
	virtual Place* clone() const;
    virtual Object* copyWithZone(Zone *pZone);
protected:
    Point _position;
};


/** @brief Calls a 'callback'
*/
class CC_DLL CallFunc : public ActionInstant //<NSCopying>
{
public:
    CallFunc()
        : _selectorTarget(NULL)
		, _scriptHandler(0)
        , _callFunc(NULL)
		, _function(nullptr)
    {
    }
    virtual ~CallFunc();

	/** creates the action with the callback of type std::function<void()>.
	 This is the preferred way to create the callback.
	 */
    static CallFunc * create(const std::function<void()>& func);

    /** creates the action with the callback 

    typedef void (Object::*SEL_CallFunc)();
	 @deprecated Use the std::function API instead.
    */
    static CallFunc * create(Object* pSelectorTarget, SEL_CallFunc selector);

	/** creates the action with the handler script function */
	static CallFunc * create(int nHandler);

	/** initializes the action with the callback 
    
    typedef void (Object::*SEL_CallFunc)();
    */
    virtual bool initWithTarget(Object* pSelectorTarget);

	/** initializes the action with the std::function<void()>
	 */
    virtual bool initWithFunction(const std::function<void()>& func);

    /** executes the callback */
    virtual void execute();
    //super methods
    virtual void update(float time);
	/** returns a new reversed action */
	virtual CallFunc* reverse() const;
	/** returns a new clone of the action */
	virtual CallFunc* clone() const;
    Object * copyWithZone(Zone *pZone);

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
    
    inline int getScriptHandler() { return _scriptHandler; };
protected:
    /** Target that will be called */
    Object*   _selectorTarget;

	int _scriptHandler;

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
    CallFuncN():_functionN(nullptr){}
    virtual ~CallFuncN(){}
    virtual long getClassTypeInfo() {
		static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CallFunc).name());
		return id;
    }

    /** creates the action with the callback of type std::function<void()>.
	 This is the preferred way to create the callback.
	 */
    static CallFuncN * create(const std::function<void(Node*)>& func);

    /** creates the action with the callback 

    typedef void (Object::*SEL_CallFuncN)(Node*);
     @deprecated Use the std::function API instead.
    */
    static CallFuncN * create(Object* pSelectorTarget, SEL_CallFuncN selector);

	/** creates the action with the handler script function */
	static CallFuncN * create(int nHandler);


    /** initializes the action with the std::function<void(Node*)>
	 */
    virtual bool initWithFunction(const std::function<void(Node*)>& func);

    /** initializes the action with the callback 

    typedef void (Object::*SEL_CallFuncN)(Node*);
    @deprecated Use the std::function API instead.
    */
    virtual bool initWithTarget(Object* pSelectorTarget, SEL_CallFuncN selector);
    // super methods
	virtual CallFuncN* clone() const;
    virtual Object* copyWithZone(Zone *pZone);
    virtual void execute();

protected:
    /** function that will be called with the "sender" as the 1st argument */
    std::function<void(Node*)> _functionN;
};

// end of actions group
/// @}

NS_CC_END

#endif //__CCINSTANT_ACTION_H__
