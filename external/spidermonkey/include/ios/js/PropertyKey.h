/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* JS::PropertyKey implementation. */

#ifndef js_PropertyKey_h
#define js_PropertyKey_h

#include "mozilla/Attributes.h"

#include "js/Value.h"

struct JSContext;

namespace JS {

class PropertyKey;

namespace detail {

extern JS_PUBLIC_API(bool)
ToPropertyKeySlow(JSContext *cx, HandleValue v, PropertyKey *key);

} // namespace detail

/*
 * A PropertyKey is a key used to access some property on an object.  It is a
 * natural way to represent a property accessed using a JavaScript value.
 *
 * PropertyKey can represent indexes, named properties, and ES6 symbols.  The
 * latter aren't implemented in SpiderMonkey yet, but PropertyKey carves out
 * space for them.
 */
class PropertyKey
{
    Value v;
    friend JS_PUBLIC_API(bool) detail::ToPropertyKeySlow(JSContext *cx, HandleValue v, PropertyKey *key);

  public:
    explicit PropertyKey(uint32_t index) : v(PrivateUint32Value(index)) {}

    /*
     * An index is a string property name whose characters exactly spell out an
     * unsigned 32-bit integer in decimal: "0", "1", "2", ...., "4294967294",
     * "4294967295".
     */
    bool isIndex(uint32_t *index) {
        // The implementation here assumes that private uint32_t are stored
        // using the int32_t representation.  This is purely an implementation
        // detail: embedders must not rely upon this!
        if (!v.isInt32())
            return false;
        *index = v.toPrivateUint32();
        return true;
    }

    /*
     * A name is a string property name which is *not* an index.  Note that by
     * the ECMAScript language grammar, any dotted property access |obj.prop|
     * will access a named property.
     */
    bool isName(JSString **str) {
        uint32_t dummy;
        if (isIndex(&dummy))
            return false;
        *str = v.toString();
        return true;
    }

    /*
     * A symbol is a property name that's a Symbol, a particular kind of object
     * in ES6.  It is the only kind of property name that's not a string.
     *
     * SpiderMonkey doesn't yet implement symbols, but we're carving out API
     * space for them in advance.
     */
    bool isSymbol() {
        return false;
    }
};

inline bool
ToPropertyKey(JSContext *cx, HandleValue v, PropertyKey *key)
{
    if (v.isInt32() && v.toInt32() >= 0) {
        *key = PropertyKey(uint32_t(v.toInt32()));
        return true;
    }

    return detail::ToPropertyKeySlow(cx, v, key);
}

} // namespace JS

#endif /* js_PropertyKey_h */
