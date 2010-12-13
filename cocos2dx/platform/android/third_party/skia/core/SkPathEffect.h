/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkPathEffect_DEFINED
#define SkPathEffect_DEFINED

#include "SkFlattenable.h"

class SkPath;

/** \class SkPathEffect

    SkPathEffect is the base class for objects in the SkPaint that affect
    the geometry of a drawing primitive before it is transformed by the
    canvas' matrix and drawn.

    Dashing is implemented as a subclass of SkPathEffect.
*/
class SkPathEffect : public SkFlattenable {
public:
    //  This method is not exported to java.
    SkPathEffect() {}

    /** Given a src path and a width value, return true if the patheffect
        has produced a new path (dst) and a new width value. If false is returned,
        ignore dst and width.
        On input, width >= 0 means the src should be stroked
        On output, width >= 0 means the dst should be stroked
    */
    virtual bool filterPath(SkPath* dst, const SkPath& src, SkScalar* width) = 0;

private:
    // illegal
    SkPathEffect(const SkPathEffect&);
    SkPathEffect& operator=(const SkPathEffect&);
};

/** \class SkPairPathEffect

    Common baseclass for Compose and Sum. This subclass manages two pathEffects,
    including flattening them. It does nothing in filterPath, and is only useful
    for managing the lifetimes of its two arguments.
*/
class SkPairPathEffect : public SkPathEffect {
public:
    SkPairPathEffect(SkPathEffect* pe0, SkPathEffect* pe1);
    virtual ~SkPairPathEffect();

protected:
    SkPairPathEffect(SkFlattenableReadBuffer&);
    virtual void flatten(SkFlattenableWriteBuffer&);
    // these are visible to our subclasses
    SkPathEffect* fPE0, *fPE1;
    
private:
    typedef SkPathEffect INHERITED;
};

/** \class SkComposePathEffect

    This subclass of SkPathEffect composes its two arguments, to create
    a compound pathEffect.
*/
class SkComposePathEffect : public SkPairPathEffect {
public:
    /** Construct a pathEffect whose effect is to apply first the inner pathEffect
        and the the outer pathEffect (e.g. outer(inner(path)))
        The reference counts for outer and inner are both incremented in the constructor,
        and decremented in the destructor.
    */
    SkComposePathEffect(SkPathEffect* outer, SkPathEffect* inner)
        : INHERITED(outer, inner) {}

    // overrides
    
    //  This method is not exported to java.
    virtual bool filterPath(SkPath* dst, const SkPath& src, SkScalar* width);

protected:
    virtual Factory getFactory() { return CreateProc; }

private:
    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer) {
        return SkNEW_ARGS(SkComposePathEffect, (buffer));
    }
    SkComposePathEffect(SkFlattenableReadBuffer& buffer) : INHERITED(buffer) {}

    // illegal
    SkComposePathEffect(const SkComposePathEffect&);
    SkComposePathEffect& operator=(const SkComposePathEffect&);
    
    typedef SkPairPathEffect INHERITED;
};

/** \class SkSumPathEffect

    This subclass of SkPathEffect applies two pathEffects, one after the other.
    Its filterPath() returns true if either of the effects succeeded.
*/
class SkSumPathEffect : public SkPairPathEffect {
public:
    /** Construct a pathEffect whose effect is to apply two effects, in sequence.
        (e.g. first(path) + second(path))
        The reference counts for first and second are both incremented in the constructor,
        and decremented in the destructor.
    */
    SkSumPathEffect(SkPathEffect* first, SkPathEffect* second)
        : INHERITED(first, second) {}

    // overrides
    //  This method is not exported to java.
    virtual bool filterPath(SkPath* dst, const SkPath& src, SkScalar* width);

protected:
    virtual Factory getFactory() { return CreateProc; }

private:
    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer)  {
        return SkNEW_ARGS(SkSumPathEffect, (buffer));
    }
    SkSumPathEffect(SkFlattenableReadBuffer& buffer) : INHERITED(buffer) {}

    // illegal
    SkSumPathEffect(const SkSumPathEffect&);
    SkSumPathEffect& operator=(const SkSumPathEffect&);

    typedef SkPairPathEffect INHERITED;
};

#endif

