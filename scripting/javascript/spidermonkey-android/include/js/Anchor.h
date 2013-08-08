/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* JS::Anchor implementation. */

#ifndef js_Anchor_h___
#define js_Anchor_h___

#include "mozilla/Attributes.h"

class JSFunction;
class JSObject;
class JSScript;
class JSString;

namespace JS { class Value; }

namespace JS {

/*
 * Protecting non-Value, non-JSObject *, non-JSString * values from collection
 *
 * Most of the time, the garbage collector's conservative stack scanner works
 * behind the scenes, finding all live values and protecting them from being
 * collected. However, when JSAPI client code obtains a pointer to data the
 * scanner does not know about, owned by an object the scanner does know about,
 * Care Must Be Taken.
 *
 * The scanner recognizes only a select set of types: pointers to JSObjects and
 * similar things (JSFunctions, and so on), pointers to JSStrings, and Values.
 * So while the scanner finds all live |JSString| pointers, it does not notice
 * |jschar| pointers.
 *
 * So suppose we have:
 *
 *   void f(JSString *str) {
 *     const jschar *ch = JS_GetStringCharsZ(str);
 *     ... do stuff with ch, but no uses of str ...;
 *   }
 *
 * After the call to |JS_GetStringCharsZ|, there are no further uses of
 * |str|, which means that the compiler is within its rights to not store
 * it anywhere. But because the stack scanner will not notice |ch|, there
 * is no longer any live value in this frame that would keep the string
 * alive. If |str| is the last reference to that |JSString|, and the
 * collector runs while we are using |ch|, the string's array of |jschar|s
 * may be freed out from under us.
 *
 * Note that there is only an issue when 1) we extract a thing X the scanner
 * doesn't recognize from 2) a thing Y the scanner does recognize, and 3) if Y
 * gets garbage-collected, then X gets freed. If we have code like this:
 *
 *   void g(JSObject *obj) {
 *     JS::Value x;
 *     JS_GetProperty(obj, "x", &x);
 *     ... do stuff with x ...
 *   }
 *
 * there's no problem, because the value we've extracted, x, is a Value, a
 * type that the conservative scanner recognizes.
 *
 * Conservative GC frees us from the obligation to explicitly root the types it
 * knows about, but when we work with derived values like |ch|, we must root
 * their owners, as the derived value alone won't keep them alive.
 *
 * A JS::Anchor is a kind of GC root that allows us to keep the owners of
 * derived values like |ch| alive throughout the Anchor's lifetime. We could
 * fix the above code as follows:
 *
 *   void f(JSString *str) {
 *     JS::Anchor<JSString *> a_str(str);
 *     const jschar *ch = JS_GetStringCharsZ(str);
 *     ... do stuff with ch, but no uses of str ...;
 *   }
 *
 * This simply ensures that |str| will be live until |a_str| goes out of scope.
 * As long as we don't retain a pointer to the string's characters for longer
 * than that, we have avoided all garbage collection hazards.
 */
template<typename T> class AnchorPermitted;
template<> class AnchorPermitted<JSObject *> { };
template<> class AnchorPermitted<const JSObject *> { };
template<> class AnchorPermitted<JSFunction *> { };
template<> class AnchorPermitted<const JSFunction *> { };
template<> class AnchorPermitted<JSString *> { };
template<> class AnchorPermitted<const JSString *> { };
template<> class AnchorPermitted<Value> { };
template<> class AnchorPermitted<const JSScript *> { };
template<> class AnchorPermitted<JSScript *> { };

template<typename T>
class Anchor : AnchorPermitted<T>
{
  public:
    Anchor() { }
    explicit Anchor(T t) { hold = t; }
    inline ~Anchor();
    T &get() { return hold; }
    const T &get() const { return hold; }
    void set(const T &t) { hold = t; }
    void operator=(const T &t) { hold = t; }
    void clear() { hold = 0; }

  private:
    T hold;
    Anchor(const Anchor &other) MOZ_DELETE;
    void operator=(const Anchor &other) MOZ_DELETE;
};

template<typename T>
inline Anchor<T>::~Anchor()
{
#ifdef __GNUC__
    /*
     * No code is generated for this. But because this is marked 'volatile', G++ will
     * assume it has important side-effects, and won't delete it. (G++ never looks at
     * the actual text and notices it's empty.) And because we have passed |hold| to
     * it, GCC will keep |hold| alive until this point.
     *
     * The "memory" clobber operand ensures that G++ will not move prior memory
     * accesses after the asm --- it's a barrier. Unfortunately, it also means that
     * G++ will assume that all memory has changed after the asm, as it would for a
     * call to an unknown function. I don't know of a way to avoid that consequence.
     */
    asm volatile("":: "g" (hold) : "memory");
#else
    /*
     * An adequate portable substitute, for non-structure types.
     *
     * The compiler promises that, by the end of an expression statement, the
     * last-stored value to a volatile object is the same as it would be in an
     * unoptimized, direct implementation (the "abstract machine" whose behavior the
     * language spec describes). However, the compiler is still free to reorder
     * non-volatile accesses across this store --- which is what we must prevent. So
     * assigning the held value to a volatile variable, as we do here, is not enough.
     *
     * In our case, however, garbage collection only occurs at function calls, so it
     * is sufficient to ensure that the destructor's store isn't moved earlier across
     * any function calls that could collect. It is hard to imagine the compiler
     * analyzing the program so thoroughly that it could prove that such motion was
     * safe. In practice, compilers treat calls to the collector as opaque operations
     * --- in particular, as operations which could access volatile variables, across
     * which this destructor must not be moved.
     *
     * ("Objection, your honor!  *Alleged* killer whale!")
     *
     * The disadvantage of this approach is that it does generate code for the store.
     * We do need to use Anchors in some cases where cycles are tight.
     *
     * Note that there is a Anchor<Value>::~Anchor() specialization in Value.h.
     */
    volatile T sink;
    sink = hold;
#endif  /* defined(__GNUC__) */
}

} // namespace JS

#endif /* js_Anchor_h___ */
