/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef jsatom_h___
#define jsatom_h___

#include <stddef.h>
#include "jsversion.h"
#include "jsalloc.h"
#include "jsapi.h"
#include "jsprvtd.h"
#include "jshash.h"
#include "jspubtd.h"
#include "jslock.h"

#include "gc/Barrier.h"
#include "js/HashTable.h"

struct JSIdArray {
    int length;
    js::HeapId vector[1];    /* actually, length jsid words */
};

/* Engine-internal extensions of jsid */

static JS_ALWAYS_INLINE jsid
JSID_FROM_BITS(size_t bits)
{
    jsid id;
    JSID_BITS(id) = bits;
    return id;
}

static JS_ALWAYS_INLINE jsid
ATOM_TO_JSID(JSAtom *atom)
{
    JS_ASSERT(((size_t)atom & 0x7) == 0);
    return JSID_FROM_BITS((size_t)atom);
}

/* All strings stored in jsids are atomized. */
static JS_ALWAYS_INLINE JSBool
JSID_IS_ATOM(jsid id)
{
    return JSID_IS_STRING(id);
}

static JS_ALWAYS_INLINE JSBool
JSID_IS_ATOM(jsid id, JSAtom *atom)
{
    return JSID_BITS(id) == JSID_BITS(ATOM_TO_JSID(atom));
}

static JS_ALWAYS_INLINE JSAtom *
JSID_TO_ATOM(jsid id)
{
    return (JSAtom *)JSID_TO_STRING(id);
}

extern jsid
js_CheckForStringIndex(jsid id);

JS_STATIC_ASSERT(sizeof(JSHashNumber) == 4);
JS_STATIC_ASSERT(sizeof(jsid) == JS_BYTES_PER_WORD);

namespace js {

static JS_ALWAYS_INLINE JSHashNumber
HashId(jsid id)
{
    JS_ASSERT(js_CheckForStringIndex(id) == id);
    JSHashNumber n =
#if JS_BYTES_PER_WORD == 4
        JSHashNumber(JSID_BITS(id));
#elif JS_BYTES_PER_WORD == 8
        JSHashNumber(JSID_BITS(id)) ^ JSHashNumber(JSID_BITS(id) >> 32);
#else
# error "Unsupported configuration"
#endif
    return n * JS_GOLDEN_RATIO;
}

static JS_ALWAYS_INLINE Value
IdToValue(jsid id)
{
    if (JSID_IS_STRING(id))
        return StringValue(JSID_TO_STRING(id));
    if (JS_LIKELY(JSID_IS_INT(id)))
        return Int32Value(JSID_TO_INT(id));
    if (JS_LIKELY(JSID_IS_OBJECT(id)))
        return ObjectValue(*JSID_TO_OBJECT(id));
    JS_ASSERT(JSID_IS_DEFAULT_XML_NAMESPACE(id) || JSID_IS_VOID(id));
    return UndefinedValue();
}

static JS_ALWAYS_INLINE jsval
IdToJsval(jsid id)
{
    return IdToValue(id);
}

template<>
struct DefaultHasher<jsid>
{
    typedef jsid Lookup;
    static HashNumber hash(const Lookup &l) {
        JS_ASSERT(l == js_CheckForStringIndex(l));
        return HashNumber(JSID_BITS(l));
    }
    static bool match(const jsid &id, const Lookup &l) {
        JS_ASSERT(l == js_CheckForStringIndex(l));
        return id == l;
    }
};

}

#if JS_BYTES_PER_WORD == 4
# define ATOM_HASH(atom)          ((JSHashNumber)(atom) >> 2)
#elif JS_BYTES_PER_WORD == 8
# define ATOM_HASH(atom)          (((JSHashNumber)(uintptr_t)(atom) >> 3) ^   \
                                   (JSHashNumber)((uintptr_t)(atom) >> 32))
#else
# error "Unsupported configuration"
#endif

/*
 * Return a printable, lossless char[] representation of a string-type atom.
 * The lifetime of the result matches the lifetime of bytes.
 */
extern const char *
js_AtomToPrintableString(JSContext *cx, JSAtom *atom, JSAutoByteString *bytes);

namespace js {

/* Compute a hash function from chars/length. */
inline uint32_t
HashChars(const jschar *chars, size_t length)
{
    uint32_t h = 0;
    for (; length; chars++, length--)
        h = JS_ROTATE_LEFT32(h, 4) ^ *chars;
    return h;
}

class AtomStateEntry
{
    uintptr_t bits;

    static const uintptr_t NO_TAG_MASK = uintptr_t(-1) - 1;

  public:
    AtomStateEntry() : bits(0) {}
    AtomStateEntry(const AtomStateEntry &other) : bits(other.bits) {}
    AtomStateEntry(JSAtom *ptr, bool tagged)
      : bits(uintptr_t(ptr) | uintptr_t(tagged))
    {
        JS_ASSERT((uintptr_t(ptr) & 0x1) == 0);
    }

    bool isTagged() const {
        return bits & 0x1;
    }

