/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Helper classes encapsulating access to the callee, |this| value, arguments,
 * and argument count for a function call.
 *
 * The intent of JS::CallArgs and JS::CallReceiver is that they be used to
 * encapsulate access to the un-abstracted |unsigned argc, Value *vp| arguments
 * to a function.  It's possible (albeit deprecated) to manually index into
 * |vp| to access the callee, |this|, and arguments of a function, and to set
 * its return value.  It's also possible to use the supported API of JS_CALLEE,
 * JS_THIS, JS_ARGV, JS_RVAL and JS_SET_RVAL to the same ends.  But neither API
 * has the error-handling or moving-GC correctness of CallArgs or CallReceiver.
 * New code should use CallArgs and CallReceiver instead whenever possible.
 *
 * The eventual plan is to change JSNative to take |const CallArgs&| directly,
 * for automatic assertion of correct use and to make calling functions more
 * efficient.  Embedders should start internally switching away from using
 * |argc| and |vp| directly, except to create a |CallArgs|.  Then, when an
 * eventual release making that change occurs, porting efforts will require
 * changing methods' signatures but won't require invasive changes to the
 * methods' implementations, potentially under time pressure.
 */

#ifndef js_CallArgs_h___
#define js_CallArgs_h___

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"

#include "jstypes.h"

#include "js/RootingAPI.h"
#include "js/Value.h"

struct JSContext;
class JSObject;

/* Typedef for native functions called by the JS VM. */
typedef JSBool
(* JSNative)(JSContext *cx, unsigned argc, JS::Value *vp);

namespace JS {

/*
 * JS::CallReceiver encapsulates access to the callee, |this|, and eventual
 * return value for a function call.  The principal way to create a
 * CallReceiver is using JS::CallReceiverFromVp:
 *
 *   static JSBool
 *   FunctionReturningThis(JSContext *cx, unsigned argc, JS::Value *vp)
 *   {
 *       JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
 *
 *       // Access to the callee must occur before accessing/setting
 *       // the return value.
 *       JSObject &callee = rec.callee();
 *       rec.rval().set(JS::ObjectValue(callee));
 *
 *       // callee() and calleev() will now assert.
 *
 *       // It's always fine to access thisv().
 *       HandleValue thisv = rec.thisv();
 *       rec.thisv().set(thisv);
 *
 *       // As the return value was last set to |this|, returns |this|.
 *       return true;
 *   }
 *
 * A note on JS_ComputeThis and JS_THIS_OBJECT: these methods currently aren't
 * part of the CallReceiver interface.  We will likely add them at some point.
 * Until then, you should probably continue using |vp| directly for these two
 * cases.
 *
 * CallReceiver is exposed publicly and used internally.  Not all parts of its
 * public interface are meant to be used by embedders!  See inline comments to
 * for details.
 */
class CallReceiver
{
  protected:
#ifdef DEBUG
    mutable bool usedRval_;
    void setUsedRval() const { usedRval_ = true; }
    void clearUsedRval() const { usedRval_ = false; }
#else
    void setUsedRval() const {}
    void clearUsedRval() const {}
#endif

    Value *argv_;

    friend CallReceiver CallReceiverFromVp(Value *vp);
    friend CallReceiver CallReceiverFromArgv(Value *argv);

  public:
    /*
     * Returns the function being called, as an object.  Must not be called
     * after rval() has been used!
     */
    JSObject &callee() const {
        MOZ_ASSERT(!usedRval_);
        return argv_[-2].toObject();
    }

    /*
     * Returns the function being called, as a value.  Must not be called after
     * rval() has been used!
     */
    HandleValue calleev() const {
        MOZ_ASSERT(!usedRval_);
        return HandleValue::fromMarkedLocation(&argv_[-2]);
    }

