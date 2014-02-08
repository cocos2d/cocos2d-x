/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_ProfilingStack_h
#define js_ProfilingStack_h

#include "mozilla/NullPtr.h"
 
#include "jsbytecode.h"
#include "jstypes.h"

#include "js/Utility.h"

struct JSRuntime;

namespace js {

// A call stack can be specified to the JS engine such that all JS entry/exits
// to functions push/pop an entry to/from the specified stack.
//
// For more detailed information, see vm/SPSProfiler.h.
//
class ProfileEntry
{
    // All fields are marked volatile to prevent the compiler from re-ordering
    // instructions. Namely this sequence:
    //
    //    entry[size] = ...;
    //    size++;
    //
    // If the size modification were somehow reordered before the stores, then
    // if a sample were taken it would be examining bogus information.
    //
    // A ProfileEntry represents both a C++ profile entry and a JS one. Both use
    // the string as a description, but JS uses the sp as nullptr to indicate
    // that it is a JS entry. The script_ is then only ever examined for a JS
    // entry, and the idx is used by both, but with different meanings.
    //
    const char * volatile string; // Descriptive string of this entry
    void * volatile sp;           // Relevant stack pointer for the entry
    JSScript * volatile script_;  // if js(), non-null script which is running
    int32_t volatile idx;         // if js(), idx of pc, otherwise line number

  public:
    // All of these methods are marked with the 'volatile' keyword because SPS's
    // representation of the stack is stored such that all ProfileEntry
    // instances are volatile. These methods would not be available unless they
    // were marked as volatile as well.

    bool js() volatile {
        JS_ASSERT_IF(sp == nullptr, script_ != nullptr);
        return sp == nullptr;
    }

    uint32_t line() volatile { JS_ASSERT(!js()); return idx; }
    JSScript *script() volatile { JS_ASSERT(js()); return script_; }
    void *stackAddress() volatile { return sp; }
    const char *label() volatile { return string; }

    void setLine(uint32_t aLine) volatile { JS_ASSERT(!js()); idx = aLine; }
    void setLabel(const char *aString) volatile { string = aString; }
    void setStackAddress(void *aSp) volatile { sp = aSp; }
    void setScript(JSScript *aScript) volatile { script_ = aScript; }

    // We can't know the layout of JSScript, so look in vm/SPSProfiler.cpp.
    JS_FRIEND_API(jsbytecode *) pc() volatile;
    JS_FRIEND_API(void) setPC(jsbytecode *pc) volatile;

    static size_t offsetOfString() { return offsetof(ProfileEntry, string); }
    static size_t offsetOfStackAddress() { return offsetof(ProfileEntry, sp); }
    static size_t offsetOfPCIdx() { return offsetof(ProfileEntry, idx); }
    static size_t offsetOfScript() { return offsetof(ProfileEntry, script_); }

    // The index used in the entry can either be a line number or the offset of
    // a pc into a script's code. To signify a nullptr pc, use a -1 index. This
    // is checked against in pc() and setPC() to set/get the right pc.
    static const int32_t NullPCIndex = -1;
};

JS_FRIEND_API(void)
SetRuntimeProfilingStack(JSRuntime *rt, ProfileEntry *stack, uint32_t *size,
                         uint32_t max);

JS_FRIEND_API(void)
EnableRuntimeProfilingStack(JSRuntime *rt, bool enabled);

JS_FRIEND_API(jsbytecode*)
ProfilingGetPC(JSRuntime *rt, JSScript *script, void *ip);

} // namespace js

#endif  /* js_ProfilingStack_h */