    /*
     * Non-branching code sequence. Note that the const_cast is safe because
     * the hash function doesn't consider the tag to be a portion of the key.
     */
    void setTagged(bool enabled) const {
        const_cast<AtomStateEntry *>(this)->bits |= uintptr_t(enabled);
    }

    JSAtom *asPtr() const;
};

struct AtomHasher
{
    struct Lookup
    {
        const jschar    *chars;
        size_t          length;
        const JSAtom    *atom; /* Optional. */

        Lookup(const jschar *chars, size_t length) : chars(chars), length(length), atom(NULL) {}
        inline Lookup(const JSAtom *atom);
    };

    static HashNumber hash(const Lookup &l) { return HashChars(l.chars, l.length); }
    static inline bool match(const AtomStateEntry &entry, const Lookup &lookup);
};

typedef HashSet<AtomStateEntry, AtomHasher, SystemAllocPolicy> AtomSet;

/*
 * On encodings:
 *
 * - Some string functions have an optional FlationCoding argument that allow
 *   the caller to force CESU-8 encoding handling. 
 * - Functions that don't take a FlationCoding base their NormalEncoding
 *   behavior on the js_CStringsAreUTF8 value. NormalEncoding is either raw
 *   (simple zero-extension) or UTF-8 depending on js_CStringsAreUTF8.
 * - Functions that explicitly state their encoding do not use the
 *   js_CStringsAreUTF8 value.
 *
 * CESU-8 (Compatibility Encoding Scheme for UTF-16: 8-bit) is a variant of
 * UTF-8 that allows us to store any wide character string as a narrow
 * character string. For strings containing mostly ascii, it saves space.
 * http://www.unicode.org/reports/tr26/
 */

enum FlationCoding
{
    NormalEncoding,
    CESU8Encoding
};

class PropertyName;

}  /* namespace js */

struct JSAtomState
{
    js::AtomSet         atoms;

    /*
     * From this point until the end of struct definition the struct must
     * contain only js::PropertyName fields. We use this to access the storage
     * occupied by the common atoms in js_FinishCommonAtoms.
     *
     * js_common_atom_names defined in jsatom.cpp contains C strings for atoms
     * in the order of atom fields here. Therefore you must update that array
     * if you change member order here.
     */

    /* The rt->emptyString atom, see jsstr.c's js_InitRuntimeStringState. */
    js::PropertyName    *emptyAtom;

    /*
     * Literal value and type names.
     * NB: booleanAtoms must come right before typeAtoms!
     */
    js::PropertyName    *booleanAtoms[2];
    js::PropertyName    *typeAtoms[JSTYPE_LIMIT];
    js::PropertyName    *nullAtom;

    /* Standard class constructor or prototype names. */
    js::PropertyName    *classAtoms[JSProto_LIMIT];

    /* Various built-in or commonly-used atoms, pinned on first context. */
#define DEFINE_ATOM(id, text)          js::PropertyName *id##Atom;
#define DEFINE_PROTOTYPE_ATOM(id)      js::PropertyName *id##Atom;
#define DEFINE_KEYWORD_ATOM(id)        js::PropertyName *id##Atom;
#include "jsatom.tbl"
#undef DEFINE_ATOM
#undef DEFINE_PROTOTYPE_ATOM
#undef DEFINE_KEYWORD_ATOM

    /* Less frequently used atoms, pinned lazily by JS_ResolveStandardClass. */
    struct {
        js::PropertyName *XMLListAtom;
        js::PropertyName *decodeURIAtom;
        js::PropertyName *decodeURIComponentAtom;
        js::PropertyName *defineGetterAtom;
        js::PropertyName *defineSetterAtom;
        js::PropertyName *encodeURIAtom;
        js::PropertyName *encodeURIComponentAtom;
        js::PropertyName *escapeAtom;
        js::PropertyName *hasOwnPropertyAtom;
        js::PropertyName *isFiniteAtom;
        js::PropertyName *isNaNAtom;
        js::PropertyName *isPrototypeOfAtom;
        js::PropertyName *isXMLNameAtom;
        js::PropertyName *lookupGetterAtom;
        js::PropertyName *lookupSetterAtom;
        js::PropertyName *parseFloatAtom;
        js::PropertyName *parseIntAtom;
        js::PropertyName *propertyIsEnumerableAtom;
        js::PropertyName *unescapeAtom;
        js::PropertyName *unevalAtom;
        js::PropertyName *unwatchAtom;
        js::PropertyName *watchAtom;
    } lazy;

    static const size_t commonAtomsOffset;
    static const size_t lazyAtomsOffset;

    void clearLazyAtoms() {
        memset(&lazy, 0, sizeof(lazy));
    }

    void junkAtoms() {
#ifdef DEBUG
        memset(commonAtomsStart(), JS_FREE_PATTERN, sizeof(*this) - commonAtomsOffset);
#endif
    }

    JSAtom **commonAtomsStart() {
        return reinterpret_cast<JSAtom **>(&emptyAtom);
    }

    void checkStaticInvariants();
};