    /*
     * Returns the |this| value passed to the function.  This method must not
     * be called when the function is being called as a constructor via |new|.
     * The value may or may not be an object: it is the individual function's
     * responsibility to box the value if needed.
     */
    HandleValue thisv() const {
        // Some internal code uses thisv() in constructing cases, so don't do
        // this yet.
        // MOZ_ASSERT(!argv_[-1].isMagic(JS_IS_CONSTRUCTING));
        return HandleValue::fromMarkedLocation(&argv_[-1]);
    }

    /*
     * Returns the currently-set return value.  The initial contents of this
     * value are unspecified.  Once this method has been called, callee() and
     * calleev() can no longer be used.  (If you're compiling against a debug
     * build of SpiderMonkey, these methods will assert to aid debugging.)
     *
     * If the method you're implementing succeeds by returning true, you *must*
     * set this.  (SpiderMonkey doesn't currently assert this, but it will do
     * so eventually.)  You don't need to use or change this if your method
     * fails.
     */
    MutableHandleValue rval() const {
        setUsedRval();
        return MutableHandleValue::fromMarkedLocation(&argv_[-2]);
    }

  public:
    // These methods are only intended for internal use.  Embedders shouldn't
    // use them!

    Value *base() const { return argv_ - 2; }

    Value *spAfterCall() const {
        setUsedRval();
        return argv_ - 1;
    }

  public:
    // These methods are publicly exposed, but they are *not* to be used when
    // implementing a JSNative method and encapsulating access to |vp| within
    // it.  You probably don't want to use these!

    void setCallee(Value aCalleev) const {
        clearUsedRval();
        argv_[-2] = aCalleev;
    }

    void setThis(Value aThisv) const {
        argv_[-1] = aThisv;
    }

    MutableHandleValue mutableThisv() const {
        return MutableHandleValue::fromMarkedLocation(&argv_[-1]);
    }
};

MOZ_ALWAYS_INLINE CallReceiver
CallReceiverFromArgv(Value *argv)
{
    CallReceiver receiver;
    receiver.clearUsedRval();
    receiver.argv_ = argv;
    return receiver;
}

MOZ_ALWAYS_INLINE CallReceiver
CallReceiverFromVp(Value *vp)
{
    return CallReceiverFromArgv(vp + 2);
}

/*
 * JS::CallArgs encapsulates everything JS::CallReceiver does, plus access to
 * the function call's arguments.  The principal way to create a CallArgs is
 * like so, using JS::CallArgsFromVp:
 *
 *   static JSBool
 *   FunctionReturningArgcTimesArg0(JSContext *cx, unsigned argc, JS::Value *vp)
 *   {
 *       JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
 *
 *       // Guard against no arguments or a non-numeric arg0.
 *       if (args.length() == 0 || !args[0].isNumber()) {
 *           args.rval().setInt32(0);
 *           return true;
 *       }
 *
 *       args.rval().set(JS::NumberValue(args.length() * args[0].toNumber()));
 *       return true;
 *   }
 *
 * CallArgs is exposed publicly and used internally.  Not all parts of its
 * public interface are meant to be used by embedders!  See inline comments to
 * for details.
 */
class CallArgs : public CallReceiver
{
  protected:
    unsigned argc_;

    friend CallArgs CallArgsFromVp(unsigned argc, Value *vp);
    friend CallArgs CallArgsFromSp(unsigned argc, Value *sp);

    static CallArgs create(unsigned argc, Value *argv) {
        CallArgs args;
        args.clearUsedRval();
        args.argv_ = argv;
        args.argc_ = argc;
        return args;
    }

  public:
    /* Returns the number of arguments. */
    unsigned length() const { return argc_; }

    /* Returns the i-th zero-indexed argument. */
    Value &operator[](unsigned i) const {
        MOZ_ASSERT(i < argc_);
        return argv_[i];
    }

    /* Returns a mutable handle for the i-th zero-indexed argument. */
    MutableHandleValue handleAt(unsigned i) {
        MOZ_ASSERT(i < argc_);
        return MutableHandleValue::fromMarkedLocation(&argv_[i]);
    }

