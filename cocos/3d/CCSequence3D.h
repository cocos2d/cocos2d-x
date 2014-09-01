/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCSEQUECE3D_H__
#define __CCSEQUECE3D_H__

#include "2d/CCActionInterval.h"
#include "3d/CCAnimate3D.h"

NS_CC_BEGIN

/**
 * It is similar to Sequence in 2D action
 * But it is only used to sequence Animate3D
 * The difference between Sequence and Sequence3D is that Sequence3D play animation one by one and with some overlap time. We use the overlap time to make the transition between one action to another. The comming action fades in and the previous one fades out.
 */
class CC_3D_DLL Sequence3D : public ActionInterval
{
public:
        /** helper constructor to create an array of sequenceable actions */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // WP8 in VS2012 does not support nullptr in variable args lists and variadic templates are also not supported
    typedef Animate3D* M;
    static Sequence3D* create(M m1, std::nullptr_t listEnd) { return variadicCreate(m1, NULL); }
    static Sequence3D* create(M m1, M m2, std::nullptr_t listEnd) { return variadicCreate(m1, m2, NULL); }
    static Sequence3D* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, NULL); }
    static Sequence3D* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, NULL); }
    static Sequence3D* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, NULL); }
    static Sequence3D* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, NULL); }
    static Sequence3D* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static Sequence3D* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static Sequence3D* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static Sequence3D* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for variable argument lists longer than 10 items, use the other create functions or variadicCreate with NULL as the last argument
    static Sequence3D* variadicCreate(Animate3D* item, ...);
#else
    static Sequence3D* create(Animate3D *action1, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /** helper constructor to create an array of sequenceable actions given an array
     * @code
     * When this funtion bound to the js or lua,the input params changed
     * in js  :var   create(var   object1,var   object2, ...)
     * in lua :local create(local object1,local object2, ...)
     * @endcode
     */
    static Sequence3D* create(const Vector<Animate3D*>& arrayOfActions);
    /** helper constructor to create an array of sequence-able actions */
    static Sequence3D* createWithVariableList(Animate3D *action1, va_list args);

    //
    // Overrides
    //
    virtual Sequence3D* clone() const override;
    virtual Sequence3D* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float t) override;
    
CC_CONSTRUCTOR_ACCESS:
    Sequence3D();
    virtual ~Sequence3D(void);

    /** initializes the action */    
    bool initWithActions(const Vector<Animate3D*>& arrayOfActions);

protected:
    Vector<Animate3D*> _actions;
    int                _curActionIdx;
    std::vector<float> _startTime;
    std::vector<float> _endTime;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Sequence3D);

};

NS_CC_END

#endif // __CCSEQUECE3D_H__