extern bool
AtomIsInterned(JSContext *cx, JSAtom *atom);

#define ATOM(name) cx->runtime->atomState.name##Atom

#define COMMON_ATOM_INDEX(name)                                               \
    ((offsetof(JSAtomState, name##Atom) - JSAtomState::commonAtomsOffset)     \
     / sizeof(JSAtom*))
#define COMMON_TYPE_ATOM_INDEX(type)                                          \
    ((offsetof(JSAtomState, typeAtoms[type]) - JSAtomState::commonAtomsOffset)\
     / sizeof(JSAtom*))

#define ATOM_OFFSET(name)       offsetof(JSAtomState, name##Atom)
#define OFFSET_TO_ATOM(rt,off)  (*(JSAtom **)((char*)&(rt)->atomState + (off)))
#define CLASS_ATOM_OFFSET(name) offsetof(JSAtomState, classAtoms[JSProto_##name])
#define CLASS_ATOM(cx,name)     ((cx)->runtime->atomState.classAtoms[JSProto_##name])

extern const char *const js_common_atom_names[];
extern const size_t      js_common_atom_count;

/*
 * Macros to access C strings for JSType and boolean literals.
 */
#define JS_BOOLEAN_STR(type) (js_common_atom_names[1 + (type)])
#define JS_TYPE_STR(type)    (js_common_atom_names[1 + 2 + (type)])

/* Type names. */
extern const char   js_object_str[];
extern const char   js_undefined_str[];

/* Well-known predefined C strings. */
#define JS_PROTO(name,code,init) extern const char js_##name##_str[];
#include "jsproto.tbl"
#undef JS_PROTO

#define DEFINE_ATOM(id, text)  extern const char js_##id##_str[];
#define DEFINE_PROTOTYPE_ATOM(id)
#define DEFINE_KEYWORD_ATOM(id)
#include "jsatom.tbl"
#undef DEFINE_ATOM
#undef DEFINE_PROTOTYPE_ATOM
#undef DEFINE_KEYWORD_ATOM

#if JS_HAS_GENERATORS
extern const char   js_close_str[];
extern const char   js_send_str[];
#endif

/* Constant strings that are not atomized. */
extern const char   js_getter_str[];
extern const char   js_setter_str[];

/*
 * Initialize atom state. Return true on success, false on failure to allocate
 * memory. The caller must zero rt->atomState before calling this function and
 * only call it after js_InitGC successfully returns.
 */
extern JSBool
js_InitAtomState(JSRuntime *rt);

/*
 * Free and clear atom state including any interned string atoms. This
 * function must be called before js_FinishGC.
 */
extern void
js_FinishAtomState(JSRuntime *rt);

/*
 * Atom tracing and garbage collection hooks.
 */

namespace js {

extern void
MarkAtomState(JSTracer *trc, bool markAll);

extern void
SweepAtomState(JSRuntime *rt);

extern bool
InitCommonAtoms(JSContext *cx);

extern void
FinishCommonAtoms(JSRuntime *rt);

/* N.B. must correspond to boolean tagging behavior. */
enum InternBehavior
{
    DoNotInternAtom = false,
    InternAtom = true
};

}  /* namespace js */

extern JSAtom *
js_Atomize(JSContext *cx, const char *bytes, size_t length,
           js::InternBehavior ib = js::DoNotInternAtom,
           js::FlationCoding fc = js::NormalEncoding);

extern JSAtom *
js_AtomizeChars(JSContext *cx, const jschar *chars, size_t length,
                js::InternBehavior ib = js::DoNotInternAtom);

extern JSAtom *
js_AtomizeString(JSContext *cx, JSString *str, js::InternBehavior ib = js::DoNotInternAtom);

/*
 * Return an existing atom for the given char array or null if the char
 * sequence is currently not atomized.
 */
extern JSAtom *
js_GetExistingStringAtom(JSContext *cx, const jschar *chars, size_t length);

#ifdef DEBUG

extern JS_FRIEND_API(void)
js_DumpAtoms(JSContext *cx, FILE *fp);

#endif

inline bool
js_ValueToAtom(JSContext *cx, const js::Value &v, JSAtom **atomp);

inline bool
js_ValueToStringId(JSContext *cx, const js::Value &v, jsid *idp);

inline bool
js_InternNonIntElementId(JSContext *cx, JSObject *obj, const js::Value &idval,
                         jsid *idp);
inline bool
js_InternNonIntElementId(JSContext *cx, JSObject *obj, const js::Value &idval,
                         jsid *idp, js::Value *vp);

namespace js {

/*
 * For all unmapped atoms recorded in al, add a mapping from the atom's index
 * to its address. map->length must already be set to the number of atoms in
 * the list and map->vector must point to pre-allocated memory.
 */
extern void
InitAtomMap(JSContext *cx, AtomIndexMap *indices, HeapPtrAtom *atoms);

template<XDRMode mode>
bool
XDRAtom(XDRState<mode> *xdr, JSAtom **atomp);

} /* namespace js */

#endif /* jsatom_h___ */