    /* Returns a Handle for the i-th zero-indexed argument. */
    HandleValue handleAt(unsigned i) const {
        MOZ_ASSERT(i < argc_);
        return HandleValue::fromMarkedLocation(&argv_[i]);
    }

    /*
     * Returns the i-th zero-indexed argument, or |undefined| if there's no
     * such argument.
     */
    Value get(unsigned i) const {
        return i < length() ? argv_[i] : UndefinedValue();
    }

    /*
     * Returns true if the i-th zero-indexed argument is present and is not
     * |undefined|.
     */
    bool hasDefined(unsigned i) const {
        return i < argc_ && !argv_[i].isUndefined();
    }

  public:
    // These methods are publicly exposed, but we're less sure of the interface
    // here than we'd like (because they're hackish and drop assertions).  Try
    // to avoid using these if you can.

    Value *array() const { return argv_; }
    Value *end() const { return argv_ + argc_; }
};

MOZ_ALWAYS_INLINE CallArgs
CallArgsFromVp(unsigned argc, Value *vp)
{
    return CallArgs::create(argc, vp + 2);
}

// This method is only intended for internal use in SpiderMonkey.  We may
// eventually move it to an internal header.  Embedders should use
// JS::CallArgsFromVp!
MOZ_ALWAYS_INLINE CallArgs
CallArgsFromSp(unsigned argc, Value *sp)
{
    return CallArgs::create(argc, sp - argc);
}

} // namespace JS

/*
 * Compute |this| for the |vp| inside a JSNative, either boxing primitives or
 * replacing with the global object as necessary.
 *
 * This method will go away at some point: instead use |args.thisv()|.  If the
 * value is an object, no further work is required.  If that value is |null| or
 * |undefined|, use |JS_GetGlobalForObject| to compute the global object.  If
 * the value is some other primitive, use |JS_ValueToObject| to box it.
 */
extern JS_PUBLIC_API(JS::Value)
JS_ComputeThis(JSContext *cx, JS::Value *vp);

/*
 * Macros to hide interpreter stack layout details from a JSNative using its
 * JS::Value *vp parameter.  DO NOT USE THESE!  Instead use JS::CallArgs and
 * friends, above.  These macros will be removed when we change JSNative to
 * take a const JS::CallArgs&.
 */

#define JS_CALLEE(cx,vp)        ((vp)[0])
#define JS_THIS_OBJECT(cx,vp)   (JSVAL_TO_OBJECT(JS_THIS(cx,vp)))
#define JS_ARGV(cx,vp)          ((vp) + 2)
#define JS_RVAL(cx,vp)          (*(vp))
#define JS_SET_RVAL(cx,vp,v)    (*(vp) = (v))

/*
 * Note: if this method returns null, an error has occurred and must be
 * propagated or caught.
 */
MOZ_ALWAYS_INLINE JS::Value
JS_THIS(JSContext *cx, JS::Value *vp)
{
    return JSVAL_IS_PRIMITIVE(vp[1]) ? JS_ComputeThis(cx, vp) : vp[1];
}

/*
 * |this| is passed to functions in ES5 without change.  Functions themselves
 * do any post-processing they desire to box |this|, compute the global object,
 * &c.  This macro retrieves a function's unboxed |this| value.
 *
 * This macro must not be used in conjunction with JS_THIS or JS_THIS_OBJECT,
 * or vice versa.  Either use the provided this value with this macro, or
 * compute the boxed |this| value using those.  JS_THIS_VALUE must not be used
 * if the function is being called as a constructor.
 *
 * But: DO NOT USE THIS!  Instead use JS::CallArgs::thisv(), above.
 *
 */
#define JS_THIS_VALUE(cx,vp)    ((vp)[1])

#endif /* js_CallArgs_h___ */
