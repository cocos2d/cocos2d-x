/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
#include "CCAction.h"

NS_CC_BEGIN

/** 
@brief Instant actions are immediate actions. They don't have a duration like
the CCIntervalAction actions.
*/ 
class CC_DLL CCActionInstant : public CCFiniteTimeAction //<NSCopying>
{
public:
    CCActionInstant();
    virtual ~CCActionInstant(){}
    // CCAction methods
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual bool isDone(void);
    virtual void step(ccTime dt);
    virtual void update(ccTime time);
    //CCFiniteTimeAction method
    virtual CCFiniteTimeAction * reverse(void);
};

/** @brief Show the node
*/
class CC_DLL CCShow : public CCActionInstant
{
public:
    CCShow(){}
    virtual ~CCShow(){}
    //super methods
    virtual void update(ccTime time);
    virtual CCFiniteTimeAction * reverse(void);
    virtual CCObject* copyWithZone(CCZone *pZone);
public:
    //override static method
    /** Allocates and initializes the action */
    static CCShow * action();
};



/** 
@brief Hide the node
*/
class CC_DLL CCHide : public CCActionInstant
{
public:
    CCHide(){}
    virtual ~CCHide(){}
    //super methods
    virtual void update(ccTime time);
    virtual CCFiniteTimeAction * reverse(void);
    virtual CCObject* copyWithZone(CCZone *pZone);
public:
    //override static method
    /** Allocates and initializes the action */
    static CCHide * action();
};

/** @brief Toggles the visibility of a node
*/
class CC_DLL CCToggleVisibility : public CCActionInstant
{
public:
    CCToggleVisibility(){}
    virtual ~CCToggleVisibility(){}
    //super method
    virtual void update(ccTime time);
    virtual CCObject* copyWithZone(CCZone *pZone);
public:
    //override static method
    /** Allocates and initializes the action */
    static CCToggleVisibility * action();
};

/** 
@brief Flips the sprite horizontally
@since v0.99.0
*/
class CC_DLL CCFlipX : public CCActionInstant
{
public:
    CCFlipX()
        :m_bFlipX(false)
    {}
    virtual ~CCFlipX(){}

    /** create the action */
    static CCFlipX * actionWithFlipX(bool x);
    /** init the action */
    bool initWithFlipX(bool x);
    //super methods
    virtual void update(ccTime time);
    virtual CCFiniteTimeAction * reverse(void);
    virtual CCObject* copyWithZone(CCZone *pZone);

protected:
    bool    m_bFlipX;
};

/** 
@brief Flips the sprite vertically
@since v0.99.0
*/
class CC_DLL CCFlipY : public CCActionInstant
{
public:
    CCFlipY()
        :m_bFlipY(false)
    {}
    virtual ~CCFlipY(){}
    
    /** create the action */
    static CCFlipY * actionWithFlipY(bool y);
    /** init the action */
    bool initWithFlipY(bool y);
    //super methods
    virtual void update(ccTime time);
    virtual CCFiniteTimeAction * reverse(void);
    virtual CCObject* copyWithZone(CCZone *pZone);

protected:
    bool    m_bFlipY;
};

/** @brief Places the node in a certain position
*/
class CC_DLL CCPlace : public CCActionInstant //<NSCopying>
{
public:
    CCPlace(){}
    virtual ~CCPlace(){}
    /** creates a Place action with a position */
    static CCPlace * actionWithPosition(const CCPoint& pos);
    /** Initializes a Place action with a position */
    bool initWithPosition(const CCPoint& pos);
    //super methods
    virtual void update(ccTime time);
    virtual CCObject* copyWithZone(CCZone *pZone);
protected:
    CCPoint m_tPosition;
};

/** @brief Calls a 'callback'
*/
class CC_DLL CCCallFunc : public CCActionInstant //<NSCopying>
{
public:
    CCCallFunc()
        : m_pSelectorTarget(NULL)
        , m_pCallFunc(NULL)

