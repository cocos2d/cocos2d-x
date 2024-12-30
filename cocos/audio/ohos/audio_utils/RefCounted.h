/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once

#include "platform/CCPlatformMacros.h"

#define CC_REF_LEAK_DETECTION 0

namespace cocos2d { namespace experimental {

class RefCounted;

/**
  * Interface that defines how to clone an Ref.
  */
class  Clonable {
public:
    /** Returns a copy of the Ref. */
    virtual Clonable *clone() const = 0;

    virtual ~Clonable() = default;
};

/**
 * Ref is used for reference count management. If a class inherits from Ref,
 * then it is easy to be shared in different places.
 */
class RefCounted {
public:
    virtual ~RefCounted();

    /**
     * Retains the ownership.
     *
     * This increases the Ref's reference count.
     *
     * @see release, autorelease
     */
    void addRef();

    /**
     * Releases the ownership immediately.
     *
     * This decrements the Ref's reference count.
     *
     * If the reference count reaches 0 after the decrement, this Ref is
     * destructed.
     *
     * @see retain, autorelease
     */
    void release();

    /**
     * Returns the Ref's current reference count.
     *
     * @returns The Ref's reference count.
     */
    unsigned int getRefCount() const;

protected:
    /**
     * Constructor
     *
     * The Ref's reference count is 1 after construction.
     */
    RefCounted();

    /// count of references
    unsigned int _referenceCount{0};

    // Memory leak diagnostic data (only included when CC_REF_LEAK_DETECTION is defined and its value isn't zero)
#if CC_REF_LEAK_DETECTION
public:
    static void printLeaks();
#endif
};

using SCHEDULE_CB = void (RefCounted::*)(float);
#define CC_SCHEDULE_CALLBACK(cb) static_cast<cc::SCHEDULE_CB>(&cb)

}} // namespace CocosDenshion
