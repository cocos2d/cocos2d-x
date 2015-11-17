/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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

#ifndef __BASE_CCREF_H__
#define __BASE_CCREF_H__

#include "platform/CCPlatformMacros.h"
#include "base/ccConfig.h"

#define CC_REF_LEAK_DETECTION 0

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN


class Ref;

/** 
  * Interface that defines how to clone an Ref.
  * @lua NA
  * @js NA
  */
class CC_DLL Clonable
{
public:
    /** Returns a copy of the Ref. */
    virtual Clonable* clone() const = 0;
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Clonable() {};

    /** Returns a copy of the Ref.
     * @deprecated Use clone() instead.
     */
    CC_DEPRECATED_ATTRIBUTE Ref* copy() const
    {
        // use "clone" instead
        CC_ASSERT(false);
        return nullptr;
    }
};

/**
 * Ref is used for reference count management. If a class inherits from Ref,
 * then it is easy to be shared in different places.
 * @js NA
 */
class CC_DLL Ref
{
public:
    /**
     * Retains the ownership.
     *
     * This increases the Ref's reference count.
     *
     * @see release, autorelease
     * @js NA
     */
    void retain();

    /**
     * Releases the ownership immediately.
     *
     * This decrements the Ref's reference count.
     *
     * If the reference count reaches 0 after the decrement, this Ref is
     * destructed.
     *
     * @see retain, autorelease
     * @js NA
     */
    void release();

    /**
     * Releases the ownership sometime soon automatically.
     *
     * This decrements the Ref's reference count at the end of current
     * autorelease pool block.
     *
     * If the reference count reaches 0 after the decrement, this Ref is
     * destructed.
     *
     * @returns The Ref itself.
     *
     * @see AutoreleasePool, retain, release
     * @js NA
     * @lua NA
     */
    Ref* autorelease();

    /**
     * Returns the Ref's current reference count.
     *
     * @returns The Ref's reference count.
     * @js NA
     */
    unsigned int getReferenceCount() const;

protected:
    /**
     * Constructor
     *
     * The Ref's reference count is 1 after construction.
     * @js NA
     */
    Ref();

public:
    /**
     * Destructor
     *
     * @js NA
     * @lua NA
     */
    virtual ~Ref();

protected:
    /// count of references
    unsigned int _referenceCount;

    friend class AutoreleasePool;

#if CC_ENABLE_SCRIPT_BINDING
public:
    /// object id, ScriptSupport need public _ID
    unsigned int        _ID;
    /// Lua reference id
    int                 _luaID;
    /// scriptObject, support for swift
    void* _scriptObject;
#endif

    // Memory leak diagnostic data (only included when CC_REF_LEAK_DETECTION is defined and its value isn't zero)
#if CC_REF_LEAK_DETECTION
public:
    static void printLeaks();
#endif
};

class Node;

typedef void (Ref::*SEL_CallFunc)();
typedef void (Ref::*SEL_CallFuncN)(Node*);
typedef void (Ref::*SEL_CallFuncND)(Node*, void*);
typedef void (Ref::*SEL_CallFuncO)(Ref*);
typedef void (Ref::*SEL_MenuHandler)(Ref*);
typedef void (Ref::*SEL_SCHEDULE)(float);

#define CC_CALLFUNC_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFunc>(&_SELECTOR)
#define CC_CALLFUNCN_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFuncN>(&_SELECTOR)
#define CC_CALLFUNCND_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFuncND>(&_SELECTOR)
#define CC_CALLFUNCO_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFuncO>(&_SELECTOR)
#define CC_MENU_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_MenuHandler>(&_SELECTOR)
#define CC_SCHEDULE_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)

// Deprecated
#define callfunc_selector(_SELECTOR) CC_CALLFUNC_SELECTOR(_SELECTOR)
#define callfuncN_selector(_SELECTOR) CC_CALLFUNCN_SELECTOR(_SELECTOR)
#define callfuncND_selector(_SELECTOR) CC_CALLFUNCND_SELECTOR(_SELECTOR)
#define callfuncO_selector(_SELECTOR) CC_CALLFUNCO_SELECTOR(_SELECTOR)
#define menu_selector(_SELECTOR) CC_MENU_SELECTOR(_SELECTOR)
#define schedule_selector(_SELECTOR) CC_SCHEDULE_SELECTOR(_SELECTOR)



NS_CC_END
// end of base group
/** @} */

#endif // __BASE_CCREF_H__