    {
    }
    virtual ~CCCallFunc()
    {
        if (m_pSelectorTarget)
        {
            m_pSelectorTarget->release();
        }
    }
    /** creates the action with the callback 

    typedef void (CCObject::*SEL_CallFunc)();
    */
    static CCCallFunc * actionWithTarget(CCObject* pSelectorTarget, SEL_CallFunc selector);
    /** initializes the action with the callback 
    
    typedef void (CCObject::*SEL_CallFunc)();
    */
    virtual bool initWithTarget(CCObject* pSelectorTarget);
    /** executes the callback */
    virtual void execute();
    //super methods
    virtual void update(ccTime time);
    CCObject * copyWithZone(CCZone *pZone);

    inline CCObject* getTargetCallback()
    {
        return m_pSelectorTarget;
    }

    inline void setTargetCallback(CCObject* pSel)
    {
        if (pSel != m_pSelectorTarget)
        {
            if (m_pSelectorTarget)
            {
                m_pSelectorTarget->release();
            }
            
            m_pSelectorTarget = pSel;

            if (m_pSelectorTarget)
            {
                m_pSelectorTarget->retain();
            }                
        }
    }

protected:
    /** Target that will be called */
    CCObject*   m_pSelectorTarget;

    union
    {
        SEL_CallFunc    m_pCallFunc;
        SEL_CallFuncN    m_pCallFuncN;
        SEL_CallFuncND    m_pCallFuncND;
        SEL_CallFuncO   m_pCallFuncO;
    };
};

/** 
@brief Calls a 'callback' with the node as the first argument
N means Node
*/
class CC_DLL CCCallFuncN : public CCCallFunc
{
public:
    CCCallFuncN(){}
    virtual ~CCCallFuncN(){}
    /** creates the action with the callback 

    typedef void (CCObject::*SEL_CallFuncN)(CCNode*);
    */
    static CCCallFuncN * actionWithTarget(CCObject* pSelectorTarget, SEL_CallFuncN selector);
    /** initializes the action with the callback 

    typedef void (CCObject::*SEL_CallFuncN)(CCNode*);
    */
    virtual bool initWithTarget(CCObject* pSelectorTarget, SEL_CallFuncN selector);
    // super methods
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void execute();
};


/** 
@brief Calls a 'callback' with the node as the first argument and the 2nd argument is data
* ND means: Node and Data. Data is void *, so it could be anything.
*/
class CC_DLL CCCallFuncND : public CCCallFuncN
{
public:

    /** creates the action with the callback and the data to pass as an argument */
    static CCCallFuncND * actionWithTarget(CCObject* pSelectorTarget, SEL_CallFuncND selector, void* d);
    /** initializes the action with the callback and the data to pass as an argument */
    virtual bool initWithTarget(CCObject* pSelectorTarget, SEL_CallFuncND selector, void* d);
    // super methods
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void execute();

protected:
    void            *m_pData;
};


/**
@brief Calls a 'callback' with an object as the first argument.
O means Object.
@since v0.99.5
*/
class CC_DLL CCCallFuncO : public CCCallFunc
{
public:
    CCCallFuncO();
    virtual ~CCCallFuncO();
    /** creates the action with the callback 

    typedef void (CCObject::*SEL_CallFuncO)(CCObject*);
    */
    static CCCallFuncO * actionWithTarget(CCObject* pSelectorTarget, SEL_CallFuncO selector, CCObject* pObject);
    /** initializes the action with the callback 

    typedef void (CCObject::*SEL_CallFuncO)(CCObject*);
    */
    virtual bool initWithTarget(CCObject* pSelectorTarget, SEL_CallFuncO selector, CCObject* pObject);
    // super methods
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void execute();

    inline CCObject* getObject()
    {
        return m_pObject;
    }

    inline void setObject(CCObject* pObj)
    {
        if (pObj != m_pObject)
        {
            CC_SAFE_RELEASE(m_pObject);
            m_pObject = pObj;
            CC_SAFE_RETAIN(m_pObject);
        }
    }

protected:
    /** object to be passed as argument */
    CCObject* m_pObject;
};

NS_CC_END

#endif //__CCINSTANT_ACTION_H__
